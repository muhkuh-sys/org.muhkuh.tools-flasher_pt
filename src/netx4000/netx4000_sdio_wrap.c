#include "netx4000_sdio_wrap.h"
#include "netx4000_sdio.h"
#include "portcontrol.h"
#include "uprintf.h"
#include "progress_bar.h"

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

static unsigned long get_chunk_len(unsigned long ulFlashAdr, unsigned long ulFlashEndAdr, unsigned long ulSectorOffset)
{
	unsigned long ulChunkLengthA;
	unsigned long ulChunkLengthB;
	unsigned long ulChunkLength;
	
	ulChunkLengthA = ulFlashEndAdr - ulFlashAdr; /* remaining range in the flash */
	ulChunkLengthB = SD_SECTOR_SIZE - ulSectorOffset; /* remaining space in the sector */
	ulChunkLength = ulChunkLengthA < ulChunkLengthB ? ulChunkLengthA : ulChunkLengthB;

	return ulChunkLength;
}


 
/*-------------------------------------------------------------------------*/

NETX_CONSOLEAPP_RESULT_T sdio_detect_wrap(SDIO_HANDLE_T *ptSdioHandle)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;

	uprintf(". Detecting SD/EMMC on SDIO port...\n");

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
	int iResult;

	const SDIO_HANDLE_T *ptSdioHandle;
	
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
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	ulFlashAdr = ptParams->ulStartAdr;
	ulFlashEndAdr = ptParams->ulEndAdr;
	pucDataAdr = ptParams->pucData;

	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashAdr);
	
	uprintf(". Reading...\n");
	
	while (ulFlashAdr < ulFlashEndAdr)
	{
		ulSectorId = ulFlashAdr >> SD_SECTOR_SIZE_LOG; /* divide by sector size 512 bytes */
		ulSectorOffset = ulFlashAdr & SD_SECTOR_SIZE_MSK; /* take the offset in a 512 byte sector */
		ulChunkLength = get_chunk_len(ulFlashAdr, ulFlashEndAdr, ulSectorOffset);
		
		uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", ulFlashAdr, ulSectorId, ulSectorOffset);
		iResult = sdio_read_sector(ptSdioHandle, ulSectorId, tSector.aul);
		if( iResult!=0 )
		{
			uprintf("! failed to read sector %d!\n", ulSectorId);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
		
		memcpy(pucDataAdr, tSector.auc + ulSectorOffset, ulChunkLength);
		pucDataAdr += ulChunkLength;
		ulFlashAdr += ulChunkLength;
		
		/* inc progress */
		ulProgressCnt += ulChunkLength;
		progress_bar_set_position(ulProgressCnt);
	}
	
	progress_bar_finalize();
	
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



/*
	return value == NETX_CONSOLEAPP_RESULT_OK and 
		ptConsoleParams->pvReturnMessage == 0: the data is equal
		ptConsoleParams->pvReturnMessage != 0: the data differs
	return value != NETX_CONSOLEAPP_RESULT_OK: an error occurred
*/
NETX_CONSOLEAPP_RESULT_T sdio_verify(CMD_PARAMETER_VERIFY_T *ptParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int fEqual; /* ==0: equal, !=0: not equal */
	int iResult; /* return values from SDIO functions */

	const SDIO_HANDLE_T *ptSdioHandle;
	
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
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	fEqual = 0;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	ulFlashAdr = ptParams->ulStartAdr;
	ulFlashEndAdr = ptParams->ulEndAdr;
	pucDataAdr = ptParams->pucData;

	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashAdr);
	
	uprintf(". Verifying...\n");
	
	while (ulFlashAdr < ulFlashEndAdr)
	{
		ulSectorId = ulFlashAdr >> SD_SECTOR_SIZE_LOG; /* divide by sector size 512 bytes */
		ulSectorOffset = ulFlashAdr & SD_SECTOR_SIZE_MSK; /* take the offset in a 512 byte sector */
		ulChunkLength = get_chunk_len(ulFlashAdr, ulFlashEndAdr, ulSectorOffset);
		
		uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", ulFlashAdr, ulSectorId, ulSectorOffset);
		iResult = sdio_read_sector(ptSdioHandle, ulSectorId, tSector.aul);
		if( iResult!=0 )
		{
			uprintf("! failed to read sector %d!\n", ulSectorId);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
		
		iResult = memcmp(pucDataAdr, tSector.auc + ulSectorOffset, ulChunkLength);
		if (iResult != 0)
		{
			uprintf(". Verify failed!\n");
			fEqual = 1;
			break;
		}
		
		pucDataAdr += ulChunkLength;
		ulFlashAdr += ulChunkLength;
		
		/* inc progress */
		ulProgressCnt += ulChunkLength;
		progress_bar_set_position(ulProgressCnt);
	}
	
	progress_bar_finalize();
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		if( fEqual==0 )
		{
			uprintf(". Verify OK. The data in the memory and the flash are identical.\n");
			ptConsoleParams->pvReturnMessage = (void*) fEqual;
		}
		else
		{
			uprintf(". Verify failed. The data in the memory and the flash differ.\n");
			ptConsoleParams->pvReturnMessage = (void*) fEqual;
		} 
	}
	
	return tResult;
}




NETX_CONSOLEAPP_RESULT_T sdio_write(CMD_PARAMETER_FLASH_T *ptParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;

	const SDIO_HANDLE_T *ptSdioHandle;
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
	
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	ulFlashAdr = ptParams->ulStartAdr;
	ulFlashEndAdr = ptParams->ulStartAdr + ptParams->ulDataByteSize;
	pucDataAdr = ptParams->pucData;

	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashAdr);
	
	uprintf(". Writing...\n");
	
	while (ulFlashAdr < ulFlashEndAdr)
	{
		ulSectorId = ulFlashAdr >> SD_SECTOR_SIZE_LOG; /* divide by sector size 512 bytes */
		ulSectorOffset = ulFlashAdr & SD_SECTOR_SIZE_MSK; /* take the offset in a 512 byte sector */
		ulChunkLength = get_chunk_len(ulFlashAdr, ulFlashEndAdr, ulSectorOffset);
		
		uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", ulFlashAdr, ulSectorId, ulSectorOffset);
		
		if ((ulSectorOffset != 0) || (ulChunkLength != SD_SECTOR_SIZE))
		{
			iResult = sdio_read_sector(ptSdioHandle, ulSectorId, tSector.aul);
			if( iResult!=0 )
			{
				uprintf("! failed to read sector %d!\n", ulSectorId);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}
		}
		
		memcpy(tSector.auc + ulSectorOffset, pucDataAdr, ulChunkLength);
		
		iResult = sdio_write_sector(ptSdioHandle, ulSectorId, tSector.aul);
		if( iResult!=0 )
		{
			uprintf("! failed to write sector %d!\n", ulSectorId);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
		
		pucDataAdr += ulChunkLength;
		ulFlashAdr += ulChunkLength;
		
		/* inc progress */
		ulProgressCnt += ulChunkLength;
		progress_bar_set_position(ulProgressCnt);
	}
	
	progress_bar_finalize();
	
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
	int iResult;

	const SDIO_HANDLE_T *ptSdioHandle;
	unsigned long ulProgressCnt;
	
	unsigned long ulFlashAdr;
	unsigned long ulFlashEndAdr;
	
	unsigned long ulSectorId;
	unsigned long ulSectorOffset;
	unsigned long ulChunkLength;
	
	union {
		unsigned long aul[SD_SECTOR_SIZE/4];
		unsigned char auc[SD_SECTOR_SIZE];
	} tSector;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	ulFlashAdr = ptParams->ulStartAdr;
	ulFlashEndAdr = ptParams->ulEndAdr;
	
	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashAdr);
	
	uprintf(". Erasing...\n");
	
	while (ulFlashAdr < ulFlashEndAdr)
	{
		ulSectorId = ulFlashAdr >> SD_SECTOR_SIZE_LOG; /* divide by sector size 512 bytes */
		ulSectorOffset = ulFlashAdr & SD_SECTOR_SIZE_MSK; /* take the offset in a 512 byte sector */
		ulChunkLength = get_chunk_len(ulFlashAdr, ulFlashEndAdr, ulSectorOffset);
		
		uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", ulFlashAdr, ulSectorId, ulSectorOffset);
		
		if ((ulSectorOffset != 0) || (ulChunkLength != SD_SECTOR_SIZE))
		{
			iResult = sdio_read_sector(ptSdioHandle, ulSectorId, tSector.aul);
			if( iResult!=0 )
			{
				uprintf("! failed to read sector %d!\n", ulSectorId);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}
		}
		
		memset(tSector.auc + ulSectorOffset, 0x00, ulChunkLength);
		
		iResult = sdio_write_sector(ptSdioHandle, ulSectorId, tSector.aul);
		if( iResult!=0 )
		{
			uprintf("! failed to write sector %d!\n", ulSectorId);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
		
		ulFlashAdr += ulChunkLength;
		
		/* inc progress */
		ulProgressCnt += ulChunkLength;
		progress_bar_set_position(ulProgressCnt);
	}
	
	progress_bar_finalize();
	
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

	uprintf("Erase area: 0x%08x - 0x%08x\n", ulOffsetStart, ulOffsetEnd);

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
NETX_CONSOLEAPP_RESULT_T sdio_is_erased(CMD_PARAMETER_ISERASED_T *ptParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int fIsErased; /* ==0: clean, !=0: dirty */
	int iResult;

	const SDIO_HANDLE_T *ptSdioHandle;
	
	unsigned long ulProgressCnt;
	
	unsigned long ulFlashAdr;
	unsigned long ulFlashEndAdr;
	
	unsigned long ulSectorId;
	unsigned long ulSectorOffset;
	unsigned long ulChunkLength;
	
	unsigned char *pucCnt;
	unsigned char *pucEnd;
	
	union {
		unsigned long aul[SD_SECTOR_SIZE/4];
		unsigned char auc[SD_SECTOR_SIZE];
	} tSector;
	
	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	fIsErased = 0;
	
	ptSdioHandle = &ptParams->ptDeviceDescription->uInfo.tSdioHandle;
	
	ulFlashAdr = ptParams->ulStartAdr;
	ulFlashEndAdr = ptParams->ulEndAdr;

	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashAdr);
	
	uprintf(". Is-erased check...\n");
	
	while ((ulFlashAdr < ulFlashEndAdr) && (fIsErased == 0))
	{
		ulSectorId = ulFlashAdr >> SD_SECTOR_SIZE_LOG; /* divide by sector size 512 bytes */
		ulSectorOffset = ulFlashAdr & SD_SECTOR_SIZE_MSK; /* take the offset in a 512 byte sector */
		ulChunkLength = get_chunk_len(ulFlashAdr, ulFlashEndAdr, ulSectorOffset);
		
		uprintf("addr: 0x%08x  sector ID: %d  sector offset: %d\n", ulFlashAdr, ulSectorId, ulSectorOffset);
		iResult = sdio_read_sector(ptSdioHandle, ulSectorId, tSector.aul);
		if( iResult!=0 )
		{
			uprintf("! failed to read sector %d!\n", ulSectorId);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
		
		pucCnt = tSector.auc+ulSectorOffset;
		pucEnd = pucCnt+ulChunkLength;
		
		while (pucCnt < pucEnd)
		{
			if (*pucCnt != 0) {
				fIsErased = 1;
				break;
			}
			pucCnt++;
		}
		
		ulFlashAdr += ulChunkLength;
		
		/* inc progress */
		ulProgressCnt += ulChunkLength;
		progress_bar_set_position(ulProgressCnt);
	}
	
	progress_bar_finalize();
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		if( fIsErased==0 )
		{
			uprintf(". CLEAN! The area is erased.\n");
			ptConsoleParams->pvReturnMessage = (void*) 0xffUL;
		}
		else
		{
			uprintf(". DIRTY! The area is not erased.\n");
			ptConsoleParams->pvReturnMessage = (void*) 0;
		} 
	}
	return tResult;
}




