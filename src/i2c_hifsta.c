/***************************************************************************
 *   Copyright (C) 2011 by Hilscher GmbH                                   *
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

#include "i2c_hifsta.h"

#include "netx_io_areas.h"


/*-------------------------------------*/

#if ASIC_TYP==500 || ASIC_TYP==100 || ASIC_TYP==50

/* Some defines for the mysterious hif regs,
 * taken from the "netX Program Reference Guide Rev0.3", page 16
 */

#define MSK_sta_netx_rdy			0x00000001U
#define SRT_sta_netx_rdy			0
#define MSK_sta_netx_run			0x00000002U
#define SRT_sta_netx_run			1
#define MSK_sta_netx_netx_state			0x0000000cU
#define SRT_sta_netx_netx_state			2
#define MSK_sta_netx_host_state			0x000000f0U
#define SRT_sta_netx_host_state			4
#define MSK_sta_netx_netx_sta_code		0x0000ff00U
#define SRT_sta_netx_netx_sta_code		8
#define MSK_sta_netx_rdy_in			0x00010000U
#define SRT_sta_netx_rdy_in			16
#define MSK_sta_netx_run_in			0x00020000U
#define SRT_sta_netx_run_in			17
#define MSK_sta_netx_rdy_pol			0x00040000U
#define SRT_sta_netx_rdy_pol			18
#define MSK_sta_netx_run_pol			0x00080000U
#define SRT_sta_netx_run_pol			19
#define MSK_sta_netx_rdy_drv			0x01000000U
#define SRT_sta_netx_rdy_drv			24
#define MSK_sta_netx_run_drv			0x02000000U
#define SRT_sta_netx_run_drv			25

#endif


/* Defines for the pio pin values passed to set pins.
 * The logic is inverted as only the low level drives the output.
 */
typedef enum
{
	PIO_I2C_LO = 1,
	PIO_I2C_HI = 0
} tI2cOut;

/*-------------------------------------*/

#define TRIGGER_ROM_WATCHDOG(a) __asm("nop\n")


#if ASIC_TYP==10 || ASIC_TYP==50 || ASIC_TYP==56 || ASIC_TYP==4000
static void i2c_hifsta_clock(void)
{
	/* trigger rom watchdog */
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);

	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
	TRIGGER_ROM_WATCHDOG(0);
}
#endif


#if ASIC_TYP==10 || ASIC_TYP==56 || ASIC_TYP==4000
void i2c_hifsta_rdy_on_run_off(void)
{
	HOSTDEF(ptAsicCtrlArea);
	unsigned long ulValue;


	ulValue = ptAsicCtrlArea->ulRdy_run_cfg;

	/* SCLK (RDY) lo */
	ulValue |= HOSTMSK(rdy_run_cfg_RDY_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	/* SData (RUN) lo */
	ulValue |= HOSTMSK(rdy_run_cfg_RUN_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	i2c_hifsta_clock();

	/* SData (RUN) hi */
	ulValue &= ~HOSTMSK(rdy_run_cfg_RUN_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	i2c_hifsta_clock();
}


void i2c_hifsta_rdy_off_run_on(void)
{
	HOSTDEF(ptAsicCtrlArea);
	unsigned long ulValue;


	ulValue = ptAsicCtrlArea->ulRdy_run_cfg;

	/* SCLK (RDY) lo */
	ulValue |= HOSTMSK(rdy_run_cfg_RDY_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	/* SData (RUN) lo */
	ulValue |= HOSTMSK(rdy_run_cfg_RUN_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	i2c_hifsta_clock();

	/* SCLK (RDY) hi */
	ulValue &= ~HOSTMSK(rdy_run_cfg_RDY_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	i2c_hifsta_clock();
}


void i2c_hifsta_rdy_off_run_off(void)
{
	HOSTDEF(ptAsicCtrlArea);
	unsigned long ulValue;


	ulValue = ptAsicCtrlArea->ulRdy_run_cfg;

	/* SCLK (RDY) hi */
	ulValue &= ~HOSTMSK(rdy_run_cfg_RDY_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	/* SData (RUN) lo */
	ulValue &= ~HOSTMSK(rdy_run_cfg_RUN_DRV);
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	i2c_hifsta_clock();
}
#elif ASIC_TYP==50
void i2c_hifsta_rdy_on_run_off(void)
{
	HOSTDEF(ptNetxControlledGlobalRegisterBlock1Area);
	unsigned long ulValue;


	ulValue = ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx;

	/* sclk (rdy) lo */
	ulValue &= ~MSK_sta_netx_rdy;
	ulValue |= MSK_sta_netx_run_drv | MSK_sta_netx_rdy_drv;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();
	i2c_hifsta_clock();

	/* sdata (run) lo */
	ulValue |= MSK_sta_netx_run;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();
}


void i2c_hifsta_rdy_off_run_on(void)
{
	HOSTDEF(ptNetxControlledGlobalRegisterBlock1Area);
	unsigned long ulValue;


	ulValue = ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx;

	/* sclk (rdy) lo */
	ulValue &= ~MSK_sta_netx_rdy;
	ulValue |= MSK_sta_netx_run_drv | MSK_sta_netx_rdy_drv;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();

	/* sdata (run) lo */
	ulValue &= ~MSK_sta_netx_run;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();
	
	ulValue |= MSK_sta_netx_rdy;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();
}


void i2c_hifsta_rdy_off_run_off(void)
{
	HOSTDEF(ptNetxControlledGlobalRegisterBlock1Area);
	unsigned long ulValue;


	ulValue = ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx;

	/* sclk (rdy) hi */
	ulValue &= ~MSK_sta_netx_rdy;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();
	i2c_hifsta_clock();

	/* sdata (run) lo */
	ulValue &= ~MSK_sta_netx_run;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	i2c_hifsta_clock();
}
#endif

/*-------------------------------------*/

