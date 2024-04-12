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
#include "rdy_run.h"

#include "board.h"

/* Internal flash routines. */
#include "internal_flash/flasher_internal_flash.h"
/* Parallel flash routines. */
#include "flasher_parflash.h"
/* Serial flash on SPI. */
#include "flasher_spi.h"
#include "spi_macro_player.h"
#include "sha1.h"

#include "flasher_interface.h"
#include "flasher_header.h"
#include "uprintf.h"
#include "systime.h"

#include "main.h"

#ifdef CFG_INCLUDE_SDIO
#include "flasher_sdio.h"
#endif

/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_detect(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	CMD_PARAMETER_DETECT_T *ptParameter;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;


	/* Get a shortcut to the parameters and the device description. */
	ptParameter = &(ptAppParams->uParameter.tDetect);
	ptDeviceDescription = ptParameter->ptDeviceDescription;

	/* Clear the result data. */
	memset(ptDeviceDescription, 0, sizeof(DEVICE_DESCRIPTION_T));

	uprintf(". Device: ");
	tSourceTyp = ptParameter->tSourceTyp;
	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash */
		uprintf("Parallel flash\n");
		tResult = parflash_detect(ptParameter);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash */
		uprintf("SPI flash\n");
		tResult = spi_detect(&(ptParameter->uSourceParameter.tSpi), &(ptDeviceDescription->uInfo.tSpiInfo), (char*)(flasher_version.pucBuffer_End));
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			ptDeviceDescription->fIsValid = 1;
			ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
			ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
			ptDeviceDescription->tSourceTyp = BUS_SPI;
		}
		else
		{
			/* Clear the result data. */
			memset(ptDeviceDescription, 0, sizeof(DEVICE_DESCRIPTION_T));
		}

		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use internal flash */
		uprintf("internal flash\n");
		tResult = internal_flash_detect(ptParameter);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		uprintf("SD/EMMC\n");
		SDIO_HANDLE_T *ptSdioHandle = &(ptParameter->ptDeviceDescription->uInfo.tSdioHandle);
		tResult = sdio_detect_wrap(ptSdioHandle);

		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			ptDeviceDescription->fIsValid = 1;
			ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
			ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
			ptDeviceDescription->tSourceTyp = BUS_SDIO;
		}
		else
		{
			/* Clear the result data. */
			memset(ptDeviceDescription, 0, sizeof(DEVICE_DESCRIPTION_T));
		}
		break;
#endif

	default:
		/* unknown device type */
		uprintf("unknown\n");
		uprintf("! illegal device id specified: %d\n", tSourceTyp);
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
#ifdef CFG_INCLUDE_PARFLASH
		case BUS_ParFlash:
			/* Use parallel flash. */
			uprintf(". Device type: Parallel flash\n");
			tResult = NETX_CONSOLEAPP_RESULT_OK;
			break;
#endif

		case BUS_SPI:
			/* Use SPI flash */
			uprintf(". Device type: SPI flash\n");
			tResult = NETX_CONSOLEAPP_RESULT_OK;
			break;

#ifdef CFG_INCLUDE_INTFLASH
		case BUS_IFlash:
			/* Use internal flash */
			uprintf(". Device type: internal flash\n");
			tResult = NETX_CONSOLEAPP_RESULT_OK;
			break;
#endif

#ifdef CFG_INCLUDE_SDIO
		case BUS_SDIO:
			/* SDIO */
			uprintf(". Device type: SDIO\n");
			tResult = NETX_CONSOLEAPP_RESULT_OK;
			break;
#endif

		default:
			/* unknown device type */
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
	CMD_PARAMETER_FLASH_T *ptParameter;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tFlash);

	/* Get the source type. */
	tSourceTyp = ptParameter->ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_flash(ptParameter);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_flash(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulDataByteSize, ptParameter->pucData);
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use internal flash. */
		tResult = internal_flash_flash(ptParameter);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_write(ptParameter);
		break;
#endif

	default:
		uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
		break;
	}

	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_erase(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	CMD_PARAMETER_ERASE_T *ptParameter;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tErase);

	/* Get the source type. */
	tSourceTyp = ptParameter->ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_erase(ptParameter);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_erase(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulEndAdr);
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use internal flash. */
		tResult = internal_flash_erase(ptParameter);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_erase(ptParameter);
		break;
#endif

	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
		break;
	}
	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_read(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	CMD_PARAMETER_READ_T *ptParameter;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tRead);

	/* Get the source type. */
	tSourceTyp = ptParameter->ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_read(ptParameter);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_read(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulEndAdr, ptParameter->pucData);
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use internal flash. */
		tResult = internal_flash_read(ptParameter);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_read(ptParameter);
		break;
#endif

	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
		break;
	}
	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_verify(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	CMD_PARAMETER_VERIFY_T *ptParameter;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tVerify);

	/* Get the source type. */
	tSourceTyp = ptParameter->ptDeviceDescription->tSourceTyp;

	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_verify(ptParameter, ptConsoleParams);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_verify(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulEndAdr, ptParameter->pucData, &(ptConsoleParams->pvReturnMessage));
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use internal flash. */
		tResult = internal_flash_verify(ptParameter, ptConsoleParams);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_verify(ptParameter, (unsigned long*) &(ptConsoleParams->pvReturnMessage));
		break;
#endif

	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
		break;
	}

	return tResult;
}

#if CFG_INCLUDE_SHA1!=0
static NETX_CONSOLEAPP_RESULT_T opMode_checksum(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	CMD_PARAMETER_CHECKSUM_T *ptParameter;
	SHA_CTX tShaContext;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tChecksum);

	SHA1_Init(&tShaContext);

	/* Get the source type. */
	tSourceTyp = ptParameter->ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_sha1(ptParameter, &tShaContext);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_sha1(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulEndAdr, &tShaContext);
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use the internal flash. */
		tResult = internal_flash_sha1(ptParameter, &tShaContext);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_sha1(ptParameter, &tShaContext);
		break;
#endif
	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
		break;
	}

	/* store hash value in parameter */
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		SHA1_Final(&(ptParameter->aucSha1[0]), &tShaContext);
	}

	return tResult;
}
#endif



static NETX_CONSOLEAPP_RESULT_T opMode_isErased(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSourceTyp;
	CMD_PARAMETER_ISERASED_T *ptParameter;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tIsErased);

	/* Get the source type. */
	tSourceTyp = ptParameter->ptDeviceDescription->tSourceTyp;
	switch(tSourceTyp)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_isErased(ptParameter, ptConsoleParams);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_isErased(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulEndAdr, &(ptConsoleParams->pvReturnMessage));
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use SPI flash. */
		tResult = internal_flash_isErased(ptParameter, ptConsoleParams);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_is_erased(ptParameter, (unsigned long*) &(ptConsoleParams->pvReturnMessage));
		break;
#endif

	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSourceTyp);
		break;
	}

	return tResult;
}


/* ------------------------------------- */

/* Flash size in bytes, except for SD cards, where it is KB */
static unsigned long getFlashSize(const DEVICE_DESCRIPTION_T *ptDeviceDescription)
{
	BUS_T tSrcType;
	unsigned long ulFlashSize;


	/* This is the default value for the error case. */
	ulFlashSize = 0;

	/* Get the source type. */
	tSrcType = ptDeviceDescription->tSourceTyp;
	switch(tSrcType)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		ulFlashSize = ptDeviceDescription->uInfo.tParFlash.ulFlashSize;
		break;
#endif

	case BUS_SPI:
		ulFlashSize = ptDeviceDescription->uInfo.tSpiInfo.tAttributes.ulSize;
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		switch(ptDeviceDescription->uInfo.tInternalFlashInfo.tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			ulFlashSize = ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0.ulSizeInBytes;
			break;
		}
		break;
#endif

	/*
		The stored size is in KB.
		If the number fits into a DWord, convert it to bytes.
		If not, set the maximum value.
	*/
#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		ulFlashSize = ptDeviceDescription->uInfo.tSdioHandle.ulSizeKB;
		if (ulFlashSize < 0x00400000U)
		{
			ulFlashSize <<= 10;
		}
		else
		{
			ulFlashSize = 0xffffffffU;
		}
		break;
#endif

	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSrcType);
		break;
	}

	return ulFlashSize;
}


static NETX_CONSOLEAPP_RESULT_T opMode_getEraseArea(tFlasherInputParameter *ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	BUS_T tSrcType;
	CMD_PARAMETER_GETERASEAREA_T *ptParameter;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Get a shortcut to the parameters. */
	ptParameter = &(ptAppParams->uParameter.tGetEraseArea);

	if (ptParameter->ulEndAdr == 0xffffffffU)
	{
		ptParameter->ulEndAdr = getFlashSize(ptParameter->ptDeviceDescription);
	}

	/* Get the source type. */
	tSrcType = ptParameter->ptDeviceDescription->tSourceTyp;
	switch(tSrcType)
	{
#ifdef CFG_INCLUDE_PARFLASH
	case BUS_ParFlash:
		/* Use parallel flash. */
		tResult = parflash_getEraseArea(ptParameter);
		break;
#endif

	case BUS_SPI:
		/* Use SPI flash. */
		tResult = spi_getEraseArea(&(ptParameter->ptDeviceDescription->uInfo.tSpiInfo), ptParameter->ulStartAdr, ptParameter->ulEndAdr, &(ptParameter->ulStartAdr), &(ptParameter->ulEndAdr));
		break;

#ifdef CFG_INCLUDE_INTFLASH
	case BUS_IFlash:
		/* Use internal flash. */
		tResult = internal_flash_getEraseArea(ptParameter);
		break;
#endif

#ifdef CFG_INCLUDE_SDIO
	case BUS_SDIO:
		/* Use SDIO */
		tResult = sdio_get_erase_area(ptParameter);
		break;
#endif

	default:
		/*  unknown device */
		uprintf("! Unknown device type: 0x%08x\n", tSrcType);
		break;
	}


	return tResult;
}


/* ------------------------------------- */


static NETX_CONSOLEAPP_RESULT_T opMode_getBoardInfo(tFlasherInputParameter *ptAppParams)
{
	const void *pvBuffer;
	size_t sizBuffer;


	board_get_unit_description(&pvBuffer, &sizBuffer);
	ptAppParams->uParameter.tGetBoardInfo.pucBuffer = pvBuffer;
	ptAppParams->uParameter.tGetBoardInfo.sizBuffer = sizBuffer;

	return NETX_CONSOLEAPP_RESULT_OK;
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


static NETX_CONSOLEAPP_RESULT_T opMode_spiMacroPlayer(tFlasherInputParameter *ptAppParams, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	(void) ptConsoleParams; /* unused */

	tResult = spi_macro_player(&(ptAppParams->uParameter.tSpiMacroPlayer));
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
	unsigned long ulEndAdr       = 0; /* avoid 'uninitialized' warning */
	unsigned long ulDataByteSize = 0; /* dito */
	unsigned char *pucData;
	unsigned long ulFlashSize;
	unsigned long ulPars;

	/*  get application parameters */
	ptAppParams = (tFlasherInputParameter*)ptConsoleParams->pvInitParams;

	/*  check parameter version */
	ulParamVersion = ptAppParams->ulParamVersion;
	if( ulParamVersion!=FLASHER_INTERFACE_VERSION )
	{
		uprintf("! unknown parameter version: %04x.%04x. Expected %04x.%04x!\n",
			ulParamVersion>>16, ulParamVersion&0xffff,
			FLASHER_INTERFACE_VERSION>>16, FLASHER_INTERFACE_VERSION&0xffff);
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

	case OPERATION_MODE_Checksum:
		ulPars = FLAG_STARTADR + FLAG_ENDADR + FLAG_DEVICE;
		ulStartAdr          = ptAppParams->uParameter.tChecksum.ulStartAdr;
		ulEndAdr            = ptAppParams->uParameter.tChecksum.ulEndAdr;
		ptDeviceDescription = ptAppParams->uParameter.tChecksum.ptDeviceDescription;
		uprintf(". Mode: Checksum (SHA1)\n");
		uprintf(". Flash offset [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr);
		break;

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

	case OPERATION_MODE_SpiMacroPlayer:
		ulPars = 0;
		/* NOTE: do not print the mode here or the user will get insane for big macros. */
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

	/* Initialize the board. */
	tResult = board_init();
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		/* Failed to initialize board, can not continue! */
		rdy_run_setLEDs(RDYRUN_YELLOW);
	}
	else
	{
		/* Switch off the SYS led. */
		rdy_run_setLEDs(RDYRUN_OFF);

		/* Configure the systime, used by progress functions. */
		systime_init();

		if (tOpMode == OPERATION_MODE_Detect || tOpMode == OPERATION_MODE_GetBoardInfo) {
		/* say hi if mode is Detect or GetBoardInfo*/

			uprintf("                                                        \n");

			uprintf(
			"\f\n\n\n\nFlasher v" FLASHER_VERSION_ALL " " FLASHER_VERSION_VCS "\n\n"
			"Copyright (C) 2005-2019 C.Thelen (cthelen@hilscher.com)\n"
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

			case OPERATION_MODE_Checksum:
#if CFG_INCLUDE_SHA1!=0
				tResult = opMode_checksum(ptAppParams);
#else
				uprintf("Error: the checksum command is not supported by this build.\n");
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
#endif
				break;

			case OPERATION_MODE_IsErased:
				tResult = opMode_isErased(ptAppParams, ptTestParam);
				break;

			case OPERATION_MODE_GetEraseArea:
				tResult = opMode_getEraseArea(ptAppParams);
				break;

			case OPERATION_MODE_GetBoardInfo:
				tResult = opMode_getBoardInfo(ptAppParams);
				break;

			case OPERATION_MODE_EasyErase:
				tResult = opMode_easyErase(ptAppParams, ptTestParam);
				break;

			case OPERATION_MODE_SpiMacroPlayer:
				tResult = opMode_spiMacroPlayer(ptAppParams, ptTestParam);
				break;
			}
		}
	}

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/*  Operation OK! */
		uprintf("* OK *\n");
		rdy_run_setLEDs(RDYRUN_GREEN);
	}
	else
	{
		/*  Operation failed. */
		rdy_run_setLEDs(RDYRUN_YELLOW);
	}


	return tResult;
}

