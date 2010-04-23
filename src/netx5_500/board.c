/*************************************************************************** 
 *   Copyright (C) 2009 by Hilscher GmbH                                   * 
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

#include <string.h>

#include "board.h"
#include "netx_io_areas.h"
#include "uprintf.h"


typedef union
{
	volatile unsigned char auc_raw[256];
	volatile unsigned short aus_raw[128];
	volatile unsigned long aul_raw[64];
	struct
	{
		volatile unsigned long ul_cfg0x0;
		volatile unsigned long aul_reserved04[3];
		volatile unsigned long ul_addr_cfg;
		volatile unsigned long ul_timing_cfg;
		volatile unsigned long ul_rdy_cfg;
		volatile unsigned long ul_status;
		volatile unsigned long ul_status_err_auto_reset;
		volatile unsigned long ul_status_err_addr;
		volatile unsigned long aul_reserved28[6];
		struct
		{
			volatile unsigned long ul_win_end;
			volatile unsigned long ul_win_map;
		} atDpmWin[5];
		volatile unsigned long aul_reserved68[6];
		volatile unsigned long ul_irq_raw;
		volatile unsigned long ul_irq_fiq_mask;
		volatile unsigned long ul_irq_irq_mask;
		volatile unsigned long ul_irq_fiq_masked;
		volatile unsigned long ul_irq_irq_masked;
		volatile unsigned long ul_fiq_irq_pad_ctrl;
		volatile unsigned long aul_reserved98[2];
		volatile unsigned long ul_io_cfg_misc;
		volatile unsigned long aul_reservedA4[3];
		volatile unsigned long ul_pio_out0;
		volatile unsigned long ul_pio_out1;
		volatile unsigned long ul_pio_oe0;
		volatile unsigned long ul_pio_oe1;
		volatile unsigned long ul_pio_in0;
		volatile unsigned long ul_pio_in1;
		volatile unsigned long aul_reservedC8[13];
		volatile unsigned long ul_netx_version;
	} sReg;
} NETX5_DPM_LAYOUT_T;


typedef enum
{
	EXTBUS_SIZE_08BIT	= 0,
	EXTBUS_SIZE_16BIT	= 1
} EXTBUS_SIZE_T;

typedef enum
{
	DPM_SIZE_08		= 0,
	DPM_SIZE_16		= 1,
	DPM_SIZE_32		= 2
} DPM_SIZE_T;


NETX5_DPM_LAYOUT_T * const ptNetX5Dpm = (NETX5_DPM_LAYOUT_T * const)Addr_NX500_hif_ahbls6;






static NETX_CONSOLEAPP_RESULT_T setup_extbus(EXTBUS_SIZE_T tSize)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulExtBusCs0Cfg;


	/* assume success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	/* enable DPM mode */
	ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
	ptAsicCtrlArea->ulIo_config = 0;

	switch(tSize)
	{
	case EXTBUS_SIZE_08BIT:
		ulExtBusCs0Cfg = 0x00a46421;
		break;

	case EXTBUS_SIZE_16BIT:
		ulExtBusCs0Cfg = 0x00a46423;
		break;

	default:
		tResult = NETX_CONSOLEAPP_RESULT_ERROR; // invalid DPM size
		break;
	}

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		ptNetXGlobalRegBlock2Area->ulExp_bus_reg	= ulExtBusCs0Cfg;
		ptNetXGlobalRegBlock2Area->ulIf_conf1		= 0x10247912;
		ptNetXGlobalRegBlock2Area->ulIf_conf2		= 0x01000000;
		ptNetXGlobalRegBlock2Area->ulIo_reg_mode0	= 0x37ff7ee7;
		ptNetXGlobalRegBlock2Area->ulIo_reg_mode1	= 0x400e7e67;
		ptNetXGlobalRegBlock2Area->ulIo_reg_drv_en0	= 0;
		ptNetXGlobalRegBlock2Area->ulIo_reg_drv_en1	= 0;
	}

	return tResult;
}


static const struct
{
	volatile unsigned long ul_win_end;
	volatile unsigned long ul_win_map;
} atNetx5WinCfg[5] =
{
	{ 0x00001000, 0x000bf700 },
	{ 0x00006000, 0x000c3000 },
	{ 0x0000a000, 0x000c6000 },
	{ 0x00010000, 0x000d6000 },
	{ 0x0001ff00, 0x000f0000 }
};

static NETX_CONSOLEAPP_RESULT_T netx5_init_dpm(DPM_SIZE_T tSize)
{
	int iCnt;
	unsigned long ulValue;
	unsigned char ucCfg0x0;
	unsigned char ucRdAddrSetupTime;
	NETX_CONSOLEAPP_RESULT_T tResult;
	EXTBUS_SIZE_T tExtBusSize;


	/* expect success */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	switch( tSize )
	{
	case DPM_SIZE_08:
		ucCfg0x0 = 0x00;
		tExtBusSize = EXTBUS_SIZE_08BIT;
		break;
	case DPM_SIZE_16:
		ucCfg0x0 = 0x05;
		tExtBusSize = EXTBUS_SIZE_16BIT;
		break;
	case DPM_SIZE_32:
		/* this is not possible with the netX500 */
	default:
		/* invalid DPM size */
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		break;
	}

	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* t_osa?!? */
		ucRdAddrSetupTime = 0;

		/* configure the DPM to 8bit */
		setup_extbus(EXTBUS_SIZE_08BIT);

		/* try to configure DPM several times */
		iCnt = 32768;
		do
		{
			/* write configuration (DPM = 8 bit) */
			ptNetX5Dpm->auc_raw[0x18] = 0x03; /* RDY=PushPull, Polarity=1 (High), RDY is generated as Wait/Busy state signal */
			ptNetX5Dpm->auc_raw[0xa0] = 0x00; /* enable RDY pin, leave SIRQ and DIRQ as IRQ pins */
			ptNetX5Dpm->auc_raw[0x10] = 0x08; /* address area=128kB */

			/* read back configuration */
			ulValue  = (ptNetX5Dpm->auc_raw[0x18] ^ 0x03);
			ulValue |= (ptNetX5Dpm->auc_raw[0xa0] ^ 0x00);
			ulValue |= (ptNetX5Dpm->auc_raw[0x10] ^ 0x08);
		} while( ulValue!=0 && --iCnt>=0);

		/* Configuration successful? */
		if( ulValue!=0 )
		{
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}
		else
		{
			/* configure netX5 DPM with selected size */
			ptNetX5Dpm->auc_raw[0x00] = ucCfg0x0;

			/* configure t_osa */
			ptNetX5Dpm->auc_raw[0x14] = 0x20U | ucRdAddrSetupTime;

			/* check for successful configuration */
			if( ptNetX5Dpm->auc_raw[0x00]!=ucCfg0x0 )
			{
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			}
			else
			{
				/* check for netx version */
				ulValue = ptNetX5Dpm->sReg.ul_netx_version;
				/* mask out the license bits */
				ulValue &= 0x000000ff;
				if( ulValue!=0x00000041 )
				{
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				}
				else
				{
					/* check the dpm_win4_end register, it is fixed to 0x001fff00 */
					ulValue = ptNetX5Dpm->sReg.atDpmWin[4].ul_win_end;
					if( ulValue!=0x0001ff00 )
					{
						tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					}
					else
					{
						/* set the standard netx5 dpm config */
						for(iCnt=0; iCnt<5; ++iCnt)
						{
							ptNetX5Dpm->sReg.atDpmWin[iCnt].ul_win_end = atNetx5WinCfg[iCnt].ul_win_end;
							ptNetX5Dpm->sReg.atDpmWin[iCnt].ul_win_map = atNetx5WinCfg[iCnt].ul_win_map;
						}
					}
				}
			}
		}
	}

	/* all ok */
	return tResult;
}


NETX_CONSOLEAPP_RESULT_T board_init(void)
{
	NETX_CONSOLEAPP_RESULT_T tResult;


	/* init the extension bus to get access to the netx5 io area */
	uprintf(". setting up extension bus to 8 bit.\n");

	tResult = netx5_init_dpm(DPM_SIZE_08);
	uprintf(". result=%d\n", tResult);

	return tResult;
}

