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

// ///////////////////////////////////////////////////// 
//! \file parallelflash.c
//!  Provides the physical driver functions for Parallel FLASH handling (Intel)
// ////////////////////////////////////////////////////

// ///////////////////////////////////////////////////// 
//! \addtogroup EBOOT_FLASH
//! \{
// ///////////////////////////////////////////////////// 

#include "spansion.h"
#include <string.h>
#include "delay.h"
#include "uprintf.h"


#define READ_USHORT(ulAddress)   (*(volatile unsigned short*)ulAddress)
#define READ_ULONG(ulAddress)    (*(volatile unsigned long*)ulAddress)

#define READ_FLASH(ulAddress)    ((ptFlashDev->fPaired)? READ_ULONG(ulAddress) : READ_USHORT(ulAddress))

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

static FLASH_ERRORS_E FlashWaitEraseDone(FLASH_DEVICE *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashWaitWriteDone(FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulOffsetData, BOOL fBufferWrite);
static int            FlashIsset        (FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulSet, unsigned long ulClear);
static void           FlashWriteCommand (FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned int uiCmd);
static void           FlashWriteCommandSequence(FLASH_DEVICE *ptFlashDev, FLASH_COMMAND_BLOCK_T* ptCmd, unsigned long ulCount);

static FLASH_ERRORS_E FlashReset      (FLASH_DEVICE *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashErase      (FLASH_DEVICE *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashEraseAll   (FLASH_DEVICE *ptFlashDev);
static FLASH_ERRORS_E FlashProgram    (FLASH_DEVICE *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData);
static FLASH_ERRORS_E FlashNormalWrite(FLASH_DEVICE *ptFlashDev, unsigned long ulSector,      unsigned long ulOffset, const unsigned char* pbData, unsigned long ulWriteSize);
static FLASH_ERRORS_E FlashLock       (FLASH_DEVICE *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashUnlock     (FLASH_DEVICE *ptFlashDev);

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

int SpansionIdentifyFlash(FLASH_DEVICE *ptFlashDev)
{
  unsigned char abDeviceId[3] = {0};
  int           fRet          = FALSE;

  /* try to identify SpansionFlash */
  FlashWriteCommandSequence(ptFlashDev, 
                            s_atAutoSelect, 
                            sizeof(s_atAutoSelect) / sizeof(s_atAutoSelect[0]));

  ptFlashDev->bManufacturer = ptFlashDev->pbFlashBase[0];

  abDeviceId[0] = ptFlashDev->pbFlashBase[2];
  abDeviceId[1] = ptFlashDev->pbFlashBase[2];
  abDeviceId[2] = ptFlashDev->pbFlashBase[2]; 

  FlashReset(ptFlashDev, 0);

  if(MFGCODE_SPANSION == ptFlashDev->bManufacturer)
  {
    /* TODO: Check Device IDs */

    strcpy(ptFlashDev->szIdent, "SPANSION");
    ptFlashDev->ptFlashFuncs = &s_tSpansionFuncs;
    fRet = TRUE;
  }

  return fRet;
}

// ////////////////////////////////////////////////////
//! Reset the flash sector to read mode
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \param ulSector    Sector to reset to read mode
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashReset(FLASH_DEVICE *ptFlashDev, unsigned long ulSector)
{
  FlashWriteCommand(ptFlashDev, 0, 0, SPANSION_CMD_RESET);

  return eFLASH_NO_ERROR;
}

// ////////////////////////////////////////////////////
//! Erase a flash sector
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \param ulSector    Sector to erase
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashErase(FLASH_DEVICE *ptFlashDev, unsigned long ulSector)
{
  FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;

  FlashWriteCommandSequence(ptFlashDev, 
                            s_atErasePrefix, 
                            sizeof(s_atErasePrefix) / sizeof(s_atErasePrefix[0]));

  FlashWriteCommand(ptFlashDev, ulSector, 0, SPANSION_CMD_SECTORERASE_CYCLE_5);

  eRet = FlashWaitEraseDone(ptFlashDev, ulSector);

  FlashReset(ptFlashDev, ulSector);

  return eRet;
}

// ////////////////////////////////////////////////////
//! Erase whole flash
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashEraseAll(FLASH_DEVICE *ptFlashDev)
{
  FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;

  FlashWriteCommandSequence(ptFlashDev, 
                            s_atErasePrefix, 
                            sizeof(s_atErasePrefix) / sizeof(s_atErasePrefix[0]));

  FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_CHIPERASE_CYCLE5, SPANSION_CMD_CHIPERASE_CYCLE5);

  eRet = FlashWaitEraseDone(ptFlashDev, 0);

  FlashReset(ptFlashDev, 0);

  return eRet;
}

// ////////////////////////////////////////////////////
//! Programs flash using single word/dword accesses
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ulStartOffset Offset to start writing at
//!  \param ulLength      Length of data to write
//!  \param pvData        Data pointer
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashNormalWrite(FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, const unsigned char* pbData, unsigned long ulWriteSize)
{
  FLASH_ERRORS_E  eRet       = eFLASH_NO_ERROR;
  unsigned long   ulBusWidth = ptFlashDev->fPaired? sizeof(unsigned long) : sizeof(unsigned short);
  unsigned long   ulIdx      = 0;

  /* TODO: Think about unlock bypass mode programming which is faster for single word/dword writes */

  for(ulIdx = 0; ulIdx < ulWriteSize / ulBusWidth; ulIdx++)
  {
    ULONG ulLastData = 0;

    FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE0, SPANSION_CMD_PROGRAM_CYCLE0);
    FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE1, SPANSION_CMD_PROGRAM_CYCLE1);
    FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_PROGRAM_CYCLE2, SPANSION_CMD_PROGRAM_CYCLE2);

    if(ptFlashDev->fPaired)
    {
      const unsigned long*    pulBuffer = (const unsigned long*)pbData;
      volatile unsigned long* pulFlash  = (volatile unsigned long*)(ptFlashDev->pbFlashBase + ulOffset);
      ulLastData      = pulBuffer[ulIdx];
      pulFlash[ulIdx] = pulBuffer[ulIdx];
    }
    else 
    {
      const unsigned short*    pusBuffer = (const unsigned short*)pbData;
      volatile unsigned short* pusFlash  = (volatile unsigned short*)(ptFlashDev->pbFlashBase + ulOffset);
      ulLastData      = pusBuffer[ulIdx];
      pusFlash[ulIdx] = pusBuffer[ulIdx];
    }

    if(eFLASH_NO_ERROR != (eRet = FlashWaitWriteDone(ptFlashDev, ulSector, ulOffset + ulIdx * ulBusWidth, ulLastData, FALSE)))
    {
      FlashWriteCommand(ptFlashDev, ulSector, 0, SPANSION_CMD_RESET);
      break;
    }
  }

  return eRet;
}


// ////////////////////////////////////////////////////
//! Program flash (uses buffered writes whenever possible)
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ulStartOffset Offset to start writing at
//!  \param ulLength      Length of data to write
//!  \param pvData        Data pointer
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashProgram(FLASH_DEVICE *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData)
{
  unsigned long  ulCurrentSector  = 0;
  unsigned long  ulCurrentOffset  = ulStartOffset; 
//  unsigned long  ulBufferWriteCnt = 0;
  const unsigned char* pbSource   = (const unsigned char*)pvData;
  unsigned long  ulCnt            = 0;
  BOOL           fFound           = FALSE;
  FLASH_ERRORS_E eRet             = eFLASH_NO_ERROR;

  /* Determine the start sector and offset inside the sector */
  for(ulCnt = 0; ulCnt < ptFlashDev->ulSectorCnt; ++ulCnt)
  {
    if(ulCurrentOffset < ptFlashDev->atSectors[ulCnt].ulSize)
    {
      ulCurrentSector = ulCnt;
      fFound          = TRUE;
      break;
    }

    ulCurrentOffset -= ptFlashDev->atSectors[ulCnt].ulSize;
  }

  if( (!fFound) ||
      (ptFlashDev->ulFlashSize < (ulStartOffset + ulLength)) )
    return eFLASH_INVALID_PARAMETER;

  FlashReset(ptFlashDev, 0);

  /* Check if address if on a page boundary page size is 8words/16bytes */
  if(ulCurrentOffset & 0xF)
  {
    unsigned short usWriteSize;

    /* get the maximum size for the normal write operation (only write until buffered write can be used) */
    usWriteSize = (USHORT)(16 - (ulCurrentOffset & 0xF));
    /* limit the write size to the requested chunk */
    if( usWriteSize>ulLength )
    {
      usWriteSize = ulLength;
    }
    eRet = FlashNormalWrite(ptFlashDev, ulCurrentSector, ulCurrentOffset, pbSource, usWriteSize);
    if(eFLASH_NO_ERROR != eRet)
    {
      return eRet;
    }

    ulCurrentOffset += usWriteSize;
    pbSource        += usWriteSize;
    ulLength        -= usWriteSize;

    /* Check for new sector wraparound */
    if(ulCurrentOffset >= ptFlashDev->atSectors[ulCurrentSector].ulSize)
    {
      ulCurrentOffset = ptFlashDev->atSectors[ulCurrentSector].ulSize - ulCurrentOffset;
      ++ulCurrentSector;
    }
  }

  while(ulLength > 0)
  {
    unsigned long ulWriteSize    = 0; //Bufferwrite size this run
    unsigned char bWriteCountCmd = 0;
    unsigned long ulMaxBuffer    = ptFlashDev->ulMaxBufferWriteSize;

    unsigned long ulLastData     = 0;
    unsigned long ulLastOffset   = 0;

    if(ptFlashDev->fPaired)
      ulMaxBuffer *= 2;

    if(ulLength > ulMaxBuffer)
      ulWriteSize = ulMaxBuffer;
    else
      ulWriteSize = ulLength;

    /* Adjust write size, til end of sector */
    if((ulCurrentOffset + ulWriteSize) > ptFlashDev->atSectors[ulCurrentSector].ulSize)
    {
      ulWriteSize = ptFlashDev->atSectors[ulCurrentSector].ulSize - ulCurrentOffset;
    }

    switch(ptFlashDev->uiWidth)
    {
    case 8:
      bWriteCountCmd = (unsigned char)(ulWriteSize - 1);
      break;

    case 16:
      bWriteCountCmd = (unsigned char)(ulWriteSize / 2 - 1);
      break;

    case 32:
      bWriteCountCmd = (unsigned char)(ulWriteSize / 4 - 1);
      break;
    }

    FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITE_CYCLE0, SPANSION_CMD_BUFFERWRITE_CYCLE0);
    FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITE_CYCLE1, SPANSION_CMD_BUFFERWRITE_CYCLE1);
    FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, SPANSION_CMD_BUFFERWRITE_CYCLE2);    
    FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, bWriteCountCmd);

    ulLength -= ulWriteSize;

    while(ulWriteSize != 0)
    {
      volatile unsigned char* pbWriteAddr = ptFlashDev->pbFlashBase + 
                                   ptFlashDev->atSectors[ulCurrentSector].ulOffset + 
                                   ulCurrentOffset;

      ulLastOffset = ulCurrentOffset;

      switch(ptFlashDev->uiWidth)
      {
      case 8:
        ulLastData = *pbSource;
        *pbWriteAddr = *pbSource++;
        ++ulCurrentOffset;
        --ulWriteSize;
        break;

      case 16:
        *(volatile unsigned short*)pbWriteAddr = *(volatile unsigned short*)pbSource;
        ulLastData = *(unsigned short*)pbSource;

        pbSource += 2;
        ulCurrentOffset += 2;
        ulWriteSize -= 2;
        break;

      case 32:
        *(volatile unsigned long*)pbWriteAddr = *(volatile unsigned long*)pbSource;
        ulLastData = *(unsigned long*)pbSource;
        pbSource += 4;
        ulCurrentOffset += 4;
        ulWriteSize -= 4;
        break;
      }
    }

    FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, SPANSION_CMD_BUFFERPROG);

    /* Wait for Flashing complete */
    if(eFLASH_NO_ERROR != (eRet = FlashWaitWriteDone(ptFlashDev, ulCurrentSector, ulLastOffset, ulLastData, TRUE)))
    {
      if(eRet == eFLASH_ABORTED)
      {
        FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITEABORT_CYCLE0, SPANSION_CMD_BUFFERWRITEABORT_CYCLE0);
        FlashWriteCommand(ptFlashDev, ulCurrentSector, ulLastOffset, SPANSION_CMD_BUFFERWRITEABORT_CYCLE1);
        FlashWriteCommand(ptFlashDev, 0, SPANSION_ADR_BUFFERWRITEABORT_CYCLE2, SPANSION_CMD_BUFFERWRITEABORT_CYCLE2);

      } else if(eRet == eFLASH_DEVICE_FAILED)
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

  FlashReset(ptFlashDev, 0);

  return eRet;
}


FLASH_ERRORS_E FlashLock(FLASH_DEVICE *ptFlashDev, unsigned long ulSector)
{
	/* not yet */
	return eFLASH_INVALID_PARAMETER;
}


FLASH_ERRORS_E FlashUnlock(FLASH_DEVICE *ptFlashDev)
{
	unsigned long ulNotProtected;
	unsigned long ulProtectionBit;
	unsigned long ulSector;
	FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;
	volatile unsigned char* pbReadAddr;


	/* default is unprotected */
	ulNotProtected = 1;

	/* enter ppb mode */
	FlashWriteCommandSequence(ptFlashDev, s_atPPBEntry, sizeof(s_atPPBEntry) / sizeof(s_atPPBEntry[0]));

	/* loop over all sectors and check if they are protected */
	ulSector = 0;
	while( ulSector<ptFlashDev->ulSectorCnt )
	{
		/* get sector address */
		pbReadAddr = ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset;
		
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

		/* wait for erase done */
		eRet = FlashWaitEraseDone(ptFlashDev, 0);
	}

	/* leave ppb mode */
	FlashWriteCommandSequence(ptFlashDev, s_atPPBExit, sizeof(s_atPPBExit) / sizeof(s_atPPBExit[0]));

	/* back to memory mode */
	FlashReset(ptFlashDev, ulSector);

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
void FlashWriteCommand(FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned int uiCmd)
{
        volatile unsigned char* pbWriteAddr = ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset;
        unsigned long ulValue;


        switch(ptFlashDev->uiWidth)
        {
        case 8:
                /* 8bits cannot be paired */
                pbWriteAddr[ulOffset] = (unsigned char)uiCmd;
                break;

        case 16:
                ulValue = uiCmd;
                if( ptFlashDev->fPaired!=0 )
                {
                        ulValue |= ulValue << 8U;
                }
                ((volatile unsigned short*)pbWriteAddr)[ulOffset] = (unsigned short)ulValue;
                break;

        case 32:
                ulValue = uiCmd;
                if( ptFlashDev->fPaired!=0 )
                {
                        ulValue |= ulValue << 16U;
                }
                ((volatile unsigned long*)pbWriteAddr)[ulOffset] = ulValue;
                break;
  }
}

// ////////////////////////////////////////////////////
//! Checks if a given flag (bCmd) is set on the FLASH device
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector FLASH sector number
//!  \param ulOffset Offset address in the actual FLASH sector
//!  \param bCmd Flag value to be checked
//!  \return TRUE on success
// ////////////////////////////////////////////////////
static int FlashIsset(FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulSet, unsigned long ulClear)
{
  int            iRet       = FALSE;
  volatile unsigned char* pbReadAddr = ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset + ulOffset;

  switch(ptFlashDev->uiWidth)
  {
  case 8:
    {
      unsigned char bValue = *pbReadAddr;

      if( ((bValue & ulSet) == ulSet) &&
          ((bValue & ulClear) == 0) )
        iRet = TRUE;
    }
    break;

  case 16:
    {
      unsigned short usValue         = *(volatile unsigned short*)pbReadAddr;
      unsigned short usCheckSetCmd   = ulSet;
      unsigned short usCheckClearCmd = ulClear;

      if(ptFlashDev->fPaired)
      {
        usCheckSetCmd   |= ulSet << 8;
        usCheckClearCmd |= ulClear;
      }

      if( ((usValue & usCheckSetCmd) == usCheckSetCmd) &&
          ((usValue & usCheckClearCmd) == 0) )
        iRet = TRUE;
    }
    break;

  case 32:
    {
      unsigned long ulValue         = *(volatile unsigned long*)pbReadAddr;
      unsigned long ulCheckSetCmd   = ulSet;
      unsigned long ulCheckClearCmd = ulClear;

      if(ptFlashDev->fPaired)
      {
        ulCheckSetCmd   |= ulSet   << 16;
        ulCheckClearCmd |= ulClear << 16;
      }

      if( ((ulValue & ulCheckSetCmd) == ulCheckSetCmd) &&
          ((ulValue & ulCheckClearCmd) == 0) )
        iRet = TRUE;
    }
    break;
  }

  return iRet;
}

// ////////////////////////////////////////////////////
//! Waitfs for an erase procedure to finish
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector   FLASH sector number
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashWaitEraseDone(FLASH_DEVICE *ptFlashDev, unsigned long ulSector)
{
//  volatile unsigned long* pulFlash  = (unsigned long*)(ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset);
  BOOL                    fRunning  = TRUE;
  FLASH_ERRORS_E          eRet      = eFLASH_NO_ERROR;

  do
  {
    /* Check for DQ7 == 1 */
    if(FlashIsset(ptFlashDev, ulSector, 0, DQ7, 0))
    {
      /* Erase success */
      fRunning = FALSE;
    } else
    {
      /* Check for DQ5 == 1 and DQ7 == 0 */
      if(FlashIsset(ptFlashDev, ulSector, 0, DQ5, DQ7))
      {
        eRet = eFLASH_DEVICE_FAILED;
        fRunning = FALSE;
      }
    }
  } while(fRunning);

  return eRet;
}

// ////////////////////////////////////////////////////
//! Checks the state of the flash
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulOffset   Offset to read status from
//!  \param ulOffset   Offset to read status from
//!  \return DEV_NOT_BUSY on success
// ////////////////////////////////////////////////////
static DEVSTATUS FlashGetStatus(FLASH_DEVICE *ptFlashDev, unsigned long ulAddress, BOOL fBufferWriteOp)
{
  unsigned long ulDQ1Mask   = (ptFlashDev->fPaired)? (DQ1 | DQ1 << 16U) : DQ1;
  unsigned long ulDQ2Mask   = (ptFlashDev->fPaired)? (DQ2 | DQ2 << 16U) : DQ2;
//  unsigned long ulDQ3Mask   = (ptFlashDev->fPaired)? (DQ3 | DQ3 << 16) : DQ3;
//  unsigned long ulDQ4Mask   = (ptFlashDev->fPaired)? (DQ4 | DQ4 << 16) : DQ4;
  unsigned long ulDQ5Mask   = (ptFlashDev->fPaired)? (DQ5 | DQ5 << 16U) : DQ5;
  unsigned long ulDQ6Mask   = (ptFlashDev->fPaired)? (DQ6 | DQ6 << 16U) : DQ6;

  unsigned long ulDQ6Toggle = 0;

  unsigned long ulRead1 = READ_FLASH(ulAddress);
  unsigned long ulRead2 = READ_FLASH(ulAddress);

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
      if ((ulDQ6Toggle && ((ulDQ6Toggle >> 5) & ulRead2)) &&
          !((ulDQ6Toggle >> 5) ^ (ulRead2 & ulDQ1Mask))) 
        return DEV_WRITE_BUFFER_ABORT;
      else
        return DEV_BUSY;
    }

    /* Checking Timeout condition: only check on the device that has DQ6 toggling */
    if( (ulDQ6Toggle >> 1) & ulRead2)
    {
      /* read again to make sure Timeout Error is correct */
      ulRead1 = READ_FLASH(ulAddress);
      ulRead2 = READ_FLASH(ulAddress);
      ulDQ6Toggle = (ulRead1 ^ ulRead2) & ulDQ6Mask;

      // Don't return TimeOut if other device DQ6 and DQ5 
      // are not the same. They may still be busy.
      if ((ulDQ6Toggle && ((ulDQ6Toggle >> 1) & ulRead2)) &&
          !( (ulDQ6Toggle >> 1) ^ (ulRead2 & ulDQ5Mask))) 
         return DEV_EXCEEDED_TIME_LIMITS;
      else
         return DEV_BUSY;
    }

    /* No timeout, no WB error */
    return DEV_BUSY;
  }
  else   /* no DQ6 toggles on all devices */
  {
    /* Checking Erase Suspend condition */
    ulRead1 = READ_FLASH(ulAddress);
    ulRead2 = READ_FLASH(ulAddress);

    if (((ulRead1 ^ ulRead2) & ulDQ2Mask) == ulDQ2Mask)   // All devices DQ2 toggling
      return DEV_SUSPEND;
    else if(((ulRead1 ^ ulRead2) & ulDQ2Mask) == 0)   // All devices DQ2 not toggling
       return DEV_NOT_BUSY;
    else
       return DEV_BUSY;
  }
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
static FLASH_ERRORS_E FlashWaitWriteDone(FLASH_DEVICE *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulOffsetData, BOOL fBufferWrite)
{
  DEVSTATUS       dev_status;
  unsigned int    polling_counter = 0xFFFFFFFF;
  unsigned long   ulActData       = 0;
  unsigned long   ulBlockAddress  = (unsigned long)(ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset + ulOffset);
  FLASH_ERRORS_E  eRet            = eFLASH_NO_ERROR;

  /* delay 4us */
  delay_us(4);

  /* Perform Polling Operation */
  do
  {
    polling_counter--;
    dev_status = FlashGetStatus(ptFlashDev, ulBlockAddress, fBufferWrite);
  }
  while((dev_status == DEV_BUSY) && polling_counter);

  /* read the actual data */
  ulActData = READ_FLASH(ulBlockAddress);

  /*
  * if device returns status other than "not busy" then we
  *  have a polling error state. 
  *  Note: assumes the "while dev_busy" test above does not change!
  *
  * if device was "not busy" then verify polling location.
  */
  if(dev_status != DEV_NOT_BUSY)
  {
    if(dev_status == DEV_WRITE_BUFFER_ABORT)
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
    if(ulOffsetData  == ulActData)
    {
      /* everything is OK */
    }
    else 
    {
      eRet = eFLASH_DEVICE_FAILED;
    }
  }

  return eRet;
}

// ////////////////////////////////////////////////////
//! Writes a sequence of flash commands
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ptCmd         Array of command blocks
//!  \param ulCount       Number of commands
// ////////////////////////////////////////////////////
static void  FlashWriteCommandSequence(FLASH_DEVICE *ptFlashDev, FLASH_COMMAND_BLOCK_T* ptCmd, unsigned long ulCount)
{
  while(ulCount-- > 0)
  {
    FlashWriteCommand(ptFlashDev, 0, ptCmd->ulAddress, ptCmd->bCmd);
    ++ptCmd;
  }
}

// ///////////////////////////////////////////////////// 
//! \}
// ///////////////////////////////////////////////////// 
