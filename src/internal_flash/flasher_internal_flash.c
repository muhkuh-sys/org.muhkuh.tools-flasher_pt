/***************************************************************************
 *   Copyright (C) 2016 by Hilscher GmbH                                   *
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


#include "flasher_internal_flash.h"

#include "internal_flash_maz_v0.h"
#include "uprintf.h"


static NETX_CONSOLEAPP_RESULT_T check_flash_type(INTERNAL_FLASH_TYPE_T tType)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	switch(tType)
	{
	case INTERNAL_FLASH_TYPE_Unknown:
	case INTERNAL_FLASH_TYPE_MAZ_V0:
		tResult = NETX_CONSOLEAPP_RESULT_OK;
		break;
	}

	return tResult;
}



#if ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
NETX_CONSOLEAPP_RESULT_T internal_flash_detect(CMD_PARAMETER_DETECT_T *ptParameter)
#else
NETX_CONSOLEAPP_RESULT_T internal_flash_detect(CMD_PARAMETER_DETECT_T *ptParameter __attribute__((unused)))
#endif
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;


	/* Initialize the device description with default values. */
	ptDeviceDescription = ptParameter->ptDeviceDescription;
	ptDeviceDescription->fIsValid = 0;
	ptDeviceDescription->sizThis = 0;
	ptDeviceDescription->ulVersion = 0;
	ptDeviceDescription->tSourceTyp = BUS_IFlash;

#if ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
	/* netX90 MPW has the first version of the MAZ flash. */
	tResult = internal_flash_maz_v0_detect(ptParameter);
#else
	uprintf("! Internal flash is not available on this platform.\n");
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;
#endif

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* Set the result data. */
		ptDeviceDescription->fIsValid = 1;
		ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
		ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
		ptDeviceDescription->tSourceTyp = BUS_IFlash;
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_flash(CMD_PARAMETER_FLASH_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_flash(ptParameter);
			break;
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_erase(CMD_PARAMETER_ERASE_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_erase(ptParameter);
			break;
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_read(CMD_PARAMETER_READ_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_read(ptParameter);
			break;
		}
	}

	return tResult;
}



#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T internal_flash_sha1(CMD_PARAMETER_CHECKSUM_T *ptParameter, SHA_CTX *ptSha1Context)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_sha1(ptParameter, ptSha1Context);
			break;
		}
	}

	return tResult;
}
#endif



NETX_CONSOLEAPP_RESULT_T internal_flash_verify(CMD_PARAMETER_VERIFY_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_verify(ptParameter, ptConsoleParams);
			break;
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_isErased(CMD_PARAMETER_ISERASED_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_is_erased(ptParameter, ptConsoleParams);
			break;
		}
	}

	return tResult;
}


NETX_CONSOLEAPP_RESULT_T internal_flash_getEraseArea(CMD_PARAMETER_GETERASEAREA_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tType;


	/* Get the detected internal flash type. */
	tType = ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType;
	tResult = check_flash_type(tType);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Unknown internal flash type: %d\n", tType);
	}
	else
	{
		switch(tType)
		{
		case INTERNAL_FLASH_TYPE_Unknown:
			uprintf("! Unknown internal flash type.\n");
			break;

		case INTERNAL_FLASH_TYPE_MAZ_V0:
			tResult = internal_flash_maz_v0_get_erase_area(ptParameter);
			break;
		}
	}

	return tResult;
}
