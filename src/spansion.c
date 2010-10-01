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

#include "spansion.h"
#include <string.h>
#include "delay.h"
#include "uprintf.h"


#if CFG_DEBUGMSG!=0
        /* show all messages by default */
        static unsigned long s_ulCurSettings = 0xffffffff;

	#define DEBUGZONE(n)  (s_ulCurSettings&(0x00000001<<(n)))

	//
	// These defines must match the ZONE_* defines
	//
	#define DBG_ZONE_ERROR      0
	#define DBG_ZONE_WARNING    1
	#define DBG_ZONE_FUNCTION   2
	#define DBG_ZONE_INIT       3
	#define DBG_ZONE_VERBOSE    7

	#define ZONE_ERROR          DEBUGZONE(DBG_ZONE_ERROR)
	#define ZONE_WARNING        DEBUGZONE(DBG_ZONE_WARNING)
	#define ZONE_FUNCTION       DEBUGZONE(DBG_ZONE_FUNCTION)
	#define ZONE_INIT           DEBUGZONE(DBG_ZONE_INIT)
        #define ZONE_VERBOSE        DEBUGZONE(DBG_ZONE_VERBOSE)

        #define DEBUGMSG(cond,printf_exp) ((void)((cond)?(uprintf printf_exp),1:0))
#else  // DEBUG
        #define DEBUGMSG(cond,printf_exp) ((void)0)
#endif // DEBUG


#define DQ0                                   0x01U
#define DQ1                                   0x02U
#define DQ2                                   0x04U
#define DQ3                                   0x08U
#define DQ4                                   0x10U
#define DQ5                                   0x20U
#define DQ6                                   0x40U
#define DQ7                                   0x80U

#define MFGCODE_SPANSION                      0x01U

#define SPANSION_CMD_RESET                    0xF0U

#define SPANSION_CMD_AUTOSEL_CYCLE0           0xAAU
#define SPANSION_CMD_AUTOSEL_CYCLE1           0x55U
#define SPANSION_CMD_AUTOSEL_CYCLE2           0x90U
#define SPANSION_ADR_AUTOSEL_CYCLE0           0x555U
#define SPANSION_ADR_AUTOSEL_CYCLE1           0x2AAU
#define SPANSION_ADR_AUTOSEL_CYCLE2           0x555U

#define SPANSION_CMD_BUFFERWRITE_CYCLE0       0xAAU
#define SPANSION_CMD_BUFFERWRITE_CYCLE1       0x55U
#define SPANSION_CMD_BUFFERWRITE_CYCLE2       0x25U
#define SPANSION_ADR_BUFFERWRITE_CYCLE0       0x555U
#define SPANSION_ADR_BUFFERWRITE_CYCLE1       0x2AAU

#define SPANSION_CMD_BUFFERWRITEABORT_CYCLE0  0xAAU
#define SPANSION_CMD_BUFFERWRITEABORT_CYCLE1  0x55U
#define SPANSION_CMD_BUFFERWRITEABORT_CYCLE2  0xF0U
#define SPANSION_ADR_BUFFERWRITEABORT_CYCLE0  0x555U
#define SPANSION_ADR_BUFFERWRITEABORT_CYCLE2  0x2AAU

#define SPANSION_CMD_PROGRAM_CYCLE0           0xAAU
#define SPANSION_CMD_PROGRAM_CYCLE1           0x55U
#define SPANSION_CMD_PROGRAM_CYCLE2           0xA0U
#define SPANSION_ADR_PROGRAM_CYCLE0           0x555U
#define SPANSION_ADR_PROGRAM_CYCLE1           0x2AAU
#define SPANSION_ADR_PROGRAM_CYCLE2           0x555U

#define SPANSION_CMD_BUFFERPROG               0x29U

#define SPANSION_CMD_ERASE_CYCLE0             0xAAU
#define SPANSION_CMD_ERASE_CYCLE1             0x55U
#define SPANSION_CMD_ERASE_CYCLE2             0x80U
#define SPANSION_CMD_ERASE_CYCLE3             0xAAU
#define SPANSION_CMD_ERASE_CYCLE4             0x55U
#define SPANSION_ADR_ERASE_CYCLE0             0x555U
#define SPANSION_ADR_ERASE_CYCLE1             0x2AAU
#define SPANSION_ADR_ERASE_CYCLE2             0x555U
#define SPANSION_ADR_ERASE_CYCLE3             0x555U
#define SPANSION_ADR_ERASE_CYCLE4             0x2AAU

#define SPANSION_CMD_CHIPERASE_CYCLE5         0x10U
#define SPANSION_ADR_CHIPERASE_CYCLE5         0x555U

#define SPANSION_CMD_SECTORERASE_CYCLE_5      0x30U

#define SPANSION_CMD_ERASEPROG_SUSPEND        0xB0U
#define SPANSION_CMD_ERASEPROG_RESUME         0x30U

#define SPANSION_ADR_PPB_ENTRY_CYCLE0         0x555U
#define SPANSION_CMD_PPB_ENTRY_CYCLE0         0xaaU
#define SPANSION_ADR_PPB_ENTRY_CYCLE1         0x2AAU
#define SPANSION_CMD_PPB_ENTRY_CYCLE1         0x55U
#define SPANSION_ADR_PPB_ENTRY_CYCLE2         0x555U
#define SPANSION_CMD_PPB_ENTRY_CYCLE2         0xC0U

#define SPANSION_ADR_PPB_CLEARALL_CYCLE0      0x000U
#define SPANSION_CMD_PPB_CLEARALL_CYCLE0      0x80U
#define SPANSION_ADR_PPB_CLEARALL_CYCLE1      0x000U
#define SPANSION_CMD_PPB_CLEARALL_CYCLE1      0x30U

#define SPANSION_ADR_PPB_EXIT_CYCLE0	        0x000U
#define SPANSION_CMD_PPB_EXIT_CYCLE0          0x90U
#define SPANSION_ADR_PPB_EXIT_CYCLE1          0x000U
#define SPANSION_CMD_PPB_EXIT_CYCLE1          0x00U



#define READ_USHORT(ulAddress)   (*(volatile unsigned short*)ulAddress)
#define READ_ULONG(ulAddress)    (*(volatile unsigned long*)ulAddress)

#define READ_FLASH(ulAddress)    ((ptFlashDev->fPaired)? READ_ULONG(ulAddress) : READ_USHORT(ulAddress))

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))


typedef enum 
{
 DEV_STATUS_UNKNOWN = 0,
 DEV_NOT_BUSY,
 DEV_BUSY,
 DEV_EXCEEDED_TIME_LIMITS,
 DEV_SUSPEND,
 DEV_WRITE_BUFFER_ABORT,
 DEV_STATUS_GET_PROBLEM,
 DEV_VERIFY_ERROR,
 DEV_BYTES_PER_OP_WRONG
} DEVSTATUS;

typedef struct FLASH_COMMAND_BLOCK_Ttag
{
  unsigned long ulAddress;
  unsigned char bCmd;
} FLASH_COMMAND_BLOCK_T;

static FLASH_ERRORS_E FlashWaitEraseDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashWaitWriteDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulOffsetData, BOOL fBufferWrite);
static int            FlashIsset        (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulSet, unsigned long ulClear);
static void           FlashWriteCommand (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned int uiCmd);
static void           FlashWriteCommandSequence(const FLASH_DEVICE_T *ptFlashDev, FLASH_COMMAND_BLOCK_T* ptCmd, unsigned long ulCount);
static FLASH_ERRORS_E FlashNormalWrite(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector,      unsigned long ulOffset, const unsigned char* pbData, unsigned long ulWriteSize);

static FLASH_ERRORS_E FlashReset      (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashErase      (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashEraseAll   (const FLASH_DEVICE_T *ptFlashDev);
static FLASH_ERRORS_E FlashProgram    (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData);
static FLASH_ERRORS_E FlashLock       (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashUnlock     (const FLASH_DEVICE_T *ptFlashDev);

static FLASH_FUNCTIONS_T s_tSpansionFuncs =
{
	FlashReset,
	FlashErase,
	FlashEraseAll,
	FlashProgram,
	FlashLock,
	FlashUnlock
};

static FLASH_COMMAND_BLOCK_T s_atAutoSelect[] =
{
	{SPANSION_ADR_AUTOSEL_CYCLE0, SPANSION_CMD_AUTOSEL_CYCLE0},
	{SPANSION_ADR_AUTOSEL_CYCLE1, SPANSION_CMD_AUTOSEL_CYCLE1},
	{SPANSION_ADR_AUTOSEL_CYCLE2, SPANSION_CMD_AUTOSEL_CYCLE2},  
};

static FLASH_COMMAND_BLOCK_T s_atErasePrefix[] =
{
	{SPANSION_ADR_ERASE_CYCLE0, SPANSION_CMD_ERASE_CYCLE0},
	{SPANSION_ADR_ERASE_CYCLE1, SPANSION_CMD_ERASE_CYCLE1},
	{SPANSION_ADR_ERASE_CYCLE2, SPANSION_CMD_ERASE_CYCLE2},
	{SPANSION_ADR_ERASE_CYCLE3, SPANSION_CMD_ERASE_CYCLE3},
	{SPANSION_ADR_ERASE_CYCLE4, SPANSION_CMD_ERASE_CYCLE4},
};

static FLASH_COMMAND_BLOCK_T s_atPPBEntry[] =
{
	{SPANSION_ADR_PPB_ENTRY_CYCLE0, SPANSION_CMD_PPB_ENTRY_CYCLE0},
	{SPANSION_ADR_PPB_ENTRY_CYCLE1, SPANSION_CMD_PPB_ENTRY_CYCLE1},
	{SPANSION_ADR_PPB_ENTRY_CYCLE2, SPANSION_CMD_PPB_ENTRY_CYCLE2}
};

static FLASH_COMMAND_BLOCK_T s_atPPBExit[] =
{
	{SPANSION_ADR_PPB_EXIT_CYCLE0, SPANSION_CMD_PPB_EXIT_CYCLE0},
        {SPANSION_ADR_PPB_EXIT_CYCLE1, SPANSION_CMD_PPB_EXIT_CYCLE1}
};

int SpansionIdentifyFlash(FLASH_DEVICE_T *ptFlashDev)
{
	unsigned char abDeviceId[3] = {0};
	int           fRet          = FALSE;


	DEBUGMSG(ZONE_FUNCTION, ("+SpansionIdentifyFlash(): ptFlashDev=0x%08x\n", ptFlashDev));

	/* try to identify SpansionFlash */
	FlashWriteCommandSequence(ptFlashDev, s_atAutoSelect, ARRAYSIZE(s_atAutoSelect));

	ptFlashDev->ucManufacturer = ptFlashDev->pucFlashBase[0];

	abDeviceId[0] = ptFlashDev->pucFlashBase[2];
	abDeviceId[1] = ptFlashDev->pucFlashBase[2];
	abDeviceId[2] = ptFlashDev->pucFlashBase[2]; 

	FlashReset(ptFlashDev, 0);

	if(MFGCODE_SPANSION == ptFlashDev->ucManufacturer)
	{
		/* TODO: Check Device IDs */

		strcpy(ptFlashDev->acIdent, "SPANSION");
		memcpy(&(ptFlashDev->tFlashFunctions), &s_tSpansionFuncs, sizeof(FLASH_FUNCTIONS_T));
		fRet = TRUE;
	}

	DEBUGMSG(ZONE_FUNCTION, ("+SpansionIdentifyFlash(): fRet=%d\n", fRet));
	return fRet;
}

// ////////////////////////////////////////////////////
//! Reset the flash sector to read mode
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \param ulSector    Sector to reset to read mode
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashReset(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
	FLASH_ERRORS_E tResult;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashReset(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));

	FlashWriteCommand(ptFlashDev, 0, 0, SPANSION_CMD_RESET);
	tResult = eFLASH_NO_ERROR;

	DEBUGMSG(ZONE_FUNCTION, ("-FlashReset(): tResult=%d\n", tResult));
	return tResult;
}

// ////////////////////////////////////////////////////
//! Erase a flash sector
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \param ulSector    Sector to erase
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashErase(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
	FLASH_ERRORS_E tResult = eFLASH_NO_ERROR;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashErase(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));

	FlashWriteCommandSequence(ptFlashDev, s_atErasePrefix, ARRAYSIZE(s_atErasePrefix));
	FlashWriteCommand(ptFlashDev, ulSector, 0, SPANSION_CMD_SECTORERASE_CYCLE_5);

	tResult = FlashWaitEraseDone(ptFlashDev, ulSector);

	FlashReset(ptFlashDev, ulSector);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashErase(): tResult=%d\n", tResult));
	return tResult;
}

// ////////////////////////////////////////////////////
//! Erase whole flash
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashEraseAll(const FLASH_DEVICE_T *ptFlashDev)
{
	FLASH_ERRORS_E tResult = eFLASH_NO_ERROR;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashEraseAll(): ptFlashDev=0x%08x\n", ptFlashDev));

	FlashWriteCommandSequence(ptFlashDev, s_atErasePrefix, ARRAYSIZE(s_atErasePrefix));
	FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_CHIPERASE_CYCLE5, SPANSION_CMD_CHIPERASE_CYCLE5);

	tResult = FlashWaitEraseDone(ptFlashDev, 0);

	FlashReset(ptFlashDev, 0);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashEraseAll(): tResult=%d\n", tResult));

	return tResult;
}

// ////////////////////////////////////////////////////
//! Programs flash using single word/dword accesses
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ulStartOffset Offset to start writing at
//!  \param ulLength      Length of data to write
//!  \param pvData        Data pointer
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashNormalWrite(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, const unsigned char *pucData, unsigned long ulWriteSize)
{
	FLASH_ERRORS_E  eRet       = eFLASH_NO_ERROR;
	unsigned long   ulBusWidth = ptFlashDev->fPaired? sizeof(unsigned long) : sizeof(unsigned short);
	unsigned long   ulIdx      = 0;
	CADR_T tSrc;
	VADR_T tDst;
	unsigned long ulLastData;


	/* TODO: Think about unlock bypass mode programming which is faster
	 * for single word/dword writes
	 */

	DEBUGMSG(ZONE_FUNCTION, ("+FlashNormalWrite(): ptFlashDev=0x%08x, ulSector=%d, ulOffset=0x%08x, pucData=0x%08x, ulWriteSize=0x%08x\n", ptFlashDev, ulSector, ulOffset, pucData, ulWriteSize));

	tSrc.puc = pucData;
	tDst.puc = ptFlashDev->pucFlashBase + ulOffset;

	for(ulIdx = 0; ulIdx < ulWriteSize / ulBusWidth; ulIdx++)
	{
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE0, SPANSION_CMD_PROGRAM_CYCLE0);
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE1, SPANSION_CMD_PROGRAM_CYCLE1);
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE2, SPANSION_CMD_PROGRAM_CYCLE2);

		if(ptFlashDev->fPaired)
		{
			ulLastData = tSrc.pul[ulIdx];
			tDst.pul[ulIdx] = tSrc.pul[ulIdx];
		}
		else
		{
			ulLastData = tSrc.pus[ulIdx];
			tDst.pus[ulIdx] = tSrc.pus[ulIdx];
		}

		eRet = FlashWaitWriteDone(ptFlashDev, ulSector, ulOffset + ulIdx * ulBusWidth, ulLastData, FALSE);
		if(eRet!=eFLASH_NO_ERROR)
		{
			FlashWriteCommand(ptFlashDev, ulSector, 0, SPANSION_CMD_RESET);
			break;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashNormalWrite(): eRet=%d\n", eRet));
	return eRet;
}


static FLASH_ERRORS_E FlashBufferedWrite(const FLASH_DEVICE_T *ptFlashDev, const unsigned char *pucSource, unsigned long ulLength, unsigned long ulCurrentSector, unsigned long ulCurrentOffset)
{
	FLASH_ERRORS_E tResult;
	unsigned long ulWriteSize;
	unsigned int uiWriteElements;
	unsigned long ulDeviceBufferSize;
	unsigned long ulSectorBytesLeft;
	unsigned long ulLastData;
	unsigned long ulLastOffset;
	CADR_T tSrc;
	VADR_T tDst;
	VADR_T tEnd;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashBufferedWrite(): ptFlashDev=0x%08x, pucSource=0x%08x, ulLength=0x%08x, ulCurrentSector=0x%08x, ulCurrentOffset=0x%08x\n", ptFlashDev, pucSource, ulLength, ulCurrentSector, ulCurrentOffset));

	/* Be optimistic. */
	tResult = eFLASH_NO_ERROR;

	/* Get the source address. */
	tSrc.puc = pucSource;

	/* Get the buffer size. */
	ulDeviceBufferSize = ptFlashDev->ulMaxBufferWriteSize;
	DEBUGMSG(ZONE_FUNCTION, (". write buffer size for 1 device: 0x%08x bytes\n", ulDeviceBufferSize));
	if(ptFlashDev->fPaired)
	{
		ulDeviceBufferSize *= 2;
		DEBUGMSG(ZONE_FUNCTION, (". write buffer size for all devices: 0x%08x bytes\n", ulDeviceBufferSize));
	}

	while(ulLength>0)
	{
		uiWriteElements = 0;

		/* Limit the write size to the buffer size. */
		ulWriteSize = ulLength;
		if(ulWriteSize>ulDeviceBufferSize)
		{
			ulWriteSize = ulDeviceBufferSize;
		}

		/* Limit the write size to the end of the sector. */
		ulSectorBytesLeft = ptFlashDev->atSectors[ulCurrentSector].ulSize - ulCurrentOffset;
		if(ulWriteSize>ulSectorBytesLeft)
		{
			ulWriteSize = ulSectorBytesLeft;
		}

		/* Convert the byte counter to the number of elements to write. */
		uiWriteElements  = ulWriteSize >> ptFlashDev->tBits;
		uiWriteElements -= 1;

		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITE_CYCLE0, SPANSION_CMD_BUFFERWRITE_CYCLE0);
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITE_CYCLE1, SPANSION_CMD_BUFFERWRITE_CYCLE1);
		FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, SPANSION_CMD_BUFFERWRITE_CYCLE2);    
		FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, uiWriteElements);

		ulLength -= ulWriteSize;

		tDst.puc  = ptFlashDev->pucFlashBase;
		tDst.puc += ptFlashDev->atSectors[ulCurrentSector].ulOffset;
		tDst.puc += ulCurrentOffset;

		tEnd.puc = tDst.puc + ulWriteSize;

		switch(ptFlashDev->tBits)
		{
		case BUS_WIDTH_8Bit:
			/* Fill the buffer. */
			do
			{
				*(tDst.puc++) = *(tSrc.puc++);
			} while( tDst.puc<tEnd.puc );
			ulCurrentOffset += ulWriteSize;
			/* Get the last location. */
			ulLastOffset = ulCurrentOffset - 1;
			/* Get the last data. */
			ulLastData = *(tSrc.puc-1);
			break;

		case BUS_WIDTH_16Bit:
			/* Fill the buffer. */
			do
			{
				*(tDst.pus++) = *(tSrc.pus++);
			} while( tDst.pus<tEnd.pus );
			ulCurrentOffset += ulWriteSize;
			/* Get the last location. */
			ulLastOffset = ulCurrentOffset - 1;
			/* Get the last data. */
			ulLastData = *(tSrc.pus-1);
			break;

		case BUS_WIDTH_32Bit:
			/* Fill the buffer. */
			do
			{
				*(tDst.pul++) = *(tSrc.pul++);
			} while( tDst.pul<tEnd.pul );
			ulCurrentOffset += ulWriteSize;
			/* Get the last location. */
			ulLastOffset = ulCurrentOffset - 1;
			/* Get the last data. */
			ulLastData = *(tSrc.pul-1);
			break;
		}

		FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, SPANSION_CMD_BUFFERPROG);

		/* Wait for Flashing complete */
		tResult = FlashWaitWriteDone(ptFlashDev, ulCurrentSector, ulLastOffset, ulLastData, TRUE);
		if( tResult!=eFLASH_NO_ERROR )
		{
			if(tResult==eFLASH_ABORTED)
			{
				FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITEABORT_CYCLE0, SPANSION_CMD_BUFFERWRITEABORT_CYCLE0);
				FlashWriteCommand(ptFlashDev, ulCurrentSector, ulLastOffset, SPANSION_CMD_BUFFERWRITEABORT_CYCLE1);
				FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITEABORT_CYCLE2, SPANSION_CMD_BUFFERWRITEABORT_CYCLE2);
			}
			else if(tResult==eFLASH_DEVICE_FAILED)
			{
				FlashReset(ptFlashDev, 0);
			}

			break;
		}

		/* sector wrap around */    
		if(ulCurrentOffset == ptFlashDev->atSectors[ulCurrentSector].ulSize)
		{
			++ulCurrentSector;
			ulCurrentOffset = 0;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashBufferedWrite(): tResult=%d\n", tResult));
	return tResult;
}


// ////////////////////////////////////////////////////
//! Program flash (uses buffered writes whenever possible)
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ulStartOffset Offset to start writing at
//!  \param ulLength      Length of data to write
//!  \param pvData        Data pointer
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashProgram(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void *pvData)
{
	unsigned long  ulCurrentSector;
	unsigned long  ulCurrentOffset;
	const unsigned char *pucSource;
	FLASH_ERRORS_E tResult;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashProgram(): ptFlashDev=0x%08x, ulStartOffset=0x%08x, ulLength=0x%08x, pvData=0x%08x\n", ptFlashDev, ulStartOffset, ulLength, pvData));

	/* Be optimistic. */
	tResult = eFLASH_NO_ERROR;

	pucSource = (const unsigned char*)pvData;

	/* Determine the start sector and offset inside the sector */
	ulCurrentSector = cfi_find_matching_sector_index(ptFlashDev, ulStartOffset);
	if( ulCurrentSector==0xffffffffU )
	{
		tResult = eFLASH_INVALID_PARAMETER;
	}
	else if( ulStartOffset+ulLength>ptFlashDev->ulFlashSize )
	{
		tResult = eFLASH_INVALID_PARAMETER;
	}
	else
	{
		ulCurrentOffset = ulStartOffset - ptFlashDev->atSectors[ulCurrentSector].ulOffset;

		FlashReset(ptFlashDev, 0);

		/* Check if address if on a page boundary page size is 8words/16bytes */
		if( (ulCurrentOffset&0x0000000fU)!=0 )
		{
			unsigned short usWriteSize;

			/* get the maximum size for the normal write operation (only write until buffered write can be used) */
			usWriteSize = (USHORT)(16 - (ulCurrentOffset & 0xF));
			/* limit the write size to the requested chunk */
			if( usWriteSize>ulLength )
			{
				usWriteSize = ulLength;
			}
			tResult = FlashNormalWrite(ptFlashDev, ulCurrentSector, ulCurrentOffset, pucSource, usWriteSize);
			if(tResult==eFLASH_NO_ERROR)
			{
				ulCurrentOffset += usWriteSize;
				pucSource        += usWriteSize;
				ulLength        -= usWriteSize;

				/* Check for new sector wraparound */
				if(ulCurrentOffset >= ptFlashDev->atSectors[ulCurrentSector].ulSize)
				{
					ulCurrentOffset = ptFlashDev->atSectors[ulCurrentSector].ulSize - ulCurrentOffset;
					++ulCurrentSector;
				}
			}
		}

		if( tResult==eFLASH_NO_ERROR )
		{
			tResult = FlashBufferedWrite(ptFlashDev, pucSource, ulLength, ulCurrentSector, ulCurrentOffset);
		}
	}

	FlashReset(ptFlashDev, 0);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashProgram(): tResult=%d\n", tResult));
	return tResult;
}


FLASH_ERRORS_E FlashLock(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
        FLASH_ERRORS_E tResult;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashLock(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));

	/* not yet */
	tResult = eFLASH_INVALID_PARAMETER;

	DEBUGMSG(ZONE_FUNCTION, ("-FlashProgram(): tResult=%d\n", tResult));

	return tResult;
}


FLASH_ERRORS_E FlashUnlock(const FLASH_DEVICE_T *ptFlashDev)
{
        unsigned long ulNotProtected;
        unsigned long ulProtectionBit;
	unsigned long ulSector;
	FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;
	volatile unsigned char* pbReadAddr;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashUnlock(): ptFlashDev=0x%08x\n", ptFlashDev));

	/* default is unprotected */
	ulNotProtected = 1;

	/* enter ppb mode */
	FlashWriteCommandSequence(ptFlashDev, s_atPPBEntry, sizeof(s_atPPBEntry) / sizeof(s_atPPBEntry[0]));

	/* loop over all sectors and check if they are protected */
	ulSector = 0;
	while( ulSector<ptFlashDev->ulSectorCnt )
	{
		/* get sector address */
		pbReadAddr = ptFlashDev->pucFlashBase + ptFlashDev->atSectors[ulSector].ulOffset;

		/* get protection info */
		ulProtectionBit = *pbReadAddr;
		if( ulProtectionBit==0 )
		{
			DEBUGMSG(ZONE_VERBOSE, (". sector %d is protected\n", ulSector));
		}
		ulNotProtected &= ulProtectionBit;

		/* next sector */
		++ulSector;
	}

	/* clear protection if at least one sector is protected */
	if( ulNotProtected==0 )
	{
		DEBUGMSG(ZONE_VERBOSE, (". unlocking all sectors...\n"));
		/* the sector is protected */
		FlashWriteCommand(ptFlashDev, SPANSION_ADR_PPB_CLEARALL_CYCLE0, 0, SPANSION_CMD_PPB_CLEARALL_CYCLE0);
		FlashWriteCommand(ptFlashDev, SPANSION_ADR_PPB_CLEARALL_CYCLE1, 0, SPANSION_CMD_PPB_CLEARALL_CYCLE1);

		/* wait for erase done */
		eRet = FlashWaitEraseDone(ptFlashDev, 0);
	}

	/* leave ppb mode */
	FlashWriteCommandSequence(ptFlashDev, s_atPPBExit, sizeof(s_atPPBExit) / sizeof(s_atPPBExit[0]));

	/* back to memory mode */
	FlashReset(ptFlashDev, ulSector);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashProgram(): eRet=0x$8\n", eRet));

	/* done */
	return eRet;
}


// ////////////////////////////////////////////////////
//! Write a command to the FLASH
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector FLASH sector number
//!  \param ulOffset Offset address in the actual FLASH sector
//!  \param bCmd Command to execute
// ////////////////////////////////////////////////////
void FlashWriteCommand(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned int uiCmd)
{
	volatile unsigned char* pbWriteAddr = ptFlashDev->pucFlashBase + ptFlashDev->atSectors[ulSector].ulOffset;
	unsigned long ulValue;


	switch(ptFlashDev->tBits)
	{
	case BUS_WIDTH_8Bit:
		/* 8bits cannot be paired */
		pbWriteAddr[ulOffset] = (unsigned char)uiCmd;
		break;

	case BUS_WIDTH_16Bit:
		ulValue = uiCmd;
		if( ptFlashDev->fPaired!=0 )
		{
			ulValue |= ulValue << 8U;
		}
		((volatile unsigned short*)pbWriteAddr)[ulOffset] = (unsigned short)ulValue;
		break;

	case BUS_WIDTH_32Bit:
		ulValue = uiCmd;
		if( ptFlashDev->fPaired!=0 )
		{
			ulValue |= ulValue << 16U;
		}
		((volatile unsigned long*)pbWriteAddr)[ulOffset] = ulValue;
		break;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashWriteCommand()\n"));
}

// ////////////////////////////////////////////////////
//! Checks if a given flag (bCmd) is set on the FLASH device
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector FLASH sector number
//!  \param ulOffset Offset address in the actual FLASH sector
//!  \param bCmd Flag value to be checked
//!  \return TRUE on success
// ////////////////////////////////////////////////////
static int FlashIsset(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulSet, unsigned long ulClear)
{
	int iRet = FALSE;
	volatile unsigned char* pbReadAddr = ptFlashDev->pucFlashBase + ptFlashDev->atSectors[ulSector].ulOffset + ulOffset;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashIsset(): ptFlashDev=0x%08x, ulSector=%d, ulOffset=0x%08x, ulSet=0x%08x, ulClear=0x%08x\n", ptFlashDev, ulSector, ulOffset, ulSet, ulClear));

	switch(ptFlashDev->tBits)
	{
	case BUS_WIDTH_8Bit:
		{
			unsigned char bValue = *pbReadAddr;

			if( ((bValue & ulSet) == ulSet) && ((bValue & ulClear) == 0) )
			{
				iRet = TRUE;
			}
		}
		break;

	case BUS_WIDTH_16Bit:
		{
			unsigned short usValue         = *(volatile unsigned short*)pbReadAddr;
			unsigned short usCheckSetCmd   = ulSet;
			unsigned short usCheckClearCmd = ulClear;

			if(ptFlashDev->fPaired)
			{
				usCheckSetCmd   |= ulSet << 8;
				usCheckClearCmd |= ulClear;
			}

			if( ((usValue & usCheckSetCmd) == usCheckSetCmd) && ((usValue & usCheckClearCmd) == 0) )
			{
				iRet = TRUE;
			}
		}
		break;

	case BUS_WIDTH_32Bit:
		{
			unsigned long ulValue         = *(volatile unsigned long*)pbReadAddr;
			unsigned long ulCheckSetCmd   = ulSet;
			unsigned long ulCheckClearCmd = ulClear;

			if(ptFlashDev->fPaired)
			{
				ulCheckSetCmd   |= ulSet   << 16;
				ulCheckClearCmd |= ulClear << 16;
			}

			if( ((ulValue & ulCheckSetCmd) == ulCheckSetCmd) && ((ulValue & ulCheckClearCmd) == 0) )
			{
				iRet = TRUE;
			}
		}
		break;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashIsset(): iRet=%d\n", iRet));
	return iRet;
}

// ////////////////////////////////////////////////////
//! Waitfs for an erase procedure to finish
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector   FLASH sector number
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashWaitEraseDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
//  volatile unsigned long* pulFlash  = (unsigned long*)(ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset);
	BOOL fRunning = TRUE;
	FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashWaitEraseDone(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));

	do
	{
		/* Check for DQ7 == 1 */
		if(FlashIsset(ptFlashDev, ulSector, 0, DQ7, 0))
		{
			/* Erase success */
			fRunning = FALSE;
		}
		else
		{
			/* Check for DQ5 == 1 and DQ7 == 0 */
			if(FlashIsset(ptFlashDev, ulSector, 0, DQ5, DQ7))
			{
				eRet = eFLASH_DEVICE_FAILED;
				fRunning = FALSE;
			}
		}
	} while(fRunning);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashWaitEraseDone(): eRet=%d\n", eRet));

	return eRet;
}

// ////////////////////////////////////////////////////
//! Checks the state of the flash
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulOffset   Offset to read status from
//!  \param ulOffset   Offset to read status from
//!  \return DEV_NOT_BUSY on success
// ////////////////////////////////////////////////////
static DEVSTATUS FlashGetStatus(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulAddress, BOOL fBufferWriteOp)
{
        unsigned long ulDQ1Mask;
        unsigned long ulDQ2Mask;
	unsigned long ulDQ5Mask;
	unsigned long ulDQ6Mask;
	unsigned long ulDQ6Toggle;
	unsigned long ulRead1;
	unsigned long ulRead2;
	DEVSTATUS tDevStatus;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashGetStatus(): ptFlashDev=0x%08x, ulAddress=0x%08x, fBufferWriteOp=%d\n", ptFlashDev, ulAddress, fBufferWriteOp));

	ulDQ1Mask = (ptFlashDev->fPaired)? (DQ1 | DQ1 << 16U) : DQ1;
	ulDQ2Mask = (ptFlashDev->fPaired)? (DQ2 | DQ2 << 16U) : DQ2;
	ulDQ5Mask = (ptFlashDev->fPaired)? (DQ5 | DQ5 << 16U) : DQ5;
	ulDQ6Mask = (ptFlashDev->fPaired)? (DQ6 | DQ6 << 16U) : DQ6;

	ulRead1 = READ_FLASH(ulAddress);
	ulRead2 = READ_FLASH(ulAddress);

	/* DQ6 toggles ? */
	ulDQ6Toggle = (ulRead1 ^ ulRead2) & ulDQ6Mask;

	if(ulDQ6Toggle)
	{
		/* at least one device's DQ6 toggles */

		/* Checking WriteBuffer Abort condition: only check on the device that has DQ6 toggling */
		/* check only when doing writebuffer operation */
		/* only check DQ1 for devices that toggled DQ6 */
		if(fBufferWriteOp && ((ulDQ6Toggle >> 5) & ulRead2))
		{
			/* read again to make sure WriteBuffer error is correct */
			ulRead1 = READ_FLASH(ulAddress);
			ulRead2 = READ_FLASH(ulAddress);
			ulDQ6Toggle = (ulRead1 ^ ulRead2) & ulDQ6Mask;

			// Don't return WBA if other device DQ6 and DQ1 
			// are not the same. They may still be busy.
			if( (ulDQ6Toggle && ((ulDQ6Toggle >> 5) & ulRead2)) && !((ulDQ6Toggle >> 5) ^ (ulRead2 & ulDQ1Mask)) )
			{
				tDevStatus = DEV_WRITE_BUFFER_ABORT;
			}
			else
			{
				tDevStatus = DEV_BUSY;
			}
		}

		/* Checking Timeout condition: only check on the device that has DQ6 toggling */
		else if( (ulDQ6Toggle >> 1) & ulRead2)
		{
			/* read again to make sure Timeout Error is correct */
			ulRead1 = READ_FLASH(ulAddress);
			ulRead2 = READ_FLASH(ulAddress);
			ulDQ6Toggle = (ulRead1 ^ ulRead2) & ulDQ6Mask;

			// Don't return TimeOut if other device DQ6 and DQ5 
			// are not the same. They may still be busy.
			if((ulDQ6Toggle && ((ulDQ6Toggle >> 1) & ulRead2)) && !( (ulDQ6Toggle >> 1) ^ (ulRead2 & ulDQ5Mask)) )
			{
				tDevStatus = DEV_EXCEEDED_TIME_LIMITS;
			}
			else
			{
				tDevStatus = DEV_BUSY;
			}
		}
		else
		{
			/* No timeout, no WB error */
			tDevStatus = DEV_BUSY;
		}
	}
	else   /* no DQ6 toggles on all devices */
	{
		/* Checking Erase Suspend condition */
		ulRead1 = READ_FLASH(ulAddress);
		ulRead2 = READ_FLASH(ulAddress);

		if( ((ulRead1 ^ ulRead2) & ulDQ2Mask)==ulDQ2Mask )   // All devices DQ2 toggling
		{
			tDevStatus = DEV_SUSPEND;
		}
		else if( ((ulRead1 ^ ulRead2) & ulDQ2Mask) == 0 )   // All devices DQ2 not toggling
		{
			tDevStatus = DEV_NOT_BUSY;
		}
		else
		{
			tDevStatus = DEV_BUSY;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashGetStatus(): tDevStatus=%d\n", tDevStatus));

	return tDevStatus;
}


// ////////////////////////////////////////////////////
//! Waits for a programming procedure to finish
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ulSector      FLASH sector number
//!  \param ulOffset      Last offset written
//!  \param ulOffsetData  Data written to last offset
//!  \param fBufferWrite  TRUE if buffered write is used
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashWaitWriteDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulOffsetData, BOOL fBufferWrite)
{
        DEVSTATUS       dev_status;
        unsigned int    polling_counter;
	unsigned long   ulActData;
	unsigned long   ulBlockAddress;
	FLASH_ERRORS_E  eRet;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashWaitWriteDone(): ptFlashDev=0x%08x, ulSector=%d, ulOffset=0x%08x, ulOffsetData=0x%08x, fBufferWrite=%d\n", ptFlashDev, ulSector, ulOffset, ulOffsetData, fBufferWrite));

	/* delay 4us */
	delay_us(4);

	/* Perform Polling Operation */
	polling_counter = 0xFFFFFFFF;
	ulBlockAddress  = (unsigned long)(ptFlashDev->pucFlashBase + ptFlashDev->atSectors[ulSector].ulOffset + ulOffset);
	do
	{
		polling_counter--;
		dev_status = FlashGetStatus(ptFlashDev, ulBlockAddress, fBufferWrite);
	} while( (dev_status==DEV_BUSY) && polling_counter!=0 );

	/* read the actual data */
	ulActData = READ_FLASH(ulBlockAddress);

	/*
	 * if device returns status other than "not busy" then we
	 *  have a polling error state. 
	 *  NOTE: assumes the "while dev_busy" test above does not change!
	 *
	 * if device was "not busy" then verify polling location.
	 */
	if( dev_status!=DEV_NOT_BUSY )
	{
		if( dev_status==DEV_WRITE_BUFFER_ABORT )
		{
			eRet = eFLASH_ABORTED;
		}
		else 
		{
			eRet = eFLASH_DEVICE_FAILED;
		}
		/* indicate to caller that there was an error */
	}
	else 
	{
		/* Check that polling location verifies correctly */
		if( ulOffsetData==ulActData )
		{
			/* everything is OK */
			eRet = eFLASH_NO_ERROR;
		}
		else 
		{
			eRet = eFLASH_DEVICE_FAILED;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashWaitWriteDone(): eRet=%d\n", eRet));

	return eRet;
}

// ////////////////////////////////////////////////////
//! Writes a sequence of flash commands
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ptCmd         Array of command blocks
//!  \param ulCount       Number of commands
// ////////////////////////////////////////////////////
static void  FlashWriteCommandSequence(const FLASH_DEVICE_T *ptFlashDev, FLASH_COMMAND_BLOCK_T* ptCmd, unsigned long ulCount)
{
	DEBUGMSG(ZONE_FUNCTION, ("+FlashWriteCommandSequence(): ptFlashDev=0x%08x, ptCmd=0x%08x, ulCount=%d\n", ptFlashDev, ptCmd, ulCount));

	while(ulCount>0)
	{
		FlashWriteCommand(ptFlashDev, 0, ptCmd->ulAddress, ptCmd->bCmd);
		++ptCmd;
		--ulCount;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashWriteCommandSequence()\n"));
}

// ///////////////////////////////////////////////////// 
//! \}
// ///////////////////////////////////////////////////// 
