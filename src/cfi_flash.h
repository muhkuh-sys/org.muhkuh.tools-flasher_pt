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

#include <stddef.h>


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

/* NOR Commands. */
#define READ_QUERY_CMD          0x98
#define READ_QUERY_CMD_OFFSET   0x55
#define CFI_QUERY_INFO_OFFSET   0x10

#define READ_IDENT_CMD          0x90

#define READ_ARRAY_OFFSET       0x00
#define READ_ARRAY_CMD          0xFF

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


typedef union
{
	const unsigned char *puc;
	const unsigned short *pus;
	const unsigned long *pul;
	unsigned long ul;
} CADR_T;

typedef union
{
	unsigned char *puc;
	unsigned short *pus;
	unsigned long *pul;
	unsigned long ul;
} ADR_T;

typedef union
{
	volatile unsigned char *puc;
	volatile unsigned short *pus;
	volatile unsigned long *pul;
	volatile unsigned long ul;
} VADR_T;


/* This structure describes one sector of a flash device. */
typedef struct tagSECTOR_INFO
{
	unsigned long ulOffset;
	unsigned long ulSize;
} SECTOR_INFO_T;


/* The errorcodes. */
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

typedef struct tagFLASH_DEVICE FLASH_DEVICE_T;

typedef FLASH_ERRORS_E(*PFN_FLASH_RESET)(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
typedef FLASH_ERRORS_E(*PFN_FLASH_ERASE)(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
typedef FLASH_ERRORS_E(*PFN_FLASH_ERASEALL)(const FLASH_DEVICE_T *ptFlashDev);
typedef FLASH_ERRORS_E(*PFN_FLASH_PROGRAM)(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartOffset, unsigned long ulLength, const void* pvData);
typedef FLASH_ERRORS_E(*PFN_FLASH_LOCK)(const FLASH_DEVICE_T *ptFlashDev, unsigned long ulSector);
typedef FLASH_ERRORS_E(*PFN_FLASH_UNLOCK)(const FLASH_DEVICE_T *ptFlashDev);



typedef struct
{
	unsigned int uiUnit;
	unsigned int uiChipSelect;
	unsigned long ulAllowedBusWidths;
} PARFLASH_CONFIGURATION_T;

typedef void(*PFN_FLASHSETUP)(const PARFLASH_CONFIGURATION_T *ptParameter, unsigned int uiWidth);

/* Function pointer table for flash support. */
typedef struct FLASH_FUNCTIONS_Ttag
{
	PFN_FLASH_RESET         pfnReset;
	PFN_FLASH_ERASE         pfnErase;
	PFN_FLASH_ERASEALL      pfnEraseDevice;
	PFN_FLASH_PROGRAM       pfnProgram;
	PFN_FLASH_LOCK          pfnLock;
	PFN_FLASH_UNLOCK        pfnUnlock;
} FLASH_FUNCTIONS_T;



typedef enum
{
	BUS_WIDTH_8Bit          = 0,
	BUS_WIDTH_16Bit         = 1,
	BUS_WIDTH_32Bit         = 2
} BUS_WIDTH_T;


typedef enum 
{
	CFI_SETUP_1x08		= 0x01,
	CFI_SETUP_2x08		= 0x02,
	CFI_SETUP_1x16		= 0x04,
	CFI_SETUP_2x16		= 0x08,
	CFI_SETUP_1x32		= 0x10
} CFI_SETUP_T;







/* CFI Query information structure located at byte offset 0x10
   when accessing device in byte mode.
*/
#pragma pack(1)
typedef struct
{
  char            abQueryIdent[3];        /* identification (must be "QRY") */
  unsigned short  usVendorCommandSet;     /* vendor command set (see CFI Publication 100) */
  unsigned short  usPrimaryAlgorithmExt;  /* Primary algorithm extension table address (0 if unsupported) */
  unsigned short  usAltVendorCommandSet;  /* alternate vendor command set (see CFI Publication 100) */
  unsigned short  usAltAlgorithmExt;      /* Alternate algorithm extension table address (0 if unsupported) */
  unsigned char   bVccMinProgramVoltage;  /* Minimum Vcc programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts) */
  unsigned char   bVccMaxProgramVoltage;  /* Maximum Vcc programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts) */
  unsigned char   bVppMinProgramVoltage;  /* Minimum Vpp programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts) */
  unsigned char   bVppMaxProgramVoltage;  /* Maximum Vpp programming voltage (7-4 BCD volts, 0-3 BCD 100mVolts) */
  unsigned char   bTypWriteTimeout;       /* Typical single byte/word write timeout 2^n us */
  unsigned char   bTypBufferWriteTimeout; /* Typical max buffer write timeout 2^n us (0 means unsupported) */
  unsigned char   bTypBlockEraseTimeout;  /* Typical per individual block erase timeout in 2^n ms */
  unsigned char   bTypChipEraserTimeout;  /* Typical per chip erase timeout in 2^n ms (0 means unsupported) */
  unsigned char   bMaxWriteTimeout;       /* Maximum timeout per single byte/word write 2^n us */
  unsigned char   bMaxBufferWriteTimeout; /* Maximum timeout per max buffer write  2^n us (0 means unsupported) */
  unsigned char   bMaxBlockEraseTimeout;  /* Maximum timeout per individual block erase in 2^n ms */
  unsigned char   bMaxChipEraserTimeout;  /* Maximum timeout per chip erase in 2^n ms (0 means unsupported) */
  unsigned char   bDeviceSize;            /* Size of device in 2^n bytes */
  unsigned short  usInterfaceDescr;       /* Interface descriptor (see CFI Publication 100) */
  unsigned short  usMaxBufferWriteSize;   /* Maximum number of bytes in buffer to write (in 2^n Bytes) */
  unsigned char   bEraseBlockRegions;     /* Number of regions in device */
  unsigned long   aulEraseRegionInfo[256]; /* information about each region (31-16: block size in 256 Byte increments, 15-0 number of cont. blocks -1) */
} CFI_QUERY_INFORMATION;

#define CFI_QUERY_BASE_SIZE (offsetof(CFI_QUERY_INFORMATION, aulEraseRegionInfo[0]))


// ///////////////////////////////////////////////////// 
//              Extended query header
// ///////////////////////////////////////////////////// 

typedef struct{
  char abExtQueryIdent[3];                 //!< ASCII string "PRI" 
  char bMajorVer;                          //!< major version number as ASCII char 
  char bMinorVer;                          //!< minor version number as ASCII char 
} CFI_EXTQUERY_HEADER_T;


// ///////////////////////////////////////////////////// 
//     Extended query structure V1.0-1.4 for Spansion
// ///////////////////////////////////////////////////// 

// fAddressSensitiveUnlock:
//   bits 0-1 00 = required, 01= not required 
//   PRI1.1/1.2: bits 2-7: process technology 
//   PRI1.3:     bits 2-5: process technology 
//            
// bProtectScheme:           
//   1 = AM29F040   (hardware only)
//   2 = AM29F016   (hardware only)
//   3 = AM29F400   (hardware only)
//   4 = AM29LV800A (hardware only)
//   5 = AM29BDS640 (software command locking)
//   6 = AM29BDD160 (new sector protect)
//   7 = AM29PDL128 (new sector protect + AM29LV800A)
//   8 = Advanced sector protection
// 
// fSimultaneousOperation:   
//   V 1.0: 0 = not supported, 1 = supported 
//   V 1.2: 0 = not supported, XX = number of sectors in bank 2
//   V 1.3: 0 = not supported, XX = number of sectors in bank in all banks except boot bank
// 
// bTopBottomBootSector:
//   0 = device without WP control
//   1 = 8x8kb sectors at to and bottom with WP control
//   2 = Bottom boot device
//   3 = Top boot device
//   4 = Uniform/bottom WP protect
//   5 = Uniform/top WP protect  
//   V 1.2: If number of erase block regions = 1, ignore this field 

typedef struct{
  char abExtQueryIdent[3];                 //!< ASCII string "PRI" 
  char bMajorVer;                          //!< major version number as ASCII char 
  char bMinorVer;                          //!< minor version number as ASCII char 
  unsigned char fAddressSensitiveUnlock;   //!< address sensitive unlock/process technology 
  unsigned char fEraseSuspendSupported;    //!< 0 = not supported, 1 = read only, 2 = read/write 
  unsigned char fSectorProtect;            //!< 0 = not supported, >0 = number of sectors per group 
  unsigned char fTempSectorUnprotect;      //!< 0 = not supported, 1 = supported (hardware/software methods) 
  unsigned char bProtectScheme;            //!< sector protection scheme 
  unsigned char fSimultaneousOperation;    //!< simultaneous operation 
  unsigned char fBurstModeType;            //!< 0 = not supported, 1 = supported 
  unsigned char fPageModeType;             //!< 0 = not supported, 1 = 4 word page, 2 = 8 word page 
  
  //!< V 1.1 and above
  unsigned char bSupplyMin;                //!< Acceleration Supply Minimum (7-4 BCD volts, 0-3 BCD 100mVolts) 
  unsigned char bSupplyMax;                //!< Acceleration Supply Maximum (7-4 BCD volts, 0-3 BCD 100mVolts) 
  unsigned char bTopBottomBootSector;
  
  //!< V 1.2 and above
  unsigned char fProgramSuspend;           //!< 0 = not supported, 1 = supported 
  
  //!< V 1.4 and above
  unsigned char fUnlockBypass;             //!< 0 = not supported, 1 = supported 
  unsigned char bSecSiSize;                //!< 2^n bytes
  unsigned char bEmbeddedHWResetMaxTimeout;//!< 2^n ns
  unsigned char bNonEmbeddedHWResetMaxTimeout;//!< 2^n ns
  unsigned char bEraseSuspendMaxTimeout;   //!< 2^n us
  unsigned char bProgramSuspendMaxTimeout; //!< 2^n us
  
  //!< V1.3: only the first 4 entries are valid, V1.4: 32 entries
  unsigned char bBankOrganization;         //!< 0: simultaneous operation = 0, xx = number of banks
  unsigned char abBankInfo[32];            //!< number of sectors in banks 1-32
} CFI_SPANSION_EXTQUERY_T;

#define SPANSION_CFI_EXTQUERY_BASE_SIZE (offsetof(CFI_SPANSION_EXTQUERY_T, bSupplyMin))


/*  
ulFeatureSupport:
Optional feature and command support(1=yes, 0=no) 
bits 9–31 are reserved; undefined bits are 0. 
If bit 31 is 1 then another 31 bit field of optional features 
follows at the end of the bit-30 field.

  bit0 Chip erase supported
  bit1 Suspend erase supported
  bit2 Suspend program supported
  bit3 Legacy lock/unlock supported
  bit4 Queued erase supported
  bit5 Instant Individual block locking supported
  bit6 Protection bits supported
  bit7 Page-mode read supported
  bit8 Synchronous read supported

*/

typedef struct{
	char abExtQueryIdent[3];                 //!< ASCII string "PRI" 
	char bMajorVer;                          //!< major version number as ASCII char 
	char bMinorVer;                          //!< minor version number as ASCII char 
	unsigned long ulFeatureSupport;          //!< optional feature and command support
	unsigned char bAfterSuspend;             //!< supported functions after suspend
	unsigned short usBlockStatusRegMask;     //!< block status register mask
	unsigned char bVCCMax;                   //!< highest performance program/erase voltage (7-4 BCD volts, 0-3 BCD 100mVolts)
	unsigned char bVPPOpt;                   //!< optimum program/erase voltage (7-4 BCD volts, 0-3 BCD 100mVolts)
	unsigned char bNumProtectionRegFields;   //!< number of protection register fields
	unsigned long aulProtectionFields[256];  //!< protection register fields
} CFI_STRATA_EXTQUERY_T;


#pragma pack()

/* Structure describing a flash device. */
struct tagFLASH_DEVICE
{
	unsigned char       ucManufacturer;          /* Manufacturer code provided by flash. */
	unsigned char       ucDevice;                /* Device code provided by flash. */
	unsigned short      usVendorCommandSet;      /* Vendor Command Set. */
	BUS_WIDTH_T         tBits;                   /* Bus width. */
	int                 fPaired;                 /* TRUE on 16/16 or 8/8 configurations. */
	CFI_SETUP_T         tSetup;                  /* Bus width and paired mode. */
	unsigned long       ulFlashSize;             /* Total size of flash in bytes. */
	unsigned long       ulMaxBufferWriteSize;    /* Buffered Write buffer length in Bytes. */
	unsigned char      *pucFlashBase;            /* Base address of flash device. */
	unsigned long       ulSectorCnt;             /* Total number of sectors. */
	FLASH_FUNCTIONS_T   tFlashFunctions;         /* Function pointer table for flash commands. */
	PFN_FLASHSETUP      pfnSetup;                /* Function to setup the memory interface. */
	char                acIdent[16];             /* Name of the device. */
	SECTOR_INFO_T       atSectors[MAX_SECTORS];  /* Information for each sector. */
	int                 fPriExtQueryValid;        //!< 1 if tPriExtQuery is valid, 0 if not
	union {
    	CFI_EXTQUERY_HEADER_T   tHeader;
    	CFI_SPANSION_EXTQUERY_T tSpansion;  
	} tPriExtQuery;                               //!< CFI primary extended query block
};

int CFI_IdentifyFlash(FLASH_DEVICE_T* ptFlashDevice, PARFLASH_CONFIGURATION_T *ptCfg);
const SECTOR_INFO_T *cfi_find_matching_sector(const FLASH_DEVICE_T *ptFlashDescription, unsigned long ulAddress);
size_t cfi_find_matching_sector_index(const FLASH_DEVICE_T *ptFlashDescription, unsigned long ulAddress);

#endif  /* __CFI_FLASH_H__ */

