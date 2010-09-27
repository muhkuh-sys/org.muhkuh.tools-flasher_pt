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

#include "strata.h"
#include <string.h>

static FLASH_ERRORS_E FlashWaitStatusDone (FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static void           FlashWriteCommand   (FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulCmd);
static int            FlashIsset          (FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulCmd);

static FLASH_ERRORS_E FlashReset(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashErase(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashEraseAll(FLASH_DEVICE_T *ptFlashDev);
static FLASH_ERRORS_E FlashProgram(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData);
static FLASH_ERRORS_E FlashLock (FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
static FLASH_ERRORS_E FlashUnlock(FLASH_DEVICE_T *ptFlashDev);

static FLASH_FUNCTIONS_T s_tIntelStrataFuncs =
{
  FlashReset,
  FlashErase,
  FlashEraseAll,
  FlashProgram,
  FlashLock,
  FlashUnlock
};

int IntelIdentifyFlash(FLASH_DEVICE_T *ptFlashDev)
{
  int fRet = FALSE;

  /* try to identify Strata Flash */
  FlashWriteCommand(ptFlashDev, 0, 0, READ_IDENT_CMD);

  ptFlashDev->bManufacturer = ptFlashDev->pbFlashBase[0];
  ptFlashDev->bDevice       = ptFlashDev->pbFlashBase[1];

  FlashWriteCommand(ptFlashDev, 0 ,0, READ_ARRAY_CMD);

  if(ptFlashDev->bManufacturer == MFGCODE_INTEL)
  {
    strcpy(ptFlashDev->szIdent, "Intel");
    ptFlashDev->ptFlashFuncs = &s_tIntelStrataFuncs;
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
static FLASH_ERRORS_E FlashReset(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
  FlashWriteCommand(ptFlashDev, ulSector, 0, READ_ARRAY);

  return eFLASH_NO_ERROR;
}

// ////////////////////////////////////////////////////
//! Erase a flash sector
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \param ulSector    Sector to erase
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashErase(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
  FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;

  FlashWriteCommand(ptFlashDev, ulSector, 0, BLOCK_ERASE);
  FlashWriteCommand(ptFlashDev, ulSector, 0, BLOCK_ERASE_PROGRAM_RESUME);

  eRet = FlashWaitStatusDone(ptFlashDev, ulSector);

  if(eFLASH_NO_ERROR != eRet)
    FlashWriteCommand(ptFlashDev, ulSector, 0, CLEAR_STATUS_REGISTER);

  FlashReset(ptFlashDev, ulSector);

  return eRet;
}

// ////////////////////////////////////////////////////
//! Erase whole flash
//!  \param ptFlashDev  Pointer to the FLASH control Block
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashEraseAll(FLASH_DEVICE_T *ptFlashDev)
{
  FLASH_ERRORS_E eRet     = eFLASH_NO_ERROR;
  unsigned long  ulSector = 0;

  for(ulSector = 0; ulSector < ptFlashDev->ulSectorCnt; ++ulSector)
  {
    if(eFLASH_NO_ERROR != (eRet = FlashErase(ptFlashDev, ulSector)))
    {
      FlashWriteCommand(ptFlashDev, ulSector, 0, CLEAR_STATUS_REGISTER);
      break;
    }
  }

  return eRet;
}

// ////////////////////////////////////////////////////
//! Program flash
//!  \param ptFlashDev    Pointer to the FLASH control Block
//!  \param ulStartOffset Offset to start writing at
//!  \param ulLength      Length of data to write
//!  \param pvData        Data pointer
//!  \return eFLASH_NO_ERROR on success
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashProgram(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData)
{
  unsigned long  ulCurrentSector  = 0;
  unsigned long  ulCurrentOffset  = ulStartOffset; 
//  unsigned long  ulBufferWriteCnt = 0;
  const unsigned char* pbSource         = (const unsigned char*)pvData;
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

  if(!fFound)
    return eFLASH_INVALID_PARAMETER;


  FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, CLEAR_STATUS_REGISTER);
  FlashReset(ptFlashDev, ulCurrentSector);

  while(ulLength > 0)
  {
    unsigned long ulWriteSize    = 0; //Bufferwrite size this run
    unsigned char bWriteCountCmd = 0;
    unsigned long ulMaxBuffer    = ptFlashDev->ulMaxBufferWriteSize;

    if(ptFlashDev->fPaired)
      ulMaxBuffer *= 2;

    if(ulLength > ulMaxBuffer)
      ulWriteSize = ulMaxBuffer;
    else
      ulWriteSize = ulLength;

    if((ulCurrentOffset + ulWriteSize) > ptFlashDev->atSectors[ulCurrentSector].ulSize)
    {
      ulWriteSize = ptFlashDev->atSectors[ulCurrentSector].ulSize - ulCurrentOffset;
    }

    switch(ptFlashDev->tBits)
    {
    case BUS_WIDTH_8Bit:
      bWriteCountCmd = (unsigned char)(ulWriteSize - 1);
      break;

    case BUS_WIDTH_16Bit:
      bWriteCountCmd = (unsigned char)(ulWriteSize / 2 - 1);
      break;

    case BUS_WIDTH_32Bit:
      bWriteCountCmd = (unsigned char)(ulWriteSize / 4 - 1);
      break;
    }

    FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, WRITE_TO_BUFFER);
    FlashWaitStatusDone(ptFlashDev, ulCurrentSector);

    FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, bWriteCountCmd);

    ulLength -= ulWriteSize;

    while(ulWriteSize != 0)
    {
      volatile unsigned char* pbWriteAddr = ptFlashDev->pbFlashBase + 
                                   ptFlashDev->atSectors[ulCurrentSector].ulOffset + 
                                   ulCurrentOffset;

      switch(ptFlashDev->tBits)
      {
      case BUS_WIDTH_8Bit:
        *pbWriteAddr = *pbSource++;
        ++ulCurrentOffset;
        --ulWriteSize;
        break;

      case BUS_WIDTH_16Bit:
        *(volatile unsigned short*)pbWriteAddr = *(volatile unsigned short*)pbSource;
        pbSource += 2;
        ulCurrentOffset += 2;
        ulWriteSize -= 2;
        break;

      case BUS_WIDTH_32Bit:
        *(volatile unsigned long*)pbWriteAddr = *(volatile unsigned long*)pbSource;
        pbSource += 4;
        ulCurrentOffset += 4;
        ulWriteSize -= 4;
        break;
      }
    }

    FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, BLOCK_ERASE_PROGRAM_RESUME);

    /* Full Status Check */
    if(eFLASH_NO_ERROR != (eRet = FlashWaitStatusDone(ptFlashDev, ulCurrentSector)))
    {
      break;
    }

    //wrap around
    if(ulCurrentOffset == ptFlashDev->atSectors[ulCurrentSector].ulSize)    
    {
      FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, READ_ARRAY);

      ulCurrentOffset = 0;
      ++ulCurrentSector;
    }
  }

  FlashWriteCommand(ptFlashDev, ulCurrentSector, 0, READ_ARRAY);

  return eRet;
}


FLASH_ERRORS_E FlashLock(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
	FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;


	FlashWriteCommand(ptFlashDev, ulSector, 0, SET_BLOCK_LOCK_BIT);
	FlashWriteCommand(ptFlashDev, ulSector, 0, SET_BLOCK_LOCK_CONFIRM);

	eRet = FlashWaitStatusDone(ptFlashDev, ulSector);
	if( eFLASH_NO_ERROR!=eRet )
	{
		FlashWriteCommand(ptFlashDev, ulSector, 0, CLEAR_STATUS_REGISTER);
	}

	FlashReset(ptFlashDev, ulSector);

	return eRet;
}


FLASH_ERRORS_E FlashUnlock(FLASH_DEVICE_T *ptFlashDev)
{
	FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;


	FlashWriteCommand(ptFlashDev, 0, 0, CLEAR_BLOCK_LOCK_BIT);
	FlashWriteCommand(ptFlashDev, 0, 0, CLEAR_BLOCK_LOCK_CONFIRM);

	eRet = FlashWaitStatusDone(ptFlashDev, 0);
	if( eRet!=eFLASH_NO_ERROR )
	{
		FlashWriteCommand(ptFlashDev, 0, 0, CLEAR_STATUS_REGISTER);
	}

	FlashReset(ptFlashDev, 0);

	return eRet;
}


// ////////////////////////////////////////////////////
//! Write a command to the FLASH
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector FLASH sector number
//!  \param ulOffset Offset address in the actual FLASH sector
//!  \param bCmd Command to execute
// ////////////////////////////////////////////////////
void FlashWriteCommand(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulCmd)
{
	union
	{
		volatile unsigned char *puc;
		volatile unsigned short *pus;
		volatile unsigned long *pul;
	} uAdr;


	uAdr.puc = ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset + ulOffset;

	switch( ptFlashDev->tBits )
	{
	case BUS_WIDTH_8Bit:
		/* 8bits cannot be paired */
		*(uAdr.puc) = (unsigned char)ulCmd;
		break;

	case BUS_WIDTH_16Bit:
		if( ptFlashDev->fPaired )
		{
			ulCmd |= ulCmd << 8;
		}

		*(uAdr.pus) = (unsigned short)ulCmd;
		break;

	case BUS_WIDTH_32Bit:
		if( ptFlashDev->fPaired )
		{
			ulCmd |= ulCmd << 16;
		}

		*(uAdr.pul) = ulCmd;
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
int FlashIsset(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector, unsigned long ulOffset, unsigned long ulCmd)
{
  int            iRet       = FALSE;
  volatile unsigned char* pbReadAddr = ptFlashDev->pbFlashBase + ptFlashDev->atSectors[ulSector].ulOffset + ulOffset;

  switch(ptFlashDev->tBits)
  {
  case BUS_WIDTH_8Bit:
    if(*pbReadAddr & ulCmd)
      iRet = TRUE;
    break;

  case BUS_WIDTH_16Bit:
    {
      unsigned short usValue    = *(volatile unsigned short*)pbReadAddr;
      unsigned short usCheckCmd = ulCmd;

      if(ptFlashDev->fPaired)
        usCheckCmd |= ulCmd << 8;

      if((usValue & usCheckCmd) == usCheckCmd)
        iRet = TRUE;
    }
    break;

  case BUS_WIDTH_32Bit:
    {
      unsigned long ulValue    = *(volatile unsigned long*)pbReadAddr;
      unsigned long ulCheckCmd = ulCmd;

      if(ptFlashDev->fPaired)
        ulCheckCmd |= ulCmd << 16;

      if((ulValue & ulCheckCmd) == ulCheckCmd)
        iRet = TRUE;
    }
    break;
  }

  return iRet;
}

// ////////////////////////////////////////////////////
//! Wait until FLASH has accepted a state change
//!  \param ptFlashDev Pointer to the FLASH control Block
//!  \param ulSector FLASH sector number
// ////////////////////////////////////////////////////
static FLASH_ERRORS_E FlashWaitStatusDone(FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector)
{
  FLASH_ERRORS_E eRet = eFLASH_NO_ERROR;

  while(!FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR7_WRT)) 
    ;

  if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR6_ERS))
  {
    eRet = eFLASH_GENERAL_ERROR;
//    EdbgOutputDebugString("ERROR: Status done. Erase suspended!\r\n");

  } else if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR5_CLR_LCK))
  {
    eRet = eFLASH_LOCKED;
//    EdbgOutputDebugString("ERROR: Status done. Erase and clear Lock!\r\n");
  } else if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR4_SET_LCK))
  {

    eRet = eFLASH_LOCKED;
//    EdbgOutputDebugString("ERROR: Status done. Program and Set Lock!\r\n");
  } else if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR3_PRG_VLT))
  {
    eRet = eFLASH_VPP_LOW;
//    EdbgOutputDebugString("ERROR: Status done. VPP low!\r\n");
  } else if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR2_PRG_SUS))
  {
    eRet = eFLASH_GENERAL_ERROR;
//    EdbgOutputDebugString("ERROR: Status done. Program suspended!\r\n");
  } else if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR1_DEV_PRT))
  {
    eRet = eFLASH_LOCKED;
//    EdbgOutputDebugString("ERROR: Status done. Sector locked!\r\n");
  } else if(FlashIsset(ptFlashDev, ulSector, 0, DRV_INTEL_SR0_RES))
  {
    eRet = eFLASH_BUSY;
//    EdbgOutputDebugString("ERROR: Status done. Reset!\r\n");
  }

  return eRet;
}

// ///////////////////////////////////////////////////// 
//! \}
// ///////////////////////////////////////////////////// 
