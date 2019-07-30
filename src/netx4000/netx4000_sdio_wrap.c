/***************************************************************************
 *   Copyright (C) 2019 by Hilscher GmbH                                   *
 *   cthelen@hilscher.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program. If not, see                          *
 *   <https://www.gnu.org/licenses/>.                                      *
 ***************************************************************************/

#include "netx4000_sdio_wrap.h"
#include "netx4000_sdio.h"
#include "portcontrol.h"
#include "uprintf.h"
#include "progress_bar.h"

/* Detection is unreliable when JTAG is used. 
   The problem does not seem to occur when ulInitialSpeedKHz is set to 800, 
   however, the standard requires max. 400 kHz during device identification. */

static const SDIO_OPTIONS_T tSdioOptions =
{
	.ulPowerUpTimeoutTicks = 200000U,    /* The timeout to get the SDIO core out of the power down mode. This is 1ms. */
	.ulResetDelayTicks     = 1000000U,   /* The delay between power enable and reset release. This is 5ms. */
	.ulInitialSpeedKHz = 400,            /* Start with 400kHz. */
	.ulMaximumSpeedKHz = 25000,          /* Allow a maximum of 25MHz. */
	.ulInitialClockGenerationUs = 3032,  /* Delay for 3032us, which is enough for the required 74 clock cycles at 400kHz. */
	.ausPortControl =
	{
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLDOWN50K),    /* SDIO_CLK  */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K),      /* SDIO_CMD  */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K),      /* SDIO_DAT0 */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K),      /* SDIO_DAT1 */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K),      /* SDIO_DAT2 */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K),      /* SDIO_DAT3 */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K),      /* SDIO_CD   */
		PORTCONTROL_CONFIGURATION(REEMUX_0, 0, REEMUX_DRV_08MA, REEMUX_UDC_PULLUP50K)       /* SDIO_WP   */
	},
	.ucHwTimeoutExponentInitialization = 20,
	.ucHwTimeoutExponentTransfer       = 27
};


/* must be a power of two */
#define SD_SECTOR_SIZE  (512)
#define SD_SECTOR_SIZE_LOG (9)
#define SD_SECTOR_SIZE_MSK (0x1ff)
 
typedef struct {
	unsigned long ulProgressCnt;
	
	unsigned long ulFlashAdr;
	unsigned long ulFlashEndAdr;
	unsigned char *pucDataAdr;
	
	unsigned long ulSectorId;
	unsigned long ulSectorOffset;
	unsigned long ulChunkLength;
	
	union {
		unsigned long aul[SD_SECTOR_SIZE/4];
		unsigned char auc[SD_SECTOR_SIZE];
	} tSector;
	
} FLASH_POSITIONS_T;


static void flashpos_init(FLASH_POSITIONS_T *ptFlashPos, 
	unsigned long ulFlashAddr, unsigned long ulFlashEndAddr, unsigned char *pucDataAddr) 
{
	ptFlashPos->ulFlashAdr = ulFlashAddr;
	ptFlashPos->ulFlashEndAdr = ulFlashEndAddr;
	ptFlashPos->pucDataAdr = pucDataAddr;

	ptFlashPos->ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAddr-ulFlashAddr);
	}

	
static int flashpos_get_chunk(FLASH_POSITIONS_T *ptFlashPos)
{
	int iRet = 0;
	unsigned long ulChunkLengthA;
	unsigned long ulChunkLengthB;
	
	if (ptFlashPos->ulFlashAdr < ptFlashPos->ulFlashEndAdr)
	{
		/* divide by sector size 512 bytes */
		ptFlashPos->ulSectorId = ptFlashPos->ulFlashAdr >> SD_SECTOR_SIZE_LOG; 
		
		/* take the offset in a 512 byte sector */
		ptFlashPos->ulSectorOffset = ptFlashPos->ulFlashAdr & SD_SECTOR_SIZE_MSK; 
		
		ulChunkLengthA = ptFlashPos->ulFlashEndAdr - ptFlashPos->ulFlashAdr;
		ulChunkLengthB = SD_SECTOR_SIZE - ptFlashPos->ulSectorOffset;
		ptFlashPos->ulChunkLength = ulChunkLengthA < ulChunkLengthB ? ulChunkLengthA : ulChunkLengthB;
		
		iRet = 1;
	}
	else
	{
		progress_bar_finalize();
	}
	
	return iRet;
}


static void flashpos_skip_chunk(FLASH_POSITIONS_T *ptFlashPos)
{
	ptFlashPos->pucDataAdr += ptFlashPos->ulChunkLength;
	ptFlashPos->ulFlashAdr += ptFlashPos->ulChunkLength;
	
	/* inc progress */
	ptFlashPos->ulProgressCnt += ptFlashPos->ulChunkLength;
	progress_bar_set_position(ptFlashPos->ulProgressCnt);
}


static NETX_CONSOLEAPP_RESULT_T flashpos_read_sector(FLASH_POSITIONS_T *ptFlashPos, 
	const SDIO_HANDLE_T *ptSdioHandle)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	/*uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", 
		ptFlashPos->ulFlashAdr, ptFlashPos->ulSectorId, ptFlashPos->ulSectorOffset);*/
	iResult = sdio_read_sector(ptSdioHandle, ptFlashPos->ulSectorId, ptFlashPos->tSector.aul);
	if( iResult!=0 )
	{
		uprintf("! failed to read sector %d!\n", ptFlashPos->ulSectorId);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	return tResult;
}


static NETX_CONSOLEAPP_RESULT_T flashpos_write_sector(FLASH_POSITIONS_T *ptFlashPos, 
	const SDIO_HANDLE_T *ptSdioHandle)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;

	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/*uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", 
		ptFlashPos->ulFlashAdr, ptFlashPos->ulSectorId, ptFlashPos->ulSectorOffset);*/
	iResult = sdio_write_sector(ptSdioHandle, ptFlashPos->ulSectorId, ptFlashPos->tSector.aul);
	if( iResult!=0 )
	{
		uprintf("! failed to write sector %d!\n", ptFlashPos->ulSectorId);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	return tResult;
}

/*-------------------------------------------------------------------------*/

NETX_CONSOLEAPP_RESULT_T sdio_detect_wrap(SDIO_HANDLE_T *ptSdioHandle)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;

	uprintf("# Detecting SD/EMMC on SDIO port...\n");

	iResult = sdio_detect(ptSdioHandle, &tSdioOptions);
	if( iResult!=0 )
	{
		uprintf("! failed to detect SD/EMMC!\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". OK, found SD/EMMC\n");
		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	return tResult;
}



NETX_CONSOLEAPP_RESULT_T sdio_read(CMD_PARAMETER_READ_T *ptParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	FLASH_POSITIONS_T tFlashPos;
	const SDIO_HANDLE_T *ptSdioHandle;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	uprintf("# Reading...\n");
	
	flashpos_init(&tFlashPos, ptParams->ulStartAdr, ptParams->ulEndAdr, ptParams->pucData);
	
	while (1 == flashpos_get_chunk(&tFlashPos))
	{
		tResult = flashpos_read_sector(&tFlashPos, ptSdioHandle);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			break;
		}
		
		memcpy(tFlashPos.pucDataAdr, tFlashPos.tSector.auc + tFlashPos.ulSectorOffset, tFlashPos.ulChunkLength);
		
		flashpos_skip_chunk(&tFlashPos);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		uprintf(". OK\n");
	}
	else
	{
		uprintf("! Failed to read area!\n");
	}
	return tResult;
}


#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T sdio_sha1(CMD_PARAMETER_CHECKSUM_T *ptParams, SHA_CTX *ptSha1Context)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	FLASH_POSITIONS_T tFlashPos;
	const SDIO_HANDLE_T *ptSdioHandle;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	uprintf("# Calculating hash...\n");
	
	flashpos_init(&tFlashPos, ptParams->ulStartAdr, ptParams->ulEndAdr, NULL);
	
	while (1 == flashpos_get_chunk(&tFlashPos))
	{
		tResult = flashpos_read_sector(&tFlashPos, ptSdioHandle);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			break;
		}
		
		SHA1_Update(ptSha1Context, (const void*)(tFlashPos.tSector.auc + tFlashPos.ulSectorOffset), tFlashPos.ulChunkLength);

		flashpos_skip_chunk(&tFlashPos);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		uprintf(". OK\n");
	}
	else
	{
		uprintf("! Failed to read area!\n");
	}
	return tResult;
}
#endif 

 
/*
	return value == NETX_CONSOLEAPP_RESULT_OK and 
		ptConsoleParams->pvReturnMessage == 0: the data is equal
		ptConsoleParams->pvReturnMessage != 0: the data differs
	return value != NETX_CONSOLEAPP_RESULT_OK: an error occurred
*/
NETX_CONSOLEAPP_RESULT_T sdio_verify(CMD_PARAMETER_VERIFY_T *ptParams, unsigned long *pulVerifyResult)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int fEqual; /* ==0: equal, !=0: not equal */

	FLASH_POSITIONS_T tFlashPos;
	const SDIO_HANDLE_T *ptSdioHandle;

	unsigned long ulFlashAdr; /* device offset (for error message) */
	unsigned char *pucBuffer; /* buffer position */
	unsigned char *pucSector; /* sector position */
	unsigned char *pucSectorEnd;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	fEqual = 0;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	uprintf("# Verifying...\n");
	
	flashpos_init(&tFlashPos, ptParams->ulStartAdr, ptParams->ulEndAdr, ptParams->pucData);
	ulFlashAdr = ptParams->ulStartAdr;
	pucBuffer = ptParams->pucData;
	
	while ((1 == flashpos_get_chunk(&tFlashPos)) && (fEqual == 0))
	{
		tResult = flashpos_read_sector(&tFlashPos, ptSdioHandle);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			break;
		}
		
		pucSector = tFlashPos.tSector.auc+tFlashPos.ulSectorOffset;
		pucSectorEnd = pucSector+tFlashPos.ulChunkLength;
		
		while (pucSector < pucSectorEnd)
		{
			if (*pucSector != *pucBuffer) {
				uprintf("! verify error at address 0x%08x. buffer: 0x%02x, flash: 0x%02x.\n", 
				ulFlashAdr, *pucBuffer, *pucSector); 
				fEqual = 1;
				break;
			}
			++pucSector;
			++pucBuffer;
			++ulFlashAdr;
		}
		
		flashpos_skip_chunk(&tFlashPos);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		if( fEqual==0 )
		{
			uprintf(". Verify OK. The data in the memory and the flash are identical.\n");
		}
		else
		{
			uprintf("! Verify failed. The data in the memory and the flash differ.\n");
		} 
		*pulVerifyResult = (unsigned long) fEqual;
	}
	
	return tResult;
}


NETX_CONSOLEAPP_RESULT_T sdio_write(CMD_PARAMETER_FLASH_T *ptParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	CMD_PARAMETER_VERIFY_T tVerifyParams;
	unsigned long ulVerifyResult;

	const SDIO_HANDLE_T *ptSdioHandle;
	FLASH_POSITIONS_T tFlashPos;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	uprintf("# Writing...\n");
	
	flashpos_init(&tFlashPos, ptParams->ulStartAdr, ptParams->ulStartAdr + ptParams->ulDataByteSize, ptParams->pucData);
	
	while (1 == flashpos_get_chunk(&tFlashPos))
	{
		if ((tFlashPos.ulSectorOffset != 0) || (tFlashPos.ulChunkLength != SD_SECTOR_SIZE))
		{
			tResult = flashpos_read_sector(&tFlashPos, ptSdioHandle);
			if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
			{
				break;
			}
		}
		
		memcpy(tFlashPos.tSector.auc + tFlashPos.ulSectorOffset, tFlashPos.pucDataAdr, tFlashPos.ulChunkLength);

		tResult = flashpos_write_sector(&tFlashPos, ptSdioHandle);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			break;
		}
		
		flashpos_skip_chunk(&tFlashPos);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		tVerifyParams.ptDeviceDescription = ptParams->ptDeviceDescription;
		tVerifyParams.ulStartAdr = ptParams->ulStartAdr;
		tVerifyParams.ulEndAdr   = ptParams->ulStartAdr + ptParams->ulDataByteSize; 
		tVerifyParams.pucData    = ptParams->pucData;
		tResult = sdio_verify (&tVerifyParams, &ulVerifyResult);

		if ((tResult != NETX_CONSOLEAPP_RESULT_OK) || ulVerifyResult != 0)
		{
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
	}

	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		uprintf(". OK\n");
	}
	else
	{
		uprintf("! failed to write area!\n");
	}
	return tResult;
}


NETX_CONSOLEAPP_RESULT_T sdio_erase(CMD_PARAMETER_ERASE_T *ptParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;

	const SDIO_HANDLE_T *ptSdioHandle;
	FLASH_POSITIONS_T tFlashPos;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	uprintf("# Erasing...\n");
	
	flashpos_init(&tFlashPos, ptParams->ulStartAdr, ptParams->ulEndAdr, NULL);

	while (1 == flashpos_get_chunk(&tFlashPos))
	{
		if ((tFlashPos.ulSectorOffset != 0) || (tFlashPos.ulChunkLength != SD_SECTOR_SIZE))
		{
			tResult = flashpos_read_sector(&tFlashPos, ptSdioHandle);
			if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
			{
				break;
			}
		}
		
		memset(tFlashPos.tSector.auc + tFlashPos.ulSectorOffset, 0x00, tFlashPos.ulChunkLength);
		
		tResult = flashpos_write_sector(&tFlashPos, ptSdioHandle);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			break;
		}
		
		flashpos_skip_chunk(&tFlashPos);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		uprintf(". OK\n");
	}
	else
	{
		uprintf("! failed to erase area!\n");
	}
	return tResult;
}



/* Dummy - returns the same start/end addresses as passed in via the parameters. */
NETX_CONSOLEAPP_RESULT_T sdio_get_erase_area(CMD_PARAMETER_GETERASEAREA_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;

	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ptParameter->ulEndAdr;

	uprintf(". Erase area: 0x%08x - 0x%08x\n", ulOffsetStart, ulOffsetEnd);

	ptParameter->ulStartAdr = ulOffsetStart;
	ptParameter->ulEndAdr = ulOffsetEnd;

	tResult = NETX_CONSOLEAPP_RESULT_OK;

	return tResult;
}  

/* 
	return value == NETX_CONSOLEAPP_RESULT_OK and 
		ptConsoleParams->pvReturnMessage == 0xff: the area is empty
		ptConsoleParams->pvReturnMessage != 0xff: the area is not empty
	return value != NETX_CONSOLEAPP_RESULT_OK: an error occurred
*/
NETX_CONSOLEAPP_RESULT_T sdio_is_erased(CMD_PARAMETER_ISERASED_T *ptParams, unsigned long *pulIsErasedResult)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int fIsErased; /* ==0: clean, !=0: dirty */

	const SDIO_HANDLE_T *ptSdioHandle;
	FLASH_POSITIONS_T tFlashPos;
	
	unsigned char *pucCnt;
	unsigned char *pucEnd;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	fIsErased = 0;
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	uprintf("# Is-erased check...\n");
	
	flashpos_init(&tFlashPos, ptParams->ulStartAdr, ptParams->ulEndAdr, NULL);
	
	while ((1 == flashpos_get_chunk(&tFlashPos)) && (fIsErased == 0))
	{
		tResult = flashpos_read_sector(&tFlashPos, ptSdioHandle);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			break;
		}
		
		pucCnt = tFlashPos.tSector.auc+tFlashPos.ulSectorOffset;
		pucEnd = pucCnt+tFlashPos.ulChunkLength;
		
		while (pucCnt < pucEnd)
		{
			if (*pucCnt != 0) {
				fIsErased = 1;
				break;
			}
			pucCnt++;
		}
		
		flashpos_skip_chunk(&tFlashPos);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		if( fIsErased==0 )
		{
			uprintf(". CLEAN! The area is erased.\n");
			*pulIsErasedResult = 0xffUL;
		}
		else
		{
			uprintf(". DIRTY! The area is not erased.\n");
			*pulIsErasedResult = 0;
		} 
	}
	return tResult;
}




