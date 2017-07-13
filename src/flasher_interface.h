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

#ifndef __FLASHER_INTERFACE_H__
#define __FLASHER_INTERFACE_H__


#include <string.h>

#include "cfi_flash.h"
#include "internal_flash/internal_flash.h"
#include "spi_flash.h"
#include "spi_macro_player.h"

/*-------------------------------------*/

#define FLASHER_INTERFACE_VERSION 0x00030000


typedef enum BUS_ENUM
{
	BUS_ParFlash                    = 0,    /* Parallel flash */
	BUS_SPI                         = 1,    /* Serial flash on SPI bus. */
	BUS_IFlash                      = 2     /* Internal flash. */
} BUS_T;

typedef enum OPERATION_MODE_ENUM
{
	OPERATION_MODE_Flash            = 0,
	OPERATION_MODE_Erase            = 1,
	OPERATION_MODE_Read             = 2,
	OPERATION_MODE_Verify           = 3,
	OPERATION_MODE_Checksum         = 4,    /* build a checksum over the contents of a specified area of a device */
	OPERATION_MODE_Detect           = 5,    /* detect a device */
	OPERATION_MODE_IsErased         = 6,    /* check if the specified area of a device is erased */
	OPERATION_MODE_GetEraseArea     = 7,    /* expand an area to the erase block borders */
	OPERATION_MODE_GetBoardInfo     = 8,    /* get bus and unit information */
	OPERATION_MODE_EasyErase        = 9,    /* A combination of GetEraseArea, IsErased and Erase. */
	OPERATION_MODE_SpiMacroPlayer   = 10    /* Play an SPI macro. */
} OPERATION_MODE_T;


typedef struct DEVICE_DESCRIPTION_STRUCT
{
	int fIsValid;                           /* a value of !=0 means the description is valid */
	size_t sizThis;                         /* size of the complete structure in bytes */
	unsigned long ulVersion;                /* interface version of this description (this is the same as the version in the input parameters) */

	BUS_T tSourceTyp;
	union
	{
		FLASH_DEVICE_T tParFlash;
		SPI_FLASH_T tSpiInfo;
		INTERNAL_FLASH_T tInternalFlashInfo;
	} uInfo;
} DEVICE_DESCRIPTION_T;


/* 
    ulStartAddr/ulEndAddr are relative offsets into the flash,
    pucData is an absolute pointer to the RAM buffer.
*/
   
typedef struct CMD_PARAMETER_FLASH_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulDataByteSize;
	unsigned char *pucData;
} CMD_PARAMETER_FLASH_T;


typedef struct CMD_PARAMETER_ERASE_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
} CMD_PARAMETER_ERASE_T;


typedef struct CMD_PARAMETER_READ_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned char *pucData;
} CMD_PARAMETER_READ_T;


typedef struct CMD_PARAMETER_VERIFY_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned char *pucData;
} CMD_PARAMETER_VERIFY_T;


typedef struct CMD_PARAMETER_CHECKSUM_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned char aucSha1[20];
} CMD_PARAMETER_CHECKSUM_T;


typedef struct CMD_PARAMETER_DETECT_STRUCT
{
	BUS_T tSourceTyp;
	union
	{
		PARFLASH_CONFIGURATION_T tParFlash;
		FLASHER_SPI_CONFIGURATION_T tSpi;
		INTERNAL_FLASH_CONFIGURATION_T tInternalFlash;
	} uSourceParameter;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;
} CMD_PARAMETER_DETECT_T;


typedef struct CMD_PARAMETER_ISERASED_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
} CMD_PARAMETER_ISERASED_T;


typedef struct CMD_PARAMETER_GETERASEAREA_STRUCT
{
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
} CMD_PARAMETER_GETERASEAREA_T;


typedef struct CMD_PARAMETER_GETBOARDINFO_STRUCT
{
	unsigned long ulBusId;
	unsigned long ulUnitId;
	unsigned char *pucBuffer;
	size_t sizBuffer;
} CMD_PARAMETER_GETBOARDINFO_T;


typedef struct tFlasherInputParameter_STRUCT
{
	unsigned long ulParamVersion;
	OPERATION_MODE_T tOperationMode;
	union
	{
		CMD_PARAMETER_FLASH_T tFlash;
		CMD_PARAMETER_ERASE_T tErase;
		CMD_PARAMETER_READ_T tRead;
		CMD_PARAMETER_VERIFY_T tVerify;
		CMD_PARAMETER_CHECKSUM_T tChecksum;
		CMD_PARAMETER_DETECT_T tDetect;
		CMD_PARAMETER_ISERASED_T tIsErased;
		CMD_PARAMETER_GETERASEAREA_T tGetEraseArea;
		CMD_PARAMETER_GETBOARDINFO_T tGetBoardInfo;
		CMD_PARAMETER_SPIMACROPLAYER_T tSpiMacroPlayer;
	} uParameter;
} tFlasherInputParameter;


/*-------------------------------------------------------------------------*/

#endif  /*__FLASHER_INTERFACE_H__ */

