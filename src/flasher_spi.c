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

 /**
  * @file
  * This file contains the functions to read and write SPI flashes.
  *
  * A general note on the end address/offset:
  * The end address/offset is the address/offset of the last byte + 1,
  * or the start address/offset plus the number of bytes to read/write/erase.
  * For example, to read 4KB from offset 0x1000 to 0x1fff,
  * you have to pass ulStartAddr=0x1000 and ulEndAddr=0x2000.
  */
 
#include <string.h>

#include "flasher_spi.h"
#include "spi_flash.h"

#include "progress_bar.h"
#include "uprintf.h"
/** @file spi.h */
/** @file spi_flash.h */

/*-----------------------------------*/

#define SPI_BUFFER_SIZE 8192
unsigned char pucSpiBuffer[SPI_BUFFER_SIZE];

/*-----------------------------------*/

static NETX_CONSOLEAPP_RESULT_T spi_write_with_progress(const FLASHER_SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
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
		uprintf("# Writing...\n");

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

			/* read the whole page */
			iResult = Drv_SpiReadFlash(ptFlashDev, ulPageStartAdr, pucSpiBuffer, ulPageSize);
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


static NETX_CONSOLEAPP_RESULT_T spi_verify_with_progress(const FLASHER_SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
{
	int iResult;
	unsigned long       ulC, ulE;
	unsigned long       ulSegSize, ulMaxSegSize;
	unsigned long       ulProgressCnt;
	unsigned char       *pucCmp0;
	const unsigned char *pucCmp1;
	const unsigned char *pucDC;
	size_t sizCmpCnt;


	uprintf("# Verifying...\n");

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


static NETX_CONSOLEAPP_RESULT_T spi_read_with_progress(const FLASHER_SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulFlashEndAdr, unsigned char *pucDataAdr)
{
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;


	uprintf("# Reading...\n");

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
static NETX_CONSOLEAPP_RESULT_T spi_sha1_with_progress(const FLASHER_SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulFlashEndAdr, SHA_CTX *ptSha1Context)
{
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;

	uprintf("# Calculating hash...\n");

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

static NETX_CONSOLEAPP_RESULT_T spi_erase_with_progress(const FLASHER_SPI_FLASH_T *ptFlashDev, unsigned long ulStartAdr, unsigned long ulEndAdr)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulPageSize;
	unsigned long ulSectorSize;
	unsigned long ulPageOffsetStart;
	unsigned long ulPageOffsetEnd;
	unsigned long ulSectorOffsetStart;
	unsigned long ulSectorOffsetEnd;
	unsigned long ulAddress;
	unsigned long ulProgressCnt;
	int iResult;
	int iCanUsePageErase;
	int iCanUseSectorErase;
	unsigned long ulEraseChunk;


	uprintf("# Erase flash...\n");

	/* Assume success. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* Be pessimistic. */
	iCanUsePageErase = 0;
	iCanUseSectorErase = 0;

	/* Get the page and sector size. */
	ulPageSize = ptFlashDev->tAttributes.ulPageSize;
	ulSectorSize = ptFlashDev->ulSectorSize;

	/* Only check for page erase if the page erase opcode is not 0. */
	if( ptFlashDev->tAttributes.ucErasePageOpcode!=0x00 )
	{
		/* Get the offsets of the start and end address to the page border. */
		ulPageOffsetStart = ulStartAdr % ulPageSize;
		ulPageOffsetEnd = ulEndAdr % ulPageSize;
		/* The offsets are 0 if they are exactly on the page boundaries. */
		if( ulPageOffsetStart==0 && ulPageOffsetEnd==0 )
		{
			iCanUsePageErase = 1;
		}
	}

	/* The sector erase command is always present. */

	/* Get the offsets of the start and end address to the sector border. */
	ulSectorOffsetStart = ulStartAdr % ulSectorSize;
	ulSectorOffsetEnd = ulEndAdr % ulSectorSize;
	/* The offsets are 0 if they are exactly on the sector boundaries. */
	if( ulSectorOffsetStart==0 && ulSectorOffsetEnd==0 )
	{
		iCanUseSectorErase = 1;
	}

	/* Prefer sector over page erase. It is faster. */
	if( iCanUseSectorErase!=0 )
	{
		iCanUsePageErase = 0;
		ulEraseChunk = ulSectorSize;
	}
	else if( iCanUsePageErase!=0 )
	{
		iCanUseSectorErase = 0;
		ulEraseChunk = ulPageSize;
	}
	/* Fallback to the old behavior if page and sector does not match.
	 * Adjust the start and end to the next sector boundaries.
	 */
	else
	{
		if( ulSectorOffsetStart!=0 )
		{
			uprintf("Warning: the start address is not aligned to a sector border!\n");
			uprintf("Warning: changing the start address from 0x%08x", ulStartAdr);
			ulStartAdr -= ulSectorOffsetStart;
			uprintf(" to 0x%08x.\n", ulStartAdr);
		}
		if( ulSectorOffsetEnd!=0 )
		{
			uprintf("Warning: the end address is not aligned to a sector border!\n");
			uprintf("Warning: changing the end address from 0x%08x", ulEndAdr);
			ulEndAdr += ulSectorSize - ulSectorOffsetEnd;
			uprintf(" to 0x%08x.\n", ulEndAdr);
		}

		iCanUsePageErase = 0;
		iCanUseSectorErase = 1;
		ulEraseChunk = ulSectorSize;
	}

	/* Show the start and the end address of the erase area. */
	uprintf(". erase 0x%08x - 0x%08x\n", ulStartAdr, ulEndAdr);

	ulProgressCnt = 0;
	progress_bar_init( ulEndAdr-ulStartAdr );

	/* Erase the complete area. */
	ulAddress = ulStartAdr;
	while( ulAddress<ulEndAdr )
	{
		if( iCanUsePageErase!=0 )
		{
			iResult = Drv_SpiEraseFlashPage(ptFlashDev, ulAddress);
		}
		else
		{
			iResult = Drv_SpiEraseFlashSector(ptFlashDev, ulAddress);
		}
		if( iResult!=0 )
		{
			uprintf("! erase failed at address 0x%08x\n", ulAddress);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}

		/* Move to the next segment. */
		ulAddress += ulEraseChunk;

		/* Increment the progress bar. */
		ulProgressCnt += ulEraseChunk;
		progress_bar_set_position(ulProgressCnt);
	}

	progress_bar_finalize();
	uprintf(". erase OK\n");

	/* Return the result. */
	return tResult;
}

/*-----------------------------------*/
/**
 * @brief Write data from RAM into the flash device.
 *
 * Writes ulDataByteSize bytes from RAM at address pucDataStartAdr to 
 * the flash starting at offset ulFlashStartAdr.
 *
 * @param ptFlashDescription  [in]  Device information returned by spi_detect.
 * @param ulFlashStartAdr     [in]  Start offset in the flash memory.
 * @param ulDataByteSize      [in]  Size of the data to be written in bytes.
 * @param pucDataStartAdr     [in]  Address of the data to be written in RAM.
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK: the data has been written to the flash and verified. 
 * - NETX_CONSOLEAPP_RESULT_ERROR: An error has occurred.
 */

NETX_CONSOLEAPP_RESULT_T spi_flash(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulFlashStartAdr, unsigned long ulDataByteSize, const unsigned char *pucDataStartAdr)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
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
	}

	return tResult;
}

/*-----------------------------------*/

/**
 * @brief Erase a range of the memory.
 *
 * Erases the memory from offset ulStartAdr to ulEndAdr-1.
 * ulStartAdr to ulEndAdr-1 must be a complete erase block, or range of erase blocks.
 * Use spi_getEraseArea to compute this range from an arbitrary start and end offset.
 * 
 * @param ptFlashDescription [in]  Device information returned by spi_detect.
 * @param ulStartAdr         [in]  Start offset of the first erase block to be erased.
 * @param ulEndAdr           [in]  End offset of the last erase block to be erased (offset of the last byte + 1).
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK: success, the memory has been erased.
 * - NETX_CONSOLEAPP_RESULT_ERROR: An error has occurred.
 */

NETX_CONSOLEAPP_RESULT_T spi_erase(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* erase the block */
	tResult = spi_erase_with_progress(ptFlashDescription, ulStartAdr, ulEndAdr);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! erase error\n");
	}

	return tResult;
}

/*-----------------------------------*/

/**
 * @brief Read data from the flash.
 *
 * Reads the memory from offset ulStartAdr to ulEndAdr-1 to RAM at pucData.
 * 
 * @param ptFlashDescription  [in]  Device information returned by spi_detect.
 * @param ulStartAdr          [in]  Start offset in the flash memory.
 * @param ulEndAdr            [in]  End offset (offset of the last byte + 1).
 * @param pucData             [out] Destination address for the data in RAM.
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK: The data has successfully been read.
 * - NETX_CONSOLEAPP_RESULT_ERROR: An error occurred.
 */

NETX_CONSOLEAPP_RESULT_T spi_read(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, unsigned char *pucData)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* Expect success. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* read data */
	tResult = spi_read_with_progress(ptFlashDescription, ulStartAdr, ulEndAdr, pucData);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! read error\n");
	}

	return tResult;
}


#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T spi_sha1(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, SHA_CTX *ptSha1Context)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* read data */
	tResult = spi_sha1_with_progress(ptFlashDescription, ulStartAdr, ulEndAdr, ptSha1Context);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! error calculating hash\n");
	}

	return tResult;
}
#endif

/*-----------------------------------*/

/**
 * @brief Compare data in flash to RAM.
 *
 * Compares the data in the flash at offset ulFlashStartAdr to ulFlashEndAdr-1 to the data in RAM
 * at address pucData.
 *
 * @param ptFlashDescription  [in]  Device information returned by spi_detect.
 * @param ulFlashStartAdr     [in]  Start offset in the flash memory.
 * @param ulFlashEndAdr       [in]  End offset (offset of the last byte + 1).
 * @param pucData             [in]  Address of the data to be verified in RAM.
 * @param ppvReturnMessage    [Out] Result of the compare operation.
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK, *ppvReturnMessage == NETX_CONSOLEAPP_RESULT_OK: Verify succeeded, the data was compared and is equal.
 * - NETX_CONSOLEAPP_RESULT_ERROR, *ppvReturnMessage == NETX_CONSOLEAPP_RESULT_ERROR Verify failed, or the data was compared and is not equal.
 */

NETX_CONSOLEAPP_RESULT_T spi_verify(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulFlashStartAdr, unsigned long ulFlashEndAdr, const unsigned char *pucData, void **ppvReturnMessage)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulDataByteSize;


	ulDataByteSize  = ulFlashEndAdr - ulFlashStartAdr;

	/* verify data */
	tResult = spi_verify_with_progress(ptFlashDescription, ulFlashStartAdr, ulDataByteSize, pucData);
	
	*ppvReturnMessage = (void*)tResult;

	return tResult;
}


/*-----------------------------------*/

/**
 * @brief Initialize SPI interface and detect serial flash.
 *
 * The flasher initializes the SPI interface specified in ptSpiConfiguration and tries to
 * detect a serial flash.
 * It tests for a number of known flash devices with specific identification sequences.
 * If none of these known flashes is found, it tries to read the SFDP information.
 * When successful, it returns a device description in ptFlashDescription, which is passed
 * to subsequently called functions that access the flash.
 *
 * @param ptSpiConfiguration [in]  Configuration of the SPI interface, e.g. the clock frequency.
 * @param ptFlashDescription [out] Information about the flash device, if any was identified.
 * @param pcBufferEnd        [in]  Pointer to the end of a buffer at least 8 KB in size.
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK: a device was detected and the device information is stored in ptFlashDescription.
 * - NETX_CONSOLEAPP_RESULT_ERROR: no device was detected or an error occurred.
 */

NETX_CONSOLEAPP_RESULT_T spi_detect(FLASHER_SPI_CONFIGURATION_T *ptSpiConfiguration, FLASHER_SPI_FLASH_T *ptFlashDescription, char *pcBufferEnd)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;


	/* try to detect flash */
	uprintf(". Detecting SPI flash on unit %d, chip select %d...\n", ptSpiConfiguration->uiUnit, ptSpiConfiguration->uiChipSelect);
	ptFlashDescription->uiSlaveId = ptSpiConfiguration->uiChipSelect;
	iResult = Drv_SpiInitializeFlash(ptSpiConfiguration, ptFlashDescription, pcBufferEnd);
	if( iResult!=0 )
	{
		/* failed to detect the SPI flash */
		uprintf("! failed to detect flash!\n");

		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". OK, found %s\n", ptFlashDescription->tAttributes.acName);

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}

	return tResult;
}


/*-----------------------------------*/

/**
 * @brief Check if an area of the flash memory is erased. 
 *
 * Checks if the area from offset ulStartAdr to ulEndAdr-1 in the flash is erased, 
 * that is, all bytes read as 0xff.
 * 
 * @param ptFlashDescription [in]  Device information returned by spi_detect.
 * @param ulStartAdr         [in]  Start offset in the flash memory.
 * @param ulEndAdr           [in]  End offset (offset of the last byte to be checked + 1).
 * @param ppvReturnMessage   [out] Return value.
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK, *ppvReturnMessage == 0xff: The memory has been checked and is erased.
 * - NETX_CONSOLEAPP_RESULT_OK, *ppvReturnMessage != 0xff The memory has been checked but is not erased.
 * - NETX_CONSOLEAPP_RESULT_ERROR: An error has occurred.
 */
NETX_CONSOLEAPP_RESULT_T spi_isErased(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, void **ppvReturnMessage)
{
	NETX_CONSOLEAPP_RESULT_T  tResult;
	unsigned long ulCnt;
	unsigned char *pucCnt;
	unsigned char *pucEnd;
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;
	unsigned long ulErased;


	/* expect success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

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

		/* increment progress */
		ulProgressCnt += ulSegSize;
		progress_bar_set_position(ulProgressCnt);
	}

	progress_bar_finalize();

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
		*ppvReturnMessage = (void*)ulErased;
	}

	return tResult;
}


/*-----------------------------------*/
/**
 * @brief Compute the range of blocks to erase.
 *
 * For a given range of bytes that we want to erase, this function computes a range of erase blocks 
 * that have to be erased. This range of erase blocks must be passed to spi_erase().
 * The size of erase blocks used is internal to the flasher and cannot be selected.
 * ulStartAdr is rounded down to the beginning of the erase block containing ulStartAdr.
 * ulEndAdr is rounded up to the end of the erase block containing ulEndAdr-1.
 * 
 * @param ptFlashDescription [in]  Device information returned by spi_detect.
 * @param ulStartAdr         [in]  Start offset in the flash memory.
 * @param ulEndAdr           [in]  End offset (offset of the last byte +1).
 * @param pulStartAdr        [out] Start offset of the erase area containing the area to be erased.
 * @param pulEndAdr          [out] End offset of the erase area (offset of the last byte +1).
 *
 * @return
 * - NETX_CONSOLEAPP_RESULT_OK: The start and end address of the erase area are in pulStartAdr/pulEndAdr
 * - NETX_CONSOLEAPP_RESULT_ERROR: An error has occurred
 */

NETX_CONSOLEAPP_RESULT_T spi_getEraseArea(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, unsigned long *pulStartAdr, unsigned long *pulEndAdr)
{
	NETX_CONSOLEAPP_RESULT_T  tResult;
	unsigned long ulEraseBlockSize;


	/* NOTE: this code assumes that the serial flash has uniform erase block sizes. */
	ulEraseBlockSize = ptFlashDescription->ulSectorSize;
	uprintf("erase block size: 0x%08x\n", ulEraseBlockSize);
	uprintf("0x%08x - 0x%08x\n", ulStartAdr, ulEndAdr);

	/* round down the first address */
	ulStartAdr /= ulEraseBlockSize;
	ulStartAdr *= ulEraseBlockSize;
	/* round up the last address */
	ulEndAdr += ulEraseBlockSize - 1;
	ulEndAdr /= ulEraseBlockSize;
	ulEndAdr *= ulEraseBlockSize;

	uprintf("0x%08x - 0x%08x\n", ulStartAdr, ulEndAdr);

	*pulStartAdr = ulStartAdr;
	*pulEndAdr = ulEndAdr;

	tResult = NETX_CONSOLEAPP_RESULT_OK;


	/* all OK */
	return tResult;
}

/*-----------------------------------*/

