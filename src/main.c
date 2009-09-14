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
 *   Free Software Foudnation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "flasher_version.h"
#include "netx_consoleapp.h"
#include "rdyrun.h"

#include "board.h"

/*  parallel flash on extension bus */
#include "flasher_ext.h"
/*  serial flash on spi */
#include "flasher_spi.h"
/*  parallel flash on sram bus */
#include "flasher_srb.h"


#include "flasher_interface.h"
#include "uprintf.h"

#include "main.h"

/* ------------------------------------- */
/*  local prototypes */

NETX_CONSOLEAPP_RESULT_T opMode_detect(ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_flash (ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_erase (ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_read  (ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_verify(ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_getEraseArea(ptFlasherInputParameter ptAppParams);

/* ------------------------------------- */

NETX_CONSOLEAPP_RESULT_T netx_consoleapp_main(NETX_CONSOLEAPP_PARAMETER_T *ptTestParam)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	ptFlasherInputParameter ptAppParams;
	unsigned long ulParamVersion;
	tOperationMode tOpMode;


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

		/* say hi */
		uprintf("\f\n\n\n\nFlasher v");
		uprintf(FLASHER_VERSION_ALL);
		uprintf("\n\n");
		uprintf("Copyright (C) 2005-2009 C.Thelen (cthelen@hilscher.com) and M.Trensch.\n");
		uprintf("There is NO warranty.  You may redistribute this software\n");
		uprintf("under the terms of the GNU Library General Public License.\n");
		uprintf("For more information about these matters, see the files named COPYING.\n");

		uprintf("\n");
		uprintf(". Data pointer:    0x$8\n", (unsigned long)ptTestParam);
		uprintf(". Init parameter:  0x$8\n", (unsigned long)ptTestParam->pvInitParams);
		uprintf("\n");

		/*  get application parameters */
		ptAppParams = (ptFlasherInputParameter)ptTestParam->pvInitParams;
#if 0
		/*  show application parameters */
		uprintf(". Application parameters:\n");
		uprintf(". parameter version: 0x$8\n", ptAppParams->ulParamVersion);
		uprintf(". operation mode:    0x$8\n", ptAppParams->ulOperationMode);
		uprintf(". data start:        0x$8\n", (unsigned long)ptAppParams->pbData);
		uprintf(". data size:         0x$8\n", ptAppParams->ulDataByteSize);
		uprintf(". boot type:         0x$8\n", ptAppParams->ulBootBlockSrcType);
		uprintf(". device offset:     0x$8\n", ptAppParams->ulDstDeviceOffset);
		uprintf("\n");
#endif
		/*  check parameter version */
		ulParamVersion = ptAppParams->ulParamVersion;
		if( ulParamVersion!=0x00020000 )
		{
			uprintf("! unknown parameter version: $4.$4. Expected 0002.0000!\n", ulParamVersion>>16, ulParamVersion&0xffff);
			setRdyRunLed(RDYRUN_LED_RED);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			/*  run operation */
			tOpMode = ptAppParams->tOperationMode;
			switch( tOpMode )
			{
			case OperationMode_Detect:
				uprintf(". Operation Mode: Detect\n");
				tResult = opMode_detect(ptAppParams);
				break;

			case OperationMode_Flash:
				uprintf(". Operation Mode: Flash\n");
				tResult = opMode_flash(ptAppParams);
				break;

			case OperationMode_Erase:
				uprintf(". Operation Mode: Erase\n");
				tResult = opMode_erase(ptAppParams);
				break;

// 			case OperationMode_Read:
// 				uprintf(". Operation Mode: Read\n");
// //				tResult = opMode_read(ptAppParams);
// 				break;

// 			case OperationMode_Verify:
// 				uprintf(". Operation Mode: Verify\n");
// //				tResult = opMode_verify(ptAppParams);
// 				break;

			case OperationMode_GetEraseArea:
				uprintf(". Operation Mode: Get Erase Area\n");
				tResult = opMode_getEraseArea(ptAppParams);
				break;

			default:
				uprintf("! unknown operation mode: $8\n", tOpMode);
				setRdyRunLed(RDYRUN_LED_RED);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
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

/* ------------------------------------- */


NETX_CONSOLEAPP_RESULT_T opMode_detect(ptFlasherInputParameter ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	tBootBlockSrcType tBBSrcType;


	tBBSrcType = ptAppParams->uParameter.tDetect.tSourceTyp;

	uprintf(". Device :");
	switch(tBBSrcType)
	{
// 	case BootBlockSrcType_SRamBus:
// 		/*  use parallel flash on SRam bus */
// 		uprintf("SRam Bus parflash\n");
// 		uprintf("! not supported yet...\n");
// 		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
// 		break;

	case BootBlockSrcType_SPI:
		/*  use SPI flash */
		uprintf("SPI flash\n");
		tResult = spi_detect(&(ptAppParams->uParameter.tDetect));
		break;

// 	case BootBlockSrcType_I2C:
// 		/*  use I2C eeprom */
// 		uprintf("I2C eeprom\n");
// 		uprintf("! not supported yet...\n");
// 		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
// 		break;

// 	case BootBlockSrcType_MMC:
// 		/*  use MMC/SD card */
// 		uprintf("MMC / SD card\n");
// 
// 		/*  not yet... */
// 		uprintf("! not supported yet...\n");
// 		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
// 
// 		break;

// 	case BootBlockSrcType_DPM:
// 		/*  DPM can't be flashed */
// 		uprintf("DPM\n");
// 
// 		uprintf("! not supported yet...\n");
// 		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
// 		break;

// 	case BootBlockSrcType_DPE:
// 		uprintf("DPM extended\n");
// 
// 		/*  DPM extended can't be flashed */
// 		uprintf("! DPM extented not supported\n");
// 		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
// 		break;

// 	case BootBlockSrcType_ExtBus:
// 		/*  use parallel flash on Extension bus */
// 		uprintf("extension bus parflash\n");
// 		tResult = ext_flash(ptAppParams->pbData, ptAppParams->ulDataByteSize);
// 		break;

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

static NETX_CONSOLEAPP_RESULT_T check_device_description(DEVICE_DESCRIPTION_T *ptDeviceDescription)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


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
		uprintf(". The device description seems to be ok.\n");
	}

	return tResult;
}

/* ------------------------------------- */


NETX_CONSOLEAPP_RESULT_T opMode_flash(ptFlasherInputParameter ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;
	tBootBlockSrcType tSourceTyp;


	/* check the device description */
	ptDeviceDescription = ptAppParams->uParameter.tFlash.ptDeviceDescription;
	tResult = check_device_description(ptDeviceDescription);

	/* get the source typ */
	tSourceTyp = ptDeviceDescription->tSourceTyp;

	uprintf(". Device :");
	switch(tSourceTyp)
	{
        case BootBlockSrcType_SPI:
                /*  use SPI flash */
                uprintf("SPI flash\n");
                tResult = spi_flash(&(ptAppParams->uParameter.tFlash));
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


NETX_CONSOLEAPP_RESULT_T opMode_erase(ptFlasherInputParameter ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;
	tBootBlockSrcType tSourceTyp;


	/* check the device description */
	ptDeviceDescription = ptAppParams->uParameter.tFlash.ptDeviceDescription;
	tResult = check_device_description(ptDeviceDescription);

	/* get the source typ */
	tSourceTyp = ptDeviceDescription->tSourceTyp;

	uprintf(". Device :");
	switch(tSourceTyp)
	{
	case BootBlockSrcType_SPI:
		/*  use SPI flash */
		uprintf("SPI flash\n");
		tResult = spi_erase(&(ptAppParams->uParameter.tErase));
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

#if 0
NETX_CONSOLEAPP_RESULT_T opMode_read(ptFlasherInputParameter ptAppParams)
{
        NETX_CONSOLEAPP_RESULT_T tResult;
        tBootBlockSrcType tBBSrcType;


        tBBSrcType = (tBootBlockSrcType)ptAppParams->ulBootBlockSrcType;

        uprintf(". Device :");
        switch(tBBSrcType)
        {
        case BootBlockSrcType_OldStyle:
                /*  old style bootblock, not supported for this operation */
                uprintf("old style device id\n");
                uprintf("! old style device id is not supported for read mode\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;
                break;

        case BootBlockSrcType_SRamBus:
                /*  use parallel flash on SRam bus */
                uprintf("SRam Bus parflash\n");
                tResult = srb_read(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_SPI:
                /*  use SPI flash */
                uprintf("SPI flash\n");
                tResult = spi_read(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_I2C:
                /*  use I2C eeprom */
                uprintf("I2C eeprom\n");
                tResult = i2c_read(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_MMC:
                /*  use MMC/SD card */
                uprintf("MMC / SD card\n");

                /*  not yet... */
                uprintf("! MMC / SD card is not supported yet...\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;

                break;

        case BootBlockSrcType_DPM:
                /*  DPM can't be flashed */
                uprintf("DPM\n");

                uprintf("! DPM is not supported\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;
                break;

        case BootBlockSrcType_DPE:
                uprintf("DPM extended\n");

                /*  DPM extended can't be flashed */
                uprintf("! DPM extented not supported\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;
                break;

        case BootBlockSrcType_ExtBus:
                /*  use parallel flash on Extension bus */
                uprintf("extension bus parflash\n");
                tResult = ext_read(ptAppParams->pbData, ptAppParams->ulDataByteSize);
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


NETX_CONSOLEAPP_RESULT_T opMode_verify(ptFlasherInputParameter ptAppParams)
{
        NETX_CONSOLEAPP_RESULT_T tResult;
        tBootBlockSrcType tBBSrcType;


        tBBSrcType = (tBootBlockSrcType)ptAppParams->ulBootBlockSrcType;

        uprintf(". Device :");
        switch(tBBSrcType)
        {
        case BootBlockSrcType_OldStyle:
                /*  old style bootblock, default to SPI */
                uprintf("old style, fallback to SPI flash\n");
                tResult = spi_verify(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_SRamBus:
                /*  use parallel flash on SRam bus */
                uprintf("SRam Bus parflash\n");
                tResult = srb_verify(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_SPI:
                /*  use SPI flash */
                uprintf("SPI flash\n");
                tResult = spi_verify(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_I2C:
                /*  use I2C eeprom */
                uprintf("I2C eeprom\n");
                tResult = i2c_verify(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_MMC:
                /*  use MMC/SD card */
                uprintf("MMC / SD card\n");

                /*  not yet... */
                uprintf("! MMC / SD card is not supported yet...\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;

                break;

        case BootBlockSrcType_DPM:
                /*  DPM can't be flashed */
                uprintf("DPM\n");

                uprintf("! DPM is not supported\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;
                break;

        case BootBlockSrcType_DPE:
                uprintf("DPM extended\n");

                /*  DPM extended can't be flashed */
                uprintf("! DPM extented not supported\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;
                break;

        case BootBlockSrcType_ExtBus:
                /*  use parallel flash on Extension bus */
                uprintf("extension bus parflash\n");
                tResult = ext_verify(ptAppParams->pbData, ptAppParams->ulDataByteSize);
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

#endif


NETX_CONSOLEAPP_RESULT_T opMode_getEraseArea(ptFlasherInputParameter ptAppParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	tBootBlockSrcType tSrcType;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;


	tSrcType = ptAppParams->uParameter.tGetEraseArea.ptDeviceDescription->tSourceTyp;
	ulStartAdr = ptAppParams->uParameter.tGetEraseArea.ulStartAdr;
	ulEndAdr = ptAppParams->uParameter.tGetEraseArea.ulEndAdr;

	if( ulStartAdr>=ulEndAdr )
	{
		uprintf("! first address is greater or equal than last address.");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		uprintf(". Device :");
		switch(tSrcType)
		{
		case BootBlockSrcType_SPI:
			/*  use SPI flash */
			uprintf("SPI flash\n");
			tResult = spi_getEraseArea(&(ptAppParams->uParameter.tGetEraseArea));
			break;

		default:
			/*  unknown boot device */
			uprintf("unknown\n");
			uprintf("! illegal device id specified\n");
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
	}

	return tResult;
}


/* ------------------------------------- */
