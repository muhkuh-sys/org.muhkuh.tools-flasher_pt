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

#include "parflash_common.h"
#include "progress_bar.h"
#include "uprintf.h"




static void showPflashError(FLASH_ERRORS_E tFlashError)
{
	switch(tFlashError)
	{
	case eFLASH_NO_ERROR:
		uprintf(". ok\n");
		break;

	case eFLASH_GENERAL_ERROR:
		uprintf("! error: flash general error!\n");
		break;

	case eFLASH_LOCKED:
		uprintf("! error: the flash is locked!\n");
		break;

	case eFLASH_BUSY:
		uprintf("! error: the flash is busy!\n");
		break;

	case eFLASH_VPP_LOW:
		uprintf("! error: vpp low!\n");
		break;

	case eFLASH_NO_ERASED:
		uprintf("! error: the flash was not erased!\n");
		break;

	case eFLASH_INVALID_PARAMETER:
		uprintf("! error: invalid parameter!\n");
		break;

	case eFLASH_ABORTED:
		uprintf("! error: flash aborted!\n");
		break;

	case eFLASH_DEVICE_FAILED:
		uprintf("! error: flash device failed!\n");
		break;

	default:
		uprintf("! error: received unknown errorcode!\n");
		break;
	};
}


static NETX_CONSOLEAPP_RESULT_T parflash_check_size(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, unsigned long ulDataByteLen)
{
	unsigned long ulOffsetSize;
	NETX_CONSOLEAPP_RESULT_T tResult;


	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* check if Image is too big to fit on Flash */
	ulOffsetSize  = ptFlashDev->ulFlashSize;
	ulOffsetSize -= ptFlashDev->atSectors[ulStartSector].ulOffset;
	uprintf(". Check size...\n");
	uprintf(". data size:  0x%08x\n", ulDataByteLen);
	uprintf(". data offset: 0x%08x\n", ulOffsetSize);
	uprintf(". flash size: 0x%08x\n", ptFlashDev->ulFlashSize);
	if( ulOffsetSize<ulDataByteLen )
	{
		/* the image does not fit */
		uprintf("! error, data size exceeds flash\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}

	return tResult;
}


static NETX_CONSOLEAPP_RESULT_T parflash_unlock(FLASH_DEVICE_T *ptFlashDev)
{
	FLASH_ERRORS_E tFlashError;
	NETX_CONSOLEAPP_RESULT_T tResult;


	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* unlock the complete flash */
	tFlashError = ptFlashDev->ptFlashFuncs->pfnUnlock(ptFlashDev);
	if( tFlashError!=eFLASH_NO_ERROR )
	{
		/* failed to unlock all sectors */
		uprintf(". failed to unlock all flash sectors\n");
		showPflashError(tFlashError);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}

	return tResult;
}


NETX_CONSOLEAPP_RESULT_T parflash_writeImage(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, const unsigned char *pbData, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long       ulSectorCnt;
	const unsigned char *pbDataCnt;
	const unsigned char *pbDataEnd;
	unsigned long       ulMaxSegmentLen;
	unsigned long       ulSegmentLen;
	unsigned long       ulSizeLeft;
	unsigned char       *pbDstCnt;
	unsigned long       ulSectorStartOffset;
	FLASH_ERRORS_E      tFlashError;
	unsigned long       ulProgressCnt;


	/* check size */
	tResult = parflash_check_size(ptFlashDev, ulStartSector, ulDataByteLen);
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		ulSectorCnt = ulStartSector;

		progress_bar_init( ulDataByteLen );

		tResult = parflash_unlock(ptFlashDev);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("# Write data...\n");

			pbDataCnt  = pbData;
			pbDataEnd  = pbData + ulDataByteLen;
			ulSizeLeft = ulDataByteLen;
			while( pbDataCnt<pbDataEnd )
			{
				/* try to erase the flash sector */
				tFlashError = ptFlashDev->ptFlashFuncs->pfnErase(ptFlashDev, ulSectorCnt);
				if( tFlashError!=eFLASH_NO_ERROR )
				{
					/* failed to erase the sector */
					uprintf(". failed to erase flash sector %d\n", ulSectorCnt);
					showPflashError(tFlashError);
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					break;
				}


				ulMaxSegmentLen = ptFlashDev->atSectors[ulSectorCnt].ulSize;
				ulSegmentLen = (ulSizeLeft>=ulMaxSegmentLen) ? ulMaxSegmentLen : ulSizeLeft;

				ulSectorStartOffset = 0;
				tFlashError = ptFlashDev->ptFlashFuncs->pfnProgram(ptFlashDev, ptFlashDev->atSectors[ulSectorCnt].ulOffset + ulSectorStartOffset, ulSegmentLen, pbDataCnt);
				if( tFlashError!=eFLASH_NO_ERROR )
				{
					/* failed to program the sector */
					uprintf(". failed to program flash sector %d\n", ulSectorCnt);
					showPflashError(tFlashError);
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					break;
				}

				pbDataCnt += ulSegmentLen;
				ulSizeLeft -= ulSegmentLen;
				++ulSectorCnt;

				/* show progress bar */
				progress_bar_set_position(ulDataByteLen-ulSizeLeft);
			}
		}

		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			progress_bar_finalize();
			uprintf(". write ok...\n");

			/* verify the image */
			uprintf("# Verify data...\n");

			ulProgressCnt = 0;
			progress_bar_init( ulDataByteLen );

			pbDataCnt = pbData;
			pbDstCnt = ptFlashDev->pbFlashBase;
			while( *(pbDataCnt++)==*(pbDstCnt++) && pbDataCnt<pbDataEnd )
			{
				if( (((unsigned long)pbDataCnt)&0xffff)==0 )
				{
					ulProgressCnt += 0x10000;
					progress_bar_set_position(ulProgressCnt);
				}
			}

			progress_bar_finalize();

			if( pbDataCnt<pbDataEnd )
			{
				/* verify error */
				uprintf("! verify error\n");
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			}
			else
			{
				uprintf(". verify ok\n");
			}
		}
	}

	return tResult;
}


NETX_CONSOLEAPP_RESULT_T parflash_erase(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long            ulSectorCnt;
	FLASH_ERRORS_E           tFlashError;
	unsigned long            ulProgressCnt;
	unsigned long            ulMaxSegmentLen;
	unsigned long            ulSegmentLen;
	unsigned long            ulSizeLeft;


	if( ulDataByteLen==0xffffffff )
	{
		ulDataByteLen = ptFlashDev->ulFlashSize;
	}

	/* check size */
	tResult = parflash_check_size(ptFlashDev, ulStartSector, ulDataByteLen);
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		ulSectorCnt = ulStartSector;

		ulProgressCnt = 0;
		progress_bar_init( ulDataByteLen );

		tResult = parflash_unlock(ptFlashDev);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			uprintf("# Erase Flash ...\n");
			ulSizeLeft = ulDataByteLen;
			while( ulSizeLeft!=0 )
			{
				/* try to erase the flash sector */
				tFlashError = ptFlashDev->ptFlashFuncs->pfnErase(ptFlashDev, ulSectorCnt);
				if( tFlashError!=eFLASH_NO_ERROR )
				{
					/* failed to erase the sector */
					uprintf(". failed to erase flash sector %d\n", ulSectorCnt);
					showPflashError(tFlashError);
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					break;
				}

				ulMaxSegmentLen = ptFlashDev->atSectors[ulSectorCnt].ulSize;
				ulSegmentLen    = (ulSizeLeft>=ulMaxSegmentLen) ? ulMaxSegmentLen : ulSizeLeft;
				ulSizeLeft     -= ulSegmentLen;

				++ulSectorCnt;
			}
			uprintf(". erase ok ...\n");
		}
	}

	return tResult;
}


NETX_CONSOLEAPP_RESULT_T parflash_read(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, unsigned char *pbData, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned char *pbDataCnt;
	unsigned char *pbDataEnd;
	unsigned char *pbDstCnt;
	unsigned long ulProgressCnt;


	/* check size */
	tResult = parflash_check_size(ptFlashDev, ulStartSector, ulDataByteLen);
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* read the image */
		uprintf("# Read data...\n");

		ulProgressCnt = 0;
		progress_bar_init( ulDataByteLen );

		pbDataCnt = pbData;
		pbDataEnd = pbData + ulDataByteLen;
		pbDstCnt = ptFlashDev->pbFlashBase;
		while( pbDataCnt<pbDataEnd )
		{
			*(pbDataCnt++) = *(pbDstCnt++);
			if( (((unsigned long)pbDataCnt)&0xffff)==0 )
			{
				ulProgressCnt += 0x10000;
				progress_bar_set_position(ulProgressCnt);
			}
		}

		progress_bar_finalize();

		uprintf(". read ok\n");
	}

	return tResult;
}


NETX_CONSOLEAPP_RESULT_T parflash_verify(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, const unsigned char *pbData, unsigned long ulDataByteLen)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const unsigned char *pbDataCnt;
	const unsigned char *pbDataEnd;
	unsigned char *pbDstCnt;
	unsigned long ulProgressCnt;


	/* check size */
	tResult = parflash_check_size(ptFlashDev, ulStartSector, ulDataByteLen);
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* verify the image */
		uprintf("# Verify data...\n");

		ulProgressCnt = 0;
		progress_bar_init( ulDataByteLen );

		pbDataCnt = pbData;
		pbDataEnd = pbData + ulDataByteLen;
		pbDstCnt = ptFlashDev->pbFlashBase;
		while( *(pbDataCnt++)==*(pbDstCnt++) && pbDataCnt<pbDataEnd )
		{
			if( (((unsigned long)pbDataCnt)&0xffff)==0 )
			{
				ulProgressCnt += 0x10000;
				progress_bar_set_position(ulProgressCnt);
			}
		}

		progress_bar_finalize();

		if( pbDataCnt<pbDataEnd )
		{
			/* verify error */
			uprintf("! verify error\n");
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			uprintf(". verify ok\n");
		}
	}

	return tResult;
}
