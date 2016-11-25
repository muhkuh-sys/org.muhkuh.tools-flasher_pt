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



#if ASIC_TYP==ASIC_TYP_NETX90_MPW
NETX_CONSOLEAPP_RESULT_T internal_flash_detect(CMD_PARAMETER_DETECT_T *ptParameter)
#else
NETX_CONSOLEAPP_RESULT_T internal_flash_detect(CMD_PARAMETER_DETECT_T *ptParameter __attribute__((unused)))
#endif
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;


#if ASIC_TYP==ASIC_TYP_NETX90_MPW
	/* netX90 MPW has the first version of the MAZ flash. */
	tResult = internal_flash_maz_v0_detect(ptParameter);
#else
	uprintf("! Internal flash is not available on this platform.\n");
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;
#endif

	ptDeviceDescription = ptParameter->ptDeviceDescription;
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* Set the result data */
		ptDeviceDescription->fIsValid = 1;
		ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
		ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
		ptDeviceDescription->tSourceTyp = BUS_IFlash;
	}
	else
	{
		/* Set the result data */
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
