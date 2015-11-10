#include "pl353_nor.h"
#include "netx_io_areas.h"

unsigned char convert_ns_to_mclks(unsigned long ulValueNs, unsigned long ulInitialNs, unsigned char ucInitialMClk, unsigned char ucMaxMClk)
{
	unsigned long ulAkkuNs;
	unsigned char ucMclkUnits;

	/* Get the value in nanoseconds. */
	ulAkkuNs = ulInitialNs;
	ucMclkUnits = ucInitialMClk;
	while( ulAkkuNs<ulValueNs )
	{
		ulAkkuNs += PL353_MCLK_NS;
		++ucMclkUnits;

		if( ucMclkUnits>ucMaxMClk )
		{
			ucMclkUnits = ucMaxMClk;
			break;
		}
	}

	return ucMclkUnits;
}



void nor_update_settings(PL353_NOR_HANDLE_T *ptHandle, PL353_NOR_SETTINGS_T *ptPl353_NorSettings)
{
	PL353_NOR_TIMINGS_T *ptTimingSetMclks;
	PL353_NOR_TIMINGS_T *ptTimingSetNs;
	unsigned long ulValue;

	ptTimingSetMclks = &(ptHandle->tTimingsMclks);
	ptTimingSetNs = &(ptPl353_NorSettings->tTimingsNs);

	/* The t_RC value must not be smaller than 2. */
	ptTimingSetMclks->usT_RC   = convert_ns_to_mclks(ptTimingSetNs->usT_RC,   40U, 2U, 15U);

	/* The t_WC value must not be smaller than 2. */
	ptTimingSetMclks->usT_WC   = convert_ns_to_mclks(ptTimingSetNs->usT_WC,   40U, 2U, 15U);

	/* The t_CEOE value must not be smaller than 1. */
	ptTimingSetMclks->ucT_CEOE = convert_ns_to_mclks(ptTimingSetNs->ucT_CEOE, 20U, 1U,  7U);

	/* The t_WP value must not be smaller than 1. */
	ptTimingSetMclks->ucT_WP   = convert_ns_to_mclks(ptTimingSetNs->ucT_WP,   20U, 1U,  7U);

	ptTimingSetMclks->ucT_PC   = convert_ns_to_mclks(ptTimingSetNs->ucT_PC,   20U, 1U,  7U);
	ptTimingSetMclks->ucT_TR   = convert_ns_to_mclks(ptTimingSetNs->ucT_TR,   20U, 1U,  7U);

	/* Copy the we_time. */
	ptTimingSetMclks->ucWeTime = ptTimingSetNs->ucWeTime;

	/* Prepare the timing value for the PL353. */

	ulValue  = ((unsigned long)ptTimingSetMclks->usT_RC)   << HOSTSRT(PL353_set_cycles_set_t0);
	ulValue |= ((unsigned long)ptTimingSetMclks->usT_WC)   << HOSTSRT(PL353_set_cycles_set_t1);
	ulValue |= ((unsigned long)ptTimingSetMclks->ucT_CEOE) << HOSTSRT(PL353_set_cycles_set_t2);
	ulValue |= ((unsigned long)ptTimingSetMclks->ucT_WP)   << HOSTSRT(PL353_set_cycles_set_t3);
	ulValue |= ((unsigned long)ptTimingSetMclks->ucT_PC)   << HOSTSRT(PL353_set_cycles_set_t4);
	ulValue |= ((unsigned long)ptTimingSetMclks->ucT_TR)   << HOSTSRT(PL353_set_cycles_set_t5);
	ulValue |= ((unsigned long)ptTimingSetMclks->ucWeTime) << HOSTSRT(PL353_set_cycles_set_t6);
	ptHandle->ulPL353_timings = ulValue;

	ulValue  = ((unsigned long)ptPl353_NorSettings->ucBurstAlign) << HOSTSRT(PL353_set_opmode_set_burst_align);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucBlsTime)    << HOSTSRT(PL353_set_opmode_set_bls);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucAdV)        << HOSTSRT(PL353_set_opmode_set_adv);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucBAA)        << HOSTSRT(PL353_set_opmode_set_baa);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucWrBl)       << HOSTSRT(PL353_set_opmode_set_wr_bl);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucWrSync)     << HOSTSRT(PL353_set_opmode_set_wr_sync);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucRdBl)       << HOSTSRT(PL353_set_opmode_set_rd_bl);
	ulValue |= ((unsigned long)ptPl353_NorSettings->ucRdSync)     << HOSTSRT(PL353_set_opmode_set_rd_sync);
	ulValue |= 0                                                  << HOSTSRT(PL353_set_opmode_set_mw);
	ptHandle->ulPL353_opmode = ulValue;

}



void pl353_nor_update_registers(PL353_NOR_HANDLE_T *ptHandle)
{
	HOSTDEF(ptPL353Area);
	unsigned long ulValue;


	ulValue  = ptHandle->uiChipSelect << HOSTSRT(PL353_direct_cmd_chip_select);  /* Set the chip select. */
	ulValue |= 2U << HOSTSRT(PL353_direct_cmd_cmd_type);               /* Update registers. */
	ulValue |= 0U << HOSTSRT(PL353_direct_cmd_set_cre);
	ulValue |= 0U << HOSTSRT(PL353_direct_cmd_addr);
	ptPL353Area->ulPL353_direct_cmd = ulValue;
}



void pl353_nor_setup(PL353_NOR_HANDLE_T *ptHandle, MEMORY_WIDTH_T tBusWidth)
{
	HOSTDEF(ptPL353Area);
	unsigned long ulValue;
	unsigned long ulMemoryWidth;

	/* Get the PL353 out of low power mode and clear and disable the IRQs. */
	ulValue  = HOSTMSK(PL353_mem_cfg_clr_int_disable0);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_int_disable1);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_low_power_exit);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_int_clr0);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_int_clr1);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_ecc_int_disable0);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_ecc_int_disable1);
	ptPL353Area->ulPL353_mem_cfg_clr = ulValue;
	/* One more write to really clear and disable the IRQs. */
	ptPL353Area->ulPL353_mem_cfg_clr = ulValue;

	/* Disable ECC. */
	ptPL353Area->ulPL353_ecc_memcfg = 0U;

	/* Set the operation mode. */
	ulMemoryWidth = (tBusWidth == MEMORY_WIDTH_16Bit)?1:0;
	ulValue  = ptHandle->ulPL353_opmode;
	ulValue |= ulMemoryWidth << HOSTSRT(PL353_set_opmode_set_mw);
	ptPL353Area->ulPL353_set_opmode = ulValue;
	pl353_nor_update_registers(ptHandle);

	/* Set the timings. */
	ptPL353Area->ulPL353_set_cycles = ptHandle->ulPL353_timings;
	pl353_nor_update_registers(ptHandle);

	/* Clear int0 and int1. */
	ulValue  = HOSTMSK(PL353_mem_cfg_clr_int_clr0);
	ulValue |= HOSTMSK(PL353_mem_cfg_clr_int_clr1);
	ptPL353Area->ulPL353_mem_cfg_clr = ulValue;

	pl353_nor_update_registers(ptHandle);
}

/*
   Default timings are maximum values.
   min( initialMClk + (ulValueNs - ulInitialNs)/PL353_MCLK_NS, ucMaxMClk)
   PL353_MCLK_NS = 20 ns
             val_ns  ini_ns    ini_clk     max_clk
   usT_RC      300     40        2           15         = 15
   usT_WC      300     40        2           15         = 15
   ucT_CEOE    140     20        1            7         = 7 
   ucT_WP      140     20        1            7         = 7
   ucT_PC      140     20        1            7         = 7
   ucT_TR      140     20        1            7         = 7
*/
PL353_NOR_SETTINGS_T g_tPl353_NorDefaultSettings = 
	{
		.tBusWidth = MEMORY_WIDTH_Auto,

		.ucBurstAlign = 0,
		.ucBlsTime    = 0,
		.ucAdV        = 0,
		.ucBAA        = 0,
		.ucWrBl       = 0,
		.ucWrSync     = 0,
		.ucRdBl       = 0,
		.ucRdSync     = 0,

		.tTimingsNs =
		{
			.usT_RC   = 300U,
			.usT_WC   = 300U,
			.ucT_CEOE = 140U,
			.ucT_WP   = 140U,
			.ucT_PC   = 140U,
			.ucT_TR   = 140U,
			.ucWeTime = 0
		}
	};


void setup_flash_nor_pl353(unsigned int uiChipSelect, MEMORY_WIDTH_T tBusWidth)
{
	PL353_NOR_HANDLE_T tHandle;
	
	tHandle.uiChipSelect = uiChipSelect;
	nor_update_settings(&tHandle, &g_tPl353_NorDefaultSettings);
	pl353_nor_setup(&tHandle, tBusWidth);

}

