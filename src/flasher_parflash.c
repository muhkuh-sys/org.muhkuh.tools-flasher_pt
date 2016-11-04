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

#include "asic_types.h"
#include "progress_bar.h"
#include "uprintf.h"
#if ASIC_TYP==ASIC_TYP_NETX4000_RELAXED
#include "pl353_nor.h"
#endif

#if CFG_DEBUGMSG!=0

	/* show all messages by default */
	static unsigned long s_ulCurSettings = 0xffffffff;

	#define DEBUGZONE(n)  (s_ulCurSettings&(0x00000001<<(n)))

	/* NOTE: These defines must match the ZONE_* defines. */
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
#else  /* CFG_DEBUGMSG!=0 */
	#define DEBUGMSG(cond,printf_exp) ((void)0)
#endif /* CFG_DEBUGMSG!=0 */



#if ASIC_TYP==ASIC_TYP_NETX500 || ASIC_TYP==ASIC_TYP_NETX100 || ASIC_TYP==ASIC_TYP_NETX50
/* in: ptCfg->uiChipSelect
   out: -
   */
static void setup_flash_srb(const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits)
{
	HOSTDEF(ptExtAsyncmemCtrlArea);
	unsigned long  ulRegValue;


	ulRegValue  = DEFAULT_PREPAUSE   << HOSTSRT(extsram0_ctrl_WSPrePauseExtMem0);
	ulRegValue |= DEFAULT_POSTPAUSE  << HOSTSRT(extsram0_ctrl_WSPostPauseExtMem0);
	ulRegValue |= DEFAULT_WAITSTATES << HOSTSRT(extsram0_ctrl_WSExtMem0);

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

	//ptNetxControlledGlobalRegisterBlock2Area->aulExtsram_ctrl[ptCfg->uiChipSelect] = ulRegValue;
	ptExtAsyncmemCtrlArea->aulExtsram_ctrl[ptCfg->uiChipSelect] = ulRegValue;
}

/* 
0x00103610-361c Extension Bus Configuration Chip Select 0/1/2/3

cs_en (bit 0) = 1
16 bit mode   = 0/1
nWr_mode      = 0
ds_mode       = 0
nRd_mode      = 0
wait_en       = 0
wait_polarity = 0
Trdwrcyc      = 15
TrdWroff      = 15
Twron         = 1
Trdon         = 1
Tcson         = 0
Tadrhold      = 0
Talewidt      = 0
*/
/* in: ptCfg->uiChipSelect
   out: -
   */

static void setup_flash_ext(const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits)
{
	HOSTDEF(ptNetxControlledGlobalRegisterBlock2Area);
	unsigned long ulIoRegMode0;
	unsigned long ulExtBusConfig;

	if( ptCfg->uiChipSelect > 3 )
	{
		uprintf("!setup_flash_ext: Invalid chipselect! Must be 0, 1, 2 or 3, but is %d.\n", ptCfg->uiChipSelect);
	}
	else
	{
		switch(tBits)
		{
		case BUS_WIDTH_8Bit:
			ulIoRegMode0   = 0xFFFFFFFF;
			ulExtBusConfig = 0x0012F781;
			break;
	
		case BUS_WIDTH_16Bit:
			ulIoRegMode0   = 0xFFFFFFFF;
			ulExtBusConfig = 0x0012F783;
			break;
		
		default:
			uprintf("!setup_flash_ext: Invalid bus width! Must be 0 or 1, but is %d.\n", tBits);
			return;
		}
		
		
		ptNetxControlledGlobalRegisterBlock2Area->ulIo_reg_mode0        = ulIoRegMode0;
		ptNetxControlledGlobalRegisterBlock2Area->ulIo_reg_mode1        = 0x000E7EFF;
	
		ptNetxControlledGlobalRegisterBlock2Area->ulIf_conf1            = 0x10000000;
		/* ptNetXGlobalRegBlock2Area->ul_if_conf2      = 0x60000000; */
	
		ptNetxControlledGlobalRegisterBlock2Area->ulIo_reg_drv_en0      = 0xFFFFFFFF;
		ptNetxControlledGlobalRegisterBlock2Area->ulIo_reg_drv_en1      = 0x000E7EFF;
	
		//ptNetXGlobalRegBlock2Area->aul_ext_bus_config[0]  = ulExtBusConfig;
		switch (ptCfg->uiChipSelect)
		{
		case 0:
			ptNetxControlledGlobalRegisterBlock2Area->ulExp_bus_reg = ulExtBusConfig;
			break;
			
		case 1:
			ptNetxControlledGlobalRegisterBlock2Area->ulDpmas_ext_config1 = ulExtBusConfig;
			break;
			
		case 2:
			ptNetxControlledGlobalRegisterBlock2Area->ulDpmas_ext_config2 = ulExtBusConfig;
			break;
			
		case 3:
			ptNetxControlledGlobalRegisterBlock2Area->ulDpmas_ext_config3 = ulExtBusConfig;
			break;
		}
	}
}

#elif ASIC_TYP==ASIC_TYP_NETX10
/* in: ptCfg->uiChipSelect
   out: -
   */
static void setup_flash(const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits)
{
	HOSTDEF(ptAsicCtrlArea);
	HOSTDEF(ptHifIoCtrlArea);
	HOSTDEF(ptExtAsyncmemCtrlArea);
	unsigned long ulValue;
	unsigned int uiChipSelect;


	/* Get the chipselect. */
	uiChipSelect = ptCfg->uiChipSelect;

	/* Check the parameters. */
	if( tBits!=BUS_WIDTH_8Bit && tBits!=BUS_WIDTH_16Bit )
	{
		uprintf("!setup_flash: Invalid bus width! Must be 0 or 1, but is %d.\n", tBits);
	}
	else if( uiChipSelect>3 )
	{
		uprintf("!setup_flash: Invalid chipselect! Must be 0, 1, 2 or 3, but is %d.\n", uiChipSelect);
	}
	else
	{
		/* Set the memory interface configuration. */
		ulValue = ((unsigned long) tBits) << SRT_NX10_hif_io_cfg_hif_mi_cfg;
		/* unlock access key */
		ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
		/* configure the hif pins */
		ptHifIoCtrlArea->ulHif_io_cfg = ulValue;

		ulValue  = DFLT_VAL_NX10_extsram0_ctrl_ws << SRT_NX10_extsram0_ctrl_ws;
		ulValue |= DFLT_VAL_NX10_extsram0_ctrl_p_pre << SRT_NX10_extsram0_ctrl_p_pre;
		ulValue |= DFLT_VAL_NX10_extsram0_ctrl_p_post << SRT_NX10_extsram0_ctrl_p_post;
		ulValue |= ((unsigned long) tBits) << SRT_NX10_extsram0_ctrl_dwidth;
		ptExtAsyncmemCtrlArea->aulExtsram_ctrl[uiChipSelect] = ulValue;
	}
}

#elif ASIC_TYP==ASIC_TYP_NETX4000_RELAXED
static void setup_flash_rap_nor(const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits)
{
	MEMORY_WIDTH_T tBusWidth = tBits == BUS_WIDTH_16Bit? MEMORY_WIDTH_16Bit:MEMORY_WIDTH_08Bit;
	setup_flash_nor_pl353(ptCfg->uiChipSelect, tBusWidth);
}

#endif



NETX_CONSOLEAPP_RESULT_T parflash_detect(CMD_PARAMETER_DETECT_T *ptParameter)
{
	FLASH_DEVICE_T *ptFlashDevice;
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

	ptDeviceDescription = ptParameter->ptDeviceDescription;
	ptFlashDevice = &(ptDeviceDescription->uInfo.tParFlash);

#if ASIC_TYP==ASIC_TYP_NETX500 || ASIC_TYP==ASIC_TYP_NETX100 || ASIC_TYP==ASIC_TYP_NETX50
/*
	in: uiUnit, uiChipSelect
	out: ptFlashDevice->pucFlashBase
	     ptFlashDevice->pfnSetup
*/
	if( uiUnit==0 )
	{
		if( uiChipSelect>3 )
		{
			uprintf("! Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			switch(uiChipSelect)
			{
			case 0:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram0);
				break;
			case 1:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram1);
				break;
			case 2:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram2);
				break;
			case 3:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram3);
				break;
			}
			ptFlashDevice->pfnSetup = setup_flash_srb;
		}
	}
	else if( uiUnit==1 )
	{
		if( uiChipSelect>3 )
		{
			uprintf("! Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			//ptFlashDevice->pucFlashBase = (unsigned char*)(HOSTADDR(hif_ahbls6)+0x02000000*uiChipSelect);
			
			switch(uiChipSelect)
			{
			case 0:
				ptFlashDevice->pucFlashBase = (unsigned char*)(HOSTADDR(pci_ahbls6)+0x02000000*0);
				break;
			case 1:
				ptFlashDevice->pucFlashBase = (unsigned char*)(HOSTADDR(pci_ahbls6)+0x02000000*1);
				break;
			case 2:
				ptFlashDevice->pucFlashBase = (unsigned char*)(HOSTADDR(pci_ahbls6)+0x02000000*2);
				break;
			case 3:
				ptFlashDevice->pucFlashBase = (unsigned char*)(HOSTADDR(pci_ahbls6)+0x02000000*3);
				break;
			}
			
			ptFlashDevice->pfnSetup = setup_flash_ext;
		}
	}
	else
	{
		uprintf("! Invalid unit number: %d\n", uiUnit);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
#elif ASIC_TYP==ASIC_TYP_NETX10
	if( uiUnit!=0 )
	{
		uprintf("! Invalid unit number: %d\n", uiUnit);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else if( uiChipSelect>3 )
	{
		uprintf("! Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		switch(uiChipSelect)
		{
		case 0:
			ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram0);
			break;
		case 1:
			ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram1);
			break;
		case 2:
			ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram2);
			break;
		case 3:
			ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(extsram3);
			break;
		}
		ptFlashDevice->pfnSetup = setup_flash;
	}
	
#elif ASIC_TYP==ASIC_TYP_NETX4000_RELAXED
#if 0
	if( uiUnit==0 )
	{
		if( uiChipSelect>3 )
		{
			uprintf("! Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			switch(uiChipSelect)
			{
			case 0:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(mem_extsram_cs0_base);
				break;
			case 1:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(mem_extsram_cs1_base);
				break;
			case 2:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(mem_extsram_cs2_base);
				break;
			case 3:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(mem_extsram_cs3_base);
				break;
			}
			/* TODO ptFlashDevice->pfnSetup = setup_flash_srb; */
		}
	}
	else if( uiUnit==1 )
	{
		if( uiChipSelect>3 )
		{
			uprintf("! Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			//ptFlashDevice->pucFlashBase = (unsigned char*)(HOSTADDR(hif_ahbls6)+0x02000000*uiChipSelect);
			
			switch(uiChipSelect)
			{
			case 0:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(hif_extsram_cs0_base);
				break;
			case 1:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(hif_extsram_cs1_base);
				break;
			case 2:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(hif_extsram_cs2_base);
				break;
			case 3:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADR(hif_extsram_cs3_base);
				break;
			}
			
			/* TODO ptFlashDevice->pfnSetup = setup_flash_ext; */
		}
	}
	else 
#endif
	if( uiUnit==2 )
	{
		if( uiChipSelect>1 )
		{
			uprintf("! Invalid chipselect for unit %d: %d\n", uiUnit, uiChipSelect);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			switch(uiChipSelect)
			{
			case 0:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(NX2RAP_extsram0);
				break;
			case 1:
				ptFlashDevice->pucFlashBase = (unsigned char*)HOSTADDR(NX2RAP_extsram1);
				break;
			}
			
			ptFlashDevice->pfnSetup = setup_flash_rap_nor;
		}
	}
	else
	{
		uprintf("! Invalid unit number: %d\n", uiUnit);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
#else
	uiUnit = uiUnit; /* avoid 'set but not used' warning */
	uiChipSelect = uiChipSelect;
	uprintf("! Unknown chip type or parallel flash not supported on this chip!\n");
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;
#endif

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* Try to detect the flash. */
		uprintf(". Detecting CFI flash at 0x%08x...\n", ptFlashDevice->pucFlashBase);
		iRes = CFI_IdentifyFlash(ptFlashDevice, &(ptParameter->uSourceParameter.tParFlash));
		if( iRes==0 )
		{
			/*  failed to identify flash */
			uprintf("! failed to detect CFI flash\n");

			/* clear the result data */
			memset(ptDeviceDescription, 0, sizeof(DEVICE_DESCRIPTION_T));

			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
#if defined(DEBUG)
			/*  Show the device identifier. */
			for(iCnt=0; iCnt<16; ++iCnt)
			{
				acCfiId[iCnt] = ptFlashDevice->szIdent[iCnt];
			}
			acCfiId[16] = 0x00;
			DEBUGMSG(ZONE_VERBOSE, (". found device '%s'\n", acCfiId));
#endif

			/* Set the result data. */
			ptDeviceDescription->fIsValid = 1;
			ptDeviceDescription->sizThis = sizeof(DEVICE_DESCRIPTION_T);
			ptDeviceDescription->ulVersion = FLASHER_INTERFACE_VERSION;
			ptDeviceDescription->tSourceTyp = BUS_ParFlash;

			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}
	}

	return tResult;
}


/* end address is exclusive */

NETX_CONSOLEAPP_RESULT_T parflash_getEraseArea(CMD_PARAMETER_GETERASEAREA_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const FLASH_DEVICE_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	const SECTOR_INFO_T *ptSectorStart;
	const SECTOR_INFO_T *ptSectorEnd;
	unsigned long ulEraseBlockStart;
	unsigned long ulEraseBlockEnd;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr  = ptParameter->ulEndAdr;

	/* Look for the erase block which contains the start address. */
	ptSectorStart = cfi_find_matching_sector(ptFlashDescription, ulStartAdr);
	ptSectorEnd = cfi_find_matching_sector(ptFlashDescription, ulEndAdr-1);

	if( ptSectorStart!=NULL && ptSectorEnd!=NULL )
	{
		ulEraseBlockStart = ptSectorStart->ulOffset;
		ulEraseBlockEnd   = ptSectorEnd->ulOffset + ptSectorEnd->ulSize;

		DEBUGMSG(ZONE_VERBOSE, ("requested area: [0x%08x, 0x%08x[\n", ulStartAdr, ulEndAdr));
		DEBUGMSG(ZONE_VERBOSE, ("erase area:     [0x%08x, 0x%08x[\n", ulEraseBlockStart, ulEraseBlockEnd));

		ptParameter->ulStartAdr = ulEraseBlockStart;
		ptParameter->ulEndAdr = ulEraseBlockEnd;

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		uprintf("! Can not find start/end address in sector table!\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}

	/* All ok! */
	return tResult;
}


NETX_CONSOLEAPP_RESULT_T parflash_isErased(const CMD_PARAMETER_ISERASED_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const FLASH_DEVICE_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	ADR_T tCnt;
	ADR_T tEnd;
	unsigned long ulProgressBarPosition;
	unsigned long ulErased;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;

	tResult = NETX_CONSOLEAPP_RESULT_OK;
	uprintf("# Checking if empty...\n");

	progress_bar_init(ulEndAdr-ulStartAdr);

	/* Get the start address. */
	tCnt.puc  = ptFlashDescription->pucFlashBase;
	tCnt.puc += ulStartAdr;

	/* Get the end address. */
	tEnd.puc  = ptFlashDescription->pucFlashBase;
	tEnd.puc += ulEndAdr;

	/* Loop over the complete area. */
	ulErased = 0xffU;
	while( tCnt.puc<tEnd.puc )
	{
		ulErased &= *(tCnt.puc++);
		if( ulErased!=0xff )
		{
			break;
		}

		/* Show progress every 64K bytes. */
		if( (tCnt.ul&0xffff)==0 )
		{
			ulProgressBarPosition  = (unsigned long)(tCnt.puc - ptFlashDescription->pucFlashBase);
			ulProgressBarPosition -= ulStartAdr;
			progress_bar_set_position(ulProgressBarPosition);
		}
	}

	progress_bar_finalize();
	
	if( ulErased==0xff )
	{
		uprintf(". CLEAN! The area is erased.\n");
	}
	else
	{
		uprintf(". DIRTY! The area is not erased.\n");
	}
	ptConsoleParams->pvReturnMessage = (void*)ulErased;


	return tResult;
}


static NETX_CONSOLEAPP_RESULT_T parflash_unlock(const FLASH_DEVICE_T *ptFlashDev)
{
	FLASH_ERRORS_E tFlashError;
	NETX_CONSOLEAPP_RESULT_T tResult;
	DEBUGMSG(ZONE_FUNCTION, ("+parflash_unlock(): ptFlashDev=0x%08x\n", ptFlashDev));

	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* unlock the complete flash */
	tFlashError = ptFlashDev->tFlashFunctions.pfnUnlock(ptFlashDev);
	if( tFlashError!=eFLASH_NO_ERROR )
	{
		/* failed to unlock all sectors */
		uprintf(". failed to unlock all flash sectors\n");
		/* showPflashError(tFlashError);*/
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-parflash_unlock(): tResult=0x%08x\n", tResult));

	return tResult;
}


static NETX_CONSOLEAPP_RESULT_T parflash_compare(
	const FLASH_DEVICE_T *ptFlashDescription, 
	unsigned long ulStartAdr, unsigned long ulEndAdr, 
	const unsigned char* pucDataStartAdr);
	
NETX_CONSOLEAPP_RESULT_T parflash_flash(const CMD_PARAMETER_FLASH_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	const unsigned char *pucDataStartAdr;
	unsigned long ulFlashStartAdr;
	unsigned long ulDataByteSize;
	
	unsigned long ulProgressBarPosition;
	
	const FLASH_DEVICE_T *ptFlashDescription;
	const SECTOR_INFO_T *ptSector;
	unsigned long ulSectorOffset;
	
	unsigned long ulChunkSize;
	FLASH_ERRORS_E tFlashError;

	ulFlashStartAdr = ptParameter->ulStartAdr;
	ulDataByteSize  = ptParameter->ulDataByteSize;
	pucDataStartAdr = ptParameter->pucData;
	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);

	tResult = parflash_unlock(ptFlashDescription);
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		uprintf("#Writing...\n");
		progress_bar_init(ulDataByteSize);
		ulProgressBarPosition = 0;
		
		while( ulDataByteSize!=0 )
		{
			/* Split the data by erase sectors. */
			ptSector = cfi_find_matching_sector(ptFlashDescription, ulFlashStartAdr);
			if( ptSector==NULL )
			{
				uprintf("Can not find sector in table!\n");
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}
			ulSectorOffset = ulFlashStartAdr - ptSector->ulOffset;
			ulChunkSize = ptSector->ulSize - ulSectorOffset;
			if( ulChunkSize>ulDataByteSize )
			{
				ulChunkSize = ulDataByteSize;
			}
	
			DEBUGMSG(ZONE_VERBOSE, ("Flashing [0x%08x, 0x%08x[\n", ulFlashStartAdr, ulFlashStartAdr+ulChunkSize));
			tFlashError = ptFlashDescription->tFlashFunctions.pfnProgram(ptFlashDescription, ulFlashStartAdr, ulChunkSize, pucDataStartAdr);
			if( tFlashError!=eFLASH_NO_ERROR )
			{
				/* failed to program the sector */
				uprintf("Failed to program flash sector!\n");
				/* showPflashError(tFlashError); */
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}
			
			ulFlashStartAdr += ulChunkSize;
			pucDataStartAdr += ulChunkSize;
			ulDataByteSize -= ulChunkSize;
			ulProgressBarPosition += ulChunkSize;
			
			progress_bar_set_position(ulProgressBarPosition);
		}
		progress_bar_finalize();
	}
		
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		ulFlashStartAdr = ptParameter->ulStartAdr;
		ulDataByteSize  = ptParameter->ulDataByteSize;
		pucDataStartAdr = ptParameter->pucData;

		tResult = parflash_compare(ptFlashDescription, ulFlashStartAdr, ulFlashStartAdr + ulDataByteSize, pucDataStartAdr);
	}
	return tResult;
}

NETX_CONSOLEAPP_RESULT_T parflash_erase(const CMD_PARAMETER_ERASE_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	unsigned long ulEraseStartAdr;
	unsigned long ulEraseEndAdr;
	unsigned long ulProgressBarPosition;
	const FLASH_DEVICE_T *ptFlashDescription;
	const SECTOR_INFO_T *ptSectors;
	FLASH_ERRORS_E tFlashError;
	size_t sizCnt;

	ulEraseStartAdr = ptParameter->ulStartAdr;
	ulEraseEndAdr   = ptParameter->ulEndAdr;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);

	tResult = NETX_CONSOLEAPP_RESULT_OK;
	/* Split the data by erase sectors. */
	sizCnt = cfi_find_matching_sector_index(ptFlashDescription, ulEraseStartAdr);
	if( sizCnt==0xffffffffU )
	{
		uprintf("! Can not find sector in table!\n");
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		tResult = parflash_unlock(ptFlashDescription);
	}
	
	if (tResult == NETX_CONSOLEAPP_RESULT_OK)
	{
		uprintf("#Erasing...\n");
		progress_bar_init(ulEraseEndAdr - ulEraseStartAdr);
		ulProgressBarPosition = 0;
		
		ptSectors = ptFlashDescription->atSectors;
		do
		{
			DEBUGMSG(ZONE_VERBOSE, (". Erasing sector %d: [0x%08x, 0x%08x[\n", 
				sizCnt, ptSectors[sizCnt].ulOffset,ptSectors[sizCnt].ulOffset+ptSectors[sizCnt].ulSize));
			tFlashError = ptFlashDescription->tFlashFunctions.pfnErase(ptFlashDescription, sizCnt);
			if( tFlashError!=eFLASH_NO_ERROR )
			{
				/* failed to erase the sector */
				uprintf(". failed to erase flash sector %d\n", sizCnt);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}
			
			/* Show progress */
			ulProgressBarPosition += ptSectors[sizCnt].ulSize;
			progress_bar_set_position(ulProgressBarPosition);
			
			/* Next sector. */
			++sizCnt;
			
		} while( sizCnt<ptFlashDescription->ulSectorCnt && ptSectors[sizCnt].ulOffset<ulEraseEndAdr );
		uprintf(". Erase complete.\n");
		progress_bar_finalize();
	}
	return tResult;
}



NETX_CONSOLEAPP_RESULT_T parflash_read(const CMD_PARAMETER_READ_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;

	const FLASH_DEVICE_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned char *pucDataStartAdr;

	CADR_T tSrc;
	ADR_T tDst;
	CADR_T tSrcEnd;
	
	unsigned long ulProgressBarPosition;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;
	pucDataStartAdr = ptParameter->pucData;
	
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	uprintf("#Reading from flash...\n");

	progress_bar_init(ulEndAdr-ulStartAdr);
	ulProgressBarPosition = 0;
	
	/* Get the source start address. */
	tSrc.puc  = ptFlashDescription->pucFlashBase;
	tSrc.puc += ulStartAdr;

	/* Get the source end address. */
	tSrcEnd.puc  = ptFlashDescription->pucFlashBase;
	tSrcEnd.puc += ulEndAdr;

	/* Get the dest address */
	tDst.puc = (unsigned char*) pucDataStartAdr;

	/* Loop over the complete area. */
	while( tSrc.puc<tSrcEnd.puc )
	{
		*tDst.puc++ = *tSrc.puc++;
		++ulProgressBarPosition;

		/* Show progress every 64K bytes. */
		if( (ulProgressBarPosition&0xffff)==0 )
		{
			progress_bar_set_position(ulProgressBarPosition);
		}
	}
	progress_bar_finalize();
	
	uprintf(". done\n");
	
	return tResult;
}

#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T parflash_sha1(const CMD_PARAMETER_CHECKSUM_T *ptParameter, SHA_CTX *ptSha1Context)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	
	const FLASH_DEVICE_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned long ulOffset;
	unsigned long ulBlockSize;
	const void *pvFlashAddr;
	
	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;

	tResult = NETX_CONSOLEAPP_RESULT_OK;
	
	uprintf("# Calculating checksum...\n");
	ulOffset = 0;
	progress_bar_init(ulEndAdr-ulStartAdr);
	while (ulOffset < ulEndAdr - ulStartAdr)
	{
		ulBlockSize = ulEndAdr - ulStartAdr - ulOffset;
		if (ulBlockSize > 0x10000) 
		{
			ulBlockSize = 0x10000;
		}
		
		pvFlashAddr = (const void*)(ptFlashDescription->pucFlashBase + ulStartAdr + ulOffset);
		SHA1_Update(ptSha1Context, pvFlashAddr, ulBlockSize);
		
		ulOffset += ulBlockSize;
		
		progress_bar_set_position(ulOffset);
		
	}
	
	uprintf(". hash done\n");
	
	return tResult;
}
#endif

/* return value: 
   NETX_CONSOLEAPP_RESULT_OK: equal, 
   NETX_CONSOLEAPP_RESULT_ERROR: not equal 
 */
static NETX_CONSOLEAPP_RESULT_T parflash_compare(const FLASH_DEVICE_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, const unsigned char* pucDataStartAdr)
{
	/* src/srcEnd point to Flash; dst, points to RAM */
	CADR_T tSrc;
	CADR_T tDst;
	CADR_T tSrcEnd;
	
	unsigned long ulProgressBarPosition;

	uprintf("# Verifying...\n");

	/* Get the source start address. */
	tSrc.puc  = ptFlashDescription->pucFlashBase;
	tSrc.puc += ulStartAdr;

	/* Get the source end address. */
	tSrcEnd.puc  = ptFlashDescription->pucFlashBase;
	tSrcEnd.puc += ulEndAdr;

	/* Get the dest address */
	tDst.puc = (const unsigned char*) pucDataStartAdr;

	progress_bar_init(ulEndAdr-ulStartAdr);
	ulProgressBarPosition = 0;
	
	/* Loop over the complete area. */
	while( tSrc.puc<tSrcEnd.puc )
	{
		if (*tDst.puc != *tSrc.puc) 
		{
			uprintf("! verify error at address 0x%08x. buffer: 0x%02x, flash: 0x%02x.\n", tSrc.ul, *tDst.puc, *tSrc.puc);
			return NETX_CONSOLEAPP_RESULT_ERROR;
		}
		++tDst.puc;
		++tSrc.puc;
		++ulProgressBarPosition;

		/* Show progress every 64K bytes. */
		if( (ulProgressBarPosition&0xffff)==0 )
		{
			progress_bar_set_position(ulProgressBarPosition);
		}
	}
	progress_bar_finalize();
	
	uprintf(". verify ok\n");
	return NETX_CONSOLEAPP_RESULT_OK;
}

/* if return value is NETX_CONSOLEAPP_RESULT_OK, 
   the value stored in ptConsoleParams->pvReturnMessage is the result of the comparison.
   0 = equal, 1 = not equal
*/
NETX_CONSOLEAPP_RESULT_T parflash_verify(const CMD_PARAMETER_VERIFY_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	NETX_CONSOLEAPP_RESULT_T tEqual;
	
	const FLASH_DEVICE_T *ptFlashDescription;
	unsigned long ulStartAdr;
	unsigned long ulEndAdr;
	unsigned char *pucDataStartAdr;

	ptFlashDescription = &(ptParameter->ptDeviceDescription->uInfo.tParFlash);
	ulStartAdr = ptParameter->ulStartAdr;
	ulEndAdr = ptParameter->ulEndAdr;
	pucDataStartAdr = ptParameter->pucData;
	
	tResult = NETX_CONSOLEAPP_RESULT_OK;
	tEqual = parflash_compare(ptFlashDescription, ulStartAdr, ulEndAdr, pucDataStartAdr);
	ptConsoleParams->pvReturnMessage = (void*)tEqual;
	
	return tResult;
}

