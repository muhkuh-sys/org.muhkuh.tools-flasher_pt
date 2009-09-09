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

#include "bootblock.h"

/*  parallel flash on extension bus */
#include "flasher_ext.h"
/*  serial eeprom on i2c */
#include "flasher_i2c.h"
/*  serial flash on spi */
#include "flasher_spi.h"
/*  parallel flash on sram bus */
#include "flasher_srb.h"

#include "uprintf.h"

#include "main.h"

/* ------------------------------------- */
/*  local prototypes */

NETX_CONSOLEAPP_RESULT_T opMode_flash (ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_erase (ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_read  (ptFlasherInputParameter ptAppParams);
NETX_CONSOLEAPP_RESULT_T opMode_verify(ptFlasherInputParameter ptAppParams);

/* ------------------------------------- */

NETX_CONSOLEAPP_RESULT_T netx_consoleapp_main(NETX_CONSOLEAPP_PARAMETER_T *ptTestParam)
{
        NETX_CONSOLEAPP_RESULT_T tTestResult;
        ptFlasherInputParameter ptAppParams;
        unsigned long ulParamVersion;
        tOperationMode tOpMode;


        /*  switch off sys led */
        setRdyRunLed(RDYRUN_LED_OFF);

        /*  say hi */
        uprintf("\f\n\n\n\nFlasher v");
        uprintf(FLASHER_VERSION_ALL);
        uprintf("\n\n");
        uprintf("Copyright (C) 2008 C.Thelen (cthelen@hilscher.com) and M.Trensch.\n");
        uprintf("There is NO warranty.  You may redistribute this software\n");
        uprintf("under the terms of the GNU Library General Public License.\n");
        uprintf("For more information about these matters, see the files named COPYING.\n");

        uprintf("\n");
        uprintf(". Data pointer:    0x$8\n", (unsigned long)ptTestParam);
        uprintf(". Init parameter:  0x$8\n", (unsigned long)ptTestParam->pvInitParams);
        uprintf("\n");

        /*  get application parameters */
        ptAppParams = (ptFlasherInputParameter)ptTestParam->pvInitParams;

        /*  show application parameters */
        uprintf(". Application parameters:\n");
        uprintf(". parameter version: 0x$8\n", ptAppParams->ulParamVersion);
        uprintf(". operation mode:    0x$8\n", ptAppParams->ulOperationMode);
        uprintf(". data start:        0x$8\n", (unsigned long)ptAppParams->pbData);
        uprintf(". data size:         0x$8\n", ptAppParams->ulDataByteSize);
        uprintf(". boot type:         0x$8\n", ptAppParams->ulBootBlockSrcType);
        uprintf(". device offset:     0x$8\n", ptAppParams->ulDstDeviceOffset);
        uprintf("\n");

        /*  check parameter version */
        ulParamVersion = ptAppParams->ulParamVersion;
        if( ulParamVersion!=0x00010000 )
        {
                uprintf("! unknown parameter version: $4.$4. Expected 0001.0000!\n", ulParamVersion>>16, ulParamVersion&0xffff);
                setRdyRunLed(RDYRUN_LED_RED);
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        /*  check offset, non 0 is not suppoerted yet */
        if( ptAppParams->ulDstDeviceOffset!=0 )
        {
                uprintf("! a device offset greater than 0 is not supported yet!\n");
                setRdyRunLed(RDYRUN_LED_RED);
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        /*  run operation */
        tOpMode = (tOperationMode)ptAppParams->ulOperationMode;
        switch( tOpMode )
        {
        case OperationMode_Flash:
                uprintf(". Operation Mode: Flash\n");
                tTestResult = opMode_flash(ptAppParams);
                break;

        case OperationMode_Erase:
                uprintf(". Operation Mode: Erase\n");
                tTestResult = opMode_erase(ptAppParams);
                break;

        case OperationMode_Read:
                uprintf(". Operation Mode: Read\n");
                tTestResult = opMode_read(ptAppParams);
                break;

        case OperationMode_Verify:
                uprintf(". Operation Mode: Verify\n");
                tTestResult = opMode_verify(ptAppParams);
                break;

        default:
                uprintf("! unknown operation mode: $8\n", tOpMode);
                setRdyRunLed(RDYRUN_LED_RED);
                tTestResult = NETX_CONSOLEAPP_RESULT_ERROR;
        }

        if( tTestResult==NETX_CONSOLEAPP_RESULT_OK )
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

        return tTestResult;
}

/* ------------------------------------- */


NETX_CONSOLEAPP_RESULT_T opMode_flash(ptFlasherInputParameter ptAppParams)
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
                tResult = spi_flash(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_SRamBus:
                /*  use parallel flash on SRam bus */
                uprintf("SRam Bus parflash\n");
                tResult = srb_flash(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_SPI:
                /*  use SPI flash */
                uprintf("SPI flash\n");
                tResult = spi_flash(ptAppParams->pbData, ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_I2C:
                /*  use I2C eeprom */
                uprintf("I2C eeprom\n");
                tResult = i2c_flash(ptAppParams->pbData, ptAppParams->ulDataByteSize);
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
                tResult = ext_flash(ptAppParams->pbData, ptAppParams->ulDataByteSize);
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
        tBootBlockSrcType tBBSrcType;


        tBBSrcType = (tBootBlockSrcType)ptAppParams->ulBootBlockSrcType;

        uprintf(". Device :");
        switch(tBBSrcType)
        {
        case BootBlockSrcType_OldStyle:
                /*  old style bootblock, not supported for this operation */
                uprintf("old style device id, not supported for erase mode!\n");
                tResult = NETX_CONSOLEAPP_RESULT_ERROR;
                break;

        case BootBlockSrcType_SRamBus:
                /*  use parallel flash on SRam bus */
                uprintf("SRam Bus parflash\n");
                tResult = srb_erase(ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_SPI:
                /*  use SPI flash */
                uprintf("SPI flash\n");
                tResult = spi_erase(ptAppParams->ulDataByteSize);
                break;

        case BootBlockSrcType_I2C:
                /*  use I2C eeprom */
                uprintf("I2C eeprom\n");
                tResult = i2c_erase(ptAppParams->ulDataByteSize);
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
                tResult = ext_erase(ptAppParams->ulDataByteSize);
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
