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

#ifndef __SPANSION_H
#define __SPANSION_H

  #include "cfi_flash.h"

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


  int SpansionIdentifyFlash(FLASH_DEVICE_T *ptFlashDev);

// ///////////////////////////////////////////////////// 
//! \}
// ///////////////////////////////////////////////////// 


#endif

