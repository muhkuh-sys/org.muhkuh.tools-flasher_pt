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
//! \file parallelflash.h
//!  Headerfile of Parallel FLASH Driver Module Function Prototypes
// ////////////////////////////////////////////////////

// ///////////////////////////////////////////////////// 
//! \addtogroup EBOOT_FLASH
//! \{
// ///////////////////////////////////////////////////// 

#ifndef __STRATA_H
#define __STRATA_H

  #include "cfi_flash.h"
       
  // Data bits to read indicating the status of an FLASH operation
  #define DRV_INTEL_SR7_WRT     (0x80)  //!< write ready busy
  #define DRV_INTEL_SR6_ERS     (0x40)  //!< erase suspended
  #define DRV_INTEL_SR5_CLR_LCK (0x20)  //!< erase and clear lock
  #define DRV_INTEL_SR4_SET_LCK (0x10)  //!< Program and set lock
  #define DRV_INTEL_SR3_PRG_VLT (0x08)  //!< VPP low
  #define DRV_INTEL_SR2_PRG_SUS (0x04)  //!< Program suspended
  #define DRV_INTEL_SR1_DEV_PRT (0x02)  //!< Sector locked
  #define DRV_INTEL_SR0_RES     (0x01)  //!< reset

  #define MFGCODE_INTEL           0x89	// Intel's flash manufacturing code.
  
  //    Define flash memory command set (these are 8bit flash commands)   
  #define BLOCK_ERASE                   0x20
  #define PROGRAM_BYTE_WORD             0x40
  #define CLEAR_STATUS_REGISTER         0x50
  #define READ_STATUS_REGISTER          0x70
  #define READ_IDENTIFIER_CODE          0x90
  #define READ_QUERY                    0x98
  #define BLOCK_ERASE_PROGRAM_SUSPEND   0xB0
  #define BLOCK_ERASE_PROGRAM_RESUME    0xD0
  #define WRITE_TO_BUFFER               0xE8
  #define SET_BLOCK_LOCK_BIT            0x60
  #define CLEAR_BLOCK_LOCK_BIT          0x60
  #define PROTECTION_PROGRAM            0xC0
  #define CONFIGURATION                 0xB8
  #define READ_ARRAY                    0xFF
  #define SET_BLOCK_LOCK_CONFIRM	0x01
  #define CLEAR_BLOCK_LOCK_CONFIRM	0xD0

  int IntelIdentifyFlash(FLASH_DEVICE *ptFlashDev);

// ///////////////////////////////////////////////////// 
//! \}
// ///////////////////////////////////////////////////// 


#endif

