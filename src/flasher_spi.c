/***************************************************************************
 *   Copyright (C) 2008 by Hilscher GmbH                                   *
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
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <string.h>

#include "flasher_spi.h"
#include "spi_flash.h"

#include "flasher_interface.h"
#include "progress_bar.h"
#include "uprintf.h"

/*-----------------------------------*/

#define SPI_BUFFER_SIZE 8192
unsigned char pucSpiBuffer[SPI_BUFFER_SIZE];

/*-----------------------------------*/

static NETX_CONSOLEAPP_RESULT_T spi_write_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
{
	const unsigned char *pucDC;
	unsigned long ulC, ulE;	
	unsigned long ulSegSize;
	unsigned long ulMaxSegSize;
	unsigned long ulPageSize;
	unsigned long ulPageStartAdr;
	unsigned long ulProgressCnt;
	unsigned long ulOffset;
	int iResult;
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* Expect success. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* use the pagesize as segmentation */
	ulPageSize = ptFlashDev->tAttributes.ulPageSize;
	if( ulPageSize>SPI_BUFFER_SIZE )
	{
		uprintf("! pagesize exceeds reserved buffer.\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		/* write the complete data */
		uprintf("# Write data...\n");

		/* loop over all data */
		ulC = ulFlashStartAdr;
		ulE = ulC + ulDataByteLen;
		pucDC = pucDataStartAdr;

		ulProgressCnt = 0;
		progress_bar_init( ulDataByteLen );

		/* start inside a page? */
		ulOffset = ulFlashStartAdr % ulPageSize;
		if( ulOffset!=0 )
		{
			/* yes, start inside a page */

			/* get the startaddress of the page */
			ulPageStartAdr = ulFlashStartAdr - ulOffset;

			/* get the new max segment size for the rest of the page */
			ulMaxSegSize = ulPageSize - ulOffset;

			/* get the next segment, limit it to 'ulMaxSegSize' */
			ulSegSize = ulE - ulC;
			if( ulSegSize>ulMaxSegSize )
			{
				ulSegSize = ulMaxSegSize;
			}

			/* read the start of the page */
			iResult = Drv_SpiReadFlash(ptFlashDev, ulPageStartAdr, pucSpiBuffer, ulOffset);
			if( iResult!=0 )
			{
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			}
			else
			{
				/* modify the rest of the page */
				memcpy(pucSpiBuffer+ulOffset, pucDC, ulSegSize);

				/* write the modified buffer */
				iResult = Drv_SpiWritePage(ptFlashDev, ulPageStartAdr, pucSpiBuffer, ulPageSize);
/*				iResult = Drv_SpiEraseAndWritePage(ptFlashDev, ulPageStartAdr, ulPageSize, pucSpiBuffer); */
				if( iResult!=0 )
				{
					uprintf("! write error\n");
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				}
				else
				{
					/* next segment */
					ulC += ulSegSize;
					pucDC += ulSegSize;

					/* inc progress */
					ulProgressCnt += ulSegSize;
					progress_bar_set_position(ulProgressCnt);
				}
			}
		}

		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* process complete pages */
			while( ulC+ulPageSize<ulE )
			{
				/* write one page */
				iResult = Drv_SpiWritePage(ptFlashDev, ulC, pucDC, ulPageSize);
/*				iResult = Drv_SpiEraseAndWritePage(ptFlashDev, ulC, ulPageSize, pucDC); */
				if( iResult!=0 )
				{
					uprintf("! write error\n");
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					break;
				}

				/* next segment */
				ulC += ulPageSize;
				pucDC += ulPageSize;

				/* inc progress */
				ulProgressCnt += ulPageSize;
				progress_bar_set_position(ulProgressCnt);
			}

			if( tResult==NETX_CONSOLEAPP_RESULT_OK )
			{
				/* part of a page left? */
				if( ulC<ulE )
				{
					/* yes, start inside a page -> get the next segment */
					ulSegSize = ulE - ulC;

					/* modify the beginning of the page */
					memcpy(pucSpiBuffer, pucDC, ulSegSize);
					/* read the rest of the buffer */
					iResult = Drv_SpiReadFlash(ptFlashDev, ulC+ulSegSize, pucSpiBuffer+ulSegSize, ulPageSize-ulSegSize);
					if( iResult!=0 )
					{
						tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					}
					else
					{
						/* write the buffer */
						iResult = Drv_SpiWritePage(ptFlashDev, ulC, pucSpiBuffer, ulPageSize);
/*						iResult = Drv_SpiEraseAndWritePage(ptFlashDev, ulC, ulPageSize, pucSpiBuffer); */
						if( iResult!=0 )
						{
							uprintf("! write error\n");
							tResult = NETX_CONSOLEAPP_RESULT_ERROR;
						}
					}
				}
			}
		}
	}

	progress_bar_finalize();

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf(". write ok\n");
	}

	return tResult;
}


static NETX_CONSOLEAPP_RESULT_T spi_verify_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
{
	int iResult;
	unsigned long       ulC, ulE;
	unsigned long       ulSegSize, ulMaxSegSize;
	unsigned long       ulProgressCnt;
	unsigned char       *pucCmp0;
	const unsigned char *pucCmp1;
	const unsigned char *pucDC;
	size_t sizCmpCnt;


	uprintf("# Verify data...\n");

	ulMaxSegSize = SPI_BUFFER_SIZE;

	/* loop over all data */
	ulC = ulFlashStartAdr;
	ulE = ulC + ulDataByteLen;
	pucDC = pucDataStartAdr;

	ulProgressCnt = 0;
	progress_bar_init(ulDataByteLen);

	while( ulC<ulE )
	{
		/* get the next segment, limit it to 'ulMaxSegSize' */
		ulSegSize = ulE - ulC;
		if( ulSegSize>ulMaxSegSize )
		{
			ulSegSize = ulMaxSegSize;
		}

		/* read the segment */
		iResult = Drv_SpiReadFlash(ptFlashDev, ulC, pucSpiBuffer, ulSegSize);
		if( iResult!=0 )
		{
			return NETX_CONSOLEAPP_RESULT_ERROR;
		}

		/* compare... */
		pucCmp0 = pucSpiBuffer;
		pucCmp1 = pucDC;
		sizCmpCnt = 0;
		while( sizCmpCnt<ulSegSize )
		{
			if( pucCmp0[sizCmpCnt]!=pucCmp1[sizCmpCnt] )
			{
				uprintf(". verify error at offset 0x%08x. buffer: 0x%02x, flash: 0x%02x.\n", ulC + ulProgressCnt + sizCmpCnt, pucCmp1[sizCmpCnt], pucCmp0[sizCmpCnt]);
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
			++sizCmpCnt;
		}

		/* next segment */
		ulC += ulSegSize;
		pucDC += ulSegSize;

		/* inc progress */
		ulProgressCnt += ulSegSize;
		progress_bar_set_position(ulProgressCnt);
	}

	progress_bar_finalize();
	uprintf(". verify ok\n");

	/* compare ok! */
	return NETX_CONSOLEAPP_RESULT_OK;
}


static NETX_CONSOLEAPP_RESULT_T spi_read_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulFlashEndAdr, unsigned char *pucDataAdr)
{
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;


	uprintf("# Read data...\n");

	ulMaxSegSize = SPI_BUFFER_SIZE;

	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashStartAdr);

	while( ulFlashStartAdr<ulFlashEndAdr )
	{
		/* get the next segment, limit it to 'ulMaxSegSize' */
		ulSegSize = ulFlashEndAdr - ulFlashStartAdr;
		if( ulSegSize>ulMaxSegSize )
		{
			ulSegSize = ulMaxSegSize;
		}

		/* read the segment */
		iResult = Drv_SpiReadFlash(ptFlashDev, ulFlashStartAdr, pucDataAdr, ulSegSize);
		if( iResult!=0 )
		{
			return NETX_CONSOLEAPP_RESULT_ERROR;
		}

		/* next segment */
		ulFlashStartAdr += ulSegSize;
		pucDataAdr += ulSegSize;

		/* inc progress */
		ulProgressCnt += ulSegSize;
		progress_bar_set_position(ulProgressCnt);
	}

	progress_bar_finalize();
	uprintf(". read ok\n");

	/* read ok! */
	return NETX_CONSOLEAPP_RESULT_OK;
}

#if CFG_INCLUDE_SHA1!=0
static NETX_CONSOLEAPP_RESULT_T spi_sha1_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulFlashEndAdr, SHA_CTX *ptSha1Context)
{
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;

	uprintf("# Hashing data...\n");

	ulMaxSegSize = SPI_BUFFER_SIZE;

	ulProgressCnt = 0;
	progress_bar_init(ulFlashEndAdr-ulFlashStartAdr);

	while( ulFlashStartAdr<ulFlashEndAdr )
	{
		/* get the next segment, limit it to 'ulMaxSegSize' */
		ulSegSize = ulFlashEndAdr - ulFlashStartAdr;
		if( ulSegSize>ulMaxSegSize )
		{
			ulSegSize = ulMaxSegSize;
		}

		/* read the segment */
		iResult = Drv_SpiReadFlash(ptFlashDev, ulFlashStartAdr, pucSpiBuffer, ulSegSize);
		if( iResult!=0 )
		{
			return NETX_CONSOLEAPP_RESULT_ERROR;
		}
		
		SHA1_Update(ptSha1Context, (const void*)pucSpiBuffer, ulSegSize);

		/* next segment */
		ulFlashStartAdr += ulSegSize;

		/* inc progress */
		ulProgressCnt += ulSegSize;
		progress_bar_set_position(ulProgressCnt);
	}

	progress_bar_finalize();
	uprintf(". hash done\n");

	/* read ok! */
	return NETX_CONSOLEAPP_RESULT_OK;
}
#endif

static NETX_CONSOLEAPP_RESULT_T spi_erase_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulStartAdr, unsigned long ulEndAdr)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulSectorSize;
	unsigned long ulAddress;
	unsigned long ulProgressCnt;
	int iResult;


	uprintf("# Erase flash...\n");

	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* get the sector start and end address */
	ulSectorSize = ptFlashDev->ulSectorSize;
	if( (ulStartAdr%ulSectorSize)!=0 )
	{
		uprintf("! The start address is not aligned to a sector!\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else if( (ulEndAdr%ulSectorSize)!=0 )
	{
		uprintf("! The end address is not aligned to a sector!\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		/* show start and end of erase area */
		uprintf(". erase 0x%08x - 0x%08x\n", ulStartAdr, ulEndAdr);

		ulProgressCnt = 0;
		progress_bar_init( ulEndAdr-ulStartAdr );

		/* erase the complete area */
		ulAddress = ulStartAdr;
		while( ulAddress<ulEndAdr )
		{
			iResult = Drv_SpiEraseFlashSector(ptFlashDev, ulAddress);
			if( iResult!=0 )
			{
				uprintf("! erase failed at address 0x%08x\n", ulAddress);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}

			/* next segment */
			ulAddress += ulSectorSize;

			/* inc progress */
			ulProgressCnt += ulSectorSize;
			progress_bar_set_position(ulProgressCnt);
		}

		progress_bar_finalize();
		uprintf(". erase ok\n");
	}

	/* return result */
	return tResult;
}

/*-----------------------------------*/

NETX_CONSOLEAPP_RESULT_T spi_flash(CMD_PARAMETER_FLASH_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const unsigned char *pucDataStartAdr;
	unsigned long ulFlashStartAdr;
	unsigned long ulDataByteSize;
	unsigned long ulFlashByteSize;
	const SPI_FLASH_T *ptFlashDescription;


	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ulFlashStartAdr = ptParameter->ulStartAdr;
	ulDataByteSize  = ptParameter->ulDataByteSize;
	pucDataStartAdr = ptParameter->pucData;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulFlashByteSize = ptFlashDescription->tAttributes.ulSize;

	/* test flash size */
	uprintf(". Check size...\n");
	uprintf(". data size:  0x%08x\n", ulDataByteSize);
	uprintf(". flash size: 0x%08x\n", ulFlashByteSize);
	if( (ulFlashStartAdr>=ulFlashByteSize) || ((ulFlashStartAdr+ulDataByteSize)>ulFlashByteSize) )
	{
		/* data is larger than flash */
		uprintf("! error, data size exceeds flash\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, data fits into flash\n");

		/* write data */
		tResult = spi_write_with_progress(ptFlashDescription, ulFlashStartAdr, ulDataByteSize, pucDataStartAdr);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("! write error\n");
		}
		else
		{
			/* verify data */
			tResult = spi_verify_with_progress(ptFlashDescription, ulFlashStartAdr, ulDataByteSize, pucDataStartAdr);
			if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
			{
				uprintf("! verify error\n");
			}
		}
	}

	return tResult;
}

/*-----------------------------------*/

NETX_CONSOLEAPP_RESULT_T spi_erase(CMD_PARAMETER_ERASE_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const SPI_FLASH_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulFlashByteSize;


	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;

	/* test flash size */
	ulFlashByteSize = ptFlashDescription->tAttributes.ulSize;

	uprintf(". Check size...\n");
	uprintf(". start adr:  0x%08x\n", ulStartAdr);
	uprintf(". end adr:    0x%08x\n", ulEndAdr);
	uprintf(". flash size: 0x%08x\n", ulFlashByteSize);
	if( (ulStartAdr>=ulFlashByteSize) || (ulEndAdr>ulFlashByteSize) )
	{
		/* data is larger than flash */
		uprintf("! error, the area exceeds the flash\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, the area fits into the flash\n");

		/* erase the block */
		tResult = spi_erase_with_progress(ptFlashDescription, ulStartAdr, ulEndAdr);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("! erase error\n");
		}
	}

	return tResult;
}

/*-----------------------------------*/


NETX_CONSOLEAPP_RESULT_T spi_read(CMD_PARAMETER_READ_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const SPI_FLASH_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulFlashByteSize;


	/* Expect success. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;

	/* test flash size */
	ulFlashByteSize = ptFlashDescription->tAttributes.ulSize;

	uprintf(". Check size...\n");
	uprintf(". start adr:  0x%08x\n", ulStartAdr);
	uprintf(". end adr:    0x%08x\n", ulEndAdr);
	uprintf(". flash size: 0x%08x\n", ulFlashByteSize);
	if( (ulStartAdr>=ulFlashByteSize) || (ulEndAdr>ulFlashByteSize) )
	{
		/* data is larger than flash */
		uprintf("! error, the area exceeds the flash\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, the area fits into the flash\n");

		/* read data */
		tResult = spi_read_with_progress(ptFlashDescription, ulStartAdr, ulEndAdr, ptParameter->pucData);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("! read error\n");
		}
	}

	/* all ok */
	return tResult;
}


#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T spi_sha1(CMD_PARAMETER_CHECKSUM_T *ptParameter, SHA_CTX *ptSha1Context)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const SPI_FLASH_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulFlashByteSize;


	/* Expect success. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;

	/* test flash size */
	ulFlashByteSize = ptFlashDescription->tAttributes.ulSize;

	uprintf(". Check size...\n");
	uprintf(". start addr: 0x%08x\n", ulStartAdr);
	uprintf(". end addr:   0x%08x\n", ulEndAdr);
	uprintf(". flash size: 0x%08x\n", ulFlashByteSize);
	if( (ulStartAdr>=ulFlashByteSize) || (ulEndAdr>ulFlashByteSize) )
	{
		/* data is larger than flash */
		uprintf("! error, the area exceeds the flash\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, the area fits into the flash\n");

		/* read data */
		tResult = spi_sha1_with_progress(ptFlashDescription, ulStartAdr, ulEndAdr, ptSha1Context);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("! read error\n");
		}
	}

	/* all ok */
	return tResult;
}
#endif

/*-----------------------------------*/


NETX_CONSOLEAPP_RESULT_T spi_verify(CMD_PARAMETER_VERIFY_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	NETX_CONSOLEAPP_RESULT_T tEqual;
	const unsigned char *pucDataStartAdr;
	unsigned long ulFlashStartAdr;
	unsigned long ulFlashEndAdr;
	unsigned long ulDataByteSize;
	unsigned long ulFlashByteSize;
	const SPI_FLASH_T *ptFlashDescription;


	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ulFlashStartAdr = ptParameter->ulStartAdr;
	ulFlashEndAdr   = ptParameter->ulEndAdr;
	ulDataByteSize  = ulFlashEndAdr - ulFlashStartAdr;
	pucDataStartAdr = ptParameter->pucData;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulFlashByteSize = ptFlashDescription->tAttributes.ulSize;

	/* test flash size */
	uprintf(". Check size...\n");
	uprintf(". data size:  0x%08x\n", ulDataByteSize);
	uprintf(". flash size: 0x%08x\n", ulFlashByteSize);
	if( (ulFlashStartAdr>=ulFlashByteSize) || (ulFlashEndAdr>ulFlashByteSize) )
	{
		/* data is larger than flash */
		uprintf("! error, data size exceeds flash\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, data fits into flash\n");

		/* verify data */
		tEqual = spi_verify_with_progress(ptFlashDescription, ulFlashStartAdr, ulDataByteSize, pucDataStartAdr);
		if( tEqual!=NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("! verify error\n");
		}
		
		ptConsoleParams->pvReturnMessage = (void*)tEqual;
	}

	return tResult;
}


/*-----------------------------------*/


NETX_CONSOLEAPP_RESULT_T spi_detect(CMD_PARAMETER_DETECT_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;
	SPI_FLASH_T *ptFlashDescription;


	ptDeviceDescription = ptParameter->ptDeviceDescription;
	ptFlashDescription = &(ptDeviceDescription->uInfo.tSpiInfo);

	/* try to detect flash */
	uprintf(". Detecting SPI flash on unit %d, cs %d...\n", ptParameter->uSourceParameter.tSpi.uiUnit, ptParameter->uSourceParameter.tSpi.uiChipSelect);
	ptFlashDescription->uiSlaveId = ptParameter->uSourceParameter.tSpi.uiChipSelect;
	iResult = Drv_SpiInitializeFlash(&(ptParameter->uSourceParameter.tSpi), ptFlashDescription);
	if( iResult!=0 )
	{
		/* failed to detect the spi flash */
		uprintf("! failed to detect flash!\n");

		/* clear the result data */
		memset(ptDeviceDescription, 0, sizeof(DEVICE_DESCRIPTION_T));

		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, found %s\n", ptFlashDescription->tAttributes.acName);

		/* set the result data */
		ptDeviceDescription->fIsValid = 1;
		ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
		ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
		ptDeviceDescription->tSourceTyp = BUS_SPI;

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}

	return tResult;
}


/*-----------------------------------*/


NETX_CONSOLEAPP_RESULT_T spi_isErased(CMD_PARAMETER_ISERASED_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T  tResult;
	const SPI_FLASH_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulFlashSize;
	unsigned long ulCnt;
	unsigned char *pucCnt;
	unsigned char *pucEnd;
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;
	unsigned long ulErased;


	/* expect success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr  = ptParameter->ulEndAdr;

	ulFlashSize = ptFlashDescription->tAttributes.ulSize;

	uprintf("flash size: 0x%08x\n", ulFlashSize);

	/* test addresses */
	if( (ulStartAdr>=ulFlashSize) || (ulEndAdr>ulFlashSize) )
	{
		/* data is larger than flash */
		uprintf("! error, the specified area exceeds the flash size\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, the area fits into the flash\n");

		ulErased = 0xffU;

		uprintf("# Checking data...\n");

		ulMaxSegSize = SPI_BUFFER_SIZE;

		/* loop over all data */
		ulCnt = ulStartAdr;

		ulProgressCnt = 0;
		progress_bar_init(ulEndAdr-ulStartAdr);

		while( ulCnt<ulEndAdr )
		{
			/* get the next segment, limit it to 'ulMaxSegSize' */
			ulSegSize = ulEndAdr - ulCnt;
			if( ulSegSize>ulMaxSegSize )
			{
				ulSegSize = ulMaxSegSize;
			}

			/* read the segment */
			iResult = Drv_SpiReadFlash(ptFlashDescription, ulCnt, pucSpiBuffer, ulSegSize);
			if( iResult!=0 )
			{
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}

			pucCnt = pucSpiBuffer;
			pucEnd = pucSpiBuffer + ulSegSize;
			while( pucCnt<pucEnd )
			{
				ulErased &= *(pucCnt++);
			}

			if( ulErased!=0xff )
			{
				break;
			}

			/* next segment */
			ulCnt += ulSegSize;
			pucCnt += ulSegSize;

			/* inc progress */
			ulProgressCnt += ulSegSize;
			progress_bar_set_position(ulProgressCnt);
		}

		progress_bar_finalize();
	}

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		if( ulErased==0xff )
		{
			uprintf(". CLEAN! The area is erased.\n");
		}
		else
		{
			uprintf(". DIRTY! The area is not erased.\n");
		}
		ptConsoleParams->pvReturnMessage = (void*)ulErased;
	}

	return tResult;
}


/*-----------------------------------*/


NETX_CONSOLEAPP_RESULT_T spi_getEraseArea(CMD_PARAMETER_GETERASEAREA_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T  tResult;
	const SPI_FLASH_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulFlashSize;
	unsigned long ulEraseBlockSize;


	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tSpiInfo);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr  = ptParameter->ulEndAdr;

	ulFlashSize = ptFlashDescription->tAttributes.ulSize;
	ulEraseBlockSize = ptFlashDescription->ulSectorSize;

	uprintf("flash size: 0x%08x\n", ulFlashSize);
	uprintf("erase block size: 0x%08x\n", ulEraseBlockSize);

	/* test addresses */
	if( (ulStartAdr>=ulFlashSize) || (ulEndAdr>ulFlashSize) )
	{
		/* data is larger than flash */
		uprintf("! error, the specified area exceeds the flash size\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". ok, the area fits into the flash\n");

		/* NOTE: this code assumes that the serial flash has uniform erase block sizes. */

		uprintf("0x%08x - 0x%08x\n", ulStartAdr, ulEndAdr);

		/* round down the first address */
		ulStartAdr /= ulEraseBlockSize;
		ulStartAdr *= ulEraseBlockSize;
		/* round up the last address */
		ulEndAdr += ulEraseBlockSize - 1;
		ulEndAdr /= ulEraseBlockSize;
		ulEndAdr *= ulEraseBlockSize;

		uprintf("0x%08x - 0x%08x\n", ulStartAdr, ulEndAdr);

		ptParameter->ulStartAdr = ulStartAdr;
		ptParameter->ulEndAdr = ulEndAdr;

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}

	/* all ok */
	return tResult;
}


/*-----------------------------------*/

