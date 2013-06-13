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

#include "flasher_version.h"
#include "netx_consoleapp.h"
#include "rdyrun.h"

#include "board.h"

/* Parallel flash routines. */
#include "flasher_parflash.h"
/* Serial flash on SPI. */
#include "flasher_spi.h"
#include "sha1.h"

#include "flasher_interface.h"
#include "units.h"
#include "uprintf.h"
#include "systime.h"

#include "main.h"


/* ------------------------------------- */



static NETX_CONSOLEAPP_RESULT_T opMode_detect(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	tSourceTyp = ptAppParams->uParameter.tDetect.tSourceTyp;

	/* Clear the result data. */
	memset(ptAppParams->uParameter.tDetect.ptDeviceDescription, 0, sizeof(DEVICE_DESCRIPTION_T));

	uprintf(". Device: ");
	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		uprintf("Parallel flash\n");
		tResult = parflash_detect(&(ptAppParams->uParameter.tDetect));
		break;

	case BUS_SPI:
		/*  use SPI flash */
		uprintf("SPI flash\n");
		tResult = spi_detect(&(ptAppParams->uParameter.tDetect));
		break;

	default:
		/*  unknown boot device */
		uprintf("unknown\n");
		uprintf("! illegal device id specified\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		break;
	}

	return tResult;
}

/* ------------------------------------- */

static NETX_CONSOLEAPP_RESULT_T check_device_description(const DEVICE_DESCRIPTION_T *ptDeviceDescription)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	
	/* expect error */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	if( ptDeviceDescription==NULL )
	{
		uprintf("! Missing device description!\n");
	}
	else if( ptDeviceDescription->fIsValid==0 )
	{
		uprintf("! The device description is not valid!\n");
	}
	else if( ptDeviceDescription->sizThis!=sizeof(DEVICE_DESCRIPTION_T) )
	{
		uprintf("! The size of the device description differs from the internal representation!\n");
	}
	else if( ptDeviceDescription->ulVersion!=FLASHER_INTERFACE_VERSION )
	{
		uprintf("! The device description has an invalid version!\n");
	}
	else
	{
		tSourceTyp = ptDeviceDescription->tSourceTyp;
		switch(tSourceTyp)
		{
		case BUS_ParFlash:
			uprintf(". Device type: Parallel flash\n");
			tResult = NETX_CONSOLEAPP_RESULT_OK;
			break;
	
		case BUS_SPI:
			/*  use SPI flash */
			uprintf(". Device type: SPI flash\n");
			tResult = NETX_CONSOLEAPP_RESULT_OK;
			break;
	
		default:
			/*  unknown boot device */
			uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
			break;
		}
	}

	return tResult;
}

/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_flash(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;

	/* get the source type */
	tSourceTyp = ptAppParams->uParameter.tFlash.ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_flash(&(ptAppParams->uParameter.tFlash));
		break;

	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_flash(&(ptAppParams->uParameter.tFlash));
		break;

	}

	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_erase(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* get the source type */
	tSourceTyp = ptAppParams->uParameter.tFlash.ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_erase(&(ptAppParams->uParameter.tErase));
		break;

	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_erase(&(ptAppParams->uParameter.tErase));
		break;
	}
	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_read(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;

	/* get the source type */
	tSourceTyp = ptAppParams->uParameter.tFlash.ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_read(&(ptAppParams->uParameter.tRead));
		break;
		
	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_read(&(ptAppParams->uParameter.tRead));
		break;
	}

	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_verify(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;

	/* get the source type */
	tSourceTyp = ptAppParams->uParameter.tFlash.ptDeviceDescription->tSourceTyp;

	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_verify(&(ptAppParams->uParameter.tVerify), ptConsoleParams);
		break;
		
	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_verify(&(ptAppParams->uParameter.tVerify), ptConsoleParams);
		break;
	}

	return tResult;
}

#if CFG_INCLUDE_SHA1!=0
static NETX_CONSOLEAPP_RESULT_T opMode_checksum(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	SHA_CTX tShaContext;
	
	SHA1_Init(&tShaContext);
	
	/* get the source type */
	tSourceTyp = ptAppParams->uParameter.tFlash.ptDeviceDescription->tSourceTyp;

	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_sha1(&(ptAppParams->uParameter.tChecksum), &tShaContext);
		break;
		
	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_sha1(&(ptAppParams->uParameter.tChecksum), &tShaContext);
		break;
	}

	/* store hash value in parameter */
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		SHA1_Final(&ptAppParams->uParameter.tChecksum.aucSha1[0], &tShaContext);
	}
	
	return tResult;
}
#endif



static NETX_CONSOLEAPP_RESULT_T opMode_isErased(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	tSourceTyp = ptAppParams->uParameter.tFlash.ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_isErased(&(ptAppParams->uParameter.tIsErased), ptConsoleParams);
		break;

	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_isErased(&(ptAppParams->uParameter.tIsErased), ptConsoleParams);
		break;
	}

	return tResult;
}


/* ------------------------------------- */

static unsigned long getFlashSize(const DEVICE_DESCRIPTION_T *ptDeviceDescription)
{
	BUS_T tSrcType;
	tSrcType = ptDeviceDescription->tSourceTyp;
	
	switch(tSrcType)
	{
	case BUS_ParFlash:
		return ptDeviceDescription->uInfo.tParFlash.ulFlashSize;
		break;

	case BUS_SPI:
		return ptDeviceDescription->uInfo.tSpiInfo.tAttributes.ulSize;
		break;

	default:
		return 0;
	}
}


static NETX_CONSOLEAPP_RESULT_T opMode_getEraseArea(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSrcType;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	tSrcType = ptAppParams->uParameter.tGetEraseArea.ptDeviceDescription->tSourceTyp;

	if (ptAppParams->uParameter.tGetEraseArea.ulEndAdr == 0xffffffffU)
	{
		ptAppParams->uParameter.tGetEraseArea.ulEndAdr = getFlashSize(ptAppParams->uParameter.tGetEraseArea.ptDeviceDescription);
	}
	
	switch(tSrcType)
	{
	case BUS_ParFlash:
		/*  use parallel flash */
		tResult = parflash_getEraseArea(&(ptAppParams->uParameter.tGetEraseArea));
		break;

	case BUS_SPI:
		/*  use SPI flash */
		tResult = spi_getEraseArea(&(ptAppParams->uParameter.tGetEraseArea));
		break;
	}


	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_getBoardInfo(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulBusId;
	unsigned long ulUnitId;
	unsigned char *pucBuffer;
	size_t sizBuffer;
	BUS_T tBusId;
	size_t sizData;



	ulBusId = ptAppParams->uParameter.tGetBoardInfo.ulBusId;
	ulUnitId = ptAppParams->uParameter.tGetBoardInfo.ulUnitId;

	pucBuffer = ptAppParams->uParameter.tGetBoardInfo.pucBuffer;
	sizBuffer = ptAppParams->uParameter.tGetBoardInfo.sizBuffer;

	if( ulBusId==0xffffffffU )
	{
		sizData = units_make_bus_table(pucBuffer, sizBuffer);
		ptConsoleParams->pvReturnMessage = (void*)sizData;

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else if( ulUnitId==0xffffffffU )
	{
		tBusId = (BUS_T)ulBusId;
		sizData = units_make_unit_table(tBusId, pucBuffer, sizBuffer);
		ptConsoleParams->pvReturnMessage = (void*)sizData;

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		/* No unit info yet. */
		ptConsoleParams->pvReturnMessage = NULL;

		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}

	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_easyErase(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* Adapt the erase area to the sector boundaries. */
	tResult = opMode_getEraseArea(ptAppParams);
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* Is the erase area already clean? */
		tResult = opMode_isErased(ptAppParams, ptConsoleParams);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* The erase area is not clean. Erase it now. */
			if( ptConsoleParams->pvReturnMessage!=((void*)0xff) )
			{
				tResult = opMode_erase(ptAppParams);
			}
		}
	}

	return tResult;
}


/* ------------------------------------- */

#define FLAG_STARTADR 1
#define FLAG_ENDADR 2
#define FLAG_SIZE 4
#define FLAG_BUFFERADR 8
#define FLAG_DEVICE 16

#if 1
static NETX_CONSOLEAPP_RESULT_T check_params(NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	tFlasherInputParameter *ptAppParams;
	unsigned long ulParamVersion;
	OPERATION_MODE_T tOpMode;
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulDataByteSize;
	unsigned char *pucData;
	unsigned long ulFlashSize;
	unsigned long ulPars;
	
	/*  get application parameters */
	ptAppParams = (tFlasherInputParameter*)ptConsoleParams->pvInitParams;

	/*  check parameter version */
	ulParamVersion = ptAppParams->ulParamVersion;
	if( ulParamVersion!=0x00020000 )
	{
		uprintf("! unknown parameter version: %04x.%04x. Expected 0002.0000!\n", ulParamVersion>>16, ulParamVersion&0xffff);
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	/* Extract and print the parameters for each mode */
	tOpMode = ptAppParams->tOperationMode;
	switch( tOpMode )
	{
	case OPERATION_MODE_Detect:
		ulPars = 0;
		uprintf(". Mode: Detect\n");
		break;

	case OPERATION_MODE_Flash:
		ulPars = FLAG_STARTADR + FLAG_SIZE + FLAG_BUFFERADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tFlash.ulStartAdr;
		ulDataByteSize      = ptAppParams->uParameter.tFlash.ulDataByteSize;
		pucData             = ptAppParams->uParameter.tFlash.pucData;
		ptDeviceDescription = ptAppParams->uParameter.tFlash.ptDeviceDescription;
		uprintf(". Mode: Write to flash\n");
		uprintf(". Start offset in flash: 0x%08x\n", ulStartAdr);
		uprintf(". Data size:             0x%08x\n", ulDataByteSize);
		uprintf(". Buffer address:        0x%08x\n", pucData);
		break;

	case OPERATION_MODE_Erase:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tErase.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tErase.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tErase.ptDeviceDescription;
		uprintf(". Mode: Erase\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		break;

	case OPERATION_MODE_Read:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_BUFFERADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tRead.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tRead.ulEndAdr;
		pucData             = ptAppParams->uParameter.tRead.pucData;
		ptDeviceDescription = ptAppParams->uParameter.tRead.ptDeviceDescription;
		uprintf(". Mode: Read\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		uprintf(". Buffer address: 0x%08x\n", pucData);
		break;
		
	case OPERATION_MODE_Verify:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_BUFFERADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tVerify.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tVerify.ulEndAdr;
		pucData             = ptAppParams->uParameter.tVerify.pucData;
		ptDeviceDescription = ptAppParams->uParameter.tVerify.ptDeviceDescription;
		uprintf(". Mode: Verify\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		uprintf(". Buffer address: 0x%08x\n", pucData);
		break;
		
#if CFG_INCLUDE_SHA1!=0
	case OPERATION_MODE_Checksum:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tChecksum.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tChecksum.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tChecksum.ptDeviceDescription;
		uprintf(". Mode: Checksum (SHA1)\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		break;
#endif
		
	case OPERATION_MODE_IsErased:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tIsErased.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tIsErased.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tIsErased.ptDeviceDescription;
		uprintf(". Mode: IsErased\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		break;

	case OPERATION_MODE_GetEraseArea:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tGetEraseArea.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tGetEraseArea.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tGetEraseArea.ptDeviceDescription;
		uprintf(". Mode: Get Erase Area\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		break;

	case OPERATION_MODE_GetBoardInfo:
		ulPars = 0;
		uprintf(".Mode: Get Board Info\n");
		break;

	case OPERATION_MODE_EasyErase:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tGetEraseArea.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tGetEraseArea.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tGetEraseArea.ptDeviceDescription;
		uprintf(". Mode: Get Erase Area\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		break;

	default:
		ulPars = 0;
		uprintf("! unknown operation mode: %d\n", tOpMode);
		return NETX_CONSOLEAPP_RESULT_ERROR;
		break;
	}
	
	/* If the mode requires a device description, check if it is correct
		and if the offsets are within the size */
	if (ulPars & FLAG_DEVICE)
	{
		tResult = check_device_description(ptDeviceDescription);
		if (tResult != NETX_CONSOLEAPP_RESULT_OK)
		{
			return tResult;
		}
		else
		{
			ulFlashSize = getFlashSize(ptDeviceDescription);
			uprintf(". Flash size: 0x%08x\n", ulFlashSize);
			
			if ((ulPars & FLAG_STARTADR) && ulStartAdr >= ulFlashSize)
			{
				uprintf("! Start offset exceeds flash size.\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
			
			if ((ulPars & FLAG_ENDADR) && ulEndAdr > ulFlashSize
				&& ( tOpMode != OPERATION_MODE_GetEraseArea && ulEndAdr != 0xffffffffU))
			{
				uprintf("! End offset exceeds flash size.\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
			
			if ((ulPars & FLAG_SIZE) && ulDataByteSize > ulFlashSize)
			{
				uprintf("! Data size exceeds flash size.\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
		}
	}
	
	if ((ulPars & FLAG_STARTADR) && (ulPars & FLAG_ENDADR) && (ulStartAdr > ulEndAdr))
	{
		uprintf("! Start offset is larger than end offset.\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	return NETX_CONSOLEAPP_RESULT_OK;
}

#else
static NETX_CONSOLEAPP_RESULT_T check_params(NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	tFlasherInputParameter *ptAppParams;
	unsigned long ulParamVersion;
	OPERATION_MODE_T tOpMode;
	const DEVICE_DESCRIPTION_T *ptDeviceDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulDataByteSize;
	unsigned char *pucData;
	unsigned long ulFlashSize;
	unsigned long ulPars;
	const char *pszMode;
	
	/*  get application parameters */
	ptAppParams = (tFlasherInputParameter*)ptConsoleParams->pvInitParams;

	/*  check parameter version */
	ulParamVersion = ptAppParams->ulParamVersion;
	if( ulParamVersion!=0x00020000 )
	{
		uprintf("! unknown parameter version: %04x.%04x. Expected 0002.0000!\n", ulParamVersion>>16, ulParamVersion&0xffff);
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	/* Extract the parameters for each mode */
	tOpMode = ptAppParams->tOperationMode;
	switch( tOpMode )
	{
	case OPERATION_MODE_Detect:
		ulPars = 0;
		pszMode = "Detect";
		break;

	case OPERATION_MODE_Flash:
		ulPars = FLAG_STARTADR + FLAG_SIZE + FLAG_BUFFERADR + FLAG_DEVICE;
		pszMode = "Write to flash";
		ulStartAdr          = ptAppParams->uParameter.tFlash.ulStartAdr;
		ulDataByteSize      = ptAppParams->uParameter.tFlash.ulDataByteSize;
		pucData             = ptAppParams->uParameter.tFlash.pucData;
		ptDeviceDescription = ptAppParams->uParameter.tFlash.ptDeviceDescription;
		break;

	case OPERATION_MODE_Erase:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		pszMode = "Erase";
		ulStartAdr          = ptAppParams->uParameter.tErase.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tErase.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tErase.ptDeviceDescription;
		break;

	case OPERATION_MODE_Read:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_BUFFERADR + FLAG_DEVICE;
		pszMode = "Read from flash";
		ulStartAdr          = ptAppParams->uParameter.tRead.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tRead.ulEndAdr;
		pucData             = ptAppParams->uParameter.tRead.pucData;
		ptDeviceDescription = ptAppParams->uParameter.tRead.ptDeviceDescription;
		break;
		
	case OPERATION_MODE_Verify:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_BUFFERADR + FLAG_DEVICE;
		pszMode = "Verify";
		ulStartAdr          = ptAppParams->uParameter.tVerify.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tVerify.ulEndAdr;
		pucData             = ptAppParams->uParameter.tVerify.pucData;
		ptDeviceDescription = ptAppParams->uParameter.tVerify.ptDeviceDescription;
		break;
		
#if CFG_INCLUDE_SHA1!=0
	case OPERATION_MODE_Checksum:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		pszMode = "Calculate SHA1 checksum";
		ulStartAdr          = ptAppParams->uParameter.tChecksum.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tChecksum.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tChecksum.ptDeviceDescription;
		break;
#endif
		
	case OPERATION_MODE_IsErased:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		pszMode = "IsErased";
		ulStartAdr          = ptAppParams->uParameter.tIsErased.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tIsErased.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tIsErased.ptDeviceDescription;
		break;

	case OPERATION_MODE_GetEraseArea:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		pszMode = "Get Erase Area";
		ulStartAdr          = ptAppParams->uParameter.tGetEraseArea.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tGetEraseArea.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tGetEraseArea.ptDeviceDescription;
		break;

	case OPERATION_MODE_GetBoardInfo:
		ulPars = 0;
		pszMode = "Get Board Info";
		break;

	default:
		ulPars = 0;
		uprintf("! unknown operation mode: %d\n", tOpMode);
		return NETX_CONSOLEAPP_RESULT_ERROR;
		break;
	}
	
	/* print the parameters */
	uprintf(". Mode: %s\n", pszMode);
	if ((ulPars & FLAG_STARTADR) && (ulPars & FLAG_ENDADR))
	{
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
	}
	else if ((ulPars & FLAG_STARTADR) && (ulPars & FLAG_SIZE))
	{
		uprintf(". Start offset in flash: 0x%08x\n", ulStartAdr);
		uprintf(". Data size:             0x%08x\n", ulDataByteSize);
	}
	
	if (ulPars & FLAG_BUFFERADR)
	{
		uprintf(". Buffer address: 0x%08x\n", pucData);
	}
	
	/* If the mode requires a device description, check if it is correct
		and if the offsets are within the size */
	if (ulPars & FLAG_DEVICE)
	{
		tResult = check_device_description(ptDeviceDescription);
		if (tResult != NETX_CONSOLEAPP_RESULT_OK)
		{
			return tResult;
		}
		else
		{
			ulFlashSize = getFlashSize(ptDeviceDescription);
			uprintf(". Flash size: 0x%08x\n", ulFlashSize);
			
			if ((ulPars & FLAG_STARTADR) && ulStartAdr >= ulFlashSize)
			{
				uprintf("! Start offset exceeds flash size.\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
			
			if ((ulPars & FLAG_ENDADR) && ulEndAdr > ulFlashSize
				&& ( tOpMode != OPERATION_MODE_GetEraseArea && ulEndAdr != 0xffffffffU))
			{
				uprintf("! End offset exceeds flash size.\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
			
			if ((ulPars & FLAG_SIZE) && ulDataByteSize > ulFlashSize)
			{
				uprintf("! Data size exceeds flash size.\n");
				return NETX_CONSOLEAPP_RESULT_ERROR;
			}
		}
	}
	
	if ((ulPars & FLAG_STARTADR) && (ulPars & FLAG_ENDADR) && (ulStartAdr > ulEndAdr))
	{
		uprintf("! Start offset is larger than end offset.\n");
		return NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	return NETX_CONSOLEAPP_RESULT_OK;
}


#endif

NETX_CONSOLEAPP_RESULT_T netx_consoleapp_main(NETX_CONSOLEAPP_PARAMETER_T *ptTestParam)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	tFlasherInputParameter *ptAppParams;
	OPERATION_MODE_T tOpMode;
	
	ptAppParams = (tFlasherInputParameter*)ptTestParam->pvInitParams;
	tOpMode = ptAppParams->tOperationMode;
	
	/* init the board */
	tResult = board_init();
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		/* failed to init board, can not continue */
		setRdyRunLed(RDYRUN_LED_RED);
	}
	else
	{
		/* switch off sys led */
		setRdyRunLed(RDYRUN_LED_OFF);
		
		/* configure systime, used by progress functions */
		systime_init();  

		if (tOpMode == OPERATION_MODE_Detect || tOpMode == OPERATION_MODE_GetBoardInfo) {
		/* say hi if mode is Detect or GetBoardInfo*/
			uprintf(
			"\f\n\n\n\nFlasher v" FLASHER_VERSION_ALL "\n\n"
			"Copyright (C) 2005-2013 C.Thelen (cthelen@hilscher.com)\n"
			"and M.Trensch.\n"
			"There is NO warranty.  You may redistribute this software\n"
			"under the terms of the GNU Library General Public License.\n"
			"For more information about these matters, see the files\n"
			"named COPYING.\n");
			
			uprintf("\n");
			uprintf(". Data pointer:    0x%08x\n", (unsigned long)ptTestParam);
			uprintf(". Init parameter:  0x%08x\n", (unsigned long)ptTestParam->pvInitParams);
			uprintf("\n");
		}
		tResult = check_params(ptTestParam);
		if (tResult == NETX_CONSOLEAPP_RESULT_OK)
		{
			/*  run operation */
			switch( tOpMode )
			{
			case OPERATION_MODE_Detect:
				tResult = opMode_detect(ptAppParams);
				break;

			case OPERATION_MODE_Flash:
				tResult = opMode_flash(ptAppParams);
				break;

			case OPERATION_MODE_Erase:
				tResult = opMode_erase(ptAppParams);
				break;

			case OPERATION_MODE_Read:
				tResult = opMode_read(ptAppParams);
				break;
				
			case OPERATION_MODE_Verify:
				tResult = opMode_verify(ptAppParams, ptTestParam);
				break;
				
#if CFG_INCLUDE_SHA1!=0
			case OPERATION_MODE_Checksum:
				tResult = opMode_checksum(ptAppParams);
				break;
#endif
				
			case OPERATION_MODE_IsErased:
				tResult = opMode_isErased(ptAppParams, ptTestParam);
				break;

			case OPERATION_MODE_GetEraseArea:
				tResult = opMode_getEraseArea(ptAppParams);
				break;

			case OPERATION_MODE_GetBoardInfo:
				tResult = opMode_getBoardInfo(ptAppParams, ptTestParam);
				break;

			case OPERATION_MODE_EasyErase:
				tResult = opMode_easyErase(ptAppParams, ptTestParam);
				break;
			}
		}
	}

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/*  operation ok */
		uprintf("* OK *\n");
		setRdyRunLed(RDYRUN_LED_GREEN);
	}
	else
	{
		/*  operation failed */
		setRdyRunLed(RDYRUN_LED_RED);
	}


	return tResult;
}

