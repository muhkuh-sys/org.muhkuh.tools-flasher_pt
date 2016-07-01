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

	/* NOTE: These defines must match the ZONE_* defines. */
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
#else  /* CFG_DEBUGMSG!=0 */
	#define DEBUGMSG(cond,printf_exp) ((void)0)
#endif /* CFG_DEBUGMSG!=0 */

#define DQ0                                   0x01U
#define DQ1                                   0x02U
#define DQ2                                   0x04U
#define DQ3                                   0x08U
#define DQ4                                   0x10U
#define DQ5                                   0x20U
#define DQ6                                   0x40U
#define DQ7                                   0x80U

#define MFGCODE_SPANSION                      0x01U
#define MFGCODE_EON                           0x7fU
#define MFGCODE_MACRONIX                      0xc2U

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



#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))


typedef enum FLASH_STATUS_ENUM
{
	FLASH_STATUS_Idle        = 0,
	FLASH_STATUS_Busy        = 1,
	FLASH_STATUS_WriteAbort  = 2,
	FLASH_STATUS_TimeOut     = 3,
	FLASH_STATUS_MultipleErrors = 4,    /* A combination of multiple devices shows more than one error. */
} FLASH_STATUS_T;


typedef struct FLASH_COMMAND_BLOCK_Ttag
{
  unsigned long ulAddress;
  unsigned char bCmd;
} FLASH_COMMAND_BLOCK_T;

//static FLASH_ERRORS_E FlashWaitWriteDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulOffsetData, BOOL fBufferWrite);
static void           FlashWriteCommandSequence(const FLASH_DEVICE_T *ptFlashDev, FLASH_COMMAND_BLOCK_T* ptCmd, unsigned long ulCount);
static FLASH_ERRORS_E FlashNormalWrite(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector,      unsigned long ulOffset, const unsigned char* pbData, unsigned long ulWriteSize);

static FLASH_ERRORS_E FlashReset      (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashErase      (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashEraseAll   (const FLASH_DEVICE_T *ptFlashDev);
static FLASH_ERRORS_E FlashProgram    (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData);
static FLASH_ERRORS_E FlashLock       (const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashUnlock     (const FLASH_DEVICE_T *ptFlashDev);
static FLASH_ERRORS_E FlashUnlockDummy(const FLASH_DEVICE_T *ptFlashDev);

static const FLASH_FUNCTIONS_T s_tSpansionFuncs =
{
	FlashReset,
	FlashErase,
	FlashEraseAll,
	FlashProgram,
	FlashLock,
	FlashUnlock
};

static const FLASH_COMMAND_BLOCK_T s_atAutoSelect[] =
{
	{SPANSION_ADR_AUTOSEL_CYCLE0, SPANSION_CMD_AUTOSEL_CYCLE0},
	{SPANSION_ADR_AUTOSEL_CYCLE1, SPANSION_CMD_AUTOSEL_CYCLE1},
	{SPANSION_ADR_AUTOSEL_CYCLE2, SPANSION_CMD_AUTOSEL_CYCLE2},  
};

static const FLASH_COMMAND_BLOCK_T s_atErasePrefix[] =
{
	{SPANSION_ADR_ERASE_CYCLE0, SPANSION_CMD_ERASE_CYCLE0},
	{SPANSION_ADR_ERASE_CYCLE1, SPANSION_CMD_ERASE_CYCLE1},
	{SPANSION_ADR_ERASE_CYCLE2, SPANSION_CMD_ERASE_CYCLE2},
	{SPANSION_ADR_ERASE_CYCLE3, SPANSION_CMD_ERASE_CYCLE3},
	{SPANSION_ADR_ERASE_CYCLE4, SPANSION_CMD_ERASE_CYCLE4},
};

static const FLASH_COMMAND_BLOCK_T s_atPPBEntry[] =
{
	{SPANSION_ADR_PPB_ENTRY_CYCLE0, SPANSION_CMD_PPB_ENTRY_CYCLE0},
	{SPANSION_ADR_PPB_ENTRY_CYCLE1, SPANSION_CMD_PPB_ENTRY_CYCLE1},
	{SPANSION_ADR_PPB_ENTRY_CYCLE2, SPANSION_CMD_PPB_ENTRY_CYCLE2}
};

static const FLASH_COMMAND_BLOCK_T s_atPPBExit[] =
{
	{SPANSION_ADR_PPB_EXIT_CYCLE0, SPANSION_CMD_PPB_EXIT_CYCLE0},
        {SPANSION_ADR_PPB_EXIT_CYCLE1, SPANSION_CMD_PPB_EXIT_CYCLE1}
};


/*-------------------------------------------------------------------------*/


static volatile unsigned char *get_flash_address(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset)
{
	volatile unsigned char *pucAddress;


	pucAddress  = ptFlashDev->pucFlashBase;
	pucAddress += ptFlashDev->atSectors[ulSector].ulOffset;
	pucAddress += ulOffset;

	return pucAddress;
}



static unsigned long read_flash_data(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset)
{
	VADR_T tAddr;
	unsigned long ulValue;


	tAddr.puc = get_flash_address(ptFlashDev, ulSector, ulOffset);
	switch( ptFlashDev->tBits )
	{
	case BUS_WIDTH_8Bit:
		ulValue = (unsigned long)(*(tAddr.puc));
		break;

	case BUS_WIDTH_16Bit:
		ulValue = (unsigned long)(*(tAddr.pus));
		break;

	case BUS_WIDTH_32Bit:
		ulValue = *(tAddr.pul);
		break;
	}

	return ulValue;
}



/*! Write a command to the FLASH
*
*   \param   ptFlashDev  Pointer to the FLASH control Block
*   \param   ulSector    FLASH sector number
*   \param   ulOffset    Offset address in the actual FLASH sector
*   \param   uiCmd       Command to execute
*/
static void FlashWriteCommand(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulCmd)
{
	unsigned char ucValue;
	unsigned short usValue;
	unsigned long ulValue;
	VADR_T tWriteAddr;
	tWriteAddr.puc = get_flash_address(ptFlashDev, ulSector, 0);

	switch(ptFlashDev->tBits)
	{
	case BUS_WIDTH_8Bit:
		/* 8bits cannot be constructed by a combination of flash devices. */
		ucValue = (unsigned char)(ulCmd & 0x000000ffU);
		tWriteAddr.puc[ulOffset] = ucValue;
		break;

	case BUS_WIDTH_16Bit:
		if( ptFlashDev->fPaired==0 )
		{
			usValue = (unsigned short)(ulCmd & 0x0000ffffU);
		}
		else
		{
			usValue  = (unsigned short) (ulCmd & 0x000000ffU);
			usValue |= (unsigned short)((ulCmd & 0x000000ffU) << 8U);
		}
		tWriteAddr.pus[ulOffset] = usValue;
		break;

	case BUS_WIDTH_32Bit:

		if( ptFlashDev->fPaired==0 )
		{
			ulValue = ulCmd;
		}
		else
		{
			ulValue  =  ulCmd & 0x0000ffffU;
			ulValue |= (ulCmd & 0x0000ffffU) << 16U;
		}
		tWriteAddr.pul[ulOffset] = ulValue;
		break;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashWriteCommand()\n"));
}



/*! Wait for all devices to leave the busy state and combine their status.
*
*   \param   ptFlashDev       Pointer to the FLASH control Block
*   \param   ulSector         FLASH sector number
*
*   \return  eFLASH_NO_ERROR  on success
*/
static FLASH_STATUS_T get_combined_status(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, int iAccessIsWriteBufferProgram)
{
	unsigned long aulCombinedStatus[3];
	unsigned long aulSingleStatus[3];
	unsigned int uiDevices; /* This is the number of devices to check. For a paired device it is 2, for a single device it is 1. */
	unsigned long aulMask[4];
	unsigned int auiSrt[4];
	FLASH_STATUS_T atStatus[4];
	unsigned int uiDeviceCnt;
	unsigned int uiCnt;
	unsigned long ulValue;
	unsigned long ulToggle0;
	unsigned long ulToggle1;
	unsigned int uiAllDevicesReady;
	FLASH_STATUS_T tStatus;
	FLASH_STATUS_T tCombinedStatus;


	DEBUGMSG(ZONE_FUNCTION, ("+get_combined_status(): ptFlashDev=0x%08x, ulSector=%d, iAccessIsWriteBufferProgram=%d\n", ptFlashDev, ulSector, iAccessIsWriteBufferProgram));

	/* Set all devices to busy. */
	memset(aulMask, 0, sizeof(aulMask));
	memset(auiSrt, 0, sizeof(auiSrt));
	for(uiCnt=0; uiCnt<(sizeof(atStatus)/sizeof(atStatus[0])); ++uiCnt)
	{
		atStatus[uiCnt] = FLASH_STATUS_Busy;
	}

	/* How many devices must be checked?
	 * FIXME: currently this is limited to 2, so a combination of 4*8bit is not possible.
	 */
	uiDevices = 0;
	switch(ptFlashDev->tBits)
	{
	case BUS_WIDTH_8Bit:
		/* 8 bit can not be paired. */
		uiDevices = 1;
		aulMask[0] = 0x000000ffU;
		auiSrt[0] = 0U;
		break;

	case BUS_WIDTH_16Bit:
		if( ptFlashDev->fPaired==0 )
		{
			/* This is a single 16bit device. */
			uiDevices = 1;
			aulMask[0] = 0x0000ffffU;
			auiSrt[0] = 0U;
		}
		else
		{
			/* This is a combination of 2*8bit devices. */
			uiDevices = 2;
			aulMask[0] = 0x000000ffU;
			auiSrt[0] = 0U;
			aulMask[1] = 0x0000ff00U;
			auiSrt[1] = 8U;
		}
		break;

	case BUS_WIDTH_32Bit:
		if( ptFlashDev->fPaired==0 )
		{
			/* This is a single 32bit device. */
			uiDevices = 1;
			aulMask[0] = 0xffffffffU;
			auiSrt[0] = 0U;
		}
		else
		{
			/* This is a combination of 2*16bit devices. */
			uiDevices = 2;
			aulMask[0] = 0x0000ffffU;
			auiSrt[0] = 0U;
			aulMask[1] = 0xffff0000U;
			auiSrt[1] = 16U;
		}
		break;
	}

	do
	{
		/* Read the combined status 3 times. */
		for(uiCnt=0; uiCnt<3; uiCnt++)
		{
			aulCombinedStatus[uiCnt] = read_flash_data(ptFlashDev, ulSector, ulOffset);
		}

		/* Check if all devices are ready. */
		uiAllDevicesReady = 1;

		/* Loop over all devices. */
		for(uiDeviceCnt=0; uiDeviceCnt<uiDevices; uiDeviceCnt++)
		{
			/* Only check the device if it is not ready yet. */
			if( atStatus[uiDeviceCnt]==FLASH_STATUS_Busy )
			{
				/* At least this device is not ready yet. */
				uiAllDevicesReady = 0;

				/* Extract the 3 status values of the current device. */
				for(uiCnt=0; uiCnt<3; uiCnt++)
				{
					ulValue   = aulCombinedStatus[uiCnt];
					ulValue  &= aulMask[uiDeviceCnt];
					ulValue >>= auiSrt[uiDeviceCnt];
					aulSingleStatus[uiCnt] = ulValue;
				}

				/* Does DQ6 toggle between the reads 0 and 1? */
				ulToggle0  = aulSingleStatus[0];
				ulToggle0 ^= aulSingleStatus[1];
				ulToggle0 &= DQ6;

				/* Does DQ6 toggle between the reads 1 and 2? */
				ulToggle1  = aulSingleStatus[1];
				ulToggle1 ^= aulSingleStatus[2];
				ulToggle1 &= DQ6;

				if( ulToggle0!=0 && ulToggle1!=0 )
				{
					/* Is this a "write buffer program" operation and is DQ1 set in the first read? */
					ulValue  = aulSingleStatus[0];
					ulValue &= DQ5;
					if( iAccessIsWriteBufferProgram!=0 && ulValue!=0 )
					{
						atStatus[uiDeviceCnt] = FLASH_STATUS_WriteAbort;
					}
					else
					{
						/* Is DQ5 set in the first read? */
						ulValue  = aulSingleStatus[0];
						ulValue &= DQ5;
						if( ulValue!=0 )
						{
							atStatus[uiDeviceCnt] = FLASH_STATUS_TimeOut;
						}
					}
				}
				else if( aulSingleStatus[0]==aulSingleStatus[1] && aulSingleStatus[0]==aulSingleStatus[2] )
				{
					/* The flash finished. */
					atStatus[uiDeviceCnt] = FLASH_STATUS_Idle;
				}
			}
		}
	} while( uiAllDevicesReady==0 );

	/* Loop over all status informations. */
	tCombinedStatus = FLASH_STATUS_Idle;
	for(uiDeviceCnt=0; uiDeviceCnt<uiDevices; uiDeviceCnt++)
	{
		tStatus = atStatus[uiDeviceCnt];
		if( tStatus!=FLASH_STATUS_Idle )
		{
			if( tCombinedStatus==FLASH_STATUS_Idle )
			{
				tCombinedStatus = tStatus;
			}
			else if( tCombinedStatus!=tStatus )
			{
				tCombinedStatus = FLASH_STATUS_MultipleErrors;
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-get_combined_status(): tCombinedStatus=%d\n", tCombinedStatus));

	return tCombinedStatus;
}



static FLASH_ERRORS_E FlashWaitForEraseDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
	FLASH_STATUS_T tStatus;
	FLASH_ERRORS_E tResult;


	tStatus = get_combined_status(ptFlashDev, ulSector, 0, 0);
	if( tStatus==FLASH_STATUS_Idle )
	{
		tResult = eFLASH_NO_ERROR;
	}
	else
	{
		tResult = eFLASH_DEVICE_FAILED;
	}

	return tResult;
}



/*! Waits for a programming procedure to finish
*
*   \param   ptFlashDev       Pointer to the FLASH control Block
*   \param   ulSector         FLASH sector number
*   \param   ulOffset         Last offset written
*   \param   ulOffsetData     Data written to last offset
*   \param   fBufferWrite     TRUE if buffered write is used
*
*   \return  eFLASH_NO_ERROR  on success
*/
static FLASH_ERRORS_E FlashWaitForWriteDone(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulOffsetData, BOOL fBufferWrite)
{
	FLASH_STATUS_T tStatus;
	unsigned long   ulActData;
	FLASH_ERRORS_E  eRet;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashWaitForWriteDone(): ptFlashDev=0x%08x, ulSector=%d, ulOffset=0x%08x, ulOffsetData=0x%08x, fBufferWrite=%d\n", ptFlashDev, ulSector, ulOffset, ulOffsetData, fBufferWrite));

	/* delay 4us */
	delay_us(4);

	tStatus = get_combined_status(ptFlashDev, ulSector, ulOffset, fBufferWrite);
	if( tStatus==FLASH_STATUS_Idle )
	{
		/* read the actual data */
		ulActData = read_flash_data(ptFlashDev, ulSector, ulOffset);

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
	else
	{
		eRet = eFLASH_DEVICE_FAILED;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-FlashWaitForWriteDone(): eRet=%d\n", eRet));

	return eRet;
}


/*-------------------------------------------------------------------------*/


/*
Todo: the version check for the primary vendor extension table and the
protect scheme check should be vendor-specific:

Mfg Spansion, Pri < V1.5, bProtectScheme < 5 -> disable unlock procedure
Mfg Eon,      Pri V1.4,   bProtectScheme = 3 -> unlock procedure should probably stay enabled
*/
int SpansionIdentifyFlash(FLASH_DEVICE_T *ptFlashDev)
{
	int fRet = FALSE;
	unsigned char ucManufacturer;
	
	DEBUGMSG(ZONE_FUNCTION, ("+SpansionIdentifyFlash(): ptFlashDev=0x%08x\n", ptFlashDev));

	/* Read manufacturer */
	/* Accept Eon and Macronix flashes and treat them as Spansion flashes */
	FlashReset(ptFlashDev, 0);
	FlashWriteCommandSequence(ptFlashDev, s_atAutoSelect, ARRAYSIZE(s_atAutoSelect));
	ucManufacturer = ptFlashDev->pucFlashBase[0];
	FlashReset(ptFlashDev, 0);
	
	uprintf("Manufacturer: %02x\n", ucManufacturer);
	
	ptFlashDev->ucManufacturer = ucManufacturer;
	
	if(MFGCODE_SPANSION == ucManufacturer)
	{
		strcpy(ptFlashDev->acIdent, "SPANSION");
		memcpy(&(ptFlashDev->tFlashFunctions), &s_tSpansionFuncs, sizeof(FLASH_FUNCTIONS_T));
		fRet = TRUE;
	}
	else if(MFGCODE_EON == ucManufacturer) 
	{
		strcpy(ptFlashDev->acIdent, "EON");
		memcpy(&(ptFlashDev->tFlashFunctions), &s_tSpansionFuncs, sizeof(FLASH_FUNCTIONS_T));
		fRet = TRUE;
	} 
	else if(MFGCODE_MACRONIX == ucManufacturer) 
	{
		strcpy(ptFlashDev->acIdent, "MACRONIX");
		memcpy(&(ptFlashDev->tFlashFunctions), &s_tSpansionFuncs, sizeof(FLASH_FUNCTIONS_T));
		fRet = TRUE;
	}
	
		
	/* If a valid ExtQuery block was read, check its version.
	   If it is a known version, check the sector protect scheme.
	   If the flash does not support software unlocking, 
	   replace the unlock function with a dummy.
	*/
	if ((fRet == TRUE) && ptFlashDev->fPriExtQueryValid)
	{
		CFI_SPANSION_EXTQUERY_T *ptExtQry;
		ptExtQry = &ptFlashDev->tPriExtQuery.tSpansion;
		uprintf(".SpansionIdentifyFlash(): ExtQuery AMD V%c.%c\n", ptExtQry->bMajorVer, ptExtQry->bMinorVer);
		if (ptExtQry->bMajorVer=='1' && ptExtQry->bMinorVer<'5')
		{
			uprintf(".SpansionIdentifyFlash(): Sector protect scheme %d\n", ptExtQry->bProtectScheme);
			if (ptExtQry->bProtectScheme<5) 
			{
				uprintf(".SpansionIdentifyFlash(): Disabling unlock\n"); 
				ptFlashDev->tFlashFunctions.pfnUnlock = FlashUnlockDummy;
			}
			else
			{
				uprintf(".SpansionIdentifyFlash(): Enabling unlock\n"); 
				ptFlashDev->tFlashFunctions.pfnUnlock = FlashUnlock;
			}
		}
	}
	
	DEBUGMSG(ZONE_FUNCTION, ("-SpansionIdentifyFlash(): fRet=%d\n", fRet));
	return fRet;
}



/*! Reset the flash sector to read mode
*
*  \param   ptFlashDev        Pointer to the FLASH control Block
*  \param   ulSector          Sector to reset to read mode
*
*  \return  eFLASH_NO_ERROR   on success
*/
static FLASH_ERRORS_E FlashReset(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector __attribute__((unused)))
{
	FLASH_ERRORS_E tResult;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashReset(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));

	FlashWriteCommand(ptFlashDev, 0, 0, SPANSION_CMD_RESET);
	tResult = eFLASH_NO_ERROR;

	DEBUGMSG(ZONE_FUNCTION, ("-FlashReset(): tResult=%d\n", tResult));
	return tResult;
}

/*! Erase a flash sector
*
*   \param   ptFlashDev       Pointer to the FLASH control Block
*   \param   ulSector         Sector to erase
*
*   \return  eFLASH_NO_ERROR  on success
*/
static FLASH_ERRORS_E FlashErase(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
	FLASH_ERRORS_E tResult = eFLASH_NO_ERROR;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashErase(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));
	FlashWriteCommandSequence(ptFlashDev, s_atErasePrefix, ARRAYSIZE(s_atErasePrefix));
	FlashWriteCommand(ptFlashDev, ulSector, 0, SPANSION_CMD_SECTORERASE_CYCLE_5);
	tResult = FlashWaitForEraseDone(ptFlashDev, ulSector);

	FlashReset(ptFlashDev, ulSector);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashErase(): tResult=%d\n", tResult));
	return tResult;
}

/*! Erase whole flash
*
*   \param   ptFlashDev       Pointer to the FLASH control Block
*
*   \return  eFLASH_NO_ERROR  on success
*/
static FLASH_ERRORS_E FlashEraseAll(const FLASH_DEVICE_T *ptFlashDev)
{
	FLASH_ERRORS_E tResult = eFLASH_NO_ERROR;

	DEBUGMSG(ZONE_FUNCTION, ("+FlashEraseAll(): ptFlashDev=0x%08x\n", ptFlashDev));

	FlashWriteCommandSequence(ptFlashDev, s_atErasePrefix, ARRAYSIZE(s_atErasePrefix));
	FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_CHIPERASE_CYCLE5, SPANSION_CMD_CHIPERASE_CYCLE5);

	tResult = FlashWaitForEraseDone(ptFlashDev, 0);

	FlashReset(ptFlashDev, 0);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashEraseAll(): tResult=%d\n", tResult));

	return tResult;
}


/*! Programs flash using single byte/word/dword accesses
*
*   \param   ptFlashDev       Pointer to the FLASH control Block
*   \param   ulStartOffset    Offset to start writing at
*   \param   ulLength         Length of data to write
*   \param   pvData           Data pointer
*
*   \return  eFLASH_NO_ERROR  on success
*/

static FLASH_ERRORS_E FlashNormalWrite(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, const unsigned char *pucData, unsigned long ulWriteSize)
{
	FLASH_ERRORS_E  eRet       = eFLASH_NO_ERROR;
	CADR_T tSrc;
	VADR_T tDst;
	unsigned long ulLastData;
	unsigned long ulLastOffset;
	unsigned long ulEndOffset;
	
	DEBUGMSG(ZONE_FUNCTION, ("+FlashNormalWrite(): ptFlashDev=0x%08x, ulSector=%d, ulOffset=0x%08x, pucData=0x%08x, ulWriteSize=0x%08x\n", ptFlashDev, ulSector, ulOffset, pucData, ulWriteSize));

	tSrc.puc = pucData;
	tDst.puc = get_flash_address(ptFlashDev, ulSector, ulOffset);
	ulEndOffset  = ulOffset + ulWriteSize;
	ulLastData   = 0;
	
	while(ulOffset < ulEndOffset)
	{
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE0, SPANSION_CMD_PROGRAM_CYCLE0);
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE1, SPANSION_CMD_PROGRAM_CYCLE1);
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE2, SPANSION_CMD_PROGRAM_CYCLE2);
		
		ulLastOffset = ulOffset;
		
		switch(ptFlashDev->tBits)
		{
		case BUS_WIDTH_8Bit:
			*tDst.puc = *tSrc.puc;
			ulLastData = *tSrc.puc;
			ulOffset+=1;
			++tDst.puc;
			++tSrc.puc;
			break;
		case BUS_WIDTH_16Bit:
			*tDst.pus = *tSrc.pus;
			ulLastData = *tSrc.pus;
			ulOffset+=2;
			++tDst.pus;
			++tSrc.pus;
			break;
		case BUS_WIDTH_32Bit:
			*tDst.pul = *tSrc.pul;
			ulLastData = *tSrc.pul;
			ulOffset+=4;
			++tDst.pul;
			++tSrc.pul;
			break;
		}
		
		eRet = FlashWaitForWriteDone(ptFlashDev, ulSector, ulLastOffset, ulLastData, FALSE);
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

		DEBUGMSG(ZONE_FUNCTION, (". ulWriteSize = 0x%08x \n", ulWriteSize)); // sl
		
		/* Convert the byte counter to the number of elements to write. */
		uiWriteElements  = ulWriteSize >> ptFlashDev->tBits;
		uiWriteElements -= 1;

		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITE_CYCLE0, SPANSION_CMD_BUFFERWRITE_CYCLE0);
		FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITE_CYCLE1, SPANSION_CMD_BUFFERWRITE_CYCLE1);
		FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, SPANSION_CMD_BUFFERWRITE_CYCLE2);    
		FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, uiWriteElements);

		ulLength -= ulWriteSize;

		tDst.puc = get_flash_address(ptFlashDev, ulCurrentSector, ulCurrentOffset);
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
			ulLastOffset = ulCurrentOffset - sizeof(unsigned char);
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
			ulLastOffset = ulCurrentOffset - sizeof(unsigned short);
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
			ulLastOffset = ulCurrentOffset - sizeof(unsigned long);
			/* Get the last data. */
			ulLastData = *(tSrc.pul-1);
			break;
			
			
		default:
			DEBUGMSG(ZONE_ERROR, ("!FlashBufferedWrite(): invalid bus width %d\n", ptFlashDev->tBits));
			tResult = eFLASH_INVALID_PARAMETER;
			break;
		}

		if(tResult!=eFLASH_NO_ERROR)
		{
			break;
		}
		
		FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, SPANSION_CMD_BUFFERPROG);

		/* Wait for Flashing complete */
		tResult = FlashWaitForWriteDone(ptFlashDev, ulCurrentSector, ulLastOffset, ulLastData, TRUE);
		
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


/*! Program flash (uses buffered writes whenever possible)
*
*  \param   ptFlashDev       Pointer to the FLASH control Block
*  \param   ulStartOffset    Offset to start writing at
*  \param   ulLength         Length of data to write
*  \param   pvData           Data pointer
*
*  \return  eFLASH_NO_ERROR  on success
*/
static FLASH_ERRORS_E FlashProgram(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void *pvData)
{
	unsigned long  ulCurrentSector;
	unsigned long  ulCurrentOffset;
	const unsigned char *pucSource;
	unsigned long ulDeviceBufferSize;
	unsigned long ulOffsetMod;
	FLASH_ERRORS_E tResult;


	DEBUGMSG(ZONE_FUNCTION, ("+FlashProgram(): ptFlashDev=0x%08x, ulStartOffset=0x%08x, ulLength=0x%08x, pvData=0x%08x\n", ptFlashDev, ulStartOffset, ulLength, pvData));

	/* Be optimistic. */
	tResult = eFLASH_NO_ERROR;

	pucSource = (const unsigned char*)pvData;

	/* Determine the start sector and offset inside the sector */
	ulCurrentSector = cfi_find_matching_sector_index(ptFlashDev, ulStartOffset);
	ulCurrentOffset = ulStartOffset - ptFlashDev->atSectors[ulCurrentSector].ulOffset;
	
	FlashReset(ptFlashDev, 0);

	if( ulCurrentSector==0xffffffffU )
	{
		tResult = eFLASH_INVALID_PARAMETER;
	}
	else if( ulStartOffset+ulLength>ptFlashDev->ulFlashSize )
	{
		tResult = eFLASH_INVALID_PARAMETER;
	}
	else if (ptFlashDev->ulMaxBufferWriteSize == 1) 
	{
		/* if the device does not support buffered writes, write the entire data normally */
		DEBUGMSG(ZONE_VERBOSE, (".FlashProgram(): using normal writes\n"));
		tResult = FlashNormalWrite(ptFlashDev, ulCurrentSector, ulCurrentOffset, pucSource, ulLength);
	}
	else
	{
		/* check if the offset is aligned to the write buffer size (a power of 2) */
		ulDeviceBufferSize = ptFlashDev->ulMaxBufferWriteSize;
		ulOffsetMod = ulCurrentOffset & (ulDeviceBufferSize - 1);

		DEBUGMSG(ZONE_VERBOSE, (". ulDeviceBufferSize = 0x%08x\n", ulDeviceBufferSize));
		DEBUGMSG(ZONE_VERBOSE, (". ulOffsetMod        = 0x%08x\n", ulOffsetMod));
		
		if( ulOffsetMod!=0 )
		{
			/* get the maximum size for the normal write operation (only write until buffered write can be used) */
			unsigned long ulUnbufferedWriteSize = ulDeviceBufferSize - ulOffsetMod;
			DEBUGMSG(ZONE_VERBOSE, (". ulUnbufferedWriteSize = 0x%08x\n", ulUnbufferedWriteSize));
			
			/* limit the write size to the requested chunk */
			if( ulUnbufferedWriteSize>ulLength )
			{
				ulUnbufferedWriteSize = ulLength;
				DEBUGMSG(ZONE_VERBOSE, (". ulUnbufferedWriteSize adjusted to 0x%08x\n", ulUnbufferedWriteSize));
			}
			tResult = FlashNormalWrite(ptFlashDev, ulCurrentSector, ulCurrentOffset, pucSource, ulUnbufferedWriteSize);
			if(tResult==eFLASH_NO_ERROR)
			{
				ulCurrentOffset += ulUnbufferedWriteSize;
				pucSource       += ulUnbufferedWriteSize;
				ulLength        -= ulUnbufferedWriteSize;

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


FLASH_ERRORS_E FlashLock(const FLASH_DEVICE_T *ptFlashDev __attribute__((unused)), unsigned long ulSector __attribute__((unused)))
{
	FLASH_ERRORS_E tResult;
	DEBUGMSG(ZONE_FUNCTION, ("+FlashLock(): ptFlashDev=0x%08x, ulSector=%d\n", ptFlashDev, ulSector));

	/* not yet */
	tResult = eFLASH_INVALID_PARAMETER;

	DEBUGMSG(ZONE_FUNCTION, ("-FlashProgram(): tResult=%d\n", tResult));

	return tResult;
}

FLASH_ERRORS_E FlashUnlockDummy(const FLASH_DEVICE_T *ptFlashDev __attribute__((unused)))
{
	uprintf(".FlashUnlockDummy(): Unlock not supported\n");
	return eFLASH_NO_ERROR;
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
			uprintf(". sector %d is protected\n", ulSector);
		}
		ulNotProtected &= ulProtectionBit;

		/* next sector */
		++ulSector;
	}

	/* clear protection if at least one sector is protected */
	if( ulNotProtected==0 )
	{
		uprintf(". unlocking all sectors...\n");
		/* the sector is protected */
		FlashWriteCommand(ptFlashDev, SPANSION_ADR_PPB_CLEARALL_CYCLE0, 0, SPANSION_CMD_PPB_CLEARALL_CYCLE0);
		FlashWriteCommand(ptFlashDev, SPANSION_ADR_PPB_CLEARALL_CYCLE1, 0, SPANSION_CMD_PPB_CLEARALL_CYCLE1);

		/* wait for unlock done */
		eRet = FlashWaitForEraseDone(ptFlashDev, 0);
	}
	else
	{
		uprintf(". Ok, no locked sectors found.\n");
	}

	/* leave ppb mode */
	FlashWriteCommandSequence(ptFlashDev, s_atPPBExit, sizeof(s_atPPBExit) / sizeof(s_atPPBExit[0]));

	/* back to memory mode */
	FlashReset(ptFlashDev, ulSector);

	DEBUGMSG(ZONE_FUNCTION, ("-FlashUnlock(): eRet=%d\n", eRet));

	/* done */
	return eRet;
}


#if 0
/*! Checks the state of the flash
*
*   \param   ptFlashDev    Pointer to the FLASH control Block
*   \param   ulOffset      Offset to read status from
*   \param   ulOffset      Offset to read status from
*
*   \return  DEV_NOT_BUSY  on success
*/
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

			/* Don't return WBA if other device DQ6 and DQ1 
			   are not the same. They may still be busy. */
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

			/* Don't return TimeOut if other device DQ6 and DQ5 
			   are not the same. They may still be busy. */
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

		if( ((ulRead1 ^ ulRead2) & ulDQ2Mask)==ulDQ2Mask )   /* All devices DQ2 toggling. */
		{
			tDevStatus = DEV_SUSPEND;
		}
		else if( ((ulRead1 ^ ulRead2) & ulDQ2Mask) == 0 )   /* All devices DQ2 not toggling. */
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
#endif



/*! Writes a sequence of flash commands
*
*   \param   ptFlashDev    Pointer to the FLASH control Block
*   \param   ptCmd         Array of command blocks
*   \param   ulCount       Number of commands
*/
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

