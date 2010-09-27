/***************************************************************************
 *   Copyright (C) 2010 by Hilscher GmbH                                   *
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

#include "flasher_parflash.h"

#include "uprintf.h"


#if CFG_DEBUGMSG!=0

	/* show all messages by default */
	static unsigned long s_ulCurSettings = 0xffffffff;

	#define DEBUGZONE(n)  (s_ulCurSettings&(0x00000001<<(n)))

	//
	// These defines must match the ZONE_* defines
	//
	#define DBG_ZONE_ERROR      0
	#define DBG_ZONE_WARNING    1
	#define DBG_ZONE_FUNCTION   2
	#define DBG_ZONE_INIT       3
	#define DBG_ZONE_VERBOSE    7

	#define ZONE_ERROR          DEBUGZONE(DBG_ZONE_ERROR)
	#define ZONE_WARNING        DEBUGZONE(DBG_ZONE_WARNING)
	#define ZONE_FUNCTION       DEBUGZONE(DBG_ZONE_FUNCTION)
	#define ZONE_INIT           DEBUGZONE(DBG_ZONE_INIT)
	#define ZONE_VERBOSE        DEBUGZONE(DBG_ZONE_VERBOSE)

	#define DEBUGMSG(cond,printf_exp) ((void)((cond)?(uprintf printf_exp),1:0))
#else  // DEBUG
	#define DEBUGMSG(cond,printf_exp) ((void)0)
#endif // DEBUG



#if ASIC_TYP==500 || ASIC_TYP==100 || ASIC_TYP==50
static void setup_flash_srb(const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits)
{
	unsigned long *pulFlashCtrl = (unsigned long*)(HOSTADR(extsram0_ctrl));
	unsigned long  ulRegValue;


	ulRegValue  = (DEFAULT_PREPAUSE   << HOSTSRT(extsram0_ctrl_WSPrePauseExtMem0);
	ulRegValue |= (DEFAULT_POSTPAUSE  << HOSTSRT(extsram0_ctrl_WSPostPauseExtMem0);
	ulRegValue |= (DEFAULT_WAITSTATES << HOSTSRT(extsram0_ctrl_WSExtMem0);

	switch(tBits)
	{
	case BUS_WIDTH_8Bit:
		break;

	case BUS_WIDTH_16Bit:
		ulRegValue |= 0x01 << HOSTSRT(extsram0_ctrl_WidthExtMem0);
		break;

	case BUS_WIDTH_32Bit:
		ulRegValue |= 0x02 << HOSTSRT(extsram0_ctrl_WidthExtMem0);
		break;
	}

	*pulFlashCtrl = ulRegValue;
}
#elif ASIC_TYP==10
static void setup_flash(const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits)
{
	unsigned long ulValue;
	unsigned int uiChipSelect;


	/* Get the chipselect. */
	uiChipSelect = ptCfg->uiChipSelect;

	/* Check the parameters. */
	if( tBits!=BUS_WIDTH_8Bit && tBits!=BUS_WIDTH_16Bit )
	{
		DEBUGMSG(ZONE_ERROR, ("Invalid bus width! Must be 0 or 1, but is %d.\n", tBits));
	}
	else if( uiChipSelect>3 )
	{
		DEBUGMSG(ZONE_ERROR, ("Invalid chipselect! Must be 0, 1, 2 or 3, but is %d.\n", uiChipSelect));
	}
	else
	{
		/* Set the memory interface configuration. */
		ulValue = tBits << SRT_NX10_extsram0_ctrl_dwidth;
		/* unlock access key */
		ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
		/* configure the hif pins */
		ptHifIoCtrlArea->ulHif_io_cfg = ulValue << SRT_NX10_hif_io_cfg_hif_mi_cfg;

		ulValue  = DFLT_VAL_NX10_extsram0_ctrl_ws << SRT_NX10_extsram0_ctrl_ws;
		ulValue |= DFLT_VAL_NX10_extsram0_ctrl_p_pre << SRT_NX10_extsram0_ctrl_p_pre;
		ulValue |= DFLT_VAL_NX10_extsram0_ctrl_p_post << SRT_NX10_extsram0_ctrl_p_post;
		ulValue |= tBits << SRT_NX10_extsram0_ctrl_dwidth;
		ptExtAsyncmemCtrlArea->aulExtsram_ctrl[uiChipSelect] = ulValue;
	}
}
#endif



NETX_CONSOLEAPP_RESULT_T parflash_detect(CMD_PARAMETER_DETECT_T *ptParameter)
{
	FLASH_DEVICE_T tFlashDevice;
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iRes;
#if defined(DEBUG)
	int iCnt;
	char acCfiId[16];
#endif
	unsigned int uiUnit;
	unsigned int uiChipSelect;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;


	/* Assume success. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* Get the base address and setup routine. */
	uiUnit = ptParameter->uSourceParameter.tParFlash.uiUnit;
	uiChipSelect = ptParameter->uSourceParameter.tParFlash.uiChipSelect;

#if ASIC_TYP==500 || ASIC_TYP==100 || ASIC_TYP==50
	tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram0);
	tFlashDevice.pfnSetup = setup_flash_srb;
#elif ASIC_TYP==10
	if( uiUnit!=0 )
	{
		DEBUGMSG(ZONE_ERROR, ("Invalid unit number: %d\n", uiUnit));
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else if( uiChipSelect>3 )
	{
		DEBUGMSG(ZONE_ERROR, ("Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect));
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		switch(uiChipSelect)
		{
		case 0:
			tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram0);
			break;
		case 1:
			tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram1);
			break;
		case 2:
			tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram2);
			break;
		case 3:
			tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram3);
			break;
		}
		tFlashDevice.pfnSetup = setup_flash;
	}
#endif

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* Try to detect the flash. */
		DEBUGMSG(ZONE_VERBOSE, (". Detecting CFI flash at 0x%08x...\n", tFlashDevice.pbFlashBase));
		iRes = CFI_IdentifyFlash(&tFlashDevice, &(ptParameter->uSourceParameter.tParFlash));
		if( iRes==0 )
		{
			/*  failed to identify flash */
			uprintf("! failed to detect CFI flash\n");
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
#if defined(DEBUG)
			/*  Show the device identifier. */
			for(iCnt=0; iCnt<16; ++iCnt)
			{
				acCfiId[iCnt] = tFlashDevice.szIdent[iCnt];
			}
			acCfiId[16] = 0x00;
			DEBUGMSG(ZONE_VERBOSE, (". found device '%s'\n", acCfiId));
#endif

			/* Set the result data. */
			ptDeviceDescription = ptParameter->ptDeviceDescription;
			ptDeviceDescription->fIsValid = 1;
			ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
			ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
			ptDeviceDescription->tSourceTyp = BUS_ParFlash;

			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}
	}

	return tResult;
}

