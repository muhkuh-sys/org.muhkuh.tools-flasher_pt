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
/***************************************************************************  
  File          : cfi_flash.h                                                   
 ---------------------------------------------------------------------------- 
  Description:                                                                
                                                                              
      CFIFlash.h : Definitions for CFI compliant flash types                                       
 ---------------------------------------------------------------------------- 
  Todo:                                                                       
                                                                              
 ---------------------------------------------------------------------------- 
  Known Problems:                                                             
                                                                              
    -                                                                         
                                                                              
 ---------------------------------------------------------------------------- 
 ***************************************************************************/ 


// ///////////////////////////////////////////////////// 
//! \file cfi_flash.h
//!  Definitions for CFI compliant flash types
// ////////////////////////////////////////////////////

#ifndef __CFI_FLASH_H__
#define __CFI_FLASH_H__

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

// NOR Commands.
#define READ_QUERY_CMD			    0x98
#define READ_QUERY_CMD_OFFSET   0x55
#define CFI_QUERY_INFO_OFFSET   0x10

#define READ_IDENT_CMD			0x90

#define READ_ARRAY_CMD			0xFF

#define CFI_FLASH_100_INTEL_STD 0x0001
#define CFI_FLASH_100_AMD_STD   0x0002
#define CFI_FLASH_100_INTEL_EXT 0x0003
#define CFI_FLASH_100_AMD_EXT   0x0004

#define MAX_SECTORS             256

#define DEFAULT_POSTPAUSE       0x03
#define DEFAULT_PREPAUSE        0x03
#define DEFAULT_WAITSTATES      0x0f

#ifndef FALSE
  #define FALSE 0
#endif

#ifndef TRUE
  #define TRUE 1
#endif

// ///////////////////////////////////////////////////// 
//! Structure containing information about a flash sector
// ///////////////////////////////////////////////////// 
typedef struct tagSECTOR_INFO
{
  unsigned long ulOffset;
  unsigned long ulSize;
  
} SECTOR_INFO;

// ////////////////////////////////////////////////////
//! Error codes for generic flash access routines
// ////////////////////////////////////////////////////
typedef enum FLASH_ERRORS_Etag
{
  eFLASH_NO_ERROR = 0,
  eFLASH_GENERAL_ERROR,
  eFLASH_LOCKED,
  eFLASH_BUSY,
  eFLASH_VPP_LOW,
  eFLASH_NO_ERASED,
  eFLASH_INVALID_PARAMETER,
  eFLASH_ABORTED,
  eFLASH_DEVICE_FAILED
} FLASH_ERRORS_E;

typedef struct tagFLASH_DEVICE    FLASH_DEVICE, *PFLASH_DEVICE;

typedef FLASH_ERRORS_E(*PFN_FLASH_RESET)(PFLASH_DEVICE ptFlashDev, unsigned long ulSector);
typedef FLASH_ERRORS_E(*PFN_FLASH_ERASE)(PFLASH_DEVICE ptFlashDev, unsigned long ulSector);
typedef FLASH_ERRORS_E(*PFN_FLASH_ERASEALL)(PFLASH_DEVICE ptFlashDev);
typedef FLASH_ERRORS_E(*PFN_FLASH_PROGRAM)(PFLASH_DEVICE ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData);
typedef FLASH_ERRORS_E(*PFN_FLASH_LOCK)(PFLASH_DEVICE ptFlashDev, unsigned long ulSector);
typedef FLASH_ERRORS_E(*PFN_FLASH_UNLOCK)(PFLASH_DEVICE ptFlashDev);


typedef void(*PFN_FLASHSETUP)(unsigned int uiWidth);

// ////////////////////////////////////////////////////
//! Function pointer table for flash support
// ////////////////////////////////////////////////////
typedef struct FLASH_FUNCTIONS_Ttag
{
  PFN_FLASH_RESET     pfnReset;         /*! Function called to reset a sector */
  PFN_FLASH_ERASE     pfnErase;         /*! Function for sector erase */
  PFN_FLASH_ERASEALL  pfnEraseDevice;   /*! Function for Device Erase */
  PFN_FLASH_PROGRAM   pfnProgram;       /*! Function to program flash */
  PFN_FLASH_LOCK      pfnLock;          /*! Function to lock a block */
  PFN_FLASH_UNLOCK    pfnUnlock;        /*! Function to unlock a block */
} FLASH_FUNCTIONS_T,*PFLASH_FUNCTIONS_T;


// ///////////////////////////////////////////////////// 
//! Structure describing a flash device
// ///////////////////////////////////////////////////// 
struct tagFLASH_DEVICE
{
  unsigned char       bManufacturer;            //!< Manufacturer code provided by flash
  unsigned char       bDevice;                  //!< Device code provided by flash
  unsigned short      usVendorCommandSet;       //!< Vendor Command Set
  char                szIdent[16];              //!< Name of the device

  unsigned int        uiWidth;                   //!< 8, 16, 32 Bit
  int                 fPaired;                  //!< TRUE on 16/16 or 8/8 configurations
  unsigned long       ulFlashSize;              //!< total size of flash in bytes
  unsigned long       ulMaxBufferWriteSize;     //!< Buffered Write buffer length in Bytes
  unsigned char*      pbFlashBase;              //!< Base address of flash device
  unsigned long       ulSectorCnt;              //!< Total number of sectors
  SECTOR_INFO         atSectors[MAX_SECTORS];   //!< Information for each sector
  PFLASH_FUNCTIONS_T  ptFlashFuncs;             //!< Function pointer table for flash commands

};




#pragma pack(1)

// ///////////////////////////////////////////////////// 
//! CFI Query information structure located at byte offset 0x10
//! when accessing device in byte mode
// ///////////////////////////////////////////////////// 
typedef struct tagCFI_QUERY_INFORMATION
{
  char            abQueryIdent[3];        //!< identification (must be "QRY")
  unsigned short  usVendorCommandSet;     //!< vendor command set (see CFI Publication 100)
  unsigned short  usPrimaryAlgorithmExt;  //!< Primary algorithm extension table address (0 if unsupported)
  unsigned short  usAltVendorCommandSet;  //!< alternate vendor command set (see CFI Publication 100)
  unsigned short  usAltAlgorithmExt;      //!< Alternate algorithm extension table address (0 if unsupported)
  unsigned char   bVccMinProgramVoltage;  //!< Minimum Vcc programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts)
  unsigned char   bVccMaxProgramVoltage;  //!< Maximum Vcc programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts)
  unsigned char   bVppMinProgramVoltage;  //!< Minimum Vpp programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts)
  unsigned char   bVppMaxProgramVoltage;  //!< Maximum Vpp programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts)
  unsigned char   bTypWriteTimeout;       //!< Typical single byte/word write timeout 2^n us
  unsigned char   bTypBufferWriteTimeout; //!< Typical max buffer write timeout 2^n us (0 means unsupported)
  unsigned char   bTypBlockEraseTimeout;  //!< Typical per individual block erase timeout in 2^n ms
  unsigned char   bTypChipEraserTimeout;  //!< Typical per chip erase timeout in 2^n ms (0 means unsupported)
  unsigned char   bMaxWriteTimeout;       //!< Maximum timeout per single byte/word write 2^n us                 
  unsigned char   bMaxBufferWriteTimeout; //!< Maximum timeout per max buffer write  2^n us (0 means unsupported) 
  unsigned char   bMaxBlockEraseTimeout;  //!< Maximum timeout per individual block erase in 2^n ms          
  unsigned char   bMaxChipEraserTimeout;  //!< Maximum timeout per chip erase in 2^n ms (0 means unsupported)
  unsigned char   bDeviceSize;            //!< Size of device in 2^n bytes
  unsigned short  usInterfaceDescr;       //!< Interface descriptor (see CFI Publication 100)
  unsigned short  usMaxBufferWriteSize;   //!< Maximum number of bytes in buffer to write (in 2^n Bytes)
  unsigned char   bEraseBlockRegions;     //!< Number of regions in device
  unsigned long   aulEraseBlockInformations[MAX_SECTORS]; //!< information about each region (31-16: block size in 256 Byte increments, 15-0 number of cont. blocks -1)
  
} CFI_QUERY_INFORMATION, *PCFI_QUERY_INFORMATION;

#pragma pack()

int  CFI_IdentifyFlash(FLASH_DEVICE* ptFlashDevice, PFN_FLASHSETUP pfnSetup);

#endif /* __CFI_FLASH_H__ */

