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

#include "progress_bar.h"
#include "uprintf.h"

/*-----------------------------------*/

NETX_CONSOLEAPP_RESULT_T spi_write_with_progress (const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr);
NETX_CONSOLEAPP_RESULT_T spi_verify_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr);
NETX_CONSOLEAPP_RESULT_T spi_read_with_progress  (const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, unsigned char *pucDataStartAdr);
NETX_CONSOLEAPP_RESULT_T spi_erase_with_progress (const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen);

/*-----------------------------------*/

/* this is the standard id for SPI flashes */
#define SPI_SLAVE_ID 1

/* this is the MMC id, it is used for the SPI test adapter */
/* #define SPI_SLAVE_ID 2 */

#define SPI_BUFFER_SIZE 8192
unsigned char pucSpiBuffer[SPI_BUFFER_SIZE];

/*-----------------------------------*/

NETX_CONSOLEAPP_RESULT_T spi_flash(const unsigned char *pbData, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	SPI_FLASH_T tFlashDev;  
	int                 iResult;
	const unsigned char *pucDataStartAdr;
	unsigned long       ulFlashStartAdr;


	pucDataStartAdr = pbData;

	/* try to detect flash */
	uprintf(". Detecting SPI flash...\n");
	tFlashDev.uiSlaveId = SPI_SLAVE_ID;
	iResult = Drv_SpiInitializeFlash(&tFlashDev);
	if( iResult==0 )
	{
		/* failed to detect the spi flash */
		uprintf("! failed to detect flash!\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, found ");
	uprintf(tFlashDev.tAttributes.acName);
	uprintf("\n");

	/* test flash size */

	uprintf(". Check size...\n");
	uprintf(". data size:  0x$8\n", ulDataByteLen);
	uprintf(". flash size: 0x$8\n", tFlashDev.tAttributes.ulSize);
	if( ulDataByteLen>tFlashDev.tAttributes.ulSize )
	{
		/* data is larger than flash */
		uprintf("! error, data size exceeds flash\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, data fits into flash\n");

	/* write data to start of flash (address 0) */
	ulFlashStartAdr = 0;

	/* write data */
	tResult = spi_write_with_progress(&tFlashDev, ulFlashStartAdr, ulDataByteLen, pucDataStartAdr);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! write error\n");
		return tResult;
	}

	/* verify data */
	tResult = spi_verify_with_progress(&tFlashDev, ulFlashStartAdr, ulDataByteLen, pucDataStartAdr);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! verify error\n");
		return tResult;
	}

	/* all ok */
	return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T spi_erase(unsigned long ulDataByteLen)
{
	int           iResult;
	unsigned long ulFlashStartAdr;  
	SPI_FLASH_T tFlashDev;  
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* try to detect flash */
	uprintf(". Detecting SPI flash...\n");
	tFlashDev.uiSlaveId = SPI_SLAVE_ID;
	iResult = Drv_SpiInitializeFlash(&tFlashDev);
	if( iResult==0 )
	{
		/* failed to detect the spi flash */
		uprintf("! failed to detect flash\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, found ");
	uprintf(tFlashDev.tAttributes.acName);
	uprintf("\n");

	/* test flash size */

	uprintf(". Check size...\n");
	if( ulDataByteLen==0xffffffff )
	{
		ulDataByteLen = tFlashDev.tAttributes.ulSize;
		uprintf(". requested to erase the complete flash, size: 0x$8\n", ulDataByteLen);
	}
	else
	{
		uprintf(". data size:  0x$8\n", ulDataByteLen);
		uprintf(". flash size: 0x$8\n", tFlashDev.tAttributes.ulSize);
		if( ulDataByteLen>tFlashDev.tAttributes.ulSize )
		{
			/* data is larger than flash */
			uprintf("! error, data size exceeds flash\n");
			return NETX_CONSOLEAPP_RESULT_ERROR;
		}
		uprintf(". ok, section fits into flash\n");
	}

	/* erase data from start of flash (address 0) */
	ulFlashStartAdr = 0;

	/* first erase the block */
	tResult = spi_erase_with_progress(&tFlashDev, ulFlashStartAdr, ulDataByteLen);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! erase error\n");
		return tResult;
	}

	/* all ok */
	return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T spi_read(unsigned char *pbData, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	SPI_FLASH_T tFlashDev;    
	int           iResult;        
	unsigned char *pucDataStartAdr;	
	unsigned long ulFlashStartAdr;	


	pucDataStartAdr = pbData;

	/* try to detect flash */
	uprintf(". Detecting SPI flash...\n");
	tFlashDev.uiSlaveId = SPI_SLAVE_ID;
	iResult = Drv_SpiInitializeFlash(&tFlashDev);
	if( iResult==0 )
	{
		/* failed to detect the spi flash */
		uprintf("! failed to detect flash\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, found ");
	uprintf(tFlashDev.tAttributes.acName);
	uprintf("\n");

	/* test flash size */

	uprintf(". Check size...\n");
	uprintf(". data size:  0x$8\n", ulDataByteLen);
	uprintf(". flash size: 0x$8\n", tFlashDev.tAttributes.ulSize);
	if( ulDataByteLen>tFlashDev.tAttributes.ulSize )
	{
		/* data is larger than flash */
		uprintf("! error, data size exceeds flash\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, data fits into flash\n");

	/* read data from start of flash (address 0) */
	ulFlashStartAdr = 0;

	/* read data */
	tResult = spi_read_with_progress(&tFlashDev, ulFlashStartAdr, ulDataByteLen, pucDataStartAdr);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! read error\n");
		return tResult;
	}

	/* all ok */
	return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T spi_verify(const unsigned char *pbData, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	SPI_FLASH_T tFlashDev;  
	int                 iResult;
	const unsigned char *pucDataStartAdr;	
	unsigned long       ulFlashStartAdr;	


	pucDataStartAdr = pbData;

	/* try to detect flash */
	uprintf(". Detecting SPI flash...\n");
	tFlashDev.uiSlaveId = SPI_SLAVE_ID;
	iResult = Drv_SpiInitializeFlash(&tFlashDev);
	if( iResult==0 )
	{
		/* failed to detect the spi flash */
		uprintf("! failed to detect flash\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, found ");
	uprintf(tFlashDev.tAttributes.acName);
	uprintf("\n");

	/* test flash size */

	uprintf(". Check size...\n");
	uprintf(". data size:  0x$8\n", ulDataByteLen);
	uprintf(". flash size: 0x$8\n", tFlashDev.tAttributes.ulSize);
	if( ulDataByteLen>tFlashDev.tAttributes.ulSize )
	{
		/* data is larger than flash */
		uprintf("! error, data size exceeds flash\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	uprintf(". ok, data fits into flash\n");

	/* verify data from start of flash (address 0) */
	ulFlashStartAdr = 0;

	/* verify data */
	tResult = spi_verify_with_progress(&tFlashDev, ulFlashStartAdr, ulDataByteLen, pucDataStartAdr);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! verify error\n");
		return tResult;
	}

	/* all ok */
	return NETX_CONSOLEAPP_RESULT_OK;
}


/*-----------------------------------*/

NETX_CONSOLEAPP_RESULT_T spi_write_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
{
	const unsigned char *pucDC;   
	unsigned long       ulC, ulE;	
	unsigned long       ulSegSize, ulMaxSegSize;
	unsigned long       ulPageSize;
	unsigned long       ulPageStartAdr;
	unsigned long       ulProgressCnt;
	unsigned long       ulOffset;
	int                 iResult;
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* use the pagesize as segmentation */
	ulPageSize = ptFlashDev->tAttributes.ulPageSize;
	if( ulPageSize>SPI_BUFFER_SIZE )
	{
		uprintf("! pagesize exceeds reserved buffer.\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}

	/* does the flash support erasing pages somehow? */
	if( ptFlashDev->tAttributes.bEraseAndPageProgOpcode==0 && ptFlashDev->tAttributes.bErasePageOpcode==0 )
	{
		/* no, it does not support page erase */
		uprintf(". The flash does not support erasing or reprogramming single pages\n");
		uprintf("# Erasing the complete area...\n");

		/* try to erase the complete area */
		tResult = spi_erase_with_progress(ptFlashDev, ulFlashStartAdr, ulDataByteLen);
		if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("! erase error\n");
			return tResult;
		}
		uprintf(". erase ok\n");

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

			/* clear the start of the page with 0xff */
			memset(pucSpiBuffer, 0xff, ulPageSize-ulSegSize);

			/* modify the rest of the page */
			memcpy(pucSpiBuffer+ulOffset, pucDC, ulSegSize);

			/* write the modified buffer */
			iResult = Drv_SpiWritePage(ptFlashDev, ulPageStartAdr, ulPageSize, pucSpiBuffer);
			if( iResult==0 )
			{
				uprintf("! write error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}

			/* next segment */
			ulC += ulSegSize;
			pucDC += ulSegSize;

			/* inc progress */
			ulProgressCnt += ulSegSize;
			progress_bar_set_position(ulProgressCnt);
		}

		/* process complete pages */
		while( ulC+ulPageSize<ulE )
		{
			/* write one page */
			iResult = Drv_SpiWritePage(ptFlashDev, ulC, ulPageSize, pucDC);
			if( iResult==0 )
			{
				uprintf("! write error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}

			/* next segment */
			ulC += ulPageSize;
			pucDC += ulPageSize;

			/* inc progress */
			ulProgressCnt += ulPageSize;
			progress_bar_set_position(ulProgressCnt);
		}

		/* part of a page left? */
		if( ulC<ulE )
		{
			/* yes, start inside a page -> get the next segment */
			ulSegSize = ulE - ulC;

			/* modify the beginning of the page */
			memcpy(pucSpiBuffer, pucDC, ulSegSize);
			/* clear the rest of the buffer */
			memset(pucSpiBuffer+ulSegSize, 0xff, ulPageSize-ulSegSize);

			/* write the buffer */
			iResult = Drv_SpiWritePage(ptFlashDev, ulC, ulPageSize, pucSpiBuffer);
			if( iResult==0 )
			{
				uprintf("! write error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
		}

		progress_bar_finalize();
		uprintf(". write ok\n");
	}
	else
	{
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

			/* read the complete page into the buffer */
			iResult = Drv_SpiReadFlash(ptFlashDev, ulPageStartAdr, pucSpiBuffer, ulPageSize);
			if( iResult==0 )
			{
				uprintf("! read error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}

			/* modify the rest of the page */
			memcpy(pucSpiBuffer+ulOffset, pucDC, ulSegSize);

			/* write the modified buffer back */
			iResult = Drv_SpiEraseAndWritePage(ptFlashDev, ulPageStartAdr, ulPageSize, pucSpiBuffer);
			if( iResult==0 )
			{
				uprintf("! write error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}

			/* next segment */
			ulC += ulSegSize;
			pucDC += ulSegSize;

			/* inc progress */
			ulProgressCnt += ulSegSize;
			progress_bar_set_position(ulProgressCnt);
		}

		/* process complete pages */
		while( ulC+ulPageSize<=ulE )
		{
			/* write one page */
			iResult = Drv_SpiEraseAndWritePage(ptFlashDev, ulC, ulPageSize, pucDC);
			if( iResult==0 )
			{
				uprintf("! write error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}

			/* next segment */
			ulC += ulPageSize;
			pucDC += ulPageSize;

			/* inc progress */
			ulProgressCnt += ulPageSize;
			progress_bar_set_position(ulProgressCnt);
		}

		/* part of a page left? */
		if( ulC<ulE )
		{
			/* get the next segment */
			ulSegSize = ulE - ulC;

			/* yes, start inside a page -> read the complete page into the buffer */
			iResult = Drv_SpiReadFlash(ptFlashDev, ulC, pucSpiBuffer, ulPageSize);
			if( iResult==0 )
			{
				uprintf("! read error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}

			/* modify the beginning of the page */
			memcpy(pucSpiBuffer, pucDC, ulSegSize);

			/* write the modified buffer back */
			iResult = Drv_SpiEraseAndWritePage(ptFlashDev, ulC, ulPageSize, pucSpiBuffer);
			if( iResult==0 )
			{
				uprintf("! write error\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
		}

		progress_bar_finalize();
		uprintf(". write ok\n");
	}

	/* write ok! */
	return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T spi_verify_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
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
		if( iResult==0 )
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
				uprintf(". verify error at offset $8. written $2, readback $2.\n", ulProgressCnt+sizCmpCnt, pucCmp1[sizCmpCnt], pucCmp0[sizCmpCnt]);
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


NETX_CONSOLEAPP_RESULT_T spi_read_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, unsigned char *pucDataStartAdr)
{
	unsigned long ulC, ulE;
	unsigned char *pucDC;
	unsigned long ulSegSize, ulMaxSegSize;
	unsigned long ulProgressCnt;
	int iResult;


	uprintf("# Read data...\n");

	ulMaxSegSize = SPI_BUFFER_SIZE;

	/* loop over all data */
	ulC = ulFlashStartAdr;
	ulE = ulC + ulDataByteLen;
	pucDC = pucDataStartAdr;

	ulProgressCnt = 0;
	progress_bar_init(ulDataByteLen);

	while( ulC<ulE ) {
		/* get the next segment, limit it to 'ulMaxSegSize' */
		ulSegSize = ulE - ulC;
		if( ulSegSize>ulMaxSegSize )
		{
			ulSegSize = ulMaxSegSize;
		}

		/* read the segment */
		iResult = Drv_SpiReadFlash(ptFlashDev, ulC, pucDC, ulSegSize);
		if( iResult==0 )
		{
			return NETX_CONSOLEAPP_RESULT_ERROR;
		}

		/* next segment */
		ulC += ulSegSize;
		pucDC += ulSegSize;

		/* inc progress */
		ulProgressCnt += ulSegSize;
		progress_bar_set_position(ulProgressCnt);
	}

	progress_bar_finalize();
	uprintf(". read ok\n");

	/* read ok! */
	return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T spi_erase_with_progress(const SPI_FLASH_T *ptFlashDev, unsigned long ulFlashStartAdr, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulSectorSize;
	unsigned long ulOffset;
	unsigned long ulSectorStartAddress;
	unsigned long ulSectorEndAddress;
	unsigned long ulAddress;
	unsigned long ulProgressCnt;
	int iResult;


	uprintf("# Erase flash...\n");

	/* get the sector start and end address */
	ulSectorSize          = ptFlashDev->ulSectorSize;
	ulOffset              = ulFlashStartAdr % ulSectorSize;
	ulSectorStartAddress  = ulFlashStartAdr - ulOffset;
	ulSectorEndAddress    = ulFlashStartAdr + ulDataByteLen + ulSectorSize-1;
	ulSectorEndAddress   &= ~((1<<ptFlashDev->uiSectorAdrShift)-1);

	/* show start and end of erase area */
	uprintf(". erase $8 - $8\n", ulSectorStartAddress, ulSectorEndAddress);

	ulProgressCnt = 0;
	progress_bar_init( ulDataByteLen );

	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* erase the complete area */
	ulAddress = ulSectorStartAddress;
	while( ulAddress<ulSectorEndAddress )
	{
		iResult = Drv_SpiEraseFlashSector(ptFlashDev, ulAddress);
		if( iResult==0 )
		{
			uprintf("! erase failed at address $8\n", ulAddress);
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

	/* return result */
	return tResult;
}


/*-----------------------------------*/

