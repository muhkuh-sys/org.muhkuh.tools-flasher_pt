/*********************************************************************/
/* from regdef.v by regdef2h auto-generated C-header file            */
/* please see the regdef.html file for detailed register description */
/*********************************************************************/

#ifndef __regdef_NX5_h
#define __regdef_NX5_h


/* ===================================================================== */

/* Area of dpm_full_window */

/* ===================================================================== */

#define Addr_NX5_dpm_full_window 0x01800000U

/* ===================================================================== */

/* Area of sram0_ahbls0 */

/* ===================================================================== */

#define Addr_NX5_sram0_ahbls0 0x01800000U

/* --------------------------------------------------------------------- */
/* Register intram0_base */
/* => internal SRAM AHBL slave 0 start address */
/*    Area size: 32kB */
/*    Read accesses in this memory area: 0WS, byte accessable */
/*    Write accesses in this memory area: 0WS, byte accessable */
/*    Offset 0x0 is ROM Boot-vector */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_intram0_base          0x00000000U
#define Adr_NX5_sram0_ahbls0_intram0_base 0x01800000U
#define Adr_NX5_intram0_base              0x01800000U

/* --------------------------------------------------------------------- */
/* Register intram0_end */
/* => internal SRAM AHBL slave 0 end address */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_intram0_end          0x00007FFCU
#define Adr_NX5_sram0_ahbls0_intram0_end 0x01807FFCU
#define Adr_NX5_intram0_end              0x01807FFCU


/* ===================================================================== */

/* Area of sram1_ahbls1 */

/* ===================================================================== */

#define Addr_NX5_sram1_ahbls1 0x01808000U

/* --------------------------------------------------------------------- */
/* Register intram1_base */
/* => internal SRAM AHBL slave 1 start address */
/*    Area size: 32kB */
/*    Read accesses in this memory area: 0WS, byte accessable */
/*    Write accesses in this memory area: 0WS, byte accessable */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_intram1_base          0x00000000U
#define Adr_NX5_sram1_ahbls1_intram1_base 0x01808000U
#define Adr_NX5_intram1_base              0x01808000U

/* --------------------------------------------------------------------- */
/* Register intram1_end */
/* => internal SRAM AHBL slave 1 end address */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_intram1_end          0x00007FFCU
#define Adr_NX5_sram1_ahbls1_intram1_end 0x0180FFFCU
#define Adr_NX5_intram1_end              0x0180FFFCU


/* ===================================================================== */

/* Area of rom_ahbls */

/* ===================================================================== */

#define Addr_NX5_rom_ahbls 0x01810000U

/* --------------------------------------------------------------------- */
/* Register introm_base */
/* => internal ROM AHBL slave start address */
/*    Area size: 8kB */
/*    Read accesses in this memory area: 0WS, byte accessable */
/*    Write accesses in this memory area: 0WS, byte accessable */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_introm_base       0x00000000U
#define Adr_NX5_rom_ahbls_introm_base 0x01810000U
#define Adr_NX5_introm_base           0x01810000U

/* --------------------------------------------------------------------- */
/* Register introm_end */
/* => internal ROM AHBL slave end address */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_introm_end       0x00001FFCU
#define Adr_NX5_rom_ahbls_introm_end 0x01811FFCU
#define Adr_NX5_introm_end           0x01811FFCU


/* ===================================================================== */

/* Area of intlogic_ahbls5 */

/* ===================================================================== */

#define Addr_NX5_intlogic_ahbls5 0x01880000U

/* ===================================================================== */

/* Area of asic_ctrl */

/* ===================================================================== */

#define Addr_NX5_asic_ctrl 0x018BF800U
#define NX5_NETX_CTRL_AREA 0x018BF800U

/* --------------------------------------------------------------------- */
/* Register io_status */
/* => Bondout Out Option Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_io_status       0x00000000U
#define Adr_NX5_asic_ctrl_io_status 0x018BF800U
#define Adr_NX5_io_status           0x018BF800U

#define MSK_NX5_io_status_bond_option    0x00000007U
#define SRT_NX5_io_status_bond_option    0
#define MSK_NX5_io_status_quick_count    0x00000008U
#define SRT_NX5_io_status_quick_count    3
#define MSK_NX5_io_status_pll_bypass     0x00000010U
#define SRT_NX5_io_status_pll_bypass     4
#define MSK_NX5_io_status_TESTMODE0      0x00000020U
#define SRT_NX5_io_status_TESTMODE0      5
#define MSK_NX5_io_status_TESTMODE1      0x00000040U
#define SRT_NX5_io_status_TESTMODE1      6
#define MSK_NX5_io_status_TESTMODE2      0x00000080U
#define SRT_NX5_io_status_TESTMODE2      7
#define MSK_NX5_io_status_TESTMODE3      0x00000100U
#define SRT_NX5_io_status_TESTMODE3      8
#define MSK_NX5_io_status_sel_dpm_serial 0x00000200U
#define SRT_NX5_io_status_sel_dpm_serial 9

enum {
	BFW_NX5_io_status_bond_option    = 3,  /* [2:0] */
	BFW_NX5_io_status_quick_count    = 1,  /* [3] */
	BFW_NX5_io_status_pll_bypass     = 1,  /* [4] */
	BFW_NX5_io_status_TESTMODE0      = 1,  /* [5] */
	BFW_NX5_io_status_TESTMODE1      = 1,  /* [6] */
	BFW_NX5_io_status_TESTMODE2      = 1,  /* [7] */
	BFW_NX5_io_status_TESTMODE3      = 1,  /* [8] */
	BFW_NX5_io_status_sel_dpm_serial = 1,  /* [9] */
	BFW_NX5_io_status_reserved1      = 22  /* [31:10] */
};

typedef struct NX5_IO_STATUS_BIT_Ttag {
	unsigned int bond_option    : BFW_NX5_io_status_bond_option;    /* Value of Bond-Option Pin2 - Pin0, KEEP in netx5!!! necessary for TSLA!!!                                               */
	unsigned int quick_count    : BFW_NX5_io_status_quick_count;    /* Testmode 'quick_count' is activated by external pins                                                                   */
	                                                                /* -> diverse internal counters count faster (RTC-clock-divider, PLL-stby-controller,...)                                 */
	unsigned int pll_bypass     : BFW_NX5_io_status_pll_bypass;     /* Testmode 'pll_bypass' is activated by external pins                                                                    */
	                                                                /* -> 400MHz-PLL is bypassed, PLL output is unused, 400MHz-Clocks (clk400, clk400_2sdram) is directly connected to XTALIN */
	unsigned int TESTMODE0      : BFW_NX5_io_status_TESTMODE0;      /* sampled netx TEST input for Productiontest purpose                                                                     */
	unsigned int TESTMODE1      : BFW_NX5_io_status_TESTMODE1;      /* sampled netx TEST input for Productiontest purpose                                                                     */
	unsigned int TESTMODE2      : BFW_NX5_io_status_TESTMODE2;      /* sampled netx TEST input for Productiontest purpose                                                                     */
	unsigned int TESTMODE3      : BFW_NX5_io_status_TESTMODE3;      /* sampled netx TEST input for Productiontest purpose                                                                     */
	unsigned int sel_dpm_serial : BFW_NX5_io_status_sel_dpm_serial; /* shows input DPM_MODE                                                                                                   */
	unsigned int reserved1      : BFW_NX5_io_status_reserved1;      /* reserved                                                                                                               */
} NX5_IO_STATUS_BIT_T;

typedef union {
	unsigned int        val;
	NX5_IO_STATUS_BIT_T bf;
} NX5_IO_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register io_config */
/* => IO Config Register: */
/*    Selects of output pin multiplexing. */
/*    See Excel pinning sheet for details. */
/*    Selects can only be activated, if appropriate bit of io_config_mask is set. */
/*    Bits will be reset according to the io_config_mask-register register if a new mask is correctly written (netX locking algorithm). */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_io_config       0x00000004U
#define Adr_NX5_asic_ctrl_io_config 0x018BF804U
#define Adr_NX5_io_config           0x018BF804U
#define DFLT_VAL_NX5_io_config      0x00000000U

#define MSK_NX5_io_config_sel_fb0clk               0x00000001U
#define SRT_NX5_io_config_sel_fb0clk               0
#define DFLT_VAL_NX5_io_config_sel_fb0clk          0x00000000U
#define MSK_NX5_io_config_sel_fb1clk               0x00000002U
#define SRT_NX5_io_config_sel_fb1clk               1
#define DFLT_VAL_NX5_io_config_sel_fb1clk          0x00000000U
#define MSK_NX5_io_config_phy_clk_out_oe           0x00000004U
#define SRT_NX5_io_config_phy_clk_out_oe           2
#define DFLT_VAL_NX5_io_config_phy_clk_out_oe      0x00000000U
#define MSK_NX5_io_config_sel_spi_cs1n             0x00000008U
#define SRT_NX5_io_config_sel_spi_cs1n             3
#define DFLT_VAL_NX5_io_config_sel_spi_cs1n        0x00000000U
#define MSK_NX5_io_config_sel_spi_cs2n             0x00000010U
#define SRT_NX5_io_config_sel_spi_cs2n             4
#define DFLT_VAL_NX5_io_config_sel_spi_cs2n        0x00000000U
#define MSK_NX5_io_config_sel_phy_clk_digital      0x00000020U
#define SRT_NX5_io_config_sel_phy_clk_digital      5
#define DFLT_VAL_NX5_io_config_sel_phy_clk_digital 0x00000000U

enum {
	BFW_NX5_io_config_sel_fb0clk          = 1,  /* [0] */
	BFW_NX5_io_config_sel_fb1clk          = 1,  /* [1] */
	BFW_NX5_io_config_phy_clk_out_oe      = 1,  /* [2] */
	BFW_NX5_io_config_sel_spi_cs1n        = 1,  /* [3] */
	BFW_NX5_io_config_sel_spi_cs2n        = 1,  /* [4] */
	BFW_NX5_io_config_sel_phy_clk_digital = 1,  /* [5] */
	BFW_NX5_io_config_reserved1           = 26  /* [31:6] */
};

typedef struct NX5_IO_CONFIG_BIT_Ttag {
	unsigned int sel_fb0clk          : BFW_NX5_io_config_sel_fb0clk;          /* select pad for fieldbus-clk0 (s. pinning.xls)                               */
	unsigned int sel_fb1clk          : BFW_NX5_io_config_sel_fb1clk;          /* select pad for fieldbus-clk1 (s. pinning.xls)                               */
	unsigned int phy_clk_out_oe      : BFW_NX5_io_config_phy_clk_out_oe;      /* output enable for phy_clk_out                                               */
	unsigned int sel_spi_cs1n        : BFW_NX5_io_config_sel_spi_cs1n;        /* select additional SPI chipselect 1 via PIO pads                             */
	unsigned int sel_spi_cs2n        : BFW_NX5_io_config_sel_spi_cs2n;        /* select additional SPI chipselect 2 via PIO pads                             */
	unsigned int sel_phy_clk_digital : BFW_NX5_io_config_sel_phy_clk_digital; /* 1: derive phy_clk_out from clk, 0: use clock from input xTAL as phy_clk_out */
	unsigned int reserved1           : BFW_NX5_io_config_reserved1;           /* reserved                                                                    */
} NX5_IO_CONFIG_BIT_T;

typedef union {
	unsigned int        val;
	NX5_IO_CONFIG_BIT_T bf;
} NX5_IO_CONFIG_T;

/* --------------------------------------------------------------------- */
/* Register reset_ctrl */
/* => Reset Control Register: */
/*    This register controls the reset functions of the netX chip and indicates the reset state. The reset state */
/*    shows which resets have occurred, allowing the firmware to detect which resets were active. In order to */
/*    determine the source of the last reset, the firmware should evaluate and reset these bits during its start */
/*    sequence. After a power on reset, the RESET_CTRL register is cleared completely. */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence:    //+ */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_reset_ctrl       0x0000000CU
#define Adr_NX5_asic_ctrl_reset_ctrl 0x018BF80CU
#define Adr_NX5_reset_ctrl           0x018BF80CU
#define DFLT_VAL_NX5_reset_ctrl      0x00000000U

#define MSK_NX5_reset_ctrl_res_xpec0             0x00000010U
#define SRT_NX5_reset_ctrl_res_xpec0             4
#define DFLT_VAL_NX5_reset_ctrl_res_xpec0        0x00000000U
#define MSK_NX5_reset_ctrl_res_xpec1             0x00000020U
#define SRT_NX5_reset_ctrl_res_xpec1             5
#define DFLT_VAL_NX5_reset_ctrl_res_xpec1        0x00000000U
#define MSK_NX5_reset_ctrl_dis_res_xpec0         0x00010000U
#define SRT_NX5_reset_ctrl_dis_res_xpec0         16
#define DFLT_VAL_NX5_reset_ctrl_dis_res_xpec0    0x00000000U
#define MSK_NX5_reset_ctrl_dis_res_xpec1         0x00020000U
#define SRT_NX5_reset_ctrl_dis_res_xpec1         17
#define DFLT_VAL_NX5_reset_ctrl_dis_res_xpec1    0x00000000U
#define MSK_NX5_reset_ctrl_res_req_firmware      0x01000000U
#define SRT_NX5_reset_ctrl_res_req_firmware      24
#define DFLT_VAL_NX5_reset_ctrl_res_req_firmware 0x00000000U

enum {
	BFW_NX5_reset_ctrl_reserved1        = 4,  /* [3:0] */
	BFW_NX5_reset_ctrl_res_xpec0        = 1,  /* [4] */
	BFW_NX5_reset_ctrl_res_xpec1        = 1,  /* [5] */
	BFW_NX5_reset_ctrl_reserved2        = 10, /* [15:6] */
	BFW_NX5_reset_ctrl_dis_res_xpec0    = 1,  /* [16] */
	BFW_NX5_reset_ctrl_dis_res_xpec1    = 1,  /* [17] */
	BFW_NX5_reset_ctrl_reserved3        = 6,  /* [23:18] */
	BFW_NX5_reset_ctrl_res_req_firmware = 1,  /* [24] */
	BFW_NX5_reset_ctrl_reserved4        = 7   /* [31:25] */
};

typedef struct NX5_RESET_CTRL_BIT_Ttag {
	unsigned int reserved1        : BFW_NX5_reset_ctrl_reserved1;        /* reserved                                                                                    */
	unsigned int res_xpec0        : BFW_NX5_reset_ctrl_res_xpec0;        /* reset from res_xpec0, after reading write back a "1" to clear the status bit                */
	unsigned int res_xpec1        : BFW_NX5_reset_ctrl_res_xpec1;        /* reset from res_xpec1, after reading write back a "1" to clear the status bit                */
	unsigned int reserved2        : BFW_NX5_reset_ctrl_reserved2;        /* reserved                                                                                    */
	unsigned int dis_res_xpec0    : BFW_NX5_reset_ctrl_dis_res_xpec0;    /* reset from res_xpec0 is disabled (read only)                                                */
	unsigned int dis_res_xpec1    : BFW_NX5_reset_ctrl_dis_res_xpec1;    /* reset from res_xpec1 is disabled (read only)                                                */
	unsigned int reserved3        : BFW_NX5_reset_ctrl_reserved3;        /* reserved                                                                                    */
	unsigned int res_req_firmware : BFW_NX5_reset_ctrl_res_req_firmware; /* software reset: writing a "1" sets the reset request to reset the whole system (write only) */
	unsigned int reserved4        : BFW_NX5_reset_ctrl_reserved4;        /* reserved                                                                                    */
} NX5_RESET_CTRL_BIT_T;

typedef union {
	unsigned int         val;
	NX5_RESET_CTRL_BIT_T bf;
} NX5_RESET_CTRL_T;

/* --------------------------------------------------------------------- */
/* Register armclk_rate_mul_add */
/* => Rate Multiplier Add Value of System Clock: */
/*    This register might be used to change internal system frequency (200MHz and 100MHz are in fixed relation). */
/*    Be careful when changing this value, as proper netX functionality is only qualified for the default value. */
/*    This register is lockable by netX locking algorithm. It will be only reset on Power on, not on normal system nres. */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out Locking Access Key */
/*    2.: write back Locking Access Key */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_armclk_rate_mul_add       0x00000014U
#define Adr_NX5_asic_ctrl_armclk_rate_mul_add 0x018BF814U
#define Adr_NX5_armclk_rate_mul_add           0x018BF814U
#define DFLT_VAL_NX5_armclk_rate_mul_add      0x00000100U

#define MSK_NX5_armclk_rate_mul_add_armclk_rate_mul_add      0x000001ffU
#define SRT_NX5_armclk_rate_mul_add_armclk_rate_mul_add      0
#define DFLT_VAL_NX5_armclk_rate_mul_add_armclk_rate_mul_add 0x00000100U

enum {
	BFW_NX5_armclk_rate_mul_add_armclk_rate_mul_add = 9,  /* [8:0] */
	BFW_NX5_armclk_rate_mul_add_reserved1           = 23  /* [31:9] */
};

typedef struct NX5_ARMCLK_RATE_MUL_ADD_BIT_Ttag {
	unsigned int armclk_rate_mul_add : BFW_NX5_armclk_rate_mul_add_armclk_rate_mul_add; /* This value is added each clk400 cycle to armclk_rate_mul to generate armclk. */
	                                                                                    /* Change value according to formula:                                           */
	unsigned int reserved1           : BFW_NX5_armclk_rate_mul_add_reserved1;           /* reserved                                                                     */
} NX5_ARMCLK_RATE_MUL_ADD_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_ARMCLK_RATE_MUL_ADD_BIT_T bf;
} NX5_ARMCLK_RATE_MUL_ADD_T;

/* --------------------------------------------------------------------- */
/* Register fb0clk_rate_mul_add */
/* => Rate Multiplier Add Value: */
/*    Fieldbus0 clock is generated by internal 400MHz rate multiplier. \ */
/*    At some fieldbus-frequencies, this clock has less jitter, than the xMAC generated output clock. \ */
/*    xMAC fieldbus outputs (mii0_txd0=xm0_tx_d, mii0_txen=xm0_tx_oe) can optionally (io_config-sel_fb0clk) be sampled by an extra register running on this clock, */
/*    resulting in jitter less fieldbus outputs. */
/*    Alternatively to this internally generated clock, an external clock (mii0_rxclk=xm0_eclk) can be used to make xMAC outputs jitter free (clock_enable-fb0). \ */
/*    Using external clocks to resample xMAC outputs requires modified xMAC software. */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out Locking Access Key */
/*    2.: write back Locking Access Key */
/*    3.: write desired value to this register */
/*     */
/*    ------------------------------------ */
/*    netX100/netX500 usage of this address: adcclk_rate_mul_add */
/*    ------------------------------------ */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fb0clk_rate_mul_add       0x0000001CU
#define Adr_NX5_asic_ctrl_fb0clk_rate_mul_add 0x018BF81CU
#define Adr_NX5_fb0clk_rate_mul_add           0x018BF81CU
#define DFLT_VAL_NX5_fb0clk_rate_mul_add      0x01000000U

#define MSK_NX5_fb0clk_rate_mul_add_fb0clk_rate_mul_add      0xffffffffU
#define SRT_NX5_fb0clk_rate_mul_add_fb0clk_rate_mul_add      0
#define DFLT_VAL_NX5_fb0clk_rate_mul_add_fb0clk_rate_mul_add 0x01000000U

enum {
	BFW_NX5_fb0clk_rate_mul_add_fb0clk_rate_mul_add = 32  /* [31:0] */
};

typedef struct NX5_FB0CLK_RATE_MUL_ADD_BIT_Ttag {
	unsigned int fb0clk_rate_mul_add : BFW_NX5_fb0clk_rate_mul_add_fb0clk_rate_mul_add; /* This value is added each clk400 cycle to fb0clk_rate_mul to generate fb0clk. */
	                                                                                    /* Change value according to formula:                                           */
} NX5_FB0CLK_RATE_MUL_ADD_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_FB0CLK_RATE_MUL_ADD_BIT_T bf;
} NX5_FB0CLK_RATE_MUL_ADD_T;

/* --------------------------------------------------------------------- */
/* Register fb1clk_rate_mul_add */
/* => Rate Multiplier Add Value: */
/*    Fieldbus1 clock is generated by internal 400MHz rate multiplier. \ */
/*    At some fieldbus-frequencies, this clock has less jitter, than the xMAC generated output clock. \ */
/*    xMAC fieldbus outputs (mii1_txd0=xm1_tx_out, mii1_txen=xm1_tx_oe) can optionally (io_config-sel_fb1clk) be sampled by an extra register running on this clock, */
/*    resulting in jitter less fieldbus outputs. */
/*    Alternatively to this internally generated clock, an external clock (mii1_rxclk=xm1_eclk) can be used to make xMAC outputs jitter free (clock_enable-fb1). \ */
/*    Using external clocks to resample xMAC outputs requires modified xMAC software. */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fb1clk_rate_mul_add       0x00000020U
#define Adr_NX5_asic_ctrl_fb1clk_rate_mul_add 0x018BF820U
#define Adr_NX5_fb1clk_rate_mul_add           0x018BF820U
#define DFLT_VAL_NX5_fb1clk_rate_mul_add      0x01000000U

#define MSK_NX5_fb1clk_rate_mul_add_fb1clk_rate_mul_add      0xffffffffU
#define SRT_NX5_fb1clk_rate_mul_add_fb1clk_rate_mul_add      0
#define DFLT_VAL_NX5_fb1clk_rate_mul_add_fb1clk_rate_mul_add 0x01000000U

enum {
	BFW_NX5_fb1clk_rate_mul_add_fb1clk_rate_mul_add = 32  /* [31:0] */
};

typedef struct NX5_FB1CLK_RATE_MUL_ADD_BIT_Ttag {
	unsigned int fb1clk_rate_mul_add : BFW_NX5_fb1clk_rate_mul_add_fb1clk_rate_mul_add; /* This value is added each clk400 cycle to fb1clk_rate_mul to generate fb1clk. */
	                                                                                    /* Change value according to formula:                                           */
} NX5_FB1CLK_RATE_MUL_ADD_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_FB1CLK_RATE_MUL_ADD_BIT_T bf;
} NX5_FB1CLK_RATE_MUL_ADD_T;

/* --------------------------------------------------------------------- */
/* Register clock_enable */
/* => Global Clock Enable Register: */
/*    Use this registers to disable modules completely for power saving purposes. */
/*    Changes will only have effect if according bit in clock_enable_mask-register is set. \ */
/*    Bits will be reset according to the clock_enable_mask-register register, if a new mask is correctly written (netX locking algorithm). */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_clock_enable       0x00000024U
#define Adr_NX5_asic_ctrl_clock_enable 0x018BF824U
#define Adr_NX5_clock_enable           0x018BF824U
#define DFLT_VAL_NX5_clock_enable      0x00000000U

#define MSK_NX5_clock_enable_fb0      0x00000400U
#define SRT_NX5_clock_enable_fb0      10
#define DFLT_VAL_NX5_clock_enable_fb0 0x00000000U
#define MSK_NX5_clock_enable_fb1      0x00000800U
#define SRT_NX5_clock_enable_fb1      11
#define DFLT_VAL_NX5_clock_enable_fb1 0x00000000U

enum {
	BFW_NX5_clock_enable_reserved1 = 10, /* [9:0] */
	BFW_NX5_clock_enable_fb0       = 1,  /* [10] */
	BFW_NX5_clock_enable_fb1       = 1,  /* [11] */
	BFW_NX5_clock_enable_reserved2 = 20  /* [31:12] */
};

typedef struct NX5_CLOCK_ENABLE_BIT_Ttag {
	unsigned int reserved1 : BFW_NX5_clock_enable_reserved1; /* reserved                                                     */
	unsigned int fb0       : BFW_NX5_clock_enable_fb0;       /* enables clock for fieldbus0:                                 */
	                                                         /* 1: use internally generated fb0clk to resample xMAC0 outputs */
	unsigned int fb1       : BFW_NX5_clock_enable_fb1;       /* enables clock for fieldbus1:                                 */
	                                                         /* 1: use internally generated fb1clk to resample xMAC1 outputs */
	unsigned int reserved2 : BFW_NX5_clock_enable_reserved2; /* reserved                                                     */
} NX5_CLOCK_ENABLE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_CLOCK_ENABLE_BIT_T bf;
} NX5_CLOCK_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register only_porn */
/* => Firmware Status register: */
/*    This register is not Reset by SW resets, only PORn will reset this register. */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_only_porn       0x00000030U
#define Adr_NX5_asic_ctrl_only_porn 0x018BF830U
#define Adr_NX5_only_porn           0x018BF830U
#define DFLT_VAL_NX5_only_porn      0x00000000U

#define MSK_NX5_only_porn_only_porn      0xffffffffU
#define SRT_NX5_only_porn_only_porn      0
#define DFLT_VAL_NX5_only_porn_only_porn 0x00000000U

enum {
	BFW_NX5_only_porn_only_porn = 32  /* [31:0] */
};

typedef struct NX5_ONLY_PORN_BIT_Ttag {
	unsigned int only_porn : BFW_NX5_only_porn_only_porn; /* netX Firmware status */
} NX5_ONLY_PORN_BIT_T;

typedef union {
	unsigned int        val;
	NX5_ONLY_PORN_BIT_T bf;
} NX5_ONLY_PORN_T;

/* --------------------------------------------------------------------- */
/* Register netx_version */
/* => netX Revision Register: */
/*    This register contains information about netX hardware and bootloader revision. */
/*    This register is lockable by netX locking algorithm. It will be only reset on Power on, not on normal system nres. */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_netx_version       0x00000034U
#define Adr_NX5_asic_ctrl_netx_version 0x018BF834U
#define Adr_NX5_netx_version           0x018BF834U
#define DFLT_VAL_NX5_netx_version      0x00000041U

#define MSK_NX5_netx_version_netx_version      0x000000ffU
#define SRT_NX5_netx_version_netx_version      0
#define DFLT_VAL_NX5_netx_version_netx_version 0x00000041U

enum {
	BFW_NX5_netx_version_netx_version = 8,  /* [7:0] */
	BFW_NX5_netx_version_reserved1    = 24  /* [31:8] */
};

typedef struct NX5_NETX_VERSION_BIT_Ttag {
	unsigned int netx_version : BFW_NX5_netx_version_netx_version; /* netX5 revision number:                        */
	                                                               /* netX5 revision number starts with "A" (0x41). */
	unsigned int reserved1    : BFW_NX5_netx_version_reserved1;    /* reserved                                      */
} NX5_NETX_VERSION_BIT_T;

typedef union {
	unsigned int           val;
	NX5_NETX_VERSION_BIT_T bf;
} NX5_NETX_VERSION_T;

/* --------------------------------------------------------------------- */
/* Register dpm_wdg */
/* => netX DPM Watchdog register: */
/*    Write to this register to reset dpm-lock/rom-hide-watchdog, no access-key-protection. */
/*    No access key protection here. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_wdg       0x00000038U
#define Adr_NX5_asic_ctrl_dpm_wdg 0x018BF838U
#define Adr_NX5_dpm_wdg           0x018BF838U
#define DFLT_VAL_NX5_dpm_wdg      0x000001ffU

#define MSK_NX5_dpm_wdg_rst_wdg      0xffffffffU
#define SRT_NX5_dpm_wdg_rst_wdg      0
#define DFLT_VAL_NX5_dpm_wdg_rst_wdg 0x000001ffU

enum {
	BFW_NX5_dpm_wdg_rst_wdg = 32  /* [31:0] */
};

typedef struct NX5_DPM_WDG_BIT_Ttag {
	unsigned int rst_wdg : BFW_NX5_dpm_wdg_rst_wdg; /* write here to reset dpm-watchdog to 0x1ff                         */
	                                                /* The watchdog will dectrement with each positiv clk (100MHz) edge. */
} NX5_DPM_WDG_BIT_T;

typedef union {
	unsigned int      val;
	NX5_DPM_WDG_BIT_T bf;
} NX5_DPM_WDG_T;

/* --------------------------------------------------------------------- */
/* Register trigger_boot_dma */
/* => Starts Boot-DMA from INTRAM0 */
/*    This register is protected by the netX access key mechanism; changing this register is only possible by the following sequence: */
/*     */
/*    1.: read out access key from ACCESS_KEY register */
/*    2.: write back access key to ACCESS_KEY register */
/*    3.: write desired value to this register */
/*     */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_boot_dma       0x00000040U
#define Adr_NX5_asic_ctrl_trigger_boot_dma 0x018BF840U
#define Adr_NX5_trigger_boot_dma           0x018BF840U
#define DFLT_VAL_NX5_trigger_boot_dma      0x00000000U

#define MSK_NX5_trigger_boot_dma_trigger_cnt      0x0000000fU
#define SRT_NX5_trigger_boot_dma_trigger_cnt      0
#define DFLT_VAL_NX5_trigger_boot_dma_trigger_cnt 0x00000000U
#define MSK_NX5_trigger_boot_dma_trigger_key      0x000000f0U
#define SRT_NX5_trigger_boot_dma_trigger_key      4
#define DFLT_VAL_NX5_trigger_boot_dma_trigger_key 0x00000000U

enum {
	BFW_NX5_trigger_boot_dma_trigger_cnt = 4,  /* [3:0] */
	BFW_NX5_trigger_boot_dma_trigger_key = 4,  /* [7:4] */
	BFW_NX5_trigger_boot_dma_reserved1   = 24  /* [31:8] */
};

typedef struct NX5_TRIGGER_BOOT_DMA_BIT_Ttag {
	unsigned int trigger_cnt : BFW_NX5_trigger_boot_dma_trigger_cnt; /* Write delay cycles to start Boot DMA system initialisation from INTRAM0 */
	                                                                 /* To start count down, trigger_key must be 0x5.                           */
	unsigned int trigger_key : BFW_NX5_trigger_boot_dma_trigger_key; /* Write 0x5 to start trigger_cnt down count                               */
	                                                                 /* Always 0x0 when read.                                                   */
	unsigned int reserved1   : BFW_NX5_trigger_boot_dma_reserved1;   /* reserved                                                                */
} NX5_TRIGGER_BOOT_DMA_BIT_T;

typedef union {
	unsigned int               val;
	NX5_TRIGGER_BOOT_DMA_BIT_T bf;
} NX5_TRIGGER_BOOT_DMA_T;

/* --------------------------------------------------------------------- */
/* Register asic_ctrl_access_key */
/* => ASIC Control Locking Access Key Register: */
/*    Writing to any register in the asic_ctrl address area is only possible after */
/*    setting the correct key here to avoid unmeant changes e.g. by crashed software. */
/*    ---- */
/*    Changing a control register in the asic_ctrl address area is only possible by the following sequence: */
/*    1.: Read out the Locking Access Key from this register. */
/*    2.: Write back this Locking Access Key to this register. */
/*    3.: Write desired value to the control register. */
/*    ---- */
/*    The Locking Access Key will become invalid after each access to any register in the asic_ctrl address area */
/*    and has to be read out and set again for sequent accesses. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_asic_ctrl_access_key       0x00000070U
#define Adr_NX5_asic_ctrl_asic_ctrl_access_key 0x018BF870U
#define Adr_NX5_asic_ctrl_access_key           0x018BF870U
#define DFLT_VAL_NX5_asic_ctrl_access_key      0x00000000U

#define MSK_NX5_asic_ctrl_access_key_access_key      0x0000ffffU
#define SRT_NX5_asic_ctrl_access_key_access_key      0
#define DFLT_VAL_NX5_asic_ctrl_access_key_access_key 0x00000000U

enum {
	BFW_NX5_asic_ctrl_access_key_access_key = 16, /* [15:0] */
	BFW_NX5_asic_ctrl_access_key_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_ASIC_CTRL_ACCESS_KEY_BIT_Ttag {
	unsigned int access_key : BFW_NX5_asic_ctrl_access_key_access_key; /* Locking Access Key for next write access. */
	unsigned int reserved1  : BFW_NX5_asic_ctrl_access_key_reserved1;  /* reserved                                  */
} NX5_ASIC_CTRL_ACCESS_KEY_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_ASIC_CTRL_ACCESS_KEY_BIT_T bf;
} NX5_ASIC_CTRL_ACCESS_KEY_T;

/* --------------------------------------------------------------------- */
/* Register netx_lock_reserved00 */
/* => reserved address for netX locking purpose */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_netx_lock_reserved00       0x00000074U
#define Adr_NX5_asic_ctrl_netx_lock_reserved00 0x018BF874U
#define Adr_NX5_netx_lock_reserved00           0x018BF874U

#define MSK_NX5_netx_lock_reserved00_lock 0xffffffffU
#define SRT_NX5_netx_lock_reserved00_lock 0

enum {
	BFW_NX5_netx_lock_reserved00_lock = 32  /* [31:0] */
};

typedef struct NX5_NETX_LOCK_RESERVED00_BIT_Ttag {
	unsigned int lock : BFW_NX5_netx_lock_reserved00_lock; /* locking purpose */
} NX5_NETX_LOCK_RESERVED00_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_NETX_LOCK_RESERVED00_BIT_T bf;
} NX5_NETX_LOCK_RESERVED00_T;

/* --------------------------------------------------------------------- */
/* Register netx_lock_reserved01 */
/* => reserved address for netX locking purpose */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_netx_lock_reserved01       0x00000078U
#define Adr_NX5_asic_ctrl_netx_lock_reserved01 0x018BF878U
#define Adr_NX5_netx_lock_reserved01           0x018BF878U

#define MSK_NX5_netx_lock_reserved01_lock 0xffffffffU
#define SRT_NX5_netx_lock_reserved01_lock 0

enum {
	BFW_NX5_netx_lock_reserved01_lock = 32  /* [31:0] */
};

typedef struct NX5_NETX_LOCK_RESERVED01_BIT_Ttag {
	unsigned int lock : BFW_NX5_netx_lock_reserved01_lock; /* locking purpose */
} NX5_NETX_LOCK_RESERVED01_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_NETX_LOCK_RESERVED01_BIT_T bf;
} NX5_NETX_LOCK_RESERVED01_T;

/* --------------------------------------------------------------------- */
/* Register netx_lock_reserved_start */
/* => Reserved start address for netX locking purpose address area */
/*    Don't implement other registers at 0x80 .. 0xfc! */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_netx_lock_reserved_start       0x00000080U
#define Adr_NX5_asic_ctrl_netx_lock_reserved_start 0x018BF880U
#define Adr_NX5_netx_lock_reserved_start           0x018BF880U

#define MSK_NX5_netx_lock_reserved_start_lock 0xffffffffU
#define SRT_NX5_netx_lock_reserved_start_lock 0

enum {
	BFW_NX5_netx_lock_reserved_start_lock = 32  /* [31:0] */
};

typedef struct NX5_NETX_LOCK_RESERVED_START_BIT_Ttag {
	unsigned int lock : BFW_NX5_netx_lock_reserved_start_lock; /* locking purpose */
} NX5_NETX_LOCK_RESERVED_START_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_NETX_LOCK_RESERVED_START_BIT_T bf;
} NX5_NETX_LOCK_RESERVED_START_T;

/* --------------------------------------------------------------------- */
/* Register netx_lock_reserved_end */
/* => Reserved end address for netX locking purpose address area */
/*    Don't implement other registers at 0x80 .. 0xfc! */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_netx_lock_reserved_end       0x000000FCU
#define Adr_NX5_asic_ctrl_netx_lock_reserved_end 0x018BF8FCU
#define Adr_NX5_netx_lock_reserved_end           0x018BF8FCU

#define MSK_NX5_netx_lock_reserved_end_lock 0xffffffffU
#define SRT_NX5_netx_lock_reserved_end_lock 0

enum {
	BFW_NX5_netx_lock_reserved_end_lock = 32  /* [31:0] */
};

typedef struct NX5_NETX_LOCK_RESERVED_END_BIT_Ttag {
	unsigned int lock : BFW_NX5_netx_lock_reserved_end_lock; /* locking purpose */
} NX5_NETX_LOCK_RESERVED_END_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_NETX_LOCK_RESERVED_END_BIT_T bf;
} NX5_NETX_LOCK_RESERVED_END_T;


/* ===================================================================== */

/* Area of abort */

/* ===================================================================== */

#define Addr_NX5_abort      0x018BF900U
#define NX5_NETX_ABORT_AREA 0x018BF900U

/* ===================================================================== */

/* Area of zpu */

/* ===================================================================== */

#define Addr_NX5_zpu 0x018BF940U

/* --------------------------------------------------------------------- */
/* Register zpu_counter */
/* => ZPU Downcounter */
/*    Counts down from programmed value to zero, then stops there. */
/*    Generates ZPU Interrupt if zpu_counter == 0. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_counter  0x00000000U
#define Adr_NX5_zpu_zpu_counter  0x018BF940U
#define Adr_NX5_zpu_counter      0x018BF940U
#define DFLT_VAL_NX5_zpu_counter 0x00000000U

#define MSK_NX5_zpu_counter_cnt      0xffffffffU
#define SRT_NX5_zpu_counter_cnt      0
#define DFLT_VAL_NX5_zpu_counter_cnt 0x00000000U

enum {
	BFW_NX5_zpu_counter_cnt = 32  /* [31:0] */
};

typedef struct NX5_ZPU_COUNTER_BIT_Ttag {
	unsigned int cnt : BFW_NX5_zpu_counter_cnt; /* counter value */
} NX5_ZPU_COUNTER_BIT_T;

typedef union {
	unsigned int          val;
	NX5_ZPU_COUNTER_BIT_T bf;
} NX5_ZPU_COUNTER_T;

/* --------------------------------------------------------------------- */
/* Register zpu_irq_raw */
/* => ZPU Raw IRQ register: */
/*    Shows status of unmasked IRQs. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_irq_raw 0x00000004U
#define Adr_NX5_zpu_zpu_irq_raw 0x018BF944U
#define Adr_NX5_zpu_irq_raw     0x018BF944U

#define MSK_NX5_zpu_irq_raw_xpec0_irq             0x00000001U
#define SRT_NX5_zpu_irq_raw_xpec0_irq             0
#define MSK_NX5_zpu_irq_raw_xpec1_irq             0x00000002U
#define SRT_NX5_zpu_irq_raw_xpec1_irq             1
#define MSK_NX5_zpu_irq_raw_sync0_irq             0x00000004U
#define SRT_NX5_zpu_irq_raw_sync0_irq             2
#define MSK_NX5_zpu_irq_raw_sync1_irq             0x00000008U
#define SRT_NX5_zpu_irq_raw_sync1_irq             3
#define MSK_NX5_zpu_irq_raw_trigger_lt_irq        0x00000010U
#define SRT_NX5_zpu_irq_raw_trigger_lt_irq        4
#define MSK_NX5_zpu_irq_raw_phy0_irq              0x00000020U
#define SRT_NX5_zpu_irq_raw_phy0_irq              5
#define MSK_NX5_zpu_irq_raw_phy1_irq              0x00000040U
#define SRT_NX5_zpu_irq_raw_phy1_irq              6
#define MSK_NX5_zpu_irq_raw_spi_irq               0x00000080U
#define SRT_NX5_zpu_irq_raw_spi_irq               7
#define MSK_NX5_zpu_irq_raw_systime_s_compare_irq 0x00000100U
#define SRT_NX5_zpu_irq_raw_systime_s_compare_irq 8
#define MSK_NX5_zpu_irq_raw_pio0                  0x00000200U
#define SRT_NX5_zpu_irq_raw_pio0                  9
#define MSK_NX5_zpu_irq_raw_pio0n                 0x00000400U
#define SRT_NX5_zpu_irq_raw_pio0n                 10
#define MSK_NX5_zpu_irq_raw_pio1                  0x00000800U
#define SRT_NX5_zpu_irq_raw_pio1                  11
#define MSK_NX5_zpu_irq_raw_pio1n                 0x00001000U
#define SRT_NX5_zpu_irq_raw_pio1n                 12
#define MSK_NX5_zpu_irq_raw_zpu_counter           0x00002000U
#define SRT_NX5_zpu_irq_raw_zpu_counter           13
#define MSK_NX5_zpu_irq_raw_zpu_sw_irq            0x00004000U
#define SRT_NX5_zpu_irq_raw_zpu_sw_irq            14

enum {
	BFW_NX5_zpu_irq_raw_xpec0_irq             = 1,  /* [0] */
	BFW_NX5_zpu_irq_raw_xpec1_irq             = 1,  /* [1] */
	BFW_NX5_zpu_irq_raw_sync0_irq             = 1,  /* [2] */
	BFW_NX5_zpu_irq_raw_sync1_irq             = 1,  /* [3] */
	BFW_NX5_zpu_irq_raw_trigger_lt_irq        = 1,  /* [4] */
	BFW_NX5_zpu_irq_raw_phy0_irq              = 1,  /* [5] */
	BFW_NX5_zpu_irq_raw_phy1_irq              = 1,  /* [6] */
	BFW_NX5_zpu_irq_raw_spi_irq               = 1,  /* [7] */
	BFW_NX5_zpu_irq_raw_systime_s_compare_irq = 1,  /* [8] */
	BFW_NX5_zpu_irq_raw_pio0                  = 1,  /* [9] */
	BFW_NX5_zpu_irq_raw_pio0n                 = 1,  /* [10] */
	BFW_NX5_zpu_irq_raw_pio1                  = 1,  /* [11] */
	BFW_NX5_zpu_irq_raw_pio1n                 = 1,  /* [12] */
	BFW_NX5_zpu_irq_raw_zpu_counter           = 1,  /* [13] */
	BFW_NX5_zpu_irq_raw_zpu_sw_irq            = 1,  /* [14] */
	BFW_NX5_zpu_irq_raw_reserved1             = 17  /* [31:15] */
};

typedef struct NX5_ZPU_IRQ_RAW_BIT_Ttag {
	unsigned int xpec0_irq             : BFW_NX5_zpu_irq_raw_xpec0_irq;             /* Communication channel 0 (or of irq-reg 0-11)           */
	unsigned int xpec1_irq             : BFW_NX5_zpu_irq_raw_xpec1_irq;             /* Communication channel 1 (or of irq-reg 0-11)           */
	unsigned int sync0_irq             : BFW_NX5_zpu_irq_raw_sync0_irq;             /* Motion synchronization channel 0 (or of irq-reg 12-15) */
	unsigned int sync1_irq             : BFW_NX5_zpu_irq_raw_sync1_irq;             /* Motion synchronization channel 1 (or of irq-reg 12-15) */
	unsigned int trigger_lt_irq        : BFW_NX5_zpu_irq_raw_trigger_lt_irq;        /* trigger latch Unit from XC                             */
	unsigned int phy0_irq              : BFW_NX5_zpu_irq_raw_phy0_irq;              /* from external Phy 0                                    */
	unsigned int phy1_irq              : BFW_NX5_zpu_irq_raw_phy1_irq;              /* from external Phy 1                                    */
	unsigned int spi_irq               : BFW_NX5_zpu_irq_raw_spi_irq;               /* SPI module (not serial DPM)                            */
	unsigned int systime_s_compare_irq : BFW_NX5_zpu_irq_raw_systime_s_compare_irq; /* systime_s systime 1day IRQ                             */
	unsigned int pio0                  : BFW_NX5_zpu_irq_raw_pio0;                  /* pio0                                                   */
	unsigned int pio0n                 : BFW_NX5_zpu_irq_raw_pio0n;                 /* inverted pio0                                          */
	unsigned int pio1                  : BFW_NX5_zpu_irq_raw_pio1;                  /* pio1                                                   */
	unsigned int pio1n                 : BFW_NX5_zpu_irq_raw_pio1n;                 /* inverted pio1                                          */
	unsigned int zpu_counter           : BFW_NX5_zpu_irq_raw_zpu_counter;           /* zpu_counter interrupt                                  */
	unsigned int zpu_sw_irq            : BFW_NX5_zpu_irq_raw_zpu_sw_irq;            /* zpu sw interrupt interrupt (always 1)                  */
	unsigned int reserved1             : BFW_NX5_zpu_irq_raw_reserved1;             /* reserved                                               */
} NX5_ZPU_IRQ_RAW_BIT_T;

typedef union {
	unsigned int          val;
	NX5_ZPU_IRQ_RAW_BIT_T bf;
} NX5_ZPU_IRQ_RAW_T;

/* --------------------------------------------------------------------- */
/* Register zpu_irq_masked */
/* => ZPU Masked IRQ register */
/*    Read access shows status of masked IRQs (OR of all these bits is connected to ZPU) */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_irq_masked 0x00000008U
#define Adr_NX5_zpu_zpu_irq_masked 0x018BF948U
#define Adr_NX5_zpu_irq_masked     0x018BF948U

#define MSK_NX5_zpu_irq_masked_xpec0_irq             0x00000001U
#define SRT_NX5_zpu_irq_masked_xpec0_irq             0
#define MSK_NX5_zpu_irq_masked_xpec1_irq             0x00000002U
#define SRT_NX5_zpu_irq_masked_xpec1_irq             1
#define MSK_NX5_zpu_irq_masked_sync0_irq             0x00000004U
#define SRT_NX5_zpu_irq_masked_sync0_irq             2
#define MSK_NX5_zpu_irq_masked_sync1_irq             0x00000008U
#define SRT_NX5_zpu_irq_masked_sync1_irq             3
#define MSK_NX5_zpu_irq_masked_trigger_lt_irq        0x00000010U
#define SRT_NX5_zpu_irq_masked_trigger_lt_irq        4
#define MSK_NX5_zpu_irq_masked_phy0_irq              0x00000020U
#define SRT_NX5_zpu_irq_masked_phy0_irq              5
#define MSK_NX5_zpu_irq_masked_phy1_irq              0x00000040U
#define SRT_NX5_zpu_irq_masked_phy1_irq              6
#define MSK_NX5_zpu_irq_masked_spi_irq               0x00000080U
#define SRT_NX5_zpu_irq_masked_spi_irq               7
#define MSK_NX5_zpu_irq_masked_systime_s_compare_irq 0x00000100U
#define SRT_NX5_zpu_irq_masked_systime_s_compare_irq 8
#define MSK_NX5_zpu_irq_masked_pio0                  0x00000200U
#define SRT_NX5_zpu_irq_masked_pio0                  9
#define MSK_NX5_zpu_irq_masked_pio0n                 0x00000400U
#define SRT_NX5_zpu_irq_masked_pio0n                 10
#define MSK_NX5_zpu_irq_masked_pio1                  0x00000800U
#define SRT_NX5_zpu_irq_masked_pio1                  11
#define MSK_NX5_zpu_irq_masked_pio1n                 0x00001000U
#define SRT_NX5_zpu_irq_masked_pio1n                 12
#define MSK_NX5_zpu_irq_masked_zpu_counter           0x00002000U
#define SRT_NX5_zpu_irq_masked_zpu_counter           13
#define MSK_NX5_zpu_irq_masked_zpu_sw_irq            0x00004000U
#define SRT_NX5_zpu_irq_masked_zpu_sw_irq            14

enum {
	BFW_NX5_zpu_irq_masked_xpec0_irq             = 1,  /* [0] */
	BFW_NX5_zpu_irq_masked_xpec1_irq             = 1,  /* [1] */
	BFW_NX5_zpu_irq_masked_sync0_irq             = 1,  /* [2] */
	BFW_NX5_zpu_irq_masked_sync1_irq             = 1,  /* [3] */
	BFW_NX5_zpu_irq_masked_trigger_lt_irq        = 1,  /* [4] */
	BFW_NX5_zpu_irq_masked_phy0_irq              = 1,  /* [5] */
	BFW_NX5_zpu_irq_masked_phy1_irq              = 1,  /* [6] */
	BFW_NX5_zpu_irq_masked_spi_irq               = 1,  /* [7] */
	BFW_NX5_zpu_irq_masked_systime_s_compare_irq = 1,  /* [8] */
	BFW_NX5_zpu_irq_masked_pio0                  = 1,  /* [9] */
	BFW_NX5_zpu_irq_masked_pio0n                 = 1,  /* [10] */
	BFW_NX5_zpu_irq_masked_pio1                  = 1,  /* [11] */
	BFW_NX5_zpu_irq_masked_pio1n                 = 1,  /* [12] */
	BFW_NX5_zpu_irq_masked_zpu_counter           = 1,  /* [13] */
	BFW_NX5_zpu_irq_masked_zpu_sw_irq            = 1,  /* [14] */
	BFW_NX5_zpu_irq_masked_reserved1             = 17  /* [31:15] */
};

typedef struct NX5_ZPU_IRQ_MASKED_BIT_Ttag {
	unsigned int xpec0_irq             : BFW_NX5_zpu_irq_masked_xpec0_irq;             /* Communication channel 0 (or of irq-reg 0-11)           */
	unsigned int xpec1_irq             : BFW_NX5_zpu_irq_masked_xpec1_irq;             /* Communication channel 1 (or of irq-reg 0-11)           */
	unsigned int sync0_irq             : BFW_NX5_zpu_irq_masked_sync0_irq;             /* Motion synchronization channel 0 (or of irq-reg 12-15) */
	unsigned int sync1_irq             : BFW_NX5_zpu_irq_masked_sync1_irq;             /* Motion synchronization channel 1 (or of irq-reg 12-15) */
	unsigned int trigger_lt_irq        : BFW_NX5_zpu_irq_masked_trigger_lt_irq;        /* trigger latch Unit from XC                             */
	unsigned int phy0_irq              : BFW_NX5_zpu_irq_masked_phy0_irq;              /* from external Phy 0                                    */
	unsigned int phy1_irq              : BFW_NX5_zpu_irq_masked_phy1_irq;              /* from external Phy 1                                    */
	unsigned int spi_irq               : BFW_NX5_zpu_irq_masked_spi_irq;               /* SPI module (not serial DPM)                            */
	unsigned int systime_s_compare_irq : BFW_NX5_zpu_irq_masked_systime_s_compare_irq; /* systime_s systime 1day IRQ                             */
	unsigned int pio0                  : BFW_NX5_zpu_irq_masked_pio0;                  /* pio0                                                   */
	unsigned int pio0n                 : BFW_NX5_zpu_irq_masked_pio0n;                 /* inverted pio0                                          */
	unsigned int pio1                  : BFW_NX5_zpu_irq_masked_pio1;                  /* pio1                                                   */
	unsigned int pio1n                 : BFW_NX5_zpu_irq_masked_pio1n;                 /* inverted pio1                                          */
	unsigned int zpu_counter           : BFW_NX5_zpu_irq_masked_zpu_counter;           /* zpu_counter interrupt                                  */
	unsigned int zpu_sw_irq            : BFW_NX5_zpu_irq_masked_zpu_sw_irq;            /* zpu sw interrupt interrupt                             */
	unsigned int reserved1             : BFW_NX5_zpu_irq_masked_reserved1;             /* reserved                                               */
} NX5_ZPU_IRQ_MASKED_BIT_T;

typedef union {
	unsigned int             val;
	NX5_ZPU_IRQ_MASKED_BIT_T bf;
} NX5_ZPU_IRQ_MASKED_T;

/* --------------------------------------------------------------------- */
/* Register zpu_irq_mask_set */
/* => ZPU interrupt mask enable: */
/*    Write access with '1' sets interrupt mask bit (enables interrupt request for ZPU) */
/*    Write access with '0' does not influence this bit */
/*    Read access shows actual interrupt mask */
/*    Attention: Before activating interrupt mask, delete old pending interrupts */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_irq_mask_set  0x0000000CU
#define Adr_NX5_zpu_zpu_irq_mask_set  0x018BF94CU
#define Adr_NX5_zpu_irq_mask_set      0x018BF94CU
#define DFLT_VAL_NX5_zpu_irq_mask_set 0x00000000U

#define MSK_NX5_zpu_irq_mask_set_xpec0_irq                  0x00000001U
#define SRT_NX5_zpu_irq_mask_set_xpec0_irq                  0
#define DFLT_VAL_NX5_zpu_irq_mask_set_xpec0_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_set_xpec1_irq                  0x00000002U
#define SRT_NX5_zpu_irq_mask_set_xpec1_irq                  1
#define DFLT_VAL_NX5_zpu_irq_mask_set_xpec1_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_set_sync0_irq                  0x00000004U
#define SRT_NX5_zpu_irq_mask_set_sync0_irq                  2
#define DFLT_VAL_NX5_zpu_irq_mask_set_sync0_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_set_sync1_irq                  0x00000008U
#define SRT_NX5_zpu_irq_mask_set_sync1_irq                  3
#define DFLT_VAL_NX5_zpu_irq_mask_set_sync1_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_set_trigger_lt_irq             0x00000010U
#define SRT_NX5_zpu_irq_mask_set_trigger_lt_irq             4
#define DFLT_VAL_NX5_zpu_irq_mask_set_trigger_lt_irq        0x00000000U
#define MSK_NX5_zpu_irq_mask_set_phy0_irq                   0x00000020U
#define SRT_NX5_zpu_irq_mask_set_phy0_irq                   5
#define DFLT_VAL_NX5_zpu_irq_mask_set_phy0_irq              0x00000000U
#define MSK_NX5_zpu_irq_mask_set_phy1_irq                   0x00000040U
#define SRT_NX5_zpu_irq_mask_set_phy1_irq                   6
#define DFLT_VAL_NX5_zpu_irq_mask_set_phy1_irq              0x00000000U
#define MSK_NX5_zpu_irq_mask_set_spi_irq                    0x00000080U
#define SRT_NX5_zpu_irq_mask_set_spi_irq                    7
#define DFLT_VAL_NX5_zpu_irq_mask_set_spi_irq               0x00000000U
#define MSK_NX5_zpu_irq_mask_set_systime_s_compare_irq      0x00000100U
#define SRT_NX5_zpu_irq_mask_set_systime_s_compare_irq      8
#define DFLT_VAL_NX5_zpu_irq_mask_set_systime_s_compare_irq 0x00000000U
#define MSK_NX5_zpu_irq_mask_set_pio0                       0x00000200U
#define SRT_NX5_zpu_irq_mask_set_pio0                       9
#define DFLT_VAL_NX5_zpu_irq_mask_set_pio0                  0x00000000U
#define MSK_NX5_zpu_irq_mask_set_pio0n                      0x00000400U
#define SRT_NX5_zpu_irq_mask_set_pio0n                      10
#define DFLT_VAL_NX5_zpu_irq_mask_set_pio0n                 0x00000000U
#define MSK_NX5_zpu_irq_mask_set_pio1                       0x00000800U
#define SRT_NX5_zpu_irq_mask_set_pio1                       11
#define DFLT_VAL_NX5_zpu_irq_mask_set_pio1                  0x00000000U
#define MSK_NX5_zpu_irq_mask_set_pio1n                      0x00001000U
#define SRT_NX5_zpu_irq_mask_set_pio1n                      12
#define DFLT_VAL_NX5_zpu_irq_mask_set_pio1n                 0x00000000U
#define MSK_NX5_zpu_irq_mask_set_zpu_counter                0x00002000U
#define SRT_NX5_zpu_irq_mask_set_zpu_counter                13
#define DFLT_VAL_NX5_zpu_irq_mask_set_zpu_counter           0x00000000U
#define MSK_NX5_zpu_irq_mask_set_zpu_sw_irq                 0x00004000U
#define SRT_NX5_zpu_irq_mask_set_zpu_sw_irq                 14
#define DFLT_VAL_NX5_zpu_irq_mask_set_zpu_sw_irq            0x00000000U

enum {
	BFW_NX5_zpu_irq_mask_set_xpec0_irq             = 1,  /* [0] */
	BFW_NX5_zpu_irq_mask_set_xpec1_irq             = 1,  /* [1] */
	BFW_NX5_zpu_irq_mask_set_sync0_irq             = 1,  /* [2] */
	BFW_NX5_zpu_irq_mask_set_sync1_irq             = 1,  /* [3] */
	BFW_NX5_zpu_irq_mask_set_trigger_lt_irq        = 1,  /* [4] */
	BFW_NX5_zpu_irq_mask_set_phy0_irq              = 1,  /* [5] */
	BFW_NX5_zpu_irq_mask_set_phy1_irq              = 1,  /* [6] */
	BFW_NX5_zpu_irq_mask_set_spi_irq               = 1,  /* [7] */
	BFW_NX5_zpu_irq_mask_set_systime_s_compare_irq = 1,  /* [8] */
	BFW_NX5_zpu_irq_mask_set_pio0                  = 1,  /* [9] */
	BFW_NX5_zpu_irq_mask_set_pio0n                 = 1,  /* [10] */
	BFW_NX5_zpu_irq_mask_set_pio1                  = 1,  /* [11] */
	BFW_NX5_zpu_irq_mask_set_pio1n                 = 1,  /* [12] */
	BFW_NX5_zpu_irq_mask_set_zpu_counter           = 1,  /* [13] */
	BFW_NX5_zpu_irq_mask_set_zpu_sw_irq            = 1,  /* [14] */
	BFW_NX5_zpu_irq_mask_set_reserved1             = 17  /* [31:15] */
};

typedef struct NX5_ZPU_IRQ_MASK_SET_BIT_Ttag {
	unsigned int xpec0_irq             : BFW_NX5_zpu_irq_mask_set_xpec0_irq;             /* Communication channel 0 (or of irq-reg 0-11)           */
	unsigned int xpec1_irq             : BFW_NX5_zpu_irq_mask_set_xpec1_irq;             /* Communication channel 1 (or of irq-reg 0-11)           */
	unsigned int sync0_irq             : BFW_NX5_zpu_irq_mask_set_sync0_irq;             /* Motion synchronization channel 0 (or of irq-reg 12-15) */
	unsigned int sync1_irq             : BFW_NX5_zpu_irq_mask_set_sync1_irq;             /* Motion synchronization channel 1 (or of irq-reg 12-15) */
	unsigned int trigger_lt_irq        : BFW_NX5_zpu_irq_mask_set_trigger_lt_irq;        /* trigger latch Unit from XC                             */
	unsigned int phy0_irq              : BFW_NX5_zpu_irq_mask_set_phy0_irq;              /* from external Phy 0                                    */
	unsigned int phy1_irq              : BFW_NX5_zpu_irq_mask_set_phy1_irq;              /* from external Phy 1                                    */
	unsigned int spi_irq               : BFW_NX5_zpu_irq_mask_set_spi_irq;               /* SPI module (not serial DPM)                            */
	unsigned int systime_s_compare_irq : BFW_NX5_zpu_irq_mask_set_systime_s_compare_irq; /* systime_s systime 1day IRQ                             */
	unsigned int pio0                  : BFW_NX5_zpu_irq_mask_set_pio0;                  /* pio0                                                   */
	unsigned int pio0n                 : BFW_NX5_zpu_irq_mask_set_pio0n;                 /* inverted pio0                                          */
	unsigned int pio1                  : BFW_NX5_zpu_irq_mask_set_pio1;                  /* pio1                                                   */
	unsigned int pio1n                 : BFW_NX5_zpu_irq_mask_set_pio1n;                 /* inverted pio1                                          */
	unsigned int zpu_counter           : BFW_NX5_zpu_irq_mask_set_zpu_counter;           /* zpu_counter interrupt                                  */
	unsigned int zpu_sw_irq            : BFW_NX5_zpu_irq_mask_set_zpu_sw_irq;            /* zpu sw interrupt interrupt                             */
	unsigned int reserved1             : BFW_NX5_zpu_irq_mask_set_reserved1;             /* reserved                                               */
} NX5_ZPU_IRQ_MASK_SET_BIT_T;

typedef union {
	unsigned int               val;
	NX5_ZPU_IRQ_MASK_SET_BIT_T bf;
} NX5_ZPU_IRQ_MASK_SET_T;

/* --------------------------------------------------------------------- */
/* Register zpu_irq_mask_rst */
/* => ZPU interrupt mask disable: */
/*    Write access with '1' resets interrupt mask bit (disables interrupt request for ZPU) */
/*    Write access with '0' does not influence this bit */
/*    Read access shows actual interrupt mask */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_irq_mask_rst  0x00000010U
#define Adr_NX5_zpu_zpu_irq_mask_rst  0x018BF950U
#define Adr_NX5_zpu_irq_mask_rst      0x018BF950U
#define DFLT_VAL_NX5_zpu_irq_mask_rst 0x00000000U

#define MSK_NX5_zpu_irq_mask_rst_xpec0_irq                  0x00000001U
#define SRT_NX5_zpu_irq_mask_rst_xpec0_irq                  0
#define DFLT_VAL_NX5_zpu_irq_mask_rst_xpec0_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_xpec1_irq                  0x00000002U
#define SRT_NX5_zpu_irq_mask_rst_xpec1_irq                  1
#define DFLT_VAL_NX5_zpu_irq_mask_rst_xpec1_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_sync0_irq                  0x00000004U
#define SRT_NX5_zpu_irq_mask_rst_sync0_irq                  2
#define DFLT_VAL_NX5_zpu_irq_mask_rst_sync0_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_sync1_irq                  0x00000008U
#define SRT_NX5_zpu_irq_mask_rst_sync1_irq                  3
#define DFLT_VAL_NX5_zpu_irq_mask_rst_sync1_irq             0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_trigger_lt_irq             0x00000010U
#define SRT_NX5_zpu_irq_mask_rst_trigger_lt_irq             4
#define DFLT_VAL_NX5_zpu_irq_mask_rst_trigger_lt_irq        0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_phy0_irq                   0x00000020U
#define SRT_NX5_zpu_irq_mask_rst_phy0_irq                   5
#define DFLT_VAL_NX5_zpu_irq_mask_rst_phy0_irq              0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_phy1_irq                   0x00000040U
#define SRT_NX5_zpu_irq_mask_rst_phy1_irq                   6
#define DFLT_VAL_NX5_zpu_irq_mask_rst_phy1_irq              0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_spi_irq                    0x00000080U
#define SRT_NX5_zpu_irq_mask_rst_spi_irq                    7
#define DFLT_VAL_NX5_zpu_irq_mask_rst_spi_irq               0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_systime_s_compare_irq      0x00000100U
#define SRT_NX5_zpu_irq_mask_rst_systime_s_compare_irq      8
#define DFLT_VAL_NX5_zpu_irq_mask_rst_systime_s_compare_irq 0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_pio0                       0x00000200U
#define SRT_NX5_zpu_irq_mask_rst_pio0                       9
#define DFLT_VAL_NX5_zpu_irq_mask_rst_pio0                  0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_pio0n                      0x00000400U
#define SRT_NX5_zpu_irq_mask_rst_pio0n                      10
#define DFLT_VAL_NX5_zpu_irq_mask_rst_pio0n                 0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_pio1                       0x00000800U
#define SRT_NX5_zpu_irq_mask_rst_pio1                       11
#define DFLT_VAL_NX5_zpu_irq_mask_rst_pio1                  0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_pio1n                      0x00001000U
#define SRT_NX5_zpu_irq_mask_rst_pio1n                      12
#define DFLT_VAL_NX5_zpu_irq_mask_rst_pio1n                 0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_zpu_counter                0x00002000U
#define SRT_NX5_zpu_irq_mask_rst_zpu_counter                13
#define DFLT_VAL_NX5_zpu_irq_mask_rst_zpu_counter           0x00000000U
#define MSK_NX5_zpu_irq_mask_rst_zpu_sw_irq                 0x00004000U
#define SRT_NX5_zpu_irq_mask_rst_zpu_sw_irq                 14
#define DFLT_VAL_NX5_zpu_irq_mask_rst_zpu_sw_irq            0x00000000U

enum {
	BFW_NX5_zpu_irq_mask_rst_xpec0_irq             = 1,  /* [0] */
	BFW_NX5_zpu_irq_mask_rst_xpec1_irq             = 1,  /* [1] */
	BFW_NX5_zpu_irq_mask_rst_sync0_irq             = 1,  /* [2] */
	BFW_NX5_zpu_irq_mask_rst_sync1_irq             = 1,  /* [3] */
	BFW_NX5_zpu_irq_mask_rst_trigger_lt_irq        = 1,  /* [4] */
	BFW_NX5_zpu_irq_mask_rst_phy0_irq              = 1,  /* [5] */
	BFW_NX5_zpu_irq_mask_rst_phy1_irq              = 1,  /* [6] */
	BFW_NX5_zpu_irq_mask_rst_spi_irq               = 1,  /* [7] */
	BFW_NX5_zpu_irq_mask_rst_systime_s_compare_irq = 1,  /* [8] */
	BFW_NX5_zpu_irq_mask_rst_pio0                  = 1,  /* [9] */
	BFW_NX5_zpu_irq_mask_rst_pio0n                 = 1,  /* [10] */
	BFW_NX5_zpu_irq_mask_rst_pio1                  = 1,  /* [11] */
	BFW_NX5_zpu_irq_mask_rst_pio1n                 = 1,  /* [12] */
	BFW_NX5_zpu_irq_mask_rst_zpu_counter           = 1,  /* [13] */
	BFW_NX5_zpu_irq_mask_rst_zpu_sw_irq            = 1,  /* [14] */
	BFW_NX5_zpu_irq_mask_rst_reserved1             = 17  /* [31:15] */
};

typedef struct NX5_ZPU_IRQ_MASK_RST_BIT_Ttag {
	unsigned int xpec0_irq             : BFW_NX5_zpu_irq_mask_rst_xpec0_irq;             /* Communication channel 0 (or of irq-reg 0-11)           */
	unsigned int xpec1_irq             : BFW_NX5_zpu_irq_mask_rst_xpec1_irq;             /* Communication channel 1 (or of irq-reg 0-11)           */
	unsigned int sync0_irq             : BFW_NX5_zpu_irq_mask_rst_sync0_irq;             /* Motion synchronization channel 0 (or of irq-reg 12-15) */
	unsigned int sync1_irq             : BFW_NX5_zpu_irq_mask_rst_sync1_irq;             /* Motion synchronization channel 1 (or of irq-reg 12-15) */
	unsigned int trigger_lt_irq        : BFW_NX5_zpu_irq_mask_rst_trigger_lt_irq;        /* trigger latch Unit from XC                             */
	unsigned int phy0_irq              : BFW_NX5_zpu_irq_mask_rst_phy0_irq;              /* from external Phy 0                                    */
	unsigned int phy1_irq              : BFW_NX5_zpu_irq_mask_rst_phy1_irq;              /* from external Phy 1                                    */
	unsigned int spi_irq               : BFW_NX5_zpu_irq_mask_rst_spi_irq;               /* SPI module (not serial DPM)                            */
	unsigned int systime_s_compare_irq : BFW_NX5_zpu_irq_mask_rst_systime_s_compare_irq; /* systime_s systime 1day IRQ                             */
	unsigned int pio0                  : BFW_NX5_zpu_irq_mask_rst_pio0;                  /* pio0                                                   */
	unsigned int pio0n                 : BFW_NX5_zpu_irq_mask_rst_pio0n;                 /* inverted pio0                                          */
	unsigned int pio1                  : BFW_NX5_zpu_irq_mask_rst_pio1;                  /* pio1                                                   */
	unsigned int pio1n                 : BFW_NX5_zpu_irq_mask_rst_pio1n;                 /* inverted pio1                                          */
	unsigned int zpu_counter           : BFW_NX5_zpu_irq_mask_rst_zpu_counter;           /* zpu_counter interrupt                                  */
	unsigned int zpu_sw_irq            : BFW_NX5_zpu_irq_mask_rst_zpu_sw_irq;            /* zpu sw interrupt interrupt                             */
	unsigned int reserved1             : BFW_NX5_zpu_irq_mask_rst_reserved1;             /* reserved                                               */
} NX5_ZPU_IRQ_MASK_RST_BIT_T;

typedef union {
	unsigned int               val;
	NX5_ZPU_IRQ_MASK_RST_BIT_T bf;
} NX5_ZPU_IRQ_MASK_RST_T;

/* --------------------------------------------------------------------- */
/* Register zpu_irq_vector */
/* => Interrupt Vector: */
/*    In case of interrupt, ZPU jumps to this address. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_irq_vector  0x00000014U
#define Adr_NX5_zpu_zpu_irq_vector  0x018BF954U
#define Adr_NX5_zpu_irq_vector      0x018BF954U
#define DFLT_VAL_NX5_zpu_irq_vector 0x00000001U

#define MSK_NX5_zpu_irq_vector_irq_vec      0x00001fffU
#define SRT_NX5_zpu_irq_vector_irq_vec      0
#define DFLT_VAL_NX5_zpu_irq_vector_irq_vec 0x00000001U

enum {
	BFW_NX5_zpu_irq_vector_irq_vec   = 13, /* [12:0] */
	BFW_NX5_zpu_irq_vector_reserved1 = 19  /* [31:13] */
};

typedef struct NX5_ZPU_IRQ_VECTOR_BIT_Ttag {
	unsigned int irq_vec   : BFW_NX5_zpu_irq_vector_irq_vec;   /* irq jump address = zpu_irq_vector * 0x20 */
	unsigned int reserved1 : BFW_NX5_zpu_irq_vector_reserved1; /* reserved                                 */
} NX5_ZPU_IRQ_VECTOR_BIT_T;

typedef union {
	unsigned int             val;
	NX5_ZPU_IRQ_VECTOR_BIT_T bf;
} NX5_ZPU_IRQ_VECTOR_T;

/* --------------------------------------------------------------------- */
/* Register zpu_emulate_offset */
/* => Offset for ZPU's emulate commands: */
/*    The ZPU knows 32 EMULATE commands. Its microcode covers an area of 0x400 and is originally located inside ROM. */
/*    This value allows to move the ZPU emulate microcode e.g. to RAM area. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_emulate_offset  0x00000018U
#define Adr_NX5_zpu_zpu_emulate_offset  0x018BF958U
#define Adr_NX5_zpu_emulate_offset      0x018BF958U
#define DFLT_VAL_NX5_zpu_emulate_offset 0x00000040U

#define MSK_NX5_zpu_emulate_offset_offset           0x000000ffU
#define SRT_NX5_zpu_emulate_offset_offset           0
#define DFLT_VAL_NX5_zpu_emulate_offset_offset      0x00000040U
#define MSK_NX5_zpu_emulate_offset_emu_pushpop      0x00000100U
#define SRT_NX5_zpu_emulate_offset_emu_pushpop      8
#define DFLT_VAL_NX5_zpu_emulate_offset_emu_pushpop 0x00000000U
#define MSK_NX5_zpu_emulate_offset_emu_branch       0x00000200U
#define SRT_NX5_zpu_emulate_offset_emu_branch       9
#define DFLT_VAL_NX5_zpu_emulate_offset_emu_branch  0x00000000U
#define MSK_NX5_zpu_emulate_offset_emu_subeq        0x00000400U
#define SRT_NX5_zpu_emulate_offset_emu_subeq        10
#define DFLT_VAL_NX5_zpu_emulate_offset_emu_subeq   0x00000000U
#define MSK_NX5_zpu_emulate_offset_emu_shift        0x00000800U
#define SRT_NX5_zpu_emulate_offset_emu_shift        11
#define DFLT_VAL_NX5_zpu_emulate_offset_emu_shift   0x00000000U
#define MSK_NX5_zpu_emulate_offset_emu_less         0x00001000U
#define SRT_NX5_zpu_emulate_offset_emu_less         12
#define DFLT_VAL_NX5_zpu_emulate_offset_emu_less    0x00000000U

enum {
	BFW_NX5_zpu_emulate_offset_offset      = 8,  /* [7:0] */
	BFW_NX5_zpu_emulate_offset_emu_pushpop = 1,  /* [8] */
	BFW_NX5_zpu_emulate_offset_emu_branch  = 1,  /* [9] */
	BFW_NX5_zpu_emulate_offset_emu_subeq   = 1,  /* [10] */
	BFW_NX5_zpu_emulate_offset_emu_shift   = 1,  /* [11] */
	BFW_NX5_zpu_emulate_offset_emu_less    = 1,  /* [12] */
	BFW_NX5_zpu_emulate_offset_reserved1   = 19  /* [31:13] */
};

typedef struct NX5_ZPU_EMULATE_OFFSET_BIT_Ttag {
	unsigned int offset      : BFW_NX5_zpu_emulate_offset_offset;      /* offset address * 0x400                                                      */
	unsigned int emu_pushpop : BFW_NX5_zpu_emulate_offset_emu_pushpop; /* emulate Poppcrel and Pushspadd instead of using special HW                  */
	unsigned int emu_branch  : BFW_NX5_zpu_emulate_offset_emu_branch;  /* emulate Eqbranch and Neqbranch instead of using special HW                  */
	unsigned int emu_subeq   : BFW_NX5_zpu_emulate_offset_emu_subeq;   /* emulate Eq, Neq and Sub instead of using special HW                         */
	unsigned int emu_shift   : BFW_NX5_zpu_emulate_offset_emu_shift;   /* emulate Ashiftleft, Ashiftright and Lshiftright instead of using special HW */
	unsigned int emu_less    : BFW_NX5_zpu_emulate_offset_emu_less;    /* emulate Lessthan and Lessthanorequal instead of using special HW            */
	unsigned int reserved1   : BFW_NX5_zpu_emulate_offset_reserved1;   /* reserved                                                                    */
} NX5_ZPU_EMULATE_OFFSET_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_ZPU_EMULATE_OFFSET_BIT_T bf;
} NX5_ZPU_EMULATE_OFFSET_T;

/* --------------------------------------------------------------------- */
/* Register zpu_pc */
/* => Program counter of ZPU: */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_pc 0x0000001CU
#define Adr_NX5_zpu_zpu_pc 0x018BF95CU
#define Adr_NX5_zpu_pc     0x018BF95CU

#define MSK_NX5_zpu_pc_pc 0x000fffffU
#define SRT_NX5_zpu_pc_pc 0

enum {
	BFW_NX5_zpu_pc_pc        = 20, /* [19:0] */
	BFW_NX5_zpu_pc_reserved1 = 12  /* [31:20] */
};

typedef struct NX5_ZPU_PC_BIT_Ttag {
	unsigned int pc        : BFW_NX5_zpu_pc_pc;        /* Program counter (byte address) */
	unsigned int reserved1 : BFW_NX5_zpu_pc_reserved1; /* reserved                       */
} NX5_ZPU_PC_BIT_T;

typedef union {
	unsigned int     val;
	NX5_ZPU_PC_BIT_T bf;
} NX5_ZPU_PC_T;

/* --------------------------------------------------------------------- */
/* Register zpu_sp */
/* => Stack pointer of ZPU: */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_sp 0x00000020U
#define Adr_NX5_zpu_zpu_sp 0x018BF960U
#define Adr_NX5_zpu_sp     0x018BF960U

#define MSK_NX5_zpu_sp_sp 0x000ffffcU
#define SRT_NX5_zpu_sp_sp 2

enum {
	BFW_NX5_zpu_sp_reserved1 = 2,  /* [1:0] */
	BFW_NX5_zpu_sp_sp        = 18, /* [19:2] */
	BFW_NX5_zpu_sp_reserved2 = 12  /* [31:20] */
};

typedef struct NX5_ZPU_SP_BIT_Ttag {
	unsigned int reserved1 : BFW_NX5_zpu_sp_reserved1; /* reserved                      */
	unsigned int sp        : BFW_NX5_zpu_sp_sp;        /* Stack pointer (dword address) */
	unsigned int reserved2 : BFW_NX5_zpu_sp_reserved2; /* reserved                      */
} NX5_ZPU_SP_BIT_T;

typedef union {
	unsigned int     val;
	NX5_ZPU_SP_BIT_T bf;
} NX5_ZPU_SP_T;

/* --------------------------------------------------------------------- */
/* Register zpu_status */
/* => Status register of ZPU: */
/*    This register shows some read only status flags. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_status 0x00000024U
#define Adr_NX5_zpu_zpu_status 0x018BF964U
#define Adr_NX5_zpu_status     0x018BF964U

#define MSK_NX5_zpu_status_zpu_break 0x00000001U
#define SRT_NX5_zpu_status_zpu_break 0
#define MSK_NX5_zpu_status_idim_flag 0x00000002U
#define SRT_NX5_zpu_status_idim_flag 1

enum {
	BFW_NX5_zpu_status_zpu_break = 1,  /* [0] */
	BFW_NX5_zpu_status_idim_flag = 1,  /* [1] */
	BFW_NX5_zpu_status_reserved1 = 30  /* [31:2] */
};

typedef struct NX5_ZPU_STATUS_BIT_Ttag {
	unsigned int zpu_break : BFW_NX5_zpu_status_zpu_break; /* ZPU is in break state */
	unsigned int idim_flag : BFW_NX5_zpu_status_idim_flag; /* IDIM Flag of ZPU      */
	unsigned int reserved1 : BFW_NX5_zpu_status_reserved1; /* reserved              */
} NX5_ZPU_STATUS_BIT_T;

typedef union {
	unsigned int         val;
	NX5_ZPU_STATUS_BIT_T bf;
} NX5_ZPU_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register zpu_ctrl */
/* => Control register of ZPU: */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zpu_ctrl  0x00000028U
#define Adr_NX5_zpu_zpu_ctrl  0x018BF968U
#define Adr_NX5_zpu_ctrl      0x018BF968U
#define DFLT_VAL_NX5_zpu_ctrl 0x00000000U

#define MSK_NX5_zpu_ctrl_single_step           0x00000001U
#define SRT_NX5_zpu_ctrl_single_step           0
#define DFLT_VAL_NX5_zpu_ctrl_single_step      0x00000000U
#define MSK_NX5_zpu_ctrl_single_step_mode      0x00000002U
#define SRT_NX5_zpu_ctrl_single_step_mode      1
#define DFLT_VAL_NX5_zpu_ctrl_single_step_mode 0x00000000U

enum {
	BFW_NX5_zpu_ctrl_single_step      = 1,  /* [0] */
	BFW_NX5_zpu_ctrl_single_step_mode = 1,  /* [1] */
	BFW_NX5_zpu_ctrl_reserved1        = 30  /* [31:2] */
};

typedef struct NX5_ZPU_CTRL_BIT_Ttag {
	unsigned int single_step      : BFW_NX5_zpu_ctrl_single_step;      /* Writing 1 to this register lets ZPU perform 1 access, then reset this bit. */
	                                                                   /* This bit is only used in single_step_mode.                                 */
	unsigned int single_step_mode : BFW_NX5_zpu_ctrl_single_step_mode; /* Single step mode (debug mode):                                             */
	                                                                   /* 1: ZPU only processes step by step by writing 1 to single_step             */
	unsigned int reserved1        : BFW_NX5_zpu_ctrl_reserved1;        /* reserved                                                                   */
} NX5_ZPU_CTRL_BIT_T;

typedef union {
	unsigned int       val;
	NX5_ZPU_CTRL_BIT_T bf;
} NX5_ZPU_CTRL_T;


/* ===================================================================== */

/* Area of pio */

/* ===================================================================== */

#define Addr_NX5_pio      0x018BFB00U
#define NX5_NETX_PIO_AREA 0x018BFB00U

/* --------------------------------------------------------------------- */
/* Register pio_in */
/* => PIO input register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pio_in 0x00000000U
#define Adr_NX5_pio_pio_in 0x018BFB00U
#define Adr_NX5_pio_in     0x018BFB00U

#define MSK_NX5_pio_in_val 0x0000ffffU
#define SRT_NX5_pio_in_val 0

enum {
	BFW_NX5_pio_in_val       = 16, /* [15:0] */
	BFW_NX5_pio_in_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_PIO_IN_BIT_Ttag {
	unsigned int val       : BFW_NX5_pio_in_val;       /* pio input values */
	unsigned int reserved1 : BFW_NX5_pio_in_reserved1; /* reserved         */
} NX5_PIO_IN_BIT_T;

typedef union {
	unsigned int     val;
	NX5_PIO_IN_BIT_T bf;
} NX5_PIO_IN_T;

/* --------------------------------------------------------------------- */
/* Register pio_out */
/* => PIO output register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pio_out  0x00000004U
#define Adr_NX5_pio_pio_out  0x018BFB04U
#define Adr_NX5_pio_out      0x018BFB04U
#define DFLT_VAL_NX5_pio_out 0x00000000U

#define MSK_NX5_pio_out_val      0x0000ffffU
#define SRT_NX5_pio_out_val      0
#define DFLT_VAL_NX5_pio_out_val 0x00000000U

enum {
	BFW_NX5_pio_out_val       = 16, /* [15:0] */
	BFW_NX5_pio_out_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_PIO_OUT_BIT_Ttag {
	unsigned int val       : BFW_NX5_pio_out_val;       /* pio output values */
	unsigned int reserved1 : BFW_NX5_pio_out_reserved1; /* reserved          */
} NX5_PIO_OUT_BIT_T;

typedef union {
	unsigned int      val;
	NX5_PIO_OUT_BIT_T bf;
} NX5_PIO_OUT_T;

/* --------------------------------------------------------------------- */
/* Register pio_oe */
/* => PIO output enable register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pio_oe  0x00000008U
#define Adr_NX5_pio_pio_oe  0x018BFB08U
#define Adr_NX5_pio_oe      0x018BFB08U
#define DFLT_VAL_NX5_pio_oe 0x00000000U

#define MSK_NX5_pio_oe_val      0x0000ffffU
#define SRT_NX5_pio_oe_val      0
#define DFLT_VAL_NX5_pio_oe_val 0x00000000U

enum {
	BFW_NX5_pio_oe_val       = 16, /* [15:0] */
	BFW_NX5_pio_oe_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_PIO_OE_BIT_Ttag {
	unsigned int val       : BFW_NX5_pio_oe_val;       /* pio output enables */
	unsigned int reserved1 : BFW_NX5_pio_oe_reserved1; /* reserved           */
} NX5_PIO_OE_BIT_T;

typedef union {
	unsigned int     val;
	NX5_PIO_OE_BIT_T bf;
} NX5_PIO_OE_T;


/* ===================================================================== */

/* Area of miimu */

/* ===================================================================== */

#define Addr_NX5_miimu      0x018BFC00U
#define NX5_NETX_MIIMU_AREA 0x018BFC00U

/* --------------------------------------------------------------------- */
/* Register miimu_reg */
/* => MIIMU Receive/Transmit Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_miimu_reg   0x00000000U
#define Adr_NX5_miimu_miimu_reg 0x018BFC00U
#define Adr_NX5_miimu_reg       0x018BFC00U
#define DFLT_VAL_NX5_miimu_reg  0x00000010U

#define MSK_NX5_miimu_reg_miimu_snrdy           0x00000001U
#define SRT_NX5_miimu_reg_miimu_snrdy           0
#define DFLT_VAL_NX5_miimu_reg_miimu_snrdy      0x00000000U
#define MSK_NX5_miimu_reg_miimu_preamble        0x00000002U
#define SRT_NX5_miimu_reg_miimu_preamble        1
#define DFLT_VAL_NX5_miimu_reg_miimu_preamble   0x00000000U
#define MSK_NX5_miimu_reg_miimu_opmode          0x00000004U
#define SRT_NX5_miimu_reg_miimu_opmode          2
#define DFLT_VAL_NX5_miimu_reg_miimu_opmode     0x00000000U
#define MSK_NX5_miimu_reg_miimu_mdc_period      0x00000008U
#define SRT_NX5_miimu_reg_miimu_mdc_period      3
#define DFLT_VAL_NX5_miimu_reg_miimu_mdc_period 0x00000000U
#define MSK_NX5_miimu_reg_phy_nres              0x00000010U
#define SRT_NX5_miimu_reg_phy_nres              4
#define DFLT_VAL_NX5_miimu_reg_phy_nres         0x00000010U
#define MSK_NX5_miimu_reg_miimu_rta             0x00000020U
#define SRT_NX5_miimu_reg_miimu_rta             5
#define DFLT_VAL_NX5_miimu_reg_miimu_rta        0x00000000U
#define MSK_NX5_miimu_reg_miimu_regaddr         0x000007c0U
#define SRT_NX5_miimu_reg_miimu_regaddr         6
#define DFLT_VAL_NX5_miimu_reg_miimu_regaddr    0x00000000U
#define MSK_NX5_miimu_reg_miimu_phyaddr         0x0000f800U
#define SRT_NX5_miimu_reg_miimu_phyaddr         11
#define DFLT_VAL_NX5_miimu_reg_miimu_phyaddr    0x00000000U
#define MSK_NX5_miimu_reg_miimu_data            0xffff0000U
#define SRT_NX5_miimu_reg_miimu_data            16
#define DFLT_VAL_NX5_miimu_reg_miimu_data       0x00000000U

enum {
	BFW_NX5_miimu_reg_miimu_snrdy      = 1,  /* [0] */
	BFW_NX5_miimu_reg_miimu_preamble   = 1,  /* [1] */
	BFW_NX5_miimu_reg_miimu_opmode     = 1,  /* [2] */
	BFW_NX5_miimu_reg_miimu_mdc_period = 1,  /* [3] */
	BFW_NX5_miimu_reg_phy_nres         = 1,  /* [4] */
	BFW_NX5_miimu_reg_miimu_rta        = 1,  /* [5] */
	BFW_NX5_miimu_reg_miimu_regaddr    = 5,  /* [10:6] */
	BFW_NX5_miimu_reg_miimu_phyaddr    = 5,  /* [15:11] */
	BFW_NX5_miimu_reg_miimu_data       = 16  /* [31:16] */
};

typedef struct NX5_MIIMU_REG_BIT_Ttag {
	unsigned int miimu_snrdy      : BFW_NX5_miimu_reg_miimu_snrdy;      /* Start not ready                                                               */
	unsigned int miimu_preamble   : BFW_NX5_miimu_reg_miimu_preamble;   /* Send preamble                                                                 */
	unsigned int miimu_opmode     : BFW_NX5_miimu_reg_miimu_opmode;     /* Operation mode:                                                               */
	                                                                    /* 1: write                                                                      */
	unsigned int miimu_mdc_period : BFW_NX5_miimu_reg_miimu_mdc_period; /* MDC period:                                                                   */
	                                                                    /* 1: 800ns                                                                      */
	unsigned int phy_nres         : BFW_NX5_miimu_reg_phy_nres;         /* PHY hardware nReset (activ low!):                                             */
	                                                                    /* If this bit and the miimu_snrdy-bit is set, the PHYs will be hardware-reset.  */
	unsigned int miimu_rta        : BFW_NX5_miimu_reg_miimu_rta;        /* Read Turn Around field:                                                       */
	                                                                    /* 0: one bit                                                                    */
	unsigned int miimu_regaddr    : BFW_NX5_miimu_reg_miimu_regaddr;    /* Register address                                                              */
	unsigned int miimu_phyaddr    : BFW_NX5_miimu_reg_miimu_phyaddr;    /* PHY address                                                                   */
	unsigned int miimu_data       : BFW_NX5_miimu_reg_miimu_data;       /* Data to or from PHY register                                                  */
} NX5_MIIMU_REG_BIT_T;

typedef union {
	unsigned int        val;
	NX5_MIIMU_REG_BIT_T bf;
} NX5_MIIMU_REG_T;

/* --------------------------------------------------------------------- */
/* Register miimu_sw_en */
/* => MIIMU Software Mode Enable */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_miimu_sw_en   0x00000004U
#define Adr_NX5_miimu_miimu_sw_en 0x018BFC04U
#define Adr_NX5_miimu_sw_en       0x018BFC04U
#define DFLT_VAL_NX5_miimu_sw_en  0x00000000U

#define MSK_NX5_miimu_sw_en_miimu_sw_en      0x00000001U
#define SRT_NX5_miimu_sw_en_miimu_sw_en      0
#define DFLT_VAL_NX5_miimu_sw_en_miimu_sw_en 0x00000000U

enum {
	BFW_NX5_miimu_sw_en_miimu_sw_en = 1,  /* [0] */
	BFW_NX5_miimu_sw_en_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_MIIMU_SW_EN_BIT_Ttag {
	unsigned int miimu_sw_en : BFW_NX5_miimu_sw_en_miimu_sw_en; /* Enables software mode:                  */
	                                                            /* MDC, MDO and MDOE are set by software.  */
	unsigned int reserved1   : BFW_NX5_miimu_sw_en_reserved1;   /* reserved                                */
} NX5_MIIMU_SW_EN_BIT_T;

typedef union {
	unsigned int          val;
	NX5_MIIMU_SW_EN_BIT_T bf;
} NX5_MIIMU_SW_EN_T;

/* --------------------------------------------------------------------- */
/* Register miimu_sw_mdc */
/* => MIIMU Software Mode MDC Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_miimu_sw_mdc   0x00000008U
#define Adr_NX5_miimu_miimu_sw_mdc 0x018BFC08U
#define Adr_NX5_miimu_sw_mdc       0x018BFC08U
#define DFLT_VAL_NX5_miimu_sw_mdc  0x00000000U

#define MSK_NX5_miimu_sw_mdc_miimu_sw_mdc      0x00000001U
#define SRT_NX5_miimu_sw_mdc_miimu_sw_mdc      0
#define DFLT_VAL_NX5_miimu_sw_mdc_miimu_sw_mdc 0x00000000U

enum {
	BFW_NX5_miimu_sw_mdc_miimu_sw_mdc = 1,  /* [0] */
	BFW_NX5_miimu_sw_mdc_reserved1    = 31  /* [31:1] */
};

typedef struct NX5_MIIMU_SW_MDC_BIT_Ttag {
	unsigned int miimu_sw_mdc : BFW_NX5_miimu_sw_mdc_miimu_sw_mdc; /* MDC value for software mode */
	unsigned int reserved1    : BFW_NX5_miimu_sw_mdc_reserved1;    /* reserved                    */
} NX5_MIIMU_SW_MDC_BIT_T;

typedef union {
	unsigned int           val;
	NX5_MIIMU_SW_MDC_BIT_T bf;
} NX5_MIIMU_SW_MDC_T;

/* --------------------------------------------------------------------- */
/* Register miimu_sw_mdo */
/* => MIIMU Software Mode MDO Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_miimu_sw_mdo   0x0000000CU
#define Adr_NX5_miimu_miimu_sw_mdo 0x018BFC0CU
#define Adr_NX5_miimu_sw_mdo       0x018BFC0CU
#define DFLT_VAL_NX5_miimu_sw_mdo  0x00000000U

#define MSK_NX5_miimu_sw_mdo_miimu_sw_mdo      0x00000001U
#define SRT_NX5_miimu_sw_mdo_miimu_sw_mdo      0
#define DFLT_VAL_NX5_miimu_sw_mdo_miimu_sw_mdo 0x00000000U

enum {
	BFW_NX5_miimu_sw_mdo_miimu_sw_mdo = 1,  /* [0] */
	BFW_NX5_miimu_sw_mdo_reserved1    = 31  /* [31:1] */
};

typedef struct NX5_MIIMU_SW_MDO_BIT_Ttag {
	unsigned int miimu_sw_mdo : BFW_NX5_miimu_sw_mdo_miimu_sw_mdo; /* MDO value for software mode */
	unsigned int reserved1    : BFW_NX5_miimu_sw_mdo_reserved1;    /* reserved                    */
} NX5_MIIMU_SW_MDO_BIT_T;

typedef union {
	unsigned int           val;
	NX5_MIIMU_SW_MDO_BIT_T bf;
} NX5_MIIMU_SW_MDO_T;

/* --------------------------------------------------------------------- */
/* Register miimu_sw_mdoe */
/* => MIIMU Software Mode MDOE Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_miimu_sw_mdoe   0x00000010U
#define Adr_NX5_miimu_miimu_sw_mdoe 0x018BFC10U
#define Adr_NX5_miimu_sw_mdoe       0x018BFC10U
#define DFLT_VAL_NX5_miimu_sw_mdoe  0x00000000U

#define MSK_NX5_miimu_sw_mdoe_miimu_sw_mdoe      0x00000001U
#define SRT_NX5_miimu_sw_mdoe_miimu_sw_mdoe      0
#define DFLT_VAL_NX5_miimu_sw_mdoe_miimu_sw_mdoe 0x00000000U

enum {
	BFW_NX5_miimu_sw_mdoe_miimu_sw_mdoe = 1,  /* [0] */
	BFW_NX5_miimu_sw_mdoe_reserved1     = 31  /* [31:1] */
};

typedef struct NX5_MIIMU_SW_MDOE_BIT_Ttag {
	unsigned int miimu_sw_mdoe : BFW_NX5_miimu_sw_mdoe_miimu_sw_mdoe; /* MDOE value for software mode */
	unsigned int reserved1     : BFW_NX5_miimu_sw_mdoe_reserved1;     /* reserved                     */
} NX5_MIIMU_SW_MDOE_BIT_T;

typedef union {
	unsigned int            val;
	NX5_MIIMU_SW_MDOE_BIT_T bf;
} NX5_MIIMU_SW_MDOE_T;

/* --------------------------------------------------------------------- */
/* Register miimu_sw_mdi */
/* => MIIMU Software Mode MDI Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_miimu_sw_mdi   0x00000014U
#define Adr_NX5_miimu_miimu_sw_mdi 0x018BFC14U
#define Adr_NX5_miimu_sw_mdi       0x018BFC14U

#define MSK_NX5_miimu_sw_mdi_miimu_sw_mdi 0x00000001U
#define SRT_NX5_miimu_sw_mdi_miimu_sw_mdi 0

enum {
	BFW_NX5_miimu_sw_mdi_miimu_sw_mdi = 1,  /* [0] */
	BFW_NX5_miimu_sw_mdi_reserved1    = 31  /* [31:1] */
};

typedef struct NX5_MIIMU_SW_MDI_BIT_Ttag {
	unsigned int miimu_sw_mdi : BFW_NX5_miimu_sw_mdi_miimu_sw_mdi; /* current MDI value */
	unsigned int reserved1    : BFW_NX5_miimu_sw_mdi_reserved1;    /* reserved          */
} NX5_MIIMU_SW_MDI_BIT_T;

typedef union {
	unsigned int           val;
	NX5_MIIMU_SW_MDI_BIT_T bf;
} NX5_MIIMU_SW_MDI_T;


/* ===================================================================== */

/* Area of spi */

/* ===================================================================== */

#define Addr_NX5_spi 0x018BFD00U

/* --------------------------------------------------------------------- */
/* Register spi_cr0 */
/* => spi control register 0 */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_cr0  0x00000000U
#define Adr_NX5_spi_spi_cr0  0x018BFD00U
#define Adr_NX5_spi_cr0      0x018BFD00U
#define DFLT_VAL_NX5_spi_cr0 0x80080007U

#define MSK_NX5_spi_cr0_datasize             0x0000000fU
#define SRT_NX5_spi_cr0_datasize             0
#define DFLT_VAL_NX5_spi_cr0_datasize        0x00000007U
#define MSK_NX5_spi_cr0_SPO                  0x00000040U
#define SRT_NX5_spi_cr0_SPO                  6
#define DFLT_VAL_NX5_spi_cr0_SPO             0x00000000U
#define MSK_NX5_spi_cr0_SPH                  0x00000080U
#define SRT_NX5_spi_cr0_SPH                  7
#define DFLT_VAL_NX5_spi_cr0_SPH             0x00000000U
#define MSK_NX5_spi_cr0_sck_muladd           0x000fff00U
#define SRT_NX5_spi_cr0_sck_muladd           8
#define DFLT_VAL_NX5_spi_cr0_sck_muladd      0x00080000U
#define MSK_NX5_spi_cr0_format               0x03000000U
#define SRT_NX5_spi_cr0_format               24
#define DFLT_VAL_NX5_spi_cr0_format          0x00000000U
#define MSK_NX5_spi_cr0_filter_in            0x08000000U
#define SRT_NX5_spi_cr0_filter_in            27
#define DFLT_VAL_NX5_spi_cr0_filter_in       0x00000000U
#define MSK_NX5_spi_cr0_slave_sig_early      0x10000000U
#define SRT_NX5_spi_cr0_slave_sig_early      28
#define DFLT_VAL_NX5_spi_cr0_slave_sig_early 0x00000000U
#define MSK_NX5_spi_cr0_netx100_comp         0x80000000U
#define SRT_NX5_spi_cr0_netx100_comp         31
#define DFLT_VAL_NX5_spi_cr0_netx100_comp    0x80000000U

enum {
	BFW_NX5_spi_cr0_datasize        = 4,  /* [3:0] */
	BFW_NX5_spi_cr0_reserved1       = 2,  /* [5:4] */
	BFW_NX5_spi_cr0_SPO             = 1,  /* [6] */
	BFW_NX5_spi_cr0_SPH             = 1,  /* [7] */
	BFW_NX5_spi_cr0_sck_muladd      = 12, /* [19:8] */
	BFW_NX5_spi_cr0_reserved2       = 4,  /* [23:20] */
	BFW_NX5_spi_cr0_format          = 2,  /* [25:24] */
	BFW_NX5_spi_cr0_reserved3       = 1,  /* [26] */
	BFW_NX5_spi_cr0_filter_in       = 1,  /* [27] */
	BFW_NX5_spi_cr0_slave_sig_early = 1,  /* [28] */
	BFW_NX5_spi_cr0_reserved4       = 2,  /* [30:29] */
	BFW_NX5_spi_cr0_netx100_comp    = 1   /* [31] */
};

typedef struct NX5_SPI_CR0_BIT_Ttag {
	unsigned int datasize        : BFW_NX5_spi_cr0_datasize;        /* DSS: data size select (transfer size = datasize + 1 bits)                                      */
	                                                                /* 0000...0010: reserved                                                                          */
	unsigned int reserved1       : BFW_NX5_spi_cr0_reserved1;       /* reserved                                                                                       */
	unsigned int SPO             : BFW_NX5_spi_cr0_SPO;             /* serial clock polarity (netx500: CR_cpol)                                                       */
	                                                                /* 0: idle: clock is low, first edge is rising                                                    */
	unsigned int SPH             : BFW_NX5_spi_cr0_SPH;             /* serial clock phase (netx500: CR_ncpha)                                                         */
	                                                                /* 1: sample data at second clock edge edge, data is generated half a clock phase before sampling */
	unsigned int sck_muladd      : BFW_NX5_spi_cr0_sck_muladd;      /* serial clock rate multiply add value for master spi_sck generation                             */
	                                                                /* spi_sck-frequency: f_spi_sck = (sck_muladd * 100)/4096 [MHz]                                   */
	unsigned int reserved2       : BFW_NX5_spi_cr0_reserved2;       /* reserved                                                                                       */
	unsigned int format          : BFW_NX5_spi_cr0_format;          /* frame format                                                                                   */
	                                                                /* 00: Motorola SPI frame format                                                                  */
	unsigned int reserved3       : BFW_NX5_spi_cr0_reserved3;       /* reserved                                                                                       */
	unsigned int filter_in       : BFW_NX5_spi_cr0_filter_in;       /* Receive-data is sampled every 10ns (100MHz sysem clock). If this bit is set, the               */
	                                                                /* stored receive value will be the result of a majority decision of the three sampling points    */
	unsigned int slave_sig_early : BFW_NX5_spi_cr0_slave_sig_early; /* Generate MISO in slavemode 1 spi_sck clock edge earlier than Spec-defined.                     */
	                                                                /* This is to compensate Pad/sampling-delays on fast data rates.                                  */
	unsigned int reserved4       : BFW_NX5_spi_cr0_reserved4;       /* reserved                                                                                       */
	unsigned int netx100_comp    : BFW_NX5_spi_cr0_netx100_comp;    /* use netx100/500-compatible SPI mode:                                                           */
	                                                                /* 0: start transfer after writing data                                                           */
} NX5_SPI_CR0_BIT_T;

typedef union {
	unsigned int      val;
	NX5_SPI_CR0_BIT_T bf;
} NX5_SPI_CR0_T;

/* --------------------------------------------------------------------- */
/* Register spi_cr1 */
/* => spi control register 0 */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_cr1  0x00000004U
#define Adr_NX5_spi_spi_cr1  0x018BFD04U
#define Adr_NX5_spi_cr1      0x018BFD04U
#define DFLT_VAL_NX5_spi_cr1 0x08080000U

#define MSK_NX5_spi_cr1_LBM              0x00000001U
#define SRT_NX5_spi_cr1_LBM              0
#define DFLT_VAL_NX5_spi_cr1_LBM         0x00000000U
#define MSK_NX5_spi_cr1_SSE              0x00000002U
#define SRT_NX5_spi_cr1_SSE              1
#define DFLT_VAL_NX5_spi_cr1_SSE         0x00000000U
#define MSK_NX5_spi_cr1_MS               0x00000004U
#define SRT_NX5_spi_cr1_MS               2
#define DFLT_VAL_NX5_spi_cr1_MS          0x00000000U
#define MSK_NX5_spi_cr1_SOD              0x00000008U
#define SRT_NX5_spi_cr1_SOD              3
#define DFLT_VAL_NX5_spi_cr1_SOD         0x00000000U
#define MSK_NX5_spi_cr1_fss              0x00000700U
#define SRT_NX5_spi_cr1_fss              8
#define DFLT_VAL_NX5_spi_cr1_fss         0x00000000U
#define MSK_NX5_spi_cr1_fss_static       0x00000800U
#define SRT_NX5_spi_cr1_fss_static       11
#define DFLT_VAL_NX5_spi_cr1_fss_static  0x00000000U
#define MSK_NX5_spi_cr1_tx_fifo_wm       0x000f0000U
#define SRT_NX5_spi_cr1_tx_fifo_wm       16
#define DFLT_VAL_NX5_spi_cr1_tx_fifo_wm  0x00080000U
#define MSK_NX5_spi_cr1_tx_fifo_clr      0x00100000U
#define SRT_NX5_spi_cr1_tx_fifo_clr      20
#define DFLT_VAL_NX5_spi_cr1_tx_fifo_clr 0x00000000U
#define MSK_NX5_spi_cr1_rx_fifo_wm       0x0f000000U
#define SRT_NX5_spi_cr1_rx_fifo_wm       24
#define DFLT_VAL_NX5_spi_cr1_rx_fifo_wm  0x08000000U
#define MSK_NX5_spi_cr1_rx_fifo_clr      0x10000000U
#define SRT_NX5_spi_cr1_rx_fifo_clr      28
#define DFLT_VAL_NX5_spi_cr1_rx_fifo_clr 0x00000000U

enum {
	BFW_NX5_spi_cr1_LBM         = 1, /* [0] */
	BFW_NX5_spi_cr1_SSE         = 1, /* [1] */
	BFW_NX5_spi_cr1_MS          = 1, /* [2] */
	BFW_NX5_spi_cr1_SOD         = 1, /* [3] */
	BFW_NX5_spi_cr1_reserved1   = 4, /* [7:4] */
	BFW_NX5_spi_cr1_fss         = 3, /* [10:8] */
	BFW_NX5_spi_cr1_fss_static  = 1, /* [11] */
	BFW_NX5_spi_cr1_reserved2   = 4, /* [15:12] */
	BFW_NX5_spi_cr1_tx_fifo_wm  = 4, /* [19:16] */
	BFW_NX5_spi_cr1_tx_fifo_clr = 1, /* [20] */
	BFW_NX5_spi_cr1_reserved3   = 3, /* [23:21] */
	BFW_NX5_spi_cr1_rx_fifo_wm  = 4, /* [27:24] */
	BFW_NX5_spi_cr1_rx_fifo_clr = 1, /* [28] */
	BFW_NX5_spi_cr1_reserved4   = 3  /* [31:29] */
};

typedef struct NX5_SPI_CR1_BIT_Ttag {
	unsigned int LBM         : BFW_NX5_spi_cr1_LBM;         /* loop back mode                                                                                    */
	                                                        /* 0: internal loop back disabled                                                                    */
	unsigned int SSE         : BFW_NX5_spi_cr1_SSE;         /* SPI enable.                                                                                       */
	                                                        /* 0: interface disabled                                                                             */
	unsigned int MS          : BFW_NX5_spi_cr1_MS;          /* mode select:                                                                                      */
	                                                        /* 0: device is configured as master                                                                 */
	unsigned int SOD         : BFW_NX5_spi_cr1_SOD;         /* slave mode output disable (to connect multibe slaves to opne master)                              */
	                                                        /* 0: SPI-MISO can be driven in slave mode                                                           */
	unsigned int reserved1   : BFW_NX5_spi_cr1_reserved1;   /* reserved                                                                                          */
	unsigned int fss         : BFW_NX5_spi_cr1_fss;         /* extended: Frame or slave select (up to 3 devices can be assigned directly,                        */
	                                                        /* up to 8 devices can be assigned if an external demultiplexer is used if device is master.         */
	unsigned int fss_static  : BFW_NX5_spi_cr1_fss_static;  /* SPI static chipselect                                                                             */
	                                                        /* 0: SPI-chipselect will be toggled automatically at data frame begin/end according to fss and FRF0 */
	unsigned int reserved2   : BFW_NX5_spi_cr1_reserved2;   /* reserved                                                                                          */
	unsigned int tx_fifo_wm  : BFW_NX5_spi_cr1_tx_fifo_wm;  /* transmit FIFO watermark for IRQ-generation                                                        */
	unsigned int tx_fifo_clr : BFW_NX5_spi_cr1_tx_fifo_clr; /* extended: writing "1" to this bit will clear the transmit-FIFOs                                   */
	                                                        /* There must be at least 1 system-clock idle after clear before writing new data to the FIFO.       */
	unsigned int reserved3   : BFW_NX5_spi_cr1_reserved3;   /* reserved                                                                                          */
	unsigned int rx_fifo_wm  : BFW_NX5_spi_cr1_rx_fifo_wm;  /* receive FIFO watermark for IRQ-generation                                                         */
	unsigned int rx_fifo_clr : BFW_NX5_spi_cr1_rx_fifo_clr; /* extended: writing "1" to this bit will clear the receive-FIFOs                                    */
	unsigned int reserved4   : BFW_NX5_spi_cr1_reserved4;   /* reserved                                                                                          */
} NX5_SPI_CR1_BIT_T;

typedef union {
	unsigned int      val;
	NX5_SPI_CR1_BIT_T bf;
} NX5_SPI_CR1_T;

/* --------------------------------------------------------------------- */
/* Register spi_dr */
/* => spi data register (DR) */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    read access: received data byte is delivered from receive FIFO */
/*    write access: send data byte is written to send FIFO */
/*    Both, receive and transmit FIFO have a depth of 16. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_dr  0x00000008U
#define Adr_NX5_spi_spi_dr  0x018BFD08U
#define Adr_NX5_spi_dr      0x018BFD08U
#define DFLT_VAL_NX5_spi_dr 0x00000000U

#define MSK_NX5_spi_dr_data      0x0001ffffU
#define SRT_NX5_spi_dr_data      0
#define DFLT_VAL_NX5_spi_dr_data 0x00000000U

enum {
	BFW_NX5_spi_dr_data      = 17, /* [16:0] */
	BFW_NX5_spi_dr_reserved1 = 15  /* [31:17] */
};

typedef struct NX5_SPI_DR_BIT_Ttag {
	unsigned int data      : BFW_NX5_spi_dr_data;      /* Transmit data, must be right aligned on writing, only bits according to spi_cr0.DSS are considered */
	                                                   /* Receive data will be delivered right aligned, unused bits (spi_cr0.DSS < 0xF) will be "0".         */
	unsigned int reserved1 : BFW_NX5_spi_dr_reserved1; /* reserved                                                                                           */
} NX5_SPI_DR_BIT_T;

typedef union {
	unsigned int     val;
	NX5_SPI_DR_BIT_T bf;
} NX5_SPI_DR_T;

/* --------------------------------------------------------------------- */
/* Register spi_sr */
/* => read only spi status register */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    SPI master mode: MISO-input-data will be stored in the receive FIFO, transmit FIFO generates MOSI-output-data */
/*    SPI slave mode: MOSI-input-data will be stored in the receive FIFO, transmit FIFO generates MISO-output-data */
/*    Shows the current status of the spi interface. */
/*    Both, receive and transmit FIFO have a depth of 16. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_sr 0x0000000CU
#define Adr_NX5_spi_spi_sr 0x018BFD0CU
#define Adr_NX5_spi_sr     0x018BFD0CU

#define MSK_NX5_spi_sr_TFE              0x00000001U
#define SRT_NX5_spi_sr_TFE              0
#define MSK_NX5_spi_sr_TNF              0x00000002U
#define SRT_NX5_spi_sr_TNF              1
#define MSK_NX5_spi_sr_RNE              0x00000004U
#define SRT_NX5_spi_sr_RNE              2
#define MSK_NX5_spi_sr_RFF              0x00000008U
#define SRT_NX5_spi_sr_RFF              3
#define MSK_NX5_spi_sr_BSY              0x00000010U
#define SRT_NX5_spi_sr_BSY              4
#define MSK_NX5_spi_sr_tx_fifo_level    0x001f0000U
#define SRT_NX5_spi_sr_tx_fifo_level    16
#define MSK_NX5_spi_sr_tx_fifo_err_ovfl 0x00400000U
#define SRT_NX5_spi_sr_tx_fifo_err_ovfl 22
#define MSK_NX5_spi_sr_tx_fifo_err_undr 0x00800000U
#define SRT_NX5_spi_sr_tx_fifo_err_undr 23
#define MSK_NX5_spi_sr_rx_fifo_level    0x1f000000U
#define SRT_NX5_spi_sr_rx_fifo_level    24
#define MSK_NX5_spi_sr_rx_fifo_err_ovfl 0x40000000U
#define SRT_NX5_spi_sr_rx_fifo_err_ovfl 30
#define MSK_NX5_spi_sr_rx_fifo_err_undr 0x80000000U
#define SRT_NX5_spi_sr_rx_fifo_err_undr 31

enum {
	BFW_NX5_spi_sr_TFE              = 1,  /* [0] */
	BFW_NX5_spi_sr_TNF              = 1,  /* [1] */
	BFW_NX5_spi_sr_RNE              = 1,  /* [2] */
	BFW_NX5_spi_sr_RFF              = 1,  /* [3] */
	BFW_NX5_spi_sr_BSY              = 1,  /* [4] */
	BFW_NX5_spi_sr_reserved1        = 11, /* [15:5] */
	BFW_NX5_spi_sr_tx_fifo_level    = 5,  /* [20:16] */
	BFW_NX5_spi_sr_reserved2        = 1,  /* [21] */
	BFW_NX5_spi_sr_tx_fifo_err_ovfl = 1,  /* [22] */
	BFW_NX5_spi_sr_tx_fifo_err_undr = 1,  /* [23] */
	BFW_NX5_spi_sr_rx_fifo_level    = 5,  /* [28:24] */
	BFW_NX5_spi_sr_reserved3        = 1,  /* [29] */
	BFW_NX5_spi_sr_rx_fifo_err_ovfl = 1,  /* [30] */
	BFW_NX5_spi_sr_rx_fifo_err_undr = 1   /* [31] */
};

typedef struct NX5_SPI_SR_BIT_Ttag {
	unsigned int TFE              : BFW_NX5_spi_sr_TFE;              /* transmit FIFO is empty (1 if empty)                                                         */
	unsigned int TNF              : BFW_NX5_spi_sr_TNF;              /* transmit FIFO is not full (0 if full)                                                       */
	unsigned int RNE              : BFW_NX5_spi_sr_RNE;              /* receive FIFO is not empty (0 if empty)                                                      */
	unsigned int RFF              : BFW_NX5_spi_sr_RFF;              /* receive FIFO is full (1 if full)                                                            */
	unsigned int BSY              : BFW_NX5_spi_sr_BSY;              /* device busy (1 if data is currently transmitted/received or the transmit FIFO is not empty) */
	unsigned int reserved1        : BFW_NX5_spi_sr_reserved1;        /* reserved                                                                                    */
	unsigned int tx_fifo_level    : BFW_NX5_spi_sr_tx_fifo_level;    /* extended: transmit FIFO level (number of words to transmit are left in FIFO)                */
	unsigned int reserved2        : BFW_NX5_spi_sr_reserved2;        /* reserved                                                                                    */
	unsigned int tx_fifo_err_ovfl : BFW_NX5_spi_sr_tx_fifo_err_ovfl; /* extended: transmit FIFO overflow error occured, data is lost                                */
	unsigned int tx_fifo_err_undr : BFW_NX5_spi_sr_tx_fifo_err_undr; /* extended: transmit FIFO underrun error occured, data is lost                                */
	unsigned int rx_fifo_level    : BFW_NX5_spi_sr_rx_fifo_level;    /* extended: receive FIFO level (number of received words to read out are left in FIFO)        */
	unsigned int reserved3        : BFW_NX5_spi_sr_reserved3;        /* reserved                                                                                    */
	unsigned int rx_fifo_err_ovfl : BFW_NX5_spi_sr_rx_fifo_err_ovfl; /* extended: receive FIFO overflow error occured, data is lost                                 */
	unsigned int rx_fifo_err_undr : BFW_NX5_spi_sr_rx_fifo_err_undr; /* extended: receive FIFO underrun error occured, data is lost                                 */
} NX5_SPI_SR_BIT_T;

typedef union {
	unsigned int     val;
	NX5_SPI_SR_BIT_T bf;
} NX5_SPI_SR_T;

/* --------------------------------------------------------------------- */
/* Register spi_cpsr */
/* => Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    spi clock prescale register */
/*    No clock predeviding is done. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_cpsr  0x00000010U
#define Adr_NX5_spi_spi_cpsr  0x018BFD10U
#define Adr_NX5_spi_cpsr      0x018BFD10U
#define DFLT_VAL_NX5_spi_cpsr 0x00000000U

#define MSK_NX5_spi_cpsr_CPSDVSR      0x000000ffU
#define SRT_NX5_spi_cpsr_CPSDVSR      0
#define DFLT_VAL_NX5_spi_cpsr_CPSDVSR 0x00000000U

enum {
	BFW_NX5_spi_cpsr_CPSDVSR   = 8,  /* [7:0] */
	BFW_NX5_spi_cpsr_reserved1 = 24  /* [31:8] */
};

typedef struct NX5_SPI_CPSR_BIT_Ttag {
	unsigned int CPSDVSR   : BFW_NX5_spi_cpsr_CPSDVSR;   /* obsolet  */
	unsigned int reserved1 : BFW_NX5_spi_cpsr_reserved1; /* reserved */
} NX5_SPI_CPSR_BIT_T;

typedef union {
	unsigned int       val;
	NX5_SPI_CPSR_BIT_T bf;
} NX5_SPI_CPSR_T;

/* --------------------------------------------------------------------- */
/* Register spi_imsc */
/* => spi interrupt mask set or clear register */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    AND-mask */
/*    Both, receive and transmit FIFO have a depth of 16. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_imsc  0x00000014U
#define Adr_NX5_spi_spi_imsc  0x018BFD14U
#define Adr_NX5_spi_imsc      0x018BFD14U
#define DFLT_VAL_NX5_spi_imsc 0x00000000U

#define MSK_NX5_spi_imsc_RORIM       0x00000001U
#define SRT_NX5_spi_imsc_RORIM       0
#define DFLT_VAL_NX5_spi_imsc_RORIM  0x00000000U
#define MSK_NX5_spi_imsc_RTIM        0x00000002U
#define SRT_NX5_spi_imsc_RTIM        1
#define DFLT_VAL_NX5_spi_imsc_RTIM   0x00000000U
#define MSK_NX5_spi_imsc_RXIM        0x00000004U
#define SRT_NX5_spi_imsc_RXIM        2
#define DFLT_VAL_NX5_spi_imsc_RXIM   0x00000000U
#define MSK_NX5_spi_imsc_TXIM        0x00000008U
#define SRT_NX5_spi_imsc_TXIM        3
#define DFLT_VAL_NX5_spi_imsc_TXIM   0x00000000U
#define MSK_NX5_spi_imsc_rxneim      0x00000010U
#define SRT_NX5_spi_imsc_rxneim      4
#define DFLT_VAL_NX5_spi_imsc_rxneim 0x00000000U
#define MSK_NX5_spi_imsc_rxfim       0x00000020U
#define SRT_NX5_spi_imsc_rxfim       5
#define DFLT_VAL_NX5_spi_imsc_rxfim  0x00000000U
#define MSK_NX5_spi_imsc_txeim       0x00000040U
#define SRT_NX5_spi_imsc_txeim       6
#define DFLT_VAL_NX5_spi_imsc_txeim  0x00000000U

enum {
	BFW_NX5_spi_imsc_RORIM     = 1,  /* [0] */
	BFW_NX5_spi_imsc_RTIM      = 1,  /* [1] */
	BFW_NX5_spi_imsc_RXIM      = 1,  /* [2] */
	BFW_NX5_spi_imsc_TXIM      = 1,  /* [3] */
	BFW_NX5_spi_imsc_rxneim    = 1,  /* [4] */
	BFW_NX5_spi_imsc_rxfim     = 1,  /* [5] */
	BFW_NX5_spi_imsc_txeim     = 1,  /* [6] */
	BFW_NX5_spi_imsc_reserved1 = 25  /* [31:7] */
};

typedef struct NX5_SPI_IMSC_BIT_Ttag {
	unsigned int RORIM     : BFW_NX5_spi_imsc_RORIM;     /* receive FIFO overrun interrupt mask                                */
	unsigned int RTIM      : BFW_NX5_spi_imsc_RTIM;      /* receive timeout interrupt mask                                     */
	unsigned int RXIM      : BFW_NX5_spi_imsc_RXIM;      /* receive FIFO interrupt mask                                        */
	unsigned int TXIM      : BFW_NX5_spi_imsc_TXIM;      /* transmit FIFO interrupt mask                                       */
	unsigned int rxneim    : BFW_NX5_spi_imsc_rxneim;    /* receive FIFO not empty interrupt mask (for netx100/500 compliance) */
	unsigned int rxfim     : BFW_NX5_spi_imsc_rxfim;     /* receive FIFO full interrupt mask (for netx100/500 compliance)      */
	unsigned int txeim     : BFW_NX5_spi_imsc_txeim;     /* transmit FIFO empty interrupt mask (for netx100/500 compliance)    */
	unsigned int reserved1 : BFW_NX5_spi_imsc_reserved1; /* reserved                                                           */
} NX5_SPI_IMSC_BIT_T;

typedef union {
	unsigned int       val;
	NX5_SPI_IMSC_BIT_T bf;
} NX5_SPI_IMSC_T;

/* --------------------------------------------------------------------- */
/* Register spi_ris */
/* => spi interrupt state before masking register (raw interrupt) */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    Both, receive and transmit FIFO have a depth of 16. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_ris 0x00000018U
#define Adr_NX5_spi_spi_ris 0x018BFD18U
#define Adr_NX5_spi_ris     0x018BFD18U

#define MSK_NX5_spi_ris_RORRIS  0x00000001U
#define SRT_NX5_spi_ris_RORRIS  0
#define MSK_NX5_spi_ris_RTRIS   0x00000002U
#define SRT_NX5_spi_ris_RTRIS   1
#define MSK_NX5_spi_ris_RXRIS   0x00000004U
#define SRT_NX5_spi_ris_RXRIS   2
#define MSK_NX5_spi_ris_TXRIS   0x00000008U
#define SRT_NX5_spi_ris_TXRIS   3
#define MSK_NX5_spi_ris_rxneris 0x00000010U
#define SRT_NX5_spi_ris_rxneris 4
#define MSK_NX5_spi_ris_rxfris  0x00000020U
#define SRT_NX5_spi_ris_rxfris  5
#define MSK_NX5_spi_ris_txeris  0x00000040U
#define SRT_NX5_spi_ris_txeris  6

enum {
	BFW_NX5_spi_ris_RORRIS    = 1,  /* [0] */
	BFW_NX5_spi_ris_RTRIS     = 1,  /* [1] */
	BFW_NX5_spi_ris_RXRIS     = 1,  /* [2] */
	BFW_NX5_spi_ris_TXRIS     = 1,  /* [3] */
	BFW_NX5_spi_ris_rxneris   = 1,  /* [4] */
	BFW_NX5_spi_ris_rxfris    = 1,  /* [5] */
	BFW_NX5_spi_ris_txeris    = 1,  /* [6] */
	BFW_NX5_spi_ris_reserved1 = 25  /* [31:7] */
};

typedef struct NX5_SPI_RIS_BIT_Ttag {
	unsigned int RORRIS    : BFW_NX5_spi_ris_RORRIS;    /* unmasked receive FIFO overrun interrupt state                                */
	                                                    /* 1: receive FIFO overun error ocuured                                         */
	unsigned int RTRIS     : BFW_NX5_spi_ris_RTRIS;     /* unmasked receive timeout interrupt state                                     */
	                                                    /* timeout period are 32 SPI-clock periods depending on adr_spi_cr0.SCR         */
	unsigned int RXRIS     : BFW_NX5_spi_ris_RXRIS;     /* unmasked receive FIFO interrupt state                                        */
	                                                    /* 1: receive FIFO is higher than spi_cr1.rx_fifo_wm                            */
	unsigned int TXRIS     : BFW_NX5_spi_ris_TXRIS;     /* unmasked transmit FIFO interrupt state                                       */
	                                                    /* 1: transmit FIFO level is below spi_cr1.tx_fifo_wm                           */
	unsigned int rxneris   : BFW_NX5_spi_ris_rxneris;   /* unmasked receive FIFO not empty interrupt state (for netx100/500 compliance) */
	                                                    /* 1: receive FIFO is not empty                                                 */
	unsigned int rxfris    : BFW_NX5_spi_ris_rxfris;    /* unmasked receive FIFO full interrupt state (for netx100/500 compliance)      */
	                                                    /* 1: receive FIFO is full                                                      */
	unsigned int txeris    : BFW_NX5_spi_ris_txeris;    /* unmasked transmit FIFO empty interrupt state (for netx100/500 compliance)    */
	                                                    /* 1: transmit FIFO is empty                                                    */
	unsigned int reserved1 : BFW_NX5_spi_ris_reserved1; /* reserved                                                                     */
} NX5_SPI_RIS_BIT_T;

typedef union {
	unsigned int      val;
	NX5_SPI_RIS_BIT_T bf;
} NX5_SPI_RIS_T;

/* --------------------------------------------------------------------- */
/* Register spi_mis */
/* => spi interrupt status register */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    Both, receive and transmit FIFO have a depth of 16. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_mis 0x0000001CU
#define Adr_NX5_spi_spi_mis 0x018BFD1CU
#define Adr_NX5_spi_mis     0x018BFD1CU

#define MSK_NX5_spi_mis_RORMIS  0x00000001U
#define SRT_NX5_spi_mis_RORMIS  0
#define MSK_NX5_spi_mis_RTMIS   0x00000002U
#define SRT_NX5_spi_mis_RTMIS   1
#define MSK_NX5_spi_mis_RXMIS   0x00000004U
#define SRT_NX5_spi_mis_RXMIS   2
#define MSK_NX5_spi_mis_TXMIS   0x00000008U
#define SRT_NX5_spi_mis_TXMIS   3
#define MSK_NX5_spi_mis_rxnemis 0x00000010U
#define SRT_NX5_spi_mis_rxnemis 4
#define MSK_NX5_spi_mis_rxfmis  0x00000020U
#define SRT_NX5_spi_mis_rxfmis  5
#define MSK_NX5_spi_mis_txemis  0x00000040U
#define SRT_NX5_spi_mis_txemis  6

enum {
	BFW_NX5_spi_mis_RORMIS    = 1,  /* [0] */
	BFW_NX5_spi_mis_RTMIS     = 1,  /* [1] */
	BFW_NX5_spi_mis_RXMIS     = 1,  /* [2] */
	BFW_NX5_spi_mis_TXMIS     = 1,  /* [3] */
	BFW_NX5_spi_mis_rxnemis   = 1,  /* [4] */
	BFW_NX5_spi_mis_rxfmis    = 1,  /* [5] */
	BFW_NX5_spi_mis_txemis    = 1,  /* [6] */
	BFW_NX5_spi_mis_reserved1 = 25  /* [31:7] */
};

typedef struct NX5_SPI_MIS_BIT_Ttag {
	unsigned int RORMIS    : BFW_NX5_spi_mis_RORMIS;    /* masked receive FIFO overrun interrupt state                                */
	unsigned int RTMIS     : BFW_NX5_spi_mis_RTMIS;     /* masked receive timeout interrupt state                                     */
	unsigned int RXMIS     : BFW_NX5_spi_mis_RXMIS;     /* masked receive FIFO interrupt state                                        */
	unsigned int TXMIS     : BFW_NX5_spi_mis_TXMIS;     /* masked transmit FIFO interrupt state                                       */
	unsigned int rxnemis   : BFW_NX5_spi_mis_rxnemis;   /* masked receive FIFO not empty interrupt state (for netx100/500 compliance) */
	unsigned int rxfmis    : BFW_NX5_spi_mis_rxfmis;    /* masked receive FIFO full interrupt state (for netx100/500 compliance)      */
	unsigned int txemis    : BFW_NX5_spi_mis_txemis;    /* masked transmit FIFO empty interrupt state (for netx100/500 compliance)    */
	unsigned int reserved1 : BFW_NX5_spi_mis_reserved1; /* reserved                                                                   */
} NX5_SPI_MIS_BIT_T;

typedef union {
	unsigned int      val;
	NX5_SPI_MIS_BIT_T bf;
} NX5_SPI_MIS_T;

/* --------------------------------------------------------------------- */
/* Register spi_icr */
/* => spi interrupt clear register */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    interrupt is cleard by writing "1" to the according bit */
/*    FIFO-state interrupts are cleared automatically if interupt criteria is no longer thrue. */
/*    Both, receive and transmit FIFO have a depth of 16. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_icr  0x00000020U
#define Adr_NX5_spi_spi_icr  0x018BFD20U
#define Adr_NX5_spi_icr      0x018BFD20U
#define DFLT_VAL_NX5_spi_icr 0x00000000U

#define MSK_NX5_spi_icr_RORIC       0x00000001U
#define SRT_NX5_spi_icr_RORIC       0
#define DFLT_VAL_NX5_spi_icr_RORIC  0x00000000U
#define MSK_NX5_spi_icr_RTIC        0x00000002U
#define SRT_NX5_spi_icr_RTIC        1
#define DFLT_VAL_NX5_spi_icr_RTIC   0x00000000U
#define MSK_NX5_spi_icr_RXIC        0x00000004U
#define SRT_NX5_spi_icr_RXIC        2
#define DFLT_VAL_NX5_spi_icr_RXIC   0x00000000U
#define MSK_NX5_spi_icr_TXIC        0x00000008U
#define SRT_NX5_spi_icr_TXIC        3
#define DFLT_VAL_NX5_spi_icr_TXIC   0x00000000U
#define MSK_NX5_spi_icr_rxneic      0x00000010U
#define SRT_NX5_spi_icr_rxneic      4
#define DFLT_VAL_NX5_spi_icr_rxneic 0x00000000U
#define MSK_NX5_spi_icr_rxfic       0x00000020U
#define SRT_NX5_spi_icr_rxfic       5
#define DFLT_VAL_NX5_spi_icr_rxfic  0x00000000U
#define MSK_NX5_spi_icr_txeic       0x00000040U
#define SRT_NX5_spi_icr_txeic       6
#define DFLT_VAL_NX5_spi_icr_txeic  0x00000000U

enum {
	BFW_NX5_spi_icr_RORIC     = 1,  /* [0] */
	BFW_NX5_spi_icr_RTIC      = 1,  /* [1] */
	BFW_NX5_spi_icr_RXIC      = 1,  /* [2] */
	BFW_NX5_spi_icr_TXIC      = 1,  /* [3] */
	BFW_NX5_spi_icr_rxneic    = 1,  /* [4] */
	BFW_NX5_spi_icr_rxfic     = 1,  /* [5] */
	BFW_NX5_spi_icr_txeic     = 1,  /* [6] */
	BFW_NX5_spi_icr_reserved1 = 25  /* [31:7] */
};

typedef struct NX5_SPI_ICR_BIT_Ttag {
	unsigned int RORIC     : BFW_NX5_spi_icr_RORIC;     /* clear receive FIFO overrun interrupt                                */
	                                                    /* writing '1' here will clear the receive FIFO                        */
	unsigned int RTIC      : BFW_NX5_spi_icr_RTIC;      /* clear receive FIFO overrun interrupt                                */
	unsigned int RXIC      : BFW_NX5_spi_icr_RXIC;      /* PL022 extention: clear receive FIFO interrupt                       */
	unsigned int TXIC      : BFW_NX5_spi_icr_TXIC;      /* PL022 extention: clear transmit FIFO interrupt                      */
	unsigned int rxneic    : BFW_NX5_spi_icr_rxneic;    /* clear receive FIFO not empty interrupt (for netx100/500 compliance) */
	unsigned int rxfic     : BFW_NX5_spi_icr_rxfic;     /* clear receive FIFO full interrupt (for netx100/500 compliance)      */
	unsigned int txeic     : BFW_NX5_spi_icr_txeic;     /* clear transmit FIFO empty interrupt (for netx100/500 compliance)    */
	unsigned int reserved1 : BFW_NX5_spi_icr_reserved1; /* reserved                                                            */
} NX5_SPI_ICR_BIT_T;

typedef union {
	unsigned int      val;
	NX5_SPI_ICR_BIT_T bf;
} NX5_SPI_ICR_T;

/* --------------------------------------------------------------------- */
/* Register spi_dmacr */
/* => spi DMA control register */
/*    Only single transfer requests will be generated by this module. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_dmacr  0x00000024U
#define Adr_NX5_spi_spi_dmacr  0x018BFD24U
#define Adr_NX5_spi_dmacr      0x018BFD24U
#define DFLT_VAL_NX5_spi_dmacr 0x00000000U

#define MSK_NX5_spi_dmacr_RXDMAE      0x00000001U
#define SRT_NX5_spi_dmacr_RXDMAE      0
#define DFLT_VAL_NX5_spi_dmacr_RXDMAE 0x00000000U
#define MSK_NX5_spi_dmacr_TXDMAE      0x00000002U
#define SRT_NX5_spi_dmacr_TXDMAE      1
#define DFLT_VAL_NX5_spi_dmacr_TXDMAE 0x00000000U

enum {
	BFW_NX5_spi_dmacr_RXDMAE    = 1,  /* [0] */
	BFW_NX5_spi_dmacr_TXDMAE    = 1,  /* [1] */
	BFW_NX5_spi_dmacr_reserved1 = 30  /* [31:2] */
};

typedef struct NX5_SPI_DMACR_BIT_Ttag {
	unsigned int RXDMAE    : BFW_NX5_spi_dmacr_RXDMAE;    /* enable DMA for SPI-receive data                                                             */
	                                                      /* A request will be generated if RX-FIFO is not empty and spi_cr1.SSE (module enable) is set. */
	unsigned int TXDMAE    : BFW_NX5_spi_dmacr_TXDMAE;    /* enable DMA for SPI-transmit data                                                            */
	                                                      /* A request will be generated if TX-FIFO is not full and spi_cr1.SSE (module enable) is set.  */
	unsigned int reserved1 : BFW_NX5_spi_dmacr_reserved1; /* reserved                                                                                    */
} NX5_SPI_DMACR_BIT_T;

typedef union {
	unsigned int        val;
	NX5_SPI_DMACR_BIT_T bf;
} NX5_SPI_DMACR_T;

/* --------------------------------------------------------------------- */
/* Register spi_data_register */
/* => netx100/500 compliant spi data register (DR) */
/*    Registers 0x30..0x3C can be used instead of registers 0x00...0x24 to keep netx50 software compliant to netx100/500 */
/*    2 data bytes with valid bits */
/*    During write-access data_byte_1 and dr_valid1 must not be used. dr_valid0 must be set. */
/*    In netx50 and later versions both, receive and transmit FIFO have a depth of 16, fill-values are fixed to 4. To keep software */
/*    compatible, not more than 8 bytes should be in netx100/500-FIFOs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_data_register  0x00000030U
#define Adr_NX5_spi_spi_data_register  0x018BFD30U
#define Adr_NX5_spi_data_register      0x018BFD30U
#define DFLT_VAL_NX5_spi_data_register 0x00000000U

#define MSK_NX5_spi_data_register_data_byte_0      0x000000ffU
#define SRT_NX5_spi_data_register_data_byte_0      0
#define DFLT_VAL_NX5_spi_data_register_data_byte_0 0x00000000U
#define MSK_NX5_spi_data_register_data_byte_1      0x0000ff00U
#define SRT_NX5_spi_data_register_data_byte_1      8
#define DFLT_VAL_NX5_spi_data_register_data_byte_1 0x00000000U
#define MSK_NX5_spi_data_register_dr_valid0        0x00010000U
#define SRT_NX5_spi_data_register_dr_valid0        16
#define DFLT_VAL_NX5_spi_data_register_dr_valid0   0x00000000U
#define MSK_NX5_spi_data_register_dr_valid1        0x00020000U
#define SRT_NX5_spi_data_register_dr_valid1        17
#define DFLT_VAL_NX5_spi_data_register_dr_valid1   0x00000000U

enum {
	BFW_NX5_spi_data_register_data_byte_0 = 8,  /* [7:0] */
	BFW_NX5_spi_data_register_data_byte_1 = 8,  /* [15:8] */
	BFW_NX5_spi_data_register_dr_valid0   = 1,  /* [16] */
	BFW_NX5_spi_data_register_dr_valid1   = 1,  /* [17] */
	BFW_NX5_spi_data_register_reserved1   = 14  /* [31:18] */
};

typedef struct NX5_SPI_DATA_REGISTER_BIT_Ttag {
	unsigned int data_byte_0 : BFW_NX5_spi_data_register_data_byte_0; /* data byte 0                                                                     */
	unsigned int data_byte_1 : BFW_NX5_spi_data_register_data_byte_1; /* obsolet, don't use                                                              */
	unsigned int dr_valid0   : BFW_NX5_spi_data_register_dr_valid0;   /* valid bit for data_byte_0                                                       */
	                                                                  /* This bit shows if data_byte_0 Is valid and must be set during FIFO write access */
	unsigned int dr_valid1   : BFW_NX5_spi_data_register_dr_valid1;   /* obsolet, always 0                                                               */
	unsigned int reserved1   : BFW_NX5_spi_data_register_reserved1;   /* reserved                                                                        */
} NX5_SPI_DATA_REGISTER_BIT_T;

typedef union {
	unsigned int                val;
	NX5_SPI_DATA_REGISTER_BIT_T bf;
} NX5_SPI_DATA_REGISTER_T;

/* --------------------------------------------------------------------- */
/* Register spi_status_register */
/* => netx100/500 compliant spi status register (SR): */
/*    Shows the actual status of the spi interface. */
/*    Bits 24..18 show occured interrupts, */
/*    writing ones into these bits deletes the interrupts. */
/*    Writing into other bits has no effect. */
/*    In netx50 and later versions both, receive and transmit FIFO have a depth of 16, fill-values are fixed to 4. To keep software */
/*    compatible, not more than 8 bytes should be in netx100/500-FIFOs. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_status_register 0x00000034U
#define Adr_NX5_spi_spi_status_register 0x018BFD34U
#define Adr_NX5_spi_status_register     0x018BFD34U

#define MSK_NX5_spi_status_register_SR_in_fuel_val  0x000001ffU
#define SRT_NX5_spi_status_register_SR_in_fuel_val  0
#define MSK_NX5_spi_status_register_SR_out_fuel_val 0x0003fe00U
#define SRT_NX5_spi_status_register_SR_out_fuel_val 9
#define MSK_NX5_spi_status_register_SR_in_fuel      0x00040000U
#define SRT_NX5_spi_status_register_SR_in_fuel      18
#define MSK_NX5_spi_status_register_SR_in_recdata   0x00080000U
#define SRT_NX5_spi_status_register_SR_in_recdata   19
#define MSK_NX5_spi_status_register_SR_in_full      0x00100000U
#define SRT_NX5_spi_status_register_SR_in_full      20
#define MSK_NX5_spi_status_register_SR_out_fuel     0x00200000U
#define SRT_NX5_spi_status_register_SR_out_fuel     21
#define MSK_NX5_spi_status_register_SR_out_fw       0x00400000U
#define SRT_NX5_spi_status_register_SR_out_fw       22
#define MSK_NX5_spi_status_register_SR_out_empty    0x00800000U
#define SRT_NX5_spi_status_register_SR_out_empty    23
#define MSK_NX5_spi_status_register_SR_out_full     0x01000000U
#define SRT_NX5_spi_status_register_SR_out_full     24
#define MSK_NX5_spi_status_register_SR_selected     0x02000000U
#define SRT_NX5_spi_status_register_SR_selected     25

enum {
	BFW_NX5_spi_status_register_SR_in_fuel_val  = 9, /* [8:0] */
	BFW_NX5_spi_status_register_SR_out_fuel_val = 9, /* [17:9] */
	BFW_NX5_spi_status_register_SR_in_fuel      = 1, /* [18] */
	BFW_NX5_spi_status_register_SR_in_recdata   = 1, /* [19] */
	BFW_NX5_spi_status_register_SR_in_full      = 1, /* [20] */
	BFW_NX5_spi_status_register_SR_out_fuel     = 1, /* [21] */
	BFW_NX5_spi_status_register_SR_out_fw       = 1, /* [22] */
	BFW_NX5_spi_status_register_SR_out_empty    = 1, /* [23] */
	BFW_NX5_spi_status_register_SR_out_full     = 1, /* [24] */
	BFW_NX5_spi_status_register_SR_selected     = 1, /* [25] */
	BFW_NX5_spi_status_register_reserved1       = 6  /* [31:26] */
};

typedef struct NX5_SPI_STATUS_REGISTER_BIT_Ttag {
	unsigned int SR_in_fuel_val  : BFW_NX5_spi_status_register_SR_in_fuel_val;  /* input FIFO fill value (number of bytes)                                                              */
	unsigned int SR_out_fuel_val : BFW_NX5_spi_status_register_SR_out_fuel_val; /* output FIFO fill vlaue (number of bytes)                                                             */
	unsigned int SR_in_fuel      : BFW_NX5_spi_status_register_SR_in_fuel;      /* adjustable fill value of input FIFO reached (equals adr_spi_ris.RXRIS in netx50 and later versions)  */
	unsigned int SR_in_recdata   : BFW_NX5_spi_status_register_SR_in_recdata;   /* valid data bytes in input FIFO (equals adr_spi_ris.rxneris in netx50 and later versions)             */
	unsigned int SR_in_full      : BFW_NX5_spi_status_register_SR_in_full;      /* input FIFO is full (equals adr_spi_ris.rxfris in netx50 and later versions)                          */
	unsigned int SR_out_fuel     : BFW_NX5_spi_status_register_SR_out_fuel;     /* adjustable fill value of output FIFO reached (equals adr_spi_ris.TXRIS in netx50 and later versions) */
	unsigned int SR_out_fw       : BFW_NX5_spi_status_register_SR_out_fw;       /* netx is writing data to fast into output FIFO. This is only with netx100/500 an IRQ.                 */
	                                                                            /* (equals adr_spi_sr.tx_fifo_err_ovfl in netx50 and later versions)                                    */
	unsigned int SR_out_empty    : BFW_NX5_spi_status_register_SR_out_empty;    /* output FIFO is empty in slave mode. (equals adr_spi_ris.txeris in netx50 and later versions)         */
	unsigned int SR_out_full     : BFW_NX5_spi_status_register_SR_out_full;     /* output FIFO is full                                                                                  */
	unsigned int SR_selected     : BFW_NX5_spi_status_register_SR_selected;     /* external master has access to spi-interface                                                          */
	unsigned int reserved1       : BFW_NX5_spi_status_register_reserved1;       /* reserved                                                                                             */
} NX5_SPI_STATUS_REGISTER_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_SPI_STATUS_REGISTER_BIT_T bf;
} NX5_SPI_STATUS_REGISTER_T;

/* --------------------------------------------------------------------- */
/* Register spi_control_register */
/* => netx100/500 compliant spi control register (CR) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_control_register  0x00000038U
#define Adr_NX5_spi_spi_control_register  0x018BFD38U
#define Adr_NX5_spi_control_register      0x018BFD38U
#define DFLT_VAL_NX5_spi_control_register 0x00000000U

#define MSK_NX5_spi_control_register_CR_softreset        0x00000001U
#define SRT_NX5_spi_control_register_CR_softreset        0
#define DFLT_VAL_NX5_spi_control_register_CR_softreset   0x00000000U
#define MSK_NX5_spi_control_register_CR_speed            0x0000001eU
#define SRT_NX5_spi_control_register_CR_speed            1
#define DFLT_VAL_NX5_spi_control_register_CR_speed       0x00000000U
#define MSK_NX5_spi_control_register_CR_read             0x00000040U
#define SRT_NX5_spi_control_register_CR_read             6
#define DFLT_VAL_NX5_spi_control_register_CR_read        0x00000000U
#define MSK_NX5_spi_control_register_CR_write            0x00000080U
#define SRT_NX5_spi_control_register_CR_write            7
#define DFLT_VAL_NX5_spi_control_register_CR_write       0x00000000U
#define MSK_NX5_spi_control_register_CR_ss               0x00000700U
#define SRT_NX5_spi_control_register_CR_ss               8
#define DFLT_VAL_NX5_spi_control_register_CR_ss          0x00000000U
#define MSK_NX5_spi_control_register_CS_mode             0x00000800U
#define SRT_NX5_spi_control_register_CS_mode             11
#define DFLT_VAL_NX5_spi_control_register_CS_mode        0x00000000U
#define MSK_NX5_spi_control_register_CR_clr_infifo       0x00100000U
#define SRT_NX5_spi_control_register_CR_clr_infifo       20
#define DFLT_VAL_NX5_spi_control_register_CR_clr_infifo  0x00000000U
#define MSK_NX5_spi_control_register_CR_clr_outfifo      0x00200000U
#define SRT_NX5_spi_control_register_CR_clr_outfifo      21
#define DFLT_VAL_NX5_spi_control_register_CR_clr_outfifo 0x00000000U
#define MSK_NX5_spi_control_register_CR_burstdelay       0x01c00000U
#define SRT_NX5_spi_control_register_CR_burstdelay       22
#define DFLT_VAL_NX5_spi_control_register_CR_burstdelay  0x00000000U
#define MSK_NX5_spi_control_register_CR_burst            0x0e000000U
#define SRT_NX5_spi_control_register_CR_burst            25
#define DFLT_VAL_NX5_spi_control_register_CR_burst       0x00000000U
#define MSK_NX5_spi_control_register_CR_ncpha            0x10000000U
#define SRT_NX5_spi_control_register_CR_ncpha            28
#define DFLT_VAL_NX5_spi_control_register_CR_ncpha       0x00000000U
#define MSK_NX5_spi_control_register_CR_cpol             0x20000000U
#define SRT_NX5_spi_control_register_CR_cpol             29
#define DFLT_VAL_NX5_spi_control_register_CR_cpol        0x00000000U
#define MSK_NX5_spi_control_register_CR_ms               0x40000000U
#define SRT_NX5_spi_control_register_CR_ms               30
#define DFLT_VAL_NX5_spi_control_register_CR_ms          0x00000000U
#define MSK_NX5_spi_control_register_CR_en               0x80000000U
#define SRT_NX5_spi_control_register_CR_en               31
#define DFLT_VAL_NX5_spi_control_register_CR_en          0x00000000U

enum {
	BFW_NX5_spi_control_register_CR_softreset   = 1, /* [0] */
	BFW_NX5_spi_control_register_CR_speed       = 4, /* [4:1] */
	BFW_NX5_spi_control_register_reserved1      = 1, /* [5] */
	BFW_NX5_spi_control_register_CR_read        = 1, /* [6] */
	BFW_NX5_spi_control_register_CR_write       = 1, /* [7] */
	BFW_NX5_spi_control_register_CR_ss          = 3, /* [10:8] */
	BFW_NX5_spi_control_register_CS_mode        = 1, /* [11] */
	BFW_NX5_spi_control_register_reserved2      = 8, /* [19:12] */
	BFW_NX5_spi_control_register_CR_clr_infifo  = 1, /* [20] */
	BFW_NX5_spi_control_register_CR_clr_outfifo = 1, /* [21] */
	BFW_NX5_spi_control_register_CR_burstdelay  = 3, /* [24:22] */
	BFW_NX5_spi_control_register_CR_burst       = 3, /* [27:25] */
	BFW_NX5_spi_control_register_CR_ncpha       = 1, /* [28] */
	BFW_NX5_spi_control_register_CR_cpol        = 1, /* [29] */
	BFW_NX5_spi_control_register_CR_ms          = 1, /* [30] */
	BFW_NX5_spi_control_register_CR_en          = 1  /* [31] */
};

typedef struct NX5_SPI_CONTROL_REGISTER_BIT_Ttag {
	unsigned int CR_softreset   : BFW_NX5_spi_control_register_CR_softreset;   /* write only: no function in netx100/netx500; later Versions: clears IRQs and FIFOs                   */
	unsigned int CR_speed       : BFW_NX5_spi_control_register_CR_speed;       /* clock devider for SPI clock (2 - 2^16)                                                              */
	                                                                           /* If SPI Clock-rate is changed by adr_spi_cr0.SCR, this value will not be updated an may be incorrect */
	unsigned int reserved1      : BFW_NX5_spi_control_register_reserved1;      /* reserved                                                                                            */
	unsigned int CR_read        : BFW_NX5_spi_control_register_CR_read;        /* netx100/netx500 only, in later versions always "1":  1: enable spi interface read data              */
	unsigned int CR_write       : BFW_NX5_spi_control_register_CR_write;       /* netx100/netx500 only, in later versions always "1":  1: enable spi interface write data             */
	unsigned int CR_ss          : BFW_NX5_spi_control_register_CR_ss;          /* external slave select                                                                               */
	unsigned int CS_mode        : BFW_NX5_spi_control_register_CS_mode;        /* 1: chip select is generated automatically by the internal state machine                             */
	                                                                           /* 0: chip select is directly controlled by software (see bits CR_ss).                                 */
	unsigned int reserved2      : BFW_NX5_spi_control_register_reserved2;      /* reserved                                                                                            */
	unsigned int CR_clr_infifo  : BFW_NX5_spi_control_register_CR_clr_infifo;  /* clear input FIFO                                                                                    */
	unsigned int CR_clr_outfifo : BFW_NX5_spi_control_register_CR_clr_outfifo; /* clear output FIFO                                                                                   */
	unsigned int CR_burstdelay  : BFW_NX5_spi_control_register_CR_burstdelay;  /* netx100/netx500 only, obsolet in later versions: delay between transmittion of 2 data bytes         */
	                                                                           /* (0 to 7 SCK cycles)                                                                                 */
	unsigned int CR_burst       : BFW_NX5_spi_control_register_CR_burst;       /* netx100/netx500 only, obsolet in later versions: burst lenght = 2^CR_burst                          */
	unsigned int CR_ncpha       : BFW_NX5_spi_control_register_CR_ncpha;       /* relative to CR_cpol                                                                                 */
	                                                                           /* 1:change data to primary spi_sck edge                                                               */
	unsigned int CR_cpol        : BFW_NX5_spi_control_register_CR_cpol;        /* 1:falling edge of spi_sck is primary                                                                */
	                                                                           /* 0:rising edge of spi_sck is primary                                                                 */
	unsigned int CR_ms          : BFW_NX5_spi_control_register_CR_ms;          /* 1:master mode 0:slave mode                                                                          */
	unsigned int CR_en          : BFW_NX5_spi_control_register_CR_en;          /* 1:enable 0:disable spi interface                                                                    */
} NX5_SPI_CONTROL_REGISTER_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_SPI_CONTROL_REGISTER_BIT_T bf;
} NX5_SPI_CONTROL_REGISTER_T;

/* --------------------------------------------------------------------- */
/* Register spi_interrupt_control_register */
/* => netx100/500 compliant spi interrupt control register (IR) */
/*    In netx50 and later versions both, receive and transmit FIFO have a depth of 16, fill-values are fixed to 4. To keep software */
/*    compatible, not more than 8 bytes should be in netx100/500-FIFOs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_spi_interrupt_control_register  0x0000003CU
#define Adr_NX5_spi_spi_interrupt_control_register  0x018BFD3CU
#define Adr_NX5_spi_interrupt_control_register      0x018BFD3CU
#define DFLT_VAL_NX5_spi_interrupt_control_register 0x00000000U

#define MSK_NX5_spi_interrupt_control_register_IR_in_fuel            0x000001ffU
#define SRT_NX5_spi_interrupt_control_register_IR_in_fuel            0
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_in_fuel       0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_out_fuel           0x0003fe00U
#define SRT_NX5_spi_interrupt_control_register_IR_out_fuel           9
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_out_fuel      0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_in_fuel_en         0x00040000U
#define SRT_NX5_spi_interrupt_control_register_IR_in_fuel_en         18
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_in_fuel_en    0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_in_recdata_en      0x00080000U
#define SRT_NX5_spi_interrupt_control_register_IR_in_recdata_en      19
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_in_recdata_en 0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_in_full_en         0x00100000U
#define SRT_NX5_spi_interrupt_control_register_IR_in_full_en         20
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_in_full_en    0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_out_fuel_en        0x00200000U
#define SRT_NX5_spi_interrupt_control_register_IR_out_fuel_en        21
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_out_fuel_en   0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_out_fw_en          0x00400000U
#define SRT_NX5_spi_interrupt_control_register_IR_out_fw_en          22
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_out_fw_en     0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_out_empty_en       0x00800000U
#define SRT_NX5_spi_interrupt_control_register_IR_out_empty_en       23
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_out_empty_en  0x00000000U
#define MSK_NX5_spi_interrupt_control_register_IR_out_full_en        0x01000000U
#define SRT_NX5_spi_interrupt_control_register_IR_out_full_en        24
#define DFLT_VAL_NX5_spi_interrupt_control_register_IR_out_full_en   0x00000000U

enum {
	BFW_NX5_spi_interrupt_control_register_IR_in_fuel       = 9, /* [8:0] */
	BFW_NX5_spi_interrupt_control_register_IR_out_fuel      = 9, /* [17:9] */
	BFW_NX5_spi_interrupt_control_register_IR_in_fuel_en    = 1, /* [18] */
	BFW_NX5_spi_interrupt_control_register_IR_in_recdata_en = 1, /* [19] */
	BFW_NX5_spi_interrupt_control_register_IR_in_full_en    = 1, /* [20] */
	BFW_NX5_spi_interrupt_control_register_IR_out_fuel_en   = 1, /* [21] */
	BFW_NX5_spi_interrupt_control_register_IR_out_fw_en     = 1, /* [22] */
	BFW_NX5_spi_interrupt_control_register_IR_out_empty_en  = 1, /* [23] */
	BFW_NX5_spi_interrupt_control_register_IR_out_full_en   = 1, /* [24] */
	BFW_NX5_spi_interrupt_control_register_reserved1        = 7  /* [31:25] */
};

typedef struct NX5_SPI_INTERRUPT_CONTROL_REGISTER_BIT_Ttag {
	unsigned int IR_in_fuel       : BFW_NX5_spi_interrupt_control_register_IR_in_fuel;       /* netx100/netx500 only: adjustable fill value of input FIFO, fix to 4 in later versions  */
	unsigned int IR_out_fuel      : BFW_NX5_spi_interrupt_control_register_IR_out_fuel;      /* netx100/netx500 only: adjustable fill value of output FIFO, fix to 4 in later versions */
	unsigned int IR_in_fuel_en    : BFW_NX5_spi_interrupt_control_register_IR_in_fuel_en;    /* IRQ enable for irq_spi(0)  (equals adr_spi_imsc.RXIM in netx50 and later versions)     */
	unsigned int IR_in_recdata_en : BFW_NX5_spi_interrupt_control_register_IR_in_recdata_en; /* IRQ enable for irq_spi(1)  (equals adr_spi_imsc.txneim in netx50 and later versions)   */
	unsigned int IR_in_full_en    : BFW_NX5_spi_interrupt_control_register_IR_in_full_en;    /* IRQ enable for irq_spi(2)  (equals adr_spi_imsc.txfim in netx50 and later versions)    */
	unsigned int IR_out_fuel_en   : BFW_NX5_spi_interrupt_control_register_IR_out_fuel_en;   /* IRQ enable for irq_spi(3)  (equals adr_spi_imsc.TXIM in netx50 and later versions)     */
	unsigned int IR_out_fw_en     : BFW_NX5_spi_interrupt_control_register_IR_out_fw_en;     /* IRQ enable for irq_spi(4), netx100/netx500 only, always "0" in later versions          */
	unsigned int IR_out_empty_en  : BFW_NX5_spi_interrupt_control_register_IR_out_empty_en;  /* IRQ enable for irq_spi(5)  (equals adr_spi_imsc.rxeim in netx50 and later versions)    */
	unsigned int IR_out_full_en   : BFW_NX5_spi_interrupt_control_register_IR_out_full_en;   /* IRQ enable for irq_spi(6), netx100/netx500 only, always "0" in later versions          */
	unsigned int reserved1        : BFW_NX5_spi_interrupt_control_register_reserved1;        /* reserved                                                                               */
} NX5_SPI_INTERRUPT_CONTROL_REGISTER_BIT_T;

typedef union {
	unsigned int                             val;
	NX5_SPI_INTERRUPT_CONTROL_REGISTER_BIT_T bf;
} NX5_SPI_INTERRUPT_CONTROL_REGISTER_T;


/* ===================================================================== */

/* Area of systime */

/* ===================================================================== */

#define Addr_NX5_systime       0x018BFE00U
#define NX5_NETX_SYS_TIME_AREA 0x018BFE00U

/* --------------------------------------------------------------------- */
/* Register systime_ns */
/* => lower SYSTIME register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_ns     0x00000000U
#define Adr_NX5_systime_systime_ns 0x018BFE00U
#define Adr_NX5_systime_ns         0x018BFE00U
#define DFLT_VAL_NX5_systime_ns    0x00000000U

#define MSK_NX5_systime_ns_systime_ns      0xffffffffU
#define SRT_NX5_systime_ns_systime_ns      0
#define DFLT_VAL_NX5_systime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_systime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_SYSTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_systime_ns_systime_ns; /* Systime low (used for counting nanoseconds in IEEE15888) */
} NX5_SYSTIME_NS_BIT_T;

typedef union {
	unsigned int         val;
	NX5_SYSTIME_NS_BIT_T bf;
} NX5_SYSTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register systime_s */
/* => upper SYSTIME register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_s     0x00000004U
#define Adr_NX5_systime_systime_s 0x018BFE04U
#define Adr_NX5_systime_s         0x018BFE04U
#define DFLT_VAL_NX5_systime_s    0x00000000U

#define MSK_NX5_systime_s_systime_s      0xffffffffU
#define SRT_NX5_systime_s_systime_s      0
#define DFLT_VAL_NX5_systime_s_systime_s 0x00000000U

enum {
	BFW_NX5_systime_s_systime_s = 32  /* [31:0] */
};

typedef struct NX5_SYSTIME_S_BIT_Ttag {
	unsigned int systime_s : BFW_NX5_systime_s_systime_s; /* systime high (used for counting seconds in IEEE 1588)      */
	                                                      /* value is incremented, if systime_ns reaches systime_border */
} NX5_SYSTIME_S_BIT_T;

typedef union {
	unsigned int        val;
	NX5_SYSTIME_S_BIT_T bf;
} NX5_SYSTIME_S_T;

/* --------------------------------------------------------------------- */
/* Register systime_border */
/* => SYSTIME border register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_border     0x00000008U
#define Adr_NX5_systime_systime_border 0x018BFE08U
#define Adr_NX5_systime_border         0x018BFE08U
#define DFLT_VAL_NX5_systime_border    0x3b9ac9ffU

#define MSK_NX5_systime_border_systime_border      0xffffffffU
#define SRT_NX5_systime_border_systime_border      0
#define DFLT_VAL_NX5_systime_border_systime_border 0x3b9ac9ffU

enum {
	BFW_NX5_systime_border_systime_border = 32  /* [31:0] */
};

typedef struct NX5_SYSTIME_BORDER_BIT_Ttag {
	unsigned int systime_border : BFW_NX5_systime_border_systime_border; /* Systime border for lower systime:                  */
	                                                                     /* systime_ns counts from 0 to this value (inlcuded), */
} NX5_SYSTIME_BORDER_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SYSTIME_BORDER_BIT_T bf;
} NX5_SYSTIME_BORDER_T;

/* --------------------------------------------------------------------- */
/* Register systime_count_value */
/* => SYSTIME count register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_count_value     0x0000000CU
#define Adr_NX5_systime_systime_count_value 0x018BFE0CU
#define Adr_NX5_systime_count_value         0x018BFE0CU
#define DFLT_VAL_NX5_systime_count_value    0xa0000000U

#define MSK_NX5_systime_count_value_systime_count_value      0xffffffffU
#define SRT_NX5_systime_count_value_systime_count_value      0
#define DFLT_VAL_NX5_systime_count_value_systime_count_value 0xa0000000U

enum {
	BFW_NX5_systime_count_value_systime_count_value = 32  /* [31:0] */
};

typedef struct NX5_SYSTIME_COUNT_VALUE_BIT_Ttag {
	unsigned int systime_count_value : BFW_NX5_systime_count_value_systime_count_value; /* Each clock cycle (systime_count_value >> 28)             */
	                                                                                    /* will be added to systime (rate multiplier for IEEE1588). */
} NX5_SYSTIME_COUNT_VALUE_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_SYSTIME_COUNT_VALUE_BIT_T bf;
} NX5_SYSTIME_COUNT_VALUE_T;

/* --------------------------------------------------------------------- */
/* Register systime_s_compare_value */
/* => SYSTIME sec compare register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_s_compare_value     0x00000010U
#define Adr_NX5_systime_systime_s_compare_value 0x018BFE10U
#define Adr_NX5_systime_s_compare_value         0x018BFE10U
#define DFLT_VAL_NX5_systime_s_compare_value    0x00000000U

#define MSK_NX5_systime_s_compare_value_systime_s_compare_value      0xffffffffU
#define SRT_NX5_systime_s_compare_value_systime_s_compare_value      0
#define DFLT_VAL_NX5_systime_s_compare_value_systime_s_compare_value 0x00000000U

enum {
	BFW_NX5_systime_s_compare_value_systime_s_compare_value = 32  /* [31:0] */
};

typedef struct NX5_SYSTIME_S_COMPARE_VALUE_BIT_Ttag {
	unsigned int systime_s_compare_value : BFW_NX5_systime_s_compare_value_systime_s_compare_value; /* compare value with systime_s (seconds)                                */
	                                                                                                /* set systime_s_compare_irq register if systime_s_compare_enable is set */
} NX5_SYSTIME_S_COMPARE_VALUE_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_SYSTIME_S_COMPARE_VALUE_BIT_T bf;
} NX5_SYSTIME_S_COMPARE_VALUE_T;

/* --------------------------------------------------------------------- */
/* Register systime_s_compare_enable */
/* => SYSTIME sec compare enable register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_s_compare_enable     0x00000014U
#define Adr_NX5_systime_systime_s_compare_enable 0x018BFE14U
#define Adr_NX5_systime_s_compare_enable         0x018BFE14U
#define DFLT_VAL_NX5_systime_s_compare_enable    0x00000000U

#define MSK_NX5_systime_s_compare_enable_systime_s_compare_enable      0x00000001U
#define SRT_NX5_systime_s_compare_enable_systime_s_compare_enable      0
#define DFLT_VAL_NX5_systime_s_compare_enable_systime_s_compare_enable 0x00000000U

enum {
	BFW_NX5_systime_s_compare_enable_systime_s_compare_enable = 1,  /* [0] */
	BFW_NX5_systime_s_compare_enable_reserved1                = 31  /* [31:1] */
};

typedef struct NX5_SYSTIME_S_COMPARE_ENABLE_BIT_Ttag {
	unsigned int systime_s_compare_enable : BFW_NX5_systime_s_compare_enable_systime_s_compare_enable; /* enable compare with systime_s (seconds)        */
	                                                                                                   /* automatic set with set systime_s_compare_value */
	unsigned int reserved1                : BFW_NX5_systime_s_compare_enable_reserved1;                /* reserved                                       */
} NX5_SYSTIME_S_COMPARE_ENABLE_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_SYSTIME_S_COMPARE_ENABLE_BIT_T bf;
} NX5_SYSTIME_S_COMPARE_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register systime_s_compare_irq */
/* => SYSTIME sec compare irq register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_systime_s_compare_irq     0x00000018U
#define Adr_NX5_systime_systime_s_compare_irq 0x018BFE18U
#define Adr_NX5_systime_s_compare_irq         0x018BFE18U
#define DFLT_VAL_NX5_systime_s_compare_irq    0x00000000U

#define MSK_NX5_systime_s_compare_irq_systime_s_compare_irq      0x00000001U
#define SRT_NX5_systime_s_compare_irq_systime_s_compare_irq      0
#define DFLT_VAL_NX5_systime_s_compare_irq_systime_s_compare_irq 0x00000000U

enum {
	BFW_NX5_systime_s_compare_irq_systime_s_compare_irq = 1,  /* [0] */
	BFW_NX5_systime_s_compare_irq_reserved1             = 31  /* [31:1] */
};

typedef struct NX5_SYSTIME_S_COMPARE_IRQ_BIT_Ttag {
	unsigned int systime_s_compare_irq : BFW_NX5_systime_s_compare_irq_systime_s_compare_irq; /* compare with systime_s (seconds) irq           */
	                                                                                          /* set if systime_s equal systime_s_compare_value */
	unsigned int reserved1             : BFW_NX5_systime_s_compare_irq_reserved1;             /* reserved                                       */
} NX5_SYSTIME_S_COMPARE_IRQ_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_SYSTIME_S_COMPARE_IRQ_BIT_T bf;
} NX5_SYSTIME_S_COMPARE_IRQ_T;


/* ===================================================================== */

/* Area of dpm */

/* ===================================================================== */

#define Addr_NX5_dpm 0x018BFF00U

/* --------------------------------------------------------------------- */
/* Register dpm_cfg0x0 */
/* => DPM IO control register 0. */
/*    This register is accessible in any DPM-mode (8, 16, 32 bit, SRAM, Intel, Motorola, little endian, big endian) by access to DPM address 0. */
/*    Basic DPM settings are configurable here to make higher addresses accessible. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_cfg0x0  0x00000000U
#define Adr_NX5_dpm_dpm_cfg0x0  0x018BFF00U
#define Adr_NX5_dpm_cfg0x0      0x018BFF00U
#define DFLT_VAL_NX5_dpm_cfg0x0 0x00000000U

#define MSK_NX5_dpm_cfg0x0_mode        0x0000000fU
#define SRT_NX5_dpm_cfg0x0_mode        0
#define DFLT_VAL_NX5_dpm_cfg0x0_mode   0x00000000U
#define MSK_NX5_dpm_cfg0x0_endian      0x00000030U
#define SRT_NX5_dpm_cfg0x0_endian      4
#define DFLT_VAL_NX5_dpm_cfg0x0_endian 0x00000000U

enum {
	BFW_NX5_dpm_cfg0x0_mode      = 4,  /* [3:0] */
	BFW_NX5_dpm_cfg0x0_endian    = 2,  /* [5:4] */
	BFW_NX5_dpm_cfg0x0_reserved1 = 26  /* [31:6] */
};

typedef struct NX5_DPM_CFG0X0_BIT_Ttag {
	unsigned int mode      : BFW_NX5_dpm_cfg0x0_mode;      /* DPM access mode:                                                                                                   */
	                                                       /* Chip-select, output-enable, write-enable and byte-enables are always low active (i.e.: nCS, nOE, nWE, nBE*, nBHE). */
	unsigned int endian    : BFW_NX5_dpm_cfg0x0_endian;    /* Endianess of 32 bit (DWord) address alignment (B0: least significant byte, B3: most significant byte):             */
	                                                       /* {       |                    |     |     |     |                                                                   */
	unsigned int reserved1 : BFW_NX5_dpm_cfg0x0_reserved1; /* reserved                                                                                                           */
} NX5_DPM_CFG0X0_BIT_T;

typedef union {
	unsigned int         val;
	NX5_DPM_CFG0X0_BIT_T bf;
} NX5_DPM_CFG0X0_T;

/* --------------------------------------------------------------------- */
/* Register dpm_addr_cfg */
/* => DPM external address range configuration register. */
/*    Unused address lines can be used as PIOs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_addr_cfg  0x00000010U
#define Adr_NX5_dpm_dpm_addr_cfg  0x018BFF10U
#define Adr_NX5_dpm_addr_cfg      0x018BFF10U
#define DFLT_VAL_NX5_dpm_addr_cfg 0x00000002U

#define MSK_NX5_dpm_addr_cfg_addr_range      0x0000000fU
#define SRT_NX5_dpm_addr_cfg_addr_range      0
#define DFLT_VAL_NX5_dpm_addr_cfg_addr_range 0x00000002U

enum {
	BFW_NX5_dpm_addr_cfg_addr_range = 4,  /* [3:0] */
	BFW_NX5_dpm_addr_cfg_reserved1  = 28  /* [31:4] */
};

typedef struct NX5_DPM_ADDR_CFG_BIT_Ttag {
	unsigned int addr_range : BFW_NX5_dpm_addr_cfg_addr_range; /* DPM external address range.                                         */
	                                                           /* {       |                                  |                      | */
	unsigned int reserved1  : BFW_NX5_dpm_addr_cfg_reserved1;  /* reserved                                                            */
} NX5_DPM_ADDR_CFG_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_ADDR_CFG_BIT_T bf;
} NX5_DPM_ADDR_CFG_T;

/* --------------------------------------------------------------------- */
/* Register dpm_timing_cfg */
/* => DPM external address range configuration register. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_timing_cfg  0x00000014U
#define Adr_NX5_dpm_dpm_timing_cfg  0x018BFF14U
#define Adr_NX5_dpm_timing_cfg      0x018BFF14U
#define DFLT_VAL_NX5_dpm_timing_cfg 0x00000022U

#define MSK_NX5_dpm_timing_cfg_t_osa            0x00000003U
#define SRT_NX5_dpm_timing_cfg_t_osa            0
#define DFLT_VAL_NX5_dpm_timing_cfg_t_osa       0x00000002U
#define MSK_NX5_dpm_timing_cfg_t_rds            0x00000070U
#define SRT_NX5_dpm_timing_cfg_t_rds            4
#define DFLT_VAL_NX5_dpm_timing_cfg_t_rds       0x00000020U
#define MSK_NX5_dpm_timing_cfg_rd_burst_en      0x00000080U
#define SRT_NX5_dpm_timing_cfg_rd_burst_en      7
#define DFLT_VAL_NX5_dpm_timing_cfg_rd_burst_en 0x00000000U

enum {
	BFW_NX5_dpm_timing_cfg_t_osa       = 2,  /* [1:0] */
	BFW_NX5_dpm_timing_cfg_reserved1   = 2,  /* [3:2] */
	BFW_NX5_dpm_timing_cfg_t_rds       = 3,  /* [6:4] */
	BFW_NX5_dpm_timing_cfg_rd_burst_en = 1,  /* [7] */
	BFW_NX5_dpm_timing_cfg_reserved2   = 24  /* [31:8] */
};

typedef struct NX5_DPM_TIMING_CFG_BIT_Ttag {
	unsigned int t_osa       : BFW_NX5_dpm_timing_cfg_t_osa;       /* Read address setup time.                                                                                                 */
	                                                               /* If address is not stable at read access start (nCS and nRD both low), address sampling can be delayed by this parameter. */
	unsigned int reserved1   : BFW_NX5_dpm_timing_cfg_reserved1;   /* reserved                                                                                                                 */
	unsigned int t_rds       : BFW_NX5_dpm_timing_cfg_t_rds;       /* Read Data Setup Time (in steps of 10ns).                                                                                 */
	                                                               /* If DPM_RDY is used (rdy_mode != 0), DPM_RDY is generated t_rds*10ns after read data is stored on Bus.                    */
	unsigned int rd_burst_en : BFW_NX5_dpm_timing_cfg_rd_burst_en; /* Read Burst enable.                                                                                                       */
	unsigned int reserved2   : BFW_NX5_dpm_timing_cfg_reserved2;   /* reserved                                                                                                                 */
} NX5_DPM_TIMING_CFG_BIT_T;

typedef union {
	unsigned int             val;
	NX5_DPM_TIMING_CFG_BIT_T bf;
} NX5_DPM_TIMING_CFG_T;

/* --------------------------------------------------------------------- */
/* Register dpm_rdy_cfg */
/* => DPM ready(RDY)-signal configuration register. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_rdy_cfg  0x00000018U
#define Adr_NX5_dpm_dpm_rdy_cfg  0x018BFF18U
#define Adr_NX5_dpm_rdy_cfg      0x018BFF18U
#define DFLT_VAL_NX5_dpm_rdy_cfg 0x00000001U

#define MSK_NX5_dpm_rdy_cfg_rdy_pol           0x00000001U
#define SRT_NX5_dpm_rdy_cfg_rdy_pol           0
#define DFLT_VAL_NX5_dpm_rdy_cfg_rdy_pol      0x00000001U
#define MSK_NX5_dpm_rdy_cfg_rdy_drv_mode      0x00000006U
#define SRT_NX5_dpm_rdy_cfg_rdy_drv_mode      1
#define DFLT_VAL_NX5_dpm_rdy_cfg_rdy_drv_mode 0x00000000U
#define MSK_NX5_dpm_rdy_cfg_rdy_sig_mode      0x00000008U
#define SRT_NX5_dpm_rdy_cfg_rdy_sig_mode      3
#define DFLT_VAL_NX5_dpm_rdy_cfg_rdy_sig_mode 0x00000000U

enum {
	BFW_NX5_dpm_rdy_cfg_rdy_pol      = 1,  /* [0] */
	BFW_NX5_dpm_rdy_cfg_rdy_drv_mode = 2,  /* [2:1] */
	BFW_NX5_dpm_rdy_cfg_rdy_sig_mode = 1,  /* [3] */
	BFW_NX5_dpm_rdy_cfg_reserved1    = 28  /* [31:4] */
};

typedef struct NX5_DPM_RDY_CFG_BIT_Ttag {
	unsigned int rdy_pol      : BFW_NX5_dpm_rdy_cfg_rdy_pol;      /* ready signal active state polarity.                                         */
	                                                              /* 1: DPM is ready when external RDY-signal is high.                           */
	unsigned int rdy_drv_mode : BFW_NX5_dpm_rdy_cfg_rdy_drv_mode; /* ready generation mode (similar to netX100/50 data ready drive mode coding). */
	                                                              /* 00: ready signal generation is disabled (High-Impedance mode).              */
	unsigned int rdy_sig_mode : BFW_NX5_dpm_rdy_cfg_rdy_sig_mode; /* ready signal mode.                                                          */
	                                                              /* 1: DPM_RDY is generated as ready/acknowledge pulse.                         */
	unsigned int reserved1    : BFW_NX5_dpm_rdy_cfg_reserved1;    /* reserved                                                                    */
} NX5_DPM_RDY_CFG_BIT_T;

typedef union {
	unsigned int          val;
	NX5_DPM_RDY_CFG_BIT_T bf;
} NX5_DPM_RDY_CFG_T;

/* --------------------------------------------------------------------- */
/* Register dpm_status */
/* => DPM status register. */
/*    DPM access errors can generate IRQ for host device (view DPM IRQ registers further down). For */
/*    error handling, the address an error occurred with is logged in dpm_status_err_addr register. Error bits can be cleared by */
/*    access to dpm_status_err_auto_reset register. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_status 0x0000001CU
#define Adr_NX5_dpm_dpm_status 0x018BFF1CU
#define Adr_NX5_dpm_status     0x018BFF1CU

#define MSK_NX5_dpm_status_unlocked         0x00000001U
#define SRT_NX5_dpm_status_unlocked         0
#define MSK_NX5_dpm_status_rd_err           0x00000002U
#define SRT_NX5_dpm_status_rd_err           1
#define MSK_NX5_dpm_status_wr_err           0x00000004U
#define SRT_NX5_dpm_status_wr_err           2
#define MSK_NX5_dpm_status_rdy_to_err       0x00000008U
#define SRT_NX5_dpm_status_rdy_to_err       3
#define MSK_NX5_dpm_status_bus_conflict_err 0x00000010U
#define SRT_NX5_dpm_status_bus_conflict_err 4
#define MSK_NX5_dpm_status_sel_dpm_serial   0x00000080U
#define SRT_NX5_dpm_status_sel_dpm_serial   7

enum {
	BFW_NX5_dpm_status_unlocked         = 1,  /* [0] */
	BFW_NX5_dpm_status_rd_err           = 1,  /* [1] */
	BFW_NX5_dpm_status_wr_err           = 1,  /* [2] */
	BFW_NX5_dpm_status_rdy_to_err       = 1,  /* [3] */
	BFW_NX5_dpm_status_bus_conflict_err = 1,  /* [4] */
	BFW_NX5_dpm_status_reserved1        = 2,  /* [6:5] */
	BFW_NX5_dpm_status_sel_dpm_serial   = 1,  /* [7] */
	BFW_NX5_dpm_status_reserved2        = 24  /* [31:8] */
};

typedef struct NX5_DPM_STATUS_BIT_Ttag {
	unsigned int unlocked         : BFW_NX5_dpm_status_unlocked;         /* DPM is locked during netX5 power up and boot phase.                                                              */
	                                                                     /* DPM access to other addresses than these DPM control address area cannot be done before this bit is set to 1.    */
	unsigned int rd_err           : BFW_NX5_dpm_status_rd_err;           /* DPM read error mirrored from dpm_err_status_auto_reset register.                                                 */
	                                                                     /* Read errors may occur if ready signal (DPM_RDY) is not respected by an external host device and                  */
	unsigned int wr_err           : BFW_NX5_dpm_status_wr_err;           /* DPM write error mirrored from dpm_err_status_auto_reset register.                                                */
	                                                                     /* Write errors may occur if ready signal (DPM_RDY) is not respected by an external host device and                 */
	unsigned int rdy_to_err       : BFW_NX5_dpm_status_rdy_to_err;       /* DPM_RDY timeout error mirrored from dpm_err_status_auto_reset register.                                          */
	                                                                     /* This error may occur if host device tries to access permanently busy netX address area (e.g. netX                */
	unsigned int bus_conflict_err : BFW_NX5_dpm_status_bus_conflict_err; /* Parallel DPM bus error detected.                                                                                 */
	                                                                     /* This bit is set if all thre signals chip select, read enable and write enable (DPM_CSN, DPM_RDN and DPM_WRN) are */
	unsigned int reserved1        : BFW_NX5_dpm_status_reserved1;        /* reserved                                                                                                         */
	unsigned int sel_dpm_serial   : BFW_NX5_dpm_status_sel_dpm_serial;   /* DPM_MODE configuration input state.                                                                              */
	                                                                     /* 0: DPM is in parallel mode (DPM_MODE configuration input is low).                                                */
	unsigned int reserved2        : BFW_NX5_dpm_status_reserved2;        /* reserved                                                                                                         */
} NX5_DPM_STATUS_BIT_T;

typedef union {
	unsigned int         val;
	NX5_DPM_STATUS_BIT_T bf;
} NX5_DPM_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register dpm_status_err_auto_reset */
/* => DPM error status register with auto reset after read. */
/*    All bits of this register are reset after access (read or write) to this register. */
/*    View dpm_status register for detailed error description. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_status_err_auto_reset 0x00000020U
#define Adr_NX5_dpm_dpm_status_err_auto_reset 0x018BFF20U
#define Adr_NX5_dpm_status_err_auto_reset     0x018BFF20U

#define MSK_NX5_dpm_status_err_auto_reset_rd_err_auto_rst           0x00000002U
#define SRT_NX5_dpm_status_err_auto_reset_rd_err_auto_rst           1
#define MSK_NX5_dpm_status_err_auto_reset_wr_err_auto_rst           0x00000004U
#define SRT_NX5_dpm_status_err_auto_reset_wr_err_auto_rst           2
#define MSK_NX5_dpm_status_err_auto_reset_rdy_to_err_auto_rst       0x00000008U
#define SRT_NX5_dpm_status_err_auto_reset_rdy_to_err_auto_rst       3
#define MSK_NX5_dpm_status_err_auto_reset_bus_conflict_err_auto_rst 0x00000010U
#define SRT_NX5_dpm_status_err_auto_reset_bus_conflict_err_auto_rst 4

enum {
	BFW_NX5_dpm_status_err_auto_reset_reserved1                 = 1,  /* [0] */
	BFW_NX5_dpm_status_err_auto_reset_rd_err_auto_rst           = 1,  /* [1] */
	BFW_NX5_dpm_status_err_auto_reset_wr_err_auto_rst           = 1,  /* [2] */
	BFW_NX5_dpm_status_err_auto_reset_rdy_to_err_auto_rst       = 1,  /* [3] */
	BFW_NX5_dpm_status_err_auto_reset_bus_conflict_err_auto_rst = 1,  /* [4] */
	BFW_NX5_dpm_status_err_auto_reset_reserved2                 = 27  /* [31:5] */
};

typedef struct NX5_DPM_STATUS_ERR_AUTO_RESET_BIT_Ttag {
	unsigned int reserved1                 : BFW_NX5_dpm_status_err_auto_reset_reserved1;                 /* reserved                                                                                                 */
	unsigned int rd_err_auto_rst           : BFW_NX5_dpm_status_err_auto_reset_rd_err_auto_rst;           /* DPM read error detection bit with auto reset function.                                                   */
	                                                                                                      /* For fast write error detection this bit can be checked after each write access. If it was set, the write */
	unsigned int wr_err_auto_rst           : BFW_NX5_dpm_status_err_auto_reset_wr_err_auto_rst;           /* DPM write error detection bit with auto reset function.                                                  */
	                                                                                                      /* For fast read error detection this bit can be checked after each read access. If it was set, the read    */
	unsigned int rdy_to_err_auto_rst       : BFW_NX5_dpm_status_err_auto_reset_rdy_to_err_auto_rst;       /* DPM_RDY timeout error.                                                                                   */
	unsigned int bus_conflict_err_auto_rst : BFW_NX5_dpm_status_err_auto_reset_bus_conflict_err_auto_rst; /* Parallel DPM bus error detected.                                                                         */
	                                                                                                      /* This bit is not used for IRQ generation.                                                                 */
	unsigned int reserved2                 : BFW_NX5_dpm_status_err_auto_reset_reserved2;                 /* reserved                                                                                                 */
} NX5_DPM_STATUS_ERR_AUTO_RESET_BIT_T;

typedef union {
	unsigned int                        val;
	NX5_DPM_STATUS_ERR_AUTO_RESET_BIT_T bf;
} NX5_DPM_STATUS_ERR_AUTO_RESET_T;

/* --------------------------------------------------------------------- */
/* Register dpm_status_err_addr */
/* => DPM error address status register. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_status_err_addr 0x00000024U
#define Adr_NX5_dpm_dpm_status_err_addr 0x018BFF24U
#define Adr_NX5_dpm_status_err_addr     0x018BFF24U

#define MSK_NX5_dpm_status_err_addr_err_addr 0x000fffffU
#define SRT_NX5_dpm_status_err_addr_err_addr 0

enum {
	BFW_NX5_dpm_status_err_addr_err_addr  = 20, /* [19:0] */
	BFW_NX5_dpm_status_err_addr_reserved1 = 12  /* [31:20] */
};

typedef struct NX5_DPM_STATUS_ERR_ADDR_BIT_Ttag {
	unsigned int err_addr  : BFW_NX5_dpm_status_err_addr_err_addr;  /* Access error address.                                                                                   */
	                                                                /* Address of first erroneous access. IRQ handler can use this value to repeat failed accesses after error */
	unsigned int reserved1 : BFW_NX5_dpm_status_err_addr_reserved1; /* reserved                                                                                                */
} NX5_DPM_STATUS_ERR_ADDR_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_DPM_STATUS_ERR_ADDR_BIT_T bf;
} NX5_DPM_STATUS_ERR_ADDR_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win1_end */
/* => DPM window 1 end address configuration register. */
/*    Smallest DPM window configuration unit is 256bytes, i.e lowest 8 bits of address configuration are always 0. */
/*    At address 0x0, fix DPM configuration window is mapped (length: 256 bytes) containing all DPM addresses defined here. Each window starts at */
/*    window end address of the preceding window. Hence external window 1 start address is 0x100, window 2 starts at value programmed in this register and so on. */
/*    Window 4 is highest DPM window an contains always address space above lower windows till address range end. Windows mapped to addresses exceeding */
/*    external address range (view dpm_addr_cfg) can not be accessed by host device. */
/*    There are 4 further programmable DPM windows in netX5. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win1_end  0x00000040U
#define Adr_NX5_dpm_dpm_win1_end  0x018BFF40U
#define Adr_NX5_dpm_win1_end      0x018BFF40U
#define DFLT_VAL_NX5_dpm_win1_end 0x00001000U

#define MSK_NX5_dpm_win1_end_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win1_end_zero_ro         0
#define DFLT_VAL_NX5_dpm_win1_end_zero_ro    0x00000000U
#define MSK_NX5_dpm_win1_end_win_end256      0x000fff00U
#define SRT_NX5_dpm_win1_end_win_end256      8
#define DFLT_VAL_NX5_dpm_win1_end_win_end256 0x00001000U

enum {
	BFW_NX5_dpm_win1_end_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win1_end_win_end256 = 12, /* [19:8] */
	BFW_NX5_dpm_win1_end_reserved1  = 12  /* [31:20] */
};

typedef struct NX5_DPM_WIN1_END_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win1_end_zero_ro;    /* always 0 (window configuration only in steps of 256 bytes possible), other values will be ignored. */
	unsigned int win_end256 : BFW_NX5_dpm_win1_end_win_end256; /* Window 1 end.                                                                                      */
	                                                           /* Last external address is win_end256*256-1.                                                         */
	unsigned int reserved1  : BFW_NX5_dpm_win1_end_reserved1;  /* reserved                                                                                           */
} NX5_DPM_WIN1_END_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN1_END_BIT_T bf;
} NX5_DPM_WIN1_END_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win1_map */
/* => DPM window 1 address map configuration register. */
/*    Smallest DPM window configuration unit is 256bytes, i.e lowest 8 bits of address configuration are always 0. */
/*    There are 3 further programmable DPM windows in netX5. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win1_map  0x00000044U
#define Adr_NX5_dpm_dpm_win1_map  0x018BFF44U
#define Adr_NX5_dpm_win1_map      0x018BFF44U
#define DFLT_VAL_NX5_dpm_win1_map 0x000bf700U

#define MSK_NX5_dpm_win1_map_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win1_map_zero_ro         0
#define DFLT_VAL_NX5_dpm_win1_map_zero_ro    0x00000000U
#define MSK_NX5_dpm_win1_map_win_map256      0x000fff00U
#define SRT_NX5_dpm_win1_map_win_map256      8
#define DFLT_VAL_NX5_dpm_win1_map_win_map256 0x000bf700U
#define MSK_NX5_dpm_win1_map_byte_area       0x40000000U
#define SRT_NX5_dpm_win1_map_byte_area       30
#define DFLT_VAL_NX5_dpm_win1_map_byte_area  0x00000000U
#define MSK_NX5_dpm_win1_map_read_ahead      0x80000000U
#define SRT_NX5_dpm_win1_map_read_ahead      31
#define DFLT_VAL_NX5_dpm_win1_map_read_ahead 0x00000000U

enum {
	BFW_NX5_dpm_win1_map_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win1_map_win_map256 = 12, /* [19:8] */
	BFW_NX5_dpm_win1_map_reserved1  = 10, /* [29:20] */
	BFW_NX5_dpm_win1_map_byte_area  = 1,  /* [30] */
	BFW_NX5_dpm_win1_map_read_ahead = 1   /* [31] */
};

typedef struct NX5_DPM_WIN1_MAP_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win1_map_zero_ro;    /* always 0 (window configuration only in steps of 256 bytes possible), other values will be ignored.              */
	unsigned int win_map256 : BFW_NX5_dpm_win1_map_win_map256; /* netX window 1 address mapping.                                                                                  */
	                                                           /* Only netX internal address area 0x01800000 to 0x01900000 (dpm_full_window: 1MB) is accessible by DPM interface. */
	unsigned int reserved1  : BFW_NX5_dpm_win1_map_reserved1;  /* reserved                                                                                                        */
	unsigned int byte_area  : BFW_NX5_dpm_win1_map_byte_area;  /* Window is byte area.                                                                                            */
	                                                           /* 1: Memory area of this window is byte accessible. All sub DWord write accesses are done immediately.            */
	unsigned int read_ahead : BFW_NX5_dpm_win1_map_read_ahead; /* Read ahead.                                                                                                     */
	                                                           /* If this bit is set, read ahead will be done. This will minimize read cycle time if ready generation is          */
} NX5_DPM_WIN1_MAP_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN1_MAP_BIT_T bf;
} NX5_DPM_WIN1_MAP_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win2_end */
/* => DPM window 2 end address configuration register. */
/*    For detailed information view dpm_win1_end description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win2_end  0x00000048U
#define Adr_NX5_dpm_dpm_win2_end  0x018BFF48U
#define Adr_NX5_dpm_win2_end      0x018BFF48U
#define DFLT_VAL_NX5_dpm_win2_end 0x00006000U

#define MSK_NX5_dpm_win2_end_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win2_end_zero_ro         0
#define DFLT_VAL_NX5_dpm_win2_end_zero_ro    0x00000000U
#define MSK_NX5_dpm_win2_end_win_end256      0x000fff00U
#define SRT_NX5_dpm_win2_end_win_end256      8
#define DFLT_VAL_NX5_dpm_win2_end_win_end256 0x00006000U

enum {
	BFW_NX5_dpm_win2_end_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win2_end_win_end256 = 12, /* [19:8] */
	BFW_NX5_dpm_win2_end_reserved1  = 12  /* [31:20] */
};

typedef struct NX5_DPM_WIN2_END_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win2_end_zero_ro;    /* always 0, other values will be ignored.                  */
	unsigned int win_end256 : BFW_NX5_dpm_win2_end_win_end256; /* window 2 end. Last external address is win_end256*256-1. */
	unsigned int reserved1  : BFW_NX5_dpm_win2_end_reserved1;  /* reserved                                                 */
} NX5_DPM_WIN2_END_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN2_END_BIT_T bf;
} NX5_DPM_WIN2_END_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win2_map */
/* => DPM window 2 address map configuration register. */
/*    For detailed information view dpm_win1_map description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win2_map  0x0000004CU
#define Adr_NX5_dpm_dpm_win2_map  0x018BFF4CU
#define Adr_NX5_dpm_win2_map      0x018BFF4CU
#define DFLT_VAL_NX5_dpm_win2_map 0x000c3000U

#define MSK_NX5_dpm_win2_map_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win2_map_zero_ro         0
#define DFLT_VAL_NX5_dpm_win2_map_zero_ro    0x00000000U
#define MSK_NX5_dpm_win2_map_win_map256      0x000fff00U
#define SRT_NX5_dpm_win2_map_win_map256      8
#define DFLT_VAL_NX5_dpm_win2_map_win_map256 0x000c3000U
#define MSK_NX5_dpm_win2_map_byte_area       0x40000000U
#define SRT_NX5_dpm_win2_map_byte_area       30
#define DFLT_VAL_NX5_dpm_win2_map_byte_area  0x00000000U
#define MSK_NX5_dpm_win2_map_read_ahead      0x80000000U
#define SRT_NX5_dpm_win2_map_read_ahead      31
#define DFLT_VAL_NX5_dpm_win2_map_read_ahead 0x00000000U

enum {
	BFW_NX5_dpm_win2_map_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win2_map_win_map256 = 12, /* [19:8] */
	BFW_NX5_dpm_win2_map_reserved1  = 10, /* [29:20] */
	BFW_NX5_dpm_win2_map_byte_area  = 1,  /* [30] */
	BFW_NX5_dpm_win2_map_read_ahead = 1   /* [31] */
};

typedef struct NX5_DPM_WIN2_MAP_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win2_map_zero_ro;    /* always 0, other values will be ignored. */
	unsigned int win_map256 : BFW_NX5_dpm_win2_map_win_map256; /* netX window 2 address mapping.          */
	unsigned int reserved1  : BFW_NX5_dpm_win2_map_reserved1;  /* reserved                                */
	unsigned int byte_area  : BFW_NX5_dpm_win2_map_byte_area;  /* Window is byte area.                    */
	unsigned int read_ahead : BFW_NX5_dpm_win2_map_read_ahead; /* Read ahead.                             */
} NX5_DPM_WIN2_MAP_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN2_MAP_BIT_T bf;
} NX5_DPM_WIN2_MAP_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win3_end */
/* => DPM window 3 end address configuration register. */
/*    For detailed information view dpm_win1_end description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win3_end  0x00000050U
#define Adr_NX5_dpm_dpm_win3_end  0x018BFF50U
#define Adr_NX5_dpm_win3_end      0x018BFF50U
#define DFLT_VAL_NX5_dpm_win3_end 0x0000a000U

#define MSK_NX5_dpm_win3_end_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win3_end_zero_ro         0
#define DFLT_VAL_NX5_dpm_win3_end_zero_ro    0x00000000U
#define MSK_NX5_dpm_win3_end_win_end256      0x000fff00U
#define SRT_NX5_dpm_win3_end_win_end256      8
#define DFLT_VAL_NX5_dpm_win3_end_win_end256 0x0000a000U

enum {
	BFW_NX5_dpm_win3_end_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win3_end_win_end256 = 12, /* [19:8] */
	BFW_NX5_dpm_win3_end_reserved1  = 12  /* [31:20] */
};

typedef struct NX5_DPM_WIN3_END_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win3_end_zero_ro;    /* always 0, other values will be ignored.                 */
	unsigned int win_end256 : BFW_NX5_dpm_win3_end_win_end256; /* window 3 end.Last external address is win_end256*256-1. */
	unsigned int reserved1  : BFW_NX5_dpm_win3_end_reserved1;  /* reserved                                                */
} NX5_DPM_WIN3_END_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN3_END_BIT_T bf;
} NX5_DPM_WIN3_END_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win3_map */
/* => DPM window 3 address map configuration register. */
/*    For detailed information view dpm_win1_map description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win3_map  0x00000054U
#define Adr_NX5_dpm_dpm_win3_map  0x018BFF54U
#define Adr_NX5_dpm_win3_map      0x018BFF54U
#define DFLT_VAL_NX5_dpm_win3_map 0x000c6000U

#define MSK_NX5_dpm_win3_map_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win3_map_zero_ro         0
#define DFLT_VAL_NX5_dpm_win3_map_zero_ro    0x00000000U
#define MSK_NX5_dpm_win3_map_win_map256      0x000fff00U
#define SRT_NX5_dpm_win3_map_win_map256      8
#define DFLT_VAL_NX5_dpm_win3_map_win_map256 0x000c6000U
#define MSK_NX5_dpm_win3_map_byte_area       0x40000000U
#define SRT_NX5_dpm_win3_map_byte_area       30
#define DFLT_VAL_NX5_dpm_win3_map_byte_area  0x00000000U
#define MSK_NX5_dpm_win3_map_read_ahead      0x80000000U
#define SRT_NX5_dpm_win3_map_read_ahead      31
#define DFLT_VAL_NX5_dpm_win3_map_read_ahead 0x00000000U

enum {
	BFW_NX5_dpm_win3_map_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win3_map_win_map256 = 12, /* [19:8] */
	BFW_NX5_dpm_win3_map_reserved1  = 10, /* [29:20] */
	BFW_NX5_dpm_win3_map_byte_area  = 1,  /* [30] */
	BFW_NX5_dpm_win3_map_read_ahead = 1   /* [31] */
};

typedef struct NX5_DPM_WIN3_MAP_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win3_map_zero_ro;    /* always 0, other values will be ignored. */
	unsigned int win_map256 : BFW_NX5_dpm_win3_map_win_map256; /* netX window map address.                */
	unsigned int reserved1  : BFW_NX5_dpm_win3_map_reserved1;  /* reserved                                */
	unsigned int byte_area  : BFW_NX5_dpm_win3_map_byte_area;  /* Window is byte area.                    */
	unsigned int read_ahead : BFW_NX5_dpm_win3_map_read_ahead; /* Read ahead.                             */
} NX5_DPM_WIN3_MAP_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN3_MAP_BIT_T bf;
} NX5_DPM_WIN3_MAP_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win4_end */
/* => DPM window 4 end address configuration register. */
/*    For detailed information view dpm_win1_end description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win4_end  0x00000058U
#define Adr_NX5_dpm_dpm_win4_end  0x018BFF58U
#define Adr_NX5_dpm_win4_end      0x018BFF58U
#define DFLT_VAL_NX5_dpm_win4_end 0x00010000U

#define MSK_NX5_dpm_win4_end_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win4_end_zero_ro         0
#define DFLT_VAL_NX5_dpm_win4_end_zero_ro    0x00000000U
#define MSK_NX5_dpm_win4_end_win_end256      0x000fff00U
#define SRT_NX5_dpm_win4_end_win_end256      8
#define DFLT_VAL_NX5_dpm_win4_end_win_end256 0x00010000U

enum {
	BFW_NX5_dpm_win4_end_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win4_end_win_end256 = 12, /* [19:8] */
	BFW_NX5_dpm_win4_end_reserved1  = 12  /* [31:20] */
};

typedef struct NX5_DPM_WIN4_END_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win4_end_zero_ro;    /* always 0, other values will be ignored.                 */
	unsigned int win_end256 : BFW_NX5_dpm_win4_end_win_end256; /* window 4 end.Last external address is win_end256*256-1. */
	unsigned int reserved1  : BFW_NX5_dpm_win4_end_reserved1;  /* reserved                                                */
} NX5_DPM_WIN4_END_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN4_END_BIT_T bf;
} NX5_DPM_WIN4_END_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win4_map */
/* => DPM window 4 address map configuration register. */
/*    For detailed information view dpm_win1_map description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win4_map  0x0000005CU
#define Adr_NX5_dpm_dpm_win4_map  0x018BFF5CU
#define Adr_NX5_dpm_win4_map      0x018BFF5CU
#define DFLT_VAL_NX5_dpm_win4_map 0x000d6000U

#define MSK_NX5_dpm_win4_map_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win4_map_zero_ro         0
#define DFLT_VAL_NX5_dpm_win4_map_zero_ro    0x00000000U
#define MSK_NX5_dpm_win4_map_win_map256      0x000fff00U
#define SRT_NX5_dpm_win4_map_win_map256      8
#define DFLT_VAL_NX5_dpm_win4_map_win_map256 0x000d6000U
#define MSK_NX5_dpm_win4_map_byte_area       0x40000000U
#define SRT_NX5_dpm_win4_map_byte_area       30
#define DFLT_VAL_NX5_dpm_win4_map_byte_area  0x00000000U
#define MSK_NX5_dpm_win4_map_read_ahead      0x80000000U
#define SRT_NX5_dpm_win4_map_read_ahead      31
#define DFLT_VAL_NX5_dpm_win4_map_read_ahead 0x00000000U

enum {
	BFW_NX5_dpm_win4_map_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win4_map_win_map256 = 12, /* [19:8] */
	BFW_NX5_dpm_win4_map_reserved1  = 10, /* [29:20] */
	BFW_NX5_dpm_win4_map_byte_area  = 1,  /* [30] */
	BFW_NX5_dpm_win4_map_read_ahead = 1   /* [31] */
};

typedef struct NX5_DPM_WIN4_MAP_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win4_map_zero_ro;    /* always 0, other values will be ignored. */
	unsigned int win_map256 : BFW_NX5_dpm_win4_map_win_map256; /* netX window map address.                */
	unsigned int reserved1  : BFW_NX5_dpm_win4_map_reserved1;  /* reserved                                */
	unsigned int byte_area  : BFW_NX5_dpm_win4_map_byte_area;  /* Window is byte area.                    */
	unsigned int read_ahead : BFW_NX5_dpm_win4_map_read_ahead; /* Read ahead.                             */
} NX5_DPM_WIN4_MAP_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN4_MAP_BIT_T bf;
} NX5_DPM_WIN4_MAP_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win5_end */
/* => DPM window 5 end address configuration register. */
/*    For detailed information view dpm_win1_end description. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win5_end 0x00000060U
#define Adr_NX5_dpm_dpm_win5_end 0x018BFF60U
#define Adr_NX5_dpm_win5_end     0x018BFF60U

#define MSK_NX5_dpm_win5_end_zero_ro       0x000000ffU
#define SRT_NX5_dpm_win5_end_zero_ro       0
#define MSK_NX5_dpm_win5_end_win_end256_ro 0x000fff00U
#define SRT_NX5_dpm_win5_end_win_end256_ro 8

enum {
	BFW_NX5_dpm_win5_end_zero_ro       = 8,  /* [7:0] */
	BFW_NX5_dpm_win5_end_win_end256_ro = 12, /* [19:8] */
	BFW_NX5_dpm_win5_end_reserved1     = 12  /* [31:20] */
};

typedef struct NX5_DPM_WIN5_END_BIT_Ttag {
	unsigned int zero_ro       : BFW_NX5_dpm_win5_end_zero_ro;       /* always 0, other values will be ignored.                                        */
	unsigned int win_end256_ro : BFW_NX5_dpm_win5_end_win_end256_ro; /* Read Only. Window 5 is highest DPM window an contains always the address space */
	                                                                 /* above lower windows up to address range end (view dpm_addr_cfg).               */
	unsigned int reserved1     : BFW_NX5_dpm_win5_end_reserved1;     /* reserved                                                                       */
} NX5_DPM_WIN5_END_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN5_END_BIT_T bf;
} NX5_DPM_WIN5_END_T;

/* --------------------------------------------------------------------- */
/* Register dpm_win5_map */
/* => DPM window 5 address map configuration register. */
/*    For detailed information view dpm_win1_map description. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_win5_map  0x00000064U
#define Adr_NX5_dpm_dpm_win5_map  0x018BFF64U
#define Adr_NX5_dpm_win5_map      0x018BFF64U
#define DFLT_VAL_NX5_dpm_win5_map 0x000f0000U

#define MSK_NX5_dpm_win5_map_zero_ro         0x000000ffU
#define SRT_NX5_dpm_win5_map_zero_ro         0
#define DFLT_VAL_NX5_dpm_win5_map_zero_ro    0x00000000U
#define MSK_NX5_dpm_win5_map_win_map256      0x000fff00U
#define SRT_NX5_dpm_win5_map_win_map256      8
#define DFLT_VAL_NX5_dpm_win5_map_win_map256 0x000f0000U
#define MSK_NX5_dpm_win5_map_byte_area       0x40000000U
#define SRT_NX5_dpm_win5_map_byte_area       30
#define DFLT_VAL_NX5_dpm_win5_map_byte_area  0x00000000U
#define MSK_NX5_dpm_win5_map_read_ahead      0x80000000U
#define SRT_NX5_dpm_win5_map_read_ahead      31
#define DFLT_VAL_NX5_dpm_win5_map_read_ahead 0x00000000U

enum {
	BFW_NX5_dpm_win5_map_zero_ro    = 8,  /* [7:0] */
	BFW_NX5_dpm_win5_map_win_map256 = 12, /* [19:8] */
	BFW_NX5_dpm_win5_map_reserved1  = 10, /* [29:20] */
	BFW_NX5_dpm_win5_map_byte_area  = 1,  /* [30] */
	BFW_NX5_dpm_win5_map_read_ahead = 1   /* [31] */
};

typedef struct NX5_DPM_WIN5_MAP_BIT_Ttag {
	unsigned int zero_ro    : BFW_NX5_dpm_win5_map_zero_ro;    /* always 0, other values will be ignored. */
	unsigned int win_map256 : BFW_NX5_dpm_win5_map_win_map256; /* netX window 5 address mapping.          */
	unsigned int reserved1  : BFW_NX5_dpm_win5_map_reserved1;  /* reserved                                */
	unsigned int byte_area  : BFW_NX5_dpm_win5_map_byte_area;  /* Window is byte area.                    */
	unsigned int read_ahead : BFW_NX5_dpm_win5_map_read_ahead; /* Read ahead.                             */
} NX5_DPM_WIN5_MAP_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_WIN5_MAP_BIT_T bf;
} NX5_DPM_WIN5_MAP_T;

/* --------------------------------------------------------------------- */
/* Register dpm_irq_raw */
/* => netX raw IRQs (before masking). */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_irq_raw 0x00000080U
#define Adr_NX5_dpm_dpm_irq_raw 0x018BFF80U
#define Adr_NX5_dpm_irq_raw     0x018BFF80U

#define MSK_NX5_dpm_irq_raw_com0       0x00000001U
#define SRT_NX5_dpm_irq_raw_com0       0
#define MSK_NX5_dpm_irq_raw_com1       0x00000002U
#define SRT_NX5_dpm_irq_raw_com1       1
#define MSK_NX5_dpm_irq_raw_msync0     0x00000004U
#define SRT_NX5_dpm_irq_raw_msync0     2
#define MSK_NX5_dpm_irq_raw_msync1     0x00000008U
#define SRT_NX5_dpm_irq_raw_msync1     3
#define MSK_NX5_dpm_irq_raw_trigger_lt 0x00000010U
#define SRT_NX5_dpm_irq_raw_trigger_lt 4
#define MSK_NX5_dpm_irq_raw_phy0       0x00000020U
#define SRT_NX5_dpm_irq_raw_phy0       5
#define MSK_NX5_dpm_irq_raw_phy1       0x00000040U
#define SRT_NX5_dpm_irq_raw_phy1       6
#define MSK_NX5_dpm_irq_raw_spi        0x00000080U
#define SRT_NX5_dpm_irq_raw_spi        7
#define MSK_NX5_dpm_irq_raw_systime_s  0x00000100U
#define SRT_NX5_dpm_irq_raw_systime_s  8
#define MSK_NX5_dpm_irq_raw_dpm_err    0x00000200U
#define SRT_NX5_dpm_irq_raw_dpm_err    9
#define MSK_NX5_dpm_irq_raw_test       0x80000000U
#define SRT_NX5_dpm_irq_raw_test       31

enum {
	BFW_NX5_dpm_irq_raw_com0       = 1,  /* [0] */
	BFW_NX5_dpm_irq_raw_com1       = 1,  /* [1] */
	BFW_NX5_dpm_irq_raw_msync0     = 1,  /* [2] */
	BFW_NX5_dpm_irq_raw_msync1     = 1,  /* [3] */
	BFW_NX5_dpm_irq_raw_trigger_lt = 1,  /* [4] */
	BFW_NX5_dpm_irq_raw_phy0       = 1,  /* [5] */
	BFW_NX5_dpm_irq_raw_phy1       = 1,  /* [6] */
	BFW_NX5_dpm_irq_raw_spi        = 1,  /* [7] */
	BFW_NX5_dpm_irq_raw_systime_s  = 1,  /* [8] */
	BFW_NX5_dpm_irq_raw_dpm_err    = 1,  /* [9] */
	BFW_NX5_dpm_irq_raw_reserved1  = 21, /* [30:10] */
	BFW_NX5_dpm_irq_raw_test       = 1   /* [31] */
};

typedef struct NX5_DPM_IRQ_RAW_BIT_Ttag {
	unsigned int com0       : BFW_NX5_dpm_irq_raw_com0;       /* Communication channel 0 (= |xpec0_irq[11:0])                                                               */
	unsigned int com1       : BFW_NX5_dpm_irq_raw_com1;       /* Communication channel 1 (= |xpec1_irq[11:0])                                                               */
	unsigned int msync0     : BFW_NX5_dpm_irq_raw_msync0;     /* Motion synchronization channel 0 (= |xpec0_irq[15:12])                                                     */
	unsigned int msync1     : BFW_NX5_dpm_irq_raw_msync1;     /* Motion synchronization channel 1 (= |xpec1_irq[15:12])                                                     */
	unsigned int trigger_lt : BFW_NX5_dpm_irq_raw_trigger_lt; /* Real-time Ethernet trigger_lt from XC.                                                                     */
	unsigned int phy0       : BFW_NX5_dpm_irq_raw_phy0;       /* external PHY0 interrupt.                                                                                   */
	unsigned int phy1       : BFW_NX5_dpm_irq_raw_phy1;       /* external PHY1 interrupt.                                                                                   */
	unsigned int spi        : BFW_NX5_dpm_irq_raw_spi;        /* SPI interrupt.                                                                                             */
	unsigned int systime_s  : BFW_NX5_dpm_irq_raw_systime_s;  /* systime 1day interrupt from SYSTIME module, Windows CE required.                                           */
	unsigned int dpm_err    : BFW_NX5_dpm_irq_raw_dpm_err;    /* DPM access error. Check error bits in dpm_status register.                                                 */
	unsigned int reserved1  : BFW_NX5_dpm_irq_raw_reserved1;  /* reserved                                                                                                   */
	unsigned int test       : BFW_NX5_dpm_irq_raw_test;       /* Test bit for interrupt test.                                                                               */
	                                                          /* Test-IRQ state is always 1 if appropriate IRQ/DIRQ or FIQ/SIRQ mask is set. If no mask is set, state is 0. */
} NX5_DPM_IRQ_RAW_BIT_T;

typedef union {
	unsigned int          val;
	NX5_DPM_IRQ_RAW_BIT_T bf;
} NX5_DPM_IRQ_RAW_T;

/* --------------------------------------------------------------------- */
/* Register dpm_irq_fiq_mask */
/* => netX fast/sirq interrupt mask. */
/*    If bit is set, the according interrupt will activate the FIQ/SIRQ signal if asserted. */
/*    Interrupts must be reset in interrupt generating module. Interrupts cannot be cleared here. */
/*    To release FIQ/SIRQ signal without clearing interrupt in module, reset according mask bit to 0. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_irq_fiq_mask  0x00000084U
#define Adr_NX5_dpm_dpm_irq_fiq_mask  0x018BFF84U
#define Adr_NX5_dpm_irq_fiq_mask      0x018BFF84U
#define DFLT_VAL_NX5_dpm_irq_fiq_mask 0x00000000U

#define MSK_NX5_dpm_irq_fiq_mask_com0            0x00000001U
#define SRT_NX5_dpm_irq_fiq_mask_com0            0
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_com0       0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_com1            0x00000002U
#define SRT_NX5_dpm_irq_fiq_mask_com1            1
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_com1       0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_msync0          0x00000004U
#define SRT_NX5_dpm_irq_fiq_mask_msync0          2
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_msync0     0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_msync1          0x00000008U
#define SRT_NX5_dpm_irq_fiq_mask_msync1          3
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_msync1     0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_trigger_lt      0x00000010U
#define SRT_NX5_dpm_irq_fiq_mask_trigger_lt      4
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_trigger_lt 0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_phy0            0x00000020U
#define SRT_NX5_dpm_irq_fiq_mask_phy0            5
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_phy0       0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_phy1            0x00000040U
#define SRT_NX5_dpm_irq_fiq_mask_phy1            6
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_phy1       0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_spi             0x00000080U
#define SRT_NX5_dpm_irq_fiq_mask_spi             7
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_spi        0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_systime_s       0x00000100U
#define SRT_NX5_dpm_irq_fiq_mask_systime_s       8
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_systime_s  0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_dpm_err         0x00000200U
#define SRT_NX5_dpm_irq_fiq_mask_dpm_err         9
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_dpm_err    0x00000000U
#define MSK_NX5_dpm_irq_fiq_mask_test            0x80000000U
#define SRT_NX5_dpm_irq_fiq_mask_test            31
#define DFLT_VAL_NX5_dpm_irq_fiq_mask_test       0x00000000U

enum {
	BFW_NX5_dpm_irq_fiq_mask_com0       = 1,  /* [0] */
	BFW_NX5_dpm_irq_fiq_mask_com1       = 1,  /* [1] */
	BFW_NX5_dpm_irq_fiq_mask_msync0     = 1,  /* [2] */
	BFW_NX5_dpm_irq_fiq_mask_msync1     = 1,  /* [3] */
	BFW_NX5_dpm_irq_fiq_mask_trigger_lt = 1,  /* [4] */
	BFW_NX5_dpm_irq_fiq_mask_phy0       = 1,  /* [5] */
	BFW_NX5_dpm_irq_fiq_mask_phy1       = 1,  /* [6] */
	BFW_NX5_dpm_irq_fiq_mask_spi        = 1,  /* [7] */
	BFW_NX5_dpm_irq_fiq_mask_systime_s  = 1,  /* [8] */
	BFW_NX5_dpm_irq_fiq_mask_dpm_err    = 1,  /* [9] */
	BFW_NX5_dpm_irq_fiq_mask_reserved1  = 21, /* [30:10] */
	BFW_NX5_dpm_irq_fiq_mask_test       = 1   /* [31] */
};

typedef struct NX5_DPM_IRQ_FIQ_MASK_BIT_Ttag {
	unsigned int com0       : BFW_NX5_dpm_irq_fiq_mask_com0;       /* Communication channel 0 (= |xpec0_irq[11:0])                     */
	unsigned int com1       : BFW_NX5_dpm_irq_fiq_mask_com1;       /* Communication channel 1 (= |xpec1_irq[11:0])                     */
	unsigned int msync0     : BFW_NX5_dpm_irq_fiq_mask_msync0;     /* Motion synchronization channel 0 (= |xpec0_irq[15:12])           */
	unsigned int msync1     : BFW_NX5_dpm_irq_fiq_mask_msync1;     /* Motion synchronization channel 1 (= |xpec1_irq[15:12])           */
	unsigned int trigger_lt : BFW_NX5_dpm_irq_fiq_mask_trigger_lt; /* Real-time Ethernet trigger_lt from XC.                           */
	unsigned int phy0       : BFW_NX5_dpm_irq_fiq_mask_phy0;       /* external PHY0 interrupt.                                         */
	unsigned int phy1       : BFW_NX5_dpm_irq_fiq_mask_phy1;       /* external PHY1 interrupt.                                         */
	unsigned int spi        : BFW_NX5_dpm_irq_fiq_mask_spi;        /* SPI interrupt.                                                   */
	unsigned int systime_s  : BFW_NX5_dpm_irq_fiq_mask_systime_s;  /* systime 1day interrupt from SYSTIME module, Windows CE required. */
	unsigned int dpm_err    : BFW_NX5_dpm_irq_fiq_mask_dpm_err;    /* DPM access error. Check error bits in dpm_status register.       */
	unsigned int reserved1  : BFW_NX5_dpm_irq_fiq_mask_reserved1;  /* reserved                                                         */
	unsigned int test       : BFW_NX5_dpm_irq_fiq_mask_test;       /* Test bit for interrupt test.                                     */
	                                                               /* Enable this bit to test FIQ/SIRQ function.                       */
} NX5_DPM_IRQ_FIQ_MASK_BIT_T;

typedef union {
	unsigned int               val;
	NX5_DPM_IRQ_FIQ_MASK_BIT_T bf;
} NX5_DPM_IRQ_FIQ_MASK_T;

/* --------------------------------------------------------------------- */
/* Register dpm_irq_irq_mask */
/* => netX normal/dirq interrupt mask. */
/*    If bit is set, the according interrupt will activate the IRQ/DIRQ signal if asserted. */
/*    Interrupts must be reset in interrupt generating module. Interrupts cannot be cleared here. */
/*    To release IRQ/DIRQ signal without clearing interrupt in module, reset according mask bit to 0. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_irq_irq_mask  0x00000088U
#define Adr_NX5_dpm_dpm_irq_irq_mask  0x018BFF88U
#define Adr_NX5_dpm_irq_irq_mask      0x018BFF88U
#define DFLT_VAL_NX5_dpm_irq_irq_mask 0x00000000U

#define MSK_NX5_dpm_irq_irq_mask_com0            0x00000001U
#define SRT_NX5_dpm_irq_irq_mask_com0            0
#define DFLT_VAL_NX5_dpm_irq_irq_mask_com0       0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_com1            0x00000002U
#define SRT_NX5_dpm_irq_irq_mask_com1            1
#define DFLT_VAL_NX5_dpm_irq_irq_mask_com1       0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_msync0          0x00000004U
#define SRT_NX5_dpm_irq_irq_mask_msync0          2
#define DFLT_VAL_NX5_dpm_irq_irq_mask_msync0     0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_msync1          0x00000008U
#define SRT_NX5_dpm_irq_irq_mask_msync1          3
#define DFLT_VAL_NX5_dpm_irq_irq_mask_msync1     0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_trigger_lt      0x00000010U
#define SRT_NX5_dpm_irq_irq_mask_trigger_lt      4
#define DFLT_VAL_NX5_dpm_irq_irq_mask_trigger_lt 0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_phy0            0x00000020U
#define SRT_NX5_dpm_irq_irq_mask_phy0            5
#define DFLT_VAL_NX5_dpm_irq_irq_mask_phy0       0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_phy1            0x00000040U
#define SRT_NX5_dpm_irq_irq_mask_phy1            6
#define DFLT_VAL_NX5_dpm_irq_irq_mask_phy1       0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_spi             0x00000080U
#define SRT_NX5_dpm_irq_irq_mask_spi             7
#define DFLT_VAL_NX5_dpm_irq_irq_mask_spi        0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_systime_s       0x00000100U
#define SRT_NX5_dpm_irq_irq_mask_systime_s       8
#define DFLT_VAL_NX5_dpm_irq_irq_mask_systime_s  0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_dpm_err         0x00000200U
#define SRT_NX5_dpm_irq_irq_mask_dpm_err         9
#define DFLT_VAL_NX5_dpm_irq_irq_mask_dpm_err    0x00000000U
#define MSK_NX5_dpm_irq_irq_mask_test            0x80000000U
#define SRT_NX5_dpm_irq_irq_mask_test            31
#define DFLT_VAL_NX5_dpm_irq_irq_mask_test       0x00000000U

enum {
	BFW_NX5_dpm_irq_irq_mask_com0       = 1,  /* [0] */
	BFW_NX5_dpm_irq_irq_mask_com1       = 1,  /* [1] */
	BFW_NX5_dpm_irq_irq_mask_msync0     = 1,  /* [2] */
	BFW_NX5_dpm_irq_irq_mask_msync1     = 1,  /* [3] */
	BFW_NX5_dpm_irq_irq_mask_trigger_lt = 1,  /* [4] */
	BFW_NX5_dpm_irq_irq_mask_phy0       = 1,  /* [5] */
	BFW_NX5_dpm_irq_irq_mask_phy1       = 1,  /* [6] */
	BFW_NX5_dpm_irq_irq_mask_spi        = 1,  /* [7] */
	BFW_NX5_dpm_irq_irq_mask_systime_s  = 1,  /* [8] */
	BFW_NX5_dpm_irq_irq_mask_dpm_err    = 1,  /* [9] */
	BFW_NX5_dpm_irq_irq_mask_reserved1  = 21, /* [30:10] */
	BFW_NX5_dpm_irq_irq_mask_test       = 1   /* [31] */
};

typedef struct NX5_DPM_IRQ_IRQ_MASK_BIT_Ttag {
	unsigned int com0       : BFW_NX5_dpm_irq_irq_mask_com0;       /* Communication channel 0 (= |xpec0_irq[11:0])                     */
	unsigned int com1       : BFW_NX5_dpm_irq_irq_mask_com1;       /* Communication channel 1 (= |xpec1_irq[11:0])                     */
	unsigned int msync0     : BFW_NX5_dpm_irq_irq_mask_msync0;     /* Motion synchronization channel 0 (= |xpec0_irq[15:12])           */
	unsigned int msync1     : BFW_NX5_dpm_irq_irq_mask_msync1;     /* Motion synchronization channel 1 (= |xpec1_irq[15:12])           */
	unsigned int trigger_lt : BFW_NX5_dpm_irq_irq_mask_trigger_lt; /* Real-time Ethernet trigger_lt from XC.                           */
	unsigned int phy0       : BFW_NX5_dpm_irq_irq_mask_phy0;       /* external PHY0 interrupt.                                         */
	unsigned int phy1       : BFW_NX5_dpm_irq_irq_mask_phy1;       /* external PHY1 interrupt.                                         */
	unsigned int spi        : BFW_NX5_dpm_irq_irq_mask_spi;        /* SPI interrupt.                                                   */
	unsigned int systime_s  : BFW_NX5_dpm_irq_irq_mask_systime_s;  /* systime 1day interrupt from SYSTIME module, Windows CE required. */
	unsigned int dpm_err    : BFW_NX5_dpm_irq_irq_mask_dpm_err;    /* DPM access error. Check error bits in dpm_status register.       */
	unsigned int reserved1  : BFW_NX5_dpm_irq_irq_mask_reserved1;  /* reserved                                                         */
	unsigned int test       : BFW_NX5_dpm_irq_irq_mask_test;       /* Test bit for interrupt test.                                     */
	                                                               /* Enable this bit to test IRQ/DIRQ function.                       */
} NX5_DPM_IRQ_IRQ_MASK_BIT_T;

typedef union {
	unsigned int               val;
	NX5_DPM_IRQ_IRQ_MASK_BIT_T bf;
} NX5_DPM_IRQ_IRQ_MASK_T;

/* --------------------------------------------------------------------- */
/* Register dpm_irq_fiq_masked */
/* => netX masked fast/sirq interrupt. */
/*    Bit is set, if the according mask bit is set in dpm_irq_fiq_mask-register. */
/*    FIQ/SIRQ signal is asserted if at least one bit is set here. */
/*    Interrupts must be reset in interrupt generating module. Interrupts cannot be cleared here. */
/*    To release FIQ/SIRQ signal without clearing interrupt in module, reset according mask bit to 0. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_irq_fiq_masked 0x0000008CU
#define Adr_NX5_dpm_dpm_irq_fiq_masked 0x018BFF8CU
#define Adr_NX5_dpm_irq_fiq_masked     0x018BFF8CU

#define MSK_NX5_dpm_irq_fiq_masked_com0       0x00000001U
#define SRT_NX5_dpm_irq_fiq_masked_com0       0
#define MSK_NX5_dpm_irq_fiq_masked_com1       0x00000002U
#define SRT_NX5_dpm_irq_fiq_masked_com1       1
#define MSK_NX5_dpm_irq_fiq_masked_msync0     0x00000004U
#define SRT_NX5_dpm_irq_fiq_masked_msync0     2
#define MSK_NX5_dpm_irq_fiq_masked_msync1     0x00000008U
#define SRT_NX5_dpm_irq_fiq_masked_msync1     3
#define MSK_NX5_dpm_irq_fiq_masked_trigger_lt 0x00000010U
#define SRT_NX5_dpm_irq_fiq_masked_trigger_lt 4
#define MSK_NX5_dpm_irq_fiq_masked_phy0       0x00000020U
#define SRT_NX5_dpm_irq_fiq_masked_phy0       5
#define MSK_NX5_dpm_irq_fiq_masked_phy1       0x00000040U
#define SRT_NX5_dpm_irq_fiq_masked_phy1       6
#define MSK_NX5_dpm_irq_fiq_masked_spi        0x00000080U
#define SRT_NX5_dpm_irq_fiq_masked_spi        7
#define MSK_NX5_dpm_irq_fiq_masked_systime_s  0x00000100U
#define SRT_NX5_dpm_irq_fiq_masked_systime_s  8
#define MSK_NX5_dpm_irq_fiq_masked_dpm_err    0x00000200U
#define SRT_NX5_dpm_irq_fiq_masked_dpm_err    9
#define MSK_NX5_dpm_irq_fiq_masked_test       0x80000000U
#define SRT_NX5_dpm_irq_fiq_masked_test       31

enum {
	BFW_NX5_dpm_irq_fiq_masked_com0       = 1,  /* [0] */
	BFW_NX5_dpm_irq_fiq_masked_com1       = 1,  /* [1] */
	BFW_NX5_dpm_irq_fiq_masked_msync0     = 1,  /* [2] */
	BFW_NX5_dpm_irq_fiq_masked_msync1     = 1,  /* [3] */
	BFW_NX5_dpm_irq_fiq_masked_trigger_lt = 1,  /* [4] */
	BFW_NX5_dpm_irq_fiq_masked_phy0       = 1,  /* [5] */
	BFW_NX5_dpm_irq_fiq_masked_phy1       = 1,  /* [6] */
	BFW_NX5_dpm_irq_fiq_masked_spi        = 1,  /* [7] */
	BFW_NX5_dpm_irq_fiq_masked_systime_s  = 1,  /* [8] */
	BFW_NX5_dpm_irq_fiq_masked_dpm_err    = 1,  /* [9] */
	BFW_NX5_dpm_irq_fiq_masked_reserved1  = 21, /* [30:10] */
	BFW_NX5_dpm_irq_fiq_masked_test       = 1   /* [31] */
};

typedef struct NX5_DPM_IRQ_FIQ_MASKED_BIT_Ttag {
	unsigned int com0       : BFW_NX5_dpm_irq_fiq_masked_com0;       /* Communication channel 0 (= |xpec0_irq[11:0])                                                               */
	unsigned int com1       : BFW_NX5_dpm_irq_fiq_masked_com1;       /* Communication channel 1 (= |xpec1_irq[11:0])                                                               */
	unsigned int msync0     : BFW_NX5_dpm_irq_fiq_masked_msync0;     /* Motion synchronization channel 0 (= |xpec0_irq[15:12])                                                     */
	unsigned int msync1     : BFW_NX5_dpm_irq_fiq_masked_msync1;     /* Motion synchronization channel 1 (= |xpec1_irq[15:12])                                                     */
	unsigned int trigger_lt : BFW_NX5_dpm_irq_fiq_masked_trigger_lt; /* Real-time Ethernet trigger_lt from XC.                                                                     */
	unsigned int phy0       : BFW_NX5_dpm_irq_fiq_masked_phy0;       /* external PHY0 interrupt.                                                                                   */
	unsigned int phy1       : BFW_NX5_dpm_irq_fiq_masked_phy1;       /* external PHY1 interrupt.                                                                                   */
	unsigned int spi        : BFW_NX5_dpm_irq_fiq_masked_spi;        /* SPI interrupt.                                                                                             */
	unsigned int systime_s  : BFW_NX5_dpm_irq_fiq_masked_systime_s;  /* systime 1day interrupt from SYSTIME module, Windows CE required.                                           */
	unsigned int dpm_err    : BFW_NX5_dpm_irq_fiq_masked_dpm_err;    /* DPM access error. Check error bits in dpm_status register.                                                 */
	unsigned int reserved1  : BFW_NX5_dpm_irq_fiq_masked_reserved1;  /* reserved                                                                                                   */
	unsigned int test       : BFW_NX5_dpm_irq_fiq_masked_test;       /* Test bit for interrupt test.                                                                               */
	                                                                 /* Test-IRQ state is always 1 if appropriate IRQ/DIRQ or FIQ/SIRQ mask is set. If no mast is set, state is 0. */
} NX5_DPM_IRQ_FIQ_MASKED_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_DPM_IRQ_FIQ_MASKED_BIT_T bf;
} NX5_DPM_IRQ_FIQ_MASKED_T;

/* --------------------------------------------------------------------- */
/* Register dpm_irq_irq_masked */
/* => netX masked normal/dirq interrupt. */
/*    Bit is set, if the according mask bit is set in dpm_irq_irq_mask-register. */
/*    IRQ/DIRQ signal is asserted if at least one bit is set here. */
/*    Interrupts must be reset in interrupt generating module. Interrupts cannot be cleared here. */
/*    To release IRQ/DIRQ signal without clearing interrupt in module, reset according mask bit to 0. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_irq_irq_masked 0x00000090U
#define Adr_NX5_dpm_dpm_irq_irq_masked 0x018BFF90U
#define Adr_NX5_dpm_irq_irq_masked     0x018BFF90U

#define MSK_NX5_dpm_irq_irq_masked_com0       0x00000001U
#define SRT_NX5_dpm_irq_irq_masked_com0       0
#define MSK_NX5_dpm_irq_irq_masked_com1       0x00000002U
#define SRT_NX5_dpm_irq_irq_masked_com1       1
#define MSK_NX5_dpm_irq_irq_masked_msync0     0x00000004U
#define SRT_NX5_dpm_irq_irq_masked_msync0     2
#define MSK_NX5_dpm_irq_irq_masked_msync1     0x00000008U
#define SRT_NX5_dpm_irq_irq_masked_msync1     3
#define MSK_NX5_dpm_irq_irq_masked_trigger_lt 0x00000010U
#define SRT_NX5_dpm_irq_irq_masked_trigger_lt 4
#define MSK_NX5_dpm_irq_irq_masked_phy0       0x00000020U
#define SRT_NX5_dpm_irq_irq_masked_phy0       5
#define MSK_NX5_dpm_irq_irq_masked_phy1       0x00000040U
#define SRT_NX5_dpm_irq_irq_masked_phy1       6
#define MSK_NX5_dpm_irq_irq_masked_spi        0x00000080U
#define SRT_NX5_dpm_irq_irq_masked_spi        7
#define MSK_NX5_dpm_irq_irq_masked_systime_s  0x00000100U
#define SRT_NX5_dpm_irq_irq_masked_systime_s  8
#define MSK_NX5_dpm_irq_irq_masked_dpm_err    0x00000200U
#define SRT_NX5_dpm_irq_irq_masked_dpm_err    9
#define MSK_NX5_dpm_irq_irq_masked_test       0x80000000U
#define SRT_NX5_dpm_irq_irq_masked_test       31

enum {
	BFW_NX5_dpm_irq_irq_masked_com0       = 1,  /* [0] */
	BFW_NX5_dpm_irq_irq_masked_com1       = 1,  /* [1] */
	BFW_NX5_dpm_irq_irq_masked_msync0     = 1,  /* [2] */
	BFW_NX5_dpm_irq_irq_masked_msync1     = 1,  /* [3] */
	BFW_NX5_dpm_irq_irq_masked_trigger_lt = 1,  /* [4] */
	BFW_NX5_dpm_irq_irq_masked_phy0       = 1,  /* [5] */
	BFW_NX5_dpm_irq_irq_masked_phy1       = 1,  /* [6] */
	BFW_NX5_dpm_irq_irq_masked_spi        = 1,  /* [7] */
	BFW_NX5_dpm_irq_irq_masked_systime_s  = 1,  /* [8] */
	BFW_NX5_dpm_irq_irq_masked_dpm_err    = 1,  /* [9] */
	BFW_NX5_dpm_irq_irq_masked_reserved1  = 21, /* [30:10] */
	BFW_NX5_dpm_irq_irq_masked_test       = 1   /* [31] */
};

typedef struct NX5_DPM_IRQ_IRQ_MASKED_BIT_Ttag {
	unsigned int com0       : BFW_NX5_dpm_irq_irq_masked_com0;       /* Communication channel 0 (= |xpec0_irq[11:0])                                                               */
	unsigned int com1       : BFW_NX5_dpm_irq_irq_masked_com1;       /* Communication channel 1 (= |xpec1_irq[11:0])                                                               */
	unsigned int msync0     : BFW_NX5_dpm_irq_irq_masked_msync0;     /* Motion synchronization channel 0 (= |xpec0_irq[15:12])                                                     */
	unsigned int msync1     : BFW_NX5_dpm_irq_irq_masked_msync1;     /* Motion synchronization channel 1 (= |xpec1_irq[15:12])                                                     */
	unsigned int trigger_lt : BFW_NX5_dpm_irq_irq_masked_trigger_lt; /* Real-time Ethernet trigger_lt from XC.                                                                     */
	unsigned int phy0       : BFW_NX5_dpm_irq_irq_masked_phy0;       /* external PHY0 interrupt.                                                                                   */
	unsigned int phy1       : BFW_NX5_dpm_irq_irq_masked_phy1;       /* external PHY1 interrupt.                                                                                   */
	unsigned int spi        : BFW_NX5_dpm_irq_irq_masked_spi;        /* SPI interrupt.                                                                                             */
	unsigned int systime_s  : BFW_NX5_dpm_irq_irq_masked_systime_s;  /* systime 1day interrupt from SYSTIME module, Windows CE required.                                           */
	unsigned int dpm_err    : BFW_NX5_dpm_irq_irq_masked_dpm_err;    /* DPM access error. Check error bits in dpm_status register.                                                 */
	unsigned int reserved1  : BFW_NX5_dpm_irq_irq_masked_reserved1;  /* reserved                                                                                                   */
	unsigned int test       : BFW_NX5_dpm_irq_irq_masked_test;       /* Test bit for interrupt test.                                                                               */
	                                                                 /* Test-IRQ state is always 1 if appropriate IRQ/DIRQ or FIQ/SIRQ mask is set. If no mast is set, state is 0. */
} NX5_DPM_IRQ_IRQ_MASKED_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_DPM_IRQ_IRQ_MASKED_BIT_T bf;
} NX5_DPM_IRQ_IRQ_MASKED_T;

/* --------------------------------------------------------------------- */
/* Register dpm_fiq_irq_pad_ctrl */
/* => netX IRQ/DIRQ and FIQ/SIRQ signal (pad) control register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_fiq_irq_pad_ctrl  0x00000094U
#define Adr_NX5_dpm_dpm_fiq_irq_pad_ctrl  0x018BFF94U
#define Adr_NX5_dpm_fiq_irq_pad_ctrl      0x018BFF94U
#define DFLT_VAL_NX5_dpm_fiq_irq_pad_ctrl 0x00000000U

#define MSK_NX5_dpm_fiq_irq_pad_ctrl_irq_pol      0x00000001U
#define SRT_NX5_dpm_fiq_irq_pad_ctrl_irq_pol      0
#define DFLT_VAL_NX5_dpm_fiq_irq_pad_ctrl_irq_pol 0x00000000U
#define MSK_NX5_dpm_fiq_irq_pad_ctrl_irq_oec      0x00000002U
#define SRT_NX5_dpm_fiq_irq_pad_ctrl_irq_oec      1
#define DFLT_VAL_NX5_dpm_fiq_irq_pad_ctrl_irq_oec 0x00000000U
#define MSK_NX5_dpm_fiq_irq_pad_ctrl_fiq_pol      0x00000100U
#define SRT_NX5_dpm_fiq_irq_pad_ctrl_fiq_pol      8
#define DFLT_VAL_NX5_dpm_fiq_irq_pad_ctrl_fiq_pol 0x00000000U
#define MSK_NX5_dpm_fiq_irq_pad_ctrl_fiq_oec      0x00000200U
#define SRT_NX5_dpm_fiq_irq_pad_ctrl_fiq_oec      9
#define DFLT_VAL_NX5_dpm_fiq_irq_pad_ctrl_fiq_oec 0x00000000U

enum {
	BFW_NX5_dpm_fiq_irq_pad_ctrl_irq_pol   = 1,  /* [0] */
	BFW_NX5_dpm_fiq_irq_pad_ctrl_irq_oec   = 1,  /* [1] */
	BFW_NX5_dpm_fiq_irq_pad_ctrl_reserved1 = 6,  /* [7:2] */
	BFW_NX5_dpm_fiq_irq_pad_ctrl_fiq_pol   = 1,  /* [8] */
	BFW_NX5_dpm_fiq_irq_pad_ctrl_fiq_oec   = 1,  /* [9] */
	BFW_NX5_dpm_fiq_irq_pad_ctrl_reserved2 = 22  /* [31:10] */
};

typedef struct NX5_DPM_FIQ_IRQ_PAD_CTRL_BIT_Ttag {
	unsigned int irq_pol   : BFW_NX5_dpm_fiq_irq_pad_ctrl_irq_pol;   /* IRQ/DIRQ signal polarity:            */
	                                                                 /*  0: IRQ/DIRQ is active low.          */
	unsigned int irq_oec   : BFW_NX5_dpm_fiq_irq_pad_ctrl_irq_oec;   /* IRQ output enable controlled.        */
	                                                                 /* 0: IRQ/DIRQ signal is always driven. */
	unsigned int reserved1 : BFW_NX5_dpm_fiq_irq_pad_ctrl_reserved1; /* reserved                             */
	unsigned int fiq_pol   : BFW_NX5_dpm_fiq_irq_pad_ctrl_fiq_pol;   /* FIQ/SIRQ signal polarity:            */
	                                                                 /*  0: FIQ/SIRQ is active low.          */
	unsigned int fiq_oec   : BFW_NX5_dpm_fiq_irq_pad_ctrl_fiq_oec;   /* FIQ/SIRQ output enable controlled.   */
	                                                                 /* 0: FIQ/SIRQ signal is always driven. */
	unsigned int reserved2 : BFW_NX5_dpm_fiq_irq_pad_ctrl_reserved2; /* reserved                             */
} NX5_DPM_FIQ_IRQ_PAD_CTRL_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_DPM_FIQ_IRQ_PAD_CTRL_BIT_T bf;
} NX5_DPM_FIQ_IRQ_PAD_CTRL_T;

/* --------------------------------------------------------------------- */
/* Register dpm_io_cfg_misc */
/* => DPM IO configuration register 0. */
/*    Unused DPM IOs can be used as PIOs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_io_cfg_misc  0x000000A0U
#define Adr_NX5_dpm_dpm_io_cfg_misc  0x018BFFA0U
#define Adr_NX5_dpm_io_cfg_misc      0x018BFFA0U
#define DFLT_VAL_NX5_dpm_io_cfg_misc 0x00000001U

#define MSK_NX5_dpm_io_cfg_misc_sel_rdy_pio       0x00000001U
#define SRT_NX5_dpm_io_cfg_misc_sel_rdy_pio       0
#define DFLT_VAL_NX5_dpm_io_cfg_misc_sel_rdy_pio  0x00000001U
#define MSK_NX5_dpm_io_cfg_misc_sel_dirq_pio      0x00000002U
#define SRT_NX5_dpm_io_cfg_misc_sel_dirq_pio      1
#define DFLT_VAL_NX5_dpm_io_cfg_misc_sel_dirq_pio 0x00000000U
#define MSK_NX5_dpm_io_cfg_misc_sel_sirq_pio      0x00000004U
#define SRT_NX5_dpm_io_cfg_misc_sel_sirq_pio      2
#define DFLT_VAL_NX5_dpm_io_cfg_misc_sel_sirq_pio 0x00000000U

enum {
	BFW_NX5_dpm_io_cfg_misc_sel_rdy_pio  = 1,  /* [0] */
	BFW_NX5_dpm_io_cfg_misc_sel_dirq_pio = 1,  /* [1] */
	BFW_NX5_dpm_io_cfg_misc_sel_sirq_pio = 1,  /* [2] */
	BFW_NX5_dpm_io_cfg_misc_reserved1    = 29  /* [31:3] */
};

typedef struct NX5_DPM_IO_CFG_MISC_BIT_Ttag {
	unsigned int sel_rdy_pio  : BFW_NX5_dpm_io_cfg_misc_sel_rdy_pio;  /* Use DPM_RDY-pin as PIO pin. RDY is by default PIO to avoid RDY-conflicts during reset. */
	unsigned int sel_dirq_pio : BFW_NX5_dpm_io_cfg_misc_sel_dirq_pio; /* Use DPM_DIRQ-pin as PIO pin.                                                           */
	unsigned int sel_sirq_pio : BFW_NX5_dpm_io_cfg_misc_sel_sirq_pio; /* Use DPM_SIRQ-pin as PIO pin.                                                           */
	unsigned int reserved1    : BFW_NX5_dpm_io_cfg_misc_reserved1;    /* reserved                                                                               */
} NX5_DPM_IO_CFG_MISC_BIT_T;

typedef union {
	unsigned int              val;
	NX5_DPM_IO_CFG_MISC_BIT_T bf;
} NX5_DPM_IO_CFG_MISC_T;

/* --------------------------------------------------------------------- */
/* Register dpm_pio_out0 */
/* => DPM PIO output state configuration register 0. */
/*    All unused DPM signals can be used as PIOs. IOs will be driven to the programmed state if appropriate enable bit */
/*    is set in dpm_pio_oe0 register and IO is not used for DPM connection to host device. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_pio_out0  0x000000B0U
#define Adr_NX5_dpm_dpm_pio_out0  0x018BFFB0U
#define Adr_NX5_dpm_pio_out0      0x018BFFB0U
#define DFLT_VAL_NX5_dpm_pio_out0 0x00000000U

#define MSK_NX5_dpm_pio_out0_dpm_a         0x000fffffU
#define SRT_NX5_dpm_pio_out0_dpm_a         0
#define DFLT_VAL_NX5_dpm_pio_out0_dpm_a    0x00000000U
#define MSK_NX5_dpm_pio_out0_dpm_d_lo      0xfff00000U
#define SRT_NX5_dpm_pio_out0_dpm_d_lo      20
#define DFLT_VAL_NX5_dpm_pio_out0_dpm_d_lo 0x00000000U

enum {
	BFW_NX5_dpm_pio_out0_dpm_a    = 20, /* [19:0] */
	BFW_NX5_dpm_pio_out0_dpm_d_lo = 12  /* [31:20] */
};

typedef struct NX5_DPM_PIO_OUT0_BIT_Ttag {
	unsigned int dpm_a    : BFW_NX5_dpm_pio_out0_dpm_a;    /* PIO output state of DPM_A0..19 signals. */
	unsigned int dpm_d_lo : BFW_NX5_dpm_pio_out0_dpm_d_lo; /* PIO output state of DPM_D0..11 signals. */
} NX5_DPM_PIO_OUT0_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_PIO_OUT0_BIT_T bf;
} NX5_DPM_PIO_OUT0_T;

/* --------------------------------------------------------------------- */
/* Register dpm_pio_out1 */
/* => DPM PIO output state configuration register 1. */
/*    All unused DPM signals can be used as PIOs. IOs will be driven to the programmed state if appropriate enable bit */
/*    is set in dpm_pio_oe1 register and IO is not used for DPM connection to host device. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_pio_out1  0x000000B4U
#define Adr_NX5_dpm_dpm_pio_out1  0x018BFFB4U
#define Adr_NX5_dpm_pio_out1      0x018BFFB4U
#define DFLT_VAL_NX5_dpm_pio_out1 0x00000000U

#define MSK_NX5_dpm_pio_out1_dpm_d_hi      0x000fffffU
#define SRT_NX5_dpm_pio_out1_dpm_d_hi      0
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_d_hi 0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_dqmn      0x00300000U
#define SRT_NX5_dpm_pio_out1_dpm_dqmn      20
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_dqmn 0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_rdn       0x00400000U
#define SRT_NX5_dpm_pio_out1_dpm_rdn       22
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_rdn  0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_wrn       0x00800000U
#define SRT_NX5_dpm_pio_out1_dpm_wrn       23
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_wrn  0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_csn       0x01000000U
#define SRT_NX5_dpm_pio_out1_dpm_csn       24
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_csn  0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_rdy       0x02000000U
#define SRT_NX5_dpm_pio_out1_dpm_rdy       25
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_rdy  0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_dirq      0x04000000U
#define SRT_NX5_dpm_pio_out1_dpm_dirq      26
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_dirq 0x00000000U
#define MSK_NX5_dpm_pio_out1_dpm_sirq      0x08000000U
#define SRT_NX5_dpm_pio_out1_dpm_sirq      27
#define DFLT_VAL_NX5_dpm_pio_out1_dpm_sirq 0x00000000U

enum {
	BFW_NX5_dpm_pio_out1_dpm_d_hi  = 20, /* [19:0] */
	BFW_NX5_dpm_pio_out1_dpm_dqmn  = 2,  /* [21:20] */
	BFW_NX5_dpm_pio_out1_dpm_rdn   = 1,  /* [22] */
	BFW_NX5_dpm_pio_out1_dpm_wrn   = 1,  /* [23] */
	BFW_NX5_dpm_pio_out1_dpm_csn   = 1,  /* [24] */
	BFW_NX5_dpm_pio_out1_dpm_rdy   = 1,  /* [25] */
	BFW_NX5_dpm_pio_out1_dpm_dirq  = 1,  /* [26] */
	BFW_NX5_dpm_pio_out1_dpm_sirq  = 1,  /* [27] */
	BFW_NX5_dpm_pio_out1_reserved1 = 4   /* [31:28] */
};

typedef struct NX5_DPM_PIO_OUT1_BIT_Ttag {
	unsigned int dpm_d_hi  : BFW_NX5_dpm_pio_out1_dpm_d_hi;  /* PIO output state of DPM_D12..31 signals.   */
	unsigned int dpm_dqmn  : BFW_NX5_dpm_pio_out1_dpm_dqmn;  /* PIO output state of DPM_DQM0N..1N signals. */
	unsigned int dpm_rdn   : BFW_NX5_dpm_pio_out1_dpm_rdn;   /* PIO output state of DPM_RDN signal.        */
	unsigned int dpm_wrn   : BFW_NX5_dpm_pio_out1_dpm_wrn;   /* PIO output state of DPM_WRN signal.        */
	unsigned int dpm_csn   : BFW_NX5_dpm_pio_out1_dpm_csn;   /* PIO output state of DPM_CSN signal.        */
	unsigned int dpm_rdy   : BFW_NX5_dpm_pio_out1_dpm_rdy;   /* PIO output state of DPM_RDY signal.        */
	unsigned int dpm_dirq  : BFW_NX5_dpm_pio_out1_dpm_dirq;  /* PIO output state of DPM_DIRQ signal.       */
	unsigned int dpm_sirq  : BFW_NX5_dpm_pio_out1_dpm_sirq;  /* PIO output state of DPM_SIRQ signal.       */
	unsigned int reserved1 : BFW_NX5_dpm_pio_out1_reserved1; /* reserved                                   */
} NX5_DPM_PIO_OUT1_BIT_T;

typedef union {
	unsigned int           val;
	NX5_DPM_PIO_OUT1_BIT_T bf;
} NX5_DPM_PIO_OUT1_T;

/* --------------------------------------------------------------------- */
/* Register dpm_pio_oe0 */
/* => DPM PIO output enable configuration register 0. */
/*    All unused DPM signals can be used as PIOs. IOs will be driven to the output state */
/*    programmed in in dpm_pio_out0 register if the appropriate bit is set here and the IO is not used for DPM connection to host device. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_pio_oe0  0x000000B8U
#define Adr_NX5_dpm_dpm_pio_oe0  0x018BFFB8U
#define Adr_NX5_dpm_pio_oe0      0x018BFFB8U
#define DFLT_VAL_NX5_dpm_pio_oe0 0x00000000U

#define MSK_NX5_dpm_pio_oe0_dpm_a         0x000fffffU
#define SRT_NX5_dpm_pio_oe0_dpm_a         0
#define DFLT_VAL_NX5_dpm_pio_oe0_dpm_a    0x00000000U
#define MSK_NX5_dpm_pio_oe0_dpm_d_lo      0xfff00000U
#define SRT_NX5_dpm_pio_oe0_dpm_d_lo      20
#define DFLT_VAL_NX5_dpm_pio_oe0_dpm_d_lo 0x00000000U

enum {
	BFW_NX5_dpm_pio_oe0_dpm_a    = 20, /* [19:0] */
	BFW_NX5_dpm_pio_oe0_dpm_d_lo = 12  /* [31:20] */
};

typedef struct NX5_DPM_PIO_OE0_BIT_Ttag {
	unsigned int dpm_a    : BFW_NX5_dpm_pio_oe0_dpm_a;    /* PIO output enable of DPM_A0..19 signals. */
	unsigned int dpm_d_lo : BFW_NX5_dpm_pio_oe0_dpm_d_lo; /* PIO output enable of DPM_D0..11 signals. */
} NX5_DPM_PIO_OE0_BIT_T;

typedef union {
	unsigned int          val;
	NX5_DPM_PIO_OE0_BIT_T bf;
} NX5_DPM_PIO_OE0_T;

/* --------------------------------------------------------------------- */
/* Register dpm_pio_oe1 */
/* => DPM PIO output enable configuration register 1. */
/*    All unused DPM signals can be used as PIOs. IOs will be driven to the output state */
/*    programmed in in dpm_pio_out1 register if the appropriate bit is set here and the IO is not used for DPM connection to host device. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_pio_oe1  0x000000BCU
#define Adr_NX5_dpm_dpm_pio_oe1  0x018BFFBCU
#define Adr_NX5_dpm_pio_oe1      0x018BFFBCU
#define DFLT_VAL_NX5_dpm_pio_oe1 0x00000000U

#define MSK_NX5_dpm_pio_oe1_dpm_d_hi      0x000fffffU
#define SRT_NX5_dpm_pio_oe1_dpm_d_hi      0
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_d_hi 0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_dqmn      0x00300000U
#define SRT_NX5_dpm_pio_oe1_dpm_dqmn      20
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_dqmn 0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_rdn       0x00400000U
#define SRT_NX5_dpm_pio_oe1_dpm_rdn       22
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_rdn  0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_wrn       0x00800000U
#define SRT_NX5_dpm_pio_oe1_dpm_wrn       23
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_wrn  0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_csn       0x01000000U
#define SRT_NX5_dpm_pio_oe1_dpm_csn       24
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_csn  0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_rdy       0x02000000U
#define SRT_NX5_dpm_pio_oe1_dpm_rdy       25
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_rdy  0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_dirq      0x04000000U
#define SRT_NX5_dpm_pio_oe1_dpm_dirq      26
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_dirq 0x00000000U
#define MSK_NX5_dpm_pio_oe1_dpm_sirq      0x08000000U
#define SRT_NX5_dpm_pio_oe1_dpm_sirq      27
#define DFLT_VAL_NX5_dpm_pio_oe1_dpm_sirq 0x00000000U

enum {
	BFW_NX5_dpm_pio_oe1_dpm_d_hi  = 20, /* [19:0] */
	BFW_NX5_dpm_pio_oe1_dpm_dqmn  = 2,  /* [21:20] */
	BFW_NX5_dpm_pio_oe1_dpm_rdn   = 1,  /* [22] */
	BFW_NX5_dpm_pio_oe1_dpm_wrn   = 1,  /* [23] */
	BFW_NX5_dpm_pio_oe1_dpm_csn   = 1,  /* [24] */
	BFW_NX5_dpm_pio_oe1_dpm_rdy   = 1,  /* [25] */
	BFW_NX5_dpm_pio_oe1_dpm_dirq  = 1,  /* [26] */
	BFW_NX5_dpm_pio_oe1_dpm_sirq  = 1,  /* [27] */
	BFW_NX5_dpm_pio_oe1_reserved1 = 4   /* [31:28] */
};

typedef struct NX5_DPM_PIO_OE1_BIT_Ttag {
	unsigned int dpm_d_hi  : BFW_NX5_dpm_pio_oe1_dpm_d_hi;  /* PIO output enable of DPM_D12..31 signals.   */
	unsigned int dpm_dqmn  : BFW_NX5_dpm_pio_oe1_dpm_dqmn;  /* PIO output enable of DPM_DQM0N..1N signals. */
	unsigned int dpm_rdn   : BFW_NX5_dpm_pio_oe1_dpm_rdn;   /* PIO output enable of DPM_RDN signal.        */
	unsigned int dpm_wrn   : BFW_NX5_dpm_pio_oe1_dpm_wrn;   /* PIO output enable of DPM_WRN signal.        */
	unsigned int dpm_csn   : BFW_NX5_dpm_pio_oe1_dpm_csn;   /* PIO output enable of DPM_CSN signal.        */
	unsigned int dpm_rdy   : BFW_NX5_dpm_pio_oe1_dpm_rdy;   /* PIO output enable of DPM_RDY signal.        */
	unsigned int dpm_dirq  : BFW_NX5_dpm_pio_oe1_dpm_dirq;  /* PIO output enable of DPM_DIRQ signal.       */
	unsigned int dpm_sirq  : BFW_NX5_dpm_pio_oe1_dpm_sirq;  /* PIO output enable of DPM_SIRQ signal.       */
	unsigned int reserved1 : BFW_NX5_dpm_pio_oe1_reserved1; /* reserved                                    */
} NX5_DPM_PIO_OE1_BIT_T;

typedef union {
	unsigned int          val;
	NX5_DPM_PIO_OE1_BIT_T bf;
} NX5_DPM_PIO_OE1_T;

/* --------------------------------------------------------------------- */
/* Register dpm_pio_in0 */
/* => DPM PIO input state register 0. */
/*    IO input states can be read here regardless whether IO is used as PIO or as DPM connection. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_pio_in0 0x000000C0U
#define Adr_NX5_dpm_dpm_pio_in0 0x018BFFC0U
#define Adr_NX5_dpm_pio_in0     0x018BFFC0U

#define MSK_NX5_dpm_pio_in0_dpm_a    0x000fffffU
#define SRT_NX5_dpm_pio_in0_dpm_a    0
#define MSK_NX5_dpm_pio_in0_dpm_d_lo 0xfff00000U
#define SRT_NX5_dpm_pio_in0_dpm_d_lo 20

enum {
	BFW_NX5_dpm_pio_in0_dpm_a    = 20, /* [19:0] */
	BFW_NX5_dpm_pio_in0_dpm_d_lo = 12  /* [31:20] */
};

typedef struct NX5_DPM_PIO_IN0_BIT_Ttag {
	unsigned int dpm_a    : BFW_NX5_dpm_pio_in0_dpm_a;    /* Input state of DPM_A0..19 signals. */
	unsigned int dpm_d_lo : BFW_NX5_dpm_pio_in0_dpm_d_lo; /* Input state of DPM_D0..11 signals. */
} NX5_DPM_PIO_IN0_BIT_T;

typedef union {
	unsigned int          val;
	NX5_DPM_PIO_IN0_BIT_T bf;
} NX5_DPM_PIO_IN0_T;

/* --------------------------------------------------------------------- */
/* Register dpm_pio_in1 */
/* => DPM PIO input state register 1. */
/*    IO input states can be read here regardless whether IO is used as PIO or as DPM connection. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_pio_in1 0x000000C4U
#define Adr_NX5_dpm_dpm_pio_in1 0x018BFFC4U
#define Adr_NX5_dpm_pio_in1     0x018BFFC4U

#define MSK_NX5_dpm_pio_in1_dpm_d_hi 0x000fffffU
#define SRT_NX5_dpm_pio_in1_dpm_d_hi 0
#define MSK_NX5_dpm_pio_in1_dpm_dqmn 0x00300000U
#define SRT_NX5_dpm_pio_in1_dpm_dqmn 20
#define MSK_NX5_dpm_pio_in1_dpm_rdn  0x00400000U
#define SRT_NX5_dpm_pio_in1_dpm_rdn  22
#define MSK_NX5_dpm_pio_in1_dpm_wrn  0x00800000U
#define SRT_NX5_dpm_pio_in1_dpm_wrn  23
#define MSK_NX5_dpm_pio_in1_dpm_csn  0x01000000U
#define SRT_NX5_dpm_pio_in1_dpm_csn  24
#define MSK_NX5_dpm_pio_in1_dpm_rdy  0x02000000U
#define SRT_NX5_dpm_pio_in1_dpm_rdy  25
#define MSK_NX5_dpm_pio_in1_dpm_dirq 0x04000000U
#define SRT_NX5_dpm_pio_in1_dpm_dirq 26
#define MSK_NX5_dpm_pio_in1_dpm_sirq 0x08000000U
#define SRT_NX5_dpm_pio_in1_dpm_sirq 27

enum {
	BFW_NX5_dpm_pio_in1_dpm_d_hi  = 20, /* [19:0] */
	BFW_NX5_dpm_pio_in1_dpm_dqmn  = 2,  /* [21:20] */
	BFW_NX5_dpm_pio_in1_dpm_rdn   = 1,  /* [22] */
	BFW_NX5_dpm_pio_in1_dpm_wrn   = 1,  /* [23] */
	BFW_NX5_dpm_pio_in1_dpm_csn   = 1,  /* [24] */
	BFW_NX5_dpm_pio_in1_dpm_rdy   = 1,  /* [25] */
	BFW_NX5_dpm_pio_in1_dpm_dirq  = 1,  /* [26] */
	BFW_NX5_dpm_pio_in1_dpm_sirq  = 1,  /* [27] */
	BFW_NX5_dpm_pio_in1_reserved1 = 4   /* [31:28] */
};

typedef struct NX5_DPM_PIO_IN1_BIT_Ttag {
	unsigned int dpm_d_hi  : BFW_NX5_dpm_pio_in1_dpm_d_hi;  /* Input state of DPM_D12..31 signals.   */
	unsigned int dpm_dqmn  : BFW_NX5_dpm_pio_in1_dpm_dqmn;  /* Input state of DPM_DQM0N..1N signals. */
	unsigned int dpm_rdn   : BFW_NX5_dpm_pio_in1_dpm_rdn;   /* Input state of DPM_RDN signal.        */
	unsigned int dpm_wrn   : BFW_NX5_dpm_pio_in1_dpm_wrn;   /* Input state of DPM_WRN signal.        */
	unsigned int dpm_csn   : BFW_NX5_dpm_pio_in1_dpm_csn;   /* Input state of DPM_CSN signal.        */
	unsigned int dpm_rdy   : BFW_NX5_dpm_pio_in1_dpm_rdy;   /* Input state of DPM_RDY signal.        */
	unsigned int dpm_dirq  : BFW_NX5_dpm_pio_in1_dpm_dirq;  /* Input state of DPM_DIRQ signal.       */
	unsigned int dpm_sirq  : BFW_NX5_dpm_pio_in1_dpm_sirq;  /* Input state of DPM_SIRQ signal.       */
	unsigned int reserved1 : BFW_NX5_dpm_pio_in1_reserved1; /* reserved                              */
} NX5_DPM_PIO_IN1_BIT_T;

typedef union {
	unsigned int          val;
	NX5_DPM_PIO_IN1_BIT_T bf;
} NX5_DPM_PIO_IN1_T;

/* --------------------------------------------------------------------- */
/* Register dpm_netx_version */
/* => netX version register. */
/*    This register is mirrored form asic_ctrl register area and can be set during netX booting phase. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dpm_netx_version 0x000000FCU
#define Adr_NX5_dpm_dpm_netx_version 0x018BFFFCU
#define Adr_NX5_dpm_netx_version     0x018BFFFCU

#define MSK_NX5_dpm_netx_version_netx_version 0xffffffffU
#define SRT_NX5_dpm_netx_version_netx_version 0

enum {
	BFW_NX5_dpm_netx_version_netx_version = 32  /* [31:0] */
};

typedef struct NX5_DPM_NETX_VERSION_BIT_Ttag {
	unsigned int netx_version : BFW_NX5_dpm_netx_version_netx_version; /* netX version.                                                             */
	                                                                   /* This register is not valid if unlocked bit is set in dpm_status register. */
} NX5_DPM_NETX_VERSION_BIT_T;

typedef union {
	unsigned int               val;
	NX5_DPM_NETX_VERSION_BIT_T bf;
} NX5_DPM_NETX_VERSION_T;


/* ===================================================================== */

/* Area of xc */

/* ===================================================================== */

#define Addr_NX5_xc      0x018C0000U
#define NX5_NETX_XC_AREA 0x018C0000U

/* --------------------------------------------------------------------- */
/* Register xc_base */
/* =>  */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xc_base 0x00000000U
#define Adr_NX5_xc_xc_base  0x018C0000U
#define Adr_NX5_xc_base     0x018C0000U


/* ===================================================================== */

/* AREA xpec */
/* Area of xpec0, xpec1 */

/* ===================================================================== */

#define Addr_NX5_xpec0    0x018C0000U
#define NX5_NETX_XP0_BASE 0x018C0000U
#define Addr_NX5_xpec1    0x018C8000U
#define NX5_NETX_XP1_BASE 0x018C8000U

/* --------------------------------------------------------------------- */
/* Register xpec_r0 */
/* => xPEC work register for indirect addressing */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r0   0x00000000U
#define Adr_NX5_xpec0_xpec_r0 0x018C0000U
#define Adr_NX5_xpec1_xpec_r0 0x018C8000U
#define DFLT_VAL_NX5_xpec_r0  0x00000000U

#define MSK_NX5_xpec_r0_r0      0xffffffffU
#define SRT_NX5_xpec_r0_r0      0
#define DFLT_VAL_NX5_xpec_r0_r0 0x00000000U

enum {
	BFW_NX5_xpec_r0_r0 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R0_BIT_Ttag {
	unsigned int r0 : BFW_NX5_xpec_r0_r0; /* Work Register 0 */
} NX5_XPEC_R0_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R0_BIT_T bf;
} NX5_XPEC_R0_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r1 */
/* => xPEC work register for indirect addressing */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r1   0x00000004U
#define Adr_NX5_xpec0_xpec_r1 0x018C0004U
#define Adr_NX5_xpec1_xpec_r1 0x018C8004U
#define DFLT_VAL_NX5_xpec_r1  0x00000000U

#define MSK_NX5_xpec_r1_r1      0xffffffffU
#define SRT_NX5_xpec_r1_r1      0
#define DFLT_VAL_NX5_xpec_r1_r1 0x00000000U

enum {
	BFW_NX5_xpec_r1_r1 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R1_BIT_Ttag {
	unsigned int r1 : BFW_NX5_xpec_r1_r1; /* Work Register 1 */
} NX5_XPEC_R1_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R1_BIT_T bf;
} NX5_XPEC_R1_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r2 */
/* => xPEC work register for indirect addressing */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r2   0x00000008U
#define Adr_NX5_xpec0_xpec_r2 0x018C0008U
#define Adr_NX5_xpec1_xpec_r2 0x018C8008U
#define DFLT_VAL_NX5_xpec_r2  0x00000000U

#define MSK_NX5_xpec_r2_r2      0xffffffffU
#define SRT_NX5_xpec_r2_r2      0
#define DFLT_VAL_NX5_xpec_r2_r2 0x00000000U

enum {
	BFW_NX5_xpec_r2_r2 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R2_BIT_Ttag {
	unsigned int r2 : BFW_NX5_xpec_r2_r2; /* Work Register 2 */
} NX5_XPEC_R2_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R2_BIT_T bf;
} NX5_XPEC_R2_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r3 */
/* => xPEC work register for indirect addressing */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r3   0x0000000CU
#define Adr_NX5_xpec0_xpec_r3 0x018C000CU
#define Adr_NX5_xpec1_xpec_r3 0x018C800CU
#define DFLT_VAL_NX5_xpec_r3  0x00000000U

#define MSK_NX5_xpec_r3_r3      0xffffffffU
#define SRT_NX5_xpec_r3_r3      0
#define DFLT_VAL_NX5_xpec_r3_r3 0x00000000U

enum {
	BFW_NX5_xpec_r3_r3 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R3_BIT_Ttag {
	unsigned int r3 : BFW_NX5_xpec_r3_r3; /* Work Register 3 */
} NX5_XPEC_R3_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R3_BIT_T bf;
} NX5_XPEC_R3_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r4 */
/* => xPEC work register for indirect addressing */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r4   0x00000010U
#define Adr_NX5_xpec0_xpec_r4 0x018C0010U
#define Adr_NX5_xpec1_xpec_r4 0x018C8010U
#define DFLT_VAL_NX5_xpec_r4  0x00000000U

#define MSK_NX5_xpec_r4_r4      0xffffffffU
#define SRT_NX5_xpec_r4_r4      0
#define DFLT_VAL_NX5_xpec_r4_r4 0x00000000U

enum {
	BFW_NX5_xpec_r4_r4 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R4_BIT_Ttag {
	unsigned int r4 : BFW_NX5_xpec_r4_r4; /* Work Register 4 */
} NX5_XPEC_R4_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R4_BIT_T bf;
} NX5_XPEC_R4_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r5 */
/* => xPEC work register for indirect addressing */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r5   0x00000014U
#define Adr_NX5_xpec0_xpec_r5 0x018C0014U
#define Adr_NX5_xpec1_xpec_r5 0x018C8014U
#define DFLT_VAL_NX5_xpec_r5  0x00000000U

#define MSK_NX5_xpec_r5_r5      0xffffffffU
#define SRT_NX5_xpec_r5_r5      0
#define DFLT_VAL_NX5_xpec_r5_r5 0x00000000U

enum {
	BFW_NX5_xpec_r5_r5 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R5_BIT_Ttag {
	unsigned int r5 : BFW_NX5_xpec_r5_r5; /* Work Register 5 */
} NX5_XPEC_R5_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R5_BIT_T bf;
} NX5_XPEC_R5_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r6 */
/* => xPEC work register for indirect addressing */
/*    Shared in xPEC fmmusm mode with fmmusm_read_addr_in (w mode). */
/*    Shared in xPEC fmmusm mode with sm_read_addr_out (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r6   0x00000018U
#define Adr_NX5_xpec0_xpec_r6 0x018C0018U
#define Adr_NX5_xpec1_xpec_r6 0x018C8018U
#define DFLT_VAL_NX5_xpec_r6  0x00000000U

#define MSK_NX5_xpec_r6_r6      0xffffffffU
#define SRT_NX5_xpec_r6_r6      0
#define DFLT_VAL_NX5_xpec_r6_r6 0x00000000U

enum {
	BFW_NX5_xpec_r6_r6 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R6_BIT_Ttag {
	unsigned int r6 : BFW_NX5_xpec_r6_r6; /* Work Register 6 */
} NX5_XPEC_R6_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R6_BIT_T bf;
} NX5_XPEC_R6_T;

/* --------------------------------------------------------------------- */
/* Register xpec_r7 */
/* => xPEC work register for indirect addressing */
/*    Shared in xPEC fmmusm mode with fmmusm_write_addr_in (w mode). */
/*    Shared in xPEC fmmusm mode with sm_write_addr_out (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_r7   0x0000001CU
#define Adr_NX5_xpec0_xpec_r7 0x018C001CU
#define Adr_NX5_xpec1_xpec_r7 0x018C801CU
#define DFLT_VAL_NX5_xpec_r7  0x00000000U

#define MSK_NX5_xpec_r7_r7      0xffffffffU
#define SRT_NX5_xpec_r7_r7      0
#define DFLT_VAL_NX5_xpec_r7_r7 0x00000000U

enum {
	BFW_NX5_xpec_r7_r7 = 32  /* [31:0] */
};

typedef struct NX5_XPEC_R7_BIT_Ttag {
	unsigned int r7 : BFW_NX5_xpec_r7_r7; /* Work Register 7 */
} NX5_XPEC_R7_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_R7_BIT_T bf;
} NX5_XPEC_R7_T;

/* --------------------------------------------------------------------- */
/* Register usr0 */
/* => xPEC user Register additional work register */
/*    Bitws 31 downto 28 are connected to the Event controller */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_usr0   0x00000020U
#define Adr_NX5_xpec0_usr0 0x018C0020U
#define Adr_NX5_xpec1_usr0 0x018C8020U
#define DFLT_VAL_NX5_usr0  0x00000000U

#define MSK_NX5_usr0_usr0      0xffffffffU
#define SRT_NX5_usr0_usr0      0
#define DFLT_VAL_NX5_usr0_usr0 0x00000000U

enum {
	BFW_NX5_usr0_usr0 = 32  /* [31:0] */
};

typedef struct NX5_USR0_BIT_Ttag {
	unsigned int usr0 : BFW_NX5_usr0_usr0; /* User Register 0 */
} NX5_USR0_BIT_T;

typedef union {
	unsigned int   val;
	NX5_USR0_BIT_T bf;
} NX5_USR0_T;

/* --------------------------------------------------------------------- */
/* Register usr1 */
/* => xPEC user Register additional work register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_usr1   0x00000024U
#define Adr_NX5_xpec0_usr1 0x018C0024U
#define Adr_NX5_xpec1_usr1 0x018C8024U
#define DFLT_VAL_NX5_usr1  0x00000000U

#define MSK_NX5_usr1_usr1      0xffffffffU
#define SRT_NX5_usr1_usr1      0
#define DFLT_VAL_NX5_usr1_usr1 0x00000000U

enum {
	BFW_NX5_usr1_usr1 = 32  /* [31:0] */
};

typedef struct NX5_USR1_BIT_Ttag {
	unsigned int usr1 : BFW_NX5_usr1_usr1; /* User Register 1 */
} NX5_USR1_BIT_T;

typedef union {
	unsigned int   val;
	NX5_USR1_BIT_T bf;
} NX5_USR1_T;

/* --------------------------------------------------------------------- */
/* Register range45 */
/* => xPEC Overflow Underflow register to limit stack and fifo buffer. */
/*    Generates range bits inside xPEC status register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_range45   0x00000028U
#define Adr_NX5_xpec0_range45 0x018C0028U
#define Adr_NX5_xpec1_range45 0x018C8028U
#define DFLT_VAL_NX5_range45  0x00000000U

#define MSK_NX5_range45_range4       0x00001fffU
#define SRT_NX5_range45_range4       0
#define DFLT_VAL_NX5_range45_range4  0x00000000U
#define MSK_NX5_range45_bigger4      0x00002000U
#define SRT_NX5_range45_bigger4      13
#define DFLT_VAL_NX5_range45_bigger4 0x00000000U
#define MSK_NX5_range45_range5       0x1fff0000U
#define SRT_NX5_range45_range5       16
#define DFLT_VAL_NX5_range45_range5  0x00000000U
#define MSK_NX5_range45_bigger5      0x20000000U
#define SRT_NX5_range45_bigger5      29
#define DFLT_VAL_NX5_range45_bigger5 0x00000000U

enum {
	BFW_NX5_range45_range4    = 13, /* [12:0] */
	BFW_NX5_range45_bigger4   = 1,  /* [13] */
	BFW_NX5_range45_reserved1 = 2,  /* [15:14] */
	BFW_NX5_range45_range5    = 13, /* [28:16] */
	BFW_NX5_range45_bigger5   = 1,  /* [29] */
	BFW_NX5_range45_reserved2 = 2   /* [31:30] */
};

typedef struct NX5_RANGE45_BIT_Ttag {
	unsigned int range4    : BFW_NX5_range45_range4;    /* border for xpec_r4                                                                          */
	unsigned int bigger4   : BFW_NX5_range45_bigger4;   /* 0: generate range status bit, if r4 < range4; 1: generate range status bit, if r4 >= range4 */
	unsigned int reserved1 : BFW_NX5_range45_reserved1; /* reserved                                                                                    */
	unsigned int range5    : BFW_NX5_range45_range5;    /* border for xpec_r5                                                                          */
	unsigned int bigger5   : BFW_NX5_range45_bigger5;   /* 0: generate range status bit, if r5 < range5; 1: generate range status bit, if r5 >= range5 */
	unsigned int reserved2 : BFW_NX5_range45_reserved2; /* reserved                                                                                    */
} NX5_RANGE45_BIT_T;

typedef union {
	unsigned int      val;
	NX5_RANGE45_BIT_T bf;
} NX5_RANGE45_T;

/* --------------------------------------------------------------------- */
/* Register range67 */
/* => xPEC Overflow Underflow register to limit stack and fifo buffer. */
/*    Generates range bits inside xPEC status register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_range67   0x0000002CU
#define Adr_NX5_xpec0_range67 0x018C002CU
#define Adr_NX5_xpec1_range67 0x018C802CU
#define DFLT_VAL_NX5_range67  0x00000000U

#define MSK_NX5_range67_range6       0x00001fffU
#define SRT_NX5_range67_range6       0
#define DFLT_VAL_NX5_range67_range6  0x00000000U
#define MSK_NX5_range67_bigger6      0x00002000U
#define SRT_NX5_range67_bigger6      13
#define DFLT_VAL_NX5_range67_bigger6 0x00000000U
#define MSK_NX5_range67_range7       0x1fff0000U
#define SRT_NX5_range67_range7       16
#define DFLT_VAL_NX5_range67_range7  0x00000000U
#define MSK_NX5_range67_bigger7      0x20000000U
#define SRT_NX5_range67_bigger7      29
#define DFLT_VAL_NX5_range67_bigger7 0x00000000U

enum {
	BFW_NX5_range67_range6    = 13, /* [12:0] */
	BFW_NX5_range67_bigger6   = 1,  /* [13] */
	BFW_NX5_range67_reserved1 = 2,  /* [15:14] */
	BFW_NX5_range67_range7    = 13, /* [28:16] */
	BFW_NX5_range67_bigger7   = 1,  /* [29] */
	BFW_NX5_range67_reserved2 = 2   /* [31:30] */
};

typedef struct NX5_RANGE67_BIT_Ttag {
	unsigned int range6    : BFW_NX5_range67_range6;    /* border for xpec_r6                                                                          */
	unsigned int bigger6   : BFW_NX5_range67_bigger6;   /* 0: generate range status bit, if r6 < range6; 1: generate range status bit, if r6 >= range6 */
	unsigned int reserved1 : BFW_NX5_range67_reserved1; /* reserved                                                                                    */
	unsigned int range7    : BFW_NX5_range67_range7;    /* border for xpec_r7                                                                          */
	unsigned int bigger7   : BFW_NX5_range67_bigger7;   /* 0: generate range status bit, if r7 < range7; 1: generate range status bit, if r7 >= range7 */
	unsigned int reserved2 : BFW_NX5_range67_reserved2; /* reserved                                                                                    */
} NX5_RANGE67_BIT_T;

typedef union {
	unsigned int      val;
	NX5_RANGE67_BIT_T bf;
} NX5_RANGE67_T;

/* --------------------------------------------------------------------- */
/* Register timer0 */
/* => xPEC Timer 0 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_timer0   0x00000030U
#define Adr_NX5_xpec0_timer0 0x018C0030U
#define Adr_NX5_xpec1_timer0 0x018C8030U
#define DFLT_VAL_NX5_timer0  0x00000000U

#define MSK_NX5_timer0_preload0      0xffffffffU
#define SRT_NX5_timer0_preload0      0
#define DFLT_VAL_NX5_timer0_preload0 0x00000000U

enum {
	BFW_NX5_timer0_preload0 = 32  /* [31:0] */
};

typedef struct NX5_TIMER0_BIT_Ttag {
	unsigned int preload0 : BFW_NX5_timer0_preload0; /* read: actual value of timer, write: timer and preload value */
} NX5_TIMER0_BIT_T;

typedef union {
	unsigned int     val;
	NX5_TIMER0_BIT_T bf;
} NX5_TIMER0_T;

/* --------------------------------------------------------------------- */
/* Register timer1 */
/* => xPEC Timer 1 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_timer1   0x00000034U
#define Adr_NX5_xpec0_timer1 0x018C0034U
#define Adr_NX5_xpec1_timer1 0x018C8034U
#define DFLT_VAL_NX5_timer1  0x00000000U

#define MSK_NX5_timer1_preload1      0xffffffffU
#define SRT_NX5_timer1_preload1      0
#define DFLT_VAL_NX5_timer1_preload1 0x00000000U

enum {
	BFW_NX5_timer1_preload1 = 32  /* [31:0] */
};

typedef struct NX5_TIMER1_BIT_Ttag {
	unsigned int preload1 : BFW_NX5_timer1_preload1; /* read: actual value of timer, write: timer and preload value */
} NX5_TIMER1_BIT_T;

typedef union {
	unsigned int     val;
	NX5_TIMER1_BIT_T bf;
} NX5_TIMER1_T;

/* --------------------------------------------------------------------- */
/* Register timer2 */
/* => xPEC Timer 2 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_timer2   0x00000038U
#define Adr_NX5_xpec0_timer2 0x018C0038U
#define Adr_NX5_xpec1_timer2 0x018C8038U
#define DFLT_VAL_NX5_timer2  0x00000000U

#define MSK_NX5_timer2_preload2      0xffffffffU
#define SRT_NX5_timer2_preload2      0
#define DFLT_VAL_NX5_timer2_preload2 0x00000000U

enum {
	BFW_NX5_timer2_preload2 = 32  /* [31:0] */
};

typedef struct NX5_TIMER2_BIT_Ttag {
	unsigned int preload2 : BFW_NX5_timer2_preload2; /* read: actual value of timer, write: timer and preload value */
} NX5_TIMER2_BIT_T;

typedef union {
	unsigned int     val;
	NX5_TIMER2_BIT_T bf;
} NX5_TIMER2_T;

/* --------------------------------------------------------------------- */
/* Register timer3 */
/* => xPEC Timer 3 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_timer3   0x0000003CU
#define Adr_NX5_xpec0_timer3 0x018C003CU
#define Adr_NX5_xpec1_timer3 0x018C803CU
#define DFLT_VAL_NX5_timer3  0x00000000U

#define MSK_NX5_timer3_preload3      0xffffffffU
#define SRT_NX5_timer3_preload3      0
#define DFLT_VAL_NX5_timer3_preload3 0x00000000U

enum {
	BFW_NX5_timer3_preload3 = 32  /* [31:0] */
};

typedef struct NX5_TIMER3_BIT_Ttag {
	unsigned int preload3 : BFW_NX5_timer3_preload3; /* read: actual value of timer, write: timer and preload value */
} NX5_TIMER3_BIT_T;

typedef union {
	unsigned int     val;
	NX5_TIMER3_BIT_T bf;
} NX5_TIMER3_T;

/* --------------------------------------------------------------------- */
/* Register urx_count */
/* => xPEC urx counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_urx_count   0x00000040U
#define Adr_NX5_xpec0_urx_count 0x018C0040U
#define Adr_NX5_xpec1_urx_count 0x018C8040U
#define DFLT_VAL_NX5_urx_count  0x00000000U

#define MSK_NX5_urx_count_urx_count      0xffffffffU
#define SRT_NX5_urx_count_urx_count      0
#define DFLT_VAL_NX5_urx_count_urx_count 0x00000000U

enum {
	BFW_NX5_urx_count_urx_count = 32  /* [31:0] */
};

typedef struct NX5_URX_COUNT_BIT_Ttag {
	unsigned int urx_count : BFW_NX5_urx_count_urx_count; /* counts up received bytes (accesses of xPEC to any URX FIFO) */
} NX5_URX_COUNT_BIT_T;

typedef union {
	unsigned int        val;
	NX5_URX_COUNT_BIT_T bf;
} NX5_URX_COUNT_T;

/* --------------------------------------------------------------------- */
/* Register utx_count */
/* => xPEC utx counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_utx_count   0x00000044U
#define Adr_NX5_xpec0_utx_count 0x018C0044U
#define Adr_NX5_xpec1_utx_count 0x018C8044U
#define DFLT_VAL_NX5_utx_count  0x00000000U

#define MSK_NX5_utx_count_utx_count      0xffffffffU
#define SRT_NX5_utx_count_utx_count      0
#define DFLT_VAL_NX5_utx_count_utx_count 0x00000000U

enum {
	BFW_NX5_utx_count_utx_count = 32  /* [31:0] */
};

typedef struct NX5_UTX_COUNT_BIT_Ttag {
	unsigned int utx_count : BFW_NX5_utx_count_utx_count; /* counts up transmitted bytes (accesses of xPEC to any UTX FIFO) */
} NX5_UTX_COUNT_BIT_T;

typedef union {
	unsigned int        val;
	NX5_UTX_COUNT_BIT_T bf;
} NX5_UTX_COUNT_T;

/* --------------------------------------------------------------------- */
/* Register xpec_pc */
/* => xPEC Program Counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_pc   0x00000048U
#define Adr_NX5_xpec0_xpec_pc 0x018C0048U
#define Adr_NX5_xpec1_xpec_pc 0x018C8048U
#define DFLT_VAL_NX5_xpec_pc  0x000007ffU

#define MSK_NX5_xpec_pc_pc      0x000007ffU
#define SRT_NX5_xpec_pc_pc      0
#define DFLT_VAL_NX5_xpec_pc_pc 0x000007ffU

enum {
	BFW_NX5_xpec_pc_pc        = 11, /* [10:0] */
	BFW_NX5_xpec_pc_reserved1 = 21  /* [31:11] */
};

typedef struct NX5_XPEC_PC_BIT_Ttag {
	unsigned int pc        : BFW_NX5_xpec_pc_pc;        /* Program Counter (dword address inside DPRAM) */
	unsigned int reserved1 : BFW_NX5_xpec_pc_reserved1; /* reserved                                     */
} NX5_XPEC_PC_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XPEC_PC_BIT_T bf;
} NX5_XPEC_PC_T;

/* --------------------------------------------------------------------- */
/* Register zero */
/* => Zero Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_zero   0x0000004CU
#define Adr_NX5_xpec0_zero 0x018C004CU
#define Adr_NX5_xpec1_zero 0x018C804CU
#define DFLT_VAL_NX5_zero  0x00000000U

#define MSK_NX5_zero_zero      0xffffffffU
#define SRT_NX5_zero_zero      0
#define DFLT_VAL_NX5_zero_zero 0x00000000U

enum {
	BFW_NX5_zero_zero = 32  /* [31:0] */
};

typedef struct NX5_ZERO_BIT_Ttag {
	unsigned int zero : BFW_NX5_zero_zero; /* Always Zero */
} NX5_ZERO_BIT_T;

typedef union {
	unsigned int   val;
	NX5_ZERO_BIT_T bf;
} NX5_ZERO_T;

/* --------------------------------------------------------------------- */
/* Register xpec_statcfg */
/* => xPEC Config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_statcfg   0x00000050U
#define Adr_NX5_xpec0_xpec_statcfg 0x018C0050U
#define Adr_NX5_xpec1_xpec_statcfg 0x018C8050U
#define DFLT_VAL_NX5_xpec_statcfg  0x00000000U

#define MSK_NX5_xpec_statcfg_timer0                  0x00000003U
#define SRT_NX5_xpec_statcfg_timer0                  0
#define DFLT_VAL_NX5_xpec_statcfg_timer0             0x00000000U
#define MSK_NX5_xpec_statcfg_timer1                  0x0000000cU
#define SRT_NX5_xpec_statcfg_timer1                  2
#define DFLT_VAL_NX5_xpec_statcfg_timer1             0x00000000U
#define MSK_NX5_xpec_statcfg_timer2                  0x00000030U
#define SRT_NX5_xpec_statcfg_timer2                  4
#define DFLT_VAL_NX5_xpec_statcfg_timer2             0x00000000U
#define MSK_NX5_xpec_statcfg_timer3                  0x000000c0U
#define SRT_NX5_xpec_statcfg_timer3                  6
#define DFLT_VAL_NX5_xpec_statcfg_timer3             0x00000000U
#define MSK_NX5_xpec_statcfg_timer4                  0x00000300U
#define SRT_NX5_xpec_statcfg_timer4                  8
#define DFLT_VAL_NX5_xpec_statcfg_timer4             0x00000000U
#define MSK_NX5_xpec_statcfg_timer5                  0x00000c00U
#define SRT_NX5_xpec_statcfg_timer5                  10
#define DFLT_VAL_NX5_xpec_statcfg_timer5             0x00000000U
#define MSK_NX5_xpec_statcfg_reset_req               0x00001000U
#define SRT_NX5_xpec_statcfg_reset_req               12
#define DFLT_VAL_NX5_xpec_statcfg_reset_req          0x00000000U
#define MSK_NX5_xpec_statcfg_reset_dis               0x00002000U
#define SRT_NX5_xpec_statcfg_reset_dis               13
#define DFLT_VAL_NX5_xpec_statcfg_reset_dis          0x00000000U
#define MSK_NX5_xpec_statcfg_debug_mode              0x00004000U
#define SRT_NX5_xpec_statcfg_debug_mode              14
#define DFLT_VAL_NX5_xpec_statcfg_debug_mode         0x00000000U
#define MSK_NX5_xpec_statcfg_register_mode           0x00030000U
#define SRT_NX5_xpec_statcfg_register_mode           16
#define DFLT_VAL_NX5_xpec_statcfg_register_mode      0x00000000U
#define MSK_NX5_xpec_statcfg_wr4_range_sel           0x000c0000U
#define SRT_NX5_xpec_statcfg_wr4_range_sel           18
#define DFLT_VAL_NX5_xpec_statcfg_wr4_range_sel      0x00000000U
#define MSK_NX5_xpec_statcfg_wr5_range_sel           0x00300000U
#define SRT_NX5_xpec_statcfg_wr5_range_sel           20
#define DFLT_VAL_NX5_xpec_statcfg_wr5_range_sel      0x00000000U
#define MSK_NX5_xpec_statcfg_wr6_range_sel           0x00c00000U
#define SRT_NX5_xpec_statcfg_wr6_range_sel           22
#define DFLT_VAL_NX5_xpec_statcfg_wr6_range_sel      0x00000000U
#define MSK_NX5_xpec_statcfg_wr7_range_sel           0x03000000U
#define SRT_NX5_xpec_statcfg_wr7_range_sel           24
#define DFLT_VAL_NX5_xpec_statcfg_wr7_range_sel      0x00000000U
#define MSK_NX5_xpec_statcfg_run_dma_controller      0x80000000U
#define SRT_NX5_xpec_statcfg_run_dma_controller      31
#define DFLT_VAL_NX5_xpec_statcfg_run_dma_controller 0x00000000U

enum {
	BFW_NX5_xpec_statcfg_timer0             = 2, /* [1:0] */
	BFW_NX5_xpec_statcfg_timer1             = 2, /* [3:2] */
	BFW_NX5_xpec_statcfg_timer2             = 2, /* [5:4] */
	BFW_NX5_xpec_statcfg_timer3             = 2, /* [7:6] */
	BFW_NX5_xpec_statcfg_timer4             = 2, /* [9:8] */
	BFW_NX5_xpec_statcfg_timer5             = 2, /* [11:10] */
	BFW_NX5_xpec_statcfg_reset_req          = 1, /* [12] */
	BFW_NX5_xpec_statcfg_reset_dis          = 1, /* [13] */
	BFW_NX5_xpec_statcfg_debug_mode         = 1, /* [14] */
	BFW_NX5_xpec_statcfg_reserved1          = 1, /* [15] */
	BFW_NX5_xpec_statcfg_register_mode      = 2, /* [17:16] */
	BFW_NX5_xpec_statcfg_wr4_range_sel      = 2, /* [19:18] */
	BFW_NX5_xpec_statcfg_wr5_range_sel      = 2, /* [21:20] */
	BFW_NX5_xpec_statcfg_wr6_range_sel      = 2, /* [23:22] */
	BFW_NX5_xpec_statcfg_wr7_range_sel      = 2, /* [25:24] */
	BFW_NX5_xpec_statcfg_reserved2          = 5, /* [30:26] */
	BFW_NX5_xpec_statcfg_run_dma_controller = 1  /* [31] */
};

typedef struct NX5_XPEC_STATCFG_BIT_Ttag {
	unsigned int timer0             : BFW_NX5_xpec_statcfg_timer0;             /* Timer0                                                  */
	                                                                           /*       2'b00 : Timer stops at 0                          */
	unsigned int timer1             : BFW_NX5_xpec_statcfg_timer1;             /* Timer1                                                  */
	unsigned int timer2             : BFW_NX5_xpec_statcfg_timer2;             /* Timer2                                                  */
	unsigned int timer3             : BFW_NX5_xpec_statcfg_timer3;             /* Timer3                                                  */
	unsigned int timer4             : BFW_NX5_xpec_statcfg_timer4;             /* Timer4                                                  */
	unsigned int timer5             : BFW_NX5_xpec_statcfg_timer5;             /* Timer5                                                  */
	unsigned int reset_req          : BFW_NX5_xpec_statcfg_reset_req;          /* System Reset                                            */
	unsigned int reset_dis          : BFW_NX5_xpec_statcfg_reset_dis;          /* disable own Reset                                       */
	unsigned int debug_mode         : BFW_NX5_xpec_statcfg_debug_mode;         /* in this mode XPEC gets debug data form sr14 and sr15    */
	unsigned int reserved1          : BFW_NX5_xpec_statcfg_reserved1;          /* reserved                                                */
	unsigned int register_mode      : BFW_NX5_xpec_statcfg_register_mode;      /* Register Mode default 0                                 */
	                                                                           /*       2'b00 : normal mode (shared register and statcfg) */
	unsigned int wr4_range_sel      : BFW_NX5_xpec_statcfg_wr4_range_sel;      /* Select range mode for wr4 default 0                     */
	                                                                           /*       2'b00 : normal mode (range4 for wr4)              */
	unsigned int wr5_range_sel      : BFW_NX5_xpec_statcfg_wr5_range_sel;      /* Select range mode for wr5 default 0                     */
	                                                                           /*       2'b00 : normal mode (range5 for wr5)              */
	unsigned int wr6_range_sel      : BFW_NX5_xpec_statcfg_wr6_range_sel;      /* Select range mode for wr6 default 0                     */
	                                                                           /*       2'b00 : normal mode (range6 for wr6)              */
	unsigned int wr7_range_sel      : BFW_NX5_xpec_statcfg_wr7_range_sel;      /* Select range mode for wr7 default 0                     */
	                                                                           /*       2'b00 : normal mode (range7 for wr7)              */
	unsigned int reserved2          : BFW_NX5_xpec_statcfg_reserved2;          /* reserved                                                */
	unsigned int run_dma_controller : BFW_NX5_xpec_statcfg_run_dma_controller; /* 0: stop dma_controller, 1: start dma_controller         */
	                                                                           /* stop / start the polling                                */
} NX5_XPEC_STATCFG_BIT_T;

typedef union {
	unsigned int           val;
	NX5_XPEC_STATCFG_BIT_T bf;
} NX5_XPEC_STATCFG_T;

/* --------------------------------------------------------------------- */
/* Register ec_maska */
/* => JMP-Mask a */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_maska   0x00000054U
#define Adr_NX5_xpec0_ec_maska 0x018C0054U
#define Adr_NX5_xpec1_ec_maska 0x018C8054U
#define DFLT_VAL_NX5_ec_maska  0x0000ffffU

#define MSK_NX5_ec_maska_sel0                   0x000000ffU
#define SRT_NX5_ec_maska_sel0                   0
#define DFLT_VAL_NX5_ec_maska_sel0              0x000000ffU
#define MSK_NX5_ec_maska_sel1                   0x0000ff00U
#define SRT_NX5_ec_maska_sel1                   8
#define DFLT_VAL_NX5_ec_maska_sel1              0x0000ff00U
#define MSK_NX5_ec_maska_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_maska_jmp_adr                16
#define DFLT_VAL_NX5_ec_maska_jmp_adr           0x00000000U
#define MSK_NX5_ec_maska_level_edge_event0      0x18000000U
#define SRT_NX5_ec_maska_level_edge_event0      27
#define DFLT_VAL_NX5_ec_maska_level_edge_event0 0x00000000U
#define MSK_NX5_ec_maska_level_edge_event1      0x60000000U
#define SRT_NX5_ec_maska_level_edge_event1      29
#define DFLT_VAL_NX5_ec_maska_level_edge_event1 0x00000000U
#define MSK_NX5_ec_maska_and_or                 0x80000000U
#define SRT_NX5_ec_maska_and_or                 31
#define DFLT_VAL_NX5_ec_maska_and_or            0x00000000U

enum {
	BFW_NX5_ec_maska_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_maska_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_maska_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_maska_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_maska_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_maska_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASKA_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_maska_sel0;              /* Select of event 0:                               */
	                                                                     /*     0-15    : XMAC status reg 0 (statcfg0 16:31) */
	unsigned int sel1              : BFW_NX5_ec_maska_sel1;              /* Select of event 1                                */
	unsigned int jmp_adr           : BFW_NX5_ec_maska_jmp_adr;           /* jmp address (0-2047)                             */
	unsigned int level_edge_event0 : BFW_NX5_ec_maska_level_edge_event0; /* for event 0 : level / edge sensitive:            */
	                                                                     /*               2'b00 sensitve to 1 level          */
	unsigned int level_edge_event1 : BFW_NX5_ec_maska_level_edge_event1; /* for event 1 : level / edge sensitive:            */
	                                                                     /*               2'b00 sensitve to 1 level          */
	unsigned int and_or            : BFW_NX5_ec_maska_and_or;            /* and/or bit:                                      */
	                                                                     /* 0 - All bits of mask must fit with events,       */
} NX5_EC_MASKA_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASKA_BIT_T bf;
} NX5_EC_MASKA_T;

/* --------------------------------------------------------------------- */
/* Register ec_maskb */
/* => JMP-Mask b */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_maskb   0x00000058U
#define Adr_NX5_xpec0_ec_maskb 0x018C0058U
#define Adr_NX5_xpec1_ec_maskb 0x018C8058U
#define DFLT_VAL_NX5_ec_maskb  0x0000ffffU

#define MSK_NX5_ec_maskb_sel0                   0x000000ffU
#define SRT_NX5_ec_maskb_sel0                   0
#define DFLT_VAL_NX5_ec_maskb_sel0              0x000000ffU
#define MSK_NX5_ec_maskb_sel1                   0x0000ff00U
#define SRT_NX5_ec_maskb_sel1                   8
#define DFLT_VAL_NX5_ec_maskb_sel1              0x0000ff00U
#define MSK_NX5_ec_maskb_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_maskb_jmp_adr                16
#define DFLT_VAL_NX5_ec_maskb_jmp_adr           0x00000000U
#define MSK_NX5_ec_maskb_level_edge_event0      0x18000000U
#define SRT_NX5_ec_maskb_level_edge_event0      27
#define DFLT_VAL_NX5_ec_maskb_level_edge_event0 0x00000000U
#define MSK_NX5_ec_maskb_level_edge_event1      0x60000000U
#define SRT_NX5_ec_maskb_level_edge_event1      29
#define DFLT_VAL_NX5_ec_maskb_level_edge_event1 0x00000000U
#define MSK_NX5_ec_maskb_and_or                 0x80000000U
#define SRT_NX5_ec_maskb_and_or                 31
#define DFLT_VAL_NX5_ec_maskb_and_or            0x00000000U

enum {
	BFW_NX5_ec_maskb_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_maskb_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_maskb_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_maskb_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_maskb_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_maskb_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASKB_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_maskb_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_maskb_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_maskb_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_maskb_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_maskb_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_maskb_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASKB_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASKB_BIT_T bf;
} NX5_EC_MASKB_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask0 */
/* => Shared in xPEC fmmusm mode with pio (r mode). */
/*    in the PIO Mode read : 31-16 pio_oe[15:0] and 15-0 pio_in[15:0] */
/*    JMP-Mask 0 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask0   0x0000005CU
#define Adr_NX5_xpec0_ec_mask0 0x018C005CU
#define Adr_NX5_xpec1_ec_mask0 0x018C805CU
#define DFLT_VAL_NX5_ec_mask0  0x0000ffffU

#define MSK_NX5_ec_mask0_sel0                   0x000000ffU
#define SRT_NX5_ec_mask0_sel0                   0
#define DFLT_VAL_NX5_ec_mask0_sel0              0x000000ffU
#define MSK_NX5_ec_mask0_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask0_sel1                   8
#define DFLT_VAL_NX5_ec_mask0_sel1              0x0000ff00U
#define MSK_NX5_ec_mask0_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask0_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask0_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask0_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask0_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask0_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask0_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask0_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask0_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask0_and_or                 0x80000000U
#define SRT_NX5_ec_mask0_and_or                 31
#define DFLT_VAL_NX5_ec_mask0_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask0_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask0_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask0_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask0_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask0_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask0_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK0_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask0_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask0_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask0_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask0_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask0_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask0_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK0_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK0_BIT_T bf;
} NX5_EC_MASK0_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask1 */
/* => Shared in xPEC fmmusm mode with dpm_pio (r mode). */
/*    in the PDM_PIO Mode read : 31-16 dpm_pio_oe[15:0] and 15-0 dpm_pio_in[15:0] */
/*    JMP-Mask 1 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask1   0x00000060U
#define Adr_NX5_xpec0_ec_mask1 0x018C0060U
#define Adr_NX5_xpec1_ec_mask1 0x018C8060U
#define DFLT_VAL_NX5_ec_mask1  0x0000ffffU

#define MSK_NX5_ec_mask1_sel0                   0x000000ffU
#define SRT_NX5_ec_mask1_sel0                   0
#define DFLT_VAL_NX5_ec_mask1_sel0              0x000000ffU
#define MSK_NX5_ec_mask1_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask1_sel1                   8
#define DFLT_VAL_NX5_ec_mask1_sel1              0x0000ff00U
#define MSK_NX5_ec_mask1_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask1_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask1_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask1_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask1_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask1_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask1_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask1_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask1_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask1_and_or                 0x80000000U
#define SRT_NX5_ec_mask1_and_or                 31
#define DFLT_VAL_NX5_ec_mask1_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask1_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask1_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask1_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask1_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask1_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask1_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK1_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask1_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask1_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask1_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask1_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask1_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask1_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK1_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK1_BIT_T bf;
} NX5_EC_MASK1_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask2 */
/* => Shared in xPEC fmmusm mode with netx_version (r mode). */
/*    JMP-Mask 2 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask2   0x00000064U
#define Adr_NX5_xpec0_ec_mask2 0x018C0064U
#define Adr_NX5_xpec1_ec_mask2 0x018C8064U
#define DFLT_VAL_NX5_ec_mask2  0x0000ffffU

#define MSK_NX5_ec_mask2_sel0                   0x000000ffU
#define SRT_NX5_ec_mask2_sel0                   0
#define DFLT_VAL_NX5_ec_mask2_sel0              0x000000ffU
#define MSK_NX5_ec_mask2_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask2_sel1                   8
#define DFLT_VAL_NX5_ec_mask2_sel1              0x0000ff00U
#define MSK_NX5_ec_mask2_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask2_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask2_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask2_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask2_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask2_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask2_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask2_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask2_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask2_and_or                 0x80000000U
#define SRT_NX5_ec_mask2_and_or                 31
#define DFLT_VAL_NX5_ec_mask2_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask2_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask2_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask2_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask2_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask2_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask2_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK2_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask2_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask2_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask2_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask2_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask2_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask2_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK2_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK2_BIT_T bf;
} NX5_EC_MASK2_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask3 */
/* => JMP-Mask 3 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask3   0x00000068U
#define Adr_NX5_xpec0_ec_mask3 0x018C0068U
#define Adr_NX5_xpec1_ec_mask3 0x018C8068U
#define DFLT_VAL_NX5_ec_mask3  0x0000ffffU

#define MSK_NX5_ec_mask3_sel0                   0x000000ffU
#define SRT_NX5_ec_mask3_sel0                   0
#define DFLT_VAL_NX5_ec_mask3_sel0              0x000000ffU
#define MSK_NX5_ec_mask3_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask3_sel1                   8
#define DFLT_VAL_NX5_ec_mask3_sel1              0x0000ff00U
#define MSK_NX5_ec_mask3_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask3_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask3_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask3_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask3_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask3_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask3_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask3_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask3_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask3_and_or                 0x80000000U
#define SRT_NX5_ec_mask3_and_or                 31
#define DFLT_VAL_NX5_ec_mask3_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask3_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask3_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask3_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask3_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask3_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask3_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK3_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask3_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask3_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask3_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask3_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask3_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask3_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK3_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK3_BIT_T bf;
} NX5_EC_MASK3_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask4 */
/* => JMP-Mask 4 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask4   0x0000006CU
#define Adr_NX5_xpec0_ec_mask4 0x018C006CU
#define Adr_NX5_xpec1_ec_mask4 0x018C806CU
#define DFLT_VAL_NX5_ec_mask4  0x0000ffffU

#define MSK_NX5_ec_mask4_sel0                   0x000000ffU
#define SRT_NX5_ec_mask4_sel0                   0
#define DFLT_VAL_NX5_ec_mask4_sel0              0x000000ffU
#define MSK_NX5_ec_mask4_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask4_sel1                   8
#define DFLT_VAL_NX5_ec_mask4_sel1              0x0000ff00U
#define MSK_NX5_ec_mask4_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask4_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask4_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask4_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask4_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask4_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask4_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask4_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask4_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask4_and_or                 0x80000000U
#define SRT_NX5_ec_mask4_and_or                 31
#define DFLT_VAL_NX5_ec_mask4_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask4_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask4_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask4_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask4_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask4_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask4_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK4_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask4_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask4_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask4_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask4_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask4_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask4_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK4_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK4_BIT_T bf;
} NX5_EC_MASK4_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask5 */
/* => JMP-Mask 5 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask5   0x00000070U
#define Adr_NX5_xpec0_ec_mask5 0x018C0070U
#define Adr_NX5_xpec1_ec_mask5 0x018C8070U
#define DFLT_VAL_NX5_ec_mask5  0x0000ffffU

#define MSK_NX5_ec_mask5_sel0                   0x000000ffU
#define SRT_NX5_ec_mask5_sel0                   0
#define DFLT_VAL_NX5_ec_mask5_sel0              0x000000ffU
#define MSK_NX5_ec_mask5_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask5_sel1                   8
#define DFLT_VAL_NX5_ec_mask5_sel1              0x0000ff00U
#define MSK_NX5_ec_mask5_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask5_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask5_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask5_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask5_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask5_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask5_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask5_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask5_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask5_and_or                 0x80000000U
#define SRT_NX5_ec_mask5_and_or                 31
#define DFLT_VAL_NX5_ec_mask5_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask5_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask5_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask5_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask5_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask5_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask5_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK5_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask5_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask5_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask5_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask5_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask5_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask5_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK5_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK5_BIT_T bf;
} NX5_EC_MASK5_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask6 */
/* => JMP-Mask 6 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask6   0x00000074U
#define Adr_NX5_xpec0_ec_mask6 0x018C0074U
#define Adr_NX5_xpec1_ec_mask6 0x018C8074U
#define DFLT_VAL_NX5_ec_mask6  0x0000ffffU

#define MSK_NX5_ec_mask6_sel0                   0x000000ffU
#define SRT_NX5_ec_mask6_sel0                   0
#define DFLT_VAL_NX5_ec_mask6_sel0              0x000000ffU
#define MSK_NX5_ec_mask6_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask6_sel1                   8
#define DFLT_VAL_NX5_ec_mask6_sel1              0x0000ff00U
#define MSK_NX5_ec_mask6_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask6_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask6_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask6_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask6_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask6_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask6_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask6_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask6_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask6_and_or                 0x80000000U
#define SRT_NX5_ec_mask6_and_or                 31
#define DFLT_VAL_NX5_ec_mask6_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask6_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask6_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask6_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask6_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask6_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask6_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK6_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask6_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask6_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask6_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask6_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask6_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask6_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK6_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK6_BIT_T bf;
} NX5_EC_MASK6_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask7 */
/* => JMP-Mask 7 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask7   0x00000078U
#define Adr_NX5_xpec0_ec_mask7 0x018C0078U
#define Adr_NX5_xpec1_ec_mask7 0x018C8078U
#define DFLT_VAL_NX5_ec_mask7  0x0000ffffU

#define MSK_NX5_ec_mask7_sel0                   0x000000ffU
#define SRT_NX5_ec_mask7_sel0                   0
#define DFLT_VAL_NX5_ec_mask7_sel0              0x000000ffU
#define MSK_NX5_ec_mask7_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask7_sel1                   8
#define DFLT_VAL_NX5_ec_mask7_sel1              0x0000ff00U
#define MSK_NX5_ec_mask7_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask7_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask7_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask7_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask7_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask7_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask7_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask7_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask7_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask7_and_or                 0x80000000U
#define SRT_NX5_ec_mask7_and_or                 31
#define DFLT_VAL_NX5_ec_mask7_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask7_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask7_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask7_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask7_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask7_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask7_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK7_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask7_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask7_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask7_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask7_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask7_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask7_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK7_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK7_BIT_T bf;
} NX5_EC_MASK7_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask8 */
/* => Shared in xPEC fmmusm mode with xmac0_tpu_sys_time (r mode). */
/*    JMP-Mask 8 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask8   0x0000007CU
#define Adr_NX5_xpec0_ec_mask8 0x018C007CU
#define Adr_NX5_xpec1_ec_mask8 0x018C807CU
#define DFLT_VAL_NX5_ec_mask8  0x0000ffffU

#define MSK_NX5_ec_mask8_sel0                   0x000000ffU
#define SRT_NX5_ec_mask8_sel0                   0
#define DFLT_VAL_NX5_ec_mask8_sel0              0x000000ffU
#define MSK_NX5_ec_mask8_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask8_sel1                   8
#define DFLT_VAL_NX5_ec_mask8_sel1              0x0000ff00U
#define MSK_NX5_ec_mask8_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask8_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask8_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask8_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask8_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask8_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask8_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask8_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask8_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask8_and_or                 0x80000000U
#define SRT_NX5_ec_mask8_and_or                 31
#define DFLT_VAL_NX5_ec_mask8_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask8_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask8_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask8_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask8_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask8_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask8_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK8_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask8_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask8_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask8_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask8_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask8_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask8_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK8_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK8_BIT_T bf;
} NX5_EC_MASK8_T;

/* --------------------------------------------------------------------- */
/* Register ec_mask9 */
/* => Shared in xPEC fmmusm mode with xmac1_tpu_sys_time (r mode). */
/*    JMP-Mask 9 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_ec_mask9   0x00000080U
#define Adr_NX5_xpec0_ec_mask9 0x018C0080U
#define Adr_NX5_xpec1_ec_mask9 0x018C8080U
#define DFLT_VAL_NX5_ec_mask9  0x0000ffffU

#define MSK_NX5_ec_mask9_sel0                   0x000000ffU
#define SRT_NX5_ec_mask9_sel0                   0
#define DFLT_VAL_NX5_ec_mask9_sel0              0x000000ffU
#define MSK_NX5_ec_mask9_sel1                   0x0000ff00U
#define SRT_NX5_ec_mask9_sel1                   8
#define DFLT_VAL_NX5_ec_mask9_sel1              0x0000ff00U
#define MSK_NX5_ec_mask9_jmp_adr                0x07ff0000U
#define SRT_NX5_ec_mask9_jmp_adr                16
#define DFLT_VAL_NX5_ec_mask9_jmp_adr           0x00000000U
#define MSK_NX5_ec_mask9_level_edge_event0      0x18000000U
#define SRT_NX5_ec_mask9_level_edge_event0      27
#define DFLT_VAL_NX5_ec_mask9_level_edge_event0 0x00000000U
#define MSK_NX5_ec_mask9_level_edge_event1      0x60000000U
#define SRT_NX5_ec_mask9_level_edge_event1      29
#define DFLT_VAL_NX5_ec_mask9_level_edge_event1 0x00000000U
#define MSK_NX5_ec_mask9_and_or                 0x80000000U
#define SRT_NX5_ec_mask9_and_or                 31
#define DFLT_VAL_NX5_ec_mask9_and_or            0x00000000U

enum {
	BFW_NX5_ec_mask9_sel0              = 8,  /* [7:0] */
	BFW_NX5_ec_mask9_sel1              = 8,  /* [15:8] */
	BFW_NX5_ec_mask9_jmp_adr           = 11, /* [26:16] */
	BFW_NX5_ec_mask9_level_edge_event0 = 2,  /* [28:27] */
	BFW_NX5_ec_mask9_level_edge_event1 = 2,  /* [30:29] */
	BFW_NX5_ec_mask9_and_or            = 1   /* [31] */
};

typedef struct NX5_EC_MASK9_BIT_Ttag {
	unsigned int sel0              : BFW_NX5_ec_mask9_sel0;              /* Select of event 0                          */
	unsigned int sel1              : BFW_NX5_ec_mask9_sel1;              /* Select of event 1                          */
	unsigned int jmp_adr           : BFW_NX5_ec_mask9_jmp_adr;           /* jmp address (0-2047)                       */
	unsigned int level_edge_event0 : BFW_NX5_ec_mask9_level_edge_event0; /* for event 0 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int level_edge_event1 : BFW_NX5_ec_mask9_level_edge_event1; /* for event 1 : level / edge sensitive:      */
	                                                                     /*               2'b00 sensitve to 1 level    */
	unsigned int and_or            : BFW_NX5_ec_mask9_and_or;            /* and/or bit:                                */
	                                                                     /* 0 - All bits of mask must fit with events, */
} NX5_EC_MASK9_BIT_T;

typedef union {
	unsigned int       val;
	NX5_EC_MASK9_BIT_T bf;
} NX5_EC_MASK9_T;

/* --------------------------------------------------------------------- */
/* Register timer4 */
/* => xPEC Timer 4 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_timer4   0x00000084U
#define Adr_NX5_xpec0_timer4 0x018C0084U
#define Adr_NX5_xpec1_timer4 0x018C8084U
#define DFLT_VAL_NX5_timer4  0x00000000U

#define MSK_NX5_timer4_preload2      0xffffffffU
#define SRT_NX5_timer4_preload2      0
#define DFLT_VAL_NX5_timer4_preload2 0x00000000U

enum {
	BFW_NX5_timer4_preload2 = 32  /* [31:0] */
};

typedef struct NX5_TIMER4_BIT_Ttag {
	unsigned int preload2 : BFW_NX5_timer4_preload2; /* read: actual value of timer, write: timer and preload value */
} NX5_TIMER4_BIT_T;

typedef union {
	unsigned int     val;
	NX5_TIMER4_BIT_T bf;
} NX5_TIMER4_T;

/* --------------------------------------------------------------------- */
/* Register timer5 */
/* => xPEC Timer 5 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_timer5   0x00000088U
#define Adr_NX5_xpec0_timer5 0x018C0088U
#define Adr_NX5_xpec1_timer5 0x018C8088U
#define DFLT_VAL_NX5_timer5  0x00000000U

#define MSK_NX5_timer5_preload3      0xffffffffU
#define SRT_NX5_timer5_preload3      0
#define DFLT_VAL_NX5_timer5_preload3 0x00000000U

enum {
	BFW_NX5_timer5_preload3 = 32  /* [31:0] */
};

typedef struct NX5_TIMER5_BIT_Ttag {
	unsigned int preload3 : BFW_NX5_timer5_preload3; /* read: actual value of timer, write: timer and preload value */
} NX5_TIMER5_BIT_T;

typedef union {
	unsigned int     val;
	NX5_TIMER5_BIT_T bf;
} NX5_TIMER5_T;

/* --------------------------------------------------------------------- */
/* Register irq */
/* => xPEC IRQ Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_irq   0x0000008CU
#define Adr_NX5_xpec0_irq 0x018C008CU
#define Adr_NX5_xpec1_irq 0x018C808CU
#define DFLT_VAL_NX5_irq  0x00000000U

#define MSK_NX5_irq_xpec_irq      0x0000ffffU
#define SRT_NX5_irq_xpec_irq      0
#define DFLT_VAL_NX5_irq_xpec_irq 0x00000000U
#define MSK_NX5_irq_arm_irq       0xffff0000U
#define SRT_NX5_irq_arm_irq       16
#define DFLT_VAL_NX5_irq_arm_irq  0x00000000U

enum {
	BFW_NX5_irq_xpec_irq = 16, /* [15:0] */
	BFW_NX5_irq_arm_irq  = 16  /* [31:16] */
};

typedef struct NX5_IRQ_BIT_Ttag {
	unsigned int xpec_irq : BFW_NX5_irq_xpec_irq; /* set by xpec ; reset by arm  */
	unsigned int arm_irq  : BFW_NX5_irq_arm_irq;  /* set by arm  ; reset by xpec */
} NX5_IRQ_BIT_T;

typedef union {
	unsigned int  val;
	NX5_IRQ_BIT_T bf;
} NX5_IRQ_T;

/* --------------------------------------------------------------------- */
/* Register xpec_systime_ns */
/* => xPEC System time (for read) */
/*    PIOs and PIOS output enables [15:0] (write) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_systime_ns   0x00000090U
#define Adr_NX5_xpec0_xpec_systime_ns 0x018C0090U
#define Adr_NX5_xpec1_xpec_systime_ns 0x018C8090U
#define DFLT_VAL_NX5_xpec_systime_ns  0x00000000U

#define MSK_NX5_xpec_systime_ns_systime_ns      0xffffffffU
#define SRT_NX5_xpec_systime_ns_systime_ns      0
#define DFLT_VAL_NX5_xpec_systime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_xpec_systime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_XPEC_SYSTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_xpec_systime_ns_systime_ns; /* read: 32 - Bit System Time (ns) */
	                                                              /* write:  31-15 pio_oe[15:0]      */
} NX5_XPEC_SYSTIME_NS_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XPEC_SYSTIME_NS_BIT_T bf;
} NX5_XPEC_SYSTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register fifo_data */
/* => xPEC fifo_data */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fifo_data   0x00000094U
#define Adr_NX5_xpec0_fifo_data 0x018C0094U
#define Adr_NX5_xpec1_fifo_data 0x018C8094U
#define DFLT_VAL_NX5_fifo_data  0x00000000U

#define MSK_NX5_fifo_data_fifo_data      0xffffffffU
#define SRT_NX5_fifo_data_fifo_data      0
#define DFLT_VAL_NX5_fifo_data_fifo_data 0x00000000U

enum {
	BFW_NX5_fifo_data_fifo_data = 32  /* [31:0] */
};

typedef struct NX5_FIFO_DATA_BIT_Ttag {
	unsigned int fifo_data : BFW_NX5_fifo_data_fifo_data; /* default 0x0000 */
} NX5_FIFO_DATA_BIT_T;

typedef union {
	unsigned int        val;
	NX5_FIFO_DATA_BIT_T bf;
} NX5_FIFO_DATA_T;

/* --------------------------------------------------------------------- */
/* Register xpec_systime_s */
/* => xPEC System time (read) */
/*    DPM_PIOs and DPM_PIOS output enables [15:0] (write) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_systime_s   0x00000098U
#define Adr_NX5_xpec0_xpec_systime_s 0x018C0098U
#define Adr_NX5_xpec1_xpec_systime_s 0x018C8098U
#define DFLT_VAL_NX5_xpec_systime_s  0x00000000U

#define MSK_NX5_xpec_systime_s_systime_s      0xffffffffU
#define SRT_NX5_xpec_systime_s_systime_s      0
#define DFLT_VAL_NX5_xpec_systime_s_systime_s 0x00000000U

enum {
	BFW_NX5_xpec_systime_s_systime_s = 32  /* [31:0] */
};

typedef struct NX5_XPEC_SYSTIME_S_BIT_Ttag {
	unsigned int systime_s : BFW_NX5_xpec_systime_s_systime_s; /* read: 32 - Bit System Time (s) */
	                                                           /* write: 31-15 dpm_pio_oe[15:0]  */
} NX5_XPEC_SYSTIME_S_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XPEC_SYSTIME_S_BIT_T bf;
} NX5_XPEC_SYSTIME_S_T;

/* --------------------------------------------------------------------- */
/* Register xpec_adc */
/* => Shared in xPEC fmmusm mode with buf_man (r/w mode). */
/*    reserved for ADC Register in future netX-versions. */
/*    becomes adr_buf_man of BUF_MAN */
/*    Buffer manager address for master xPEC: */
/*    16 buffer manager modules can be accessed, where each one handles buffer numbers between up to 4 procesors. */
/*    Each read request of a master will be answered by the most actual buffer number, */
/*    each write request of a master will be answered by the lowest free buffer number. */
/*    The buffer managers can be accessed in 2 different modes: 'normal mode' and 'parallel mode' (also known as EtherCAT mode): */
/*    In normal mode getting a new buffer happens with 2 command accesses: */
/*    1st: Write access: Tell the buf_manager channel (0..15) and wether you want read or write buffer. */
/*         Wait for 2 clockcycles, until new buffer number is calculated after any write access. */
/*    2nd: Read access: Read the buffer number (0..4). */
/*    In parallel mode all buffers are accessed in parallel but some functionality is limited. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_adc   0x0000009CU
#define Adr_NX5_xpec0_xpec_adc 0x018C009CU
#define Adr_NX5_xpec1_xpec_adc 0x018C809CU
#define DFLT_VAL_NX5_xpec_adc  0x00000007U

#define MSK_NX5_xpec_adc_buf_nr              0x0000000fU
#define SRT_NX5_xpec_adc_buf_nr              0
#define DFLT_VAL_NX5_xpec_adc_buf_nr         0x00000007U
#define MSK_NX5_xpec_adc_req_type            0x00000060U
#define SRT_NX5_xpec_adc_req_type            5
#define DFLT_VAL_NX5_xpec_adc_req_type       0x00000000U
#define MSK_NX5_xpec_adc_semaphore_mode      0x00000080U
#define SRT_NX5_xpec_adc_semaphore_mode      7
#define DFLT_VAL_NX5_xpec_adc_semaphore_mode 0x00000000U
#define MSK_NX5_xpec_adc_parallel_mode       0x00000100U
#define SRT_NX5_xpec_adc_parallel_mode       8
#define DFLT_VAL_NX5_xpec_adc_parallel_mode  0x00000000U
#define MSK_NX5_xpec_adc_reset               0x00000200U
#define SRT_NX5_xpec_adc_reset               9
#define DFLT_VAL_NX5_xpec_adc_reset          0x00000000U
#define MSK_NX5_xpec_adc_sm_update_en        0x00000400U
#define SRT_NX5_xpec_adc_sm_update_en        10
#define DFLT_VAL_NX5_xpec_adc_sm_update_en   0x00000000U
#define MSK_NX5_xpec_adc_sm_update_dis       0x00000800U
#define SRT_NX5_xpec_adc_sm_update_dis       11
#define DFLT_VAL_NX5_xpec_adc_sm_update_dis  0x00000000U

enum {
	BFW_NX5_xpec_adc_buf_nr         = 4,  /* [3:0] */
	BFW_NX5_xpec_adc_reserved1      = 1,  /* [4] */
	BFW_NX5_xpec_adc_req_type       = 2,  /* [6:5] */
	BFW_NX5_xpec_adc_semaphore_mode = 1,  /* [7] */
	BFW_NX5_xpec_adc_parallel_mode  = 1,  /* [8] */
	BFW_NX5_xpec_adc_reset          = 1,  /* [9] */
	BFW_NX5_xpec_adc_sm_update_en   = 1,  /* [10] */
	BFW_NX5_xpec_adc_sm_update_dis  = 1,  /* [11] */
	BFW_NX5_xpec_adc_reserved2      = 20  /* [31:12] */
};

typedef struct NX5_XPEC_ADC_BIT_Ttag {
	unsigned int buf_nr         : BFW_NX5_xpec_adc_buf_nr;         /* write access: number of buf_manager channel (0..15)                                              */
	                                                               /* read access: number of buffer (0..m+1), where m ist the number of masters using this buf_manager */
	unsigned int reserved1      : BFW_NX5_xpec_adc_reserved1;      /* reserved                                                                                         */
	unsigned int req_type       : BFW_NX5_xpec_adc_req_type;       /* Request type bits are write-only                                                                 */
	                                                               /* 00: request read buffer (or semaphore)                                                           */
	unsigned int semaphore_mode : BFW_NX5_xpec_adc_semaphore_mode; /* Activate 'semaphore mode' for this buf_nr by writing 1 to this bit.                              */
	                                                               /* To return from semaphore-mode reset this channel                                                 */
	unsigned int parallel_mode  : BFW_NX5_xpec_adc_parallel_mode;  /* activate parallel mode by writing 1 to this bit (other bits are ignored):                        */
	                                                               /* In parallel mode, the behavior of all bits of this register changes completely.                  */
	unsigned int reset          : BFW_NX5_xpec_adc_reset;          /* reset channel                                                                                    */
	unsigned int sm_update_en   : BFW_NX5_xpec_adc_sm_update_en;   /* activate SM_auto_update mode by writing 1 to this bit:                                           */
	                                                               /* In SM_auto_update mode the requested buffer numbers of buffer managers 0..7 will automatically   */
	unsigned int sm_update_dis  : BFW_NX5_xpec_adc_sm_update_dis;  /* de-activate SM_auto_update mode by writing 1 to this bit:                                        */
	unsigned int reserved2      : BFW_NX5_xpec_adc_reserved2;      /* reserved                                                                                         */
} NX5_XPEC_ADC_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_ADC_BIT_T bf;
} NX5_XPEC_ADC_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr0 */
/* => Shared Work Register 0 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr0   0x000000A0U
#define Adr_NX5_xpec0_xpec_sr0 0x018C00A0U
#define Adr_NX5_xpec1_xpec_sr0 0x018C80A0U
#define DFLT_VAL_NX5_xpec_sr0  0x00000000U

#define MSK_NX5_xpec_sr0_SR0         0x0000ffffU
#define SRT_NX5_xpec_sr0_SR0         0
#define DFLT_VAL_NX5_xpec_sr0_SR0    0x00000000U
#define MSK_NX5_xpec_sr0_SR0_15      0xffff0000U
#define SRT_NX5_xpec_sr0_SR0_15      16
#define DFLT_VAL_NX5_xpec_sr0_SR0_15 0x00000000U

enum {
	BFW_NX5_xpec_sr0_SR0    = 16, /* [15:0] */
	BFW_NX5_xpec_sr0_SR0_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR0_BIT_Ttag {
	unsigned int SR0    : BFW_NX5_xpec_sr0_SR0;    /* Shared Register */
	unsigned int SR0_15 : BFW_NX5_xpec_sr0_SR0_15; /* Sign extension  */
} NX5_XPEC_SR0_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR0_BIT_T bf;
} NX5_XPEC_SR0_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr1 */
/* => Shared Work Register 1 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr1   0x000000A4U
#define Adr_NX5_xpec0_xpec_sr1 0x018C00A4U
#define Adr_NX5_xpec1_xpec_sr1 0x018C80A4U
#define DFLT_VAL_NX5_xpec_sr1  0x00000000U

#define MSK_NX5_xpec_sr1_SR1         0x0000ffffU
#define SRT_NX5_xpec_sr1_SR1         0
#define DFLT_VAL_NX5_xpec_sr1_SR1    0x00000000U
#define MSK_NX5_xpec_sr1_SR1_15      0xffff0000U
#define SRT_NX5_xpec_sr1_SR1_15      16
#define DFLT_VAL_NX5_xpec_sr1_SR1_15 0x00000000U

enum {
	BFW_NX5_xpec_sr1_SR1    = 16, /* [15:0] */
	BFW_NX5_xpec_sr1_SR1_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR1_BIT_Ttag {
	unsigned int SR1    : BFW_NX5_xpec_sr1_SR1;    /* Shared Register */
	unsigned int SR1_15 : BFW_NX5_xpec_sr1_SR1_15; /* Sign extension  */
} NX5_XPEC_SR1_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR1_BIT_T bf;
} NX5_XPEC_SR1_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr2 */
/* => Shared Work Register 2 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr2   0x000000A8U
#define Adr_NX5_xpec0_xpec_sr2 0x018C00A8U
#define Adr_NX5_xpec1_xpec_sr2 0x018C80A8U
#define DFLT_VAL_NX5_xpec_sr2  0x00000000U

#define MSK_NX5_xpec_sr2_SR2         0x0000ffffU
#define SRT_NX5_xpec_sr2_SR2         0
#define DFLT_VAL_NX5_xpec_sr2_SR2    0x00000000U
#define MSK_NX5_xpec_sr2_SR2_15      0xffff0000U
#define SRT_NX5_xpec_sr2_SR2_15      16
#define DFLT_VAL_NX5_xpec_sr2_SR2_15 0x00000000U

enum {
	BFW_NX5_xpec_sr2_SR2    = 16, /* [15:0] */
	BFW_NX5_xpec_sr2_SR2_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR2_BIT_Ttag {
	unsigned int SR2    : BFW_NX5_xpec_sr2_SR2;    /* Shared Register */
	unsigned int SR2_15 : BFW_NX5_xpec_sr2_SR2_15; /* Sign extension  */
} NX5_XPEC_SR2_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR2_BIT_T bf;
} NX5_XPEC_SR2_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr3 */
/* => Shared Work Register 3 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr3   0x000000ACU
#define Adr_NX5_xpec0_xpec_sr3 0x018C00ACU
#define Adr_NX5_xpec1_xpec_sr3 0x018C80ACU
#define DFLT_VAL_NX5_xpec_sr3  0x00000000U

#define MSK_NX5_xpec_sr3_SR3         0x0000ffffU
#define SRT_NX5_xpec_sr3_SR3         0
#define DFLT_VAL_NX5_xpec_sr3_SR3    0x00000000U
#define MSK_NX5_xpec_sr3_SR3_15      0xffff0000U
#define SRT_NX5_xpec_sr3_SR3_15      16
#define DFLT_VAL_NX5_xpec_sr3_SR3_15 0x00000000U

enum {
	BFW_NX5_xpec_sr3_SR3    = 16, /* [15:0] */
	BFW_NX5_xpec_sr3_SR3_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR3_BIT_Ttag {
	unsigned int SR3    : BFW_NX5_xpec_sr3_SR3;    /* Shared Register */
	unsigned int SR3_15 : BFW_NX5_xpec_sr3_SR3_15; /* Sign extension  */
} NX5_XPEC_SR3_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR3_BIT_T bf;
} NX5_XPEC_SR3_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr4 */
/* => Shared Work Register 4 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr4   0x000000B0U
#define Adr_NX5_xpec0_xpec_sr4 0x018C00B0U
#define Adr_NX5_xpec1_xpec_sr4 0x018C80B0U
#define DFLT_VAL_NX5_xpec_sr4  0x00000000U

#define MSK_NX5_xpec_sr4_SR4         0x0000ffffU
#define SRT_NX5_xpec_sr4_SR4         0
#define DFLT_VAL_NX5_xpec_sr4_SR4    0x00000000U
#define MSK_NX5_xpec_sr4_SR4_15      0xffff0000U
#define SRT_NX5_xpec_sr4_SR4_15      16
#define DFLT_VAL_NX5_xpec_sr4_SR4_15 0x00000000U

enum {
	BFW_NX5_xpec_sr4_SR4    = 16, /* [15:0] */
	BFW_NX5_xpec_sr4_SR4_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR4_BIT_Ttag {
	unsigned int SR4    : BFW_NX5_xpec_sr4_SR4;    /* Shared Register */
	unsigned int SR4_15 : BFW_NX5_xpec_sr4_SR4_15; /* Sign extension  */
} NX5_XPEC_SR4_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR4_BIT_T bf;
} NX5_XPEC_SR4_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr5 */
/* => Shared Work Register 5 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr5   0x000000B4U
#define Adr_NX5_xpec0_xpec_sr5 0x018C00B4U
#define Adr_NX5_xpec1_xpec_sr5 0x018C80B4U
#define DFLT_VAL_NX5_xpec_sr5  0x00000000U

#define MSK_NX5_xpec_sr5_SR5         0x0000ffffU
#define SRT_NX5_xpec_sr5_SR5         0
#define DFLT_VAL_NX5_xpec_sr5_SR5    0x00000000U
#define MSK_NX5_xpec_sr5_SR5_15      0xffff0000U
#define SRT_NX5_xpec_sr5_SR5_15      16
#define DFLT_VAL_NX5_xpec_sr5_SR5_15 0x00000000U

enum {
	BFW_NX5_xpec_sr5_SR5    = 16, /* [15:0] */
	BFW_NX5_xpec_sr5_SR5_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR5_BIT_Ttag {
	unsigned int SR5    : BFW_NX5_xpec_sr5_SR5;    /* Shared Register */
	unsigned int SR5_15 : BFW_NX5_xpec_sr5_SR5_15; /* Sign extension  */
} NX5_XPEC_SR5_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR5_BIT_T bf;
} NX5_XPEC_SR5_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr6 */
/* => Shared Work Register 6 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr6   0x000000B8U
#define Adr_NX5_xpec0_xpec_sr6 0x018C00B8U
#define Adr_NX5_xpec1_xpec_sr6 0x018C80B8U
#define DFLT_VAL_NX5_xpec_sr6  0x00000000U

#define MSK_NX5_xpec_sr6_SR6         0x0000ffffU
#define SRT_NX5_xpec_sr6_SR6         0
#define DFLT_VAL_NX5_xpec_sr6_SR6    0x00000000U
#define MSK_NX5_xpec_sr6_SR6_15      0xffff0000U
#define SRT_NX5_xpec_sr6_SR6_15      16
#define DFLT_VAL_NX5_xpec_sr6_SR6_15 0x00000000U

enum {
	BFW_NX5_xpec_sr6_SR6    = 16, /* [15:0] */
	BFW_NX5_xpec_sr6_SR6_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR6_BIT_Ttag {
	unsigned int SR6    : BFW_NX5_xpec_sr6_SR6;    /* Shared Register */
	unsigned int SR6_15 : BFW_NX5_xpec_sr6_SR6_15; /* Sign extension  */
} NX5_XPEC_SR6_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR6_BIT_T bf;
} NX5_XPEC_SR6_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr7 */
/* => Shared Work Register 7 accessed by all xPECs and all xMACs. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr7   0x000000BCU
#define Adr_NX5_xpec0_xpec_sr7 0x018C00BCU
#define Adr_NX5_xpec1_xpec_sr7 0x018C80BCU
#define DFLT_VAL_NX5_xpec_sr7  0x00000000U

#define MSK_NX5_xpec_sr7_SR7         0x0000ffffU
#define SRT_NX5_xpec_sr7_SR7         0
#define DFLT_VAL_NX5_xpec_sr7_SR7    0x00000000U
#define MSK_NX5_xpec_sr7_SR7_15      0xffff0000U
#define SRT_NX5_xpec_sr7_SR7_15      16
#define DFLT_VAL_NX5_xpec_sr7_SR7_15 0x00000000U

enum {
	BFW_NX5_xpec_sr7_SR7    = 16, /* [15:0] */
	BFW_NX5_xpec_sr7_SR7_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR7_BIT_Ttag {
	unsigned int SR7    : BFW_NX5_xpec_sr7_SR7;    /* Shared Register */
	unsigned int SR7_15 : BFW_NX5_xpec_sr7_SR7_15; /* Sign extension  */
} NX5_XPEC_SR7_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR7_BIT_T bf;
} NX5_XPEC_SR7_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr8 */
/* => Shared Work Register 8 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_sample_irq (r/w mode). */
/*    Shared in xPEC fmmusm mode with fmmusm_len_en (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr8   0x000000C0U
#define Adr_NX5_xpec0_xpec_sr8 0x018C00C0U
#define Adr_NX5_xpec1_xpec_sr8 0x018C80C0U
#define DFLT_VAL_NX5_xpec_sr8  0x00000000U

#define MSK_NX5_xpec_sr8_SR8         0x0000ffffU
#define SRT_NX5_xpec_sr8_SR8         0
#define DFLT_VAL_NX5_xpec_sr8_SR8    0x00000000U
#define MSK_NX5_xpec_sr8_SR8_15      0xffff0000U
#define SRT_NX5_xpec_sr8_SR8_15      16
#define DFLT_VAL_NX5_xpec_sr8_SR8_15 0x00000000U

enum {
	BFW_NX5_xpec_sr8_SR8    = 16, /* [15:0] */
	BFW_NX5_xpec_sr8_SR8_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR8_BIT_Ttag {
	unsigned int SR8    : BFW_NX5_xpec_sr8_SR8;    /* Shared Register */
	unsigned int SR8_15 : BFW_NX5_xpec_sr8_SR8_15; /* Sign extension  */
} NX5_XPEC_SR8_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR8_BIT_T bf;
} NX5_XPEC_SR8_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr9 */
/* => Shared Work Register 9 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_activate (r/w mode). */
/*    Shared in xPEC fmmusm mode with fmmusm_status_out (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr9   0x000000C4U
#define Adr_NX5_xpec0_xpec_sr9 0x018C00C4U
#define Adr_NX5_xpec1_xpec_sr9 0x018C80C4U
#define DFLT_VAL_NX5_xpec_sr9  0x00000000U

#define MSK_NX5_xpec_sr9_SR9         0x0000ffffU
#define SRT_NX5_xpec_sr9_SR9         0
#define DFLT_VAL_NX5_xpec_sr9_SR9    0x00000000U
#define MSK_NX5_xpec_sr9_SR9_15      0xffff0000U
#define SRT_NX5_xpec_sr9_SR9_15      16
#define DFLT_VAL_NX5_xpec_sr9_SR9_15 0x00000000U

enum {
	BFW_NX5_xpec_sr9_SR9    = 16, /* [15:0] */
	BFW_NX5_xpec_sr9_SR9_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR9_BIT_Ttag {
	unsigned int SR9    : BFW_NX5_xpec_sr9_SR9;    /* Shared Register */
	unsigned int SR9_15 : BFW_NX5_xpec_sr9_SR9_15; /* Sign extension  */
} NX5_XPEC_SR9_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XPEC_SR9_BIT_T bf;
} NX5_XPEC_SR9_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr10 */
/* => Shared Work Register 10 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_impulse_length (r/w mode). */
/*    Shared in xPEC fmmusm mode with sm_buf_statcfg (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr10   0x000000C8U
#define Adr_NX5_xpec0_xpec_sr10 0x018C00C8U
#define Adr_NX5_xpec1_xpec_sr10 0x018C80C8U
#define DFLT_VAL_NX5_xpec_sr10  0x00000000U

#define MSK_NX5_xpec_sr10_SR10         0x0000ffffU
#define SRT_NX5_xpec_sr10_SR10         0
#define DFLT_VAL_NX5_xpec_sr10_SR10    0x00000000U
#define MSK_NX5_xpec_sr10_SR10_15      0xffff0000U
#define SRT_NX5_xpec_sr10_SR10_15      16
#define DFLT_VAL_NX5_xpec_sr10_SR10_15 0x00000000U

enum {
	BFW_NX5_xpec_sr10_SR10    = 16, /* [15:0] */
	BFW_NX5_xpec_sr10_SR10_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR10_BIT_Ttag {
	unsigned int SR10    : BFW_NX5_xpec_sr10_SR10;    /* Shared Register */
	unsigned int SR10_15 : BFW_NX5_xpec_sr10_SR10_15; /* Sign extension  */
} NX5_XPEC_SR10_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XPEC_SR10_BIT_T bf;
} NX5_XPEC_SR10_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr11 */
/* => Shared Work Register 11 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_0_starttime_ns (r/w mode). */
/*    Shared in xPEC fmmusm mode with sm_read_event (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr11   0x000000CCU
#define Adr_NX5_xpec0_xpec_sr11 0x018C00CCU
#define Adr_NX5_xpec1_xpec_sr11 0x018C80CCU
#define DFLT_VAL_NX5_xpec_sr11  0x00000000U

#define MSK_NX5_xpec_sr11_SR11         0x0000ffffU
#define SRT_NX5_xpec_sr11_SR11         0
#define DFLT_VAL_NX5_xpec_sr11_SR11    0x00000000U
#define MSK_NX5_xpec_sr11_SR11_15      0xffff0000U
#define SRT_NX5_xpec_sr11_SR11_15      16
#define DFLT_VAL_NX5_xpec_sr11_SR11_15 0x00000000U

enum {
	BFW_NX5_xpec_sr11_SR11    = 16, /* [15:0] */
	BFW_NX5_xpec_sr11_SR11_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR11_BIT_Ttag {
	unsigned int SR11    : BFW_NX5_xpec_sr11_SR11;    /* Shared Register */
	unsigned int SR11_15 : BFW_NX5_xpec_sr11_SR11_15; /* Sign extension  */
} NX5_XPEC_SR11_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XPEC_SR11_BIT_T bf;
} NX5_XPEC_SR11_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr12 */
/* => Shared Work Register 12 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_1_starttime_ns (r/w mode). */
/*    Shared in xPEC fmmusm mode with sm_write_event (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr12   0x000000D0U
#define Adr_NX5_xpec0_xpec_sr12 0x018C00D0U
#define Adr_NX5_xpec1_xpec_sr12 0x018C80D0U
#define DFLT_VAL_NX5_xpec_sr12  0x00000000U

#define MSK_NX5_xpec_sr12_SR12         0x0000ffffU
#define SRT_NX5_xpec_sr12_SR12         0
#define DFLT_VAL_NX5_xpec_sr12_SR12    0x00000000U
#define MSK_NX5_xpec_sr12_SR12_15      0xffff0000U
#define SRT_NX5_xpec_sr12_SR12_15      16
#define DFLT_VAL_NX5_xpec_sr12_SR12_15 0x00000000U

enum {
	BFW_NX5_xpec_sr12_SR12    = 16, /* [15:0] */
	BFW_NX5_xpec_sr12_SR12_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR12_BIT_Ttag {
	unsigned int SR12    : BFW_NX5_xpec_sr12_SR12;    /* Shared Register */
	unsigned int SR12_15 : BFW_NX5_xpec_sr12_SR12_15; /* Sign extension  */
} NX5_XPEC_SR12_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XPEC_SR12_BIT_T bf;
} NX5_XPEC_SR12_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr13 */
/* => Shared Work Register 13 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_0_cyc_time (r/w mode). */
/*    Shared in xPEC fmmusm mode with sm_first_byte_addressed (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr13   0x000000D4U
#define Adr_NX5_xpec0_xpec_sr13 0x018C00D4U
#define Adr_NX5_xpec1_xpec_sr13 0x018C80D4U
#define DFLT_VAL_NX5_xpec_sr13  0x00000000U

#define MSK_NX5_xpec_sr13_SR13         0x0000ffffU
#define SRT_NX5_xpec_sr13_SR13         0
#define DFLT_VAL_NX5_xpec_sr13_SR13    0x00000000U
#define MSK_NX5_xpec_sr13_SR13_15      0xffff0000U
#define SRT_NX5_xpec_sr13_SR13_15      16
#define DFLT_VAL_NX5_xpec_sr13_SR13_15 0x00000000U

enum {
	BFW_NX5_xpec_sr13_SR13    = 16, /* [15:0] */
	BFW_NX5_xpec_sr13_SR13_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR13_BIT_Ttag {
	unsigned int SR13    : BFW_NX5_xpec_sr13_SR13;    /* Shared Register */
	unsigned int SR13_15 : BFW_NX5_xpec_sr13_SR13_15; /* Sign extension  */
} NX5_XPEC_SR13_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XPEC_SR13_BIT_T bf;
} NX5_XPEC_SR13_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr14 */
/* => Shared Work Register 14 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_trigger_1_cyc_time (r/w mode). */
/*    Shared in xPEC fmmusm mode with sm_last_byte_addressed (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr14   0x000000D8U
#define Adr_NX5_xpec0_xpec_sr14 0x018C00D8U
#define Adr_NX5_xpec1_xpec_sr14 0x018C80D8U
#define DFLT_VAL_NX5_xpec_sr14  0x00000000U

#define MSK_NX5_xpec_sr14_SR14         0x0000ffffU
#define SRT_NX5_xpec_sr14_SR14         0
#define DFLT_VAL_NX5_xpec_sr14_SR14    0x00000000U
#define MSK_NX5_xpec_sr14_SR14_15      0xffff0000U
#define SRT_NX5_xpec_sr14_SR14_15      16
#define DFLT_VAL_NX5_xpec_sr14_SR14_15 0x00000000U

enum {
	BFW_NX5_xpec_sr14_SR14    = 16, /* [15:0] */
	BFW_NX5_xpec_sr14_SR14_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR14_BIT_Ttag {
	unsigned int SR14    : BFW_NX5_xpec_sr14_SR14;    /* Shared Register -- in debug mode (statcfg[14]) read 32 Bit xpec_debug_code */
	unsigned int SR14_15 : BFW_NX5_xpec_sr14_SR14_15; /* Sign extension                                                             */
} NX5_XPEC_SR14_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XPEC_SR14_BIT_T bf;
} NX5_XPEC_SR14_T;

/* --------------------------------------------------------------------- */
/* Register xpec_sr15 */
/* => Shared Work Register 15 accessed by all xPECs and all xMACs. */
/*    Shared in xPEC trigger_sample mode with adr_sample_mode (r/w mode). */
/*    Shared in xPEC fmmusm mode with sm_served (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec_sr15   0x000000DCU
#define Adr_NX5_xpec0_xpec_sr15 0x018C00DCU
#define Adr_NX5_xpec1_xpec_sr15 0x018C80DCU
#define DFLT_VAL_NX5_xpec_sr15  0x00000000U

#define MSK_NX5_xpec_sr15_SR15         0x0000ffffU
#define SRT_NX5_xpec_sr15_SR15         0
#define DFLT_VAL_NX5_xpec_sr15_SR15    0x00000000U
#define MSK_NX5_xpec_sr15_SR15_15      0xffff0000U
#define SRT_NX5_xpec_sr15_SR15_15      16
#define DFLT_VAL_NX5_xpec_sr15_SR15_15 0x00000000U

enum {
	BFW_NX5_xpec_sr15_SR15    = 16, /* [15:0] */
	BFW_NX5_xpec_sr15_SR15_15 = 16  /* [31:16] */
};

typedef struct NX5_XPEC_SR15_BIT_Ttag {
	unsigned int SR15    : BFW_NX5_xpec_sr15_SR15;    /* Shared Register -- in debug mode (statcfg[14]) read 11 Bit xpec_debug_pc */
	unsigned int SR15_15 : BFW_NX5_xpec_sr15_SR15_15; /* Sign extension                                                           */
} NX5_XPEC_SR15_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XPEC_SR15_BIT_T bf;
} NX5_XPEC_SR15_T;

/* --------------------------------------------------------------------- */
/* Register statcfg0 */
/* => xMAC0 Shared Config/Status Register */
/*    for write mode the upper Bits [31:16] are mask bits for Bits [15:0] of shared_config (xMAC) register */
/*    Shared in xPEC trigger_sample mode with adr_sample_0_pos_systime_ns (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_statcfg0   0x000000E0U
#define Adr_NX5_xpec0_statcfg0 0x018C00E0U
#define Adr_NX5_xpec1_statcfg0 0x018C80E0U
#define DFLT_VAL_NX5_statcfg0  0x00500000U

#define MSK_NX5_statcfg0_gpio2_out          0x00000001U
#define SRT_NX5_statcfg0_gpio2_out          0
#define DFLT_VAL_NX5_statcfg0_gpio2_out     0x00000000U
#define MSK_NX5_statcfg0_gpio2_oe           0x00000002U
#define SRT_NX5_statcfg0_gpio2_oe           1
#define DFLT_VAL_NX5_statcfg0_gpio2_oe      0x00000000U
#define MSK_NX5_statcfg0_gpio3_out          0x00000004U
#define SRT_NX5_statcfg0_gpio3_out          2
#define DFLT_VAL_NX5_statcfg0_gpio3_out     0x00000000U
#define MSK_NX5_statcfg0_gpio3_oe           0x00000008U
#define SRT_NX5_statcfg0_gpio3_oe           3
#define DFLT_VAL_NX5_statcfg0_gpio3_oe      0x00000000U
#define MSK_NX5_statcfg0_gpio4_out          0x00000010U
#define SRT_NX5_statcfg0_gpio4_out          4
#define DFLT_VAL_NX5_statcfg0_gpio4_out     0x00000000U
#define MSK_NX5_statcfg0_gpio4_oe           0x00000020U
#define SRT_NX5_statcfg0_gpio4_oe           5
#define DFLT_VAL_NX5_statcfg0_gpio4_oe      0x00000000U
#define MSK_NX5_statcfg0_gpio5_out          0x00000040U
#define SRT_NX5_statcfg0_gpio5_out          6
#define DFLT_VAL_NX5_statcfg0_gpio5_out     0x00000000U
#define MSK_NX5_statcfg0_gpio5_oe           0x00000080U
#define SRT_NX5_statcfg0_gpio5_oe           7
#define DFLT_VAL_NX5_statcfg0_gpio5_oe      0x00000000U
#define MSK_NX5_statcfg0_rx_shift_lr        0x00000100U
#define SRT_NX5_statcfg0_rx_shift_lr        8
#define DFLT_VAL_NX5_statcfg0_rx_shift_lr   0x00000000U
#define MSK_NX5_statcfg0_tx_shift_lr        0x00000200U
#define SRT_NX5_statcfg0_tx_shift_lr        9
#define DFLT_VAL_NX5_statcfg0_tx_shift_lr   0x00000000U
#define MSK_NX5_statcfg0_reset_rx_fifo      0x00000400U
#define SRT_NX5_statcfg0_reset_rx_fifo      10
#define DFLT_VAL_NX5_statcfg0_reset_rx_fifo 0x00000000U
#define MSK_NX5_statcfg0_reset_tx_fifo      0x00000800U
#define SRT_NX5_statcfg0_reset_tx_fifo      11
#define DFLT_VAL_NX5_statcfg0_reset_tx_fifo 0x00000000U
#define MSK_NX5_statcfg0_gpio0_out          0x00001000U
#define SRT_NX5_statcfg0_gpio0_out          12
#define DFLT_VAL_NX5_statcfg0_gpio0_out     0x00000000U
#define MSK_NX5_statcfg0_gpio0_oe           0x00002000U
#define SRT_NX5_statcfg0_gpio0_oe           13
#define DFLT_VAL_NX5_statcfg0_gpio0_oe      0x00000000U
#define MSK_NX5_statcfg0_gpio1_out          0x00004000U
#define SRT_NX5_statcfg0_gpio1_out          14
#define DFLT_VAL_NX5_statcfg0_gpio1_out     0x00000000U
#define MSK_NX5_statcfg0_gpio1_oe           0x00008000U
#define SRT_NX5_statcfg0_gpio1_oe           15
#define DFLT_VAL_NX5_statcfg0_gpio1_oe      0x00000000U
#define MSK_NX5_statcfg0_gpio0_in           0x00010000U
#define SRT_NX5_statcfg0_gpio0_in           16
#define DFLT_VAL_NX5_statcfg0_gpio0_in      0x00000000U
#define MSK_NX5_statcfg0_gpio1_in           0x00020000U
#define SRT_NX5_statcfg0_gpio1_in           17
#define DFLT_VAL_NX5_statcfg0_gpio1_in      0x00000000U
#define MSK_NX5_statcfg0_rx_rdy             0x00040000U
#define SRT_NX5_statcfg0_rx_rdy             18
#define DFLT_VAL_NX5_statcfg0_rx_rdy        0x00000000U
#define MSK_NX5_statcfg0_rx_ovf             0x00080000U
#define SRT_NX5_statcfg0_rx_ovf             19
#define DFLT_VAL_NX5_statcfg0_rx_ovf        0x00000000U
#define MSK_NX5_statcfg0_tx_nxt             0x00100000U
#define SRT_NX5_statcfg0_tx_nxt             20
#define DFLT_VAL_NX5_statcfg0_tx_nxt        0x00100000U
#define MSK_NX5_statcfg0_tx_ufl             0x00200000U
#define SRT_NX5_statcfg0_tx_ufl             21
#define DFLT_VAL_NX5_statcfg0_tx_ufl        0x00000000U
#define MSK_NX5_statcfg0_utx_empty          0x00400000U
#define SRT_NX5_statcfg0_utx_empty          22
#define DFLT_VAL_NX5_statcfg0_utx_empty     0x00400000U
#define MSK_NX5_statcfg0_brec               0x00800000U
#define SRT_NX5_statcfg0_brec               23
#define DFLT_VAL_NX5_statcfg0_brec          0x00000000U
#define MSK_NX5_statcfg0_btran              0x01000000U
#define SRT_NX5_statcfg0_btran              24
#define DFLT_VAL_NX5_statcfg0_btran         0x00000000U
#define MSK_NX5_statcfg0_stat_rpu           0x02000000U
#define SRT_NX5_statcfg0_stat_rpu           25
#define DFLT_VAL_NX5_statcfg0_stat_rpu      0x00000000U
#define MSK_NX5_statcfg0_stat_tpu           0x04000000U
#define SRT_NX5_statcfg0_stat_tpu           26
#define DFLT_VAL_NX5_statcfg0_stat_tpu      0x00000000U
#define MSK_NX5_statcfg0_gpio2_in           0x10000000U
#define SRT_NX5_statcfg0_gpio2_in           28
#define DFLT_VAL_NX5_statcfg0_gpio2_in      0x00000000U
#define MSK_NX5_statcfg0_gpio3_in           0x20000000U
#define SRT_NX5_statcfg0_gpio3_in           29
#define DFLT_VAL_NX5_statcfg0_gpio3_in      0x00000000U
#define MSK_NX5_statcfg0_gpio4_in           0x40000000U
#define SRT_NX5_statcfg0_gpio4_in           30
#define DFLT_VAL_NX5_statcfg0_gpio4_in      0x00000000U
#define MSK_NX5_statcfg0_gpio5_in           0x80000000U
#define SRT_NX5_statcfg0_gpio5_in           31
#define DFLT_VAL_NX5_statcfg0_gpio5_in      0x00000000U

enum {
	BFW_NX5_statcfg0_gpio2_out     = 1, /* [0] */
	BFW_NX5_statcfg0_gpio2_oe      = 1, /* [1] */
	BFW_NX5_statcfg0_gpio3_out     = 1, /* [2] */
	BFW_NX5_statcfg0_gpio3_oe      = 1, /* [3] */
	BFW_NX5_statcfg0_gpio4_out     = 1, /* [4] */
	BFW_NX5_statcfg0_gpio4_oe      = 1, /* [5] */
	BFW_NX5_statcfg0_gpio5_out     = 1, /* [6] */
	BFW_NX5_statcfg0_gpio5_oe      = 1, /* [7] */
	BFW_NX5_statcfg0_rx_shift_lr   = 1, /* [8] */
	BFW_NX5_statcfg0_tx_shift_lr   = 1, /* [9] */
	BFW_NX5_statcfg0_reset_rx_fifo = 1, /* [10] */
	BFW_NX5_statcfg0_reset_tx_fifo = 1, /* [11] */
	BFW_NX5_statcfg0_gpio0_out     = 1, /* [12] */
	BFW_NX5_statcfg0_gpio0_oe      = 1, /* [13] */
	BFW_NX5_statcfg0_gpio1_out     = 1, /* [14] */
	BFW_NX5_statcfg0_gpio1_oe      = 1, /* [15] */
	BFW_NX5_statcfg0_gpio0_in      = 1, /* [16] */
	BFW_NX5_statcfg0_gpio1_in      = 1, /* [17] */
	BFW_NX5_statcfg0_rx_rdy        = 1, /* [18] */
	BFW_NX5_statcfg0_rx_ovf        = 1, /* [19] */
	BFW_NX5_statcfg0_tx_nxt        = 1, /* [20] */
	BFW_NX5_statcfg0_tx_ufl        = 1, /* [21] */
	BFW_NX5_statcfg0_utx_empty     = 1, /* [22] */
	BFW_NX5_statcfg0_brec          = 1, /* [23] */
	BFW_NX5_statcfg0_btran         = 1, /* [24] */
	BFW_NX5_statcfg0_stat_rpu      = 1, /* [25] */
	BFW_NX5_statcfg0_stat_tpu      = 1, /* [26] */
	BFW_NX5_statcfg0_reserved1     = 1, /* [27] */
	BFW_NX5_statcfg0_gpio2_in      = 1, /* [28] */
	BFW_NX5_statcfg0_gpio3_in      = 1, /* [29] */
	BFW_NX5_statcfg0_gpio4_in      = 1, /* [30] */
	BFW_NX5_statcfg0_gpio5_in      = 1  /* [31] */
};

typedef struct NX5_STATCFG0_BIT_Ttag {
	unsigned int gpio2_out     : BFW_NX5_statcfg0_gpio2_out;     /* General Purpose IO 2 output                                                    */
	unsigned int gpio2_oe      : BFW_NX5_statcfg0_gpio2_oe;      /* General Purpose IO 2 output enable                                             */
	unsigned int gpio3_out     : BFW_NX5_statcfg0_gpio3_out;     /* General Purpose IO 3 output                                                    */
	unsigned int gpio3_oe      : BFW_NX5_statcfg0_gpio3_oe;      /* General Purpose IO 3 output enable                                             */
	unsigned int gpio4_out     : BFW_NX5_statcfg0_gpio4_out;     /* General Purpose IO 4 output                                                    */
	unsigned int gpio4_oe      : BFW_NX5_statcfg0_gpio4_oe;      /* General Purpose IO 4 output enable                                             */
	unsigned int gpio5_out     : BFW_NX5_statcfg0_gpio5_out;     /* General Purpose IO 5 output                                                    */
	unsigned int gpio5_oe      : BFW_NX5_statcfg0_gpio5_oe;      /* General Purpose IO 5 output enable                                             */
	unsigned int rx_shift_lr   : BFW_NX5_statcfg0_rx_shift_lr;   /* 1: SBU reads incoming bits to position 0 of register rx and shifts rx left,    */
	                                                             /* 0: SBU reads incoming bits to position 15 of register rx and shifts rx right   */
	unsigned int tx_shift_lr   : BFW_NX5_statcfg0_tx_shift_lr;   /* 1: OBU reads outgoing bits from position 15 of register tx and shifts tx left, */
	                                                             /* 0: OBU reads outgoing bits from position 0 of register tx and shifts tx right  */
	unsigned int reset_rx_fifo : BFW_NX5_statcfg0_reset_rx_fifo; /* reset URX_FIFO and rx_ovf bit inside status_shared register                    */
	unsigned int reset_tx_fifo : BFW_NX5_statcfg0_reset_tx_fifo; /* reset UTX_FIFO and tx_ufl bit inside status_shared register                    */
	unsigned int gpio0_out     : BFW_NX5_statcfg0_gpio0_out;     /* General Purpose IO 0 output                                                    */
	unsigned int gpio0_oe      : BFW_NX5_statcfg0_gpio0_oe;      /* General Purpose IO 0 output enable                                             */
	unsigned int gpio1_out     : BFW_NX5_statcfg0_gpio1_out;     /* General Purpose IO 1 output                                                    */
	unsigned int gpio1_oe      : BFW_NX5_statcfg0_gpio1_oe;      /* General Purpose IO 1 output enable                                             */
	unsigned int gpio0_in      : BFW_NX5_statcfg0_gpio0_in;      /* value at external gpio pin                                                     */
	unsigned int gpio1_in      : BFW_NX5_statcfg0_gpio1_in;      /* value at external gpio pin                                                     */
	unsigned int rx_rdy        : BFW_NX5_statcfg0_rx_rdy;        /* received bytes are valid at output of URX_FIFO                                 */
	unsigned int rx_ovf        : BFW_NX5_statcfg0_rx_ovf;        /* receive overflow (too much data in URX_FIFO)                                   */
	unsigned int tx_nxt        : BFW_NX5_statcfg0_tx_nxt;        /* put next tx_word to UTX_FIFO: at least one entry of UTX_FIFO is empty          */
	unsigned int tx_ufl        : BFW_NX5_statcfg0_tx_ufl;        /* transmit underflow (not enough data in UTX_FIFO)                               */
	unsigned int utx_empty     : BFW_NX5_statcfg0_utx_empty;     /* UTX_FIFO is empty                                                              */
	unsigned int brec          : BFW_NX5_statcfg0_brec;          /* bit_received (active for 1 cc)                                                 */
	unsigned int btran         : BFW_NX5_statcfg0_btran;         /* bit_transmitted (active for 1 cc)                                              */
	unsigned int stat_rpu      : BFW_NX5_statcfg0_stat_rpu;      /* set and reset by RPU command bits                                              */
	unsigned int stat_tpu      : BFW_NX5_statcfg0_stat_tpu;      /* set and reset by TPU command bits                                              */
	unsigned int reserved1     : BFW_NX5_statcfg0_reserved1;     /* reserved                                                                       */
	unsigned int gpio2_in      : BFW_NX5_statcfg0_gpio2_in;      /* value at external gpio pin, also used for external PHY LED                     */
	unsigned int gpio3_in      : BFW_NX5_statcfg0_gpio3_in;      /* value at external gpio pin, also used for external PHY LED                     */
	unsigned int gpio4_in      : BFW_NX5_statcfg0_gpio4_in;      /* value at external gpio pin, also used for external PHY LED                     */
	unsigned int gpio5_in      : BFW_NX5_statcfg0_gpio5_in;      /* value at external gpio pin, also used for external PHY LED                     */
} NX5_STATCFG0_BIT_T;

typedef union {
	unsigned int       val;
	NX5_STATCFG0_BIT_T bf;
} NX5_STATCFG0_T;

/* --------------------------------------------------------------------- */
/* Register statcfg1 */
/* => xMAC1 Shared Config/Status Register */
/*    for write mode the upper Bits [31:16] are mask bits for Bits [15:0] of shared_config (xMAC) register */
/*    Shared in xPEC trigger_sample mode with adr_sample_0_neg_systime_ns (r/w mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_statcfg1   0x000000E4U
#define Adr_NX5_xpec0_statcfg1 0x018C00E4U
#define Adr_NX5_xpec1_statcfg1 0x018C80E4U
#define DFLT_VAL_NX5_statcfg1  0x00500000U

#define MSK_NX5_statcfg1_gpio2_out          0x00000001U
#define SRT_NX5_statcfg1_gpio2_out          0
#define DFLT_VAL_NX5_statcfg1_gpio2_out     0x00000000U
#define MSK_NX5_statcfg1_gpio2_oe           0x00000002U
#define SRT_NX5_statcfg1_gpio2_oe           1
#define DFLT_VAL_NX5_statcfg1_gpio2_oe      0x00000000U
#define MSK_NX5_statcfg1_gpio3_out          0x00000004U
#define SRT_NX5_statcfg1_gpio3_out          2
#define DFLT_VAL_NX5_statcfg1_gpio3_out     0x00000000U
#define MSK_NX5_statcfg1_gpio3_oe           0x00000008U
#define SRT_NX5_statcfg1_gpio3_oe           3
#define DFLT_VAL_NX5_statcfg1_gpio3_oe      0x00000000U
#define MSK_NX5_statcfg1_gpio4_out          0x00000010U
#define SRT_NX5_statcfg1_gpio4_out          4
#define DFLT_VAL_NX5_statcfg1_gpio4_out     0x00000000U
#define MSK_NX5_statcfg1_gpio4_oe           0x00000020U
#define SRT_NX5_statcfg1_gpio4_oe           5
#define DFLT_VAL_NX5_statcfg1_gpio4_oe      0x00000000U
#define MSK_NX5_statcfg1_gpio5_out          0x00000040U
#define SRT_NX5_statcfg1_gpio5_out          6
#define DFLT_VAL_NX5_statcfg1_gpio5_out     0x00000000U
#define MSK_NX5_statcfg1_gpio5_oe           0x00000080U
#define SRT_NX5_statcfg1_gpio5_oe           7
#define DFLT_VAL_NX5_statcfg1_gpio5_oe      0x00000000U
#define MSK_NX5_statcfg1_rx_shift_lr        0x00000100U
#define SRT_NX5_statcfg1_rx_shift_lr        8
#define DFLT_VAL_NX5_statcfg1_rx_shift_lr   0x00000000U
#define MSK_NX5_statcfg1_tx_shift_lr        0x00000200U
#define SRT_NX5_statcfg1_tx_shift_lr        9
#define DFLT_VAL_NX5_statcfg1_tx_shift_lr   0x00000000U
#define MSK_NX5_statcfg1_reset_rx_fifo      0x00000400U
#define SRT_NX5_statcfg1_reset_rx_fifo      10
#define DFLT_VAL_NX5_statcfg1_reset_rx_fifo 0x00000000U
#define MSK_NX5_statcfg1_reset_tx_fifo      0x00000800U
#define SRT_NX5_statcfg1_reset_tx_fifo      11
#define DFLT_VAL_NX5_statcfg1_reset_tx_fifo 0x00000000U
#define MSK_NX5_statcfg1_gpio0_out          0x00001000U
#define SRT_NX5_statcfg1_gpio0_out          12
#define DFLT_VAL_NX5_statcfg1_gpio0_out     0x00000000U
#define MSK_NX5_statcfg1_gpio0_oe           0x00002000U
#define SRT_NX5_statcfg1_gpio0_oe           13
#define DFLT_VAL_NX5_statcfg1_gpio0_oe      0x00000000U
#define MSK_NX5_statcfg1_gpio1_out          0x00004000U
#define SRT_NX5_statcfg1_gpio1_out          14
#define DFLT_VAL_NX5_statcfg1_gpio1_out     0x00000000U
#define MSK_NX5_statcfg1_gpio0_in           0x00010000U
#define SRT_NX5_statcfg1_gpio0_in           16
#define DFLT_VAL_NX5_statcfg1_gpio0_in      0x00000000U
#define MSK_NX5_statcfg1_gpio1_in           0x00020000U
#define SRT_NX5_statcfg1_gpio1_in           17
#define DFLT_VAL_NX5_statcfg1_gpio1_in      0x00000000U
#define MSK_NX5_statcfg1_rx_rdy             0x00040000U
#define SRT_NX5_statcfg1_rx_rdy             18
#define DFLT_VAL_NX5_statcfg1_rx_rdy        0x00000000U
#define MSK_NX5_statcfg1_rx_ovf             0x00080000U
#define SRT_NX5_statcfg1_rx_ovf             19
#define DFLT_VAL_NX5_statcfg1_rx_ovf        0x00000000U
#define MSK_NX5_statcfg1_tx_nxt             0x00100000U
#define SRT_NX5_statcfg1_tx_nxt             20
#define DFLT_VAL_NX5_statcfg1_tx_nxt        0x00100000U
#define MSK_NX5_statcfg1_tx_ufl             0x00200000U
#define SRT_NX5_statcfg1_tx_ufl             21
#define DFLT_VAL_NX5_statcfg1_tx_ufl        0x00000000U
#define MSK_NX5_statcfg1_utx_empty          0x00400000U
#define SRT_NX5_statcfg1_utx_empty          22
#define DFLT_VAL_NX5_statcfg1_utx_empty     0x00400000U
#define MSK_NX5_statcfg1_brec               0x00800000U
#define SRT_NX5_statcfg1_brec               23
#define DFLT_VAL_NX5_statcfg1_brec          0x00000000U
#define MSK_NX5_statcfg1_btran              0x01000000U
#define SRT_NX5_statcfg1_btran              24
#define DFLT_VAL_NX5_statcfg1_btran         0x00000000U
#define MSK_NX5_statcfg1_stat_rpu           0x02000000U
#define SRT_NX5_statcfg1_stat_rpu           25
#define DFLT_VAL_NX5_statcfg1_stat_rpu      0x00000000U
#define MSK_NX5_statcfg1_stat_tpu           0x04000000U
#define SRT_NX5_statcfg1_stat_tpu           26
#define DFLT_VAL_NX5_statcfg1_stat_tpu      0x00000000U
#define MSK_NX5_statcfg1_gpio2_in           0x10000000U
#define SRT_NX5_statcfg1_gpio2_in           28
#define DFLT_VAL_NX5_statcfg1_gpio2_in      0x00000000U
#define MSK_NX5_statcfg1_gpio3_in           0x20000000U
#define SRT_NX5_statcfg1_gpio3_in           29
#define DFLT_VAL_NX5_statcfg1_gpio3_in      0x00000000U
#define MSK_NX5_statcfg1_gpio4_in           0x40000000U
#define SRT_NX5_statcfg1_gpio4_in           30
#define DFLT_VAL_NX5_statcfg1_gpio4_in      0x00000000U
#define MSK_NX5_statcfg1_gpio5_in           0x80000000U
#define SRT_NX5_statcfg1_gpio5_in           31
#define DFLT_VAL_NX5_statcfg1_gpio5_in      0x00000000U

enum {
	BFW_NX5_statcfg1_gpio2_out     = 1, /* [0] */
	BFW_NX5_statcfg1_gpio2_oe      = 1, /* [1] */
	BFW_NX5_statcfg1_gpio3_out     = 1, /* [2] */
	BFW_NX5_statcfg1_gpio3_oe      = 1, /* [3] */
	BFW_NX5_statcfg1_gpio4_out     = 1, /* [4] */
	BFW_NX5_statcfg1_gpio4_oe      = 1, /* [5] */
	BFW_NX5_statcfg1_gpio5_out     = 1, /* [6] */
	BFW_NX5_statcfg1_gpio5_oe      = 1, /* [7] */
	BFW_NX5_statcfg1_rx_shift_lr   = 1, /* [8] */
	BFW_NX5_statcfg1_tx_shift_lr   = 1, /* [9] */
	BFW_NX5_statcfg1_reset_rx_fifo = 1, /* [10] */
	BFW_NX5_statcfg1_reset_tx_fifo = 1, /* [11] */
	BFW_NX5_statcfg1_gpio0_out     = 1, /* [12] */
	BFW_NX5_statcfg1_gpio0_oe      = 1, /* [13] */
	BFW_NX5_statcfg1_gpio1_out     = 1, /* [14] */
	BFW_NX5_statcfg1_reserved1     = 1, /* [15] */
	BFW_NX5_statcfg1_gpio0_in      = 1, /* [16] */
	BFW_NX5_statcfg1_gpio1_in      = 1, /* [17] */
	BFW_NX5_statcfg1_rx_rdy        = 1, /* [18] */
	BFW_NX5_statcfg1_rx_ovf        = 1, /* [19] */
	BFW_NX5_statcfg1_tx_nxt        = 1, /* [20] */
	BFW_NX5_statcfg1_tx_ufl        = 1, /* [21] */
	BFW_NX5_statcfg1_utx_empty     = 1, /* [22] */
	BFW_NX5_statcfg1_brec          = 1, /* [23] */
	BFW_NX5_statcfg1_btran         = 1, /* [24] */
	BFW_NX5_statcfg1_stat_rpu      = 1, /* [25] */
	BFW_NX5_statcfg1_stat_tpu      = 1, /* [26] */
	BFW_NX5_statcfg1_reserved2     = 1, /* [27] */
	BFW_NX5_statcfg1_gpio2_in      = 1, /* [28] */
	BFW_NX5_statcfg1_gpio3_in      = 1, /* [29] */
	BFW_NX5_statcfg1_gpio4_in      = 1, /* [30] */
	BFW_NX5_statcfg1_gpio5_in      = 1  /* [31] */
};

typedef struct NX5_STATCFG1_BIT_Ttag {
	unsigned int gpio2_out     : BFW_NX5_statcfg1_gpio2_out;     /* General Purpose IO 2 output                                                    */
	unsigned int gpio2_oe      : BFW_NX5_statcfg1_gpio2_oe;      /* General Purpose IO 2 output enable                                             */
	unsigned int gpio3_out     : BFW_NX5_statcfg1_gpio3_out;     /* General Purpose IO 3 output                                                    */
	unsigned int gpio3_oe      : BFW_NX5_statcfg1_gpio3_oe;      /* General Purpose IO 3 output enable                                             */
	unsigned int gpio4_out     : BFW_NX5_statcfg1_gpio4_out;     /* General Purpose IO 4 output                                                    */
	unsigned int gpio4_oe      : BFW_NX5_statcfg1_gpio4_oe;      /* General Purpose IO 4 output enable                                             */
	unsigned int gpio5_out     : BFW_NX5_statcfg1_gpio5_out;     /* General Purpose IO 5 output                                                    */
	unsigned int gpio5_oe      : BFW_NX5_statcfg1_gpio5_oe;      /* General Purpose IO 5 output enable                                             */
	unsigned int rx_shift_lr   : BFW_NX5_statcfg1_rx_shift_lr;   /* 1: SBU reads incoming bits to position 0 of register rx and shifts rx left,    */
	                                                             /* 0: SBU reads incoming bits to position 15 of register rx and shifts rx right   */
	unsigned int tx_shift_lr   : BFW_NX5_statcfg1_tx_shift_lr;   /* 1: OBU reads outgoing bits from position 15 of register tx and shifts tx left, */
	                                                             /* 0: OBU reads outgoing bits from position 0 of register tx and shifts tx right  */
	unsigned int reset_rx_fifo : BFW_NX5_statcfg1_reset_rx_fifo; /* reset URX_FIFO and rx_ovf bit inside status_shared register                    */
	unsigned int reset_tx_fifo : BFW_NX5_statcfg1_reset_tx_fifo; /* reset UTX_FIFO and tx_ufl bit inside status_shared register                    */
	unsigned int gpio0_out     : BFW_NX5_statcfg1_gpio0_out;     /* General Purpose IO 0 output                                                    */
	unsigned int gpio0_oe      : BFW_NX5_statcfg1_gpio0_oe;      /* General Purpose IO 0 output enable                                             */
	unsigned int gpio1_out     : BFW_NX5_statcfg1_gpio1_out;     /* General Purpose IO 1 output                                                    */
	unsigned int reserved1     : BFW_NX5_statcfg1_reserved1;     /* reserved                                                                       */
	unsigned int gpio0_in      : BFW_NX5_statcfg1_gpio0_in;      /* value at external gpio pin                                                     */
	unsigned int gpio1_in      : BFW_NX5_statcfg1_gpio1_in;      /* value at external gpio pin                                                     */
	unsigned int rx_rdy        : BFW_NX5_statcfg1_rx_rdy;        /* received bytes are valid at output of URX_FIFO                                 */
	unsigned int rx_ovf        : BFW_NX5_statcfg1_rx_ovf;        /* receive overflow (too much data in URX_FIFO)                                   */
	unsigned int tx_nxt        : BFW_NX5_statcfg1_tx_nxt;        /* put next tx_word to UTX_FIFO: at least one entry of UTX_FIFO is empty          */
	unsigned int tx_ufl        : BFW_NX5_statcfg1_tx_ufl;        /* transmit underflow (not enough data in UTX_FIFO)                               */
	unsigned int utx_empty     : BFW_NX5_statcfg1_utx_empty;     /* UTX_FIFO is empty                                                              */
	unsigned int brec          : BFW_NX5_statcfg1_brec;          /* bit_received (active for 1 cc)                                                 */
	unsigned int btran         : BFW_NX5_statcfg1_btran;         /* bit_transmitted (active for 1 cc)                                              */
	unsigned int stat_rpu      : BFW_NX5_statcfg1_stat_rpu;      /* set and reset by RPU command bits                                              */
	unsigned int stat_tpu      : BFW_NX5_statcfg1_stat_tpu;      /* set and reset by TPU command bits                                              */
	unsigned int reserved2     : BFW_NX5_statcfg1_reserved2;     /* reserved                                                                       */
	unsigned int gpio2_in      : BFW_NX5_statcfg1_gpio2_in;      /* value at external gpio pin, also used for external PHY LED                     */
	unsigned int gpio3_in      : BFW_NX5_statcfg1_gpio3_in;      /* value at external gpio pin, also used for external PHY LED                     */
	unsigned int gpio4_in      : BFW_NX5_statcfg1_gpio4_in;      /* value at external gpio pin, also used for external PHY LED                     */
	unsigned int gpio5_in      : BFW_NX5_statcfg1_gpio5_in;      /* value at external gpio pin, also used for external PHY LED                     */
} NX5_STATCFG1_BIT_T;

typedef union {
	unsigned int       val;
	NX5_STATCFG1_BIT_T bf;
} NX5_STATCFG1_T;

/* --------------------------------------------------------------------- */
/* Register statcfg2 */
/* => reserved address in net50 */
/*    Shared in xPEC trigger_sample mode with adr_sample_1_pos_systime_ns (r/w mode). */
/*    Shared in xPEC fmmusm mode with fmmu_read_bit_rol_pos (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_statcfg2   0x000000E8U
#define Adr_NX5_xpec0_statcfg2 0x018C00E8U
#define Adr_NX5_xpec1_statcfg2 0x018C80E8U

/* --------------------------------------------------------------------- */
/* Register statcfg3 */
/* => reserved address in net50 */
/*    Shared in xPEC trigger_sample mode with adr_sample_1_neg_systime_ns (r/w mode). */
/*    Shared in xPEC fmmusm mode with fmmu_write_bit_rol_pos (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_statcfg3   0x000000ECU
#define Adr_NX5_xpec0_statcfg3 0x018C00ECU
#define Adr_NX5_xpec1_statcfg3 0x018C80ECU

/* --------------------------------------------------------------------- */
/* Register urtx0 */
/* => xMAC0 URX Shared Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_urtx0   0x000000F0U
#define Adr_NX5_xpec0_urtx0 0x018C00F0U
#define Adr_NX5_xpec1_urtx0 0x018C80F0U
#define DFLT_VAL_NX5_urtx0  0x00000000U

#define MSK_NX5_urtx0_urtx_xmac0      0x0000ffffU
#define SRT_NX5_urtx0_urtx_xmac0      0
#define DFLT_VAL_NX5_urtx0_urtx_xmac0 0x00000000U

enum {
	BFW_NX5_urtx0_urtx_xmac0 = 16, /* [15:0] */
	BFW_NX5_urtx0_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_URTX0_BIT_Ttag {
	unsigned int urtx_xmac0 : BFW_NX5_urtx0_urtx_xmac0; /* read access:  Lastly received bits (output of URX_FIFO)       */
	                                                    /* write access: Bits to be transmitted next (input of UTX_FIFO) */
	unsigned int reserved1  : BFW_NX5_urtx0_reserved1;  /* reserved                                                      */
} NX5_URTX0_BIT_T;

typedef union {
	unsigned int    val;
	NX5_URTX0_BIT_T bf;
} NX5_URTX0_T;

/* --------------------------------------------------------------------- */
/* Register urtx1 */
/* => xMAC1 URX Shared Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_urtx1   0x000000F4U
#define Adr_NX5_xpec0_urtx1 0x018C00F4U
#define Adr_NX5_xpec1_urtx1 0x018C80F4U
#define DFLT_VAL_NX5_urtx1  0x00000000U

#define MSK_NX5_urtx1_urtx_xmac1      0x0000ffffU
#define SRT_NX5_urtx1_urtx_xmac1      0
#define DFLT_VAL_NX5_urtx1_urtx_xmac1 0x00000000U

enum {
	BFW_NX5_urtx1_urtx_xmac1 = 16, /* [15:0] */
	BFW_NX5_urtx1_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_URTX1_BIT_Ttag {
	unsigned int urtx_xmac1 : BFW_NX5_urtx1_urtx_xmac1; /* read access:  Lastly received bits (output of URX_FIFO)       */
	                                                    /* write access: Bits to be transmitted next (input of UTX_FIFO) */
	unsigned int reserved1  : BFW_NX5_urtx1_reserved1;  /* reserved                                                      */
} NX5_URTX1_BIT_T;

typedef union {
	unsigned int    val;
	NX5_URTX1_BIT_T bf;
} NX5_URTX1_T;

/* --------------------------------------------------------------------- */
/* Register urtx2 */
/* => reserved address in net50 */
/*    Shared in xPEC trigger_sample mode with adr_trigger_sample_config (r/w mode). */
/*    Shared in xPEC fmmusm mode with fmmu_read_bit_mask (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_urtx2   0x000000F8U
#define Adr_NX5_xpec0_urtx2 0x018C00F8U
#define Adr_NX5_xpec1_urtx2 0x018C80F8U

/* --------------------------------------------------------------------- */
/* Register urtx3 */
/* => reserved address in net50 */
/*    Shared in xPEC trigger_sample mode with adr_trigger_sample_status (r/w mode). */
/*    Shared in xPEC fmmusm mode with fmmu_write_bit_mask (r mode). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_urtx3   0x000000FCU
#define Adr_NX5_xpec0_urtx3 0x018C00FCU
#define Adr_NX5_xpec1_urtx3 0x018C80FCU

/* --------------------------------------------------------------------- */
/* Register xpu_hold_pc */
/* => xPEC hold_pc register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpu_hold_pc   0x00000100U
#define Adr_NX5_xpec0_xpu_hold_pc 0x018C0100U
#define Adr_NX5_xpec1_xpu_hold_pc 0x018C8100U
#define DFLT_VAL_NX5_xpu_hold_pc  0x00000001U

#define MSK_NX5_xpu_hold_pc_hold      0x00000001U
#define SRT_NX5_xpu_hold_pc_hold      0
#define DFLT_VAL_NX5_xpu_hold_pc_hold 0x00000001U

enum {
	BFW_NX5_xpu_hold_pc_hold      = 1,  /* [0] */
	BFW_NX5_xpu_hold_pc_reserved1 = 31  /* [31:1] */
};

typedef struct NX5_XPU_HOLD_PC_BIT_Ttag {
	unsigned int hold      : BFW_NX5_xpu_hold_pc_hold;      /* 0: start XPU, 1: hold XPU  */
	                                                        /* only accessible by the ARM */
	unsigned int reserved1 : BFW_NX5_xpu_hold_pc_reserved1; /* reserved                   */
} NX5_XPU_HOLD_PC_BIT_T;

typedef union {
	unsigned int          val;
	NX5_XPU_HOLD_PC_BIT_T bf;
} NX5_XPU_HOLD_PC_T;

/* --------------------------------------------------------------------- */
/* Register pram_start */
/* =>  */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pram_start   0x00004000U
#define Adr_NX5_xpec0_pram_start 0x018C4000U
#define Adr_NX5_xpec1_pram_start 0x018CC000U

/* --------------------------------------------------------------------- */
/* Register dram_start */
/* =>  */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_dram_start   0x00006000U
#define Adr_NX5_xpec0_dram_start 0x018C6000U
#define Adr_NX5_xpec1_dram_start 0x018CE000U


/* ===================================================================== */

/* AREA xmac */
/* Area of xmac0, xmac1 */

/* ===================================================================== */

#define Addr_NX5_xmac0    0x018E0000U
#define NX5_NETX_XM0_BASE 0x018E0000U
#define Addr_NX5_xmac1    0x018E1000U
#define NX5_NETX_XM1_BASE 0x018E1000U

/* --------------------------------------------------------------------- */
/* Register xmac_rpu_program_start */
/* => xMAC RPU program-RAM start address. */
/*    The Program-RAM is not addressable for xMAC RPU and TPU ! */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpu_program_start   0x00000000U
#define Adr_NX5_xmac0_xmac_rpu_program_start 0x018E0000U
#define Adr_NX5_xmac1_xmac_rpu_program_start 0x018E1000U

/* --------------------------------------------------------------------- */
/* Register xmac_rpu_program_end */
/* => xMAC RPU program-RAM end address. */
/*    This value is not used by design flow, only for documentation */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpu_program_end   0x000003FFU
#define Adr_NX5_xmac0_xmac_rpu_program_end 0x018E03FFU
#define Adr_NX5_xmac1_xmac_rpu_program_end 0x018E13FFU

/* --------------------------------------------------------------------- */
/* Register xmac_tpu_program_start */
/* => xMAC TPU program-RAM start address. */
/*    The Program-RAM is not addressable for xMAC RPU and TPU ! */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpu_program_start   0x00000400U
#define Adr_NX5_xmac0_xmac_tpu_program_start 0x018E0400U
#define Adr_NX5_xmac1_xmac_tpu_program_start 0x018E1400U

/* --------------------------------------------------------------------- */
/* Register xmac_tpu_program_end */
/* => xMAC TPU program-RAM end address. */
/*    This value is not used by design flow, only for documentation */
/* => Mode:  */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpu_program_end   0x000007FFU
#define Adr_NX5_xmac0_xmac_tpu_program_end 0x018E07FFU
#define Adr_NX5_xmac1_xmac_tpu_program_end 0x018E17FFU

/* --------------------------------------------------------------------- */
/* Register xmac_sr0 */
/* => Shared Work Register 0 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr0   0x00000800U
#define Adr_NX5_xmac0_xmac_sr0 0x018E0800U
#define Adr_NX5_xmac1_xmac_sr0 0x018E1800U
#define DFLT_VAL_NX5_xmac_sr0  0x00000000U

#define MSK_NX5_xmac_sr0_SR0      0x0000ffffU
#define SRT_NX5_xmac_sr0_SR0      0
#define DFLT_VAL_NX5_xmac_sr0_SR0 0x00000000U

enum {
	BFW_NX5_xmac_sr0_SR0       = 16, /* [15:0] */
	BFW_NX5_xmac_sr0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR0_BIT_Ttag {
	unsigned int SR0       : BFW_NX5_xmac_sr0_SR0;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr0_reserved1; /* reserved        */
} NX5_XMAC_SR0_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR0_BIT_T bf;
} NX5_XMAC_SR0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr1 */
/* => Shared Work Register 1 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr1   0x00000804U
#define Adr_NX5_xmac0_xmac_sr1 0x018E0804U
#define Adr_NX5_xmac1_xmac_sr1 0x018E1804U
#define DFLT_VAL_NX5_xmac_sr1  0x00000000U

#define MSK_NX5_xmac_sr1_SR1      0x0000ffffU
#define SRT_NX5_xmac_sr1_SR1      0
#define DFLT_VAL_NX5_xmac_sr1_SR1 0x00000000U

enum {
	BFW_NX5_xmac_sr1_SR1       = 16, /* [15:0] */
	BFW_NX5_xmac_sr1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR1_BIT_Ttag {
	unsigned int SR1       : BFW_NX5_xmac_sr1_SR1;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr1_reserved1; /* reserved        */
} NX5_XMAC_SR1_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR1_BIT_T bf;
} NX5_XMAC_SR1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr2 */
/* => Shared Work Register 2 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr2   0x00000808U
#define Adr_NX5_xmac0_xmac_sr2 0x018E0808U
#define Adr_NX5_xmac1_xmac_sr2 0x018E1808U
#define DFLT_VAL_NX5_xmac_sr2  0x00000000U

#define MSK_NX5_xmac_sr2_SR2      0x0000ffffU
#define SRT_NX5_xmac_sr2_SR2      0
#define DFLT_VAL_NX5_xmac_sr2_SR2 0x00000000U

enum {
	BFW_NX5_xmac_sr2_SR2       = 16, /* [15:0] */
	BFW_NX5_xmac_sr2_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR2_BIT_Ttag {
	unsigned int SR2       : BFW_NX5_xmac_sr2_SR2;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr2_reserved1; /* reserved        */
} NX5_XMAC_SR2_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR2_BIT_T bf;
} NX5_XMAC_SR2_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr3 */
/* => Shared Work Register 3 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr3   0x0000080CU
#define Adr_NX5_xmac0_xmac_sr3 0x018E080CU
#define Adr_NX5_xmac1_xmac_sr3 0x018E180CU
#define DFLT_VAL_NX5_xmac_sr3  0x00000000U

#define MSK_NX5_xmac_sr3_SR3      0x0000ffffU
#define SRT_NX5_xmac_sr3_SR3      0
#define DFLT_VAL_NX5_xmac_sr3_SR3 0x00000000U

enum {
	BFW_NX5_xmac_sr3_SR3       = 16, /* [15:0] */
	BFW_NX5_xmac_sr3_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR3_BIT_Ttag {
	unsigned int SR3       : BFW_NX5_xmac_sr3_SR3;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr3_reserved1; /* reserved        */
} NX5_XMAC_SR3_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR3_BIT_T bf;
} NX5_XMAC_SR3_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr4 */
/* => Shared Work Register 4 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr4   0x00000810U
#define Adr_NX5_xmac0_xmac_sr4 0x018E0810U
#define Adr_NX5_xmac1_xmac_sr4 0x018E1810U
#define DFLT_VAL_NX5_xmac_sr4  0x00000000U

#define MSK_NX5_xmac_sr4_SR4      0x0000ffffU
#define SRT_NX5_xmac_sr4_SR4      0
#define DFLT_VAL_NX5_xmac_sr4_SR4 0x00000000U

enum {
	BFW_NX5_xmac_sr4_SR4       = 16, /* [15:0] */
	BFW_NX5_xmac_sr4_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR4_BIT_Ttag {
	unsigned int SR4       : BFW_NX5_xmac_sr4_SR4;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr4_reserved1; /* reserved        */
} NX5_XMAC_SR4_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR4_BIT_T bf;
} NX5_XMAC_SR4_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr5 */
/* => Shared Work Register 5 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr5   0x00000814U
#define Adr_NX5_xmac0_xmac_sr5 0x018E0814U
#define Adr_NX5_xmac1_xmac_sr5 0x018E1814U
#define DFLT_VAL_NX5_xmac_sr5  0x00000000U

#define MSK_NX5_xmac_sr5_SR5      0x0000ffffU
#define SRT_NX5_xmac_sr5_SR5      0
#define DFLT_VAL_NX5_xmac_sr5_SR5 0x00000000U

enum {
	BFW_NX5_xmac_sr5_SR5       = 16, /* [15:0] */
	BFW_NX5_xmac_sr5_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR5_BIT_Ttag {
	unsigned int SR5       : BFW_NX5_xmac_sr5_SR5;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr5_reserved1; /* reserved        */
} NX5_XMAC_SR5_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR5_BIT_T bf;
} NX5_XMAC_SR5_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr6 */
/* => Shared Work Register 6 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr6   0x00000818U
#define Adr_NX5_xmac0_xmac_sr6 0x018E0818U
#define Adr_NX5_xmac1_xmac_sr6 0x018E1818U
#define DFLT_VAL_NX5_xmac_sr6  0x00000000U

#define MSK_NX5_xmac_sr6_SR6      0x0000ffffU
#define SRT_NX5_xmac_sr6_SR6      0
#define DFLT_VAL_NX5_xmac_sr6_SR6 0x00000000U

enum {
	BFW_NX5_xmac_sr6_SR6       = 16, /* [15:0] */
	BFW_NX5_xmac_sr6_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR6_BIT_Ttag {
	unsigned int SR6       : BFW_NX5_xmac_sr6_SR6;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr6_reserved1; /* reserved        */
} NX5_XMAC_SR6_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR6_BIT_T bf;
} NX5_XMAC_SR6_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr7 */
/* => Shared Work Register 7 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr7   0x0000081CU
#define Adr_NX5_xmac0_xmac_sr7 0x018E081CU
#define Adr_NX5_xmac1_xmac_sr7 0x018E181CU
#define DFLT_VAL_NX5_xmac_sr7  0x00000000U

#define MSK_NX5_xmac_sr7_SR7      0x0000ffffU
#define SRT_NX5_xmac_sr7_SR7      0
#define DFLT_VAL_NX5_xmac_sr7_SR7 0x00000000U

enum {
	BFW_NX5_xmac_sr7_SR7       = 16, /* [15:0] */
	BFW_NX5_xmac_sr7_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR7_BIT_Ttag {
	unsigned int SR7       : BFW_NX5_xmac_sr7_SR7;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr7_reserved1; /* reserved        */
} NX5_XMAC_SR7_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR7_BIT_T bf;
} NX5_XMAC_SR7_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr8 */
/* => Shared Work Register 8 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr8   0x00000820U
#define Adr_NX5_xmac0_xmac_sr8 0x018E0820U
#define Adr_NX5_xmac1_xmac_sr8 0x018E1820U
#define DFLT_VAL_NX5_xmac_sr8  0x00000000U

#define MSK_NX5_xmac_sr8_SR8      0x0000ffffU
#define SRT_NX5_xmac_sr8_SR8      0
#define DFLT_VAL_NX5_xmac_sr8_SR8 0x00000000U

enum {
	BFW_NX5_xmac_sr8_SR8       = 16, /* [15:0] */
	BFW_NX5_xmac_sr8_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR8_BIT_Ttag {
	unsigned int SR8       : BFW_NX5_xmac_sr8_SR8;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr8_reserved1; /* reserved        */
} NX5_XMAC_SR8_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR8_BIT_T bf;
} NX5_XMAC_SR8_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr9 */
/* => Shared Work Register 9 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr9   0x00000824U
#define Adr_NX5_xmac0_xmac_sr9 0x018E0824U
#define Adr_NX5_xmac1_xmac_sr9 0x018E1824U
#define DFLT_VAL_NX5_xmac_sr9  0x00000000U

#define MSK_NX5_xmac_sr9_SR9      0x0000ffffU
#define SRT_NX5_xmac_sr9_SR9      0
#define DFLT_VAL_NX5_xmac_sr9_SR9 0x00000000U

enum {
	BFW_NX5_xmac_sr9_SR9       = 16, /* [15:0] */
	BFW_NX5_xmac_sr9_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR9_BIT_Ttag {
	unsigned int SR9       : BFW_NX5_xmac_sr9_SR9;       /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr9_reserved1; /* reserved        */
} NX5_XMAC_SR9_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_SR9_BIT_T bf;
} NX5_XMAC_SR9_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr10 */
/* => Shared Work Register 10 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr10   0x00000828U
#define Adr_NX5_xmac0_xmac_sr10 0x018E0828U
#define Adr_NX5_xmac1_xmac_sr10 0x018E1828U
#define DFLT_VAL_NX5_xmac_sr10  0x00000000U

#define MSK_NX5_xmac_sr10_SR10      0x0000ffffU
#define SRT_NX5_xmac_sr10_SR10      0
#define DFLT_VAL_NX5_xmac_sr10_SR10 0x00000000U

enum {
	BFW_NX5_xmac_sr10_SR10      = 16, /* [15:0] */
	BFW_NX5_xmac_sr10_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR10_BIT_Ttag {
	unsigned int SR10      : BFW_NX5_xmac_sr10_SR10;      /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr10_reserved1; /* reserved        */
} NX5_XMAC_SR10_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XMAC_SR10_BIT_T bf;
} NX5_XMAC_SR10_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr11 */
/* => Shared Work Register 11 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr11   0x0000082CU
#define Adr_NX5_xmac0_xmac_sr11 0x018E082CU
#define Adr_NX5_xmac1_xmac_sr11 0x018E182CU
#define DFLT_VAL_NX5_xmac_sr11  0x00000000U

#define MSK_NX5_xmac_sr11_SR11      0x0000ffffU
#define SRT_NX5_xmac_sr11_SR11      0
#define DFLT_VAL_NX5_xmac_sr11_SR11 0x00000000U

enum {
	BFW_NX5_xmac_sr11_SR11      = 16, /* [15:0] */
	BFW_NX5_xmac_sr11_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR11_BIT_Ttag {
	unsigned int SR11      : BFW_NX5_xmac_sr11_SR11;      /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr11_reserved1; /* reserved        */
} NX5_XMAC_SR11_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XMAC_SR11_BIT_T bf;
} NX5_XMAC_SR11_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr12 */
/* => Shared Work Register 12 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr12   0x00000830U
#define Adr_NX5_xmac0_xmac_sr12 0x018E0830U
#define Adr_NX5_xmac1_xmac_sr12 0x018E1830U
#define DFLT_VAL_NX5_xmac_sr12  0x00000000U

#define MSK_NX5_xmac_sr12_SR12      0x0000ffffU
#define SRT_NX5_xmac_sr12_SR12      0
#define DFLT_VAL_NX5_xmac_sr12_SR12 0x00000000U

enum {
	BFW_NX5_xmac_sr12_SR12      = 16, /* [15:0] */
	BFW_NX5_xmac_sr12_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR12_BIT_Ttag {
	unsigned int SR12      : BFW_NX5_xmac_sr12_SR12;      /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr12_reserved1; /* reserved        */
} NX5_XMAC_SR12_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XMAC_SR12_BIT_T bf;
} NX5_XMAC_SR12_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr13 */
/* => Shared Work Register 13 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr13   0x00000834U
#define Adr_NX5_xmac0_xmac_sr13 0x018E0834U
#define Adr_NX5_xmac1_xmac_sr13 0x018E1834U
#define DFLT_VAL_NX5_xmac_sr13  0x00000000U

#define MSK_NX5_xmac_sr13_SR13      0x0000ffffU
#define SRT_NX5_xmac_sr13_SR13      0
#define DFLT_VAL_NX5_xmac_sr13_SR13 0x00000000U

enum {
	BFW_NX5_xmac_sr13_SR13      = 16, /* [15:0] */
	BFW_NX5_xmac_sr13_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR13_BIT_Ttag {
	unsigned int SR13      : BFW_NX5_xmac_sr13_SR13;      /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr13_reserved1; /* reserved        */
} NX5_XMAC_SR13_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XMAC_SR13_BIT_T bf;
} NX5_XMAC_SR13_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr14 */
/* => Shared Work Register 14 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr14   0x00000838U
#define Adr_NX5_xmac0_xmac_sr14 0x018E0838U
#define Adr_NX5_xmac1_xmac_sr14 0x018E1838U
#define DFLT_VAL_NX5_xmac_sr14  0x00000000U

#define MSK_NX5_xmac_sr14_SR14      0x0000ffffU
#define SRT_NX5_xmac_sr14_SR14      0
#define DFLT_VAL_NX5_xmac_sr14_SR14 0x00000000U

enum {
	BFW_NX5_xmac_sr14_SR14      = 16, /* [15:0] */
	BFW_NX5_xmac_sr14_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR14_BIT_Ttag {
	unsigned int SR14      : BFW_NX5_xmac_sr14_SR14;      /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr14_reserved1; /* reserved        */
} NX5_XMAC_SR14_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XMAC_SR14_BIT_T bf;
} NX5_XMAC_SR14_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sr15 */
/* => Shared Work Register 15 accessible by all xMACs and xPECs */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sr15   0x0000083CU
#define Adr_NX5_xmac0_xmac_sr15 0x018E083CU
#define Adr_NX5_xmac1_xmac_sr15 0x018E183CU
#define DFLT_VAL_NX5_xmac_sr15  0x00000000U

#define MSK_NX5_xmac_sr15_SR15      0x0000ffffU
#define SRT_NX5_xmac_sr15_SR15      0
#define DFLT_VAL_NX5_xmac_sr15_SR15 0x00000000U

enum {
	BFW_NX5_xmac_sr15_SR15      = 16, /* [15:0] */
	BFW_NX5_xmac_sr15_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SR15_BIT_Ttag {
	unsigned int SR15      : BFW_NX5_xmac_sr15_SR15;      /* Shared Register */
	unsigned int reserved1 : BFW_NX5_xmac_sr15_reserved1; /* reserved        */
} NX5_XMAC_SR15_BIT_T;

typedef union {
	unsigned int        val;
	NX5_XMAC_SR15_BIT_T bf;
} NX5_XMAC_SR15_T;

/* --------------------------------------------------------------------- */
/* Register xmac_status_shared0 */
/* => xMAC0 Shared Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_status_shared0   0x00000840U
#define Adr_NX5_xmac0_xmac_status_shared0 0x018E0840U
#define Adr_NX5_xmac1_xmac_status_shared0 0x018E1840U

#define MSK_NX5_xmac_status_shared0_gpio0_in  0x00000001U
#define SRT_NX5_xmac_status_shared0_gpio0_in  0
#define MSK_NX5_xmac_status_shared0_gpio1_in  0x00000002U
#define SRT_NX5_xmac_status_shared0_gpio1_in  1
#define MSK_NX5_xmac_status_shared0_rx_rdy    0x00000004U
#define SRT_NX5_xmac_status_shared0_rx_rdy    2
#define MSK_NX5_xmac_status_shared0_rx_ovf    0x00000008U
#define SRT_NX5_xmac_status_shared0_rx_ovf    3
#define MSK_NX5_xmac_status_shared0_tx_nxt    0x00000010U
#define SRT_NX5_xmac_status_shared0_tx_nxt    4
#define MSK_NX5_xmac_status_shared0_tx_ufl    0x00000020U
#define SRT_NX5_xmac_status_shared0_tx_ufl    5
#define MSK_NX5_xmac_status_shared0_utx_empty 0x00000040U
#define SRT_NX5_xmac_status_shared0_utx_empty 6
#define MSK_NX5_xmac_status_shared0_brec      0x00000080U
#define SRT_NX5_xmac_status_shared0_brec      7
#define MSK_NX5_xmac_status_shared0_btran     0x00000100U
#define SRT_NX5_xmac_status_shared0_btran     8
#define MSK_NX5_xmac_status_shared0_stat_rpu  0x00000200U
#define SRT_NX5_xmac_status_shared0_stat_rpu  9
#define MSK_NX5_xmac_status_shared0_stat_tpu  0x00000400U
#define SRT_NX5_xmac_status_shared0_stat_tpu  10
#define MSK_NX5_xmac_status_shared0_gpio2_in  0x00001000U
#define SRT_NX5_xmac_status_shared0_gpio2_in  12
#define MSK_NX5_xmac_status_shared0_gpio3_in  0x00002000U
#define SRT_NX5_xmac_status_shared0_gpio3_in  13
#define MSK_NX5_xmac_status_shared0_gpio4_in  0x00004000U
#define SRT_NX5_xmac_status_shared0_gpio4_in  14
#define MSK_NX5_xmac_status_shared0_gpio5_in  0x00008000U
#define SRT_NX5_xmac_status_shared0_gpio5_in  15

enum {
	BFW_NX5_xmac_status_shared0_gpio0_in  = 1,  /* [0] */
	BFW_NX5_xmac_status_shared0_gpio1_in  = 1,  /* [1] */
	BFW_NX5_xmac_status_shared0_rx_rdy    = 1,  /* [2] */
	BFW_NX5_xmac_status_shared0_rx_ovf    = 1,  /* [3] */
	BFW_NX5_xmac_status_shared0_tx_nxt    = 1,  /* [4] */
	BFW_NX5_xmac_status_shared0_tx_ufl    = 1,  /* [5] */
	BFW_NX5_xmac_status_shared0_utx_empty = 1,  /* [6] */
	BFW_NX5_xmac_status_shared0_brec      = 1,  /* [7] */
	BFW_NX5_xmac_status_shared0_btran     = 1,  /* [8] */
	BFW_NX5_xmac_status_shared0_stat_rpu  = 1,  /* [9] */
	BFW_NX5_xmac_status_shared0_stat_tpu  = 1,  /* [10] */
	BFW_NX5_xmac_status_shared0_reserved1 = 1,  /* [11] */
	BFW_NX5_xmac_status_shared0_gpio2_in  = 1,  /* [12] */
	BFW_NX5_xmac_status_shared0_gpio3_in  = 1,  /* [13] */
	BFW_NX5_xmac_status_shared0_gpio4_in  = 1,  /* [14] */
	BFW_NX5_xmac_status_shared0_gpio5_in  = 1,  /* [15] */
	BFW_NX5_xmac_status_shared0_reserved2 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STATUS_SHARED0_BIT_Ttag {
	unsigned int gpio0_in  : BFW_NX5_xmac_status_shared0_gpio0_in;  /* value at external gpio pin                                            */
	unsigned int gpio1_in  : BFW_NX5_xmac_status_shared0_gpio1_in;  /* value at external gpio pin                                            */
	unsigned int rx_rdy    : BFW_NX5_xmac_status_shared0_rx_rdy;    /* received bytes are valid at output of URX_FIFO                        */
	unsigned int rx_ovf    : BFW_NX5_xmac_status_shared0_rx_ovf;    /* receive overflow (too much data in URX_FIFO)                          */
	unsigned int tx_nxt    : BFW_NX5_xmac_status_shared0_tx_nxt;    /* put next tx_word to UTX_FIFO: at least one entry of UTX_FIFO is empty */
	unsigned int tx_ufl    : BFW_NX5_xmac_status_shared0_tx_ufl;    /* transmit underflow (not enough data in UTX_FIFO)                      */
	unsigned int utx_empty : BFW_NX5_xmac_status_shared0_utx_empty; /* UTX_FIFO is empty                                                     */
	unsigned int brec      : BFW_NX5_xmac_status_shared0_brec;      /* bit_received (active for 1 cc)                                        */
	unsigned int btran     : BFW_NX5_xmac_status_shared0_btran;     /* bit_transmitted (active for 1 cc)                                     */
	unsigned int stat_rpu  : BFW_NX5_xmac_status_shared0_stat_rpu;  /* set and reset by RPU command bits                                     */
	unsigned int stat_tpu  : BFW_NX5_xmac_status_shared0_stat_tpu;  /* set and reset by TPU command bits                                     */
	unsigned int reserved1 : BFW_NX5_xmac_status_shared0_reserved1; /* reserved                                                              */
	unsigned int gpio2_in  : BFW_NX5_xmac_status_shared0_gpio2_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int gpio3_in  : BFW_NX5_xmac_status_shared0_gpio3_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int gpio4_in  : BFW_NX5_xmac_status_shared0_gpio4_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int gpio5_in  : BFW_NX5_xmac_status_shared0_gpio5_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int reserved2 : BFW_NX5_xmac_status_shared0_reserved2; /* reserved                                                              */
} NX5_XMAC_STATUS_SHARED0_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_STATUS_SHARED0_BIT_T bf;
} NX5_XMAC_STATUS_SHARED0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_shared0 */
/* => xMAC0 Shared Config Register */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_shared0   0x00000844U
#define Adr_NX5_xmac0_xmac_config_shared0 0x018E0844U
#define Adr_NX5_xmac1_xmac_config_shared0 0x018E1844U
#define DFLT_VAL_NX5_xmac_config_shared0  0x00000000U

#define MSK_NX5_xmac_config_shared0_gpio2_out          0x00000001U
#define SRT_NX5_xmac_config_shared0_gpio2_out          0
#define DFLT_VAL_NX5_xmac_config_shared0_gpio2_out     0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio2_oe           0x00000002U
#define SRT_NX5_xmac_config_shared0_gpio2_oe           1
#define DFLT_VAL_NX5_xmac_config_shared0_gpio2_oe      0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio3_out          0x00000004U
#define SRT_NX5_xmac_config_shared0_gpio3_out          2
#define DFLT_VAL_NX5_xmac_config_shared0_gpio3_out     0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio3_oe           0x00000008U
#define SRT_NX5_xmac_config_shared0_gpio3_oe           3
#define DFLT_VAL_NX5_xmac_config_shared0_gpio3_oe      0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio4_out          0x00000010U
#define SRT_NX5_xmac_config_shared0_gpio4_out          4
#define DFLT_VAL_NX5_xmac_config_shared0_gpio4_out     0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio4_oe           0x00000020U
#define SRT_NX5_xmac_config_shared0_gpio4_oe           5
#define DFLT_VAL_NX5_xmac_config_shared0_gpio4_oe      0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio5_out          0x00000040U
#define SRT_NX5_xmac_config_shared0_gpio5_out          6
#define DFLT_VAL_NX5_xmac_config_shared0_gpio5_out     0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio5_oe           0x00000080U
#define SRT_NX5_xmac_config_shared0_gpio5_oe           7
#define DFLT_VAL_NX5_xmac_config_shared0_gpio5_oe      0x00000000U
#define MSK_NX5_xmac_config_shared0_rx_shift_lr        0x00000100U
#define SRT_NX5_xmac_config_shared0_rx_shift_lr        8
#define DFLT_VAL_NX5_xmac_config_shared0_rx_shift_lr   0x00000000U
#define MSK_NX5_xmac_config_shared0_tx_shift_lr        0x00000200U
#define SRT_NX5_xmac_config_shared0_tx_shift_lr        9
#define DFLT_VAL_NX5_xmac_config_shared0_tx_shift_lr   0x00000000U
#define MSK_NX5_xmac_config_shared0_reset_rx_fifo      0x00000400U
#define SRT_NX5_xmac_config_shared0_reset_rx_fifo      10
#define DFLT_VAL_NX5_xmac_config_shared0_reset_rx_fifo 0x00000000U
#define MSK_NX5_xmac_config_shared0_reset_tx_fifo      0x00000800U
#define SRT_NX5_xmac_config_shared0_reset_tx_fifo      11
#define DFLT_VAL_NX5_xmac_config_shared0_reset_tx_fifo 0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio0_out          0x00001000U
#define SRT_NX5_xmac_config_shared0_gpio0_out          12
#define DFLT_VAL_NX5_xmac_config_shared0_gpio0_out     0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio0_oe           0x00002000U
#define SRT_NX5_xmac_config_shared0_gpio0_oe           13
#define DFLT_VAL_NX5_xmac_config_shared0_gpio0_oe      0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio1_out          0x00004000U
#define SRT_NX5_xmac_config_shared0_gpio1_out          14
#define DFLT_VAL_NX5_xmac_config_shared0_gpio1_out     0x00000000U
#define MSK_NX5_xmac_config_shared0_gpio1_oe           0x00008000U
#define SRT_NX5_xmac_config_shared0_gpio1_oe           15
#define DFLT_VAL_NX5_xmac_config_shared0_gpio1_oe      0x00000000U

enum {
	BFW_NX5_xmac_config_shared0_gpio2_out     = 1,  /* [0] */
	BFW_NX5_xmac_config_shared0_gpio2_oe      = 1,  /* [1] */
	BFW_NX5_xmac_config_shared0_gpio3_out     = 1,  /* [2] */
	BFW_NX5_xmac_config_shared0_gpio3_oe      = 1,  /* [3] */
	BFW_NX5_xmac_config_shared0_gpio4_out     = 1,  /* [4] */
	BFW_NX5_xmac_config_shared0_gpio4_oe      = 1,  /* [5] */
	BFW_NX5_xmac_config_shared0_gpio5_out     = 1,  /* [6] */
	BFW_NX5_xmac_config_shared0_gpio5_oe      = 1,  /* [7] */
	BFW_NX5_xmac_config_shared0_rx_shift_lr   = 1,  /* [8] */
	BFW_NX5_xmac_config_shared0_tx_shift_lr   = 1,  /* [9] */
	BFW_NX5_xmac_config_shared0_reset_rx_fifo = 1,  /* [10] */
	BFW_NX5_xmac_config_shared0_reset_tx_fifo = 1,  /* [11] */
	BFW_NX5_xmac_config_shared0_gpio0_out     = 1,  /* [12] */
	BFW_NX5_xmac_config_shared0_gpio0_oe      = 1,  /* [13] */
	BFW_NX5_xmac_config_shared0_gpio1_out     = 1,  /* [14] */
	BFW_NX5_xmac_config_shared0_gpio1_oe      = 1,  /* [15] */
	BFW_NX5_xmac_config_shared0_reserved1     = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CONFIG_SHARED0_BIT_Ttag {
	unsigned int gpio2_out     : BFW_NX5_xmac_config_shared0_gpio2_out;     /* General Purpose IO 2 output                                                    */
	unsigned int gpio2_oe      : BFW_NX5_xmac_config_shared0_gpio2_oe;      /* General Purpose IO 2 output enable                                             */
	unsigned int gpio3_out     : BFW_NX5_xmac_config_shared0_gpio3_out;     /* General Purpose IO 3 output                                                    */
	unsigned int gpio3_oe      : BFW_NX5_xmac_config_shared0_gpio3_oe;      /* General Purpose IO 3 output enable                                             */
	unsigned int gpio4_out     : BFW_NX5_xmac_config_shared0_gpio4_out;     /* General Purpose IO 4 output                                                    */
	unsigned int gpio4_oe      : BFW_NX5_xmac_config_shared0_gpio4_oe;      /* General Purpose IO 4 output enable                                             */
	unsigned int gpio5_out     : BFW_NX5_xmac_config_shared0_gpio5_out;     /* General Purpose IO 5 output                                                    */
	unsigned int gpio5_oe      : BFW_NX5_xmac_config_shared0_gpio5_oe;      /* General Purpose IO 5 output enable                                             */
	unsigned int rx_shift_lr   : BFW_NX5_xmac_config_shared0_rx_shift_lr;   /* 1: SBU writes incoming bits to position 0 of register rx and shifts rx left,   */
	                                                                        /* 0: SBU writes incoming bits to position 15 of register rx and shifts rx right  */
	unsigned int tx_shift_lr   : BFW_NX5_xmac_config_shared0_tx_shift_lr;   /* 1: OBU reads outgoing bits from position 15 of register tx and shifts tx left, */
	                                                                        /* 0: OBU reads outgoing bits from position 0 of register tx and shifts tx right  */
	unsigned int reset_rx_fifo : BFW_NX5_xmac_config_shared0_reset_rx_fifo; /* reset URX_FIFO and rx_ovf bit inside status_shared register                    */
	unsigned int reset_tx_fifo : BFW_NX5_xmac_config_shared0_reset_tx_fifo; /* reset UTX_FIFO and tx_ufl bit inside status_shared register                    */
	unsigned int gpio0_out     : BFW_NX5_xmac_config_shared0_gpio0_out;     /* General Purpose IO 0 output                                                    */
	unsigned int gpio0_oe      : BFW_NX5_xmac_config_shared0_gpio0_oe;      /* General Purpose IO 0 output enable                                             */
	unsigned int gpio1_out     : BFW_NX5_xmac_config_shared0_gpio1_out;     /* General Purpose IO 1 output                                                    */
	unsigned int gpio1_oe      : BFW_NX5_xmac_config_shared0_gpio1_oe;      /* General Purpose IO 1 output enable                                             */
	unsigned int reserved1     : BFW_NX5_xmac_config_shared0_reserved1;     /* reserved                                                                       */
} NX5_XMAC_CONFIG_SHARED0_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_CONFIG_SHARED0_BIT_T bf;
} NX5_XMAC_CONFIG_SHARED0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_status_shared1 */
/* => xMAC1 Shared Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_status_shared1   0x00000848U
#define Adr_NX5_xmac0_xmac_status_shared1 0x018E0848U
#define Adr_NX5_xmac1_xmac_status_shared1 0x018E1848U

#define MSK_NX5_xmac_status_shared1_gpio0_in  0x00000001U
#define SRT_NX5_xmac_status_shared1_gpio0_in  0
#define MSK_NX5_xmac_status_shared1_gpio1_in  0x00000002U
#define SRT_NX5_xmac_status_shared1_gpio1_in  1
#define MSK_NX5_xmac_status_shared1_rx_rdy    0x00000004U
#define SRT_NX5_xmac_status_shared1_rx_rdy    2
#define MSK_NX5_xmac_status_shared1_rx_ovf    0x00000008U
#define SRT_NX5_xmac_status_shared1_rx_ovf    3
#define MSK_NX5_xmac_status_shared1_tx_nxt    0x00000010U
#define SRT_NX5_xmac_status_shared1_tx_nxt    4
#define MSK_NX5_xmac_status_shared1_tx_ufl    0x00000020U
#define SRT_NX5_xmac_status_shared1_tx_ufl    5
#define MSK_NX5_xmac_status_shared1_utx_empty 0x00000040U
#define SRT_NX5_xmac_status_shared1_utx_empty 6
#define MSK_NX5_xmac_status_shared1_brec      0x00000080U
#define SRT_NX5_xmac_status_shared1_brec      7
#define MSK_NX5_xmac_status_shared1_btran     0x00000100U
#define SRT_NX5_xmac_status_shared1_btran     8
#define MSK_NX5_xmac_status_shared1_stat_rpu  0x00000200U
#define SRT_NX5_xmac_status_shared1_stat_rpu  9
#define MSK_NX5_xmac_status_shared1_stat_tpu  0x00000400U
#define SRT_NX5_xmac_status_shared1_stat_tpu  10
#define MSK_NX5_xmac_status_shared1_gpio2_in  0x00001000U
#define SRT_NX5_xmac_status_shared1_gpio2_in  12
#define MSK_NX5_xmac_status_shared1_gpio3_in  0x00002000U
#define SRT_NX5_xmac_status_shared1_gpio3_in  13
#define MSK_NX5_xmac_status_shared1_gpio4_in  0x00004000U
#define SRT_NX5_xmac_status_shared1_gpio4_in  14
#define MSK_NX5_xmac_status_shared1_gpio5_in  0x00008000U
#define SRT_NX5_xmac_status_shared1_gpio5_in  15

enum {
	BFW_NX5_xmac_status_shared1_gpio0_in  = 1,  /* [0] */
	BFW_NX5_xmac_status_shared1_gpio1_in  = 1,  /* [1] */
	BFW_NX5_xmac_status_shared1_rx_rdy    = 1,  /* [2] */
	BFW_NX5_xmac_status_shared1_rx_ovf    = 1,  /* [3] */
	BFW_NX5_xmac_status_shared1_tx_nxt    = 1,  /* [4] */
	BFW_NX5_xmac_status_shared1_tx_ufl    = 1,  /* [5] */
	BFW_NX5_xmac_status_shared1_utx_empty = 1,  /* [6] */
	BFW_NX5_xmac_status_shared1_brec      = 1,  /* [7] */
	BFW_NX5_xmac_status_shared1_btran     = 1,  /* [8] */
	BFW_NX5_xmac_status_shared1_stat_rpu  = 1,  /* [9] */
	BFW_NX5_xmac_status_shared1_stat_tpu  = 1,  /* [10] */
	BFW_NX5_xmac_status_shared1_reserved1 = 1,  /* [11] */
	BFW_NX5_xmac_status_shared1_gpio2_in  = 1,  /* [12] */
	BFW_NX5_xmac_status_shared1_gpio3_in  = 1,  /* [13] */
	BFW_NX5_xmac_status_shared1_gpio4_in  = 1,  /* [14] */
	BFW_NX5_xmac_status_shared1_gpio5_in  = 1,  /* [15] */
	BFW_NX5_xmac_status_shared1_reserved2 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STATUS_SHARED1_BIT_Ttag {
	unsigned int gpio0_in  : BFW_NX5_xmac_status_shared1_gpio0_in;  /* value at external gpio pin                                            */
	unsigned int gpio1_in  : BFW_NX5_xmac_status_shared1_gpio1_in;  /* value at external gpio pin                                            */
	unsigned int rx_rdy    : BFW_NX5_xmac_status_shared1_rx_rdy;    /* received bytes are valid at output of URX_FIFO                        */
	unsigned int rx_ovf    : BFW_NX5_xmac_status_shared1_rx_ovf;    /* receive overflow (too much data in URX_FIFO)                          */
	unsigned int tx_nxt    : BFW_NX5_xmac_status_shared1_tx_nxt;    /* put next tx_word to UTX_FIFO: at least one entry of UTX_FIFO is empty */
	unsigned int tx_ufl    : BFW_NX5_xmac_status_shared1_tx_ufl;    /* transmit underflow (not enough data in UTX_FIFO)                      */
	unsigned int utx_empty : BFW_NX5_xmac_status_shared1_utx_empty; /* UTX_FIFO is empty                                                     */
	unsigned int brec      : BFW_NX5_xmac_status_shared1_brec;      /* bit_received (active for 1 cc)                                        */
	unsigned int btran     : BFW_NX5_xmac_status_shared1_btran;     /* bit_transmitted (active for 1 cc)                                     */
	unsigned int stat_rpu  : BFW_NX5_xmac_status_shared1_stat_rpu;  /* set and reset by RPU command bits                                     */
	unsigned int stat_tpu  : BFW_NX5_xmac_status_shared1_stat_tpu;  /* set and reset by TPU command bits                                     */
	unsigned int reserved1 : BFW_NX5_xmac_status_shared1_reserved1; /* reserved                                                              */
	unsigned int gpio2_in  : BFW_NX5_xmac_status_shared1_gpio2_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int gpio3_in  : BFW_NX5_xmac_status_shared1_gpio3_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int gpio4_in  : BFW_NX5_xmac_status_shared1_gpio4_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int gpio5_in  : BFW_NX5_xmac_status_shared1_gpio5_in;  /* value at external gpio pin, also used for external PHY LED            */
	unsigned int reserved2 : BFW_NX5_xmac_status_shared1_reserved2; /* reserved                                                              */
} NX5_XMAC_STATUS_SHARED1_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_STATUS_SHARED1_BIT_T bf;
} NX5_XMAC_STATUS_SHARED1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_shared1 */
/* => xMAC1 Shared Config Register */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_shared1   0x0000084CU
#define Adr_NX5_xmac0_xmac_config_shared1 0x018E084CU
#define Adr_NX5_xmac1_xmac_config_shared1 0x018E184CU
#define DFLT_VAL_NX5_xmac_config_shared1  0x00000000U

#define MSK_NX5_xmac_config_shared1_gpio2_out          0x00000001U
#define SRT_NX5_xmac_config_shared1_gpio2_out          0
#define DFLT_VAL_NX5_xmac_config_shared1_gpio2_out     0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio2_oe           0x00000002U
#define SRT_NX5_xmac_config_shared1_gpio2_oe           1
#define DFLT_VAL_NX5_xmac_config_shared1_gpio2_oe      0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio3_out          0x00000004U
#define SRT_NX5_xmac_config_shared1_gpio3_out          2
#define DFLT_VAL_NX5_xmac_config_shared1_gpio3_out     0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio3_oe           0x00000008U
#define SRT_NX5_xmac_config_shared1_gpio3_oe           3
#define DFLT_VAL_NX5_xmac_config_shared1_gpio3_oe      0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio4_out          0x00000010U
#define SRT_NX5_xmac_config_shared1_gpio4_out          4
#define DFLT_VAL_NX5_xmac_config_shared1_gpio4_out     0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio4_oe           0x00000020U
#define SRT_NX5_xmac_config_shared1_gpio4_oe           5
#define DFLT_VAL_NX5_xmac_config_shared1_gpio4_oe      0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio5_out          0x00000040U
#define SRT_NX5_xmac_config_shared1_gpio5_out          6
#define DFLT_VAL_NX5_xmac_config_shared1_gpio5_out     0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio5_oe           0x00000080U
#define SRT_NX5_xmac_config_shared1_gpio5_oe           7
#define DFLT_VAL_NX5_xmac_config_shared1_gpio5_oe      0x00000000U
#define MSK_NX5_xmac_config_shared1_rx_shift_lr        0x00000100U
#define SRT_NX5_xmac_config_shared1_rx_shift_lr        8
#define DFLT_VAL_NX5_xmac_config_shared1_rx_shift_lr   0x00000000U
#define MSK_NX5_xmac_config_shared1_tx_shift_lr        0x00000200U
#define SRT_NX5_xmac_config_shared1_tx_shift_lr        9
#define DFLT_VAL_NX5_xmac_config_shared1_tx_shift_lr   0x00000000U
#define MSK_NX5_xmac_config_shared1_reset_rx_fifo      0x00000400U
#define SRT_NX5_xmac_config_shared1_reset_rx_fifo      10
#define DFLT_VAL_NX5_xmac_config_shared1_reset_rx_fifo 0x00000000U
#define MSK_NX5_xmac_config_shared1_reset_tx_fifo      0x00000800U
#define SRT_NX5_xmac_config_shared1_reset_tx_fifo      11
#define DFLT_VAL_NX5_xmac_config_shared1_reset_tx_fifo 0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio0_out          0x00001000U
#define SRT_NX5_xmac_config_shared1_gpio0_out          12
#define DFLT_VAL_NX5_xmac_config_shared1_gpio0_out     0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio0_oe           0x00002000U
#define SRT_NX5_xmac_config_shared1_gpio0_oe           13
#define DFLT_VAL_NX5_xmac_config_shared1_gpio0_oe      0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio1_out          0x00004000U
#define SRT_NX5_xmac_config_shared1_gpio1_out          14
#define DFLT_VAL_NX5_xmac_config_shared1_gpio1_out     0x00000000U
#define MSK_NX5_xmac_config_shared1_gpio1_oe           0x00008000U
#define SRT_NX5_xmac_config_shared1_gpio1_oe           15
#define DFLT_VAL_NX5_xmac_config_shared1_gpio1_oe      0x00000000U

enum {
	BFW_NX5_xmac_config_shared1_gpio2_out     = 1,  /* [0] */
	BFW_NX5_xmac_config_shared1_gpio2_oe      = 1,  /* [1] */
	BFW_NX5_xmac_config_shared1_gpio3_out     = 1,  /* [2] */
	BFW_NX5_xmac_config_shared1_gpio3_oe      = 1,  /* [3] */
	BFW_NX5_xmac_config_shared1_gpio4_out     = 1,  /* [4] */
	BFW_NX5_xmac_config_shared1_gpio4_oe      = 1,  /* [5] */
	BFW_NX5_xmac_config_shared1_gpio5_out     = 1,  /* [6] */
	BFW_NX5_xmac_config_shared1_gpio5_oe      = 1,  /* [7] */
	BFW_NX5_xmac_config_shared1_rx_shift_lr   = 1,  /* [8] */
	BFW_NX5_xmac_config_shared1_tx_shift_lr   = 1,  /* [9] */
	BFW_NX5_xmac_config_shared1_reset_rx_fifo = 1,  /* [10] */
	BFW_NX5_xmac_config_shared1_reset_tx_fifo = 1,  /* [11] */
	BFW_NX5_xmac_config_shared1_gpio0_out     = 1,  /* [12] */
	BFW_NX5_xmac_config_shared1_gpio0_oe      = 1,  /* [13] */
	BFW_NX5_xmac_config_shared1_gpio1_out     = 1,  /* [14] */
	BFW_NX5_xmac_config_shared1_gpio1_oe      = 1,  /* [15] */
	BFW_NX5_xmac_config_shared1_reserved1     = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CONFIG_SHARED1_BIT_Ttag {
	unsigned int gpio2_out     : BFW_NX5_xmac_config_shared1_gpio2_out;     /* General Purpose IO 2 output                                                    */
	unsigned int gpio2_oe      : BFW_NX5_xmac_config_shared1_gpio2_oe;      /* General Purpose IO 2 output enable                                             */
	unsigned int gpio3_out     : BFW_NX5_xmac_config_shared1_gpio3_out;     /* General Purpose IO 3 output                                                    */
	unsigned int gpio3_oe      : BFW_NX5_xmac_config_shared1_gpio3_oe;      /* General Purpose IO 3 output enable                                             */
	unsigned int gpio4_out     : BFW_NX5_xmac_config_shared1_gpio4_out;     /* General Purpose IO 4 output                                                    */
	unsigned int gpio4_oe      : BFW_NX5_xmac_config_shared1_gpio4_oe;      /* General Purpose IO 4 output enable                                             */
	unsigned int gpio5_out     : BFW_NX5_xmac_config_shared1_gpio5_out;     /* General Purpose IO 5 output                                                    */
	unsigned int gpio5_oe      : BFW_NX5_xmac_config_shared1_gpio5_oe;      /* General Purpose IO 5 output enable                                             */
	unsigned int rx_shift_lr   : BFW_NX5_xmac_config_shared1_rx_shift_lr;   /* 1: SBU writes incoming bits to position 0 of register rx and shifts rx left,   */
	                                                                        /* 0: SBU writes incoming bits to position 15 of register rx and shifts rx right  */
	unsigned int tx_shift_lr   : BFW_NX5_xmac_config_shared1_tx_shift_lr;   /* 1: OBU reads outgoing bits from position 15 of register tx and shifts tx left, */
	                                                                        /* 0: OBU reads outgoing bits from position 0 of register tx and shifts tx right  */
	unsigned int reset_rx_fifo : BFW_NX5_xmac_config_shared1_reset_rx_fifo; /* reset URX_FIFO and rx_ovf bit inside status_shared register                    */
	unsigned int reset_tx_fifo : BFW_NX5_xmac_config_shared1_reset_tx_fifo; /* reset UTX_FIFO and tx_ufl bit inside status_shared register                    */
	unsigned int gpio0_out     : BFW_NX5_xmac_config_shared1_gpio0_out;     /* General Purpose IO 0 output                                                    */
	unsigned int gpio0_oe      : BFW_NX5_xmac_config_shared1_gpio0_oe;      /* General Purpose IO 0 output enable                                             */
	unsigned int gpio1_out     : BFW_NX5_xmac_config_shared1_gpio1_out;     /* General Purpose IO 1 output                                                    */
	unsigned int gpio1_oe      : BFW_NX5_xmac_config_shared1_gpio1_oe;      /* General Purpose IO 1 output enable                                             */
	unsigned int reserved1     : BFW_NX5_xmac_config_shared1_reserved1;     /* reserved                                                                       */
} NX5_XMAC_CONFIG_SHARED1_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_CONFIG_SHARED1_BIT_T bf;
} NX5_XMAC_CONFIG_SHARED1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_urx_utx0 */
/* => xMAC0 URX/UTX Shared Register FIFO */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_urx_utx0   0x00000860U
#define Adr_NX5_xmac0_xmac_urx_utx0 0x018E0860U
#define Adr_NX5_xmac1_xmac_urx_utx0 0x018E1860U
#define DFLT_VAL_NX5_xmac_urx_utx0  0x00000000U

#define MSK_NX5_xmac_urx_utx0_UTX_XMAC0      0x0000ffffU
#define SRT_NX5_xmac_urx_utx0_UTX_XMAC0      0
#define DFLT_VAL_NX5_xmac_urx_utx0_UTX_XMAC0 0x00000000U

enum {
	BFW_NX5_xmac_urx_utx0_UTX_XMAC0 = 16, /* [15:0] */
	BFW_NX5_xmac_urx_utx0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_URX_UTX0_BIT_Ttag {
	unsigned int UTX_XMAC0 : BFW_NX5_xmac_urx_utx0_UTX_XMAC0; /* read access:  Lastly received bits (output of URX_FIFO)       */
	                                                          /* write access: Bits to be transmitted next (input of UTX_FIFO) */
	unsigned int reserved1 : BFW_NX5_xmac_urx_utx0_reserved1; /* reserved                                                      */
} NX5_XMAC_URX_UTX0_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_URX_UTX0_BIT_T bf;
} NX5_XMAC_URX_UTX0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_urx_utx1 */
/* => xMAC1 URX/UTX Shared Register FIFO */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_urx_utx1   0x00000864U
#define Adr_NX5_xmac0_xmac_urx_utx1 0x018E0864U
#define Adr_NX5_xmac1_xmac_urx_utx1 0x018E1864U
#define DFLT_VAL_NX5_xmac_urx_utx1  0x00000000U

#define MSK_NX5_xmac_urx_utx1_UTX_XMAC1      0x0000ffffU
#define SRT_NX5_xmac_urx_utx1_UTX_XMAC1      0
#define DFLT_VAL_NX5_xmac_urx_utx1_UTX_XMAC1 0x00000000U

enum {
	BFW_NX5_xmac_urx_utx1_UTX_XMAC1 = 16, /* [15:0] */
	BFW_NX5_xmac_urx_utx1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_URX_UTX1_BIT_Ttag {
	unsigned int UTX_XMAC1 : BFW_NX5_xmac_urx_utx1_UTX_XMAC1; /* read access:  Lastly received bits (output of URX_FIFO)       */
	                                                          /* write access: Bits to be transmitted next (input of UTX_FIFO) */
	unsigned int reserved1 : BFW_NX5_xmac_urx_utx1_reserved1; /* reserved                                                      */
} NX5_XMAC_URX_UTX1_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_URX_UTX1_BIT_T bf;
} NX5_XMAC_URX_UTX1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_urx */
/* => xMAC URX FIFO input */
/*    URX FIFO is part of xMAC. It can be read (output) by all xMACs and xPECs, but only written (input) by the xMAC it belongs to. */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_urx   0x00000870U
#define Adr_NX5_xmac0_xmac_urx 0x018E0870U
#define Adr_NX5_xmac1_xmac_urx 0x018E1870U
#define DFLT_VAL_NX5_xmac_urx  0x00000000U

#define MSK_NX5_xmac_urx_urx      0x0000ffffU
#define SRT_NX5_xmac_urx_urx      0
#define DFLT_VAL_NX5_xmac_urx_urx 0x00000000U

enum {
	BFW_NX5_xmac_urx_urx       = 16, /* [15:0] */
	BFW_NX5_xmac_urx_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_URX_BIT_Ttag {
	unsigned int urx       : BFW_NX5_xmac_urx_urx;       /* Lastly received bits to be transmitted to xPEC (input of URX_FIFO) */
	unsigned int reserved1 : BFW_NX5_xmac_urx_reserved1; /* reserved                                                           */
} NX5_XMAC_URX_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_URX_BIT_T bf;
} NX5_XMAC_URX_T;

/* --------------------------------------------------------------------- */
/* Register xmac_utx */
/* => xMAC UTX FIFO output */
/*    UTX FIFO is part of xMAC. It can be written (input) by all xMACs and xPECs, but only read (output) by the xMAC it belongs to. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_utx   0x00000874U
#define Adr_NX5_xmac0_xmac_utx 0x018E0874U
#define Adr_NX5_xmac1_xmac_utx 0x018E1874U

#define MSK_NX5_xmac_utx_utx 0x0000ffffU
#define SRT_NX5_xmac_utx_utx 0

enum {
	BFW_NX5_xmac_utx_utx       = 16, /* [15:0] */
	BFW_NX5_xmac_utx_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_UTX_BIT_Ttag {
	unsigned int utx       : BFW_NX5_xmac_utx_utx;       /* Bits to be transmitted next (output of UTX_FIFO)                             */
	                                                     /* read as src2 allows multiple reads, only read as src1 will change FIFO state */
	unsigned int reserved1 : BFW_NX5_xmac_utx_reserved1; /* reserved                                                                     */
} NX5_XMAC_UTX_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_UTX_BIT_T bf;
} NX5_XMAC_UTX_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx */
/* => xMAC RX Register */
/*    Sampled bits from SBU are collected in this register, */
/*    i.e. if a new bit arrives from SBU (sync), other bits are shifted (direction programmable). */
/*    Same behavior in MII-Modes (4 bits arrive in parallel and the other bits are shifted by 4). */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx   0x00000878U
#define Adr_NX5_xmac0_xmac_rx 0x018E0878U
#define Adr_NX5_xmac1_xmac_rx 0x018E1878U

#define MSK_NX5_xmac_rx_rx 0x0000ffffU
#define SRT_NX5_xmac_rx_rx 0

enum {
	BFW_NX5_xmac_rx_rx        = 16, /* [15:0] */
	BFW_NX5_xmac_rx_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_BIT_Ttag {
	unsigned int rx        : BFW_NX5_xmac_rx_rx;        /* 16 previously received bits */
	unsigned int reserved1 : BFW_NX5_xmac_rx_reserved1; /* reserved                    */
} NX5_XMAC_RX_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XMAC_RX_BIT_T bf;
} NX5_XMAC_RX_T;

/* --------------------------------------------------------------------- */
/* Register xmac_other_rx */
/* => RX Register of other xMAC. */
/*    Used for fast forward of data between 2 xMACs (specially in MII-HUB-mode) */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_other_rx   0x0000087CU
#define Adr_NX5_xmac0_xmac_other_rx 0x018E087CU
#define Adr_NX5_xmac1_xmac_other_rx 0x018E187CU

#define MSK_NX5_xmac_other_rx_rx 0x0000ffffU
#define SRT_NX5_xmac_other_rx_rx 0

enum {
	BFW_NX5_xmac_other_rx_rx        = 16, /* [15:0] */
	BFW_NX5_xmac_other_rx_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_OTHER_RX_BIT_Ttag {
	unsigned int rx        : BFW_NX5_xmac_other_rx_rx;        /* 16 previously received bits of other xMAC */
	unsigned int reserved1 : BFW_NX5_xmac_other_rx_reserved1; /* reserved                                  */
} NX5_XMAC_OTHER_RX_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_OTHER_RX_BIT_T bf;
} NX5_XMAC_OTHER_RX_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_hw */
/* => xMAC RX_HW Register */
/*    rx_hw bit in RPU-code writes actually received bit from rx to this register. */
/*    Useful in case of bitwise format, to collect source bits from raw input bitstream (e.g. in HDLC-coding). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_hw   0x00000880U
#define Adr_NX5_xmac0_xmac_rx_hw 0x018E0880U
#define Adr_NX5_xmac1_xmac_rx_hw 0x018E1880U
#define DFLT_VAL_NX5_xmac_rx_hw  0x00000000U

#define MSK_NX5_xmac_rx_hw_rx_hw      0x0000ffffU
#define SRT_NX5_xmac_rx_hw_rx_hw      0
#define DFLT_VAL_NX5_xmac_rx_hw_rx_hw 0x00000000U

enum {
	BFW_NX5_xmac_rx_hw_rx_hw     = 16, /* [15:0] */
	BFW_NX5_xmac_rx_hw_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_HW_BIT_Ttag {
	unsigned int rx_hw     : BFW_NX5_xmac_rx_hw_rx_hw;     /* collected source bits from raw input bitstream                        */
	                                                       /* same orientation of bits as in rx register (depending on rx_shift_lr) */
	unsigned int reserved1 : BFW_NX5_xmac_rx_hw_reserved1; /* reserved                                                              */
} NX5_XMAC_RX_HW_BIT_T;

typedef union {
	unsigned int         val;
	NX5_XMAC_RX_HW_BIT_T bf;
} NX5_XMAC_RX_HW_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_hw_count */
/* => xMAC RX_HW_COUNT Register */
/*    Counts bits collected by rx_hw bit RPU-code. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_hw_count   0x00000884U
#define Adr_NX5_xmac0_xmac_rx_hw_count 0x018E0884U
#define Adr_NX5_xmac1_xmac_rx_hw_count 0x018E1884U
#define DFLT_VAL_NX5_xmac_rx_hw_count  0x00000000U

#define MSK_NX5_xmac_rx_hw_count_rx_hw_count      0x0000ffffU
#define SRT_NX5_xmac_rx_hw_count_rx_hw_count      0
#define DFLT_VAL_NX5_xmac_rx_hw_count_rx_hw_count 0x00000000U

enum {
	BFW_NX5_xmac_rx_hw_count_rx_hw_count = 16, /* [15:0] */
	BFW_NX5_xmac_rx_hw_count_reserved1   = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_HW_COUNT_BIT_Ttag {
	unsigned int rx_hw_count : BFW_NX5_xmac_rx_hw_count_rx_hw_count; /* counts down with rx_hw in RPU-code                               */
	                                                                 /* (from rx_nof_bits-1 to 0, 16-bit downcounter if rx_nof_bits = 0) */
	unsigned int reserved1   : BFW_NX5_xmac_rx_hw_count_reserved1;   /* reserved                                                         */
} NX5_XMAC_RX_HW_COUNT_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_RX_HW_COUNT_BIT_T bf;
} NX5_XMAC_RX_HW_COUNT_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx */
/* => xMAC TX Register */
/*    Transmitted bits read automatically by OBU from this register, */
/*    i.e. if a bit is send (sync), other bits are rotated accordingly (direction programmable). */
/*    Same behavior in MII-Modes (4 bits arrive in parallel and the other bits are rotated by 4). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx   0x00000888U
#define Adr_NX5_xmac0_xmac_tx 0x018E0888U
#define Adr_NX5_xmac1_xmac_tx 0x018E1888U
#define DFLT_VAL_NX5_xmac_tx  0x00000000U

#define MSK_NX5_xmac_tx_tx      0x0000ffffU
#define SRT_NX5_xmac_tx_tx      0
#define DFLT_VAL_NX5_xmac_tx_tx 0x00000000U

enum {
	BFW_NX5_xmac_tx_tx        = 16, /* [15:0] */
	BFW_NX5_xmac_tx_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_BIT_Ttag {
	unsigned int tx        : BFW_NX5_xmac_tx_tx;        /* to be transmitted bits                                */
	                                                    /* bit 0  is transmitted next in case of tx_shift_lr = 0 */
	unsigned int reserved1 : BFW_NX5_xmac_tx_reserved1; /* reserved                                              */
} NX5_XMAC_TX_BIT_T;

typedef union {
	unsigned int      val;
	NX5_XMAC_TX_BIT_T bf;
} NX5_XMAC_TX_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_hw */
/* => xMAC TX_HW Register */
/*    tx_hw bit in TPU-code writes to be transmitted bit in tx register from this register */
/*    Useful in case of bitwise format, to insert source bits into output bitstream. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_hw   0x0000088CU
#define Adr_NX5_xmac0_xmac_tx_hw 0x018E088CU
#define Adr_NX5_xmac1_xmac_tx_hw 0x018E188CU
#define DFLT_VAL_NX5_xmac_tx_hw  0x00000000U

#define MSK_NX5_xmac_tx_hw_tx_hw      0x0000ffffU
#define SRT_NX5_xmac_tx_hw_tx_hw      0
#define DFLT_VAL_NX5_xmac_tx_hw_tx_hw 0x00000000U

enum {
	BFW_NX5_xmac_tx_hw_tx_hw     = 16, /* [15:0] */
	BFW_NX5_xmac_tx_hw_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_HW_BIT_Ttag {
	unsigned int tx_hw     : BFW_NX5_xmac_tx_hw_tx_hw;     /* bits to be inserted into output bitstream                             */
	                                                       /* same orientation of bits as in tx register (depending on tx_shift_lr) */
	unsigned int reserved1 : BFW_NX5_xmac_tx_hw_reserved1; /* reserved                                                              */
} NX5_XMAC_TX_HW_BIT_T;

typedef union {
	unsigned int         val;
	NX5_XMAC_TX_HW_BIT_T bf;
} NX5_XMAC_TX_HW_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_hw_count */
/* => xMAC TX_HW_COUNT Register */
/*    Counts bits collected by tx_hw bit TPU-code. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_hw_count   0x00000890U
#define Adr_NX5_xmac0_xmac_tx_hw_count 0x018E0890U
#define Adr_NX5_xmac1_xmac_tx_hw_count 0x018E1890U
#define DFLT_VAL_NX5_xmac_tx_hw_count  0x00000000U

#define MSK_NX5_xmac_tx_hw_count_tx_hw_count      0x0000ffffU
#define SRT_NX5_xmac_tx_hw_count_tx_hw_count      0
#define DFLT_VAL_NX5_xmac_tx_hw_count_tx_hw_count 0x00000000U

enum {
	BFW_NX5_xmac_tx_hw_count_tx_hw_count = 16, /* [15:0] */
	BFW_NX5_xmac_tx_hw_count_reserved1   = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_HW_COUNT_BIT_Ttag {
	unsigned int tx_hw_count : BFW_NX5_xmac_tx_hw_count_tx_hw_count; /* counts down with tx_hw in TPU-code                               */
	                                                                 /* (from tx_nof_bits-1 to 0, 16-bit downcounter if tx_nof_bits = 0) */
	unsigned int reserved1   : BFW_NX5_xmac_tx_hw_count_reserved1;   /* reserved                                                         */
} NX5_XMAC_TX_HW_COUNT_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_TX_HW_COUNT_BIT_T bf;
} NX5_XMAC_TX_HW_COUNT_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_sent */
/* => xMAC TX Sent Register */
/*    Collects already transmitted bits. */
/*    Useful for pattern match. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_sent   0x00000894U
#define Adr_NX5_xmac0_xmac_tx_sent 0x018E0894U
#define Adr_NX5_xmac1_xmac_tx_sent 0x018E1894U
#define DFLT_VAL_NX5_xmac_tx_sent  0x00000000U

#define MSK_NX5_xmac_tx_sent_tx_sent      0x0000ffffU
#define SRT_NX5_xmac_tx_sent_tx_sent      0
#define DFLT_VAL_NX5_xmac_tx_sent_tx_sent 0x00000000U

enum {
	BFW_NX5_xmac_tx_sent_tx_sent   = 16, /* [15:0] */
	BFW_NX5_xmac_tx_sent_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_SENT_BIT_Ttag {
	unsigned int tx_sent   : BFW_NX5_xmac_tx_sent_tx_sent;   /* already transmitted bits,                                          */
	                                                         /* bit 15 is always the oldest bit (shift direction not programmable) */
	unsigned int reserved1 : BFW_NX5_xmac_tx_sent_reserved1; /* reserved                                                           */
} NX5_XMAC_TX_SENT_BIT_T;

typedef union {
	unsigned int           val;
	NX5_XMAC_TX_SENT_BIT_T bf;
} NX5_XMAC_TX_SENT_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpu_pc */
/* => RPU Progamm counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpu_pc   0x00000898U
#define Adr_NX5_xmac0_xmac_rpu_pc 0x018E0898U
#define Adr_NX5_xmac1_xmac_rpu_pc 0x018E1898U
#define DFLT_VAL_NX5_xmac_rpu_pc  0x00000000U

#define MSK_NX5_xmac_rpu_pc_rpu_pc      0x0000007fU
#define SRT_NX5_xmac_rpu_pc_rpu_pc      0
#define DFLT_VAL_NX5_xmac_rpu_pc_rpu_pc 0x00000000U

enum {
	BFW_NX5_xmac_rpu_pc_rpu_pc    = 7,  /* [6:0] */
	BFW_NX5_xmac_rpu_pc_reserved1 = 25  /* [31:7] */
};

typedef struct NX5_XMAC_RPU_PC_BIT_Ttag {
	unsigned int rpu_pc    : BFW_NX5_xmac_rpu_pc_rpu_pc;    /* Program Counter of RPU */
	unsigned int reserved1 : BFW_NX5_xmac_rpu_pc_reserved1; /* reserved               */
} NX5_XMAC_RPU_PC_BIT_T;

typedef union {
	unsigned int          val;
	NX5_XMAC_RPU_PC_BIT_T bf;
} NX5_XMAC_RPU_PC_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpu_pc */
/* => TPU Progamm counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpu_pc   0x0000089CU
#define Adr_NX5_xmac0_xmac_tpu_pc 0x018E089CU
#define Adr_NX5_xmac1_xmac_tpu_pc 0x018E189CU
#define DFLT_VAL_NX5_xmac_tpu_pc  0x00000000U

#define MSK_NX5_xmac_tpu_pc_tpu_pc      0x0000007fU
#define SRT_NX5_xmac_tpu_pc_tpu_pc      0
#define DFLT_VAL_NX5_xmac_tpu_pc_tpu_pc 0x00000000U

enum {
	BFW_NX5_xmac_tpu_pc_tpu_pc    = 7,  /* [6:0] */
	BFW_NX5_xmac_tpu_pc_reserved1 = 25  /* [31:7] */
};

typedef struct NX5_XMAC_TPU_PC_BIT_Ttag {
	unsigned int tpu_pc    : BFW_NX5_xmac_tpu_pc_tpu_pc;    /* Program Counter of TPU */
	unsigned int reserved1 : BFW_NX5_xmac_tpu_pc_reserved1; /* reserved               */
} NX5_XMAC_TPU_PC_BIT_T;

typedef union {
	unsigned int          val;
	NX5_XMAC_TPU_PC_BIT_T bf;
} NX5_XMAC_TPU_PC_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr0 */
/* => xMAC internal Work Register 0 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr0   0x000008A0U
#define Adr_NX5_xmac0_xmac_wr0 0x018E08A0U
#define Adr_NX5_xmac1_xmac_wr0 0x018E18A0U
#define DFLT_VAL_NX5_xmac_wr0  0x00000000U

#define MSK_NX5_xmac_wr0_WR0      0x0000ffffU
#define SRT_NX5_xmac_wr0_WR0      0
#define DFLT_VAL_NX5_xmac_wr0_WR0 0x00000000U

enum {
	BFW_NX5_xmac_wr0_WR0       = 16, /* [15:0] */
	BFW_NX5_xmac_wr0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR0_BIT_Ttag {
	unsigned int WR0       : BFW_NX5_xmac_wr0_WR0;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr0_reserved1; /* reserved      */
} NX5_XMAC_WR0_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR0_BIT_T bf;
} NX5_XMAC_WR0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr1 */
/* => xMAC internal Work Register 1 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr1   0x000008A4U
#define Adr_NX5_xmac0_xmac_wr1 0x018E08A4U
#define Adr_NX5_xmac1_xmac_wr1 0x018E18A4U
#define DFLT_VAL_NX5_xmac_wr1  0x00000000U

#define MSK_NX5_xmac_wr1_WR1      0x0000ffffU
#define SRT_NX5_xmac_wr1_WR1      0
#define DFLT_VAL_NX5_xmac_wr1_WR1 0x00000000U

enum {
	BFW_NX5_xmac_wr1_WR1       = 16, /* [15:0] */
	BFW_NX5_xmac_wr1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR1_BIT_Ttag {
	unsigned int WR1       : BFW_NX5_xmac_wr1_WR1;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr1_reserved1; /* reserved      */
} NX5_XMAC_WR1_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR1_BIT_T bf;
} NX5_XMAC_WR1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr2 */
/* => xMAC internal Work Register 2 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr2   0x000008A8U
#define Adr_NX5_xmac0_xmac_wr2 0x018E08A8U
#define Adr_NX5_xmac1_xmac_wr2 0x018E18A8U
#define DFLT_VAL_NX5_xmac_wr2  0x00000000U

#define MSK_NX5_xmac_wr2_WR2      0x0000ffffU
#define SRT_NX5_xmac_wr2_WR2      0
#define DFLT_VAL_NX5_xmac_wr2_WR2 0x00000000U

enum {
	BFW_NX5_xmac_wr2_WR2       = 16, /* [15:0] */
	BFW_NX5_xmac_wr2_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR2_BIT_Ttag {
	unsigned int WR2       : BFW_NX5_xmac_wr2_WR2;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr2_reserved1; /* reserved      */
} NX5_XMAC_WR2_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR2_BIT_T bf;
} NX5_XMAC_WR2_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr3 */
/* => xMAC internal Work Register 3 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr3   0x000008ACU
#define Adr_NX5_xmac0_xmac_wr3 0x018E08ACU
#define Adr_NX5_xmac1_xmac_wr3 0x018E18ACU
#define DFLT_VAL_NX5_xmac_wr3  0x00000000U

#define MSK_NX5_xmac_wr3_WR3      0x0000ffffU
#define SRT_NX5_xmac_wr3_WR3      0
#define DFLT_VAL_NX5_xmac_wr3_WR3 0x00000000U

enum {
	BFW_NX5_xmac_wr3_WR3       = 16, /* [15:0] */
	BFW_NX5_xmac_wr3_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR3_BIT_Ttag {
	unsigned int WR3       : BFW_NX5_xmac_wr3_WR3;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr3_reserved1; /* reserved      */
} NX5_XMAC_WR3_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR3_BIT_T bf;
} NX5_XMAC_WR3_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr4 */
/* => xMAC internal Work Register 4 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr4   0x000008B0U
#define Adr_NX5_xmac0_xmac_wr4 0x018E08B0U
#define Adr_NX5_xmac1_xmac_wr4 0x018E18B0U
#define DFLT_VAL_NX5_xmac_wr4  0x00000000U

#define MSK_NX5_xmac_wr4_WR4      0x0000ffffU
#define SRT_NX5_xmac_wr4_WR4      0
#define DFLT_VAL_NX5_xmac_wr4_WR4 0x00000000U

enum {
	BFW_NX5_xmac_wr4_WR4       = 16, /* [15:0] */
	BFW_NX5_xmac_wr4_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR4_BIT_Ttag {
	unsigned int WR4       : BFW_NX5_xmac_wr4_WR4;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr4_reserved1; /* reserved      */
} NX5_XMAC_WR4_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR4_BIT_T bf;
} NX5_XMAC_WR4_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr5 */
/* => xMAC internal Work Register 5 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr5   0x000008B4U
#define Adr_NX5_xmac0_xmac_wr5 0x018E08B4U
#define Adr_NX5_xmac1_xmac_wr5 0x018E18B4U
#define DFLT_VAL_NX5_xmac_wr5  0x00000000U

#define MSK_NX5_xmac_wr5_WR5      0x0000ffffU
#define SRT_NX5_xmac_wr5_WR5      0
#define DFLT_VAL_NX5_xmac_wr5_WR5 0x00000000U

enum {
	BFW_NX5_xmac_wr5_WR5       = 16, /* [15:0] */
	BFW_NX5_xmac_wr5_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR5_BIT_Ttag {
	unsigned int WR5       : BFW_NX5_xmac_wr5_WR5;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr5_reserved1; /* reserved      */
} NX5_XMAC_WR5_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR5_BIT_T bf;
} NX5_XMAC_WR5_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr6 */
/* => xMAC internal Work Register 6 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr6   0x000008B8U
#define Adr_NX5_xmac0_xmac_wr6 0x018E08B8U
#define Adr_NX5_xmac1_xmac_wr6 0x018E18B8U
#define DFLT_VAL_NX5_xmac_wr6  0x00000000U

#define MSK_NX5_xmac_wr6_WR6      0x0000ffffU
#define SRT_NX5_xmac_wr6_WR6      0
#define DFLT_VAL_NX5_xmac_wr6_WR6 0x00000000U

enum {
	BFW_NX5_xmac_wr6_WR6       = 16, /* [15:0] */
	BFW_NX5_xmac_wr6_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR6_BIT_Ttag {
	unsigned int WR6       : BFW_NX5_xmac_wr6_WR6;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr6_reserved1; /* reserved      */
} NX5_XMAC_WR6_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR6_BIT_T bf;
} NX5_XMAC_WR6_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr7 */
/* => xMAC internal Work Register 7 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr7   0x000008BCU
#define Adr_NX5_xmac0_xmac_wr7 0x018E08BCU
#define Adr_NX5_xmac1_xmac_wr7 0x018E18BCU
#define DFLT_VAL_NX5_xmac_wr7  0x00000000U

#define MSK_NX5_xmac_wr7_WR7      0x0000ffffU
#define SRT_NX5_xmac_wr7_WR7      0
#define DFLT_VAL_NX5_xmac_wr7_WR7 0x00000000U

enum {
	BFW_NX5_xmac_wr7_WR7       = 16, /* [15:0] */
	BFW_NX5_xmac_wr7_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR7_BIT_Ttag {
	unsigned int WR7       : BFW_NX5_xmac_wr7_WR7;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr7_reserved1; /* reserved      */
} NX5_XMAC_WR7_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR7_BIT_T bf;
} NX5_XMAC_WR7_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr8 */
/* => xMAC internal Work Register 7 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr8   0x000008C0U
#define Adr_NX5_xmac0_xmac_wr8 0x018E08C0U
#define Adr_NX5_xmac1_xmac_wr8 0x018E18C0U
#define DFLT_VAL_NX5_xmac_wr8  0x00000000U

#define MSK_NX5_xmac_wr8_WR7      0x0000ffffU
#define SRT_NX5_xmac_wr8_WR7      0
#define DFLT_VAL_NX5_xmac_wr8_WR7 0x00000000U

enum {
	BFW_NX5_xmac_wr8_WR7       = 16, /* [15:0] */
	BFW_NX5_xmac_wr8_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR8_BIT_Ttag {
	unsigned int WR7       : BFW_NX5_xmac_wr8_WR7;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr8_reserved1; /* reserved      */
} NX5_XMAC_WR8_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR8_BIT_T bf;
} NX5_XMAC_WR8_T;

/* --------------------------------------------------------------------- */
/* Register xmac_wr9 */
/* => xMAC internal Work Register 7 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_wr9   0x000008C4U
#define Adr_NX5_xmac0_xmac_wr9 0x018E08C4U
#define Adr_NX5_xmac1_xmac_wr9 0x018E18C4U
#define DFLT_VAL_NX5_xmac_wr9  0x00000000U

#define MSK_NX5_xmac_wr9_WR7      0x0000ffffU
#define SRT_NX5_xmac_wr9_WR7      0
#define DFLT_VAL_NX5_xmac_wr9_WR7 0x00000000U

enum {
	BFW_NX5_xmac_wr9_WR7       = 16, /* [15:0] */
	BFW_NX5_xmac_wr9_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_WR9_BIT_Ttag {
	unsigned int WR7       : BFW_NX5_xmac_wr9_WR7;       /* Work Register */
	unsigned int reserved1 : BFW_NX5_xmac_wr9_reserved1; /* reserved      */
} NX5_XMAC_WR9_BIT_T;

typedef union {
	unsigned int       val;
	NX5_XMAC_WR9_BIT_T bf;
} NX5_XMAC_WR9_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sys_time */
/* => xMAC System Time */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sys_time   0x000008C8U
#define Adr_NX5_xmac0_xmac_sys_time 0x018E08C8U
#define Adr_NX5_xmac1_xmac_sys_time 0x018E18C8U

#define MSK_NX5_xmac_sys_time_sys_time 0x0000ffffU
#define SRT_NX5_xmac_sys_time_sys_time 0

enum {
	BFW_NX5_xmac_sys_time_sys_time  = 16, /* [15:0] */
	BFW_NX5_xmac_sys_time_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SYS_TIME_BIT_Ttag {
	unsigned int sys_time  : BFW_NX5_xmac_sys_time_sys_time;  /* 16 lower bits of 32 bit systime_ns */
	unsigned int reserved1 : BFW_NX5_xmac_sys_time_reserved1; /* reserved                           */
} NX5_XMAC_SYS_TIME_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_SYS_TIME_BIT_T bf;
} NX5_XMAC_SYS_TIME_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sys_time_upper */
/* => xMAC System Time uppler bits, */
/*    latched at read access of xmac_sys_time */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sys_time_upper   0x000008CCU
#define Adr_NX5_xmac0_xmac_sys_time_upper 0x018E08CCU
#define Adr_NX5_xmac1_xmac_sys_time_upper 0x018E18CCU

#define MSK_NX5_xmac_sys_time_upper_sys_time_upper 0x0000ffffU
#define SRT_NX5_xmac_sys_time_upper_sys_time_upper 0

enum {
	BFW_NX5_xmac_sys_time_upper_sys_time_upper = 16, /* [15:0] */
	BFW_NX5_xmac_sys_time_upper_reserved1      = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SYS_TIME_UPPER_BIT_Ttag {
	unsigned int sys_time_upper : BFW_NX5_xmac_sys_time_upper_sys_time_upper; /* 16 upper bits of 32 bit systime_ns,              */
	                                                                          /* latched at read access of xmac_sys_time (lower), */
	unsigned int reserved1      : BFW_NX5_xmac_sys_time_upper_reserved1;      /* reserved                                         */
} NX5_XMAC_SYS_TIME_UPPER_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_SYS_TIME_UPPER_BIT_T bf;
} NX5_XMAC_SYS_TIME_UPPER_T;

/* --------------------------------------------------------------------- */
/* Register xmac_cmp0_status */
/* => xMAC Compare0 Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_cmp0_status   0x000008D0U
#define Adr_NX5_xmac0_xmac_cmp0_status 0x018E08D0U
#define Adr_NX5_xmac1_xmac_cmp0_status 0x018E18D0U

#define MSK_NX5_xmac_cmp0_status_sr0_z       0x00000001U
#define SRT_NX5_xmac_cmp0_status_sr0_z       0
#define MSK_NX5_xmac_cmp0_status_sr1_z       0x00000002U
#define SRT_NX5_xmac_cmp0_status_sr1_z       1
#define MSK_NX5_xmac_cmp0_status_sr2_z       0x00000004U
#define SRT_NX5_xmac_cmp0_status_sr2_z       2
#define MSK_NX5_xmac_cmp0_status_sr3_z       0x00000008U
#define SRT_NX5_xmac_cmp0_status_sr3_z       3
#define MSK_NX5_xmac_cmp0_status_sr4_z       0x00000010U
#define SRT_NX5_xmac_cmp0_status_sr4_z       4
#define MSK_NX5_xmac_cmp0_status_sr5_z       0x00000020U
#define SRT_NX5_xmac_cmp0_status_sr5_z       5
#define MSK_NX5_xmac_cmp0_status_sr6_z       0x00000040U
#define SRT_NX5_xmac_cmp0_status_sr6_z       6
#define MSK_NX5_xmac_cmp0_status_sr7_z       0x00000080U
#define SRT_NX5_xmac_cmp0_status_sr7_z       7
#define MSK_NX5_xmac_cmp0_status_cnt_rx_z    0x00000100U
#define SRT_NX5_xmac_cmp0_status_cnt_rx_z    8
#define MSK_NX5_xmac_cmp0_status_cnt_tx_z    0x00000200U
#define SRT_NX5_xmac_cmp0_status_cnt_tx_z    9
#define MSK_NX5_xmac_cmp0_status_cnt_rx_hw_z 0x00000400U
#define SRT_NX5_xmac_cmp0_status_cnt_rx_hw_z 10
#define MSK_NX5_xmac_cmp0_status_cnt_tx_hw_z 0x00000800U
#define SRT_NX5_xmac_cmp0_status_cnt_tx_hw_z 11
#define MSK_NX5_xmac_cmp0_status_cnt1_rpu_z  0x00001000U
#define SRT_NX5_xmac_cmp0_status_cnt1_rpu_z  12
#define MSK_NX5_xmac_cmp0_status_cnt2_rpu_z  0x00002000U
#define SRT_NX5_xmac_cmp0_status_cnt2_rpu_z  13
#define MSK_NX5_xmac_cmp0_status_cnt1_tpu_z  0x00004000U
#define SRT_NX5_xmac_cmp0_status_cnt1_tpu_z  14
#define MSK_NX5_xmac_cmp0_status_cnt2_tpu_z  0x00008000U
#define SRT_NX5_xmac_cmp0_status_cnt2_tpu_z  15

enum {
	BFW_NX5_xmac_cmp0_status_sr0_z       = 1,  /* [0] */
	BFW_NX5_xmac_cmp0_status_sr1_z       = 1,  /* [1] */
	BFW_NX5_xmac_cmp0_status_sr2_z       = 1,  /* [2] */
	BFW_NX5_xmac_cmp0_status_sr3_z       = 1,  /* [3] */
	BFW_NX5_xmac_cmp0_status_sr4_z       = 1,  /* [4] */
	BFW_NX5_xmac_cmp0_status_sr5_z       = 1,  /* [5] */
	BFW_NX5_xmac_cmp0_status_sr6_z       = 1,  /* [6] */
	BFW_NX5_xmac_cmp0_status_sr7_z       = 1,  /* [7] */
	BFW_NX5_xmac_cmp0_status_cnt_rx_z    = 1,  /* [8] */
	BFW_NX5_xmac_cmp0_status_cnt_tx_z    = 1,  /* [9] */
	BFW_NX5_xmac_cmp0_status_cnt_rx_hw_z = 1,  /* [10] */
	BFW_NX5_xmac_cmp0_status_cnt_tx_hw_z = 1,  /* [11] */
	BFW_NX5_xmac_cmp0_status_cnt1_rpu_z  = 1,  /* [12] */
	BFW_NX5_xmac_cmp0_status_cnt2_rpu_z  = 1,  /* [13] */
	BFW_NX5_xmac_cmp0_status_cnt1_tpu_z  = 1,  /* [14] */
	BFW_NX5_xmac_cmp0_status_cnt2_tpu_z  = 1,  /* [15] */
	BFW_NX5_xmac_cmp0_status_reserved1   = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CMP0_STATUS_BIT_Ttag {
	unsigned int sr0_z       : BFW_NX5_xmac_cmp0_status_sr0_z;       /* sr0 = 0         */
	unsigned int sr1_z       : BFW_NX5_xmac_cmp0_status_sr1_z;       /* sr1 = 0         */
	unsigned int sr2_z       : BFW_NX5_xmac_cmp0_status_sr2_z;       /* sr2 = 0         */
	unsigned int sr3_z       : BFW_NX5_xmac_cmp0_status_sr3_z;       /* sr3 = 0         */
	unsigned int sr4_z       : BFW_NX5_xmac_cmp0_status_sr4_z;       /* sr4 = 0         */
	unsigned int sr5_z       : BFW_NX5_xmac_cmp0_status_sr5_z;       /* sr5 = 0         */
	unsigned int sr6_z       : BFW_NX5_xmac_cmp0_status_sr6_z;       /* sr6 = 0         */
	unsigned int sr7_z       : BFW_NX5_xmac_cmp0_status_sr7_z;       /* sr7 = 0         */
	unsigned int cnt_rx_z    : BFW_NX5_xmac_cmp0_status_cnt_rx_z;    /* count_rx = 0    */
	unsigned int cnt_tx_z    : BFW_NX5_xmac_cmp0_status_cnt_tx_z;    /* count_tx = 0    */
	unsigned int cnt_rx_hw_z : BFW_NX5_xmac_cmp0_status_cnt_rx_hw_z; /* rx_hw_count = 0 */
	unsigned int cnt_tx_hw_z : BFW_NX5_xmac_cmp0_status_cnt_tx_hw_z; /* tx_hw_count = 0 */
	unsigned int cnt1_rpu_z  : BFW_NX5_xmac_cmp0_status_cnt1_rpu_z;  /* rpu_count1 = 0  */
	unsigned int cnt2_rpu_z  : BFW_NX5_xmac_cmp0_status_cnt2_rpu_z;  /* rpu_count2 = 0  */
	unsigned int cnt1_tpu_z  : BFW_NX5_xmac_cmp0_status_cnt1_tpu_z;  /* tpu_count1 = 0  */
	unsigned int cnt2_tpu_z  : BFW_NX5_xmac_cmp0_status_cnt2_tpu_z;  /* tpu_count2 = 0  */
	unsigned int reserved1   : BFW_NX5_xmac_cmp0_status_reserved1;   /* reserved        */
} NX5_XMAC_CMP0_STATUS_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_CMP0_STATUS_BIT_T bf;
} NX5_XMAC_CMP0_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_cmp1_status */
/* => xMAC Compare1 Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_cmp1_status   0x000008D4U
#define Adr_NX5_xmac0_xmac_cmp1_status 0x018E08D4U
#define Adr_NX5_xmac1_xmac_cmp1_status 0x018E18D4U

#define MSK_NX5_xmac_cmp1_status_wr0_z    0x00000001U
#define SRT_NX5_xmac_cmp1_status_wr0_z    0
#define MSK_NX5_xmac_cmp1_status_wr1_z    0x00000002U
#define SRT_NX5_xmac_cmp1_status_wr1_z    1
#define MSK_NX5_xmac_cmp1_status_wr2_z    0x00000004U
#define SRT_NX5_xmac_cmp1_status_wr2_z    2
#define MSK_NX5_xmac_cmp1_status_wr3_z    0x00000008U
#define SRT_NX5_xmac_cmp1_status_wr3_z    3
#define MSK_NX5_xmac_cmp1_status_wr4_z    0x00000010U
#define SRT_NX5_xmac_cmp1_status_wr4_z    4
#define MSK_NX5_xmac_cmp1_status_wr5_z    0x00000020U
#define SRT_NX5_xmac_cmp1_status_wr5_z    5
#define MSK_NX5_xmac_cmp1_status_wr6_z    0x00000040U
#define SRT_NX5_xmac_cmp1_status_wr6_z    6
#define MSK_NX5_xmac_cmp1_status_wr7_z    0x00000080U
#define SRT_NX5_xmac_cmp1_status_wr7_z    7
#define MSK_NX5_xmac_cmp1_status_wr8_z    0x00000100U
#define SRT_NX5_xmac_cmp1_status_wr8_z    8
#define MSK_NX5_xmac_cmp1_status_wr9_z    0x00000200U
#define SRT_NX5_xmac_cmp1_status_wr9_z    9
#define MSK_NX5_xmac_cmp1_status_wr0_wr1  0x00000400U
#define SRT_NX5_xmac_cmp1_status_wr0_wr1  10
#define MSK_NX5_xmac_cmp1_status_wr2_wr3  0x00000800U
#define SRT_NX5_xmac_cmp1_status_wr2_wr3  11
#define MSK_NX5_xmac_cmp1_status_wr4_wr5  0x00001000U
#define SRT_NX5_xmac_cmp1_status_wr4_wr5  12
#define MSK_NX5_xmac_cmp1_status_wr6_wr7  0x00002000U
#define SRT_NX5_xmac_cmp1_status_wr6_wr7  13
#define MSK_NX5_xmac_cmp1_status_wr8_wr9  0x00004000U
#define SRT_NX5_xmac_cmp1_status_wr8_wr9  14
#define MSK_NX5_xmac_cmp1_status_sys_time 0x00008000U
#define SRT_NX5_xmac_cmp1_status_sys_time 15

enum {
	BFW_NX5_xmac_cmp1_status_wr0_z     = 1,  /* [0] */
	BFW_NX5_xmac_cmp1_status_wr1_z     = 1,  /* [1] */
	BFW_NX5_xmac_cmp1_status_wr2_z     = 1,  /* [2] */
	BFW_NX5_xmac_cmp1_status_wr3_z     = 1,  /* [3] */
	BFW_NX5_xmac_cmp1_status_wr4_z     = 1,  /* [4] */
	BFW_NX5_xmac_cmp1_status_wr5_z     = 1,  /* [5] */
	BFW_NX5_xmac_cmp1_status_wr6_z     = 1,  /* [6] */
	BFW_NX5_xmac_cmp1_status_wr7_z     = 1,  /* [7] */
	BFW_NX5_xmac_cmp1_status_wr8_z     = 1,  /* [8] */
	BFW_NX5_xmac_cmp1_status_wr9_z     = 1,  /* [9] */
	BFW_NX5_xmac_cmp1_status_wr0_wr1   = 1,  /* [10] */
	BFW_NX5_xmac_cmp1_status_wr2_wr3   = 1,  /* [11] */
	BFW_NX5_xmac_cmp1_status_wr4_wr5   = 1,  /* [12] */
	BFW_NX5_xmac_cmp1_status_wr6_wr7   = 1,  /* [13] */
	BFW_NX5_xmac_cmp1_status_wr8_wr9   = 1,  /* [14] */
	BFW_NX5_xmac_cmp1_status_sys_time  = 1,  /* [15] */
	BFW_NX5_xmac_cmp1_status_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CMP1_STATUS_BIT_Ttag {
	unsigned int wr0_z     : BFW_NX5_xmac_cmp1_status_wr0_z;     /* 1: work register 0 equals 0                                               */
	unsigned int wr1_z     : BFW_NX5_xmac_cmp1_status_wr1_z;     /* 1: work register 1 equals 0                                               */
	unsigned int wr2_z     : BFW_NX5_xmac_cmp1_status_wr2_z;     /* 1: work register 2 equals 0                                               */
	unsigned int wr3_z     : BFW_NX5_xmac_cmp1_status_wr3_z;     /* 1: work register 3 equals 0                                               */
	unsigned int wr4_z     : BFW_NX5_xmac_cmp1_status_wr4_z;     /* 1: work register 4 equals 0                                               */
	unsigned int wr5_z     : BFW_NX5_xmac_cmp1_status_wr5_z;     /* 1: work register 5 equals 0                                               */
	unsigned int wr6_z     : BFW_NX5_xmac_cmp1_status_wr6_z;     /* 1: work register 6 equals 0                                               */
	unsigned int wr7_z     : BFW_NX5_xmac_cmp1_status_wr7_z;     /* 1: work register 7 equals 0                                               */
	unsigned int wr8_z     : BFW_NX5_xmac_cmp1_status_wr8_z;     /* 1: work register 8 equals 0                                               */
	unsigned int wr9_z     : BFW_NX5_xmac_cmp1_status_wr9_z;     /* 1: work register 9 equals 0                                               */
	unsigned int wr0_wr1   : BFW_NX5_xmac_cmp1_status_wr0_wr1;   /* 1: wr0 equals wr1                                                         */
	unsigned int wr2_wr3   : BFW_NX5_xmac_cmp1_status_wr2_wr3;   /* 1: wr2 equals wr3                                                         */
	unsigned int wr4_wr5   : BFW_NX5_xmac_cmp1_status_wr4_wr5;   /* 1: wr4 equals wr5                                                         */
	unsigned int wr6_wr7   : BFW_NX5_xmac_cmp1_status_wr6_wr7;   /* 1: wr6 equals wr7                                                         */
	unsigned int wr8_wr9   : BFW_NX5_xmac_cmp1_status_wr8_wr9;   /* 1: wr8 equals wr9                                                         */
	unsigned int sys_time  : BFW_NX5_xmac_cmp1_status_sys_time;  /* compare of sys_time with wr6,wr2(value) and wr7,wr3(mask):                */
	                                                             /* {wr7,wr3} define, which bits of sys_time and {wr6,wr2} are to be compared */
	unsigned int reserved1 : BFW_NX5_xmac_cmp1_status_reserved1; /* reserved                                                                  */
} NX5_XMAC_CMP1_STATUS_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_CMP1_STATUS_BIT_T bf;
} NX5_XMAC_CMP1_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_cmp2_status */
/* => xMAC Compare2 Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_cmp2_status   0x000008D8U
#define Adr_NX5_xmac0_xmac_cmp2_status 0x018E08D8U
#define Adr_NX5_xmac1_xmac_cmp2_status 0x018E18D8U

#define MSK_NX5_xmac_cmp2_status_wr0_sr0  0x00000001U
#define SRT_NX5_xmac_cmp2_status_wr0_sr0  0
#define MSK_NX5_xmac_cmp2_status_wr1_sr1  0x00000002U
#define SRT_NX5_xmac_cmp2_status_wr1_sr1  1
#define MSK_NX5_xmac_cmp2_status_wr2_sr2  0x00000004U
#define SRT_NX5_xmac_cmp2_status_wr2_sr2  2
#define MSK_NX5_xmac_cmp2_status_wr3_sr3  0x00000008U
#define SRT_NX5_xmac_cmp2_status_wr3_sr3  3
#define MSK_NX5_xmac_cmp2_status_wr4_sr4  0x00000010U
#define SRT_NX5_xmac_cmp2_status_wr4_sr4  4
#define MSK_NX5_xmac_cmp2_status_wr5_sr5  0x00000020U
#define SRT_NX5_xmac_cmp2_status_wr5_sr5  5
#define MSK_NX5_xmac_cmp2_status_wr6_sr6  0x00000040U
#define SRT_NX5_xmac_cmp2_status_wr6_sr6  6
#define MSK_NX5_xmac_cmp2_status_wr7_sr7  0x00000080U
#define SRT_NX5_xmac_cmp2_status_wr7_sr7  7
#define MSK_NX5_xmac_cmp2_status_wr8_sr8  0x00000100U
#define SRT_NX5_xmac_cmp2_status_wr8_sr8  8
#define MSK_NX5_xmac_cmp2_status_wr9_sr9  0x00000200U
#define SRT_NX5_xmac_cmp2_status_wr9_sr9  9
#define MSK_NX5_xmac_cmp2_status_wr5_sr10 0x00000400U
#define SRT_NX5_xmac_cmp2_status_wr5_sr10 10
#define MSK_NX5_xmac_cmp2_status_wr6_sr11 0x00000800U
#define SRT_NX5_xmac_cmp2_status_wr6_sr11 11
#define MSK_NX5_xmac_cmp2_status_wr5_sr12 0x00001000U
#define SRT_NX5_xmac_cmp2_status_wr5_sr12 12
#define MSK_NX5_xmac_cmp2_status_wr6_sr13 0x00002000U
#define SRT_NX5_xmac_cmp2_status_wr6_sr13 13
#define MSK_NX5_xmac_cmp2_status_wr5_sr14 0x00004000U
#define SRT_NX5_xmac_cmp2_status_wr5_sr14 14
#define MSK_NX5_xmac_cmp2_status_wr6_sr15 0x00008000U
#define SRT_NX5_xmac_cmp2_status_wr6_sr15 15

enum {
	BFW_NX5_xmac_cmp2_status_wr0_sr0   = 1,  /* [0] */
	BFW_NX5_xmac_cmp2_status_wr1_sr1   = 1,  /* [1] */
	BFW_NX5_xmac_cmp2_status_wr2_sr2   = 1,  /* [2] */
	BFW_NX5_xmac_cmp2_status_wr3_sr3   = 1,  /* [3] */
	BFW_NX5_xmac_cmp2_status_wr4_sr4   = 1,  /* [4] */
	BFW_NX5_xmac_cmp2_status_wr5_sr5   = 1,  /* [5] */
	BFW_NX5_xmac_cmp2_status_wr6_sr6   = 1,  /* [6] */
	BFW_NX5_xmac_cmp2_status_wr7_sr7   = 1,  /* [7] */
	BFW_NX5_xmac_cmp2_status_wr8_sr8   = 1,  /* [8] */
	BFW_NX5_xmac_cmp2_status_wr9_sr9   = 1,  /* [9] */
	BFW_NX5_xmac_cmp2_status_wr5_sr10  = 1,  /* [10] */
	BFW_NX5_xmac_cmp2_status_wr6_sr11  = 1,  /* [11] */
	BFW_NX5_xmac_cmp2_status_wr5_sr12  = 1,  /* [12] */
	BFW_NX5_xmac_cmp2_status_wr6_sr13  = 1,  /* [13] */
	BFW_NX5_xmac_cmp2_status_wr5_sr14  = 1,  /* [14] */
	BFW_NX5_xmac_cmp2_status_wr6_sr15  = 1,  /* [15] */
	BFW_NX5_xmac_cmp2_status_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CMP2_STATUS_BIT_Ttag {
	unsigned int wr0_sr0   : BFW_NX5_xmac_cmp2_status_wr0_sr0;   /* 1: wr0 equals sr0  */
	unsigned int wr1_sr1   : BFW_NX5_xmac_cmp2_status_wr1_sr1;   /* 1: wr1 equals sr1  */
	unsigned int wr2_sr2   : BFW_NX5_xmac_cmp2_status_wr2_sr2;   /* 1: wr2 equals sr2  */
	unsigned int wr3_sr3   : BFW_NX5_xmac_cmp2_status_wr3_sr3;   /* 1: wr3 equals sr3  */
	unsigned int wr4_sr4   : BFW_NX5_xmac_cmp2_status_wr4_sr4;   /* 1: wr4 equals sr4  */
	unsigned int wr5_sr5   : BFW_NX5_xmac_cmp2_status_wr5_sr5;   /* 1: wr5 equals sr5  */
	unsigned int wr6_sr6   : BFW_NX5_xmac_cmp2_status_wr6_sr6;   /* 1: wr6 equals sr6  */
	unsigned int wr7_sr7   : BFW_NX5_xmac_cmp2_status_wr7_sr7;   /* 1: wr7 equals sr7  */
	unsigned int wr8_sr8   : BFW_NX5_xmac_cmp2_status_wr8_sr8;   /* 1: wr8 equals sr8  */
	unsigned int wr9_sr9   : BFW_NX5_xmac_cmp2_status_wr9_sr9;   /* 1: wr9 equals sr9  */
	unsigned int wr5_sr10  : BFW_NX5_xmac_cmp2_status_wr5_sr10;  /* 1: wr5 equals sr10 */
	unsigned int wr6_sr11  : BFW_NX5_xmac_cmp2_status_wr6_sr11;  /* 1: wr6 equals sr11 */
	unsigned int wr5_sr12  : BFW_NX5_xmac_cmp2_status_wr5_sr12;  /* 1: wr5 equals sr12 */
	unsigned int wr6_sr13  : BFW_NX5_xmac_cmp2_status_wr6_sr13;  /* 1: wr6 equals sr13 */
	unsigned int wr5_sr14  : BFW_NX5_xmac_cmp2_status_wr5_sr14;  /* 1: wr5 equals sr14 */
	unsigned int wr6_sr15  : BFW_NX5_xmac_cmp2_status_wr6_sr15;  /* 1: wr6 equals sr15 */
	unsigned int reserved1 : BFW_NX5_xmac_cmp2_status_reserved1; /* reserved           */
} NX5_XMAC_CMP2_STATUS_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_CMP2_STATUS_BIT_T bf;
} NX5_XMAC_CMP2_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_cmp3_status */
/* => xMAC Compare3 Status Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_cmp3_status   0x000008DCU
#define Adr_NX5_xmac0_xmac_cmp3_status 0x018E08DCU
#define Adr_NX5_xmac1_xmac_cmp3_status 0x018E18DCU

#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr0 0x00000001U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr0 0
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr1 0x00000002U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr1 1
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr2 0x00000004U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr2 2
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr3 0x00000008U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr3 3
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr4 0x00000010U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr4 4
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr5 0x00000020U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr5 5
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr6 0x00000040U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr6 6
#define MSK_NX5_xmac_cmp3_status_rpucnt1_wr7 0x00000080U
#define SRT_NX5_xmac_cmp3_status_rpucnt1_wr7 7
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr0 0x00000100U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr0 8
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr1 0x00000200U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr1 9
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr2 0x00000400U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr2 10
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr3 0x00000800U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr3 11
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr4 0x00001000U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr4 12
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr5 0x00002000U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr5 13
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr6 0x00004000U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr6 14
#define MSK_NX5_xmac_cmp3_status_tpucnt1_wr7 0x00008000U
#define SRT_NX5_xmac_cmp3_status_tpucnt1_wr7 15

enum {
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr0 = 1,  /* [0] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr1 = 1,  /* [1] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr2 = 1,  /* [2] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr3 = 1,  /* [3] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr4 = 1,  /* [4] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr5 = 1,  /* [5] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr6 = 1,  /* [6] */
	BFW_NX5_xmac_cmp3_status_rpucnt1_wr7 = 1,  /* [7] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr0 = 1,  /* [8] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr1 = 1,  /* [9] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr2 = 1,  /* [10] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr3 = 1,  /* [11] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr4 = 1,  /* [12] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr5 = 1,  /* [13] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr6 = 1,  /* [14] */
	BFW_NX5_xmac_cmp3_status_tpucnt1_wr7 = 1,  /* [15] */
	BFW_NX5_xmac_cmp3_status_reserved1   = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CMP3_STATUS_BIT_Ttag {
	unsigned int rpucnt1_wr0 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr0; /* 1: rpu_count1 equals wr0 */
	unsigned int rpucnt1_wr1 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr1; /* 1: rpu_count1 equals wr1 */
	unsigned int rpucnt1_wr2 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr2; /* 1: rpu_count1 equals wr2 */
	unsigned int rpucnt1_wr3 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr3; /* 1: rpu_count1 equals wr3 */
	unsigned int rpucnt1_wr4 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr4; /* 1: rpu_count1 equals wr4 */
	unsigned int rpucnt1_wr5 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr5; /* 1: rpu_count1 equals wr5 */
	unsigned int rpucnt1_wr6 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr6; /* 1: rpu_count1 equals wr6 */
	unsigned int rpucnt1_wr7 : BFW_NX5_xmac_cmp3_status_rpucnt1_wr7; /* 1: rpu_count1 equals wr7 */
	unsigned int tpucnt1_wr0 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr0; /* 1: tpu_count1 equals wr0 */
	unsigned int tpucnt1_wr1 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr1; /* 1: tpu_count1 equals wr1 */
	unsigned int tpucnt1_wr2 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr2; /* 1: tpu_count1 equals wr2 */
	unsigned int tpucnt1_wr3 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr3; /* 1: tpu_count1 equals wr3 */
	unsigned int tpucnt1_wr4 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr4; /* 1: tpu_count1 equals wr4 */
	unsigned int tpucnt1_wr5 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr5; /* 1: tpu_count1 equals wr5 */
	unsigned int tpucnt1_wr6 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr6; /* 1: tpu_count1 equals wr6 */
	unsigned int tpucnt1_wr7 : BFW_NX5_xmac_cmp3_status_tpucnt1_wr7; /* 1: tpu_count1 equals wr7 */
	unsigned int reserved1   : BFW_NX5_xmac_cmp3_status_reserved1;   /* reserved                 */
} NX5_XMAC_CMP3_STATUS_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_CMP3_STATUS_BIT_T bf;
} NX5_XMAC_CMP3_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_alu_flags */
/* => xMAC RPU and TPU ALU Flags: */
/*    ALU Flags are only influenced by combinatonal commands like add, sub, rotate, shift. */
/*    Bitwise commands (e.g. and, or, ...) do not influence ALU-Flags. */
/*    In case of bitwise commands, ALU-Flags keep their old value. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_alu_flags   0x000008E0U
#define Adr_NX5_xmac0_xmac_alu_flags 0x018E08E0U
#define Adr_NX5_xmac1_xmac_alu_flags 0x018E18E0U

#define MSK_NX5_xmac_alu_flags_rpu_carry 0x00000001U
#define SRT_NX5_xmac_alu_flags_rpu_carry 0
#define MSK_NX5_xmac_alu_flags_rpu_zero  0x00000002U
#define SRT_NX5_xmac_alu_flags_rpu_zero  1
#define MSK_NX5_xmac_alu_flags_rpu_neg   0x00000004U
#define SRT_NX5_xmac_alu_flags_rpu_neg   2
#define MSK_NX5_xmac_alu_flags_rpu_ovf   0x00000008U
#define SRT_NX5_xmac_alu_flags_rpu_ovf   3
#define MSK_NX5_xmac_alu_flags_tpu_carry 0x00000010U
#define SRT_NX5_xmac_alu_flags_tpu_carry 4
#define MSK_NX5_xmac_alu_flags_tpu_zero  0x00000020U
#define SRT_NX5_xmac_alu_flags_tpu_zero  5
#define MSK_NX5_xmac_alu_flags_tpu_neg   0x00000040U
#define SRT_NX5_xmac_alu_flags_tpu_neg   6
#define MSK_NX5_xmac_alu_flags_tpu_ovf   0x00000080U
#define SRT_NX5_xmac_alu_flags_tpu_ovf   7
#define MSK_NX5_xmac_alu_flags_rxcnt_wr2 0x00004000U
#define SRT_NX5_xmac_alu_flags_rxcnt_wr2 14
#define MSK_NX5_xmac_alu_flags_txcnt_wr7 0x00008000U
#define SRT_NX5_xmac_alu_flags_txcnt_wr7 15

enum {
	BFW_NX5_xmac_alu_flags_rpu_carry = 1,  /* [0] */
	BFW_NX5_xmac_alu_flags_rpu_zero  = 1,  /* [1] */
	BFW_NX5_xmac_alu_flags_rpu_neg   = 1,  /* [2] */
	BFW_NX5_xmac_alu_flags_rpu_ovf   = 1,  /* [3] */
	BFW_NX5_xmac_alu_flags_tpu_carry = 1,  /* [4] */
	BFW_NX5_xmac_alu_flags_tpu_zero  = 1,  /* [5] */
	BFW_NX5_xmac_alu_flags_tpu_neg   = 1,  /* [6] */
	BFW_NX5_xmac_alu_flags_tpu_ovf   = 1,  /* [7] */
	BFW_NX5_xmac_alu_flags_reserved1 = 6,  /* [13:8] */
	BFW_NX5_xmac_alu_flags_rxcnt_wr2 = 1,  /* [14] */
	BFW_NX5_xmac_alu_flags_txcnt_wr7 = 1,  /* [15] */
	BFW_NX5_xmac_alu_flags_reserved2 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_ALU_FLAGS_BIT_Ttag {
	unsigned int rpu_carry : BFW_NX5_xmac_alu_flags_rpu_carry; /* RPU carry flag                                              */
	unsigned int rpu_zero  : BFW_NX5_xmac_alu_flags_rpu_zero;  /* RPU zero flag                                               */
	unsigned int rpu_neg   : BFW_NX5_xmac_alu_flags_rpu_neg;   /* RPU neg flag                                                */
	unsigned int rpu_ovf   : BFW_NX5_xmac_alu_flags_rpu_ovf;   /* RPU ovf flag                                                */
	unsigned int tpu_carry : BFW_NX5_xmac_alu_flags_tpu_carry; /* TPU carry flag                                              */
	unsigned int tpu_zero  : BFW_NX5_xmac_alu_flags_tpu_zero;  /* TPU zero flag                                               */
	unsigned int tpu_neg   : BFW_NX5_xmac_alu_flags_tpu_neg;   /* TPU neg flag                                                */
	unsigned int tpu_ovf   : BFW_NX5_xmac_alu_flags_tpu_ovf;   /* TPU ovf flag                                                */
	unsigned int reserved1 : BFW_NX5_xmac_alu_flags_reserved1; /* reserved                                                    */
	unsigned int rxcnt_wr2 : BFW_NX5_xmac_alu_flags_rxcnt_wr2; /* 1: rx_count equals wr2, no ALU-Flag, calculated every cycle */
	unsigned int txcnt_wr7 : BFW_NX5_xmac_alu_flags_txcnt_wr7; /* 1: tx_count equals wr7, no ALU-Flag, calculated every cycle */
	unsigned int reserved2 : BFW_NX5_xmac_alu_flags_reserved2; /* reserved                                                    */
} NX5_XMAC_ALU_FLAGS_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XMAC_ALU_FLAGS_BIT_T bf;
} NX5_XMAC_ALU_FLAGS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_status_int */
/* => xMAC Status Internal Register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_status_int   0x000008E4U
#define Adr_NX5_xmac0_xmac_status_int 0x018E08E4U
#define Adr_NX5_xmac1_xmac_status_int 0x018E18E4U

#define MSK_NX5_xmac_status_int_rpm_hit0    0x00000001U
#define SRT_NX5_xmac_status_int_rpm_hit0    0
#define MSK_NX5_xmac_status_int_rpm_hit1    0x00000002U
#define SRT_NX5_xmac_status_int_rpm_hit1    1
#define MSK_NX5_xmac_status_int_rpm_hit0or1 0x00000004U
#define SRT_NX5_xmac_status_int_rpm_hit0or1 2
#define MSK_NX5_xmac_status_int_tpm_hit0    0x00000008U
#define SRT_NX5_xmac_status_int_tpm_hit0    3
#define MSK_NX5_xmac_status_int_tpm_hit1    0x00000010U
#define SRT_NX5_xmac_status_int_tpm_hit1    4
#define MSK_NX5_xmac_status_int_tpm_hit0or1 0x00000020U
#define SRT_NX5_xmac_status_int_tpm_hit0or1 5
#define MSK_NX5_xmac_status_int_lbit_eq_bit 0x00000040U
#define SRT_NX5_xmac_status_int_lbit_eq_bit 6
#define MSK_NX5_xmac_status_int_tx_eq_wr45  0x00000080U
#define SRT_NX5_xmac_status_int_tx_eq_wr45  7
#define MSK_NX5_xmac_status_int_rx_crc_ok   0x00000100U
#define SRT_NX5_xmac_status_int_rx_crc_ok   8
#define MSK_NX5_xmac_status_int_tx_crc_ok   0x00000200U
#define SRT_NX5_xmac_status_int_tx_crc_ok   9
#define MSK_NX5_xmac_status_int_rx_crc32_ok 0x00000400U
#define SRT_NX5_xmac_status_int_rx_crc32_ok 10
#define MSK_NX5_xmac_status_int_recbit      0x00000800U
#define SRT_NX5_xmac_status_int_recbit      11
#define MSK_NX5_xmac_status_int_brec        0x00001000U
#define SRT_NX5_xmac_status_int_brec        12
#define MSK_NX5_xmac_status_int_btran       0x00002000U
#define SRT_NX5_xmac_status_int_btran       13
#define MSK_NX5_xmac_status_int_zero        0x00008000U
#define SRT_NX5_xmac_status_int_zero        15

enum {
	BFW_NX5_xmac_status_int_rpm_hit0    = 1,  /* [0] */
	BFW_NX5_xmac_status_int_rpm_hit1    = 1,  /* [1] */
	BFW_NX5_xmac_status_int_rpm_hit0or1 = 1,  /* [2] */
	BFW_NX5_xmac_status_int_tpm_hit0    = 1,  /* [3] */
	BFW_NX5_xmac_status_int_tpm_hit1    = 1,  /* [4] */
	BFW_NX5_xmac_status_int_tpm_hit0or1 = 1,  /* [5] */
	BFW_NX5_xmac_status_int_lbit_eq_bit = 1,  /* [6] */
	BFW_NX5_xmac_status_int_tx_eq_wr45  = 1,  /* [7] */
	BFW_NX5_xmac_status_int_rx_crc_ok   = 1,  /* [8] */
	BFW_NX5_xmac_status_int_tx_crc_ok   = 1,  /* [9] */
	BFW_NX5_xmac_status_int_rx_crc32_ok = 1,  /* [10] */
	BFW_NX5_xmac_status_int_recbit      = 1,  /* [11] */
	BFW_NX5_xmac_status_int_brec        = 1,  /* [12] */
	BFW_NX5_xmac_status_int_btran       = 1,  /* [13] */
	BFW_NX5_xmac_status_int_reserved1   = 1,  /* [14] */
	BFW_NX5_xmac_status_int_zero        = 1,  /* [15] */
	BFW_NX5_xmac_status_int_reserved2   = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STATUS_INT_BIT_Ttag {
	unsigned int rpm_hit0    : BFW_NX5_xmac_status_int_rpm_hit0;    /* receive pattern 0 matches                                */
	unsigned int rpm_hit1    : BFW_NX5_xmac_status_int_rpm_hit1;    /* receive pattern 1 matches                                */
	unsigned int rpm_hit0or1 : BFW_NX5_xmac_status_int_rpm_hit0or1; /* receive pattern 0 or pattern 1 matches                   */
	unsigned int tpm_hit0    : BFW_NX5_xmac_status_int_tpm_hit0;    /* transmit pattern 0 matches                               */
	unsigned int tpm_hit1    : BFW_NX5_xmac_status_int_tpm_hit1;    /* transmit pattern 1 matches                               */
	unsigned int tpm_hit0or1 : BFW_NX5_xmac_status_int_tpm_hit0or1; /* transmit pattern 0 or pattern 1 matches                  */
	unsigned int lbit_eq_bit : BFW_NX5_xmac_status_int_lbit_eq_bit; /* last received bit = actually received bit                */
	unsigned int tx_eq_wr45  : BFW_NX5_xmac_status_int_tx_eq_wr45;  /* compare of tx with wr4(value) and wr5(mask):             */
	                                                                /* wr5 defines, which bits of tx and wr4 are to be compared */
	unsigned int rx_crc_ok   : BFW_NX5_xmac_status_int_rx_crc_ok;   /* compare of rx_crc_l/_h with wr0/1:                       */
	unsigned int tx_crc_ok   : BFW_NX5_xmac_status_int_tx_crc_ok;   /* compare of tx_crc_l/_h with wr8/9:                       */
	unsigned int rx_crc32_ok : BFW_NX5_xmac_status_int_rx_crc32_ok; /* compare of rx_crc32 with 0xc704dd7b                      */
	unsigned int recbit      : BFW_NX5_xmac_status_int_recbit;      /* acutally received bit                                    */
	unsigned int brec        : BFW_NX5_xmac_status_int_brec;        /* bit received (active for 1 cc)                           */
	unsigned int btran       : BFW_NX5_xmac_status_int_btran;       /* bit transmitted (active for 1 cc)                        */
	unsigned int reserved1   : BFW_NX5_xmac_status_int_reserved1;   /* reserved                                                 */
	unsigned int zero        : BFW_NX5_xmac_status_int_zero;        /* always 0                                                 */
	unsigned int reserved2   : BFW_NX5_xmac_status_int_reserved2;   /* reserved                                                 */
} NX5_XMAC_STATUS_INT_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_STATUS_INT_BIT_T bf;
} NX5_XMAC_STATUS_INT_T;

/* --------------------------------------------------------------------- */
/* Register xmac_stat_bits */
/* => xMAC stat_bits: */
/*    set and reset by hw_support bits (set_stat and reset_stat) and selected by src1_adr, */
/*    accessible by all RPUs and TPUs with higher set than reset priority */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_stat_bits   0x000008E8U
#define Adr_NX5_xmac0_xmac_stat_bits 0x018E08E8U
#define Adr_NX5_xmac1_xmac_stat_bits 0x018E18E8U

#define MSK_NX5_xmac_stat_bits_stat_bits 0x0000ffffU
#define SRT_NX5_xmac_stat_bits_stat_bits 0

enum {
	BFW_NX5_xmac_stat_bits_stat_bits = 16, /* [15:0] */
	BFW_NX5_xmac_stat_bits_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STAT_BITS_BIT_Ttag {
	unsigned int stat_bits : BFW_NX5_xmac_stat_bits_stat_bits; /* seperate bits selected by lower bits of src1_adr, if set_stat/reset_stat are active */
	unsigned int reserved1 : BFW_NX5_xmac_stat_bits_reserved1; /* reserved                                                                            */
} NX5_XMAC_STAT_BITS_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XMAC_STAT_BITS_BIT_T bf;
} NX5_XMAC_STAT_BITS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_status_mii */
/* => xMAC MII receive status register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_status_mii   0x000008ECU
#define Adr_NX5_xmac0_xmac_status_mii 0x018E08ECU
#define Adr_NX5_xmac1_xmac_status_mii 0x018E18ECU

#define MSK_NX5_xmac_status_mii_rx_dv       0x00000001U
#define SRT_NX5_xmac_status_mii_rx_dv       0
#define MSK_NX5_xmac_status_mii_rx_err      0x00000002U
#define SRT_NX5_xmac_status_mii_rx_err      1
#define MSK_NX5_xmac_status_mii_crs         0x00000004U
#define SRT_NX5_xmac_status_mii_crs         2
#define MSK_NX5_xmac_status_mii_col         0x00000008U
#define SRT_NX5_xmac_status_mii_col         3
#define MSK_NX5_xmac_status_mii_s_nc        0x00000010U
#define SRT_NX5_xmac_status_mii_s_nc        4
#define MSK_NX5_xmac_status_mii_v_ne_ns_nc  0x00000020U
#define SRT_NX5_xmac_status_mii_v_ne_ns_nc  5
#define MSK_NX5_xmac_status_mii_v_ne_nc     0x00000040U
#define SRT_NX5_xmac_status_mii_v_ne_nc     6
#define MSK_NX5_xmac_status_mii_v_ne_ns     0x00000080U
#define SRT_NX5_xmac_status_mii_v_ne_ns     7
#define MSK_NX5_xmac_status_mii_v_ne        0x00000100U
#define SRT_NX5_xmac_status_mii_v_ne        8
#define MSK_NX5_xmac_status_mii_v_ne_s_nc   0x00000200U
#define SRT_NX5_xmac_status_mii_v_ne_s_nc   9
#define MSK_NX5_xmac_status_mii_v_ne_s      0x00000400U
#define SRT_NX5_xmac_status_mii_v_ne_s      10
#define MSK_NX5_xmac_status_mii_v_ne_nc_p0  0x00000800U
#define SRT_NX5_xmac_status_mii_v_ne_nc_p0  11
#define MSK_NX5_xmac_status_mii_v_ne_nc_p1  0x00001000U
#define SRT_NX5_xmac_status_mii_v_ne_nc_p1  12
#define MSK_NX5_xmac_status_mii_v_ne_nc_p01 0x00002000U
#define SRT_NX5_xmac_status_mii_v_ne_nc_p01 13

enum {
	BFW_NX5_xmac_status_mii_rx_dv       = 1,  /* [0] */
	BFW_NX5_xmac_status_mii_rx_err      = 1,  /* [1] */
	BFW_NX5_xmac_status_mii_crs         = 1,  /* [2] */
	BFW_NX5_xmac_status_mii_col         = 1,  /* [3] */
	BFW_NX5_xmac_status_mii_s_nc        = 1,  /* [4] */
	BFW_NX5_xmac_status_mii_v_ne_ns_nc  = 1,  /* [5] */
	BFW_NX5_xmac_status_mii_v_ne_nc     = 1,  /* [6] */
	BFW_NX5_xmac_status_mii_v_ne_ns     = 1,  /* [7] */
	BFW_NX5_xmac_status_mii_v_ne        = 1,  /* [8] */
	BFW_NX5_xmac_status_mii_v_ne_s_nc   = 1,  /* [9] */
	BFW_NX5_xmac_status_mii_v_ne_s      = 1,  /* [10] */
	BFW_NX5_xmac_status_mii_v_ne_nc_p0  = 1,  /* [11] */
	BFW_NX5_xmac_status_mii_v_ne_nc_p1  = 1,  /* [12] */
	BFW_NX5_xmac_status_mii_v_ne_nc_p01 = 1,  /* [13] */
	BFW_NX5_xmac_status_mii_reserved1   = 18  /* [31:14] */
};

typedef struct NX5_XMAC_STATUS_MII_BIT_Ttag {
	unsigned int rx_dv       : BFW_NX5_xmac_status_mii_rx_dv;       /* mii data valid                                         */
	unsigned int rx_err      : BFW_NX5_xmac_status_mii_rx_err;      /* mii rx_err                                             */
	unsigned int crs         : BFW_NX5_xmac_status_mii_crs;         /* mii crs                                                */
	unsigned int col         : BFW_NX5_xmac_status_mii_col;         /* mii col                                                */
	unsigned int s_nc        : BFW_NX5_xmac_status_mii_s_nc;        /* crs & !col                                             */
	unsigned int v_ne_ns_nc  : BFW_NX5_xmac_status_mii_v_ne_ns_nc;  /* rx_dv & !rx_err & !crs & !col                          */
	unsigned int v_ne_nc     : BFW_NX5_xmac_status_mii_v_ne_nc;     /* rx_dv & !rx_err &        !col                          */
	unsigned int v_ne_ns     : BFW_NX5_xmac_status_mii_v_ne_ns;     /* rx_dv & !rx_err & !crs                                 */
	unsigned int v_ne        : BFW_NX5_xmac_status_mii_v_ne;        /* rx_dv & !rx_err                                        */
	unsigned int v_ne_s_nc   : BFW_NX5_xmac_status_mii_v_ne_s_nc;   /* rx_dv & !rx_err &  crs & !col                          */
	unsigned int v_ne_s      : BFW_NX5_xmac_status_mii_v_ne_s;      /* rx_dv & !rx_err &  crs                                 */
	unsigned int v_ne_nc_p0  : BFW_NX5_xmac_status_mii_v_ne_nc_p0;  /* rx_dv & !rx_err &        !col &  rpm_hit0              */
	unsigned int v_ne_nc_p1  : BFW_NX5_xmac_status_mii_v_ne_nc_p1;  /* rx_dv & !rx_err &        !col &              rpm_hit1  */
	unsigned int v_ne_nc_p01 : BFW_NX5_xmac_status_mii_v_ne_nc_p01; /* rx_dv & !rx_err &        !col & (rpm_hit0 |  rpm_hit1) */
	unsigned int reserved1   : BFW_NX5_xmac_status_mii_reserved1;   /* reserved                                               */
} NX5_XMAC_STATUS_MII_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_STATUS_MII_BIT_T bf;
} NX5_XMAC_STATUS_MII_T;

/* --------------------------------------------------------------------- */
/* Register xmac_status_mii2 */
/* => xMAC 2nd MII receive status register */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_status_mii2   0x000008F0U
#define Adr_NX5_xmac0_xmac_status_mii2 0x018E08F0U
#define Adr_NX5_xmac1_xmac_status_mii2 0x018E18F0U

#define MSK_NX5_xmac_status_mii2_dv                    0x00000001U
#define SRT_NX5_xmac_status_mii2_dv                    0
#define MSK_NX5_xmac_status_mii2_rx_dv                 0x00000002U
#define SRT_NX5_xmac_status_mii2_rx_dv                 1
#define MSK_NX5_xmac_status_mii2_rx_err                0x00000004U
#define SRT_NX5_xmac_status_mii2_rx_err                2
#define MSK_NX5_xmac_status_mii2_rx_crs                0x00000008U
#define SRT_NX5_xmac_status_mii2_rx_crs                3
#define MSK_NX5_xmac_status_mii2_v_ne                  0x00000010U
#define SRT_NX5_xmac_status_mii2_v_ne                  4
#define MSK_NX5_xmac_status_mii2_rx_miif_error_ro      0x00000020U
#define SRT_NX5_xmac_status_mii2_rx_miif_error_ro      5
#define MSK_NX5_xmac_status_mii2_rx_miif_ovfl_ro       0x00000040U
#define SRT_NX5_xmac_status_mii2_rx_miif_ovfl_ro       6
#define MSK_NX5_xmac_status_mii2_rx_miif_unfl_ro       0x00000080U
#define SRT_NX5_xmac_status_mii2_rx_miif_unfl_ro       7
#define MSK_NX5_xmac_status_mii2_rx_miif_short_dv_ro   0x00000100U
#define SRT_NX5_xmac_status_mii2_rx_miif_short_dv_ro   8
#define MSK_NX5_xmac_status_mii2_tx_miif_error_ro      0x00000200U
#define SRT_NX5_xmac_status_mii2_tx_miif_error_ro      9
#define MSK_NX5_xmac_status_mii2_tx_miif_ovfl_ro       0x00000400U
#define SRT_NX5_xmac_status_mii2_tx_miif_ovfl_ro       10
#define MSK_NX5_xmac_status_mii2_tx_miif_unfl_ro       0x00000800U
#define SRT_NX5_xmac_status_mii2_tx_miif_unfl_ro       11
#define MSK_NX5_xmac_status_mii2_tx_miif_short_txen_ro 0x00001000U
#define SRT_NX5_xmac_status_mii2_tx_miif_short_txen_ro 12
#define MSK_NX5_xmac_status_mii2_rx_err_was_here       0x00002000U
#define SRT_NX5_xmac_status_mii2_rx_err_was_here       13
#define MSK_NX5_xmac_status_mii2_col_was_here          0x00004000U
#define SRT_NX5_xmac_status_mii2_col_was_here          14
#define MSK_NX5_xmac_status_mii2_crs_was_here          0x00008000U
#define SRT_NX5_xmac_status_mii2_crs_was_here          15

enum {
	BFW_NX5_xmac_status_mii2_dv                    = 1,  /* [0] */
	BFW_NX5_xmac_status_mii2_rx_dv                 = 1,  /* [1] */
	BFW_NX5_xmac_status_mii2_rx_err                = 1,  /* [2] */
	BFW_NX5_xmac_status_mii2_rx_crs                = 1,  /* [3] */
	BFW_NX5_xmac_status_mii2_v_ne                  = 1,  /* [4] */
	BFW_NX5_xmac_status_mii2_rx_miif_error_ro      = 1,  /* [5] */
	BFW_NX5_xmac_status_mii2_rx_miif_ovfl_ro       = 1,  /* [6] */
	BFW_NX5_xmac_status_mii2_rx_miif_unfl_ro       = 1,  /* [7] */
	BFW_NX5_xmac_status_mii2_rx_miif_short_dv_ro   = 1,  /* [8] */
	BFW_NX5_xmac_status_mii2_tx_miif_error_ro      = 1,  /* [9] */
	BFW_NX5_xmac_status_mii2_tx_miif_ovfl_ro       = 1,  /* [10] */
	BFW_NX5_xmac_status_mii2_tx_miif_unfl_ro       = 1,  /* [11] */
	BFW_NX5_xmac_status_mii2_tx_miif_short_txen_ro = 1,  /* [12] */
	BFW_NX5_xmac_status_mii2_rx_err_was_here       = 1,  /* [13] */
	BFW_NX5_xmac_status_mii2_col_was_here          = 1,  /* [14] */
	BFW_NX5_xmac_status_mii2_crs_was_here          = 1,  /* [15] */
	BFW_NX5_xmac_status_mii2_reserved1             = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STATUS_MII2_BIT_Ttag {
	unsigned int dv                    : BFW_NX5_xmac_status_mii2_dv;                    /* RX-Nibble-FIFO data valid:                                                                     */
	                                                                                     /* Fifo is automatically filled, if rx_dv=1. This bit gets active, if fifo contains enough data.  */
	unsigned int rx_dv                 : BFW_NX5_xmac_status_mii2_rx_dv;                 /* MII rx_dv before RX_Nibble-FIFO.                                                               */
	                                                                                     /* This bit is a copy of xmac_status_mii-rx_dv.                                                   */
	unsigned int rx_err                : BFW_NX5_xmac_status_mii2_rx_err;                /* MII rx_err before RX_Nibble-FIFO.                                                              */
	                                                                                     /* This bit is a copy of xmac_status_mii-rx_err.                                                  */
	unsigned int rx_crs                : BFW_NX5_xmac_status_mii2_rx_crs;                /* MII crs before RX_Nibble-FIFO.                                                                 */
	                                                                                     /* This bit is a copy of xmac_status_mii-crs.                                                     */
	unsigned int v_ne                  : BFW_NX5_xmac_status_mii2_v_ne;                  /* dv & !rx_err                                                                                   */
	                                                                                     /* Useful, if rx_err has to be checked every cycle by software                                    */
	unsigned int rx_miif_error_ro      : BFW_NX5_xmac_status_mii2_rx_miif_error_ro;      /* Any error at RX-Nibble-FIFO occured,                                                           */
	                                                                                     /* Any error can be tx_miif_short_txen_ro, tx_miif_ovfl_ro or tx_miif_unfl_ro.                    */
	unsigned int rx_miif_ovfl_ro       : BFW_NX5_xmac_status_mii2_rx_miif_ovfl_ro;       /* RX-Nibble-FIFO overflow.                                                                       */
	                                                                                     /* This bit is read only.                                                                         */
	unsigned int rx_miif_unfl_ro       : BFW_NX5_xmac_status_mii2_rx_miif_unfl_ro;       /* RX-Nibble-FIFO underflow.                                                                      */
	                                                                                     /* This bit is read only.                                                                         */
	unsigned int rx_miif_short_dv_ro   : BFW_NX5_xmac_status_mii2_rx_miif_short_dv_ro;   /* RX-Nibble-FIFO error: rx_dv was active or inactive for very short time.                        */
	                                                                                     /* Rx_dv went inactive before FIFO reached fill_level or went active before FIFO was flushed.     */
	unsigned int tx_miif_error_ro      : BFW_NX5_xmac_status_mii2_tx_miif_error_ro;      /* Any error at TX-Nibble-FIFO occured,                                                           */
	                                                                                     /* Any error can be tx_miif_short_txen_ro, tx_miif_ovfl_ro or tx_miif_unfl_ro.                    */
	unsigned int tx_miif_ovfl_ro       : BFW_NX5_xmac_status_mii2_tx_miif_ovfl_ro;       /* TX-Nibble-FIFO overflow.                                                                       */
	                                                                                     /* This bit is read only.                                                                         */
	unsigned int tx_miif_unfl_ro       : BFW_NX5_xmac_status_mii2_tx_miif_unfl_ro;       /* TX-Nibble-FIFO underflow.                                                                      */
	                                                                                     /* This bit is read only.                                                                         */
	unsigned int tx_miif_short_txen_ro : BFW_NX5_xmac_status_mii2_tx_miif_short_txen_ro; /* tx_en was changed too fast:                                                                    */
	                                                                                     /* When setting tx_en=1, it must stay active at least until fifo reaches fill_level (fifo_depth). */
	unsigned int rx_err_was_here       : BFW_NX5_xmac_status_mii2_rx_err_was_here;       /* rx_err was here:                                                                               */
	                                                                                     /* Useful, if rx_err needs only to be checked at end of frame.                                    */
	unsigned int col_was_here          : BFW_NX5_xmac_status_mii2_col_was_here;          /* col was here:                                                                                  */
	                                                                                     /* Useful, if col needs only to be checked at end of frame.                                       */
	unsigned int crs_was_here          : BFW_NX5_xmac_status_mii2_crs_was_here;          /* crs was here:                                                                                  */
	                                                                                     /* Useful, if crs needs only to be checked at end of frame.                                       */
	unsigned int reserved1             : BFW_NX5_xmac_status_mii2_reserved1;             /* reserved                                                                                       */
} NX5_XMAC_STATUS_MII2_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_STATUS_MII2_BIT_T bf;
} NX5_XMAC_STATUS_MII2_T;

/* --------------------------------------------------------------------- */
/* Register xmac_other_status_mii2 */
/* => xMAC 2nd MII receive status register of other xMAC */
/*    Used for fast forward of data between 2 xMACs (specially in MII-HUB-mode) */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_other_status_mii2   0x000008F4U
#define Adr_NX5_xmac0_xmac_other_status_mii2 0x018E08F4U
#define Adr_NX5_xmac1_xmac_other_status_mii2 0x018E18F4U

#define MSK_NX5_xmac_other_status_mii2_dv                    0x00000001U
#define SRT_NX5_xmac_other_status_mii2_dv                    0
#define MSK_NX5_xmac_other_status_mii2_rx_dv                 0x00000002U
#define SRT_NX5_xmac_other_status_mii2_rx_dv                 1
#define MSK_NX5_xmac_other_status_mii2_rx_err                0x00000004U
#define SRT_NX5_xmac_other_status_mii2_rx_err                2
#define MSK_NX5_xmac_other_status_mii2_rx_crs                0x00000008U
#define SRT_NX5_xmac_other_status_mii2_rx_crs                3
#define MSK_NX5_xmac_other_status_mii2_v_ne                  0x00000010U
#define SRT_NX5_xmac_other_status_mii2_v_ne                  4
#define MSK_NX5_xmac_other_status_mii2_rx_miif_error_ro      0x00000020U
#define SRT_NX5_xmac_other_status_mii2_rx_miif_error_ro      5
#define MSK_NX5_xmac_other_status_mii2_rx_miif_ovfl_ro       0x00000040U
#define SRT_NX5_xmac_other_status_mii2_rx_miif_ovfl_ro       6
#define MSK_NX5_xmac_other_status_mii2_rx_miif_unfl_ro       0x00000080U
#define SRT_NX5_xmac_other_status_mii2_rx_miif_unfl_ro       7
#define MSK_NX5_xmac_other_status_mii2_rx_miif_short_dv_ro   0x00000100U
#define SRT_NX5_xmac_other_status_mii2_rx_miif_short_dv_ro   8
#define MSK_NX5_xmac_other_status_mii2_tx_miif_error_ro      0x00000200U
#define SRT_NX5_xmac_other_status_mii2_tx_miif_error_ro      9
#define MSK_NX5_xmac_other_status_mii2_tx_miif_ovfl_ro       0x00000400U
#define SRT_NX5_xmac_other_status_mii2_tx_miif_ovfl_ro       10
#define MSK_NX5_xmac_other_status_mii2_tx_miif_unfl_ro       0x00000800U
#define SRT_NX5_xmac_other_status_mii2_tx_miif_unfl_ro       11
#define MSK_NX5_xmac_other_status_mii2_tx_miif_short_txen_ro 0x00001000U
#define SRT_NX5_xmac_other_status_mii2_tx_miif_short_txen_ro 12
#define MSK_NX5_xmac_other_status_mii2_rx_err_was_here       0x00002000U
#define SRT_NX5_xmac_other_status_mii2_rx_err_was_here       13
#define MSK_NX5_xmac_other_status_mii2_col_was_here          0x00004000U
#define SRT_NX5_xmac_other_status_mii2_col_was_here          14
#define MSK_NX5_xmac_other_status_mii2_crs_was_here          0x00008000U
#define SRT_NX5_xmac_other_status_mii2_crs_was_here          15

enum {
	BFW_NX5_xmac_other_status_mii2_dv                    = 1,  /* [0] */
	BFW_NX5_xmac_other_status_mii2_rx_dv                 = 1,  /* [1] */
	BFW_NX5_xmac_other_status_mii2_rx_err                = 1,  /* [2] */
	BFW_NX5_xmac_other_status_mii2_rx_crs                = 1,  /* [3] */
	BFW_NX5_xmac_other_status_mii2_v_ne                  = 1,  /* [4] */
	BFW_NX5_xmac_other_status_mii2_rx_miif_error_ro      = 1,  /* [5] */
	BFW_NX5_xmac_other_status_mii2_rx_miif_ovfl_ro       = 1,  /* [6] */
	BFW_NX5_xmac_other_status_mii2_rx_miif_unfl_ro       = 1,  /* [7] */
	BFW_NX5_xmac_other_status_mii2_rx_miif_short_dv_ro   = 1,  /* [8] */
	BFW_NX5_xmac_other_status_mii2_tx_miif_error_ro      = 1,  /* [9] */
	BFW_NX5_xmac_other_status_mii2_tx_miif_ovfl_ro       = 1,  /* [10] */
	BFW_NX5_xmac_other_status_mii2_tx_miif_unfl_ro       = 1,  /* [11] */
	BFW_NX5_xmac_other_status_mii2_tx_miif_short_txen_ro = 1,  /* [12] */
	BFW_NX5_xmac_other_status_mii2_rx_err_was_here       = 1,  /* [13] */
	BFW_NX5_xmac_other_status_mii2_col_was_here          = 1,  /* [14] */
	BFW_NX5_xmac_other_status_mii2_crs_was_here          = 1,  /* [15] */
	BFW_NX5_xmac_other_status_mii2_reserved1             = 16  /* [31:16] */
};

typedef struct NX5_XMAC_OTHER_STATUS_MII2_BIT_Ttag {
	unsigned int dv                    : BFW_NX5_xmac_other_status_mii2_dv;                    /* RX-Nibble-FIFO data valid:                                                                     */
	                                                                                           /* Fifo is automatically filled, if rx_dv=1. This bit gets active, if fifo contains enough data.  */
	unsigned int rx_dv                 : BFW_NX5_xmac_other_status_mii2_rx_dv;                 /* MII rx_dv before RX_Nibble-FIFO.                                                               */
	                                                                                           /* This bit is a copy of xmac_status_mii-rx_dv.                                                   */
	unsigned int rx_err                : BFW_NX5_xmac_other_status_mii2_rx_err;                /* MII rx_err before RX_Nibble-FIFO.                                                              */
	                                                                                           /* This bit is a copy of xmac_status_mii-rx_err.                                                  */
	unsigned int rx_crs                : BFW_NX5_xmac_other_status_mii2_rx_crs;                /* MII crs before RX_Nibble-FIFO.                                                                 */
	                                                                                           /* This bit is a copy of xmac_status_mii-crs.                                                     */
	unsigned int v_ne                  : BFW_NX5_xmac_other_status_mii2_v_ne;                  /* dv & !rx_err                                                                                   */
	                                                                                           /* Useful, if rx_err has to be checked every cycle by software                                    */
	unsigned int rx_miif_error_ro      : BFW_NX5_xmac_other_status_mii2_rx_miif_error_ro;      /* Any error at RX-Nibble-FIFO occured,                                                           */
	                                                                                           /* Any error can be tx_miif_short_txen_ro, tx_miif_ovfl_ro or tx_miif_unfl_ro.                    */
	unsigned int rx_miif_ovfl_ro       : BFW_NX5_xmac_other_status_mii2_rx_miif_ovfl_ro;       /* RX-Nibble-FIFO overflow.                                                                       */
	                                                                                           /* This bit is read only.                                                                         */
	unsigned int rx_miif_unfl_ro       : BFW_NX5_xmac_other_status_mii2_rx_miif_unfl_ro;       /* RX-Nibble-FIFO underflow.                                                                      */
	                                                                                           /* This bit is read only.                                                                         */
	unsigned int rx_miif_short_dv_ro   : BFW_NX5_xmac_other_status_mii2_rx_miif_short_dv_ro;   /* RX-Nibble-FIFO error: rx_dv was active or inactive for very short time.                        */
	                                                                                           /* Rx_dv went inactive before FIFO reached fill_level or went active before FIFO was flushed.     */
	unsigned int tx_miif_error_ro      : BFW_NX5_xmac_other_status_mii2_tx_miif_error_ro;      /* Any error at TX-Nibble-FIFO occured,                                                           */
	                                                                                           /* Any error can be tx_miif_short_txen_ro, tx_miif_ovfl_ro or tx_miif_unfl_ro.                    */
	unsigned int tx_miif_ovfl_ro       : BFW_NX5_xmac_other_status_mii2_tx_miif_ovfl_ro;       /* TX-Nibble-FIFO overflow.                                                                       */
	                                                                                           /* This bit is read only.                                                                         */
	unsigned int tx_miif_unfl_ro       : BFW_NX5_xmac_other_status_mii2_tx_miif_unfl_ro;       /* TX-Nibble-FIFO underflow.                                                                      */
	                                                                                           /* This bit is read only.                                                                         */
	unsigned int tx_miif_short_txen_ro : BFW_NX5_xmac_other_status_mii2_tx_miif_short_txen_ro; /* tx_en was changed too fast:                                                                    */
	                                                                                           /* When setting tx_en=1, it must stay active at least until fifo reaches fill_level (fifo_depth). */
	unsigned int rx_err_was_here       : BFW_NX5_xmac_other_status_mii2_rx_err_was_here;       /* rx_err was here:                                                                               */
	                                                                                           /* Useful, if rx_err needs only to be checked at end of frame.                                    */
	unsigned int col_was_here          : BFW_NX5_xmac_other_status_mii2_col_was_here;          /* col was here:                                                                                  */
	                                                                                           /* Useful, if col needs only to be checked at end of frame.                                       */
	unsigned int crs_was_here          : BFW_NX5_xmac_other_status_mii2_crs_was_here;          /* crs was here:                                                                                  */
	                                                                                           /* Useful, if crs needs only to be checked at end of frame.                                       */
	unsigned int reserved1             : BFW_NX5_xmac_other_status_mii2_reserved1;             /* reserved                                                                                       */
} NX5_XMAC_OTHER_STATUS_MII2_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_XMAC_OTHER_STATUS_MII2_BIT_T bf;
} NX5_XMAC_OTHER_STATUS_MII2_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_mii */
/* => xMAC MII transmit config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_mii   0x000008F8U
#define Adr_NX5_xmac0_xmac_config_mii 0x018E08F8U
#define Adr_NX5_xmac1_xmac_config_mii 0x018E18F8U
#define DFLT_VAL_NX5_xmac_config_mii  0x00000000U

#define MSK_NX5_xmac_config_mii_tx_en       0x00000001U
#define SRT_NX5_xmac_config_mii_tx_en       0
#define DFLT_VAL_NX5_xmac_config_mii_tx_en  0x00000000U
#define MSK_NX5_xmac_config_mii_tx_err      0x00000002U
#define SRT_NX5_xmac_config_mii_tx_err      1
#define DFLT_VAL_NX5_xmac_config_mii_tx_err 0x00000000U

enum {
	BFW_NX5_xmac_config_mii_tx_en     = 1,  /* [0] */
	BFW_NX5_xmac_config_mii_tx_err    = 1,  /* [1] */
	BFW_NX5_xmac_config_mii_reserved1 = 30  /* [31:2] */
};

typedef struct NX5_XMAC_CONFIG_MII_BIT_Ttag {
	unsigned int tx_en     : BFW_NX5_xmac_config_mii_tx_en;     /* mii tx_en                  */
	                                                            /* Synchronized to mii tx_clk */
	unsigned int tx_err    : BFW_NX5_xmac_config_mii_tx_err;    /* mii tx_err                 */
	                                                            /* Synchronized to mii tx_clk */
	unsigned int reserved1 : BFW_NX5_xmac_config_mii_reserved1; /* reserved                   */
} NX5_XMAC_CONFIG_MII_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_CONFIG_MII_BIT_T bf;
} NX5_XMAC_CONFIG_MII_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_rx_nibble_fifo */
/* => xMAC RX MII Nibble FIFO config register */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_rx_nibble_fifo   0x000008FCU
#define Adr_NX5_xmac0_xmac_config_rx_nibble_fifo 0x018E08FCU
#define Adr_NX5_xmac1_xmac_config_rx_nibble_fifo 0x018E18FCU
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo  0x00001000U

#define MSK_NX5_xmac_config_rx_nibble_fifo_sample_phase        0x00000007U
#define SRT_NX5_xmac_config_rx_nibble_fifo_sample_phase        0
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo_sample_phase   0x00000000U
#define MSK_NX5_xmac_config_rx_nibble_fifo_delay_rx_data       0x00000008U
#define SRT_NX5_xmac_config_rx_nibble_fifo_delay_rx_data       3
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo_delay_rx_data  0x00000000U
#define MSK_NX5_xmac_config_rx_nibble_fifo_fifo_depth_add      0x00000030U
#define SRT_NX5_xmac_config_rx_nibble_fifo_fifo_depth_add      4
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo_fifo_depth_add 0x00000000U
#define MSK_NX5_xmac_config_rx_nibble_fifo_fifo_depth          0x000003c0U
#define SRT_NX5_xmac_config_rx_nibble_fifo_fifo_depth          6
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo_fifo_depth     0x00000000U
#define MSK_NX5_xmac_config_rx_nibble_fifo_rx_write_phase      0x00000c00U
#define SRT_NX5_xmac_config_rx_nibble_fifo_rx_write_phase      10
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo_rx_write_phase 0x00000000U
#define MSK_NX5_xmac_config_rx_nibble_fifo_rpu_sync_delay      0x00003000U
#define SRT_NX5_xmac_config_rx_nibble_fifo_rpu_sync_delay      12
#define DFLT_VAL_NX5_xmac_config_rx_nibble_fifo_rpu_sync_delay 0x00001000U

enum {
	BFW_NX5_xmac_config_rx_nibble_fifo_sample_phase   = 3,  /* [2:0] */
	BFW_NX5_xmac_config_rx_nibble_fifo_delay_rx_data  = 1,  /* [3] */
	BFW_NX5_xmac_config_rx_nibble_fifo_fifo_depth_add = 2,  /* [5:4] */
	BFW_NX5_xmac_config_rx_nibble_fifo_fifo_depth     = 4,  /* [9:6] */
	BFW_NX5_xmac_config_rx_nibble_fifo_rx_write_phase = 2,  /* [11:10] */
	BFW_NX5_xmac_config_rx_nibble_fifo_rpu_sync_delay = 2,  /* [13:12] */
	BFW_NX5_xmac_config_rx_nibble_fifo_reserved1      = 18  /* [31:14] */
};

typedef struct NX5_XMAC_CONFIG_RX_NIBBLE_FIFO_BIT_Ttag {
	unsigned int sample_phase   : BFW_NX5_xmac_config_rx_nibble_fifo_sample_phase;   /* Phase of mii_rx_clk, where mii_rx_d, rx_dv, rx_err, crs, col are sampled:                                                                 */
	                                                                                 /* This value is used for input of MII data independant on RX-Nibble-FIFO.                                                                   */
	unsigned int delay_rx_data  : BFW_NX5_xmac_config_rx_nibble_fifo_delay_rx_data;  /* Delay mii inputs (rx_d, rx_dv, rx_err, crs, col) by 1 clockcycle before sampling them.                                                    */
	                                                                                 /* Enable this, if rx_d gets invalid shortly after rx_clk (hold<10ns).                                                                       */
	unsigned int fifo_depth_add : BFW_NX5_xmac_config_rx_nibble_fifo_fifo_depth_add; /* Fill level additional wait cycles                                                                                                         */
	                                                                                 /* Allows to increase the garanteed delay of the fifo in bitclock units instead of full nibbles.                                             */
	unsigned int fifo_depth     : BFW_NX5_xmac_config_rx_nibble_fifo_fifo_depth;     /* Fill level (= number of nibbles) up to which RX-Nibble-FIFO is filled, before reading to rx register starts.                              */
	                                                                                 /* 0 means, RX-Nibble-FIFO is turned off, data is sampled directly to rx register (with jitter), FIFO is reset.                              */
	unsigned int rx_write_phase : BFW_NX5_xmac_config_rx_nibble_fifo_rx_write_phase; /* Phases, in which nibbles from RX-Nibble-FIFO are written to rx register:                                                                  */
	                                                                                 /* If RX-Nibble-FIFO is enabled (fifo_depth!=0), the sync-signal (copies data to rx register) is generated by a counter (instead of rx_clk), */
	unsigned int rpu_sync_delay : BFW_NX5_xmac_config_rx_nibble_fifo_rpu_sync_delay; /* Delay between rx_write_phase and RPU-sync pulse:                                                                                          */
	                                                                                 /* By this value the RPU-sync pulse is delayed by 0, 1, 2 or 3 clockcycles (x10ns).                                                          */
	unsigned int reserved1      : BFW_NX5_xmac_config_rx_nibble_fifo_reserved1;      /* reserved                                                                                                                                  */
} NX5_XMAC_CONFIG_RX_NIBBLE_FIFO_BIT_T;

typedef union {
	unsigned int                         val;
	NX5_XMAC_CONFIG_RX_NIBBLE_FIFO_BIT_T bf;
} NX5_XMAC_CONFIG_RX_NIBBLE_FIFO_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_tx_nibble_fifo */
/* => xMAC TX NII Nibble FIFO config register */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_tx_nibble_fifo   0x00000900U
#define Adr_NX5_xmac0_xmac_config_tx_nibble_fifo 0x018E0900U
#define Adr_NX5_xmac1_xmac_config_tx_nibble_fifo 0x018E1900U
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo  0x00000000U

#define MSK_NX5_xmac_config_tx_nibble_fifo_output_phase           0x00000007U
#define SRT_NX5_xmac_config_tx_nibble_fifo_output_phase           0
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo_output_phase      0x00000000U
#define MSK_NX5_xmac_config_tx_nibble_fifo_fifo_depth_add         0x00000018U
#define SRT_NX5_xmac_config_tx_nibble_fifo_fifo_depth_add         3
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo_fifo_depth_add    0x00000000U
#define MSK_NX5_xmac_config_tx_nibble_fifo_fifo_depth             0x000001e0U
#define SRT_NX5_xmac_config_tx_nibble_fifo_fifo_depth             5
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo_fifo_depth        0x00000000U
#define MSK_NX5_xmac_config_tx_nibble_fifo_tx_read_phase          0x00000600U
#define SRT_NX5_xmac_config_tx_nibble_fifo_tx_read_phase          9
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo_tx_read_phase     0x00000000U
#define MSK_NX5_xmac_config_tx_nibble_fifo_tpu_sync_delay         0x00001800U
#define SRT_NX5_xmac_config_tx_nibble_fifo_tpu_sync_delay         11
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo_tpu_sync_delay    0x00000000U
#define MSK_NX5_xmac_config_tx_nibble_fifo_outputedge_tx_clk      0x00002000U
#define SRT_NX5_xmac_config_tx_nibble_fifo_outputedge_tx_clk      13
#define DFLT_VAL_NX5_xmac_config_tx_nibble_fifo_outputedge_tx_clk 0x00000000U

enum {
	BFW_NX5_xmac_config_tx_nibble_fifo_output_phase      = 3,  /* [2:0] */
	BFW_NX5_xmac_config_tx_nibble_fifo_fifo_depth_add    = 2,  /* [4:3] */
	BFW_NX5_xmac_config_tx_nibble_fifo_fifo_depth        = 4,  /* [8:5] */
	BFW_NX5_xmac_config_tx_nibble_fifo_tx_read_phase     = 2,  /* [10:9] */
	BFW_NX5_xmac_config_tx_nibble_fifo_tpu_sync_delay    = 2,  /* [12:11] */
	BFW_NX5_xmac_config_tx_nibble_fifo_outputedge_tx_clk = 1,  /* [13] */
	BFW_NX5_xmac_config_tx_nibble_fifo_reserved1         = 18  /* [31:14] */
};

typedef struct NX5_XMAC_CONFIG_TX_NIBBLE_FIFO_BIT_Ttag {
	unsigned int output_phase      : BFW_NX5_xmac_config_tx_nibble_fifo_output_phase;      /* Phase of mii_tx_clk, where mii_tx_d, tx_en, tx_err outputs are changed in relation to incoming mii_txclk:      */
	                                                                                       /* This value is used for output of MII data independant on TX-Nibble-FIFO.                                       */
	unsigned int fifo_depth_add    : BFW_NX5_xmac_config_tx_nibble_fifo_fifo_depth_add;    /* Fill level additional wait cycles                                                                              */
	                                                                                       /* Allows to increase the garanteed delay of the fifo in bitclock units instead of full nibbles.                  */
	unsigned int fifo_depth        : BFW_NX5_xmac_config_tx_nibble_fifo_fifo_depth;        /* Fill level (= number of nibbles) up to which TX-Nibble-FIFO is filled, before output to external pins starts.  */
	                                                                                       /* 0 means, TX-Nibble-FIFO is turned off, data is sampled directly from tx register (with jitter), FIFO is reset. */
	unsigned int tx_read_phase     : BFW_NX5_xmac_config_tx_nibble_fifo_tx_read_phase;     /* TX register read phase:                                                                                        */
	                                                                                       /* If TX-Nibble-FIFO is enabled (fifo_depth!=0), TX-register is only dependant on a global 2-bit-counter.         */
	unsigned int tpu_sync_delay    : BFW_NX5_xmac_config_tx_nibble_fifo_tpu_sync_delay;    /* Delay between read of TX-register and TPU-sync pulse:                                                          */
	                                                                                       /* By this value the TPU-sync pulse is delayed by 0, 1, 2 or 3 clockcycles (x10ns).                               */
	unsigned int outputedge_tx_clk : BFW_NX5_xmac_config_tx_nibble_fifo_outputedge_tx_clk; /* MII output data is changed (active for 1cc)                                                                    */
	unsigned int reserved1         : BFW_NX5_xmac_config_tx_nibble_fifo_reserved1;         /* reserved                                                                                                       */
} NX5_XMAC_CONFIG_TX_NIBBLE_FIFO_BIT_T;

typedef union {
	unsigned int                         val;
	NX5_XMAC_CONFIG_TX_NIBBLE_FIFO_BIT_T bf;
} NX5_XMAC_CONFIG_TX_NIBBLE_FIFO_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_sbu */
/* => xMAC Config Register for SBU */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_sbu   0x00000904U
#define Adr_NX5_xmac0_xmac_config_sbu 0x018E0904U
#define Adr_NX5_xmac1_xmac_config_sbu 0x018E1904U
#define DFLT_VAL_NX5_xmac_config_sbu  0x00000000U

#define MSK_NX5_xmac_config_sbu_sync_to_eclk           0x00000001U
#define SRT_NX5_xmac_config_sbu_sync_to_eclk           0
#define DFLT_VAL_NX5_xmac_config_sbu_sync_to_eclk      0x00000000U
#define MSK_NX5_xmac_config_sbu_sync_to_bitstream      0x00000002U
#define SRT_NX5_xmac_config_sbu_sync_to_bitstream      1
#define DFLT_VAL_NX5_xmac_config_sbu_sync_to_bitstream 0x00000000U
#define MSK_NX5_xmac_config_sbu_sync_to_posedge        0x00000004U
#define SRT_NX5_xmac_config_sbu_sync_to_posedge        2
#define DFLT_VAL_NX5_xmac_config_sbu_sync_to_posedge   0x00000000U
#define MSK_NX5_xmac_config_sbu_sync_to_negedge        0x00000008U
#define SRT_NX5_xmac_config_sbu_sync_to_negedge        3
#define DFLT_VAL_NX5_xmac_config_sbu_sync_to_negedge   0x00000000U
#define MSK_NX5_xmac_config_sbu_count_modulo           0x00000010U
#define SRT_NX5_xmac_config_sbu_count_modulo           4
#define DFLT_VAL_NX5_xmac_config_sbu_count_modulo      0x00000000U
#define MSK_NX5_xmac_config_sbu_invert_bit             0x00000020U
#define SRT_NX5_xmac_config_sbu_invert_bit             5
#define DFLT_VAL_NX5_xmac_config_sbu_invert_bit        0x00000000U
#define MSK_NX5_xmac_config_sbu_predivide_clk          0x00000040U
#define SRT_NX5_xmac_config_sbu_predivide_clk          6
#define DFLT_VAL_NX5_xmac_config_sbu_predivide_clk     0x00000000U
#define MSK_NX5_xmac_config_sbu_ext_mode               0x00000300U
#define SRT_NX5_xmac_config_sbu_ext_mode               8
#define DFLT_VAL_NX5_xmac_config_sbu_ext_mode          0x00000000U
#define MSK_NX5_xmac_config_sbu_rx_err_low_active      0x00000400U
#define SRT_NX5_xmac_config_sbu_rx_err_low_active      10
#define DFLT_VAL_NX5_xmac_config_sbu_rx_err_low_active 0x00000000U
#define MSK_NX5_xmac_config_sbu_rx_err_reset           0x00000800U
#define SRT_NX5_xmac_config_sbu_rx_err_reset           11
#define DFLT_VAL_NX5_xmac_config_sbu_rx_err_reset      0x00000000U
#define MSK_NX5_xmac_config_sbu_col_low_active         0x00001000U
#define SRT_NX5_xmac_config_sbu_col_low_active         12
#define DFLT_VAL_NX5_xmac_config_sbu_col_low_active    0x00000000U
#define MSK_NX5_xmac_config_sbu_col_reset              0x00002000U
#define SRT_NX5_xmac_config_sbu_col_reset              13
#define DFLT_VAL_NX5_xmac_config_sbu_col_reset         0x00000000U
#define MSK_NX5_xmac_config_sbu_crs_low_active         0x00004000U
#define SRT_NX5_xmac_config_sbu_crs_low_active         14
#define DFLT_VAL_NX5_xmac_config_sbu_crs_low_active    0x00000000U
#define MSK_NX5_xmac_config_sbu_crs_reset              0x00008000U
#define SRT_NX5_xmac_config_sbu_crs_reset              15
#define DFLT_VAL_NX5_xmac_config_sbu_crs_reset         0x00000000U

enum {
	BFW_NX5_xmac_config_sbu_sync_to_eclk      = 1,  /* [0] */
	BFW_NX5_xmac_config_sbu_sync_to_bitstream = 1,  /* [1] */
	BFW_NX5_xmac_config_sbu_sync_to_posedge   = 1,  /* [2] */
	BFW_NX5_xmac_config_sbu_sync_to_negedge   = 1,  /* [3] */
	BFW_NX5_xmac_config_sbu_count_modulo      = 1,  /* [4] */
	BFW_NX5_xmac_config_sbu_invert_bit        = 1,  /* [5] */
	BFW_NX5_xmac_config_sbu_predivide_clk     = 1,  /* [6] */
	BFW_NX5_xmac_config_sbu_reserved1         = 1,  /* [7] */
	BFW_NX5_xmac_config_sbu_ext_mode          = 2,  /* [9:8] */
	BFW_NX5_xmac_config_sbu_rx_err_low_active = 1,  /* [10] */
	BFW_NX5_xmac_config_sbu_rx_err_reset      = 1,  /* [11] */
	BFW_NX5_xmac_config_sbu_col_low_active    = 1,  /* [12] */
	BFW_NX5_xmac_config_sbu_col_reset         = 1,  /* [13] */
	BFW_NX5_xmac_config_sbu_crs_low_active    = 1,  /* [14] */
	BFW_NX5_xmac_config_sbu_crs_reset         = 1,  /* [15] */
	BFW_NX5_xmac_config_sbu_reserved2         = 16  /* [31:16] */
};

typedef struct NX5_XMAC_CONFIG_SBU_BIT_Ttag {
	unsigned int sync_to_eclk      : BFW_NX5_xmac_config_sbu_sync_to_eclk;      /* Synchronize rate_multiplier to external clock,                             */
	                                                                            /* rate_mul is set to rate_mul_start at pos/negedge of eclk                   */
	unsigned int sync_to_bitstream : BFW_NX5_xmac_config_sbu_sync_to_bitstream; /* Synchronize rate_multiplier to data_in,                                    */
	                                                                            /* rate_mul is set to rate_mul_start at pos/negedge of data_in                */
	unsigned int sync_to_posedge   : BFW_NX5_xmac_config_sbu_sync_to_posedge;   /* Synchronization of rate_multiplier works on positive edges of data_in/eclk */
	unsigned int sync_to_negedge   : BFW_NX5_xmac_config_sbu_sync_to_negedge;   /* Synchronization of rate_multiplier works on negative edges of data_in/eclk */
	unsigned int count_modulo      : BFW_NX5_xmac_config_sbu_count_modulo;      /* rate_multiplier continues counting after maximum value is reached          */
	unsigned int invert_bit        : BFW_NX5_xmac_config_sbu_invert_bit;        /* invert incoming bits (mii and bitstream mode)                              */
	unsigned int predivide_clk     : BFW_NX5_xmac_config_sbu_predivide_clk;     /* use a clock frequency divided by 256                                       */
	unsigned int reserved1         : BFW_NX5_xmac_config_sbu_reserved1;         /* reserved                                                                   */
	unsigned int ext_mode          : BFW_NX5_xmac_config_sbu_ext_mode;          /* 00 single bit, 01 mii, 10,11 reserved                                      */
	unsigned int rx_err_low_active : BFW_NX5_xmac_config_sbu_rx_err_low_active; /* to generate rx_err_was_here signal:                                        */
	                                                                            /* 0: activate rx_err_was_here if rx_err=1,                                   */
	unsigned int rx_err_reset      : BFW_NX5_xmac_config_sbu_rx_err_reset;      /* to reset rx_err_was_here signal                                            */
	unsigned int col_low_active    : BFW_NX5_xmac_config_sbu_col_low_active;    /* to generate col_was_here signal:                                           */
	                                                                            /* 0: activate col_was_here if col=1,                                         */
	unsigned int col_reset         : BFW_NX5_xmac_config_sbu_col_reset;         /* to reset col_was_here signal                                               */
	unsigned int crs_low_active    : BFW_NX5_xmac_config_sbu_crs_low_active;    /* to generate crs_was_here signal:                                           */
	                                                                            /* 0: activate crs_was_here if crs=1,                                         */
	unsigned int crs_reset         : BFW_NX5_xmac_config_sbu_crs_reset;         /* to reset crs_was_here signal                                               */
	unsigned int reserved2         : BFW_NX5_xmac_config_sbu_reserved2;         /* reserved                                                                   */
} NX5_XMAC_CONFIG_SBU_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_CONFIG_SBU_BIT_T bf;
} NX5_XMAC_CONFIG_SBU_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sbu_rate_mul_add */
/* => xMAC SBU rate_mul_add: */
/*    Value added each cc to Rate Multiplier. */
/*    rate_mul_add = eclk / clk * 65536 */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sbu_rate_mul_add   0x00000908U
#define Adr_NX5_xmac0_xmac_sbu_rate_mul_add 0x018E0908U
#define Adr_NX5_xmac1_xmac_sbu_rate_mul_add 0x018E1908U
#define DFLT_VAL_NX5_xmac_sbu_rate_mul_add  0x00000001U

#define MSK_NX5_xmac_sbu_rate_mul_add_rate_mul_add      0x0000ffffU
#define SRT_NX5_xmac_sbu_rate_mul_add_rate_mul_add      0
#define DFLT_VAL_NX5_xmac_sbu_rate_mul_add_rate_mul_add 0x00000001U

enum {
	BFW_NX5_xmac_sbu_rate_mul_add_rate_mul_add = 16, /* [15:0] */
	BFW_NX5_xmac_sbu_rate_mul_add_reserved1    = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SBU_RATE_MUL_ADD_BIT_Ttag {
	unsigned int rate_mul_add : BFW_NX5_xmac_sbu_rate_mul_add_rate_mul_add; /* Value added each cc to Rate Multiplier.                             */
	                                                                        /* If rate_mul_add=1:      rate_mul counts from [rate_mul_start:65535] */
	unsigned int reserved1    : BFW_NX5_xmac_sbu_rate_mul_add_reserved1;    /* reserved                                                            */
} NX5_XMAC_SBU_RATE_MUL_ADD_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_XMAC_SBU_RATE_MUL_ADD_BIT_T bf;
} NX5_XMAC_SBU_RATE_MUL_ADD_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sbu_rate_mul_start */
/* => xMAC SBU rate_mul_start */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sbu_rate_mul_start   0x0000090CU
#define Adr_NX5_xmac0_xmac_sbu_rate_mul_start 0x018E090CU
#define Adr_NX5_xmac1_xmac_sbu_rate_mul_start 0x018E190CU
#define DFLT_VAL_NX5_xmac_sbu_rate_mul_start  0x00000000U

#define MSK_NX5_xmac_sbu_rate_mul_start_rate_mul_start      0x0000ffffU
#define SRT_NX5_xmac_sbu_rate_mul_start_rate_mul_start      0
#define DFLT_VAL_NX5_xmac_sbu_rate_mul_start_rate_mul_start 0x00000000U

enum {
	BFW_NX5_xmac_sbu_rate_mul_start_rate_mul_start = 16, /* [15:0] */
	BFW_NX5_xmac_sbu_rate_mul_start_reserved1      = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SBU_RATE_MUL_START_BIT_Ttag {
	unsigned int rate_mul_start : BFW_NX5_xmac_sbu_rate_mul_start_rate_mul_start; /* Value, the Rate Multiplier is set to at sync */
	unsigned int reserved1      : BFW_NX5_xmac_sbu_rate_mul_start_reserved1;      /* reserved                                     */
} NX5_XMAC_SBU_RATE_MUL_START_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_XMAC_SBU_RATE_MUL_START_BIT_T bf;
} NX5_XMAC_SBU_RATE_MUL_START_T;

/* --------------------------------------------------------------------- */
/* Register xmac_sbu_rate_mul */
/* => xMAC SBU rate_mul */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_sbu_rate_mul   0x00000910U
#define Adr_NX5_xmac0_xmac_sbu_rate_mul 0x018E0910U
#define Adr_NX5_xmac1_xmac_sbu_rate_mul 0x018E1910U
#define DFLT_VAL_NX5_xmac_sbu_rate_mul  0x00000000U

#define MSK_NX5_xmac_sbu_rate_mul_rate_mul      0x0000ffffU
#define SRT_NX5_xmac_sbu_rate_mul_rate_mul      0
#define DFLT_VAL_NX5_xmac_sbu_rate_mul_rate_mul 0x00000000U

enum {
	BFW_NX5_xmac_sbu_rate_mul_rate_mul  = 16, /* [15:0] */
	BFW_NX5_xmac_sbu_rate_mul_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_SBU_RATE_MUL_BIT_Ttag {
	unsigned int rate_mul  : BFW_NX5_xmac_sbu_rate_mul_rate_mul;  /* current value of Rate Multiplier */
	unsigned int reserved1 : BFW_NX5_xmac_sbu_rate_mul_reserved1; /* reserved                         */
} NX5_XMAC_SBU_RATE_MUL_BIT_T;

typedef union {
	unsigned int                val;
	NX5_XMAC_SBU_RATE_MUL_BIT_T bf;
} NX5_XMAC_SBU_RATE_MUL_T;

/* --------------------------------------------------------------------- */
/* Register xmac_start_sample_pos */
/* => xMAC SBU start_sample_pos */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_start_sample_pos   0x00000914U
#define Adr_NX5_xmac0_xmac_start_sample_pos 0x018E0914U
#define Adr_NX5_xmac1_xmac_start_sample_pos 0x018E1914U
#define DFLT_VAL_NX5_xmac_start_sample_pos  0x00000000U

#define MSK_NX5_xmac_start_sample_pos_start_sample_pos      0x0000ffffU
#define SRT_NX5_xmac_start_sample_pos_start_sample_pos      0
#define DFLT_VAL_NX5_xmac_start_sample_pos_start_sample_pos 0x00000000U

enum {
	BFW_NX5_xmac_start_sample_pos_start_sample_pos = 16, /* [15:0] */
	BFW_NX5_xmac_start_sample_pos_reserved1        = 16  /* [31:16] */
};

typedef struct NX5_XMAC_START_SAMPLE_POS_BIT_Ttag {
	unsigned int start_sample_pos : BFW_NX5_xmac_start_sample_pos_start_sample_pos; /* data is sampled and averaged if start_sample_pos <= rate_mul < stop_sample_pos */
	unsigned int reserved1        : BFW_NX5_xmac_start_sample_pos_reserved1;        /* reserved                                                                       */
} NX5_XMAC_START_SAMPLE_POS_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_XMAC_START_SAMPLE_POS_BIT_T bf;
} NX5_XMAC_START_SAMPLE_POS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_stop_sample_pos */
/* => xMAC SBU stop_sample_pos */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_stop_sample_pos   0x00000918U
#define Adr_NX5_xmac0_xmac_stop_sample_pos 0x018E0918U
#define Adr_NX5_xmac1_xmac_stop_sample_pos 0x018E1918U
#define DFLT_VAL_NX5_xmac_stop_sample_pos  0x00000000U

#define MSK_NX5_xmac_stop_sample_pos_stop_sample_pos      0x0000ffffU
#define SRT_NX5_xmac_stop_sample_pos_stop_sample_pos      0
#define DFLT_VAL_NX5_xmac_stop_sample_pos_stop_sample_pos 0x00000000U

enum {
	BFW_NX5_xmac_stop_sample_pos_stop_sample_pos = 16, /* [15:0] */
	BFW_NX5_xmac_stop_sample_pos_reserved1       = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STOP_SAMPLE_POS_BIT_Ttag {
	unsigned int stop_sample_pos : BFW_NX5_xmac_stop_sample_pos_stop_sample_pos; /* data is sampled and averaged if start_sample_pos <= rate_mul < stop_sample_pos */
	unsigned int reserved1       : BFW_NX5_xmac_stop_sample_pos_reserved1;       /* reserved                                                                       */
} NX5_XMAC_STOP_SAMPLE_POS_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_XMAC_STOP_SAMPLE_POS_BIT_T bf;
} NX5_XMAC_STOP_SAMPLE_POS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_config_obu */
/* => xMAC Config Register for OBU */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_config_obu   0x0000091CU
#define Adr_NX5_xmac0_xmac_config_obu 0x018E091CU
#define Adr_NX5_xmac1_xmac_config_obu 0x018E191CU
#define DFLT_VAL_NX5_xmac_config_obu  0x00000180U

#define MSK_NX5_xmac_config_obu_sync_to_eclk               0x00000001U
#define SRT_NX5_xmac_config_obu_sync_to_eclk               0
#define DFLT_VAL_NX5_xmac_config_obu_sync_to_eclk          0x00000000U
#define MSK_NX5_xmac_config_obu_sync_to_bitstream          0x00000002U
#define SRT_NX5_xmac_config_obu_sync_to_bitstream          1
#define DFLT_VAL_NX5_xmac_config_obu_sync_to_bitstream     0x00000000U
#define MSK_NX5_xmac_config_obu_sync_to_posedge            0x00000004U
#define SRT_NX5_xmac_config_obu_sync_to_posedge            2
#define DFLT_VAL_NX5_xmac_config_obu_sync_to_posedge       0x00000000U
#define MSK_NX5_xmac_config_obu_sync_to_negedge            0x00000008U
#define SRT_NX5_xmac_config_obu_sync_to_negedge            3
#define DFLT_VAL_NX5_xmac_config_obu_sync_to_negedge       0x00000000U
#define MSK_NX5_xmac_config_obu_count_modulo               0x00000010U
#define SRT_NX5_xmac_config_obu_count_modulo               4
#define DFLT_VAL_NX5_xmac_config_obu_count_modulo          0x00000000U
#define MSK_NX5_xmac_config_obu_invert_tx_oe               0x00000020U
#define SRT_NX5_xmac_config_obu_invert_tx_oe               5
#define DFLT_VAL_NX5_xmac_config_obu_invert_tx_oe          0x00000000U
#define MSK_NX5_xmac_config_obu_predivide_clk              0x00000040U
#define SRT_NX5_xmac_config_obu_predivide_clk              6
#define DFLT_VAL_NX5_xmac_config_obu_predivide_clk         0x00000000U
#define MSK_NX5_xmac_config_obu_tx_three_state             0x00000080U
#define SRT_NX5_xmac_config_obu_tx_three_state             7
#define DFLT_VAL_NX5_xmac_config_obu_tx_three_state        0x00000080U
#define MSK_NX5_xmac_config_obu_eclk_noe                   0x00000100U
#define SRT_NX5_xmac_config_obu_eclk_noe                   8
#define DFLT_VAL_NX5_xmac_config_obu_eclk_noe              0x00000100U
#define MSK_NX5_xmac_config_obu_sample_bitstream_eclk      0x00000200U
#define SRT_NX5_xmac_config_obu_sample_bitstream_eclk      9
#define DFLT_VAL_NX5_xmac_config_obu_sample_bitstream_eclk 0x00000000U

enum {
	BFW_NX5_xmac_config_obu_sync_to_eclk          = 1,  /* [0] */
	BFW_NX5_xmac_config_obu_sync_to_bitstream     = 1,  /* [1] */
	BFW_NX5_xmac_config_obu_sync_to_posedge       = 1,  /* [2] */
	BFW_NX5_xmac_config_obu_sync_to_negedge       = 1,  /* [3] */
	BFW_NX5_xmac_config_obu_count_modulo          = 1,  /* [4] */
	BFW_NX5_xmac_config_obu_invert_tx_oe          = 1,  /* [5] */
	BFW_NX5_xmac_config_obu_predivide_clk         = 1,  /* [6] */
	BFW_NX5_xmac_config_obu_tx_three_state        = 1,  /* [7] */
	BFW_NX5_xmac_config_obu_eclk_noe              = 1,  /* [8] */
	BFW_NX5_xmac_config_obu_sample_bitstream_eclk = 1,  /* [9] */
	BFW_NX5_xmac_config_obu_reserved1             = 22  /* [31:10] */
};

typedef struct NX5_XMAC_CONFIG_OBU_BIT_Ttag {
	unsigned int sync_to_eclk          : BFW_NX5_xmac_config_obu_sync_to_eclk;          /* Synchronize rate_multiplier to external clock,                                      */
	                                                                                    /* rate_mul is set to rate_mul_start at pos/negedge of eclk                            */
	unsigned int sync_to_bitstream     : BFW_NX5_xmac_config_obu_sync_to_bitstream;     /* Synchronize rate_multiplier to data_in,                                             */
	                                                                                    /* rate_mul is set to rate_mul_start at pos/negedge of data_in                         */
	unsigned int sync_to_posedge       : BFW_NX5_xmac_config_obu_sync_to_posedge;       /* Synchronization of rate_multiplier works on positive edges of data_in/eclk          */
	unsigned int sync_to_negedge       : BFW_NX5_xmac_config_obu_sync_to_negedge;       /* Synchronization of rate_multiplier works on negative edges of data_in/eclk          */
	unsigned int count_modulo          : BFW_NX5_xmac_config_obu_count_modulo;          /* rate_multiplier continues counting after maximum value is reached                   */
	unsigned int invert_tx_oe          : BFW_NX5_xmac_config_obu_invert_tx_oe;          /* Invert outgoing tx_bit_oe:                                                          */
	                                                                                    /* Only the output_enable going to pad tx_bit_oe (mii_txen) is inverted,               */
	unsigned int predivide_clk         : BFW_NX5_xmac_config_obu_predivide_clk;         /* use a clock frequency divided by 256                                                */
	unsigned int tx_three_state        : BFW_NX5_xmac_config_obu_tx_three_state;        /* deactivates output enable of actually transmitted bit (or nibble in mii-mode)       */
	unsigned int eclk_noe              : BFW_NX5_xmac_config_obu_eclk_noe;              /* inv. output enable of eclk: 0: eclk generated by xMAC, 1: eclk coming from external */
	unsigned int sample_bitstream_eclk : BFW_NX5_xmac_config_obu_sample_bitstream_eclk; /* 1: sample outgoing bitstream and its oe with eclk (posedge).                        */
	unsigned int reserved1             : BFW_NX5_xmac_config_obu_reserved1;             /* reserved                                                                            */
} NX5_XMAC_CONFIG_OBU_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_CONFIG_OBU_BIT_T bf;
} NX5_XMAC_CONFIG_OBU_T;

/* --------------------------------------------------------------------- */
/* Register xmac_obu_rate_mul_add */
/* => xMAC OBU rate_mul_add: */
/*    Value added each cc to Rate Multiplier. */
/*    rate_mul_add = eclk / clk * 65536 */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_obu_rate_mul_add   0x00000920U
#define Adr_NX5_xmac0_xmac_obu_rate_mul_add 0x018E0920U
#define Adr_NX5_xmac1_xmac_obu_rate_mul_add 0x018E1920U
#define DFLT_VAL_NX5_xmac_obu_rate_mul_add  0x00000001U

#define MSK_NX5_xmac_obu_rate_mul_add_rate_mul_add      0x0000ffffU
#define SRT_NX5_xmac_obu_rate_mul_add_rate_mul_add      0
#define DFLT_VAL_NX5_xmac_obu_rate_mul_add_rate_mul_add 0x00000001U

enum {
	BFW_NX5_xmac_obu_rate_mul_add_rate_mul_add = 16, /* [15:0] */
	BFW_NX5_xmac_obu_rate_mul_add_reserved1    = 16  /* [31:16] */
};

typedef struct NX5_XMAC_OBU_RATE_MUL_ADD_BIT_Ttag {
	unsigned int rate_mul_add : BFW_NX5_xmac_obu_rate_mul_add_rate_mul_add; /* Value added each cc to Rate Multiplier.                             */
	                                                                        /* If rate_mul_add=1:      rate_mul counts from [rate_mul_start:65535] */
	unsigned int reserved1    : BFW_NX5_xmac_obu_rate_mul_add_reserved1;    /* reserved                                                            */
} NX5_XMAC_OBU_RATE_MUL_ADD_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_XMAC_OBU_RATE_MUL_ADD_BIT_T bf;
} NX5_XMAC_OBU_RATE_MUL_ADD_T;

/* --------------------------------------------------------------------- */
/* Register xmac_obu_rate_mul_start */
/* => xMAC OBU rate_mul_start */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_obu_rate_mul_start   0x00000924U
#define Adr_NX5_xmac0_xmac_obu_rate_mul_start 0x018E0924U
#define Adr_NX5_xmac1_xmac_obu_rate_mul_start 0x018E1924U
#define DFLT_VAL_NX5_xmac_obu_rate_mul_start  0x00000000U

#define MSK_NX5_xmac_obu_rate_mul_start_rate_mul_start      0x0000ffffU
#define SRT_NX5_xmac_obu_rate_mul_start_rate_mul_start      0
#define DFLT_VAL_NX5_xmac_obu_rate_mul_start_rate_mul_start 0x00000000U

enum {
	BFW_NX5_xmac_obu_rate_mul_start_rate_mul_start = 16, /* [15:0] */
	BFW_NX5_xmac_obu_rate_mul_start_reserved1      = 16  /* [31:16] */
};

typedef struct NX5_XMAC_OBU_RATE_MUL_START_BIT_Ttag {
	unsigned int rate_mul_start : BFW_NX5_xmac_obu_rate_mul_start_rate_mul_start; /* Value, the Rate Multiplier is set to at sync */
	unsigned int reserved1      : BFW_NX5_xmac_obu_rate_mul_start_reserved1;      /* reserved                                     */
} NX5_XMAC_OBU_RATE_MUL_START_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_XMAC_OBU_RATE_MUL_START_BIT_T bf;
} NX5_XMAC_OBU_RATE_MUL_START_T;

/* --------------------------------------------------------------------- */
/* Register xmac_obu_rate_mul */
/* => xMAC OBU rate_mul */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_obu_rate_mul   0x00000928U
#define Adr_NX5_xmac0_xmac_obu_rate_mul 0x018E0928U
#define Adr_NX5_xmac1_xmac_obu_rate_mul 0x018E1928U
#define DFLT_VAL_NX5_xmac_obu_rate_mul  0x00000000U

#define MSK_NX5_xmac_obu_rate_mul_rate_mul      0x0000ffffU
#define SRT_NX5_xmac_obu_rate_mul_rate_mul      0
#define DFLT_VAL_NX5_xmac_obu_rate_mul_rate_mul 0x00000000U

enum {
	BFW_NX5_xmac_obu_rate_mul_rate_mul  = 16, /* [15:0] */
	BFW_NX5_xmac_obu_rate_mul_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_OBU_RATE_MUL_BIT_Ttag {
	unsigned int rate_mul  : BFW_NX5_xmac_obu_rate_mul_rate_mul;  /* current value of Rate Multiplier */
	unsigned int reserved1 : BFW_NX5_xmac_obu_rate_mul_reserved1; /* reserved                         */
} NX5_XMAC_OBU_RATE_MUL_BIT_T;

typedef union {
	unsigned int                val;
	NX5_XMAC_OBU_RATE_MUL_BIT_T bf;
} NX5_XMAC_OBU_RATE_MUL_T;

/* --------------------------------------------------------------------- */
/* Register xmac_start_trans_pos */
/* => xMAC SBU start_trans_pos */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_start_trans_pos   0x0000092CU
#define Adr_NX5_xmac0_xmac_start_trans_pos 0x018E092CU
#define Adr_NX5_xmac1_xmac_start_trans_pos 0x018E192CU
#define DFLT_VAL_NX5_xmac_start_trans_pos  0x00000000U

#define MSK_NX5_xmac_start_trans_pos_start_trans_pos      0x0000ffffU
#define SRT_NX5_xmac_start_trans_pos_start_trans_pos      0
#define DFLT_VAL_NX5_xmac_start_trans_pos_start_trans_pos 0x00000000U

enum {
	BFW_NX5_xmac_start_trans_pos_start_trans_pos = 16, /* [15:0] */
	BFW_NX5_xmac_start_trans_pos_reserved1       = 16  /* [31:16] */
};

typedef struct NX5_XMAC_START_TRANS_POS_BIT_Ttag {
	unsigned int start_trans_pos : BFW_NX5_xmac_start_trans_pos_start_trans_pos; /* bitstream_out and bitstream_oe change their value at start_trans_pos = rate_mul */
	unsigned int reserved1       : BFW_NX5_xmac_start_trans_pos_reserved1;       /* reserved                                                                        */
} NX5_XMAC_START_TRANS_POS_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_XMAC_START_TRANS_POS_BIT_T bf;
} NX5_XMAC_START_TRANS_POS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_stop_trans_pos */
/* => xMAC SBU stop_trans_pos */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_stop_trans_pos   0x00000930U
#define Adr_NX5_xmac0_xmac_stop_trans_pos 0x018E0930U
#define Adr_NX5_xmac1_xmac_stop_trans_pos 0x018E1930U
#define DFLT_VAL_NX5_xmac_stop_trans_pos  0x00000000U

#define MSK_NX5_xmac_stop_trans_pos_stop_trans_pos      0x0000ffffU
#define SRT_NX5_xmac_stop_trans_pos_stop_trans_pos      0
#define DFLT_VAL_NX5_xmac_stop_trans_pos_stop_trans_pos 0x00000000U

enum {
	BFW_NX5_xmac_stop_trans_pos_stop_trans_pos = 16, /* [15:0] */
	BFW_NX5_xmac_stop_trans_pos_reserved1      = 16  /* [31:16] */
};

typedef struct NX5_XMAC_STOP_TRANS_POS_BIT_Ttag {
	unsigned int stop_trans_pos : BFW_NX5_xmac_stop_trans_pos_stop_trans_pos; /* bitstream_oe becomes 0 if rate_mul >= stop_trans_pos */
	unsigned int reserved1      : BFW_NX5_xmac_stop_trans_pos_reserved1;      /* reserved                                             */
} NX5_XMAC_STOP_TRANS_POS_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_STOP_TRANS_POS_BIT_T bf;
} NX5_XMAC_STOP_TRANS_POS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpu_count1 */
/* => xMAC RPU Counter 1 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpu_count1   0x00000934U
#define Adr_NX5_xmac0_xmac_rpu_count1 0x018E0934U
#define Adr_NX5_xmac1_xmac_rpu_count1 0x018E1934U
#define DFLT_VAL_NX5_xmac_rpu_count1  0x00000000U

#define MSK_NX5_xmac_rpu_count1_rpu_count1      0x0000ffffU
#define SRT_NX5_xmac_rpu_count1_rpu_count1      0
#define DFLT_VAL_NX5_xmac_rpu_count1_rpu_count1 0x00000000U

enum {
	BFW_NX5_xmac_rpu_count1_rpu_count1 = 16, /* [15:0] */
	BFW_NX5_xmac_rpu_count1_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPU_COUNT1_BIT_Ttag {
	unsigned int rpu_count1 : BFW_NX5_xmac_rpu_count1_rpu_count1; /* Counter incremented by rpu-hw_support bit cnt1 */
	unsigned int reserved1  : BFW_NX5_xmac_rpu_count1_reserved1;  /* reserved                                       */
} NX5_XMAC_RPU_COUNT1_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_RPU_COUNT1_BIT_T bf;
} NX5_XMAC_RPU_COUNT1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpu_count2 */
/* => xMAC RPU Counter 2 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpu_count2   0x00000938U
#define Adr_NX5_xmac0_xmac_rpu_count2 0x018E0938U
#define Adr_NX5_xmac1_xmac_rpu_count2 0x018E1938U
#define DFLT_VAL_NX5_xmac_rpu_count2  0x00000000U

#define MSK_NX5_xmac_rpu_count2_rpu_count2      0x0000ffffU
#define SRT_NX5_xmac_rpu_count2_rpu_count2      0
#define DFLT_VAL_NX5_xmac_rpu_count2_rpu_count2 0x00000000U

enum {
	BFW_NX5_xmac_rpu_count2_rpu_count2 = 16, /* [15:0] */
	BFW_NX5_xmac_rpu_count2_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPU_COUNT2_BIT_Ttag {
	unsigned int rpu_count2 : BFW_NX5_xmac_rpu_count2_rpu_count2; /* Counter incremented by rpu-hw_support bit cnt2 */
	unsigned int reserved1  : BFW_NX5_xmac_rpu_count2_reserved1;  /* reserved                                       */
} NX5_XMAC_RPU_COUNT2_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_RPU_COUNT2_BIT_T bf;
} NX5_XMAC_RPU_COUNT2_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpu_count1 */
/* => xMAC TPU Counter 1 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpu_count1   0x0000093CU
#define Adr_NX5_xmac0_xmac_tpu_count1 0x018E093CU
#define Adr_NX5_xmac1_xmac_tpu_count1 0x018E193CU
#define DFLT_VAL_NX5_xmac_tpu_count1  0x00000000U

#define MSK_NX5_xmac_tpu_count1_tpu_count1      0x0000ffffU
#define SRT_NX5_xmac_tpu_count1_tpu_count1      0
#define DFLT_VAL_NX5_xmac_tpu_count1_tpu_count1 0x00000000U

enum {
	BFW_NX5_xmac_tpu_count1_tpu_count1 = 16, /* [15:0] */
	BFW_NX5_xmac_tpu_count1_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPU_COUNT1_BIT_Ttag {
	unsigned int tpu_count1 : BFW_NX5_xmac_tpu_count1_tpu_count1; /* Counter incremented by tpu-hw_support bit cnt1 */
	unsigned int reserved1  : BFW_NX5_xmac_tpu_count1_reserved1;  /* reserved                                       */
} NX5_XMAC_TPU_COUNT1_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_TPU_COUNT1_BIT_T bf;
} NX5_XMAC_TPU_COUNT1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpu_count2 */
/* => xMAC TPU Counter 2 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpu_count2   0x00000940U
#define Adr_NX5_xmac0_xmac_tpu_count2 0x018E0940U
#define Adr_NX5_xmac1_xmac_tpu_count2 0x018E1940U
#define DFLT_VAL_NX5_xmac_tpu_count2  0x00000000U

#define MSK_NX5_xmac_tpu_count2_tpu_count2      0x0000ffffU
#define SRT_NX5_xmac_tpu_count2_tpu_count2      0
#define DFLT_VAL_NX5_xmac_tpu_count2_tpu_count2 0x00000000U

enum {
	BFW_NX5_xmac_tpu_count2_tpu_count2 = 16, /* [15:0] */
	BFW_NX5_xmac_tpu_count2_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPU_COUNT2_BIT_Ttag {
	unsigned int tpu_count2 : BFW_NX5_xmac_tpu_count2_tpu_count2; /* Counter incremented by tpu-hw_support bit cnt2 */
	unsigned int reserved1  : BFW_NX5_xmac_tpu_count2_reserved1;  /* reserved                                       */
} NX5_XMAC_TPU_COUNT2_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_TPU_COUNT2_BIT_T bf;
} NX5_XMAC_TPU_COUNT2_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_count */
/* => xMAC RX Counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_count   0x00000944U
#define Adr_NX5_xmac0_xmac_rx_count 0x018E0944U
#define Adr_NX5_xmac1_xmac_rx_count 0x018E1944U
#define DFLT_VAL_NX5_xmac_rx_count  0x00000000U

#define MSK_NX5_xmac_rx_count_rx_count      0x0000ffffU
#define SRT_NX5_xmac_rx_count_rx_count      0
#define DFLT_VAL_NX5_xmac_rx_count_rx_count 0x00000000U

enum {
	BFW_NX5_xmac_rx_count_rx_count  = 16, /* [15:0] */
	BFW_NX5_xmac_rx_count_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_COUNT_BIT_Ttag {
	unsigned int rx_count  : BFW_NX5_xmac_rx_count_rx_count;  /* Counter running on eclk */
	unsigned int reserved1 : BFW_NX5_xmac_rx_count_reserved1; /* reserved                */
} NX5_XMAC_RX_COUNT_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_RX_COUNT_BIT_T bf;
} NX5_XMAC_RX_COUNT_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_count */
/* => xMAC TX Counter */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_count   0x00000948U
#define Adr_NX5_xmac0_xmac_tx_count 0x018E0948U
#define Adr_NX5_xmac1_xmac_tx_count 0x018E1948U
#define DFLT_VAL_NX5_xmac_tx_count  0x00000000U

#define MSK_NX5_xmac_tx_count_tx_count      0x0000ffffU
#define SRT_NX5_xmac_tx_count_tx_count      0
#define DFLT_VAL_NX5_xmac_tx_count_tx_count 0x00000000U

enum {
	BFW_NX5_xmac_tx_count_tx_count  = 16, /* [15:0] */
	BFW_NX5_xmac_tx_count_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_COUNT_BIT_Ttag {
	unsigned int tx_count  : BFW_NX5_xmac_tx_count_tx_count;  /* Counter running on eclk */
	unsigned int reserved1 : BFW_NX5_xmac_tx_count_reserved1; /* reserved                */
} NX5_XMAC_TX_COUNT_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_TX_COUNT_BIT_T bf;
} NX5_XMAC_TX_COUNT_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpm_mask0 */
/* => xMAC Receive Pattern Match Mask 0 Register: */
/*    Defines, which bits are compared between xmac_rpm_val0 and xmac_rx. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpm_mask0   0x0000094CU
#define Adr_NX5_xmac0_xmac_rpm_mask0 0x018E094CU
#define Adr_NX5_xmac1_xmac_rpm_mask0 0x018E194CU
#define DFLT_VAL_NX5_xmac_rpm_mask0  0x00000000U

#define MSK_NX5_xmac_rpm_mask0_PM_MASK0      0x0000ffffU
#define SRT_NX5_xmac_rpm_mask0_PM_MASK0      0
#define DFLT_VAL_NX5_xmac_rpm_mask0_PM_MASK0 0x00000000U

enum {
	BFW_NX5_xmac_rpm_mask0_PM_MASK0  = 16, /* [15:0] */
	BFW_NX5_xmac_rpm_mask0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPM_MASK0_BIT_Ttag {
	unsigned int PM_MASK0  : BFW_NX5_xmac_rpm_mask0_PM_MASK0;  /* Pattern Match Mask:                                   */
	                                                           /* 1: compare this position of xmac_rpm_val0 and xmac_rx */
	unsigned int reserved1 : BFW_NX5_xmac_rpm_mask0_reserved1; /* reserved                                              */
} NX5_XMAC_RPM_MASK0_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XMAC_RPM_MASK0_BIT_T bf;
} NX5_XMAC_RPM_MASK0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpm_val0 */
/* => xMAC Receive Pattern Match Value 0 Register: */
/*    Defines value of bits to be compared with xmac_rx. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpm_val0   0x00000950U
#define Adr_NX5_xmac0_xmac_rpm_val0 0x018E0950U
#define Adr_NX5_xmac1_xmac_rpm_val0 0x018E1950U
#define DFLT_VAL_NX5_xmac_rpm_val0  0x00000000U

#define MSK_NX5_xmac_rpm_val0_PM_VAL0      0x0000ffffU
#define SRT_NX5_xmac_rpm_val0_PM_VAL0      0
#define DFLT_VAL_NX5_xmac_rpm_val0_PM_VAL0 0x00000000U

enum {
	BFW_NX5_xmac_rpm_val0_PM_VAL0   = 16, /* [15:0] */
	BFW_NX5_xmac_rpm_val0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPM_VAL0_BIT_Ttag {
	unsigned int PM_VAL0   : BFW_NX5_xmac_rpm_val0_PM_VAL0;   /* Pattern Match Value */
	unsigned int reserved1 : BFW_NX5_xmac_rpm_val0_reserved1; /* reserved            */
} NX5_XMAC_RPM_VAL0_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_RPM_VAL0_BIT_T bf;
} NX5_XMAC_RPM_VAL0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpm_mask1 */
/* => xMAC Receive Pattern Match Mask 1 Register: */
/*    Defines, which bits are compared between xmac_rpm_val1 and xmac_rx */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpm_mask1   0x00000954U
#define Adr_NX5_xmac0_xmac_rpm_mask1 0x018E0954U
#define Adr_NX5_xmac1_xmac_rpm_mask1 0x018E1954U
#define DFLT_VAL_NX5_xmac_rpm_mask1  0x00000000U

#define MSK_NX5_xmac_rpm_mask1_PM_MASK1      0x0000ffffU
#define SRT_NX5_xmac_rpm_mask1_PM_MASK1      0
#define DFLT_VAL_NX5_xmac_rpm_mask1_PM_MASK1 0x00000000U

enum {
	BFW_NX5_xmac_rpm_mask1_PM_MASK1  = 16, /* [15:0] */
	BFW_NX5_xmac_rpm_mask1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPM_MASK1_BIT_Ttag {
	unsigned int PM_MASK1  : BFW_NX5_xmac_rpm_mask1_PM_MASK1;  /* Pattern Match Mask:                                   */
	                                                           /* 1: compare this position of xmac_rpm_val1 and xmac_rx */
	unsigned int reserved1 : BFW_NX5_xmac_rpm_mask1_reserved1; /* reserved                                              */
} NX5_XMAC_RPM_MASK1_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XMAC_RPM_MASK1_BIT_T bf;
} NX5_XMAC_RPM_MASK1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpm_val1 */
/* => xMAC Receive Pattern Match Value 1 Register: */
/*    Defines value of bits to be compared with xmac_rx. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpm_val1   0x00000958U
#define Adr_NX5_xmac0_xmac_rpm_val1 0x018E0958U
#define Adr_NX5_xmac1_xmac_rpm_val1 0x018E1958U
#define DFLT_VAL_NX5_xmac_rpm_val1  0x00000000U

#define MSK_NX5_xmac_rpm_val1_PM_VAL1      0x0000ffffU
#define SRT_NX5_xmac_rpm_val1_PM_VAL1      0
#define DFLT_VAL_NX5_xmac_rpm_val1_PM_VAL1 0x00000000U

enum {
	BFW_NX5_xmac_rpm_val1_PM_VAL1   = 16, /* [15:0] */
	BFW_NX5_xmac_rpm_val1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPM_VAL1_BIT_Ttag {
	unsigned int PM_VAL1   : BFW_NX5_xmac_rpm_val1_PM_VAL1;   /* Pattern Match Value */
	unsigned int reserved1 : BFW_NX5_xmac_rpm_val1_reserved1; /* reserved            */
} NX5_XMAC_RPM_VAL1_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_RPM_VAL1_BIT_T bf;
} NX5_XMAC_RPM_VAL1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpm_mask0 */
/* => xMAC Transmit Pattern Match Mask 0 Register: */
/*    Defines, which bits are compared between xmac_tpm_val0 and xmac_tx_sent. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpm_mask0   0x0000095CU
#define Adr_NX5_xmac0_xmac_tpm_mask0 0x018E095CU
#define Adr_NX5_xmac1_xmac_tpm_mask0 0x018E195CU
#define DFLT_VAL_NX5_xmac_tpm_mask0  0x00000000U

#define MSK_NX5_xmac_tpm_mask0_PM_MASK0      0x0000ffffU
#define SRT_NX5_xmac_tpm_mask0_PM_MASK0      0
#define DFLT_VAL_NX5_xmac_tpm_mask0_PM_MASK0 0x00000000U

enum {
	BFW_NX5_xmac_tpm_mask0_PM_MASK0  = 16, /* [15:0] */
	BFW_NX5_xmac_tpm_mask0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPM_MASK0_BIT_Ttag {
	unsigned int PM_MASK0  : BFW_NX5_xmac_tpm_mask0_PM_MASK0;  /* Pattern Match Mask:                                        */
	                                                           /* 1: compare this position of xmac_tpm_val0 and xmac_tx_sent */
	unsigned int reserved1 : BFW_NX5_xmac_tpm_mask0_reserved1; /* reserved                                                   */
} NX5_XMAC_TPM_MASK0_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XMAC_TPM_MASK0_BIT_T bf;
} NX5_XMAC_TPM_MASK0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpm_val0 */
/* => xMAC Transmit Pattern Match Value 0 Register: */
/*    Defines value of bits to be compared with xmac_tx_sent. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpm_val0   0x00000960U
#define Adr_NX5_xmac0_xmac_tpm_val0 0x018E0960U
#define Adr_NX5_xmac1_xmac_tpm_val0 0x018E1960U
#define DFLT_VAL_NX5_xmac_tpm_val0  0x00000000U

#define MSK_NX5_xmac_tpm_val0_PM_VAL0      0x0000ffffU
#define SRT_NX5_xmac_tpm_val0_PM_VAL0      0
#define DFLT_VAL_NX5_xmac_tpm_val0_PM_VAL0 0x00000000U

enum {
	BFW_NX5_xmac_tpm_val0_PM_VAL0   = 16, /* [15:0] */
	BFW_NX5_xmac_tpm_val0_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPM_VAL0_BIT_Ttag {
	unsigned int PM_VAL0   : BFW_NX5_xmac_tpm_val0_PM_VAL0;   /* Pattern Match Value */
	unsigned int reserved1 : BFW_NX5_xmac_tpm_val0_reserved1; /* reserved            */
} NX5_XMAC_TPM_VAL0_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_TPM_VAL0_BIT_T bf;
} NX5_XMAC_TPM_VAL0_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpm_mask1 */
/* => xMAC Transmit Pattern Match Mask 1 Register: */
/*    Defines, which bits are compared between xmac_tpm_val1 and xmac_tx_sent. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpm_mask1   0x00000964U
#define Adr_NX5_xmac0_xmac_tpm_mask1 0x018E0964U
#define Adr_NX5_xmac1_xmac_tpm_mask1 0x018E1964U
#define DFLT_VAL_NX5_xmac_tpm_mask1  0x00000000U

#define MSK_NX5_xmac_tpm_mask1_PM_MASK1      0x0000ffffU
#define SRT_NX5_xmac_tpm_mask1_PM_MASK1      0
#define DFLT_VAL_NX5_xmac_tpm_mask1_PM_MASK1 0x00000000U

enum {
	BFW_NX5_xmac_tpm_mask1_PM_MASK1  = 16, /* [15:0] */
	BFW_NX5_xmac_tpm_mask1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPM_MASK1_BIT_Ttag {
	unsigned int PM_MASK1  : BFW_NX5_xmac_tpm_mask1_PM_MASK1;  /* Pattern Match Mask:                                        */
	                                                           /* 1: compare this position of xmac_tpm_val1 and xmac_tx_sent */
	unsigned int reserved1 : BFW_NX5_xmac_tpm_mask1_reserved1; /* reserved                                                   */
} NX5_XMAC_TPM_MASK1_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XMAC_TPM_MASK1_BIT_T bf;
} NX5_XMAC_TPM_MASK1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpm_val1 */
/* => xMAC Transmit Pattern Match Value 1 Register: */
/*    Defines value of bits to be compared with xmac_tx_sent. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpm_val1   0x00000968U
#define Adr_NX5_xmac0_xmac_tpm_val1 0x018E0968U
#define Adr_NX5_xmac1_xmac_tpm_val1 0x018E1968U
#define DFLT_VAL_NX5_xmac_tpm_val1  0x00000000U

#define MSK_NX5_xmac_tpm_val1_PM_VAL1      0x0000ffffU
#define SRT_NX5_xmac_tpm_val1_PM_VAL1      0
#define DFLT_VAL_NX5_xmac_tpm_val1_PM_VAL1 0x00000000U

enum {
	BFW_NX5_xmac_tpm_val1_PM_VAL1   = 16, /* [15:0] */
	BFW_NX5_xmac_tpm_val1_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPM_VAL1_BIT_Ttag {
	unsigned int PM_VAL1   : BFW_NX5_xmac_tpm_val1_PM_VAL1;   /* Pattern Match Value */
	unsigned int reserved1 : BFW_NX5_xmac_tpm_val1_reserved1; /* reserved            */
} NX5_XMAC_TPM_VAL1_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_TPM_VAL1_BIT_T bf;
} NX5_XMAC_TPM_VAL1_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_tx_nof_bits */
/* => xMAC RX / TX number of bits */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_tx_nof_bits   0x000009BCU
#define Adr_NX5_xmac0_xmac_rx_tx_nof_bits 0x018E09BCU
#define Adr_NX5_xmac1_xmac_rx_tx_nof_bits 0x018E19BCU
#define DFLT_VAL_NX5_xmac_rx_tx_nof_bits  0x00000088U

#define MSK_NX5_xmac_rx_tx_nof_bits_rx_nof_bits      0x0000000fU
#define SRT_NX5_xmac_rx_tx_nof_bits_rx_nof_bits      0
#define DFLT_VAL_NX5_xmac_rx_tx_nof_bits_rx_nof_bits 0x00000008U
#define MSK_NX5_xmac_rx_tx_nof_bits_tx_nof_bits      0x000000f0U
#define SRT_NX5_xmac_rx_tx_nof_bits_tx_nof_bits      4
#define DFLT_VAL_NX5_xmac_rx_tx_nof_bits_tx_nof_bits 0x00000080U

enum {
	BFW_NX5_xmac_rx_tx_nof_bits_rx_nof_bits = 4,  /* [3:0] */
	BFW_NX5_xmac_rx_tx_nof_bits_tx_nof_bits = 4,  /* [7:4] */
	BFW_NX5_xmac_rx_tx_nof_bits_reserved1   = 24  /* [31:8] */
};

typedef struct NX5_XMAC_RX_TX_NOF_BITS_BIT_Ttag {
	unsigned int rx_nof_bits : BFW_NX5_xmac_rx_tx_nof_bits_rx_nof_bits; /* Number of bits written by SBU to rx-register, only used for rx_hw_count */
	unsigned int tx_nof_bits : BFW_NX5_xmac_rx_tx_nof_bits_tx_nof_bits; /* Number of bits read by OBU from tx-register                             */
	unsigned int reserved1   : BFW_NX5_xmac_rx_tx_nof_bits_reserved1;   /* reserved                                                                */
} NX5_XMAC_RX_TX_NOF_BITS_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_XMAC_RX_TX_NOF_BITS_BIT_T bf;
} NX5_XMAC_RX_TX_NOF_BITS_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc32_l */
/* => xMAC RX CRC32 lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc32_l   0x000009C0U
#define Adr_NX5_xmac0_xmac_rx_crc32_l 0x018E09C0U
#define Adr_NX5_xmac1_xmac_rx_crc32_l 0x018E19C0U
#define DFLT_VAL_NX5_xmac_rx_crc32_l  0x00000000U

#define MSK_NX5_xmac_rx_crc32_l_RX_CRC32_L      0x0000ffffU
#define SRT_NX5_xmac_rx_crc32_l_RX_CRC32_L      0
#define DFLT_VAL_NX5_xmac_rx_crc32_l_RX_CRC32_L 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc32_l_RX_CRC32_L = 16, /* [15:0] */
	BFW_NX5_xmac_rx_crc32_l_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_CRC32_L_BIT_Ttag {
	unsigned int RX_CRC32_L : BFW_NX5_xmac_rx_crc32_l_RX_CRC32_L; /* lower bits of RX-CRC32 */
	unsigned int reserved1  : BFW_NX5_xmac_rx_crc32_l_reserved1;  /* reserved               */
} NX5_XMAC_RX_CRC32_L_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_RX_CRC32_L_BIT_T bf;
} NX5_XMAC_RX_CRC32_L_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc32_h */
/* => xMAC RX CRC32 upper part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc32_h   0x000009C4U
#define Adr_NX5_xmac0_xmac_rx_crc32_h 0x018E09C4U
#define Adr_NX5_xmac1_xmac_rx_crc32_h 0x018E19C4U
#define DFLT_VAL_NX5_xmac_rx_crc32_h  0x00000000U

#define MSK_NX5_xmac_rx_crc32_h_RX_CRC32_H      0x0000ffffU
#define SRT_NX5_xmac_rx_crc32_h_RX_CRC32_H      0
#define DFLT_VAL_NX5_xmac_rx_crc32_h_RX_CRC32_H 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc32_h_RX_CRC32_H = 16, /* [15:0] */
	BFW_NX5_xmac_rx_crc32_h_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_CRC32_H_BIT_Ttag {
	unsigned int RX_CRC32_H : BFW_NX5_xmac_rx_crc32_h_RX_CRC32_H; /* upper bits of RX-CRC32 */
	unsigned int reserved1  : BFW_NX5_xmac_rx_crc32_h_reserved1;  /* reserved               */
} NX5_XMAC_RX_CRC32_H_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_RX_CRC32_H_BIT_T bf;
} NX5_XMAC_RX_CRC32_H_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc32_cfg */
/* => xMAC RX CRC32 Config Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc32_cfg   0x000009C8U
#define Adr_NX5_xmac0_xmac_rx_crc32_cfg 0x018E09C8U
#define Adr_NX5_xmac1_xmac_rx_crc32_cfg 0x018E19C8U
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg  0x00000000U

#define MSK_NX5_xmac_rx_crc32_cfg_shift_right      0x00000001U
#define SRT_NX5_xmac_rx_crc32_cfg_shift_right      0
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_shift_right 0x00000000U
#define MSK_NX5_xmac_rx_crc32_cfg_zero             0x00000002U
#define SRT_NX5_xmac_rx_crc32_cfg_zero             1
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_zero        0x00000000U
#define MSK_NX5_xmac_rx_crc32_cfg_invert           0x00000004U
#define SRT_NX5_xmac_rx_crc32_cfg_invert           2
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_invert      0x00000000U
#define MSK_NX5_xmac_rx_crc32_cfg_nof_bits         0x00000300U
#define SRT_NX5_xmac_rx_crc32_cfg_nof_bits         8
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_nof_bits    0x00000000U
#define MSK_NX5_xmac_rx_crc32_cfg_direct_div       0x00000400U
#define SRT_NX5_xmac_rx_crc32_cfg_direct_div       10
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_direct_div  0x00000000U
#define MSK_NX5_xmac_rx_crc32_cfg_endian           0x00000800U
#define SRT_NX5_xmac_rx_crc32_cfg_endian           11
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_endian      0x00000000U
#define MSK_NX5_xmac_rx_crc32_cfg_swap_output      0x00001000U
#define SRT_NX5_xmac_rx_crc32_cfg_swap_output      12
#define DFLT_VAL_NX5_xmac_rx_crc32_cfg_swap_output 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc32_cfg_shift_right = 1,  /* [0] */
	BFW_NX5_xmac_rx_crc32_cfg_zero        = 1,  /* [1] */
	BFW_NX5_xmac_rx_crc32_cfg_invert      = 1,  /* [2] */
	BFW_NX5_xmac_rx_crc32_cfg_reserved1   = 5,  /* [7:3] */
	BFW_NX5_xmac_rx_crc32_cfg_nof_bits    = 2,  /* [9:8] */
	BFW_NX5_xmac_rx_crc32_cfg_direct_div  = 1,  /* [10] */
	BFW_NX5_xmac_rx_crc32_cfg_endian      = 1,  /* [11] */
	BFW_NX5_xmac_rx_crc32_cfg_swap_output = 1,  /* [12] */
	BFW_NX5_xmac_rx_crc32_cfg_reserved2   = 19  /* [31:13] */
};

typedef struct NX5_XMAC_RX_CRC32_CFG_BIT_Ttag {
	unsigned int shift_right : BFW_NX5_xmac_rx_crc32_cfg_shift_right; /* Shift RX CRC32 from left to right                                      */
	                                                                  /* (usually used with crc_swap_output but inverted in case of crc_endian) */
	unsigned int zero        : BFW_NX5_xmac_rx_crc32_cfg_zero;        /* Set input of RX CRC32 to zero (before invert)                          */
	unsigned int invert      : BFW_NX5_xmac_rx_crc32_cfg_invert;      /* Invert input of RX CRC32                                               */
	unsigned int reserved1   : BFW_NX5_xmac_rx_crc32_cfg_reserved1;   /* reserved                                                               */
	unsigned int nof_bits    : BFW_NX5_xmac_rx_crc32_cfg_nof_bits;    /* 1(0),2(1),4(2),8(3) Bits from rx register to be executed in parallel   */
	unsigned int direct_div  : BFW_NX5_xmac_rx_crc32_cfg_direct_div;  /* calculate direct polynomial division without n zeros after frame       */
	unsigned int endian      : BFW_NX5_xmac_rx_crc32_cfg_endian;      /* Swap incoming bits in case of nof_bits = 2,4,8                         */
	unsigned int swap_output : BFW_NX5_xmac_rx_crc32_cfg_swap_output; /* Swap output of crc at PU access                                        */
	unsigned int reserved2   : BFW_NX5_xmac_rx_crc32_cfg_reserved2;   /* reserved                                                               */
} NX5_XMAC_RX_CRC32_CFG_BIT_T;

typedef union {
	unsigned int                val;
	NX5_XMAC_RX_CRC32_CFG_BIT_T bf;
} NX5_XMAC_RX_CRC32_CFG_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc32_l */
/* => xMAC TX CRC32 lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc32_l   0x000009CCU
#define Adr_NX5_xmac0_xmac_tx_crc32_l 0x018E09CCU
#define Adr_NX5_xmac1_xmac_tx_crc32_l 0x018E19CCU
#define DFLT_VAL_NX5_xmac_tx_crc32_l  0x00000000U

#define MSK_NX5_xmac_tx_crc32_l_TX_CRC32_L      0x0000ffffU
#define SRT_NX5_xmac_tx_crc32_l_TX_CRC32_L      0
#define DFLT_VAL_NX5_xmac_tx_crc32_l_TX_CRC32_L 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc32_l_TX_CRC32_L = 16, /* [15:0] */
	BFW_NX5_xmac_tx_crc32_l_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_CRC32_L_BIT_Ttag {
	unsigned int TX_CRC32_L : BFW_NX5_xmac_tx_crc32_l_TX_CRC32_L; /* lower bits of TX-CRC32 */
	unsigned int reserved1  : BFW_NX5_xmac_tx_crc32_l_reserved1;  /* reserved               */
} NX5_XMAC_TX_CRC32_L_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_TX_CRC32_L_BIT_T bf;
} NX5_XMAC_TX_CRC32_L_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc32_h */
/* => xMAC TX CRC32 upper part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc32_h   0x000009D0U
#define Adr_NX5_xmac0_xmac_tx_crc32_h 0x018E09D0U
#define Adr_NX5_xmac1_xmac_tx_crc32_h 0x018E19D0U
#define DFLT_VAL_NX5_xmac_tx_crc32_h  0x00000000U

#define MSK_NX5_xmac_tx_crc32_h_TX_CRC32_H      0x0000ffffU
#define SRT_NX5_xmac_tx_crc32_h_TX_CRC32_H      0
#define DFLT_VAL_NX5_xmac_tx_crc32_h_TX_CRC32_H 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc32_h_TX_CRC32_H = 16, /* [15:0] */
	BFW_NX5_xmac_tx_crc32_h_reserved1  = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_CRC32_H_BIT_Ttag {
	unsigned int TX_CRC32_H : BFW_NX5_xmac_tx_crc32_h_TX_CRC32_H; /* upper bits of TX-CRC32 */
	unsigned int reserved1  : BFW_NX5_xmac_tx_crc32_h_reserved1;  /* reserved               */
} NX5_XMAC_TX_CRC32_H_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_TX_CRC32_H_BIT_T bf;
} NX5_XMAC_TX_CRC32_H_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc32_cfg */
/* => xMAC TX CRC32 Config Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc32_cfg   0x000009D4U
#define Adr_NX5_xmac0_xmac_tx_crc32_cfg 0x018E09D4U
#define Adr_NX5_xmac1_xmac_tx_crc32_cfg 0x018E19D4U
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg  0x00000000U

#define MSK_NX5_xmac_tx_crc32_cfg_shift_right      0x00000001U
#define SRT_NX5_xmac_tx_crc32_cfg_shift_right      0
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_shift_right 0x00000000U
#define MSK_NX5_xmac_tx_crc32_cfg_zero             0x00000002U
#define SRT_NX5_xmac_tx_crc32_cfg_zero             1
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_zero        0x00000000U
#define MSK_NX5_xmac_tx_crc32_cfg_invert           0x00000004U
#define SRT_NX5_xmac_tx_crc32_cfg_invert           2
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_invert      0x00000000U
#define MSK_NX5_xmac_tx_crc32_cfg_nof_bits         0x00000300U
#define SRT_NX5_xmac_tx_crc32_cfg_nof_bits         8
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_nof_bits    0x00000000U
#define MSK_NX5_xmac_tx_crc32_cfg_direct_div       0x00000400U
#define SRT_NX5_xmac_tx_crc32_cfg_direct_div       10
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_direct_div  0x00000000U
#define MSK_NX5_xmac_tx_crc32_cfg_endian           0x00000800U
#define SRT_NX5_xmac_tx_crc32_cfg_endian           11
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_endian      0x00000000U
#define MSK_NX5_xmac_tx_crc32_cfg_swap_output      0x00001000U
#define SRT_NX5_xmac_tx_crc32_cfg_swap_output      12
#define DFLT_VAL_NX5_xmac_tx_crc32_cfg_swap_output 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc32_cfg_shift_right = 1,  /* [0] */
	BFW_NX5_xmac_tx_crc32_cfg_zero        = 1,  /* [1] */
	BFW_NX5_xmac_tx_crc32_cfg_invert      = 1,  /* [2] */
	BFW_NX5_xmac_tx_crc32_cfg_reserved1   = 5,  /* [7:3] */
	BFW_NX5_xmac_tx_crc32_cfg_nof_bits    = 2,  /* [9:8] */
	BFW_NX5_xmac_tx_crc32_cfg_direct_div  = 1,  /* [10] */
	BFW_NX5_xmac_tx_crc32_cfg_endian      = 1,  /* [11] */
	BFW_NX5_xmac_tx_crc32_cfg_swap_output = 1,  /* [12] */
	BFW_NX5_xmac_tx_crc32_cfg_reserved2   = 19  /* [31:13] */
};

typedef struct NX5_XMAC_TX_CRC32_CFG_BIT_Ttag {
	unsigned int shift_right : BFW_NX5_xmac_tx_crc32_cfg_shift_right; /* Shift TX CRC32 from left to right                                      */
	                                                                  /* (usually used with crc_swap_output but inverted in case of crc_endian) */
	unsigned int zero        : BFW_NX5_xmac_tx_crc32_cfg_zero;        /* Set input of TX CRC32 to zero (before invert)                          */
	unsigned int invert      : BFW_NX5_xmac_tx_crc32_cfg_invert;      /* Invert input of TX CRC32                                               */
	unsigned int reserved1   : BFW_NX5_xmac_tx_crc32_cfg_reserved1;   /* reserved                                                               */
	unsigned int nof_bits    : BFW_NX5_xmac_tx_crc32_cfg_nof_bits;    /* 1(0),2(1),4(2),8(3) Bits from tx_register to be executed in parallel   */
	unsigned int direct_div  : BFW_NX5_xmac_tx_crc32_cfg_direct_div;  /* calculate direct polynomial division without n zeros after frame       */
	unsigned int endian      : BFW_NX5_xmac_tx_crc32_cfg_endian;      /* Swap incoming bits in case of nof_bits = 2,4,8                         */
	unsigned int swap_output : BFW_NX5_xmac_tx_crc32_cfg_swap_output; /* Swap output of crc at PU access                                        */
	unsigned int reserved2   : BFW_NX5_xmac_tx_crc32_cfg_reserved2;   /* reserved                                                               */
} NX5_XMAC_TX_CRC32_CFG_BIT_T;

typedef union {
	unsigned int                val;
	NX5_XMAC_TX_CRC32_CFG_BIT_T bf;
} NX5_XMAC_TX_CRC32_CFG_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc_polynomial_l */
/* => xMAC RX CRC Polynomial lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc_polynomial_l   0x000009D8U
#define Adr_NX5_xmac0_xmac_rx_crc_polynomial_l 0x018E09D8U
#define Adr_NX5_xmac1_xmac_rx_crc_polynomial_l 0x018E19D8U
#define DFLT_VAL_NX5_xmac_rx_crc_polynomial_l  0x00000000U

#define MSK_NX5_xmac_rx_crc_polynomial_l_RX_POL_L      0x0000ffffU
#define SRT_NX5_xmac_rx_crc_polynomial_l_RX_POL_L      0
#define DFLT_VAL_NX5_xmac_rx_crc_polynomial_l_RX_POL_L 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc_polynomial_l_RX_POL_L  = 16, /* [15:0] */
	BFW_NX5_xmac_rx_crc_polynomial_l_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_CRC_POLYNOMIAL_L_BIT_Ttag {
	unsigned int RX_POL_L  : BFW_NX5_xmac_rx_crc_polynomial_l_RX_POL_L;  /* lower bits of RX-CRC Polynomial */
	unsigned int reserved1 : BFW_NX5_xmac_rx_crc_polynomial_l_reserved1; /* reserved                        */
} NX5_XMAC_RX_CRC_POLYNOMIAL_L_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_XMAC_RX_CRC_POLYNOMIAL_L_BIT_T bf;
} NX5_XMAC_RX_CRC_POLYNOMIAL_L_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc_polynomial_h */
/* => xMAC RX CRC Polynomial lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc_polynomial_h   0x000009DCU
#define Adr_NX5_xmac0_xmac_rx_crc_polynomial_h 0x018E09DCU
#define Adr_NX5_xmac1_xmac_rx_crc_polynomial_h 0x018E19DCU
#define DFLT_VAL_NX5_xmac_rx_crc_polynomial_h  0x00000000U

#define MSK_NX5_xmac_rx_crc_polynomial_h_RX_POL_H      0x0000ffffU
#define SRT_NX5_xmac_rx_crc_polynomial_h_RX_POL_H      0
#define DFLT_VAL_NX5_xmac_rx_crc_polynomial_h_RX_POL_H 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc_polynomial_h_RX_POL_H  = 16, /* [15:0] */
	BFW_NX5_xmac_rx_crc_polynomial_h_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_CRC_POLYNOMIAL_H_BIT_Ttag {
	unsigned int RX_POL_H  : BFW_NX5_xmac_rx_crc_polynomial_h_RX_POL_H;  /* upper bits of RX-CRC Polynomial */
	unsigned int reserved1 : BFW_NX5_xmac_rx_crc_polynomial_h_reserved1; /* reserved                        */
} NX5_XMAC_RX_CRC_POLYNOMIAL_H_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_XMAC_RX_CRC_POLYNOMIAL_H_BIT_T bf;
} NX5_XMAC_RX_CRC_POLYNOMIAL_H_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc_l */
/* => xMAC RX CRC lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc_l   0x000009E0U
#define Adr_NX5_xmac0_xmac_rx_crc_l 0x018E09E0U
#define Adr_NX5_xmac1_xmac_rx_crc_l 0x018E19E0U
#define DFLT_VAL_NX5_xmac_rx_crc_l  0x00000000U

#define MSK_NX5_xmac_rx_crc_l_RX_CRC_L      0x0000ffffU
#define SRT_NX5_xmac_rx_crc_l_RX_CRC_L      0
#define DFLT_VAL_NX5_xmac_rx_crc_l_RX_CRC_L 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc_l_RX_CRC_L  = 16, /* [15:0] */
	BFW_NX5_xmac_rx_crc_l_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_CRC_L_BIT_Ttag {
	unsigned int RX_CRC_L  : BFW_NX5_xmac_rx_crc_l_RX_CRC_L;  /* lower bits of RX-CRC */
	unsigned int reserved1 : BFW_NX5_xmac_rx_crc_l_reserved1; /* reserved             */
} NX5_XMAC_RX_CRC_L_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_RX_CRC_L_BIT_T bf;
} NX5_XMAC_RX_CRC_L_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc_h */
/* => xMAC RX CRC upper part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc_h   0x000009E4U
#define Adr_NX5_xmac0_xmac_rx_crc_h 0x018E09E4U
#define Adr_NX5_xmac1_xmac_rx_crc_h 0x018E19E4U
#define DFLT_VAL_NX5_xmac_rx_crc_h  0x00000000U

#define MSK_NX5_xmac_rx_crc_h_RX_CRC_H      0x0000ffffU
#define SRT_NX5_xmac_rx_crc_h_RX_CRC_H      0
#define DFLT_VAL_NX5_xmac_rx_crc_h_RX_CRC_H 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc_h_RX_CRC_H  = 16, /* [15:0] */
	BFW_NX5_xmac_rx_crc_h_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RX_CRC_H_BIT_Ttag {
	unsigned int RX_CRC_H  : BFW_NX5_xmac_rx_crc_h_RX_CRC_H;  /* upper bits of RX-CRC */
	unsigned int reserved1 : BFW_NX5_xmac_rx_crc_h_reserved1; /* reserved             */
} NX5_XMAC_RX_CRC_H_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_RX_CRC_H_BIT_T bf;
} NX5_XMAC_RX_CRC_H_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rx_crc_cfg */
/* => xMAC RX CRC Config Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rx_crc_cfg   0x000009E8U
#define Adr_NX5_xmac0_xmac_rx_crc_cfg 0x018E09E8U
#define Adr_NX5_xmac1_xmac_rx_crc_cfg 0x018E19E8U
#define DFLT_VAL_NX5_xmac_rx_crc_cfg  0x00000000U

#define MSK_NX5_xmac_rx_crc_cfg_shift_right      0x00000001U
#define SRT_NX5_xmac_rx_crc_cfg_shift_right      0
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_shift_right 0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_zero             0x00000002U
#define SRT_NX5_xmac_rx_crc_cfg_zero             1
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_zero        0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_invert           0x00000004U
#define SRT_NX5_xmac_rx_crc_cfg_invert           2
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_invert      0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_len              0x000000f8U
#define SRT_NX5_xmac_rx_crc_cfg_len              3
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_len         0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_nof_bits         0x00000300U
#define SRT_NX5_xmac_rx_crc_cfg_nof_bits         8
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_nof_bits    0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_direct_div       0x00000400U
#define SRT_NX5_xmac_rx_crc_cfg_direct_div       10
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_direct_div  0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_endian           0x00000800U
#define SRT_NX5_xmac_rx_crc_cfg_endian           11
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_endian      0x00000000U
#define MSK_NX5_xmac_rx_crc_cfg_swap_output      0x00001000U
#define SRT_NX5_xmac_rx_crc_cfg_swap_output      12
#define DFLT_VAL_NX5_xmac_rx_crc_cfg_swap_output 0x00000000U

enum {
	BFW_NX5_xmac_rx_crc_cfg_shift_right = 1,  /* [0] */
	BFW_NX5_xmac_rx_crc_cfg_zero        = 1,  /* [1] */
	BFW_NX5_xmac_rx_crc_cfg_invert      = 1,  /* [2] */
	BFW_NX5_xmac_rx_crc_cfg_len         = 5,  /* [7:3] */
	BFW_NX5_xmac_rx_crc_cfg_nof_bits    = 2,  /* [9:8] */
	BFW_NX5_xmac_rx_crc_cfg_direct_div  = 1,  /* [10] */
	BFW_NX5_xmac_rx_crc_cfg_endian      = 1,  /* [11] */
	BFW_NX5_xmac_rx_crc_cfg_swap_output = 1,  /* [12] */
	BFW_NX5_xmac_rx_crc_cfg_reserved1   = 19  /* [31:13] */
};

typedef struct NX5_XMAC_RX_CRC_CFG_BIT_Ttag {
	unsigned int shift_right : BFW_NX5_xmac_rx_crc_cfg_shift_right; /* Shift RX CRC from left to right                                        */
	                                                                /* (usually used with crc_swap_output but inverted in case of crc_endian) */
	unsigned int zero        : BFW_NX5_xmac_rx_crc_cfg_zero;        /* Set input of RX CRC to zero (before invert)                            */
	unsigned int invert      : BFW_NX5_xmac_rx_crc_cfg_invert;      /* Invert input of RX CRC                                                 */
	unsigned int len         : BFW_NX5_xmac_rx_crc_cfg_len;         /* Length of RX_CRC minus 1 (0-31)                                        */
	unsigned int nof_bits    : BFW_NX5_xmac_rx_crc_cfg_nof_bits;    /* 1(0),2(1),4(2),8(3) Bits from rx register to be executed in parallel   */
	unsigned int direct_div  : BFW_NX5_xmac_rx_crc_cfg_direct_div;  /* calculate direct polynomial division without n zeros after frame       */
	unsigned int endian      : BFW_NX5_xmac_rx_crc_cfg_endian;      /* Swap incoming bits in case of nof_bits = 2,4,8                         */
	unsigned int swap_output : BFW_NX5_xmac_rx_crc_cfg_swap_output; /* Swap output of crc at PU access                                        */
	unsigned int reserved1   : BFW_NX5_xmac_rx_crc_cfg_reserved1;   /* reserved                                                               */
} NX5_XMAC_RX_CRC_CFG_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_RX_CRC_CFG_BIT_T bf;
} NX5_XMAC_RX_CRC_CFG_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc_polynomial_l */
/* => xMAC TX CRC Polynomial lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc_polynomial_l   0x000009ECU
#define Adr_NX5_xmac0_xmac_tx_crc_polynomial_l 0x018E09ECU
#define Adr_NX5_xmac1_xmac_tx_crc_polynomial_l 0x018E19ECU
#define DFLT_VAL_NX5_xmac_tx_crc_polynomial_l  0x00000000U

#define MSK_NX5_xmac_tx_crc_polynomial_l_TX_POL_L      0x0000ffffU
#define SRT_NX5_xmac_tx_crc_polynomial_l_TX_POL_L      0
#define DFLT_VAL_NX5_xmac_tx_crc_polynomial_l_TX_POL_L 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc_polynomial_l_TX_POL_L  = 16, /* [15:0] */
	BFW_NX5_xmac_tx_crc_polynomial_l_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_CRC_POLYNOMIAL_L_BIT_Ttag {
	unsigned int TX_POL_L  : BFW_NX5_xmac_tx_crc_polynomial_l_TX_POL_L;  /* lower bits of TX-CRC Polynomial */
	unsigned int reserved1 : BFW_NX5_xmac_tx_crc_polynomial_l_reserved1; /* reserved                        */
} NX5_XMAC_TX_CRC_POLYNOMIAL_L_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_XMAC_TX_CRC_POLYNOMIAL_L_BIT_T bf;
} NX5_XMAC_TX_CRC_POLYNOMIAL_L_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc_polynomial_h */
/* => xMAC TX CRC Polynomial lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc_polynomial_h   0x000009F0U
#define Adr_NX5_xmac0_xmac_tx_crc_polynomial_h 0x018E09F0U
#define Adr_NX5_xmac1_xmac_tx_crc_polynomial_h 0x018E19F0U
#define DFLT_VAL_NX5_xmac_tx_crc_polynomial_h  0x00000000U

#define MSK_NX5_xmac_tx_crc_polynomial_h_TX_POL_H      0x0000ffffU
#define SRT_NX5_xmac_tx_crc_polynomial_h_TX_POL_H      0
#define DFLT_VAL_NX5_xmac_tx_crc_polynomial_h_TX_POL_H 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc_polynomial_h_TX_POL_H  = 16, /* [15:0] */
	BFW_NX5_xmac_tx_crc_polynomial_h_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_CRC_POLYNOMIAL_H_BIT_Ttag {
	unsigned int TX_POL_H  : BFW_NX5_xmac_tx_crc_polynomial_h_TX_POL_H;  /* upper bits of TX-CRC Polynomial */
	unsigned int reserved1 : BFW_NX5_xmac_tx_crc_polynomial_h_reserved1; /* reserved                        */
} NX5_XMAC_TX_CRC_POLYNOMIAL_H_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_XMAC_TX_CRC_POLYNOMIAL_H_BIT_T bf;
} NX5_XMAC_TX_CRC_POLYNOMIAL_H_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc_l */
/* => xMAC TX CRC lower part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc_l   0x000009F4U
#define Adr_NX5_xmac0_xmac_tx_crc_l 0x018E09F4U
#define Adr_NX5_xmac1_xmac_tx_crc_l 0x018E19F4U
#define DFLT_VAL_NX5_xmac_tx_crc_l  0x00000000U

#define MSK_NX5_xmac_tx_crc_l_TX_CRC_L      0x0000ffffU
#define SRT_NX5_xmac_tx_crc_l_TX_CRC_L      0
#define DFLT_VAL_NX5_xmac_tx_crc_l_TX_CRC_L 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc_l_TX_CRC_L  = 16, /* [15:0] */
	BFW_NX5_xmac_tx_crc_l_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_CRC_L_BIT_Ttag {
	unsigned int TX_CRC_L  : BFW_NX5_xmac_tx_crc_l_TX_CRC_L;  /* lower bits of TX-CRC */
	unsigned int reserved1 : BFW_NX5_xmac_tx_crc_l_reserved1; /* reserved             */
} NX5_XMAC_TX_CRC_L_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_TX_CRC_L_BIT_T bf;
} NX5_XMAC_TX_CRC_L_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc_h */
/* => xMAC TX CRC upper part */
/*    This register has a write pipeline delay of 1 clock cycle */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc_h   0x000009F8U
#define Adr_NX5_xmac0_xmac_tx_crc_h 0x018E09F8U
#define Adr_NX5_xmac1_xmac_tx_crc_h 0x018E19F8U
#define DFLT_VAL_NX5_xmac_tx_crc_h  0x00000000U

#define MSK_NX5_xmac_tx_crc_h_TX_CRC_H      0x0000ffffU
#define SRT_NX5_xmac_tx_crc_h_TX_CRC_H      0
#define DFLT_VAL_NX5_xmac_tx_crc_h_TX_CRC_H 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc_h_TX_CRC_H  = 16, /* [15:0] */
	BFW_NX5_xmac_tx_crc_h_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TX_CRC_H_BIT_Ttag {
	unsigned int TX_CRC_H  : BFW_NX5_xmac_tx_crc_h_TX_CRC_H;  /* upper bits of TX-CRC */
	unsigned int reserved1 : BFW_NX5_xmac_tx_crc_h_reserved1; /* reserved             */
} NX5_XMAC_TX_CRC_H_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XMAC_TX_CRC_H_BIT_T bf;
} NX5_XMAC_TX_CRC_H_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tx_crc_cfg */
/* => xMAC TX CRC Config Register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tx_crc_cfg   0x000009FCU
#define Adr_NX5_xmac0_xmac_tx_crc_cfg 0x018E09FCU
#define Adr_NX5_xmac1_xmac_tx_crc_cfg 0x018E19FCU
#define DFLT_VAL_NX5_xmac_tx_crc_cfg  0x00000000U

#define MSK_NX5_xmac_tx_crc_cfg_shift_right      0x00000001U
#define SRT_NX5_xmac_tx_crc_cfg_shift_right      0
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_shift_right 0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_zero             0x00000002U
#define SRT_NX5_xmac_tx_crc_cfg_zero             1
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_zero        0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_invert           0x00000004U
#define SRT_NX5_xmac_tx_crc_cfg_invert           2
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_invert      0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_len              0x000000f8U
#define SRT_NX5_xmac_tx_crc_cfg_len              3
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_len         0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_nof_bits         0x00000300U
#define SRT_NX5_xmac_tx_crc_cfg_nof_bits         8
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_nof_bits    0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_direct_div       0x00000400U
#define SRT_NX5_xmac_tx_crc_cfg_direct_div       10
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_direct_div  0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_endian           0x00000800U
#define SRT_NX5_xmac_tx_crc_cfg_endian           11
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_endian      0x00000000U
#define MSK_NX5_xmac_tx_crc_cfg_swap_output      0x00001000U
#define SRT_NX5_xmac_tx_crc_cfg_swap_output      12
#define DFLT_VAL_NX5_xmac_tx_crc_cfg_swap_output 0x00000000U

enum {
	BFW_NX5_xmac_tx_crc_cfg_shift_right = 1,  /* [0] */
	BFW_NX5_xmac_tx_crc_cfg_zero        = 1,  /* [1] */
	BFW_NX5_xmac_tx_crc_cfg_invert      = 1,  /* [2] */
	BFW_NX5_xmac_tx_crc_cfg_len         = 5,  /* [7:3] */
	BFW_NX5_xmac_tx_crc_cfg_nof_bits    = 2,  /* [9:8] */
	BFW_NX5_xmac_tx_crc_cfg_direct_div  = 1,  /* [10] */
	BFW_NX5_xmac_tx_crc_cfg_endian      = 1,  /* [11] */
	BFW_NX5_xmac_tx_crc_cfg_swap_output = 1,  /* [12] */
	BFW_NX5_xmac_tx_crc_cfg_reserved1   = 19  /* [31:13] */
};

typedef struct NX5_XMAC_TX_CRC_CFG_BIT_Ttag {
	unsigned int shift_right : BFW_NX5_xmac_tx_crc_cfg_shift_right; /* Shift TX CRC from left to right                                        */
	                                                                /* (usually used with crc_swap_output but inverted in case of crc_endian) */
	unsigned int zero        : BFW_NX5_xmac_tx_crc_cfg_zero;        /* Set input of TX CRC to zero (before invert)                            */
	unsigned int invert      : BFW_NX5_xmac_tx_crc_cfg_invert;      /* Invert input of TX CRC                                                 */
	unsigned int len         : BFW_NX5_xmac_tx_crc_cfg_len;         /* Length of TX_CRC minus 1 (0-31)                                        */
	unsigned int nof_bits    : BFW_NX5_xmac_tx_crc_cfg_nof_bits;    /* 1(0),2(1),4(2),8(3) Bits from tx_register to be executed in parallel   */
	unsigned int direct_div  : BFW_NX5_xmac_tx_crc_cfg_direct_div;  /* calculate direct polynomial division without n zeros after frame       */
	unsigned int endian      : BFW_NX5_xmac_tx_crc_cfg_endian;      /* Swap incoming bits in case of nof_bits = 2,4,8                         */
	unsigned int swap_output : BFW_NX5_xmac_tx_crc_cfg_swap_output; /* Swap output of crc at PU access                                        */
	unsigned int reserved1   : BFW_NX5_xmac_tx_crc_cfg_reserved1;   /* reserved                                                               */
} NX5_XMAC_TX_CRC_CFG_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XMAC_TX_CRC_CFG_BIT_T bf;
} NX5_XMAC_TX_CRC_CFG_T;

/* --------------------------------------------------------------------- */
/* Register xmac_rpu_hold_pc */
/* => xMAC RPU hold_pc register: */
/*    rpu_hold_pc and tpu_hold_pc are the only registers accessible by ARM-CPU, */
/*    while RPU or TPU are running (hold=0). */
/*    To access other registers of xMAC, first hold RPU and TPU. */
/*    This register is not visible for xMAC RPU and TPU. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_rpu_hold_pc   0x00000A00U
#define Adr_NX5_xmac0_xmac_rpu_hold_pc 0x018E0A00U
#define Adr_NX5_xmac1_xmac_rpu_hold_pc 0x018E1A00U
#define DFLT_VAL_NX5_xmac_rpu_hold_pc  0x00008000U

#define MSK_NX5_xmac_rpu_hold_pc_rpu_pc        0x0000007fU
#define SRT_NX5_xmac_rpu_hold_pc_rpu_pc        0
#define DFLT_VAL_NX5_xmac_rpu_hold_pc_rpu_pc   0x00000000U
#define MSK_NX5_xmac_rpu_hold_pc_rpu_hold      0x00008000U
#define SRT_NX5_xmac_rpu_hold_pc_rpu_hold      15
#define DFLT_VAL_NX5_xmac_rpu_hold_pc_rpu_hold 0x00008000U

enum {
	BFW_NX5_xmac_rpu_hold_pc_rpu_pc    = 7,  /* [6:0] */
	BFW_NX5_xmac_rpu_hold_pc_reserved1 = 8,  /* [14:7] */
	BFW_NX5_xmac_rpu_hold_pc_rpu_hold  = 1,  /* [15] */
	BFW_NX5_xmac_rpu_hold_pc_reserved2 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_RPU_HOLD_PC_BIT_Ttag {
	unsigned int rpu_pc    : BFW_NX5_xmac_rpu_hold_pc_rpu_pc;    /* Program counter (read only, write can happen via adr_xmac_rpu_pc) */
	unsigned int reserved1 : BFW_NX5_xmac_rpu_hold_pc_reserved1; /* reserved                                                          */
	unsigned int rpu_hold  : BFW_NX5_xmac_rpu_hold_pc_rpu_hold;  /* to hold RPU                                                       */
	unsigned int reserved2 : BFW_NX5_xmac_rpu_hold_pc_reserved2; /* reserved                                                          */
} NX5_XMAC_RPU_HOLD_PC_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_RPU_HOLD_PC_BIT_T bf;
} NX5_XMAC_RPU_HOLD_PC_T;

/* --------------------------------------------------------------------- */
/* Register xmac_tpu_hold_pc */
/* => xMAC TPU hold_pc register: */
/*    rpu_hold_pc and tpu_hold_pc are the only registers accessible by ARM-CPU, */
/*    while RPU or TPU are running (hold=0). */
/*    To access other registers of xMAC, first hold RPU and TPU. */
/*    This register is not visible for xMAC RPU and TPU. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xmac_tpu_hold_pc   0x00000A04U
#define Adr_NX5_xmac0_xmac_tpu_hold_pc 0x018E0A04U
#define Adr_NX5_xmac1_xmac_tpu_hold_pc 0x018E1A04U
#define DFLT_VAL_NX5_xmac_tpu_hold_pc  0x00008000U

#define MSK_NX5_xmac_tpu_hold_pc_tpu_pc        0x0000007fU
#define SRT_NX5_xmac_tpu_hold_pc_tpu_pc        0
#define DFLT_VAL_NX5_xmac_tpu_hold_pc_tpu_pc   0x00000000U
#define MSK_NX5_xmac_tpu_hold_pc_tpu_hold      0x00008000U
#define SRT_NX5_xmac_tpu_hold_pc_tpu_hold      15
#define DFLT_VAL_NX5_xmac_tpu_hold_pc_tpu_hold 0x00008000U

enum {
	BFW_NX5_xmac_tpu_hold_pc_tpu_pc    = 7,  /* [6:0] */
	BFW_NX5_xmac_tpu_hold_pc_reserved1 = 8,  /* [14:7] */
	BFW_NX5_xmac_tpu_hold_pc_tpu_hold  = 1,  /* [15] */
	BFW_NX5_xmac_tpu_hold_pc_reserved2 = 16  /* [31:16] */
};

typedef struct NX5_XMAC_TPU_HOLD_PC_BIT_Ttag {
	unsigned int tpu_pc    : BFW_NX5_xmac_tpu_hold_pc_tpu_pc;    /* Program counter (read only, write can happen via adr_xmac_tpu_pc) */
	unsigned int reserved1 : BFW_NX5_xmac_tpu_hold_pc_reserved1; /* reserved                                                          */
	unsigned int tpu_hold  : BFW_NX5_xmac_tpu_hold_pc_tpu_hold;  /* to hold TPU                                                       */
	unsigned int reserved2 : BFW_NX5_xmac_tpu_hold_pc_reserved2; /* reserved                                                          */
} NX5_XMAC_TPU_HOLD_PC_BIT_T;

typedef union {
	unsigned int               val;
	NX5_XMAC_TPU_HOLD_PC_BIT_T bf;
} NX5_XMAC_TPU_HOLD_PC_T;


/* ===================================================================== */

/* Area of pointer_fifo */

/* ===================================================================== */

#define Addr_NX5_pointer_fifo  0x018E4000U
#define NX5_NETX_PTR_FIFO_AREA 0x018E4000U

/* --------------------------------------------------------------------- */
/* Register pfifo_base */
/* => Pointer FIFO table: */
/*    Each of the following 32 addresses accesses a FIFO. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_base          0x00000000U
#define Adr_NX5_pointer_fifo_pfifo_base 0x018E4000U
#define Adr_NX5_pfifo_base              0x018E4000U
#define DFLT_VAL_NX5_pfifo_base         0x00000000U

#define MSK_NX5_pfifo_base_fifo_data      0xffffffffU
#define SRT_NX5_pfifo_base_fifo_data      0
#define DFLT_VAL_NX5_pfifo_base_fifo_data 0x00000000U

enum {
	BFW_NX5_pfifo_base_fifo_data = 32  /* [31:0] */
};

typedef struct NX5_PFIFO_BASE_BIT_Ttag {
	unsigned int fifo_data : BFW_NX5_pfifo_base_fifo_data; /* In/output data to/from FIFO:     */
	                                                       /* write access: write data to FIFO */
} NX5_PFIFO_BASE_BIT_T;

typedef union {
	unsigned int         val;
	NX5_PFIFO_BASE_BIT_T bf;
} NX5_PFIFO_BASE_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_border_base */
/* => Pointer FIFO Upper Borders table: */
/*    The sizes of all FIFOs are programmable. The total size of all FIFOs must not exceed 1024 dwords. \ */
/*    Each of the following 32 addresses accesses the upper border of the appropriate FIFO in a 1024x32 bit RAM. \ */
/*    All upper borders should be rising with number of FIFO. \ */
/*    Each FIFO starts at the upper border + 1 of the preceding FIFO and ends at its upper border. */
/*    If a border between two FIFOs is moved, the adjacent FIFOs should be reset first. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_border_base          0x00000080U
#define Adr_NX5_pointer_fifo_pfifo_border_base 0x018E4080U
#define Adr_NX5_pfifo_border_base              0x018E4080U
#define DFLT_VAL_NX5_pfifo_border_base         0x00000000U

#define MSK_NX5_pfifo_border_base_border      0x000003ffU
#define SRT_NX5_pfifo_border_base_border      0
#define DFLT_VAL_NX5_pfifo_border_base_border 0x00000000U

enum {
	BFW_NX5_pfifo_border_base_border    = 10, /* [9:0] */
	BFW_NX5_pfifo_border_base_reserved1 = 22  /* [31:10] */
};

typedef struct NX5_PFIFO_BORDER_BASE_BIT_Ttag {
	unsigned int border    : BFW_NX5_pfifo_border_base_border;    /* last address of RAM used by appropriate FIFO, = (first address-1) of next FIFO. */
	                                                              /* FIFO 0 default depth:     512                                                   */
	unsigned int reserved1 : BFW_NX5_pfifo_border_base_reserved1; /* reserved                                                                        */
} NX5_PFIFO_BORDER_BASE_BIT_T;

typedef union {
	unsigned int                val;
	NX5_PFIFO_BORDER_BASE_BIT_T bf;
} NX5_PFIFO_BORDER_BASE_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_reset */
/* => Pointer FIFO Reset Vector: */
/*    This register allows to reset each of 32 FIFOs, \ */
/*    i.e. set read and write pointer to lower border of FIFO, reset full, overflow, underrun flag and set empty flag. */
/*    The reset flag of adjacent FIFOs should be set before resizing the FIFO. */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_reset          0x00000100U
#define Adr_NX5_pointer_fifo_pfifo_reset 0x018E4100U
#define Adr_NX5_pfifo_reset              0x018E4100U
#define DFLT_VAL_NX5_pfifo_reset         0x00000000U

#define MSK_NX5_pfifo_reset_reset_fifo      0xffffffffU
#define SRT_NX5_pfifo_reset_reset_fifo      0
#define DFLT_VAL_NX5_pfifo_reset_reset_fifo 0x00000000U

enum {
	BFW_NX5_pfifo_reset_reset_fifo = 32  /* [31:0] */
};

typedef struct NX5_PFIFO_RESET_BIT_Ttag {
	unsigned int reset_fifo : BFW_NX5_pfifo_reset_reset_fifo; /* Reset Vector, 1 bit per FIFO: */
	                                                          /* 1: reset FIFO                 */
} NX5_PFIFO_RESET_BIT_T;

typedef union {
	unsigned int          val;
	NX5_PFIFO_RESET_BIT_T bf;
} NX5_PFIFO_RESET_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_full */
/* => Pointer FIFO Full Vector: */
/*    This read only address shows the fifo_full flag of each FIFO. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_full          0x00000104U
#define Adr_NX5_pointer_fifo_pfifo_full 0x018E4104U
#define Adr_NX5_pfifo_full              0x018E4104U

#define MSK_NX5_pfifo_full_fifo_full 0xffffffffU
#define SRT_NX5_pfifo_full_fifo_full 0

enum {
	BFW_NX5_pfifo_full_fifo_full = 32  /* [31:0] */
};

typedef struct NX5_PFIFO_FULL_BIT_Ttag {
	unsigned int fifo_full : BFW_NX5_pfifo_full_fifo_full; /* FIFO full vector, 1 bit per FIFO */
} NX5_PFIFO_FULL_BIT_T;

typedef union {
	unsigned int         val;
	NX5_PFIFO_FULL_BIT_T bf;
} NX5_PFIFO_FULL_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_empty */
/* => Pointer FIFO Empty Vector: */
/*    This read only address shows the fifo_empty flag of each FIFO. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_empty          0x00000108U
#define Adr_NX5_pointer_fifo_pfifo_empty 0x018E4108U
#define Adr_NX5_pfifo_empty              0x018E4108U

#define MSK_NX5_pfifo_empty_fifo_empty 0xffffffffU
#define SRT_NX5_pfifo_empty_fifo_empty 0

enum {
	BFW_NX5_pfifo_empty_fifo_empty = 32  /* [31:0] */
};

typedef struct NX5_PFIFO_EMPTY_BIT_Ttag {
	unsigned int fifo_empty : BFW_NX5_pfifo_empty_fifo_empty; /* FIFO empty vector, 1 bit per FIFO */
} NX5_PFIFO_EMPTY_BIT_T;

typedef union {
	unsigned int          val;
	NX5_PFIFO_EMPTY_BIT_T bf;
} NX5_PFIFO_EMPTY_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_overflow */
/* => Pointer FIFO Overflow Vector: */
/*    This read only address shows the fifo_overflow flag of each FIFO. */
/*    If the FIFO had an overflow, it should be reset. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_overflow          0x0000010CU
#define Adr_NX5_pointer_fifo_pfifo_overflow 0x018E410CU
#define Adr_NX5_pfifo_overflow              0x018E410CU

#define MSK_NX5_pfifo_overflow_fifo_overflow 0xffffffffU
#define SRT_NX5_pfifo_overflow_fifo_overflow 0

enum {
	BFW_NX5_pfifo_overflow_fifo_overflow = 32  /* [31:0] */
};

typedef struct NX5_PFIFO_OVERFLOW_BIT_Ttag {
	unsigned int fifo_overflow : BFW_NX5_pfifo_overflow_fifo_overflow; /* FIFO overflow vector, 1 bit per FIFO */
} NX5_PFIFO_OVERFLOW_BIT_T;

typedef union {
	unsigned int             val;
	NX5_PFIFO_OVERFLOW_BIT_T bf;
} NX5_PFIFO_OVERFLOW_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_underrun */
/* => Pointer FIFO Underrun Vector: */
/*    This read only address shows the fifo_underrun flag of each FIFO. */
/*    If the FIFO had an underrun, it should be reset. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_underrun          0x00000110U
#define Adr_NX5_pointer_fifo_pfifo_underrun 0x018E4110U
#define Adr_NX5_pfifo_underrun              0x018E4110U

#define MSK_NX5_pfifo_underrun_fifo_underrun 0xffffffffU
#define SRT_NX5_pfifo_underrun_fifo_underrun 0

enum {
	BFW_NX5_pfifo_underrun_fifo_underrun = 32  /* [31:0] */
};

typedef struct NX5_PFIFO_UNDERRUN_BIT_Ttag {
	unsigned int fifo_underrun : BFW_NX5_pfifo_underrun_fifo_underrun; /* FIFO underrun vector, 1 bit per FIFO */
} NX5_PFIFO_UNDERRUN_BIT_T;

typedef union {
	unsigned int             val;
	NX5_PFIFO_UNDERRUN_BIT_T bf;
} NX5_PFIFO_UNDERRUN_T;

/* --------------------------------------------------------------------- */
/* Register pfifo_fill_level_base */
/* => Pointer FIFO Fill-Level table: */
/*    Each of the following 32 addresses reads the fill-level of the appropriate FIFO. */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_pfifo_fill_level_base          0x00000180U
#define Adr_NX5_pointer_fifo_pfifo_fill_level_base 0x018E4180U
#define Adr_NX5_pfifo_fill_level_base              0x018E4180U

#define MSK_NX5_pfifo_fill_level_base_fill_level 0x000003ffU
#define SRT_NX5_pfifo_fill_level_base_fill_level 0

enum {
	BFW_NX5_pfifo_fill_level_base_fill_level = 10, /* [9:0] */
	BFW_NX5_pfifo_fill_level_base_reserved1  = 22  /* [31:10] */
};

typedef struct NX5_PFIFO_FILL_LEVEL_BASE_BIT_Ttag {
	unsigned int fill_level : BFW_NX5_pfifo_fill_level_base_fill_level; /* actual number of words in appropriate FIFO       */
	                                                                    /* (not valid, if FIFO had an overflow or underrun) */
	unsigned int reserved1  : BFW_NX5_pfifo_fill_level_base_reserved1;  /* reserved                                         */
} NX5_PFIFO_FILL_LEVEL_BASE_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_PFIFO_FILL_LEVEL_BASE_BIT_T bf;
} NX5_PFIFO_FILL_LEVEL_BASE_T;


/* ===================================================================== */

/* Area of xpec_irq_registers */

/* ===================================================================== */

#define Addr_NX5_xpec_irq_registers 0x018E4400U
#define NX5_NETX_XP_IRQ_AREA        0x018E4400U

/* --------------------------------------------------------------------- */
/* Register irq_xpec0 */
/* => IRQ_XPEC 0 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_irq_xpec0                0x00000000U
#define Adr_NX5_xpec_irq_registers_irq_xpec0 0x018E4400U
#define Adr_NX5_irq_xpec0                    0x018E4400U
#define DFLT_VAL_NX5_irq_xpec0               0x00000000U

#define MSK_NX5_irq_xpec0_xpec_irq      0x0000ffffU
#define SRT_NX5_irq_xpec0_xpec_irq      0
#define DFLT_VAL_NX5_irq_xpec0_xpec_irq 0x00000000U
#define MSK_NX5_irq_xpec0_arm_irq       0xffff0000U
#define SRT_NX5_irq_xpec0_arm_irq       16
#define DFLT_VAL_NX5_irq_xpec0_arm_irq  0x00000000U

enum {
	BFW_NX5_irq_xpec0_xpec_irq = 16, /* [15:0] */
	BFW_NX5_irq_xpec0_arm_irq  = 16  /* [31:16] */
};

typedef struct NX5_IRQ_XPEC0_BIT_Ttag {
	unsigned int xpec_irq : BFW_NX5_irq_xpec0_xpec_irq; /* set by xpec ; reset by arm  */
	unsigned int arm_irq  : BFW_NX5_irq_xpec0_arm_irq;  /* set by arm  ; reset by xpec */
} NX5_IRQ_XPEC0_BIT_T;

typedef union {
	unsigned int        val;
	NX5_IRQ_XPEC0_BIT_T bf;
} NX5_IRQ_XPEC0_T;

/* --------------------------------------------------------------------- */
/* Register irq_xpec1 */
/* => IRQ_XPEC 1 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_irq_xpec1                0x00000004U
#define Adr_NX5_xpec_irq_registers_irq_xpec1 0x018E4404U
#define Adr_NX5_irq_xpec1                    0x018E4404U
#define DFLT_VAL_NX5_irq_xpec1               0x00000000U

#define MSK_NX5_irq_xpec1_xpec_irq      0x0000ffffU
#define SRT_NX5_irq_xpec1_xpec_irq      0
#define DFLT_VAL_NX5_irq_xpec1_xpec_irq 0x00000000U
#define MSK_NX5_irq_xpec1_arm_irq       0xffff0000U
#define SRT_NX5_irq_xpec1_arm_irq       16
#define DFLT_VAL_NX5_irq_xpec1_arm_irq  0x00000000U

enum {
	BFW_NX5_irq_xpec1_xpec_irq = 16, /* [15:0] */
	BFW_NX5_irq_xpec1_arm_irq  = 16  /* [31:16] */
};

typedef struct NX5_IRQ_XPEC1_BIT_Ttag {
	unsigned int xpec_irq : BFW_NX5_irq_xpec1_xpec_irq; /* set by xpec ; reset by arm  */
	unsigned int arm_irq  : BFW_NX5_irq_xpec1_arm_irq;  /* set by arm  ; reset by xpec */
} NX5_IRQ_XPEC1_BIT_T;

typedef union {
	unsigned int        val;
	NX5_IRQ_XPEC1_BIT_T bf;
} NX5_IRQ_XPEC1_T;


/* ===================================================================== */

/* Area of xc_mem_prot */

/* ===================================================================== */

#define Addr_NX5_xc_mem_prot 0x018E4800U
#define NX5_NETX_XC_MEM_PROT 0x018E4800U

/* --------------------------------------------------------------------- */
/* Register xpec0_ram_low */
/* => not protected memory area (lower border) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec0_ram_low         0x00000000U
#define Adr_NX5_xc_mem_prot_xpec0_ram_low 0x018E4800U
#define Adr_NX5_xpec0_ram_low             0x018E4800U
#define DFLT_VAL_NX5_xpec0_ram_low        0x00000000U

#define MSK_NX5_xpec0_ram_low_xpec0_ram_low      0x00001fffU
#define SRT_NX5_xpec0_ram_low_xpec0_ram_low      0
#define DFLT_VAL_NX5_xpec0_ram_low_xpec0_ram_low 0x00000000U

enum {
	BFW_NX5_xpec0_ram_low_xpec0_ram_low = 13, /* [12:0] */
	BFW_NX5_xpec0_ram_low_reserved1     = 19  /* [31:13] */
};

typedef struct NX5_XPEC0_RAM_LOW_BIT_Ttag {
	unsigned int xpec0_ram_low : BFW_NX5_xpec0_ram_low_xpec0_ram_low; /* lower border (include) of not protected memory area */
	unsigned int reserved1     : BFW_NX5_xpec0_ram_low_reserved1;     /* reserved                                            */
} NX5_XPEC0_RAM_LOW_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XPEC0_RAM_LOW_BIT_T bf;
} NX5_XPEC0_RAM_LOW_T;

/* --------------------------------------------------------------------- */
/* Register xpec1_ram_low */
/* => not protected memory area (lower border) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec1_ram_low         0x00000004U
#define Adr_NX5_xc_mem_prot_xpec1_ram_low 0x018E4804U
#define Adr_NX5_xpec1_ram_low             0x018E4804U
#define DFLT_VAL_NX5_xpec1_ram_low        0x00000000U

#define MSK_NX5_xpec1_ram_low_xpec1_ram_low      0x00001fffU
#define SRT_NX5_xpec1_ram_low_xpec1_ram_low      0
#define DFLT_VAL_NX5_xpec1_ram_low_xpec1_ram_low 0x00000000U

enum {
	BFW_NX5_xpec1_ram_low_xpec1_ram_low = 13, /* [12:0] */
	BFW_NX5_xpec1_ram_low_reserved1     = 19  /* [31:13] */
};

typedef struct NX5_XPEC1_RAM_LOW_BIT_Ttag {
	unsigned int xpec1_ram_low : BFW_NX5_xpec1_ram_low_xpec1_ram_low; /* lower border (include) of not protected memory area */
	unsigned int reserved1     : BFW_NX5_xpec1_ram_low_reserved1;     /* reserved                                            */
} NX5_XPEC1_RAM_LOW_BIT_T;

typedef union {
	unsigned int            val;
	NX5_XPEC1_RAM_LOW_BIT_T bf;
} NX5_XPEC1_RAM_LOW_T;

/* --------------------------------------------------------------------- */
/* Register xpec0_ram_high */
/* => not protected memory area (higher border) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec0_ram_high         0x00000010U
#define Adr_NX5_xc_mem_prot_xpec0_ram_high 0x018E4810U
#define Adr_NX5_xpec0_ram_high             0x018E4810U
#define DFLT_VAL_NX5_xpec0_ram_high        0x00000000U

#define MSK_NX5_xpec0_ram_high_xpec0_ram_high      0x00001fffU
#define SRT_NX5_xpec0_ram_high_xpec0_ram_high      0
#define DFLT_VAL_NX5_xpec0_ram_high_xpec0_ram_high 0x00000000U

enum {
	BFW_NX5_xpec0_ram_high_xpec0_ram_high = 13, /* [12:0] */
	BFW_NX5_xpec0_ram_high_reserved1      = 19  /* [31:13] */
};

typedef struct NX5_XPEC0_RAM_HIGH_BIT_Ttag {
	unsigned int xpec0_ram_high : BFW_NX5_xpec0_ram_high_xpec0_ram_high; /* higher border(include) of not protected memory area */
	unsigned int reserved1      : BFW_NX5_xpec0_ram_high_reserved1;      /* reserved                                            */
} NX5_XPEC0_RAM_HIGH_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XPEC0_RAM_HIGH_BIT_T bf;
} NX5_XPEC0_RAM_HIGH_T;

/* --------------------------------------------------------------------- */
/* Register xpec1_ram_high */
/* => not protected memory area (higher border) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xpec1_ram_high         0x00000014U
#define Adr_NX5_xc_mem_prot_xpec1_ram_high 0x018E4814U
#define Adr_NX5_xpec1_ram_high             0x018E4814U
#define DFLT_VAL_NX5_xpec1_ram_high        0x00000000U

#define MSK_NX5_xpec1_ram_high_xpec1_ram_high      0x00001fffU
#define SRT_NX5_xpec1_ram_high_xpec1_ram_high      0
#define DFLT_VAL_NX5_xpec1_ram_high_xpec1_ram_high 0x00000000U

enum {
	BFW_NX5_xpec1_ram_high_xpec1_ram_high = 13, /* [12:0] */
	BFW_NX5_xpec1_ram_high_reserved1      = 19  /* [31:13] */
};

typedef struct NX5_XPEC1_RAM_HIGH_BIT_Ttag {
	unsigned int xpec1_ram_high : BFW_NX5_xpec1_ram_high_xpec1_ram_high; /* higher border(include) of not protected memory area */
	unsigned int reserved1      : BFW_NX5_xpec1_ram_high_reserved1;      /* reserved                                            */
} NX5_XPEC1_RAM_HIGH_BIT_T;

typedef union {
	unsigned int             val;
	NX5_XPEC1_RAM_HIGH_BIT_T bf;
} NX5_XPEC1_RAM_HIGH_T;

/* --------------------------------------------------------------------- */
/* Register prot_key_enable */
/* => protection key enable */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_prot_key_enable         0x00000100U
#define Adr_NX5_xc_mem_prot_prot_key_enable 0x018E4900U
#define Adr_NX5_prot_key_enable             0x018E4900U
#define DFLT_VAL_NX5_prot_key_enable        0x00000000U

#define MSK_NX5_prot_key_enable_prot_key_enable      0xffffffffU
#define SRT_NX5_prot_key_enable_prot_key_enable      0
#define DFLT_VAL_NX5_prot_key_enable_prot_key_enable 0x00000000U

enum {
	BFW_NX5_prot_key_enable_prot_key_enable = 32  /* [31:0] */
};

typedef struct NX5_PROT_KEY_ENABLE_BIT_Ttag {
	unsigned int prot_key_enable : BFW_NX5_prot_key_enable_prot_key_enable; /* 1. Read out the access key from this register. 2. Write back this access key to this register. 3. Memory protection is enable. */
} NX5_PROT_KEY_ENABLE_BIT_T;

typedef union {
	unsigned int              val;
	NX5_PROT_KEY_ENABLE_BIT_T bf;
} NX5_PROT_KEY_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register prot_key_disable */
/* => protection key disable */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_prot_key_disable         0x00000104U
#define Adr_NX5_xc_mem_prot_prot_key_disable 0x018E4904U
#define Adr_NX5_prot_key_disable             0x018E4904U
#define DFLT_VAL_NX5_prot_key_disable        0x00000000U

#define MSK_NX5_prot_key_disable_prot_key_disable      0xffffffffU
#define SRT_NX5_prot_key_disable_prot_key_disable      0
#define DFLT_VAL_NX5_prot_key_disable_prot_key_disable 0x00000000U

enum {
	BFW_NX5_prot_key_disable_prot_key_disable = 32  /* [31:0] */
};

typedef struct NX5_PROT_KEY_DISABLE_BIT_Ttag {
	unsigned int prot_key_disable : BFW_NX5_prot_key_disable_prot_key_disable; /* 1. Read out the access key from this register. 2. Write back this access key to this register. 3. Memory protection is disable. */
} NX5_PROT_KEY_DISABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_PROT_KEY_DISABLE_BIT_T bf;
} NX5_PROT_KEY_DISABLE_T;

/* --------------------------------------------------------------------- */
/* Register prot_status */
/* => protection status */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_prot_status         0x00000108U
#define Adr_NX5_xc_mem_prot_prot_status 0x018E4908U
#define Adr_NX5_prot_status             0x018E4908U

#define MSK_NX5_prot_status_prot_stauts 0x00000001U
#define SRT_NX5_prot_status_prot_stauts 0

enum {
	BFW_NX5_prot_status_prot_stauts = 1,  /* [0] */
	BFW_NX5_prot_status_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_PROT_STATUS_BIT_Ttag {
	unsigned int prot_stauts : BFW_NX5_prot_status_prot_stauts; /* Protection Status (read only) 1: protection mode 0: not protected */
	unsigned int reserved1   : BFW_NX5_prot_status_reserved1;   /* reserved                                                          */
} NX5_PROT_STATUS_BIT_T;

typedef union {
	unsigned int          val;
	NX5_PROT_STATUS_BIT_T bf;
} NX5_PROT_STATUS_T;


/* ===================================================================== */

/* Area of xc_debug */

/* ===================================================================== */

#define Addr_NX5_xc_debug 0x018E4C00U
#define NX5_NETX_XC_DBG   0x018E4C00U

/* --------------------------------------------------------------------- */
/* Register xc_debug_config */
/* => config XC debug module */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xc_debug_config      0x00000000U
#define Adr_NX5_xc_debug_xc_debug_config 0x018E4C00U
#define Adr_NX5_xc_debug_config          0x018E4C00U
#define DFLT_VAL_NX5_xc_debug_config     0x00000000U

#define MSK_NX5_xc_debug_config_select_xpec       0x00000003U
#define SRT_NX5_xc_debug_config_select_xpec       0
#define DFLT_VAL_NX5_xc_debug_config_select_xpec  0x00000000U
#define MSK_NX5_xc_debug_config_debug_enable      0x80000000U
#define SRT_NX5_xc_debug_config_debug_enable      31
#define DFLT_VAL_NX5_xc_debug_config_debug_enable 0x00000000U

enum {
	BFW_NX5_xc_debug_config_select_xpec  = 2,  /* [1:0] */
	BFW_NX5_xc_debug_config_reserved1    = 29, /* [30:2] */
	BFW_NX5_xc_debug_config_debug_enable = 1   /* [31] */
};

typedef struct NX5_XC_DEBUG_CONFIG_BIT_Ttag {
	unsigned int select_xpec  : BFW_NX5_xc_debug_config_select_xpec;  /* (00 = xpec0, 01 = xpec1, 10 = xpec2, 11 = xpec3) default 0x0 */
	unsigned int reserved1    : BFW_NX5_xc_debug_config_reserved1;    /* reserved                                                     */
	unsigned int debug_enable : BFW_NX5_xc_debug_config_debug_enable; /* default 0x0                                                  */
} NX5_XC_DEBUG_CONFIG_BIT_T;

typedef union {
	unsigned int              val;
	NX5_XC_DEBUG_CONFIG_BIT_T bf;
} NX5_XC_DEBUG_CONFIG_T;


/* ===================================================================== */

/* Area of trigger_sample_unit */

/* ===================================================================== */

#define Addr_NX5_trigger_sample_unit 0x018E5000U
#define NX5_NETX_TRIG_SAMP_AREA      0x018E5000U

/* --------------------------------------------------------------------- */
/* Register trigger_sample_config */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_sample_config                 0x00000000U
#define Adr_NX5_trigger_sample_unit_trigger_sample_config 0x018E5000U
#define Adr_NX5_trigger_sample_config                     0x018E5000U
#define DFLT_VAL_NX5_trigger_sample_config                0x00000000U

#define MSK_NX5_trigger_sample_config_sync0_output_driver        0x00000001U
#define SRT_NX5_trigger_sample_config_sync0_output_driver        0
#define DFLT_VAL_NX5_trigger_sample_config_sync0_output_driver   0x00000000U
#define MSK_NX5_trigger_sample_config_sync0_polarity             0x00000002U
#define SRT_NX5_trigger_sample_config_sync0_polarity             1
#define DFLT_VAL_NX5_trigger_sample_config_sync0_polarity        0x00000000U
#define MSK_NX5_trigger_sample_config_sync0_oe                   0x00000004U
#define SRT_NX5_trigger_sample_config_sync0_oe                   2
#define DFLT_VAL_NX5_trigger_sample_config_sync0_oe              0x00000000U
#define MSK_NX5_trigger_sample_config_sync0_irq_en               0x00000008U
#define SRT_NX5_trigger_sample_config_sync0_irq_en               3
#define DFLT_VAL_NX5_trigger_sample_config_sync0_irq_en          0x00000000U
#define MSK_NX5_trigger_sample_config_sync1_output_driver        0x00000010U
#define SRT_NX5_trigger_sample_config_sync1_output_driver        4
#define DFLT_VAL_NX5_trigger_sample_config_sync1_output_driver   0x00000000U
#define MSK_NX5_trigger_sample_config_sync1_polarity             0x00000020U
#define SRT_NX5_trigger_sample_config_sync1_polarity             5
#define DFLT_VAL_NX5_trigger_sample_config_sync1_polarity        0x00000000U
#define MSK_NX5_trigger_sample_config_sync1_oe                   0x00000040U
#define SRT_NX5_trigger_sample_config_sync1_oe                   6
#define DFLT_VAL_NX5_trigger_sample_config_sync1_oe              0x00000000U
#define MSK_NX5_trigger_sample_config_sync1_irq_en               0x00000080U
#define SRT_NX5_trigger_sample_config_sync1_irq_en               7
#define DFLT_VAL_NX5_trigger_sample_config_sync1_irq_en          0x00000000U
#define MSK_NX5_trigger_sample_config_trigger_mode               0x00000300U
#define SRT_NX5_trigger_sample_config_trigger_mode               8
#define DFLT_VAL_NX5_trigger_sample_config_trigger_mode          0x00000000U
#define MSK_NX5_trigger_sample_config_latch_unit_activate        0x00010000U
#define SRT_NX5_trigger_sample_config_latch_unit_activate        16
#define DFLT_VAL_NX5_trigger_sample_config_latch_unit_activate   0x00000000U
#define MSK_NX5_trigger_sample_config_latch0_posedge_irq_en      0x01000000U
#define SRT_NX5_trigger_sample_config_latch0_posedge_irq_en      24
#define DFLT_VAL_NX5_trigger_sample_config_latch0_posedge_irq_en 0x00000000U
#define MSK_NX5_trigger_sample_config_latch0_negedge_irq_en      0x02000000U
#define SRT_NX5_trigger_sample_config_latch0_negedge_irq_en      25
#define DFLT_VAL_NX5_trigger_sample_config_latch0_negedge_irq_en 0x00000000U
#define MSK_NX5_trigger_sample_config_latch1_posedge_irq_en      0x04000000U
#define SRT_NX5_trigger_sample_config_latch1_posedge_irq_en      26
#define DFLT_VAL_NX5_trigger_sample_config_latch1_posedge_irq_en 0x00000000U
#define MSK_NX5_trigger_sample_config_latch1_negedge_irq_en      0x08000000U
#define SRT_NX5_trigger_sample_config_latch1_negedge_irq_en      27
#define DFLT_VAL_NX5_trigger_sample_config_latch1_negedge_irq_en 0x00000000U

enum {
	BFW_NX5_trigger_sample_config_sync0_output_driver   = 1, /* [0] */
	BFW_NX5_trigger_sample_config_sync0_polarity        = 1, /* [1] */
	BFW_NX5_trigger_sample_config_sync0_oe              = 1, /* [2] */
	BFW_NX5_trigger_sample_config_sync0_irq_en          = 1, /* [3] */
	BFW_NX5_trigger_sample_config_sync1_output_driver   = 1, /* [4] */
	BFW_NX5_trigger_sample_config_sync1_polarity        = 1, /* [5] */
	BFW_NX5_trigger_sample_config_sync1_oe              = 1, /* [6] */
	BFW_NX5_trigger_sample_config_sync1_irq_en          = 1, /* [7] */
	BFW_NX5_trigger_sample_config_trigger_mode          = 2, /* [9:8] */
	BFW_NX5_trigger_sample_config_reserved1             = 6, /* [15:10] */
	BFW_NX5_trigger_sample_config_latch_unit_activate   = 1, /* [16] */
	BFW_NX5_trigger_sample_config_reserved2             = 7, /* [23:17] */
	BFW_NX5_trigger_sample_config_latch0_posedge_irq_en = 1, /* [24] */
	BFW_NX5_trigger_sample_config_latch0_negedge_irq_en = 1, /* [25] */
	BFW_NX5_trigger_sample_config_latch1_posedge_irq_en = 1, /* [26] */
	BFW_NX5_trigger_sample_config_latch1_negedge_irq_en = 1, /* [27] */
	BFW_NX5_trigger_sample_config_reserved3             = 4  /* [31:28] */
};

typedef struct NX5_TRIGGER_SAMPLE_CONFIG_BIT_Ttag {
	unsigned int sync0_output_driver   : BFW_NX5_trigger_sample_config_sync0_output_driver;   /* 1/0: sync0 (ethercat) / con clk (sercos3) open-drain                                             */
	unsigned int sync0_polarity        : BFW_NX5_trigger_sample_config_sync0_polarity;        /* 1/0: sync0 (ethercat) / con clk (sercos3) high/low active                                        */
	unsigned int sync0_oe              : BFW_NX5_trigger_sample_config_sync0_oe;              /* 1/0: sync0 (ethercat) / con clk (sercos3) output enabled/disabled                                */
	unsigned int sync0_irq_en          : BFW_NX5_trigger_sample_config_sync0_irq_en;          /* 1/0: sync0 (ethercat) interrupt enabled/disabled / tmst irq enable (sercos 3 mode)               */
	unsigned int sync1_output_driver   : BFW_NX5_trigger_sample_config_sync1_output_driver;   /* 1/0: sync1 (ethercat) / div clk (sercos3) open-drain/ push-pull                                  */
	unsigned int sync1_polarity        : BFW_NX5_trigger_sample_config_sync1_polarity;        /* 1/0: sync1 (ethercat) / div clk (sercos3) high/low active                                        */
	unsigned int sync1_oe              : BFW_NX5_trigger_sample_config_sync1_oe;              /* 1/0: sync1 (ethercat) / div clk (sercos3) output enabled/disabled                                */
	unsigned int sync1_irq_en          : BFW_NX5_trigger_sample_config_sync1_irq_en;          /* 1/0: sync1 (ethercat) interrupt enabled/disabled / div clk irq enable (sercos 3 mode)            */
	unsigned int trigger_mode          : BFW_NX5_trigger_sample_config_trigger_mode;          /* trigger unit mode:                                                                               */
	                                                                                          /* 2'b00: normal (sync0 and sync1 are independent, damit sollte PROFINET spielen)                   */
	unsigned int reserved1             : BFW_NX5_trigger_sample_config_reserved1;             /* reserved                                                                                         */
	unsigned int latch_unit_activate   : BFW_NX5_trigger_sample_config_latch_unit_activate;   /* 0->1 (posedge)/ 1->0 (negedge): latching enabled/disabled (reset internal statemachine ethercat) */
	unsigned int reserved2             : BFW_NX5_trigger_sample_config_reserved2;             /* reserved                                                                                         */
	unsigned int latch0_posedge_irq_en : BFW_NX5_trigger_sample_config_latch0_posedge_irq_en; /* 1/0: latch0 posedge interrupt enabled(ethercat mode) / tint_0 interrupt enabled(sercos 3 mode)   */
	unsigned int latch0_negedge_irq_en : BFW_NX5_trigger_sample_config_latch0_negedge_irq_en; /* 1/0: latch0 negedge interrupt enabled(ethercat mode) / tint_1 interrupt enabled(sercos 3 mode)   */
	unsigned int latch1_posedge_irq_en : BFW_NX5_trigger_sample_config_latch1_posedge_irq_en; /* 1/0: latch1 posedge interrupt enabled(ethercat mode) / tint_2 interrupt enabled(sercos 3 mode)   */
	unsigned int latch1_negedge_irq_en : BFW_NX5_trigger_sample_config_latch1_negedge_irq_en; /* 1/0: latch1 negedge interrupt enabled(ethercat mode) / tint_3 interrupt enabled(sercos 3 mode)   */
	unsigned int reserved3             : BFW_NX5_trigger_sample_config_reserved3;             /* reserved                                                                                         */
} NX5_TRIGGER_SAMPLE_CONFIG_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_TRIGGER_SAMPLE_CONFIG_BIT_T bf;
} NX5_TRIGGER_SAMPLE_CONFIG_T;

/* --------------------------------------------------------------------- */
/* Register trigger_sample_status */
/* => r/w access by xPEC and ARM, set by trigger_sample_unit, write access (1'b1) clears the events, all status signals are connected to the xPEC event controller of each xPEC */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_sample_status                 0x00000004U
#define Adr_NX5_trigger_sample_unit_trigger_sample_status 0x018E5004U
#define Adr_NX5_trigger_sample_status                     0x018E5004U
#define DFLT_VAL_NX5_trigger_sample_status                0x00000000U

#define MSK_NX5_trigger_sample_status_sync0_status                 0x00000001U
#define SRT_NX5_trigger_sample_status_sync0_status                 0
#define DFLT_VAL_NX5_trigger_sample_status_sync0_status            0x00000000U
#define MSK_NX5_trigger_sample_status_sync1_status                 0x00000100U
#define SRT_NX5_trigger_sample_status_sync1_status                 8
#define DFLT_VAL_NX5_trigger_sample_status_sync1_status            0x00000000U
#define MSK_NX5_trigger_sample_status_sample_0_posedge_status      0x00010000U
#define SRT_NX5_trigger_sample_status_sample_0_posedge_status      16
#define DFLT_VAL_NX5_trigger_sample_status_sample_0_posedge_status 0x00000000U
#define MSK_NX5_trigger_sample_status_sample_0_negedge_status      0x00020000U
#define SRT_NX5_trigger_sample_status_sample_0_negedge_status      17
#define DFLT_VAL_NX5_trigger_sample_status_sample_0_negedge_status 0x00000000U
#define MSK_NX5_trigger_sample_status_sample_0_in                  0x00040000U
#define SRT_NX5_trigger_sample_status_sample_0_in                  18
#define DFLT_VAL_NX5_trigger_sample_status_sample_0_in             0x00000000U
#define MSK_NX5_trigger_sample_status_sample_1_posedge_status      0x01000000U
#define SRT_NX5_trigger_sample_status_sample_1_posedge_status      24
#define DFLT_VAL_NX5_trigger_sample_status_sample_1_posedge_status 0x00000000U
#define MSK_NX5_trigger_sample_status_sample_1_negedge_status      0x02000000U
#define SRT_NX5_trigger_sample_status_sample_1_negedge_status      25
#define DFLT_VAL_NX5_trigger_sample_status_sample_1_negedge_status 0x00000000U
#define MSK_NX5_trigger_sample_status_sample_1_in                  0x04000000U
#define SRT_NX5_trigger_sample_status_sample_1_in                  26
#define DFLT_VAL_NX5_trigger_sample_status_sample_1_in             0x00000000U

enum {
	BFW_NX5_trigger_sample_status_sync0_status            = 1, /* [0] */
	BFW_NX5_trigger_sample_status_reserved1               = 7, /* [7:1] */
	BFW_NX5_trigger_sample_status_sync1_status            = 1, /* [8] */
	BFW_NX5_trigger_sample_status_reserved2               = 7, /* [15:9] */
	BFW_NX5_trigger_sample_status_sample_0_posedge_status = 1, /* [16] */
	BFW_NX5_trigger_sample_status_sample_0_negedge_status = 1, /* [17] */
	BFW_NX5_trigger_sample_status_sample_0_in             = 1, /* [18] */
	BFW_NX5_trigger_sample_status_reserved3               = 5, /* [23:19] */
	BFW_NX5_trigger_sample_status_sample_1_posedge_status = 1, /* [24] */
	BFW_NX5_trigger_sample_status_sample_1_negedge_status = 1, /* [25] */
	BFW_NX5_trigger_sample_status_sample_1_in             = 1, /* [26] */
	BFW_NX5_trigger_sample_status_reserved4               = 5  /* [31:27] */
};

typedef struct NX5_TRIGGER_SAMPLE_STATUS_BIT_Ttag {
	unsigned int sync0_status            : BFW_NX5_trigger_sample_status_sync0_status;            /* status of sync0                                     */
	unsigned int reserved1               : BFW_NX5_trigger_sample_status_reserved1;               /* reserved                                            */
	unsigned int sync1_status            : BFW_NX5_trigger_sample_status_sync1_status;            /* status of sync1                                     */
	unsigned int reserved2               : BFW_NX5_trigger_sample_status_reserved2;               /* reserved                                            */
	unsigned int sample_0_posedge_status : BFW_NX5_trigger_sample_status_sample_0_posedge_status; /* 1/0: positive edge detected/not detected at latch 0 */
	unsigned int sample_0_negedge_status : BFW_NX5_trigger_sample_status_sample_0_negedge_status; /* 1/0: negative edge detected/not detected at latch 0 */
	unsigned int sample_0_in             : BFW_NX5_trigger_sample_status_sample_0_in;             /* current value at latch0                             */
	unsigned int reserved3               : BFW_NX5_trigger_sample_status_reserved3;               /* reserved                                            */
	unsigned int sample_1_posedge_status : BFW_NX5_trigger_sample_status_sample_1_posedge_status; /* 1/0: positive edge detected/not detected at latch 1 */
	unsigned int sample_1_negedge_status : BFW_NX5_trigger_sample_status_sample_1_negedge_status; /* 1/0: negative edge detected/not detected at latch 1 */
	unsigned int sample_1_in             : BFW_NX5_trigger_sample_status_sample_1_in;             /* current value at latch1                             */
	unsigned int reserved4               : BFW_NX5_trigger_sample_status_reserved4;               /* reserved                                            */
} NX5_TRIGGER_SAMPLE_STATUS_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_TRIGGER_SAMPLE_STATUS_BIT_T bf;
} NX5_TRIGGER_SAMPLE_STATUS_T;

/* --------------------------------------------------------------------- */
/* Register trigger_sample_irq */
/* => r/w by xPEC and ARM, one global irq register for trigger_sample unit (must be also visible for HIF); irq set by xPEC, reset by arm (always with writing a 1 at appropriate bit position) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_sample_irq                 0x00000008U
#define Adr_NX5_trigger_sample_unit_trigger_sample_irq 0x018E5008U
#define Adr_NX5_trigger_sample_irq                     0x018E5008U
#define DFLT_VAL_NX5_trigger_sample_irq                0x00000000U

#define MSK_NX5_trigger_sample_irq_sync0_irq               0x00000001U
#define SRT_NX5_trigger_sample_irq_sync0_irq               0
#define DFLT_VAL_NX5_trigger_sample_irq_sync0_irq          0x00000000U
#define MSK_NX5_trigger_sample_irq_sync1_irq               0x00000002U
#define SRT_NX5_trigger_sample_irq_sync1_irq               1
#define DFLT_VAL_NX5_trigger_sample_irq_sync1_irq          0x00000000U
#define MSK_NX5_trigger_sample_irq_latch0_posedge_irq      0x00000100U
#define SRT_NX5_trigger_sample_irq_latch0_posedge_irq      8
#define DFLT_VAL_NX5_trigger_sample_irq_latch0_posedge_irq 0x00000000U
#define MSK_NX5_trigger_sample_irq_latch0_negedge_irq      0x00000200U
#define SRT_NX5_trigger_sample_irq_latch0_negedge_irq      9
#define DFLT_VAL_NX5_trigger_sample_irq_latch0_negedge_irq 0x00000000U
#define MSK_NX5_trigger_sample_irq_latch1_posedge_irq      0x00000400U
#define SRT_NX5_trigger_sample_irq_latch1_posedge_irq      10
#define DFLT_VAL_NX5_trigger_sample_irq_latch1_posedge_irq 0x00000000U
#define MSK_NX5_trigger_sample_irq_latch1_negedge_irq      0x00000800U
#define SRT_NX5_trigger_sample_irq_latch1_negedge_irq      11
#define DFLT_VAL_NX5_trigger_sample_irq_latch1_negedge_irq 0x00000000U

enum {
	BFW_NX5_trigger_sample_irq_sync0_irq          = 1,  /* [0] */
	BFW_NX5_trigger_sample_irq_sync1_irq          = 1,  /* [1] */
	BFW_NX5_trigger_sample_irq_reserved1          = 6,  /* [7:2] */
	BFW_NX5_trigger_sample_irq_latch0_posedge_irq = 1,  /* [8] */
	BFW_NX5_trigger_sample_irq_latch0_negedge_irq = 1,  /* [9] */
	BFW_NX5_trigger_sample_irq_latch1_posedge_irq = 1,  /* [10] */
	BFW_NX5_trigger_sample_irq_latch1_negedge_irq = 1,  /* [11] */
	BFW_NX5_trigger_sample_irq_reserved2          = 20  /* [31:12] */
};

typedef struct NX5_TRIGGER_SAMPLE_IRQ_BIT_Ttag {
	unsigned int sync0_irq          : BFW_NX5_trigger_sample_irq_sync0_irq;          /* sync0 interrupt # default 0 / tmst interrup (sercos 3 mode)      */
	unsigned int sync1_irq          : BFW_NX5_trigger_sample_irq_sync1_irq;          /* sync1 interrupt # default 0 / div clock interrupt(sercos 3 mode) */
	unsigned int reserved1          : BFW_NX5_trigger_sample_irq_reserved1;          /* reserved                                                         */
	unsigned int latch0_posedge_irq : BFW_NX5_trigger_sample_irq_latch0_posedge_irq; /* latch0 posedge interrupt (ethercat mode) / tint_0(sercos 3 mode) */
	unsigned int latch0_negedge_irq : BFW_NX5_trigger_sample_irq_latch0_negedge_irq; /* latch0 negedge interrupt (ethercat mode) / tint_1(sercos 3 mode) */
	unsigned int latch1_posedge_irq : BFW_NX5_trigger_sample_irq_latch1_posedge_irq; /* latch1 posedge interrupt (ethercat mode) / tint_2(sercos 3 mode) */
	unsigned int latch1_negedge_irq : BFW_NX5_trigger_sample_irq_latch1_negedge_irq; /* latch1 negedge interrupt (ethercat mode) / tint_3(sercos 3 mode) */
	unsigned int reserved2          : BFW_NX5_trigger_sample_irq_reserved2;          /* reserved                                                         */
} NX5_TRIGGER_SAMPLE_IRQ_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_TRIGGER_SAMPLE_IRQ_BIT_T bf;
} NX5_TRIGGER_SAMPLE_IRQ_T;

/* --------------------------------------------------------------------- */
/* Register trigger_activate */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_activate                 0x0000000CU
#define Adr_NX5_trigger_sample_unit_trigger_activate 0x018E500CU
#define Adr_NX5_trigger_activate                     0x018E500CU
#define DFLT_VAL_NX5_trigger_activate                0x00000000U

#define MSK_NX5_trigger_activate_trigger_unit_activate      0x00000100U
#define SRT_NX5_trigger_activate_trigger_unit_activate      8
#define DFLT_VAL_NX5_trigger_activate_trigger_unit_activate 0x00000000U
#define MSK_NX5_trigger_activate_sync0_activate             0x00000200U
#define SRT_NX5_trigger_activate_sync0_activate             9
#define DFLT_VAL_NX5_trigger_activate_sync0_activate        0x00000000U
#define MSK_NX5_trigger_activate_sync1_activate             0x00000400U
#define SRT_NX5_trigger_activate_sync1_activate             10
#define DFLT_VAL_NX5_trigger_activate_sync1_activate        0x00000000U

enum {
	BFW_NX5_trigger_activate_reserved1             = 8,  /* [7:0] */
	BFW_NX5_trigger_activate_trigger_unit_activate = 1,  /* [8] */
	BFW_NX5_trigger_activate_sync0_activate        = 1,  /* [9] */
	BFW_NX5_trigger_activate_sync1_activate        = 1,  /* [10] */
	BFW_NX5_trigger_activate_reserved2             = 21  /* [31:11] */
};

typedef struct NX5_TRIGGER_ACTIVATE_BIT_Ttag {
	unsigned int reserved1             : BFW_NX5_trigger_activate_reserved1;             /* reserved                                                                              */
	unsigned int trigger_unit_activate : BFW_NX5_trigger_activate_trigger_unit_activate; /* 0->1 (posedge): activates trigger unit cyclic functions, and sercos -> mode           */
	                                                                                     /* normal mode: unit waits for trigger_0_starttime and trigger_1_starttime independently */
	unsigned int sync0_activate        : BFW_NX5_trigger_activate_sync0_activate;        /* 1/0: sync0 activated/deactivated                                                      */
	unsigned int sync1_activate        : BFW_NX5_trigger_activate_sync1_activate;        /* 1/0: sync1 activated/deactivated                                                      */
	unsigned int reserved2             : BFW_NX5_trigger_activate_reserved2;             /* reserved                                                                              */
} NX5_TRIGGER_ACTIVATE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_TRIGGER_ACTIVATE_BIT_T bf;
} NX5_TRIGGER_ACTIVATE_T;

/* --------------------------------------------------------------------- */
/* Register trigger_impulse_length */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_impulse_length                 0x00000010U
#define Adr_NX5_trigger_sample_unit_trigger_impulse_length 0x018E5010U
#define Adr_NX5_trigger_impulse_length                     0x018E5010U
#define DFLT_VAL_NX5_trigger_impulse_length                0x00000000U

#define MSK_NX5_trigger_impulse_length_sync0_impulse_length      0x0000ffffU
#define SRT_NX5_trigger_impulse_length_sync0_impulse_length      0
#define DFLT_VAL_NX5_trigger_impulse_length_sync0_impulse_length 0x00000000U
#define MSK_NX5_trigger_impulse_length_sync1_impulse_length      0xffff0000U
#define SRT_NX5_trigger_impulse_length_sync1_impulse_length      16
#define DFLT_VAL_NX5_trigger_impulse_length_sync1_impulse_length 0x00000000U

enum {
	BFW_NX5_trigger_impulse_length_sync0_impulse_length = 16, /* [15:0] */
	BFW_NX5_trigger_impulse_length_sync1_impulse_length = 16  /* [31:16] */
};

typedef struct NX5_TRIGGER_IMPULSE_LENGTH_BIT_Ttag {
	unsigned int sync0_impulse_length : BFW_NX5_trigger_impulse_length_sync0_impulse_length; /* impulse length Sync0 signal (in Units of 10ns), 0x0000: activates acknowledge mode */
	unsigned int sync1_impulse_length : BFW_NX5_trigger_impulse_length_sync1_impulse_length; /* impulse length Sync1 signal (in Units of 10ns), 0x0000: activates acknowledge mode */
} NX5_TRIGGER_IMPULSE_LENGTH_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_TRIGGER_IMPULSE_LENGTH_BIT_T bf;
} NX5_TRIGGER_IMPULSE_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register trigger_0_starttime_ns */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_0_starttime_ns                 0x00000014U
#define Adr_NX5_trigger_sample_unit_trigger_0_starttime_ns 0x018E5014U
#define Adr_NX5_trigger_0_starttime_ns                     0x018E5014U
#define DFLT_VAL_NX5_trigger_0_starttime_ns                0x00000000U

#define MSK_NX5_trigger_0_starttime_ns_systime_ns      0xffffffffU
#define SRT_NX5_trigger_0_starttime_ns_systime_ns      0
#define DFLT_VAL_NX5_trigger_0_starttime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_trigger_0_starttime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_TRIGGER_0_STARTTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_trigger_0_starttime_ns_systime_ns; /* write: system time ns when 1st sync0 event shall occur */
	                                                                     /* read: systime_ns value of next sync0 event             */
} NX5_TRIGGER_0_STARTTIME_NS_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_TRIGGER_0_STARTTIME_NS_BIT_T bf;
} NX5_TRIGGER_0_STARTTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register trigger_1_starttime_ns */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_1_starttime_ns                 0x0000001CU
#define Adr_NX5_trigger_sample_unit_trigger_1_starttime_ns 0x018E501CU
#define Adr_NX5_trigger_1_starttime_ns                     0x018E501CU
#define DFLT_VAL_NX5_trigger_1_starttime_ns                0x00000000U

#define MSK_NX5_trigger_1_starttime_ns_systime_ns      0xffffffffU
#define SRT_NX5_trigger_1_starttime_ns_systime_ns      0
#define DFLT_VAL_NX5_trigger_1_starttime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_trigger_1_starttime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_TRIGGER_1_STARTTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_trigger_1_starttime_ns_systime_ns; /* write: systime_ns when 1st sync1 event shall occur */
	                                                                     /* read: systime_ns value of next sync1 event         */
} NX5_TRIGGER_1_STARTTIME_NS_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_TRIGGER_1_STARTTIME_NS_BIT_T bf;
} NX5_TRIGGER_1_STARTTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register trigger_0_cyc_time */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_0_cyc_time                 0x00000024U
#define Adr_NX5_trigger_sample_unit_trigger_0_cyc_time 0x018E5024U
#define Adr_NX5_trigger_0_cyc_time                     0x018E5024U
#define DFLT_VAL_NX5_trigger_0_cyc_time                0x00000000U

#define MSK_NX5_trigger_0_cyc_time_systime_ns      0xffffffffU
#define SRT_NX5_trigger_0_cyc_time_systime_ns      0
#define DFLT_VAL_NX5_trigger_0_cyc_time_systime_ns 0x00000000U

enum {
	BFW_NX5_trigger_0_cyc_time_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_TRIGGER_0_CYC_TIME_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_trigger_0_cyc_time_systime_ns; /* Time between two consecutive SYNC0 Signals                          */
	                                                                 /* cyclic functions are disabled if CYC_TIME0==0 -> single event usage */
} NX5_TRIGGER_0_CYC_TIME_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_TRIGGER_0_CYC_TIME_BIT_T bf;
} NX5_TRIGGER_0_CYC_TIME_T;

/* --------------------------------------------------------------------- */
/* Register trigger_1_cyc_time */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_trigger_1_cyc_time                 0x00000028U
#define Adr_NX5_trigger_sample_unit_trigger_1_cyc_time 0x018E5028U
#define Adr_NX5_trigger_1_cyc_time                     0x018E5028U
#define DFLT_VAL_NX5_trigger_1_cyc_time                0x00000000U

#define MSK_NX5_trigger_1_cyc_time_systime_ns      0xffffffffU
#define SRT_NX5_trigger_1_cyc_time_systime_ns      0
#define DFLT_VAL_NX5_trigger_1_cyc_time_systime_ns 0x00000000U

enum {
	BFW_NX5_trigger_1_cyc_time_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_TRIGGER_1_CYC_TIME_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_trigger_1_cyc_time_systime_ns; /* normal mode: Time between two consecutive SYNC1 Signal */
	                                                                 /* ecat mode: Time between SYNC1 Signal and SYNC0 Signal  */
} NX5_TRIGGER_1_CYC_TIME_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_TRIGGER_1_CYC_TIME_BIT_T bf;
} NX5_TRIGGER_1_CYC_TIME_T;

/* --------------------------------------------------------------------- */
/* Register sample_mode */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sample_mode                 0x0000002CU
#define Adr_NX5_trigger_sample_unit_sample_mode 0x018E502CU
#define Adr_NX5_sample_mode                     0x018E502CU
#define DFLT_VAL_NX5_sample_mode                0x00000000U

#define MSK_NX5_sample_mode_sample_0_posedge_mode      0x00000001U
#define SRT_NX5_sample_mode_sample_0_posedge_mode      0
#define DFLT_VAL_NX5_sample_mode_sample_0_posedge_mode 0x00000000U
#define MSK_NX5_sample_mode_sample_0_negedge_mode      0x00000002U
#define SRT_NX5_sample_mode_sample_0_negedge_mode      1
#define DFLT_VAL_NX5_sample_mode_sample_0_negedge_mode 0x00000000U
#define MSK_NX5_sample_mode_sample_1_posedge_mode      0x00000100U
#define SRT_NX5_sample_mode_sample_1_posedge_mode      8
#define DFLT_VAL_NX5_sample_mode_sample_1_posedge_mode 0x00000000U
#define MSK_NX5_sample_mode_sample_1_negedge_mode      0x00000200U
#define SRT_NX5_sample_mode_sample_1_negedge_mode      9
#define DFLT_VAL_NX5_sample_mode_sample_1_negedge_mode 0x00000000U

enum {
	BFW_NX5_sample_mode_sample_0_posedge_mode = 1,  /* [0] */
	BFW_NX5_sample_mode_sample_0_negedge_mode = 1,  /* [1] */
	BFW_NX5_sample_mode_reserved1             = 6,  /* [7:2] */
	BFW_NX5_sample_mode_sample_1_posedge_mode = 1,  /* [8] */
	BFW_NX5_sample_mode_sample_1_negedge_mode = 1,  /* [9] */
	BFW_NX5_sample_mode_reserved2             = 22  /* [31:10] */
};

typedef struct NX5_SAMPLE_MODE_BIT_Ttag {
	unsigned int sample_0_posedge_mode : BFW_NX5_sample_mode_sample_0_posedge_mode; /* latch0 positive edge mode                                                                            */
	                                                                                /* 0: continuous sampling 1: single sampling (latch status must be reset before latching enabled again) */
	unsigned int sample_0_negedge_mode : BFW_NX5_sample_mode_sample_0_negedge_mode; /* latch0 negative edge mode                                                                            */
	                                                                                /* 0: continuous sampling 1: single sampling (latch status must be reset before latching enabled again) */
	unsigned int reserved1             : BFW_NX5_sample_mode_reserved1;             /* reserved                                                                                             */
	unsigned int sample_1_posedge_mode : BFW_NX5_sample_mode_sample_1_posedge_mode; /* latch1 positive edge mode                                                                            */
	                                                                                /* 0: continuous sampling 1: single sampling (latch status must be reset before latching enabled again) */
	unsigned int sample_1_negedge_mode : BFW_NX5_sample_mode_sample_1_negedge_mode; /* latch1 negative edge mode                                                                            */
	                                                                                /* 0: continuous sampling 1: single sampling (latch status must be reset before latching enabled again) */
	unsigned int reserved2             : BFW_NX5_sample_mode_reserved2;             /* reserved                                                                                             */
} NX5_SAMPLE_MODE_BIT_T;

typedef union {
	unsigned int          val;
	NX5_SAMPLE_MODE_BIT_T bf;
} NX5_SAMPLE_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sample_0_pos_systime_ns */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sample_0_pos_systime_ns                 0x00000030U
#define Adr_NX5_trigger_sample_unit_sample_0_pos_systime_ns 0x018E5030U
#define Adr_NX5_sample_0_pos_systime_ns                     0x018E5030U
#define DFLT_VAL_NX5_sample_0_pos_systime_ns                0x00000000U

#define MSK_NX5_sample_0_pos_systime_ns_systime_ns      0xffffffffU
#define SRT_NX5_sample_0_pos_systime_ns_systime_ns      0
#define DFLT_VAL_NX5_sample_0_pos_systime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_sample_0_pos_systime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_SAMPLE_0_POS_SYSTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_sample_0_pos_systime_ns_systime_ns; /* systime_ns when posedge at latch 0 occurred */
} NX5_SAMPLE_0_POS_SYSTIME_NS_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_SAMPLE_0_POS_SYSTIME_NS_BIT_T bf;
} NX5_SAMPLE_0_POS_SYSTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register sample_0_neg_systime_ns */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sample_0_neg_systime_ns                 0x00000038U
#define Adr_NX5_trigger_sample_unit_sample_0_neg_systime_ns 0x018E5038U
#define Adr_NX5_sample_0_neg_systime_ns                     0x018E5038U
#define DFLT_VAL_NX5_sample_0_neg_systime_ns                0x00000000U

#define MSK_NX5_sample_0_neg_systime_ns_systime_ns      0xffffffffU
#define SRT_NX5_sample_0_neg_systime_ns_systime_ns      0
#define DFLT_VAL_NX5_sample_0_neg_systime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_sample_0_neg_systime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_SAMPLE_0_NEG_SYSTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_sample_0_neg_systime_ns_systime_ns; /* systime_ns when posedge at latch 0 occurred */
} NX5_SAMPLE_0_NEG_SYSTIME_NS_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_SAMPLE_0_NEG_SYSTIME_NS_BIT_T bf;
} NX5_SAMPLE_0_NEG_SYSTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register sample_1_pos_systime_ns */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sample_1_pos_systime_ns                 0x00000040U
#define Adr_NX5_trigger_sample_unit_sample_1_pos_systime_ns 0x018E5040U
#define Adr_NX5_sample_1_pos_systime_ns                     0x018E5040U
#define DFLT_VAL_NX5_sample_1_pos_systime_ns                0x00000000U

#define MSK_NX5_sample_1_pos_systime_ns_systime_ns      0xffffffffU
#define SRT_NX5_sample_1_pos_systime_ns_systime_ns      0
#define DFLT_VAL_NX5_sample_1_pos_systime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_sample_1_pos_systime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_SAMPLE_1_POS_SYSTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_sample_1_pos_systime_ns_systime_ns; /* systime_ns when posedge at latch 1 occurred */
} NX5_SAMPLE_1_POS_SYSTIME_NS_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_SAMPLE_1_POS_SYSTIME_NS_BIT_T bf;
} NX5_SAMPLE_1_POS_SYSTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register sample_1_neg_systime_ns */
/* => r/w access by xPEC and ARM */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sample_1_neg_systime_ns                 0x00000048U
#define Adr_NX5_trigger_sample_unit_sample_1_neg_systime_ns 0x018E5048U
#define Adr_NX5_sample_1_neg_systime_ns                     0x018E5048U
#define DFLT_VAL_NX5_sample_1_neg_systime_ns                0x00000000U

#define MSK_NX5_sample_1_neg_systime_ns_systime_ns      0xffffffffU
#define SRT_NX5_sample_1_neg_systime_ns_systime_ns      0
#define DFLT_VAL_NX5_sample_1_neg_systime_ns_systime_ns 0x00000000U

enum {
	BFW_NX5_sample_1_neg_systime_ns_systime_ns = 32  /* [31:0] */
};

typedef struct NX5_SAMPLE_1_NEG_SYSTIME_NS_BIT_Ttag {
	unsigned int systime_ns : BFW_NX5_sample_1_neg_systime_ns_systime_ns; /* systime_ns when negedge at latch 1 occurred */
} NX5_SAMPLE_1_NEG_SYSTIME_NS_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_SAMPLE_1_NEG_SYSTIME_NS_BIT_T bf;
} NX5_SAMPLE_1_NEG_SYSTIME_NS_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_timing_delay_mst_1 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_trigger_0_starttime_ns (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_timing_delay_mst_1                 0x00000050U
#define Adr_NX5_trigger_sample_unit_sercos3_timing_delay_mst_1 0x018E5050U
#define Adr_NX5_sercos3_timing_delay_mst_1                     0x018E5050U
#define DFLT_VAL_NX5_sercos3_timing_delay_mst_1                0x00000000U

#define MSK_NX5_sercos3_timing_delay_mst_1_timing_delay_mst_1      0xffffffffU
#define SRT_NX5_sercos3_timing_delay_mst_1_timing_delay_mst_1      0
#define DFLT_VAL_NX5_sercos3_timing_delay_mst_1_timing_delay_mst_1 0x00000000U

enum {
	BFW_NX5_sercos3_timing_delay_mst_1_timing_delay_mst_1 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TIMING_DELAY_MST_1_BIT_Ttag {
	unsigned int timing_delay_mst_1 : BFW_NX5_sercos3_timing_delay_mst_1_timing_delay_mst_1; /* Timing Delay MST 1 (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TIMING_DELAY_MST_1_BIT_T;

typedef union {
	unsigned int                         val;
	NX5_SERCOS3_TIMING_DELAY_MST_1_BIT_T bf;
} NX5_SERCOS3_TIMING_DELAY_MST_1_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_timing_delay_mst_2 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_trigger_1_starttime_ns (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_timing_delay_mst_2                 0x00000054U
#define Adr_NX5_trigger_sample_unit_sercos3_timing_delay_mst_2 0x018E5054U
#define Adr_NX5_sercos3_timing_delay_mst_2                     0x018E5054U
#define DFLT_VAL_NX5_sercos3_timing_delay_mst_2                0x00000000U

#define MSK_NX5_sercos3_timing_delay_mst_2_timing_delay_mst_2      0xffffffffU
#define SRT_NX5_sercos3_timing_delay_mst_2_timing_delay_mst_2      0
#define DFLT_VAL_NX5_sercos3_timing_delay_mst_2_timing_delay_mst_2 0x00000000U

enum {
	BFW_NX5_sercos3_timing_delay_mst_2_timing_delay_mst_2 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TIMING_DELAY_MST_2_BIT_Ttag {
	unsigned int timing_delay_mst_2 : BFW_NX5_sercos3_timing_delay_mst_2_timing_delay_mst_2; /* Timing Delay MST 2 (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TIMING_DELAY_MST_2_BIT_T;

typedef union {
	unsigned int                         val;
	NX5_SERCOS3_TIMING_DELAY_MST_2_BIT_T bf;
} NX5_SERCOS3_TIMING_DELAY_MST_2_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_ring_delay */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_trigger_impulse_length (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_ring_delay                 0x00000058U
#define Adr_NX5_trigger_sample_unit_sercos3_ring_delay 0x018E5058U
#define Adr_NX5_sercos3_ring_delay                     0x018E5058U
#define DFLT_VAL_NX5_sercos3_ring_delay                0x00000000U

#define MSK_NX5_sercos3_ring_delay_ring_delay      0xffffffffU
#define SRT_NX5_sercos3_ring_delay_ring_delay      0
#define DFLT_VAL_NX5_sercos3_ring_delay_ring_delay 0x00000000U

enum {
	BFW_NX5_sercos3_ring_delay_ring_delay = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_RING_DELAY_BIT_Ttag {
	unsigned int ring_delay : BFW_NX5_sercos3_ring_delay_ring_delay; /* Ring Delay (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_RING_DELAY_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_SERCOS3_RING_DELAY_BIT_T bf;
} NX5_SERCOS3_RING_DELAY_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_sync_count_1 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_sample_0_pos_systime_ns (ethercat) */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_sync_count_1                 0x0000005CU
#define Adr_NX5_trigger_sample_unit_sercos3_sync_count_1 0x018E505CU
#define Adr_NX5_sercos3_sync_count_1                     0x018E505CU

#define MSK_NX5_sercos3_sync_count_1_sync_count_1 0xffffffffU
#define SRT_NX5_sercos3_sync_count_1_sync_count_1 0

enum {
	BFW_NX5_sercos3_sync_count_1_sync_count_1 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_SYNC_COUNT_1_BIT_Ttag {
	unsigned int sync_count_1 : BFW_NX5_sercos3_sync_count_1_sync_count_1; /* Sync Count 1 (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_SYNC_COUNT_1_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_SERCOS3_SYNC_COUNT_1_BIT_T bf;
} NX5_SERCOS3_SYNC_COUNT_1_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_sync_count_2 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_sample_0_neg_systime_ns (ethercat) */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_sync_count_2                 0x00000060U
#define Adr_NX5_trigger_sample_unit_sercos3_sync_count_2 0x018E5060U
#define Adr_NX5_sercos3_sync_count_2                     0x018E5060U

#define MSK_NX5_sercos3_sync_count_2_sync_count_2 0xffffffffU
#define SRT_NX5_sercos3_sync_count_2_sync_count_2 0

enum {
	BFW_NX5_sercos3_sync_count_2_sync_count_2 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_SYNC_COUNT_2_BIT_Ttag {
	unsigned int sync_count_2 : BFW_NX5_sercos3_sync_count_2_sync_count_2; /* Sync Count 2 (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_SYNC_COUNT_2_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_SERCOS3_SYNC_COUNT_2_BIT_T bf;
} NX5_SERCOS3_SYNC_COUNT_2_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tcnt_0 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_sample_1_pos_systime_ns (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tcnt_0                 0x00000064U
#define Adr_NX5_trigger_sample_unit_sercos3_tcnt_0 0x018E5064U
#define Adr_NX5_sercos3_tcnt_0                     0x018E5064U
#define DFLT_VAL_NX5_sercos3_tcnt_0                0x00000000U

#define MSK_NX5_sercos3_tcnt_0_tcnt_0      0xffffffffU
#define SRT_NX5_sercos3_tcnt_0_tcnt_0      0
#define DFLT_VAL_NX5_sercos3_tcnt_0_tcnt_0 0x00000000U

enum {
	BFW_NX5_sercos3_tcnt_0_tcnt_0 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TCNT_0_BIT_Ttag {
	unsigned int tcnt_0 : BFW_NX5_sercos3_tcnt_0_tcnt_0; /* tcnt_0 (con clock)(Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TCNT_0_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SERCOS3_TCNT_0_BIT_T bf;
} NX5_SERCOS3_TCNT_0_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tcnt_1 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_sample_1_neg_systime_ns (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tcnt_1                 0x00000068U
#define Adr_NX5_trigger_sample_unit_sercos3_tcnt_1 0x018E5068U
#define Adr_NX5_sercos3_tcnt_1                     0x018E5068U
#define DFLT_VAL_NX5_sercos3_tcnt_1                0x00000000U

#define MSK_NX5_sercos3_tcnt_1_tcnt_1      0xffffffffU
#define SRT_NX5_sercos3_tcnt_1_tcnt_1      0
#define DFLT_VAL_NX5_sercos3_tcnt_1_tcnt_1 0x00000000U

enum {
	BFW_NX5_sercos3_tcnt_1_tcnt_1 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TCNT_1_BIT_Ttag {
	unsigned int tcnt_1 : BFW_NX5_sercos3_tcnt_1_tcnt_1; /* tcnt_1 (con clock length)(Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TCNT_1_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SERCOS3_TCNT_1_BIT_T bf;
} NX5_SERCOS3_TCNT_1_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tcnt_2 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_trigger_0_cyc_time (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tcnt_2                 0x0000006CU
#define Adr_NX5_trigger_sample_unit_sercos3_tcnt_2 0x018E506CU
#define Adr_NX5_sercos3_tcnt_2                     0x018E506CU
#define DFLT_VAL_NX5_sercos3_tcnt_2                0x00000000U

#define MSK_NX5_sercos3_tcnt_2_tcnt_2      0xffffffffU
#define SRT_NX5_sercos3_tcnt_2_tcnt_2      0
#define DFLT_VAL_NX5_sercos3_tcnt_2_tcnt_2 0x00000000U

enum {
	BFW_NX5_sercos3_tcnt_2_tcnt_2 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TCNT_2_BIT_Ttag {
	unsigned int tcnt_2 : BFW_NX5_sercos3_tcnt_2_tcnt_2; /* tcnt_2 (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TCNT_2_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SERCOS3_TCNT_2_BIT_T bf;
} NX5_SERCOS3_TCNT_2_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tcnt_3 */
/* => r/w access by xPEC and ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_trigger_1_cyc_time (ethercat) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tcnt_3                 0x00000070U
#define Adr_NX5_trigger_sample_unit_sercos3_tcnt_3 0x018E5070U
#define Adr_NX5_sercos3_tcnt_3                     0x018E5070U
#define DFLT_VAL_NX5_sercos3_tcnt_3                0x00000000U

#define MSK_NX5_sercos3_tcnt_3_tcnt_3      0xffffffffU
#define SRT_NX5_sercos3_tcnt_3_tcnt_3      0
#define DFLT_VAL_NX5_sercos3_tcnt_3_tcnt_3 0x00000000U

enum {
	BFW_NX5_sercos3_tcnt_3_tcnt_3 = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TCNT_3_BIT_Ttag {
	unsigned int tcnt_3 : BFW_NX5_sercos3_tcnt_3_tcnt_3; /* tcnt_3 (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TCNT_3_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SERCOS3_TCNT_3_BIT_T bf;
} NX5_SERCOS3_TCNT_3_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tdiv_clk */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu0_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tdiv_clk                 0x00000074U
#define Adr_NX5_trigger_sample_unit_sercos3_tdiv_clk 0x018E5074U
#define Adr_NX5_sercos3_tdiv_clk                     0x018E5074U
#define DFLT_VAL_NX5_sercos3_tdiv_clk                0x00000000U

#define MSK_NX5_sercos3_tdiv_clk_tdiv_clk      0xffffffffU
#define SRT_NX5_sercos3_tdiv_clk_tdiv_clk      0
#define DFLT_VAL_NX5_sercos3_tdiv_clk_tdiv_clk 0x00000000U

enum {
	BFW_NX5_sercos3_tdiv_clk_tdiv_clk = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TDIV_CLK_BIT_Ttag {
	unsigned int tdiv_clk : BFW_NX5_sercos3_tdiv_clk_tdiv_clk; /* tdiv_clk (Sercos3) (1ns resolution - 10ns steps)+10ns ? */
} NX5_SERCOS3_TDIV_CLK_BIT_T;

typedef union {
	unsigned int               val;
	NX5_SERCOS3_TDIV_CLK_BIT_T bf;
} NX5_SERCOS3_TDIV_CLK_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_dtdiv_clk */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu1_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_dtdiv_clk                 0x00000078U
#define Adr_NX5_trigger_sample_unit_sercos3_dtdiv_clk 0x018E5078U
#define Adr_NX5_sercos3_dtdiv_clk                     0x018E5078U
#define DFLT_VAL_NX5_sercos3_dtdiv_clk                0x00000000U

#define MSK_NX5_sercos3_dtdiv_clk_dtdiv_clk      0xffffffffU
#define SRT_NX5_sercos3_dtdiv_clk_dtdiv_clk      0
#define DFLT_VAL_NX5_sercos3_dtdiv_clk_dtdiv_clk 0x00000000U

enum {
	BFW_NX5_sercos3_dtdiv_clk_dtdiv_clk = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_DTDIV_CLK_BIT_Ttag {
	unsigned int dtdiv_clk : BFW_NX5_sercos3_dtdiv_clk_dtdiv_clk; /* dtdiv_clk (Sercos3) (1ns resolution - 10ns steps) +10ns ? */
} NX5_SERCOS3_DTDIV_CLK_BIT_T;

typedef union {
	unsigned int                val;
	NX5_SERCOS3_DTDIV_CLK_BIT_T bf;
} NX5_SERCOS3_DTDIV_CLK_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_ndiv_clk */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu2_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_ndiv_clk                 0x0000007CU
#define Adr_NX5_trigger_sample_unit_sercos3_ndiv_clk 0x018E507CU
#define Adr_NX5_sercos3_ndiv_clk                     0x018E507CU
#define DFLT_VAL_NX5_sercos3_ndiv_clk                0x00000000U

#define MSK_NX5_sercos3_ndiv_clk_ndiv_clk      0x000000ffU
#define SRT_NX5_sercos3_ndiv_clk_ndiv_clk      0
#define DFLT_VAL_NX5_sercos3_ndiv_clk_ndiv_clk 0x00000000U

enum {
	BFW_NX5_sercos3_ndiv_clk_ndiv_clk  = 8,  /* [7:0] */
	BFW_NX5_sercos3_ndiv_clk_reserved1 = 24  /* [31:8] */
};

typedef struct NX5_SERCOS3_NDIV_CLK_BIT_Ttag {
	unsigned int ndiv_clk  : BFW_NX5_sercos3_ndiv_clk_ndiv_clk;  /* ndiv_clk (Sercos3) */
	unsigned int reserved1 : BFW_NX5_sercos3_ndiv_clk_reserved1; /* reserved           */
} NX5_SERCOS3_NDIV_CLK_BIT_T;

typedef union {
	unsigned int               val;
	NX5_SERCOS3_NDIV_CLK_BIT_T bf;
} NX5_SERCOS3_NDIV_CLK_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_divclk_length */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu3_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_divclk_length                 0x00000080U
#define Adr_NX5_trigger_sample_unit_sercos3_divclk_length 0x018E5080U
#define Adr_NX5_sercos3_divclk_length                     0x018E5080U
#define DFLT_VAL_NX5_sercos3_divclk_length                0x00000000U

#define MSK_NX5_sercos3_divclk_length_divclk_length      0xffffffffU
#define SRT_NX5_sercos3_divclk_length_divclk_length      0
#define DFLT_VAL_NX5_sercos3_divclk_length_divclk_length 0x00000000U

enum {
	BFW_NX5_sercos3_divclk_length_divclk_length = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_DIVCLK_LENGTH_BIT_Ttag {
	unsigned int divclk_length : BFW_NX5_sercos3_divclk_length_divclk_length; /* divclk_length (Sercos3) (1ns resolution - 10ns steps) +10ns ? */
} NX5_SERCOS3_DIVCLK_LENGTH_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_SERCOS3_DIVCLK_LENGTH_BIT_T bf;
} NX5_SERCOS3_DIVCLK_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_divclk_config */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu4_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_divclk_config                 0x00000084U
#define Adr_NX5_trigger_sample_unit_sercos3_divclk_config 0x018E5084U
#define Adr_NX5_sercos3_divclk_config                     0x018E5084U
#define DFLT_VAL_NX5_sercos3_divclk_config                0x00000000U

#define MSK_NX5_sercos3_divclk_config_line_port_1      0x00000001U
#define SRT_NX5_sercos3_divclk_config_line_port_1      0
#define DFLT_VAL_NX5_sercos3_divclk_config_line_port_1 0x00000000U
#define MSK_NX5_sercos3_divclk_config_line_port_2      0x00000002U
#define SRT_NX5_sercos3_divclk_config_line_port_2      1
#define DFLT_VAL_NX5_sercos3_divclk_config_line_port_2 0x00000000U
#define MSK_NX5_sercos3_divclk_config_divclk_mode      0x00000004U
#define SRT_NX5_sercos3_divclk_config_divclk_mode      2
#define DFLT_VAL_NX5_sercos3_divclk_config_divclk_mode 0x00000000U
#define MSK_NX5_sercos3_divclk_config_sel_mst_1        0x00000078U
#define SRT_NX5_sercos3_divclk_config_sel_mst_1        3
#define DFLT_VAL_NX5_sercos3_divclk_config_sel_mst_1   0x00000000U
#define MSK_NX5_sercos3_divclk_config_sel_mst_2        0x00000780U
#define SRT_NX5_sercos3_divclk_config_sel_mst_2        7
#define DFLT_VAL_NX5_sercos3_divclk_config_sel_mst_2   0x00000000U

enum {
	BFW_NX5_sercos3_divclk_config_line_port_1 = 1,  /* [0] */
	BFW_NX5_sercos3_divclk_config_line_port_2 = 1,  /* [1] */
	BFW_NX5_sercos3_divclk_config_divclk_mode = 1,  /* [2] */
	BFW_NX5_sercos3_divclk_config_sel_mst_1   = 4,  /* [6:3] */
	BFW_NX5_sercos3_divclk_config_sel_mst_2   = 4,  /* [10:7] */
	BFW_NX5_sercos3_divclk_config_reserved1   = 21  /* [31:11] */
};

typedef struct NX5_SERCOS3_DIVCLK_CONFIG_BIT_Ttag {
	unsigned int line_port_1 : BFW_NX5_sercos3_divclk_config_line_port_1; /* loopback only port1 receive                          */
	unsigned int line_port_2 : BFW_NX5_sercos3_divclk_config_line_port_2; /* loopback only port2 receive                          */
	unsigned int divclk_mode : BFW_NX5_sercos3_divclk_config_divclk_mode; /* divclk_mode                                          */
	unsigned int sel_mst_1   : BFW_NX5_sercos3_divclk_config_sel_mst_1;   /* sel_mst_1 from shared register -> nr 0 - 15 - bit 15 */
	unsigned int sel_mst_2   : BFW_NX5_sercos3_divclk_config_sel_mst_2;   /* sel_mst_2 from shared register -> nr 0 - 15 - bit 15 */
	unsigned int reserved1   : BFW_NX5_sercos3_divclk_config_reserved1;   /* reserved                                             */
} NX5_SERCOS3_DIVCLK_CONFIG_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_SERCOS3_DIVCLK_CONFIG_BIT_T bf;
} NX5_SERCOS3_DIVCLK_CONFIG_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tcnt_max */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu5_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tcnt_max                 0x00000088U
#define Adr_NX5_trigger_sample_unit_sercos3_tcnt_max 0x018E5088U
#define Adr_NX5_sercos3_tcnt_max                     0x018E5088U
#define DFLT_VAL_NX5_sercos3_tcnt_max                0x00000000U

#define MSK_NX5_sercos3_tcnt_max_tcnt_max      0xffffffffU
#define SRT_NX5_sercos3_tcnt_max_tcnt_max      0
#define DFLT_VAL_NX5_sercos3_tcnt_max_tcnt_max 0x00000000U

enum {
	BFW_NX5_sercos3_tcnt_max_tcnt_max = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TCNT_MAX_BIT_Ttag {
	unsigned int tcnt_max : BFW_NX5_sercos3_tcnt_max_tcnt_max; /* tcnt_max (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TCNT_MAX_BIT_T;

typedef union {
	unsigned int               val;
	NX5_SERCOS3_TCNT_MAX_BIT_T bf;
} NX5_SERCOS3_TCNT_MAX_T;

/* --------------------------------------------------------------------- */
/* Register sercos3_tmx */
/* => r/w access by ARM */
/*    WARNING: separate address for SERCOS 3 / same register: adr_fmmu6_cfg_log_startaddr (ethercat FMMUSM - Unit) */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sercos3_tmx                 0x0000008CU
#define Adr_NX5_trigger_sample_unit_sercos3_tmx 0x018E508CU
#define Adr_NX5_sercos3_tmx                     0x018E508CU
#define DFLT_VAL_NX5_sercos3_tmx                0x00000000U

#define MSK_NX5_sercos3_tmx_tmx      0xffffffffU
#define SRT_NX5_sercos3_tmx_tmx      0
#define DFLT_VAL_NX5_sercos3_tmx_tmx 0x00000000U

enum {
	BFW_NX5_sercos3_tmx_tmx = 32  /* [31:0] */
};

typedef struct NX5_SERCOS3_TMX_BIT_Ttag {
	unsigned int tmx : BFW_NX5_sercos3_tmx_tmx; /* tmx  (Sercos3) (1ns resolution - 10ns steps) */
} NX5_SERCOS3_TMX_BIT_T;

typedef union {
	unsigned int          val;
	NX5_SERCOS3_TMX_BIT_T bf;
} NX5_SERCOS3_TMX_T;


/* ===================================================================== */

/* Area of fmmusm */

/* ===================================================================== */

#define Addr_NX5_fmmusm      0x018E5400U
#define NX5_NETX_FMMUSM_AREA 0x018E5400U

/* --------------------------------------------------------------------- */
/* Register fmmu0_cfg_log_startaddr */
/* => FMMU 0 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu0_cfg_log_startaddr    0x00000000U
#define Adr_NX5_fmmusm_fmmu0_cfg_log_startaddr 0x018E5400U
#define Adr_NX5_fmmu0_cfg_log_startaddr        0x018E5400U
#define DFLT_VAL_NX5_fmmu0_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu0_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu0_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu0_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu0_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU0_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu0_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU0_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU0_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU0_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu0_cfg_length */
/* => FMMU 0 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu0_cfg_length    0x00000004U
#define Adr_NX5_fmmusm_fmmu0_cfg_length 0x018E5404U
#define Adr_NX5_fmmu0_cfg_length        0x018E5404U
#define DFLT_VAL_NX5_fmmu0_cfg_length   0x07000000U

#define MSK_NX5_fmmu0_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu0_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu0_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu0_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu0_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu0_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu0_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu0_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu0_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu0_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu0_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu0_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu0_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu0_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu0_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU0_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu0_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu0_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu0_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu0_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu0_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu0_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU0_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU0_CFG_LENGTH_BIT_T bf;
} NX5_FMMU0_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu0_cfg_phys_startaddr */
/* => FMMU 0 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu0_cfg_phys_startaddr    0x00000008U
#define Adr_NX5_fmmusm_fmmu0_cfg_phys_startaddr 0x018E5408U
#define Adr_NX5_fmmu0_cfg_phys_startaddr        0x018E5408U
#define DFLT_VAL_NX5_fmmu0_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu0_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu0_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu0_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu0_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu0_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu0_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu0_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu0_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu0_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu0_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu0_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu0_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu0_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu0_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu0_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu0_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu0_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu0_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu0_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU0_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu0_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu0_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu0_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu0_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu0_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel  */
	unsigned int proc_wr_enable : BFW_NX5_fmmu0_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu0_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU0_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU0_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU0_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu0_cfg_enable */
/* => FMMU 0 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu0_cfg_enable    0x0000000CU
#define Adr_NX5_fmmusm_fmmu0_cfg_enable 0x018E540CU
#define Adr_NX5_fmmu0_cfg_enable        0x018E540CU
#define DFLT_VAL_NX5_fmmu0_cfg_enable   0x00000000U

#define MSK_NX5_fmmu0_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu0_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu0_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu0_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu0_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU0_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu0_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu0_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU0_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU0_CFG_ENABLE_BIT_T bf;
} NX5_FMMU0_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu1_cfg_log_startaddr */
/* => FMMU 1 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu1_cfg_log_startaddr    0x00000010U
#define Adr_NX5_fmmusm_fmmu1_cfg_log_startaddr 0x018E5410U
#define Adr_NX5_fmmu1_cfg_log_startaddr        0x018E5410U
#define DFLT_VAL_NX5_fmmu1_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu1_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu1_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu1_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu1_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU1_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu1_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU1_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU1_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU1_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu1_cfg_length */
/* => FMMU 1 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu1_cfg_length    0x00000014U
#define Adr_NX5_fmmusm_fmmu1_cfg_length 0x018E5414U
#define Adr_NX5_fmmu1_cfg_length        0x018E5414U
#define DFLT_VAL_NX5_fmmu1_cfg_length   0x07000000U

#define MSK_NX5_fmmu1_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu1_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu1_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu1_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu1_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu1_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu1_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu1_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu1_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu1_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu1_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu1_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu1_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu1_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu1_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU1_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu1_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu1_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu1_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu1_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu1_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu1_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU1_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU1_CFG_LENGTH_BIT_T bf;
} NX5_FMMU1_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu1_cfg_phys_startaddr */
/* => FMMU 1 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu1_cfg_phys_startaddr    0x00000018U
#define Adr_NX5_fmmusm_fmmu1_cfg_phys_startaddr 0x018E5418U
#define Adr_NX5_fmmu1_cfg_phys_startaddr        0x018E5418U
#define DFLT_VAL_NX5_fmmu1_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu1_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu1_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu1_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu1_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu1_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu1_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu1_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu1_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu1_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu1_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu1_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu1_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu1_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu1_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu1_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu1_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu1_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu1_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu1_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU1_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu1_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu1_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu1_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu1_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu1_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu1_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu1_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU1_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU1_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU1_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu1_cfg_enable */
/* => FMMU 1 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu1_cfg_enable    0x0000001CU
#define Adr_NX5_fmmusm_fmmu1_cfg_enable 0x018E541CU
#define Adr_NX5_fmmu1_cfg_enable        0x018E541CU
#define DFLT_VAL_NX5_fmmu1_cfg_enable   0x00000000U

#define MSK_NX5_fmmu1_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu1_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu1_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu1_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu1_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU1_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu1_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu1_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU1_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU1_CFG_ENABLE_BIT_T bf;
} NX5_FMMU1_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu2_cfg_log_startaddr */
/* => FMMU 2 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu2_cfg_log_startaddr    0x00000020U
#define Adr_NX5_fmmusm_fmmu2_cfg_log_startaddr 0x018E5420U
#define Adr_NX5_fmmu2_cfg_log_startaddr        0x018E5420U
#define DFLT_VAL_NX5_fmmu2_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu2_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu2_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu2_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu2_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU2_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu2_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU2_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU2_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU2_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu2_cfg_length */
/* => FMMU 2 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu2_cfg_length    0x00000024U
#define Adr_NX5_fmmusm_fmmu2_cfg_length 0x018E5424U
#define Adr_NX5_fmmu2_cfg_length        0x018E5424U
#define DFLT_VAL_NX5_fmmu2_cfg_length   0x07000000U

#define MSK_NX5_fmmu2_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu2_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu2_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu2_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu2_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu2_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu2_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu2_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu2_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu2_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu2_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu2_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu2_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu2_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu2_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU2_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu2_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu2_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu2_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu2_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu2_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu2_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU2_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU2_CFG_LENGTH_BIT_T bf;
} NX5_FMMU2_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu2_cfg_phys_startaddr */
/* => FMMU 2 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu2_cfg_phys_startaddr    0x00000028U
#define Adr_NX5_fmmusm_fmmu2_cfg_phys_startaddr 0x018E5428U
#define Adr_NX5_fmmu2_cfg_phys_startaddr        0x018E5428U
#define DFLT_VAL_NX5_fmmu2_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu2_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu2_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu2_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu2_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu2_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu2_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu2_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu2_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu2_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu2_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu2_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu2_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu2_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu2_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu2_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu2_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu2_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu2_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu2_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU2_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu2_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu2_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu2_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu2_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu2_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu2_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu2_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU2_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU2_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU2_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu2_cfg_enable */
/* => FMMU 2 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu2_cfg_enable    0x0000002CU
#define Adr_NX5_fmmusm_fmmu2_cfg_enable 0x018E542CU
#define Adr_NX5_fmmu2_cfg_enable        0x018E542CU
#define DFLT_VAL_NX5_fmmu2_cfg_enable   0x00000000U

#define MSK_NX5_fmmu2_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu2_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu2_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu2_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu2_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU2_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu2_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu2_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU2_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU2_CFG_ENABLE_BIT_T bf;
} NX5_FMMU2_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu3_cfg_log_startaddr */
/* => FMMU 3 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu3_cfg_log_startaddr    0x00000030U
#define Adr_NX5_fmmusm_fmmu3_cfg_log_startaddr 0x018E5430U
#define Adr_NX5_fmmu3_cfg_log_startaddr        0x018E5430U
#define DFLT_VAL_NX5_fmmu3_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu3_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu3_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu3_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu3_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU3_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu3_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU3_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU3_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU3_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu3_cfg_length */
/* => FMMU 3 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu3_cfg_length    0x00000034U
#define Adr_NX5_fmmusm_fmmu3_cfg_length 0x018E5434U
#define Adr_NX5_fmmu3_cfg_length        0x018E5434U
#define DFLT_VAL_NX5_fmmu3_cfg_length   0x07000000U

#define MSK_NX5_fmmu3_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu3_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu3_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu3_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu3_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu3_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu3_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu3_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu3_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu3_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu3_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu3_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu3_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu3_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu3_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU3_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu3_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu3_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu3_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu3_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu3_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu3_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU3_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU3_CFG_LENGTH_BIT_T bf;
} NX5_FMMU3_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu3_cfg_phys_startaddr */
/* => FMMU 3 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu3_cfg_phys_startaddr    0x00000038U
#define Adr_NX5_fmmusm_fmmu3_cfg_phys_startaddr 0x018E5438U
#define Adr_NX5_fmmu3_cfg_phys_startaddr        0x018E5438U
#define DFLT_VAL_NX5_fmmu3_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu3_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu3_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu3_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu3_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu3_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu3_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu3_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu3_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu3_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu3_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu3_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu3_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu3_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu3_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu3_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu3_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu3_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu3_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu3_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU3_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu3_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu3_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu3_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu3_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu3_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu3_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu3_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU3_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU3_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU3_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu3_cfg_enable */
/* => FMMU 3 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu3_cfg_enable    0x0000003CU
#define Adr_NX5_fmmusm_fmmu3_cfg_enable 0x018E543CU
#define Adr_NX5_fmmu3_cfg_enable        0x018E543CU
#define DFLT_VAL_NX5_fmmu3_cfg_enable   0x00000000U

#define MSK_NX5_fmmu3_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu3_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu3_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu3_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu3_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU3_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu3_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu3_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU3_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU3_CFG_ENABLE_BIT_T bf;
} NX5_FMMU3_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu4_cfg_log_startaddr */
/* => FMMU 4 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu4_cfg_log_startaddr    0x00000040U
#define Adr_NX5_fmmusm_fmmu4_cfg_log_startaddr 0x018E5440U
#define Adr_NX5_fmmu4_cfg_log_startaddr        0x018E5440U
#define DFLT_VAL_NX5_fmmu4_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu4_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu4_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu4_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu4_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU4_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu4_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU4_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU4_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU4_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu4_cfg_length */
/* => FMMU 4 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu4_cfg_length    0x00000044U
#define Adr_NX5_fmmusm_fmmu4_cfg_length 0x018E5444U
#define Adr_NX5_fmmu4_cfg_length        0x018E5444U
#define DFLT_VAL_NX5_fmmu4_cfg_length   0x07000000U

#define MSK_NX5_fmmu4_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu4_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu4_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu4_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu4_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu4_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu4_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu4_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu4_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu4_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu4_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu4_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu4_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu4_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu4_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU4_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu4_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu4_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu4_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu4_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu4_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu4_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU4_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU4_CFG_LENGTH_BIT_T bf;
} NX5_FMMU4_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu4_cfg_phys_startaddr */
/* => FMMU 4 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu4_cfg_phys_startaddr    0x00000048U
#define Adr_NX5_fmmusm_fmmu4_cfg_phys_startaddr 0x018E5448U
#define Adr_NX5_fmmu4_cfg_phys_startaddr        0x018E5448U
#define DFLT_VAL_NX5_fmmu4_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu4_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu4_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu4_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu4_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu4_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu4_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu4_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu4_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu4_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu4_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu4_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu4_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu4_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu4_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu4_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu4_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu4_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu4_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu4_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU4_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu4_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu4_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu4_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu4_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu4_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu4_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu4_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU4_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU4_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU4_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu4_cfg_enable */
/* => FMMU 4 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu4_cfg_enable    0x0000004CU
#define Adr_NX5_fmmusm_fmmu4_cfg_enable 0x018E544CU
#define Adr_NX5_fmmu4_cfg_enable        0x018E544CU
#define DFLT_VAL_NX5_fmmu4_cfg_enable   0x00000000U

#define MSK_NX5_fmmu4_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu4_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu4_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu4_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu4_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU4_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu4_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu4_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU4_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU4_CFG_ENABLE_BIT_T bf;
} NX5_FMMU4_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu5_cfg_log_startaddr */
/* => FMMU 5 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu5_cfg_log_startaddr    0x00000050U
#define Adr_NX5_fmmusm_fmmu5_cfg_log_startaddr 0x018E5450U
#define Adr_NX5_fmmu5_cfg_log_startaddr        0x018E5450U
#define DFLT_VAL_NX5_fmmu5_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu5_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu5_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu5_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu5_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU5_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu5_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU5_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU5_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU5_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu5_cfg_length */
/* => FMMU 5 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu5_cfg_length    0x00000054U
#define Adr_NX5_fmmusm_fmmu5_cfg_length 0x018E5454U
#define Adr_NX5_fmmu5_cfg_length        0x018E5454U
#define DFLT_VAL_NX5_fmmu5_cfg_length   0x07000000U

#define MSK_NX5_fmmu5_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu5_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu5_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu5_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu5_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu5_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu5_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu5_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu5_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu5_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu5_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu5_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu5_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu5_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu5_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU5_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu5_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu5_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu5_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu5_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu5_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu5_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU5_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU5_CFG_LENGTH_BIT_T bf;
} NX5_FMMU5_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu5_cfg_phys_startaddr */
/* => FMMU 5 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu5_cfg_phys_startaddr    0x00000058U
#define Adr_NX5_fmmusm_fmmu5_cfg_phys_startaddr 0x018E5458U
#define Adr_NX5_fmmu5_cfg_phys_startaddr        0x018E5458U
#define DFLT_VAL_NX5_fmmu5_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu5_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu5_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu5_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu5_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu5_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu5_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu5_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu5_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu5_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu5_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu5_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu5_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu5_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu5_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu5_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu5_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu5_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu5_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu5_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU5_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu5_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu5_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu5_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu5_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu5_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu5_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu5_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU5_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU5_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU5_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu5_cfg_enable */
/* => FMMU 5 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu5_cfg_enable    0x0000005CU
#define Adr_NX5_fmmusm_fmmu5_cfg_enable 0x018E545CU
#define Adr_NX5_fmmu5_cfg_enable        0x018E545CU
#define DFLT_VAL_NX5_fmmu5_cfg_enable   0x00000000U

#define MSK_NX5_fmmu5_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu5_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu5_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu5_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu5_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU5_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu5_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu5_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU5_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU5_CFG_ENABLE_BIT_T bf;
} NX5_FMMU5_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu6_cfg_log_startaddr */
/* => FMMU 6 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu6_cfg_log_startaddr    0x00000060U
#define Adr_NX5_fmmusm_fmmu6_cfg_log_startaddr 0x018E5460U
#define Adr_NX5_fmmu6_cfg_log_startaddr        0x018E5460U
#define DFLT_VAL_NX5_fmmu6_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu6_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu6_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu6_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu6_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU6_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu6_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU6_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU6_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU6_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu6_cfg_length */
/* => FMMU 6 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu6_cfg_length    0x00000064U
#define Adr_NX5_fmmusm_fmmu6_cfg_length 0x018E5464U
#define Adr_NX5_fmmu6_cfg_length        0x018E5464U
#define DFLT_VAL_NX5_fmmu6_cfg_length   0x07000000U

#define MSK_NX5_fmmu6_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu6_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu6_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu6_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu6_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu6_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu6_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu6_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu6_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu6_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu6_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu6_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu6_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu6_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu6_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU6_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu6_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu6_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu6_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu6_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu6_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu6_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU6_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU6_CFG_LENGTH_BIT_T bf;
} NX5_FMMU6_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu6_cfg_phys_startaddr */
/* => FMMU 6 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu6_cfg_phys_startaddr    0x00000068U
#define Adr_NX5_fmmusm_fmmu6_cfg_phys_startaddr 0x018E5468U
#define Adr_NX5_fmmu6_cfg_phys_startaddr        0x018E5468U
#define DFLT_VAL_NX5_fmmu6_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu6_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu6_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu6_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu6_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu6_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu6_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu6_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu6_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu6_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu6_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu6_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu6_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu6_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu6_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu6_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu6_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu6_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu6_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu6_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU6_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu6_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu6_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu6_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu6_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu6_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu6_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu6_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU6_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU6_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU6_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu6_cfg_enable */
/* => FMMU 6 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu6_cfg_enable    0x0000006CU
#define Adr_NX5_fmmusm_fmmu6_cfg_enable 0x018E546CU
#define Adr_NX5_fmmu6_cfg_enable        0x018E546CU
#define DFLT_VAL_NX5_fmmu6_cfg_enable   0x00000000U

#define MSK_NX5_fmmu6_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu6_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu6_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu6_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu6_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU6_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu6_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu6_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU6_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU6_CFG_ENABLE_BIT_T bf;
} NX5_FMMU6_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register fmmu7_cfg_log_startaddr */
/* => FMMU 7 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu7_cfg_log_startaddr    0x00000070U
#define Adr_NX5_fmmusm_fmmu7_cfg_log_startaddr 0x018E5470U
#define Adr_NX5_fmmu7_cfg_log_startaddr        0x018E5470U
#define DFLT_VAL_NX5_fmmu7_cfg_log_startaddr   0x00000000U

#define MSK_NX5_fmmu7_cfg_log_startaddr_log_startaddr      0xffffffffU
#define SRT_NX5_fmmu7_cfg_log_startaddr_log_startaddr      0
#define DFLT_VAL_NX5_fmmu7_cfg_log_startaddr_log_startaddr 0x00000000U

enum {
	BFW_NX5_fmmu7_cfg_log_startaddr_log_startaddr = 32  /* [31:0] */
};

typedef struct NX5_FMMU7_CFG_LOG_STARTADDR_BIT_Ttag {
	unsigned int log_startaddr : BFW_NX5_fmmu7_cfg_log_startaddr_log_startaddr; /* Logical start address of FMMU-area */
} NX5_FMMU7_CFG_LOG_STARTADDR_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_FMMU7_CFG_LOG_STARTADDR_BIT_T bf;
} NX5_FMMU7_CFG_LOG_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu7_cfg_length */
/* => FMMU 7 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu7_cfg_length    0x00000074U
#define Adr_NX5_fmmusm_fmmu7_cfg_length 0x018E5474U
#define Adr_NX5_fmmu7_cfg_length        0x018E5474U
#define DFLT_VAL_NX5_fmmu7_cfg_length   0x07000000U

#define MSK_NX5_fmmu7_cfg_length_length             0x00001fffU
#define SRT_NX5_fmmu7_cfg_length_length             0
#define DFLT_VAL_NX5_fmmu7_cfg_length_length        0x00000000U
#define MSK_NX5_fmmu7_cfg_length_log_start_bit      0x00070000U
#define SRT_NX5_fmmu7_cfg_length_log_start_bit      16
#define DFLT_VAL_NX5_fmmu7_cfg_length_log_start_bit 0x00000000U
#define MSK_NX5_fmmu7_cfg_length_log_stop_bit       0x07000000U
#define SRT_NX5_fmmu7_cfg_length_log_stop_bit       24
#define DFLT_VAL_NX5_fmmu7_cfg_length_log_stop_bit  0x07000000U

enum {
	BFW_NX5_fmmu7_cfg_length_length        = 13, /* [12:0] */
	BFW_NX5_fmmu7_cfg_length_reserved1     = 3,  /* [15:13] */
	BFW_NX5_fmmu7_cfg_length_log_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu7_cfg_length_reserved2     = 5,  /* [23:19] */
	BFW_NX5_fmmu7_cfg_length_log_stop_bit  = 3,  /* [26:24] */
	BFW_NX5_fmmu7_cfg_length_reserved3     = 5   /* [31:27] */
};

typedef struct NX5_FMMU7_CFG_LENGTH_BIT_Ttag {
	unsigned int length        : BFW_NX5_fmmu7_cfg_length_length;        /* Length of FMMU-area in bytes                    */
	unsigned int reserved1     : BFW_NX5_fmmu7_cfg_length_reserved1;     /* reserved                                        */
	unsigned int log_start_bit : BFW_NX5_fmmu7_cfg_length_log_start_bit; /* Logical start bit, used for bitwise addressing. */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved2     : BFW_NX5_fmmu7_cfg_length_reserved2;     /* reserved                                        */
	unsigned int log_stop_bit  : BFW_NX5_fmmu7_cfg_length_log_stop_bit;  /* Logical stop bit, used for bitwise addressing.  */
	                                                                     /* Restricted at netX for use inside one byte.     */
	unsigned int reserved3     : BFW_NX5_fmmu7_cfg_length_reserved3;     /* reserved                                        */
} NX5_FMMU7_CFG_LENGTH_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU7_CFG_LENGTH_BIT_T bf;
} NX5_FMMU7_CFG_LENGTH_T;

/* --------------------------------------------------------------------- */
/* Register fmmu7_cfg_phys_startaddr */
/* => FMMU 7 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu7_cfg_phys_startaddr    0x00000078U
#define Adr_NX5_fmmusm_fmmu7_cfg_phys_startaddr 0x018E5478U
#define Adr_NX5_fmmu7_cfg_phys_startaddr        0x018E5478U
#define DFLT_VAL_NX5_fmmu7_cfg_phys_startaddr   0x00000000U

#define MSK_NX5_fmmu7_cfg_phys_startaddr_phys_startaddr      0x00003fffU
#define SRT_NX5_fmmu7_cfg_phys_startaddr_phys_startaddr      0
#define DFLT_VAL_NX5_fmmu7_cfg_phys_startaddr_phys_startaddr 0x00000000U
#define MSK_NX5_fmmu7_cfg_phys_startaddr_phys_start_bit      0x00070000U
#define SRT_NX5_fmmu7_cfg_phys_startaddr_phys_start_bit      16
#define DFLT_VAL_NX5_fmmu7_cfg_phys_startaddr_phys_start_bit 0x00000000U
#define MSK_NX5_fmmu7_cfg_phys_startaddr_proc_rd_enable      0x01000000U
#define SRT_NX5_fmmu7_cfg_phys_startaddr_proc_rd_enable      24
#define DFLT_VAL_NX5_fmmu7_cfg_phys_startaddr_proc_rd_enable 0x00000000U
#define MSK_NX5_fmmu7_cfg_phys_startaddr_proc_wr_enable      0x02000000U
#define SRT_NX5_fmmu7_cfg_phys_startaddr_proc_wr_enable      25
#define DFLT_VAL_NX5_fmmu7_cfg_phys_startaddr_proc_wr_enable 0x00000000U

enum {
	BFW_NX5_fmmu7_cfg_phys_startaddr_phys_startaddr = 14, /* [13:0] */
	BFW_NX5_fmmu7_cfg_phys_startaddr_reserved1      = 2,  /* [15:14] */
	BFW_NX5_fmmu7_cfg_phys_startaddr_phys_start_bit = 3,  /* [18:16] */
	BFW_NX5_fmmu7_cfg_phys_startaddr_reserved2      = 5,  /* [23:19] */
	BFW_NX5_fmmu7_cfg_phys_startaddr_proc_rd_enable = 1,  /* [24] */
	BFW_NX5_fmmu7_cfg_phys_startaddr_proc_wr_enable = 1,  /* [25] */
	BFW_NX5_fmmu7_cfg_phys_startaddr_reserved3      = 6   /* [31:26] */
};

typedef struct NX5_FMMU7_CFG_PHYS_STARTADDR_BIT_Ttag {
	unsigned int phys_startaddr : BFW_NX5_fmmu7_cfg_phys_startaddr_phys_startaddr; /* Physical byte address inside 8kByte xPEC data memory    */
	unsigned int reserved1      : BFW_NX5_fmmu7_cfg_phys_startaddr_reserved1;      /* reserved                                                */
	unsigned int phys_start_bit : BFW_NX5_fmmu7_cfg_phys_startaddr_phys_start_bit; /* Physical start bit, used for bitwise addressing.        */
	                                                                               /* Restricted at netX for use inside one byte.             */
	unsigned int reserved2      : BFW_NX5_fmmu7_cfg_phys_startaddr_reserved2;      /* reserved                                                */
	unsigned int proc_rd_enable : BFW_NX5_fmmu7_cfg_phys_startaddr_proc_rd_enable; /* Enable FMMU-mapping for read access of process channel. */
	unsigned int proc_wr_enable : BFW_NX5_fmmu7_cfg_phys_startaddr_proc_wr_enable; /* Enable FMMU-mapping for write access of process channel */
	unsigned int reserved3      : BFW_NX5_fmmu7_cfg_phys_startaddr_reserved3;      /* reserved                                                */
} NX5_FMMU7_CFG_PHYS_STARTADDR_BIT_T;

typedef union {
	unsigned int                       val;
	NX5_FMMU7_CFG_PHYS_STARTADDR_BIT_T bf;
} NX5_FMMU7_CFG_PHYS_STARTADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmu7_cfg_enable */
/* => FMMU 7 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu7_cfg_enable    0x0000007CU
#define Adr_NX5_fmmusm_fmmu7_cfg_enable 0x018E547CU
#define Adr_NX5_fmmu7_cfg_enable        0x018E547CU
#define DFLT_VAL_NX5_fmmu7_cfg_enable   0x00000000U

#define MSK_NX5_fmmu7_cfg_enable_proc_enable      0x00000001U
#define SRT_NX5_fmmu7_cfg_enable_proc_enable      0
#define DFLT_VAL_NX5_fmmu7_cfg_enable_proc_enable 0x00000000U

enum {
	BFW_NX5_fmmu7_cfg_enable_proc_enable = 1,  /* [0] */
	BFW_NX5_fmmu7_cfg_enable_reserved1   = 31  /* [31:1] */
};

typedef struct NX5_FMMU7_CFG_ENABLE_BIT_Ttag {
	unsigned int proc_enable : BFW_NX5_fmmu7_cfg_enable_proc_enable; /* FMMU enable for process channel (1:active, 0: only forward) */
	unsigned int reserved1   : BFW_NX5_fmmu7_cfg_enable_reserved1;   /* reserved                                                    */
} NX5_FMMU7_CFG_ENABLE_BIT_T;

typedef union {
	unsigned int               val;
	NX5_FMMU7_CFG_ENABLE_BIT_T bf;
} NX5_FMMU7_CFG_ENABLE_T;

/* --------------------------------------------------------------------- */
/* Register sm0_cfg_adr_len */
/* => SM 0 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm0_cfg_adr_len    0x00000080U
#define Adr_NX5_fmmusm_sm0_cfg_adr_len 0x018E5480U
#define Adr_NX5_sm0_cfg_adr_len        0x018E5480U
#define DFLT_VAL_NX5_sm0_cfg_adr_len   0x00000000U

#define MSK_NX5_sm0_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm0_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm0_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm0_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm0_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm0_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm0_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm0_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM0_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm0_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm0_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM0_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM0_CFG_ADR_LEN_BIT_T bf;
} NX5_SM0_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm0_cfg_mode */
/* => SM 0 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm0_cfg_mode    0x00000084U
#define Adr_NX5_fmmusm_sm0_cfg_mode 0x018E5484U
#define Adr_NX5_sm0_cfg_mode        0x018E5484U
#define DFLT_VAL_NX5_sm0_cfg_mode   0x00000000U

#define MSK_NX5_sm0_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm0_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm0_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm0_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm0_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm0_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm0_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm0_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm0_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm0_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm0_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm0_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm0_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm0_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm0_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm0_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm0_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm0_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm0_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm0_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM0_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm0_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm0_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm0_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm0_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm0_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm0_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm0_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm0_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM0_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM0_CFG_MODE_BIT_T bf;
} NX5_SM0_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm1_cfg_adr_len */
/* => SM 1 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm1_cfg_adr_len    0x00000088U
#define Adr_NX5_fmmusm_sm1_cfg_adr_len 0x018E5488U
#define Adr_NX5_sm1_cfg_adr_len        0x018E5488U
#define DFLT_VAL_NX5_sm1_cfg_adr_len   0x00000000U

#define MSK_NX5_sm1_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm1_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm1_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm1_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm1_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm1_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm1_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm1_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM1_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm1_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm1_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM1_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM1_CFG_ADR_LEN_BIT_T bf;
} NX5_SM1_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm1_cfg_mode */
/* => SM 1 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm1_cfg_mode    0x0000008CU
#define Adr_NX5_fmmusm_sm1_cfg_mode 0x018E548CU
#define Adr_NX5_sm1_cfg_mode        0x018E548CU
#define DFLT_VAL_NX5_sm1_cfg_mode   0x00000000U

#define MSK_NX5_sm1_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm1_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm1_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm1_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm1_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm1_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm1_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm1_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm1_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm1_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm1_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm1_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm1_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm1_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm1_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm1_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm1_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm1_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm1_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm1_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM1_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm1_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm1_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm1_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm1_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm1_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm1_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm1_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm1_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM1_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM1_CFG_MODE_BIT_T bf;
} NX5_SM1_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm2_cfg_adr_len */
/* => SM 2 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm2_cfg_adr_len    0x00000090U
#define Adr_NX5_fmmusm_sm2_cfg_adr_len 0x018E5490U
#define Adr_NX5_sm2_cfg_adr_len        0x018E5490U
#define DFLT_VAL_NX5_sm2_cfg_adr_len   0x00000000U

#define MSK_NX5_sm2_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm2_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm2_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm2_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm2_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm2_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm2_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm2_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM2_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm2_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm2_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM2_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM2_CFG_ADR_LEN_BIT_T bf;
} NX5_SM2_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm2_cfg_mode */
/* => SM 2 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm2_cfg_mode    0x00000094U
#define Adr_NX5_fmmusm_sm2_cfg_mode 0x018E5494U
#define Adr_NX5_sm2_cfg_mode        0x018E5494U
#define DFLT_VAL_NX5_sm2_cfg_mode   0x00000000U

#define MSK_NX5_sm2_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm2_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm2_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm2_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm2_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm2_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm2_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm2_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm2_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm2_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm2_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm2_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm2_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm2_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm2_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm2_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm2_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm2_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm2_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm2_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM2_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm2_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm2_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm2_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm2_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm2_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm2_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm2_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm2_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM2_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM2_CFG_MODE_BIT_T bf;
} NX5_SM2_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm3_cfg_adr_len */
/* => SM 3 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm3_cfg_adr_len    0x00000098U
#define Adr_NX5_fmmusm_sm3_cfg_adr_len 0x018E5498U
#define Adr_NX5_sm3_cfg_adr_len        0x018E5498U
#define DFLT_VAL_NX5_sm3_cfg_adr_len   0x00000000U

#define MSK_NX5_sm3_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm3_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm3_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm3_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm3_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm3_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm3_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm3_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM3_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm3_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm3_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM3_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM3_CFG_ADR_LEN_BIT_T bf;
} NX5_SM3_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm3_cfg_mode */
/* => SM 3 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm3_cfg_mode    0x0000009CU
#define Adr_NX5_fmmusm_sm3_cfg_mode 0x018E549CU
#define Adr_NX5_sm3_cfg_mode        0x018E549CU
#define DFLT_VAL_NX5_sm3_cfg_mode   0x00000000U

#define MSK_NX5_sm3_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm3_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm3_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm3_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm3_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm3_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm3_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm3_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm3_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm3_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm3_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm3_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm3_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm3_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm3_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm3_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm3_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm3_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm3_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm3_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM3_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm3_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm3_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm3_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm3_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm3_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm3_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm3_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm3_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM3_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM3_CFG_MODE_BIT_T bf;
} NX5_SM3_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm4_cfg_adr_len */
/* => SM 4 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm4_cfg_adr_len    0x000000A0U
#define Adr_NX5_fmmusm_sm4_cfg_adr_len 0x018E54A0U
#define Adr_NX5_sm4_cfg_adr_len        0x018E54A0U
#define DFLT_VAL_NX5_sm4_cfg_adr_len   0x00000000U

#define MSK_NX5_sm4_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm4_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm4_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm4_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm4_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm4_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm4_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm4_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM4_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm4_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm4_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM4_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM4_CFG_ADR_LEN_BIT_T bf;
} NX5_SM4_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm4_cfg_mode */
/* => SM 4 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm4_cfg_mode    0x000000A4U
#define Adr_NX5_fmmusm_sm4_cfg_mode 0x018E54A4U
#define Adr_NX5_sm4_cfg_mode        0x018E54A4U
#define DFLT_VAL_NX5_sm4_cfg_mode   0x00000000U

#define MSK_NX5_sm4_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm4_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm4_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm4_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm4_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm4_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm4_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm4_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm4_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm4_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm4_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm4_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm4_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm4_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm4_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm4_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm4_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm4_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm4_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm4_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM4_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm4_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm4_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm4_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm4_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm4_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm4_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm4_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm4_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM4_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM4_CFG_MODE_BIT_T bf;
} NX5_SM4_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm5_cfg_adr_len */
/* => SM 5 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm5_cfg_adr_len    0x000000A8U
#define Adr_NX5_fmmusm_sm5_cfg_adr_len 0x018E54A8U
#define Adr_NX5_sm5_cfg_adr_len        0x018E54A8U
#define DFLT_VAL_NX5_sm5_cfg_adr_len   0x00000000U

#define MSK_NX5_sm5_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm5_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm5_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm5_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm5_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm5_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm5_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm5_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM5_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm5_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm5_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM5_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM5_CFG_ADR_LEN_BIT_T bf;
} NX5_SM5_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm5_cfg_mode */
/* => SM 5 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm5_cfg_mode    0x000000ACU
#define Adr_NX5_fmmusm_sm5_cfg_mode 0x018E54ACU
#define Adr_NX5_sm5_cfg_mode        0x018E54ACU
#define DFLT_VAL_NX5_sm5_cfg_mode   0x00000000U

#define MSK_NX5_sm5_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm5_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm5_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm5_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm5_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm5_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm5_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm5_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm5_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm5_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm5_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm5_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm5_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm5_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm5_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm5_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm5_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm5_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm5_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm5_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM5_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm5_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm5_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm5_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm5_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm5_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm5_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm5_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm5_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM5_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM5_CFG_MODE_BIT_T bf;
} NX5_SM5_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm6_cfg_adr_len */
/* => SM 6 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm6_cfg_adr_len    0x000000B0U
#define Adr_NX5_fmmusm_sm6_cfg_adr_len 0x018E54B0U
#define Adr_NX5_sm6_cfg_adr_len        0x018E54B0U
#define DFLT_VAL_NX5_sm6_cfg_adr_len   0x00000000U

#define MSK_NX5_sm6_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm6_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm6_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm6_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm6_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm6_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm6_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm6_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM6_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm6_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm6_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM6_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM6_CFG_ADR_LEN_BIT_T bf;
} NX5_SM6_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm6_cfg_mode */
/* => SM 6 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm6_cfg_mode    0x000000B4U
#define Adr_NX5_fmmusm_sm6_cfg_mode 0x018E54B4U
#define Adr_NX5_sm6_cfg_mode        0x018E54B4U
#define DFLT_VAL_NX5_sm6_cfg_mode   0x00000000U

#define MSK_NX5_sm6_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm6_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm6_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm6_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm6_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm6_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm6_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm6_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm6_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm6_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm6_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm6_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm6_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm6_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm6_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm6_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm6_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm6_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm6_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm6_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM6_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm6_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm6_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm6_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm6_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm6_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm6_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm6_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm6_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM6_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM6_CFG_MODE_BIT_T bf;
} NX5_SM6_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register sm7_cfg_adr_len */
/* => SM 7 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm7_cfg_adr_len    0x000000B8U
#define Adr_NX5_fmmusm_sm7_cfg_adr_len 0x018E54B8U
#define Adr_NX5_sm7_cfg_adr_len        0x018E54B8U
#define DFLT_VAL_NX5_sm7_cfg_adr_len   0x00000000U

#define MSK_NX5_sm7_cfg_adr_len_startaddr      0x0000ffffU
#define SRT_NX5_sm7_cfg_adr_len_startaddr      0
#define DFLT_VAL_NX5_sm7_cfg_adr_len_startaddr 0x00000000U
#define MSK_NX5_sm7_cfg_adr_len_length         0xffff0000U
#define SRT_NX5_sm7_cfg_adr_len_length         16
#define DFLT_VAL_NX5_sm7_cfg_adr_len_length    0x00000000U

enum {
	BFW_NX5_sm7_cfg_adr_len_startaddr = 16, /* [15:0] */
	BFW_NX5_sm7_cfg_adr_len_length    = 16  /* [31:16] */
};

typedef struct NX5_SM7_CFG_ADR_LEN_BIT_Ttag {
	unsigned int startaddr : BFW_NX5_sm7_cfg_adr_len_startaddr; /* Physical start address of SM-area  */
	unsigned int length    : BFW_NX5_sm7_cfg_adr_len_length;    /* Length of SM-area in bytes,        */
	                                                            /* tripled in case of 3-buffer method */
} NX5_SM7_CFG_ADR_LEN_BIT_T;

typedef union {
	unsigned int              val;
	NX5_SM7_CFG_ADR_LEN_BIT_T bf;
} NX5_SM7_CFG_ADR_LEN_T;

/* --------------------------------------------------------------------- */
/* Register sm7_cfg_mode */
/* => SM 7 config register */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm7_cfg_mode    0x000000BCU
#define Adr_NX5_fmmusm_sm7_cfg_mode 0x018E54BCU
#define Adr_NX5_sm7_cfg_mode        0x018E54BCU
#define DFLT_VAL_NX5_sm7_cfg_mode   0x00000000U

#define MSK_NX5_sm7_cfg_mode_buf_method       0x00000002U
#define SRT_NX5_sm7_cfg_mode_buf_method       1
#define DFLT_VAL_NX5_sm7_cfg_mode_buf_method  0x00000000U
#define MSK_NX5_sm7_cfg_mode_write_read       0x00000004U
#define SRT_NX5_sm7_cfg_mode_write_read       2
#define DFLT_VAL_NX5_sm7_cfg_mode_write_read  0x00000000U
#define MSK_NX5_sm7_cfg_mode_proc_enable      0x00010000U
#define SRT_NX5_sm7_cfg_mode_proc_enable      16
#define DFLT_VAL_NX5_sm7_cfg_mode_proc_enable 0x00000000U
#define MSK_NX5_sm7_cfg_mode_dis_by_arm       0x01000000U
#define SRT_NX5_sm7_cfg_mode_dis_by_arm       24
#define DFLT_VAL_NX5_sm7_cfg_mode_dis_by_arm  0x00000000U

enum {
	BFW_NX5_sm7_cfg_mode_reserved1   = 1,  /* [0] */
	BFW_NX5_sm7_cfg_mode_buf_method  = 1,  /* [1] */
	BFW_NX5_sm7_cfg_mode_write_read  = 1,  /* [2] */
	BFW_NX5_sm7_cfg_mode_reserved2   = 13, /* [15:3] */
	BFW_NX5_sm7_cfg_mode_proc_enable = 1,  /* [16] */
	BFW_NX5_sm7_cfg_mode_reserved3   = 7,  /* [23:17] */
	BFW_NX5_sm7_cfg_mode_dis_by_arm  = 1,  /* [24] */
	BFW_NX5_sm7_cfg_mode_reserved4   = 7   /* [31:25] */
};

typedef struct NX5_SM7_CFG_MODE_BIT_Ttag {
	unsigned int reserved1   : BFW_NX5_sm7_cfg_mode_reserved1;   /* reserved                                        */
	unsigned int buf_method  : BFW_NX5_sm7_cfg_mode_buf_method;  /* Buffer method:                                  */
	                                                             /* 0: 3 buffer method                              */
	unsigned int write_read  : BFW_NX5_sm7_cfg_mode_write_read;  /* Write/Read:                                     */
	                                                             /* 0: read:  EtherCAT read,  ARM write             */
	unsigned int reserved2   : BFW_NX5_sm7_cfg_mode_reserved2;   /* reserved                                        */
	unsigned int proc_enable : BFW_NX5_sm7_cfg_mode_proc_enable; /* Enable for process channel                      */
	                                                             /* 0: Sync-manager is disabled for process channel */
	unsigned int reserved3   : BFW_NX5_sm7_cfg_mode_reserved3;   /* reserved                                        */
	unsigned int dis_by_arm  : BFW_NX5_sm7_cfg_mode_dis_by_arm;  /* Sync-manager locked by ARM                      */
	                                                             /* 0: Sync-manager is operable                     */
	unsigned int reserved4   : BFW_NX5_sm7_cfg_mode_reserved4;   /* reserved                                        */
} NX5_SM7_CFG_MODE_BIT_T;

typedef union {
	unsigned int           val;
	NX5_SM7_CFG_MODE_BIT_T bf;
} NX5_SM7_CFG_MODE_T;

/* --------------------------------------------------------------------- */
/* Register phys_addr_offset */
/* => Physical offset of phys. ECAT address and xPEC data ram address */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_phys_addr_offset    0x000000D0U
#define Adr_NX5_fmmusm_phys_addr_offset 0x018E54D0U
#define Adr_NX5_phys_addr_offset        0x018E54D0U
#define DFLT_VAL_NX5_phys_addr_offset   0x00000000U

#define MSK_NX5_phys_addr_offset_phys_addr_offset                    0x0000ffffU
#define SRT_NX5_phys_addr_offset_phys_addr_offset                    0
#define DFLT_VAL_NX5_phys_addr_offset_phys_addr_offset               0x00000000U
#define MSK_NX5_phys_addr_offset_phys_addr_offset_register_area      0xffff0000U
#define SRT_NX5_phys_addr_offset_phys_addr_offset_register_area      16
#define DFLT_VAL_NX5_phys_addr_offset_phys_addr_offset_register_area 0x00000000U

enum {
	BFW_NX5_phys_addr_offset_phys_addr_offset               = 16, /* [15:0] */
	BFW_NX5_phys_addr_offset_phys_addr_offset_register_area = 16  /* [31:16] */
};

typedef struct NX5_PHYS_ADDR_OFFSET_BIT_Ttag {
	unsigned int phys_addr_offset               : BFW_NX5_phys_addr_offset_phys_addr_offset;               /* Physical offset of phys. ECAT address and xPEC data ram address for phys_ECAT_addr>=0x1000 */
	                                                                                                       /* sm_write_addr_out = physical write address to access + phys_addr_offset                    */
	unsigned int phys_addr_offset_register_area : BFW_NX5_phys_addr_offset_phys_addr_offset_register_area; /* Physical offset of phys. ECAT address and xPEC data ram address for phys_ECAT_addr<0x1000  */
	                                                                                                       /* sm_write_addr_out = physical write address to access + phys_addr_offset_register_area      */
} NX5_PHYS_ADDR_OFFSET_BIT_T;

typedef union {
	unsigned int               val;
	NX5_PHYS_ADDR_OFFSET_BIT_T bf;
} NX5_PHYS_ADDR_OFFSET_T;

/* --------------------------------------------------------------------- */
/* Register phys_last_addr */
/* =>  */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_phys_last_addr    0x000000D4U
#define Adr_NX5_fmmusm_phys_last_addr 0x018E54D4U
#define Adr_NX5_phys_last_addr        0x018E54D4U
#define DFLT_VAL_NX5_phys_last_addr   0x00001fffU

#define MSK_NX5_phys_last_addr_phys_last_addr      0x0000ffffU
#define SRT_NX5_phys_last_addr_phys_last_addr      0
#define DFLT_VAL_NX5_phys_last_addr_phys_last_addr 0x00001fffU

enum {
	BFW_NX5_phys_last_addr_phys_last_addr = 16, /* [15:0] */
	BFW_NX5_phys_last_addr_reserved1      = 16  /* [31:16] */
};

typedef struct NX5_PHYS_LAST_ADDR_BIT_Ttag {
	unsigned int phys_last_addr : BFW_NX5_phys_last_addr_phys_last_addr; /* last accessible ecat data memory address within xPEC memory, (0x1000-phys_offset_data_ram_start+ecat data size) */
	                                                                     /* IF (sm_read_addr_out  > phys_last_addr) THEN { read to ecat data memory is locked (read_allowed=0)              */
	unsigned int reserved1      : BFW_NX5_phys_last_addr_reserved1;      /* reserved                                                                                                        */
} NX5_PHYS_LAST_ADDR_BIT_T;

typedef union {
	unsigned int             val;
	NX5_PHYS_LAST_ADDR_BIT_T bf;
} NX5_PHYS_LAST_ADDR_T;

/* --------------------------------------------------------------------- */
/* Register fmmusm_xpec_nr */
/* =>  */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmusm_xpec_nr    0x000000D8U
#define Adr_NX5_fmmusm_fmmusm_xpec_nr 0x018E54D8U
#define Adr_NX5_fmmusm_xpec_nr        0x018E54D8U
#define DFLT_VAL_NX5_fmmusm_xpec_nr   0x00000000U

#define MSK_NX5_fmmusm_xpec_nr_xpec_nr      0x00000001U
#define SRT_NX5_fmmusm_xpec_nr_xpec_nr      0
#define DFLT_VAL_NX5_fmmusm_xpec_nr_xpec_nr 0x00000000U

enum {
	BFW_NX5_fmmusm_xpec_nr_xpec_nr   = 1,  /* [0] */
	BFW_NX5_fmmusm_xpec_nr_reserved1 = 31  /* [31:1] */
};

typedef struct NX5_FMMUSM_XPEC_NR_BIT_Ttag {
	unsigned int xpec_nr   : BFW_NX5_fmmusm_xpec_nr_xpec_nr;   /* number of xPEC using FMMUSM (utx_count is read from this xPEC) */
	unsigned int reserved1 : BFW_NX5_fmmusm_xpec_nr_reserved1; /* reserved                                                       */
} NX5_FMMUSM_XPEC_NR_BIT_T;

typedef union {
	unsigned int             val;
	NX5_FMMUSM_XPEC_NR_BIT_T bf;
} NX5_FMMUSM_XPEC_NR_T;

/* --------------------------------------------------------------------- */
/* Register fmmusm_read_addr_in */
/* => Read address from EtherCAT telegram */
/*    Write access by xPEC at adr_xpec_r6 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmusm_read_addr_in    0x00000100U
#define Adr_NX5_fmmusm_fmmusm_read_addr_in 0x018E5500U
#define Adr_NX5_fmmusm_read_addr_in        0x018E5500U
#define DFLT_VAL_NX5_fmmusm_read_addr_in   0x00000000U

#define MSK_NX5_fmmusm_read_addr_in_read_adr      0xffffffffU
#define SRT_NX5_fmmusm_read_addr_in_read_adr      0
#define DFLT_VAL_NX5_fmmusm_read_addr_in_read_adr 0x00000000U

enum {
	BFW_NX5_fmmusm_read_addr_in_read_adr = 32  /* [31:0] */
};

typedef struct NX5_FMMUSM_READ_ADDR_IN_BIT_Ttag {
	unsigned int read_adr : BFW_NX5_fmmusm_read_addr_in_read_adr; /* Read address from EtherCAT telegram */
} NX5_FMMUSM_READ_ADDR_IN_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_FMMUSM_READ_ADDR_IN_BIT_T bf;
} NX5_FMMUSM_READ_ADDR_IN_T;

/* --------------------------------------------------------------------- */
/* Register fmmusm_write_addr_in */
/* => Write address from EtherCAT telegram */
/*    Write access by xPEC at adr_xpec_r7 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmusm_write_addr_in    0x00000104U
#define Adr_NX5_fmmusm_fmmusm_write_addr_in 0x018E5504U
#define Adr_NX5_fmmusm_write_addr_in        0x018E5504U
#define DFLT_VAL_NX5_fmmusm_write_addr_in   0x00000000U

#define MSK_NX5_fmmusm_write_addr_in_write_adr      0xffffffffU
#define SRT_NX5_fmmusm_write_addr_in_write_adr      0
#define DFLT_VAL_NX5_fmmusm_write_addr_in_write_adr 0x00000000U

enum {
	BFW_NX5_fmmusm_write_addr_in_write_adr = 32  /* [31:0] */
};

typedef struct NX5_FMMUSM_WRITE_ADDR_IN_BIT_Ttag {
	unsigned int write_adr : BFW_NX5_fmmusm_write_addr_in_write_adr; /* Write address from EtherCAT telegram */
} NX5_FMMUSM_WRITE_ADDR_IN_BIT_T;

typedef union {
	unsigned int                   val;
	NX5_FMMUSM_WRITE_ADDR_IN_BIT_T bf;
} NX5_FMMUSM_WRITE_ADDR_IN_T;

/* --------------------------------------------------------------------- */
/* Register sm_read_addr_out */
/* => Physical read address in xPEC RAM */
/*    Read access by xPEC at adr_xpec_r6 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_read_addr_out    0x00000108U
#define Adr_NX5_fmmusm_sm_read_addr_out 0x018E5508U
#define Adr_NX5_sm_read_addr_out        0x018E5508U

#define MSK_NX5_sm_read_addr_out_sm_read_adr_out 0x00001fffU
#define SRT_NX5_sm_read_addr_out_sm_read_adr_out 0

enum {
	BFW_NX5_sm_read_addr_out_sm_read_adr_out = 13, /* [12:0] */
	BFW_NX5_sm_read_addr_out_reserved1       = 19  /* [31:13] */
};

typedef struct NX5_SM_READ_ADDR_OUT_BIT_Ttag {
	unsigned int sm_read_adr_out : BFW_NX5_sm_read_addr_out_sm_read_adr_out; /* Physical read address in xPEC RAM */
	                                                                         /* process by FMMU and SM            */
	unsigned int reserved1       : BFW_NX5_sm_read_addr_out_reserved1;       /* reserved                          */
} NX5_SM_READ_ADDR_OUT_BIT_T;

typedef union {
	unsigned int               val;
	NX5_SM_READ_ADDR_OUT_BIT_T bf;
} NX5_SM_READ_ADDR_OUT_T;

/* --------------------------------------------------------------------- */
/* Register sm_write_addr_out */
/* => Physical write address in xPEC RAM */
/*    Read access by xPEC at adr_xpec_r7 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_write_addr_out    0x0000010CU
#define Adr_NX5_fmmusm_sm_write_addr_out 0x018E550CU
#define Adr_NX5_sm_write_addr_out        0x018E550CU

#define MSK_NX5_sm_write_addr_out_sm_write_adr_out 0x00001fffU
#define SRT_NX5_sm_write_addr_out_sm_write_adr_out 0

enum {
	BFW_NX5_sm_write_addr_out_sm_write_adr_out = 13, /* [12:0] */
	BFW_NX5_sm_write_addr_out_reserved1        = 19  /* [31:13] */
};

typedef struct NX5_SM_WRITE_ADDR_OUT_BIT_Ttag {
	unsigned int sm_write_adr_out : BFW_NX5_sm_write_addr_out_sm_write_adr_out; /* Physical write address in xPEC RAM */
	                                                                            /* process by FMMU and SM             */
	unsigned int reserved1        : BFW_NX5_sm_write_addr_out_reserved1;        /* reserved                           */
} NX5_SM_WRITE_ADDR_OUT_BIT_T;

typedef union {
	unsigned int                val;
	NX5_SM_WRITE_ADDR_OUT_BIT_T bf;
} NX5_SM_WRITE_ADDR_OUT_T;

/* --------------------------------------------------------------------- */
/* Register fmmu_read_bit_rol_pos */
/* => Shift and mask value for bitwise read access */
/*    For direct use with combined rol-and command. */
/*    Read access by xPEC at adr_statcfg2 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu_read_bit_rol_pos    0x00000110U
#define Adr_NX5_fmmusm_fmmu_read_bit_rol_pos 0x018E5510U
#define Adr_NX5_fmmu_read_bit_rol_pos        0x018E5510U

#define MSK_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_rol      0x0000001fU
#define SRT_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_rol      0
#define MSK_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_maskmode 0x000000e0U
#define SRT_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_maskmode 5
#define MSK_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_mask     0x0000ff00U
#define SRT_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_mask     8
#define MSK_NX5_fmmu_read_bit_rol_pos_zero                   0xffff0000U
#define SRT_NX5_fmmu_read_bit_rol_pos_zero                   16

enum {
	BFW_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_rol      = 5,  /* [4:0] */
	BFW_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_maskmode = 3,  /* [7:5] */
	BFW_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_mask     = 8,  /* [15:8] */
	BFW_NX5_fmmu_read_bit_rol_pos_zero                   = 16  /* [31:16] */
};

typedef struct NX5_FMMU_READ_BIT_ROL_POS_BIT_Ttag {
	unsigned int fmmu_read_bit_rol      : BFW_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_rol;      /* rotate left value for bitwise read from RAM to bitstream.            */
	                                                                                            /* Rotates byte from RAM to correct position for insertion into stream, */
	unsigned int fmmu_read_bit_maskmode : BFW_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_maskmode; /* always 3'b010: and-mask-mode with upper mask-bits=0                  */
	unsigned int fmmu_read_bit_mask     : BFW_NX5_fmmu_read_bit_rol_pos_fmmu_read_bit_mask;     /* mask for combined rol-and command,                                   */
	                                                                                            /* same as at adr_fmmu_read_bit_mask                                    */
	unsigned int zero                   : BFW_NX5_fmmu_read_bit_rol_pos_zero;                   /* upper mask bits, always zero                                         */
} NX5_FMMU_READ_BIT_ROL_POS_BIT_T;

typedef union {
	unsigned int                    val;
	NX5_FMMU_READ_BIT_ROL_POS_BIT_T bf;
} NX5_FMMU_READ_BIT_ROL_POS_T;

/* --------------------------------------------------------------------- */
/* Register fmmu_read_bit_mask */
/* => AND-mask for bitwise read access */
/*    In case of read_allowed==0, mask is set to 0. */
/*    Read access by xPEC at adr_statcfg3 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu_read_bit_mask    0x00000114U
#define Adr_NX5_fmmusm_fmmu_read_bit_mask 0x018E5514U
#define Adr_NX5_fmmu_read_bit_mask        0x018E5514U

#define MSK_NX5_fmmu_read_bit_mask_fmmu_read_bit_mask 0x000000ffU
#define SRT_NX5_fmmu_read_bit_mask_fmmu_read_bit_mask 0

enum {
	BFW_NX5_fmmu_read_bit_mask_fmmu_read_bit_mask = 8,  /* [7:0] */
	BFW_NX5_fmmu_read_bit_mask_reserved1          = 24  /* [31:8] */
};

typedef struct NX5_FMMU_READ_BIT_MASK_BIT_Ttag {
	unsigned int fmmu_read_bit_mask : BFW_NX5_fmmu_read_bit_mask_fmmu_read_bit_mask; /* AND mask for bitwise read from RAM to bitstream */
	                                                                                 /* 1: Bit of UTX-Byte is read from RAM             */
	unsigned int reserved1          : BFW_NX5_fmmu_read_bit_mask_reserved1;          /* reserved                                        */
} NX5_FMMU_READ_BIT_MASK_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_FMMU_READ_BIT_MASK_BIT_T bf;
} NX5_FMMU_READ_BIT_MASK_T;

/* --------------------------------------------------------------------- */
/* Register fmmu_write_bit_rol_pos */
/* => Shift and mask value for bitwise write access. */
/*    For direct use with combined rol-and command. */
/*    Read access by xPEC at adr_urtx2 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu_write_bit_rol_pos    0x00000118U
#define Adr_NX5_fmmusm_fmmu_write_bit_rol_pos 0x018E5518U
#define Adr_NX5_fmmu_write_bit_rol_pos        0x018E5518U

#define MSK_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_rol      0x0000001fU
#define SRT_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_rol      0
#define MSK_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_maskmode 0x000000e0U
#define SRT_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_maskmode 5
#define MSK_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_mask     0x0000ff00U
#define SRT_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_mask     8
#define MSK_NX5_fmmu_write_bit_rol_pos_zero                    0xffff0000U
#define SRT_NX5_fmmu_write_bit_rol_pos_zero                    16

enum {
	BFW_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_rol      = 5,  /* [4:0] */
	BFW_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_maskmode = 3,  /* [7:5] */
	BFW_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_mask     = 8,  /* [15:8] */
	BFW_NX5_fmmu_write_bit_rol_pos_zero                    = 16  /* [31:16] */
};

typedef struct NX5_FMMU_WRITE_BIT_ROL_POS_BIT_Ttag {
	unsigned int fmmu_write_bit_rol      : BFW_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_rol;      /*  rotate left value for bitwise write from bitstream to RAM.        */
	                                                                                               /*  Rotates byte from URX to correct position for insertion into RAM, */
	unsigned int fmmu_write_bit_maskmode : BFW_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_maskmode; /* always 3'b010: and-mask-mode with upper mask-bits=0                */
	unsigned int fmmu_write_bit_mask     : BFW_NX5_fmmu_write_bit_rol_pos_fmmu_write_bit_mask;     /* mask for combined rol-and command,                                 */
	                                                                                               /* same as at adr_fmmu_write_bit_mask                                 */
	unsigned int zero                    : BFW_NX5_fmmu_write_bit_rol_pos_zero;                    /* upper mask bits, always zero                                       */
} NX5_FMMU_WRITE_BIT_ROL_POS_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_FMMU_WRITE_BIT_ROL_POS_BIT_T bf;
} NX5_FMMU_WRITE_BIT_ROL_POS_T;

/* --------------------------------------------------------------------- */
/* Register fmmu_write_bit_mask */
/* => AND-mask for bitwise write access */
/*    In case of write_allowed==0, mask is set to 0. */
/*    Read access by xPEC at adr_urtx3 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmu_write_bit_mask    0x0000011CU
#define Adr_NX5_fmmusm_fmmu_write_bit_mask 0x018E551CU
#define Adr_NX5_fmmu_write_bit_mask        0x018E551CU

#define MSK_NX5_fmmu_write_bit_mask_fmmu_write_bit_mask 0x000000ffU
#define SRT_NX5_fmmu_write_bit_mask_fmmu_write_bit_mask 0

enum {
	BFW_NX5_fmmu_write_bit_mask_fmmu_write_bit_mask = 8,  /* [7:0] */
	BFW_NX5_fmmu_write_bit_mask_reserved1           = 24  /* [31:8] */
};

typedef struct NX5_FMMU_WRITE_BIT_MASK_BIT_Ttag {
	unsigned int fmmu_write_bit_mask : BFW_NX5_fmmu_write_bit_mask_fmmu_write_bit_mask; /* AND mask for bitwise write from bitstream to RAM */
	                                                                                    /* 1: Bit of RAM Byte is written from stream (URX)  */
	unsigned int reserved1           : BFW_NX5_fmmu_write_bit_mask_reserved1;           /* reserved                                         */
} NX5_FMMU_WRITE_BIT_MASK_BIT_T;

typedef union {
	unsigned int                  val;
	NX5_FMMU_WRITE_BIT_MASK_BIT_T bf;
} NX5_FMMU_WRITE_BIT_MASK_T;

/* --------------------------------------------------------------------- */
/* Register fmmusm_len_en */
/* => Logical address enable from EtherCAT command */
/*    Read/Write access by xPEC at adr_xpec_sr8 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmusm_len_en    0x00000120U
#define Adr_NX5_fmmusm_fmmusm_len_en 0x018E5520U
#define Adr_NX5_fmmusm_len_en        0x018E5520U
#define DFLT_VAL_NX5_fmmusm_len_en   0x00000000U

#define MSK_NX5_fmmusm_len_en_ecat_len         0x0000ffffU
#define SRT_NX5_fmmusm_len_en_ecat_len         0
#define DFLT_VAL_NX5_fmmusm_len_en_ecat_len    0x00000000U
#define MSK_NX5_fmmusm_len_en_log_addr_en      0x00010000U
#define SRT_NX5_fmmusm_len_en_log_addr_en      16
#define DFLT_VAL_NX5_fmmusm_len_en_log_addr_en 0x00000000U
#define MSK_NX5_fmmusm_len_en_rd_en            0x00020000U
#define SRT_NX5_fmmusm_len_en_rd_en            17
#define DFLT_VAL_NX5_fmmusm_len_en_rd_en       0x00000000U
#define MSK_NX5_fmmusm_len_en_wr_en            0x00040000U
#define SRT_NX5_fmmusm_len_en_wr_en            18
#define DFLT_VAL_NX5_fmmusm_len_en_wr_en       0x00000000U

enum {
	BFW_NX5_fmmusm_len_en_ecat_len    = 16, /* [15:0] */
	BFW_NX5_fmmusm_len_en_log_addr_en = 1,  /* [16] */
	BFW_NX5_fmmusm_len_en_rd_en       = 1,  /* [17] */
	BFW_NX5_fmmusm_len_en_wr_en       = 1,  /* [18] */
	BFW_NX5_fmmusm_len_en_reserved1   = 13  /* [31:19] */
};

typedef struct NX5_FMMUSM_LEN_EN_BIT_Ttag {
	unsigned int ecat_len    : BFW_NX5_fmmusm_len_en_ecat_len;    /* Length of EtherCAT telegram:                                          */
	                                                              /* If UTX_COUNT == ecat_len                                              */
	unsigned int log_addr_en : BFW_NX5_fmmusm_len_en_log_addr_en; /* Logical address enable                                                */
	                                                              /* 1: fmmusm_read_addr_in and fmmusm_write_addr_in are logical addresses */
	unsigned int rd_en       : BFW_NX5_fmmusm_len_en_rd_en;       /* 1/0: check/no_check for read direction                                */
	unsigned int wr_en       : BFW_NX5_fmmusm_len_en_wr_en;       /* 1/0: check/no_check for write direction                               */
	unsigned int reserved1   : BFW_NX5_fmmusm_len_en_reserved1;   /* reserved                                                              */
} NX5_FMMUSM_LEN_EN_BIT_T;

typedef union {
	unsigned int            val;
	NX5_FMMUSM_LEN_EN_BIT_T bf;
} NX5_FMMUSM_LEN_EN_T;

/* --------------------------------------------------------------------- */
/* Register fmmusm_status_out */
/* => FMMU and SM match status: */
/*    Flags [31,30] are connected to event controller. */
/*    Read access by xPEC at adr_xpec_sr9 */
/* => Mode: R */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_fmmusm_status_out    0x00000124U
#define Adr_NX5_fmmusm_fmmusm_status_out 0x018E5524U
#define Adr_NX5_fmmusm_status_out        0x018E5524U

#define MSK_NX5_fmmusm_status_out_read_sm_nr               0x00000007U
#define SRT_NX5_fmmusm_status_out_read_sm_nr               0
#define MSK_NX5_fmmusm_status_out_read_sm_no_match         0x00000008U
#define SRT_NX5_fmmusm_status_out_read_sm_no_match         3
#define MSK_NX5_fmmusm_status_out_read_sm_fba              0x00000010U
#define SRT_NX5_fmmusm_status_out_read_sm_fba              4
#define MSK_NX5_fmmusm_status_out_read_sm_lba              0x00000020U
#define SRT_NX5_fmmusm_status_out_read_sm_lba              5
#define MSK_NX5_fmmusm_status_out_read_allowed             0x00000040U
#define SRT_NX5_fmmusm_status_out_read_allowed             6
#define MSK_NX5_fmmusm_status_out_read_allowed_bitwise     0x00000080U
#define SRT_NX5_fmmusm_status_out_read_allowed_bitwise     7
#define MSK_NX5_fmmusm_status_out_write_sm_nr              0x00000700U
#define SRT_NX5_fmmusm_status_out_write_sm_nr              8
#define MSK_NX5_fmmusm_status_out_write_sm_no_match        0x00000800U
#define SRT_NX5_fmmusm_status_out_write_sm_no_match        11
#define MSK_NX5_fmmusm_status_out_write_sm_fba             0x00001000U
#define SRT_NX5_fmmusm_status_out_write_sm_fba             12
#define MSK_NX5_fmmusm_status_out_write_sm_lba             0x00002000U
#define SRT_NX5_fmmusm_status_out_write_sm_lba             13
#define MSK_NX5_fmmusm_status_out_write_allowed            0x00004000U
#define SRT_NX5_fmmusm_status_out_write_allowed            14
#define MSK_NX5_fmmusm_status_out_write_allowed_bitwise    0x00008000U
#define SRT_NX5_fmmusm_status_out_write_allowed_bitwise    15
#define MSK_NX5_fmmusm_status_out_read_fmmu_match_nr       0x00070000U
#define SRT_NX5_fmmusm_status_out_read_fmmu_match_nr       16
#define MSK_NX5_fmmusm_status_out_read_fmmu_no_match       0x00080000U
#define SRT_NX5_fmmusm_status_out_read_fmmu_no_match       19
#define MSK_NX5_fmmusm_status_out_write_fmmu_match_nr      0x00700000U
#define SRT_NX5_fmmusm_status_out_write_fmmu_match_nr      20
#define MSK_NX5_fmmusm_status_out_write_fmmu_no_match      0x00800000U
#define SRT_NX5_fmmusm_status_out_write_fmmu_no_match      23
#define MSK_NX5_fmmusm_status_out_read_fmmu_match_bitwise  0x01000000U
#define SRT_NX5_fmmusm_status_out_read_fmmu_match_bitwise  24
#define MSK_NX5_fmmusm_status_out_write_fmmu_match_bitwise 0x02000000U
#define SRT_NX5_fmmusm_status_out_write_fmmu_match_bitwise 25
#define MSK_NX5_fmmusm_status_out_allowed_bitwise          0x20000000U
#define SRT_NX5_fmmusm_status_out_allowed_bitwise          29
#define MSK_NX5_fmmusm_status_out_allowed                  0x40000000U
#define SRT_NX5_fmmusm_status_out_allowed                  30
#define MSK_NX5_fmmusm_status_out_ecat_fin                 0x80000000U
#define SRT_NX5_fmmusm_status_out_ecat_fin                 31

enum {
	BFW_NX5_fmmusm_status_out_read_sm_nr               = 3, /* [2:0] */
	BFW_NX5_fmmusm_status_out_read_sm_no_match         = 1, /* [3] */
	BFW_NX5_fmmusm_status_out_read_sm_fba              = 1, /* [4] */
	BFW_NX5_fmmusm_status_out_read_sm_lba              = 1, /* [5] */
	BFW_NX5_fmmusm_status_out_read_allowed             = 1, /* [6] */
	BFW_NX5_fmmusm_status_out_read_allowed_bitwise     = 1, /* [7] */
	BFW_NX5_fmmusm_status_out_write_sm_nr              = 3, /* [10:8] */
	BFW_NX5_fmmusm_status_out_write_sm_no_match        = 1, /* [11] */
	BFW_NX5_fmmusm_status_out_write_sm_fba             = 1, /* [12] */
	BFW_NX5_fmmusm_status_out_write_sm_lba             = 1, /* [13] */
	BFW_NX5_fmmusm_status_out_write_allowed            = 1, /* [14] */
	BFW_NX5_fmmusm_status_out_write_allowed_bitwise    = 1, /* [15] */
	BFW_NX5_fmmusm_status_out_read_fmmu_match_nr       = 3, /* [18:16] */
	BFW_NX5_fmmusm_status_out_read_fmmu_no_match       = 1, /* [19] */
	BFW_NX5_fmmusm_status_out_write_fmmu_match_nr      = 3, /* [22:20] */
	BFW_NX5_fmmusm_status_out_write_fmmu_no_match      = 1, /* [23] */
	BFW_NX5_fmmusm_status_out_read_fmmu_match_bitwise  = 1, /* [24] */
	BFW_NX5_fmmusm_status_out_write_fmmu_match_bitwise = 1, /* [25] */
	BFW_NX5_fmmusm_status_out_reserved1                = 3, /* [28:26] */
	BFW_NX5_fmmusm_status_out_allowed_bitwise          = 1, /* [29] */
	BFW_NX5_fmmusm_status_out_allowed                  = 1, /* [30] */
	BFW_NX5_fmmusm_status_out_ecat_fin                 = 1  /* [31] */
};

typedef struct NX5_FMMUSM_STATUS_OUT_BIT_Ttag {
	unsigned int read_sm_nr               : BFW_NX5_fmmusm_status_out_read_sm_nr;               /* Number of actual matching sync manager for read access (0..7), independent on %read_allowed%      */
	unsigned int read_sm_no_match         : BFW_NX5_fmmusm_status_out_read_sm_no_match;         /* 1: No sync manager matches for reading -> direct access into xPEC Memory (register or data area). */
	                                                                                            /*    Read access is allowed, if last_phys_data_addr is not exceeded.                                */
	unsigned int read_sm_fba              : BFW_NX5_fmmusm_status_out_read_sm_fba;              /* Actual Sync Manager (read_sm_nr) matches on first byte, only valid if read_allowed==1             */
	unsigned int read_sm_lba              : BFW_NX5_fmmusm_status_out_read_sm_lba;              /* Actual Sync Manager (read_sm_nr) matches on last byte, only valid if read_allowed==1              */
	unsigned int read_allowed             : BFW_NX5_fmmusm_status_out_read_allowed;             /* 1/0: xPEC memory address %sm_read_addr_out% is released/ locked for reading                       */
	unsigned int read_allowed_bitwise     : BFW_NX5_fmmusm_status_out_read_allowed_bitwise;     /* 1/0: read access type is bitwise/bytewise, only valid if %read_allowed%==1                        */
	unsigned int write_sm_nr              : BFW_NX5_fmmusm_status_out_write_sm_nr;              /* Number of actual matching sync manager for write access (0..7), independent on %write_allowed%    */
	unsigned int write_sm_no_match        : BFW_NX5_fmmusm_status_out_write_sm_no_match;        /* 1: No sync manager matches for writing -> direct access into xPEC Memory (register or data area). */
	                                                                                            /*    Write access is allowed, if last_phys_data_addr is not exceeded.                               */
	unsigned int write_sm_fba             : BFW_NX5_fmmusm_status_out_write_sm_fba;             /* Actual Sync Manager (write_sm_nr) matches on first byte, only valid if write_allowed==1           */
	unsigned int write_sm_lba             : BFW_NX5_fmmusm_status_out_write_sm_lba;             /* Actual Sync Manager (write_sm_nr) matches on last byte, only valid if write_allowed==1            */
	unsigned int write_allowed            : BFW_NX5_fmmusm_status_out_write_allowed;            /* 1/0: xPEC memory address %sm_write_addr_out% is released/ locked for writing                      */
	unsigned int write_allowed_bitwise    : BFW_NX5_fmmusm_status_out_write_allowed_bitwise;    /* 1/0: write access type is bitwise/bytewise, only valid if %write_allowed%==1                      */
	unsigned int read_fmmu_match_nr       : BFW_NX5_fmmusm_status_out_read_fmmu_match_nr;       /* Number of actual matching fmmu manager for read access (0..7)                                     */
	                                                                                            /* ----------------------------------------------------------------------                            */
	unsigned int read_fmmu_no_match       : BFW_NX5_fmmusm_status_out_read_fmmu_no_match;       /* 1: no fmmu read match, read address translation failed, read_fmmu_match_nr is invalid             */
	unsigned int write_fmmu_match_nr      : BFW_NX5_fmmusm_status_out_write_fmmu_match_nr;      /* Number of actual matching fmmu manager for write access (0..7), write_fmmu_match_nr is invalid    */
	unsigned int write_fmmu_no_match      : BFW_NX5_fmmusm_status_out_write_fmmu_no_match;      /* 1: no fmmu write match, write address translation failed, write_fmmu_match_nr is invalid          */
	unsigned int read_fmmu_match_bitwise  : BFW_NX5_fmmusm_status_out_read_fmmu_match_bitwise;  /* 1: fmmu bitwise read match, read address translation successful, read access is bitwise           */
	unsigned int write_fmmu_match_bitwise : BFW_NX5_fmmusm_status_out_write_fmmu_match_bitwise; /* 1: fmmu bitwise write match, write address translation successful, write access is bitwise        */
	unsigned int reserved1                : BFW_NX5_fmmusm_status_out_reserved1;                /* reserved                                                                                          */
	unsigned int allowed_bitwise          : BFW_NX5_fmmusm_status_out_allowed_bitwise;          /* Read or write bitwise allowed                                                                     */
	                                                                                            /* ----------------------------------------------------------------------                            */
	unsigned int allowed                  : BFW_NX5_fmmusm_status_out_allowed;                  /* Read or write allowed, bitwise or bytewise                                                        */
	unsigned int ecat_fin                 : BFW_NX5_fmmusm_status_out_ecat_fin;                 /* EtherCAT telegram is finished (utx_count == fmmusm_len_en.ecat_len)                               */
} NX5_FMMUSM_STATUS_OUT_BIT_T;

typedef union {
	unsigned int                val;
	NX5_FMMUSM_STATUS_OUT_BIT_T bf;
} NX5_FMMUSM_STATUS_OUT_T;

/* --------------------------------------------------------------------- */
/* Register sm_buf_statcfg */
/* => Config bits set by xPEC, if any 3-buffer-SM gets new buffer. */
/*    Writable in parallel with mask by all xPECs, ARM and BUF_MAN. */
/*    Read/Write access by xPEC at adr_xpec_sr10 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_buf_statcfg    0x00000128U
#define Adr_NX5_fmmusm_sm_buf_statcfg 0x018E5528U
#define Adr_NX5_sm_buf_statcfg        0x018E5528U
#define DFLT_VAL_NX5_sm_buf_statcfg   0x00ffff00U

#define MSK_NX5_sm_buf_statcfg_buf_full_0      0x00000001U
#define SRT_NX5_sm_buf_statcfg_buf_full_0      0
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_0 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_1      0x00000002U
#define SRT_NX5_sm_buf_statcfg_buf_full_1      1
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_1 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_2      0x00000004U
#define SRT_NX5_sm_buf_statcfg_buf_full_2      2
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_2 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_3      0x00000008U
#define SRT_NX5_sm_buf_statcfg_buf_full_3      3
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_3 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_4      0x00000010U
#define SRT_NX5_sm_buf_statcfg_buf_full_4      4
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_4 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_5      0x00000020U
#define SRT_NX5_sm_buf_statcfg_buf_full_5      5
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_5 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_6      0x00000040U
#define SRT_NX5_sm_buf_statcfg_buf_full_6      6
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_6 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_full_7      0x00000080U
#define SRT_NX5_sm_buf_statcfg_buf_full_7      7
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_full_7 0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_nr_0        0x00000300U
#define SRT_NX5_sm_buf_statcfg_buf_nr_0        8
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_0   0x00000300U
#define MSK_NX5_sm_buf_statcfg_buf_nr_1        0x00000c00U
#define SRT_NX5_sm_buf_statcfg_buf_nr_1        10
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_1   0x00000c00U
#define MSK_NX5_sm_buf_statcfg_buf_nr_2        0x00003000U
#define SRT_NX5_sm_buf_statcfg_buf_nr_2        12
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_2   0x00003000U
#define MSK_NX5_sm_buf_statcfg_buf_nr_3        0x0000c000U
#define SRT_NX5_sm_buf_statcfg_buf_nr_3        14
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_3   0x0000c000U
#define MSK_NX5_sm_buf_statcfg_buf_nr_4        0x00030000U
#define SRT_NX5_sm_buf_statcfg_buf_nr_4        16
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_4   0x00030000U
#define MSK_NX5_sm_buf_statcfg_buf_nr_5        0x000c0000U
#define SRT_NX5_sm_buf_statcfg_buf_nr_5        18
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_5   0x000c0000U
#define MSK_NX5_sm_buf_statcfg_buf_nr_6        0x00300000U
#define SRT_NX5_sm_buf_statcfg_buf_nr_6        20
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_6   0x00300000U
#define MSK_NX5_sm_buf_statcfg_buf_nr_7        0x00c00000U
#define SRT_NX5_sm_buf_statcfg_buf_nr_7        22
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_nr_7   0x00c00000U
#define MSK_NX5_sm_buf_statcfg_buf_mask0       0x01000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask0       24
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask0  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask1       0x02000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask1       25
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask1  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask2       0x04000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask2       26
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask2  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask3       0x08000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask3       27
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask3  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask4       0x10000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask4       28
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask4  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask5       0x20000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask5       29
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask5  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask6       0x40000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask6       30
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask6  0x00000000U
#define MSK_NX5_sm_buf_statcfg_buf_mask7       0x80000000U
#define SRT_NX5_sm_buf_statcfg_buf_mask7       31
#define DFLT_VAL_NX5_sm_buf_statcfg_buf_mask7  0x00000000U

enum {
	BFW_NX5_sm_buf_statcfg_buf_full_0 = 1, /* [0] */
	BFW_NX5_sm_buf_statcfg_buf_full_1 = 1, /* [1] */
	BFW_NX5_sm_buf_statcfg_buf_full_2 = 1, /* [2] */
	BFW_NX5_sm_buf_statcfg_buf_full_3 = 1, /* [3] */
	BFW_NX5_sm_buf_statcfg_buf_full_4 = 1, /* [4] */
	BFW_NX5_sm_buf_statcfg_buf_full_5 = 1, /* [5] */
	BFW_NX5_sm_buf_statcfg_buf_full_6 = 1, /* [6] */
	BFW_NX5_sm_buf_statcfg_buf_full_7 = 1, /* [7] */
	BFW_NX5_sm_buf_statcfg_buf_nr_0   = 2, /* [9:8] */
	BFW_NX5_sm_buf_statcfg_buf_nr_1   = 2, /* [11:10] */
	BFW_NX5_sm_buf_statcfg_buf_nr_2   = 2, /* [13:12] */
	BFW_NX5_sm_buf_statcfg_buf_nr_3   = 2, /* [15:14] */
	BFW_NX5_sm_buf_statcfg_buf_nr_4   = 2, /* [17:16] */
	BFW_NX5_sm_buf_statcfg_buf_nr_5   = 2, /* [19:18] */
	BFW_NX5_sm_buf_statcfg_buf_nr_6   = 2, /* [21:20] */
	BFW_NX5_sm_buf_statcfg_buf_nr_7   = 2, /* [23:22] */
	BFW_NX5_sm_buf_statcfg_buf_mask0  = 1, /* [24] */
	BFW_NX5_sm_buf_statcfg_buf_mask1  = 1, /* [25] */
	BFW_NX5_sm_buf_statcfg_buf_mask2  = 1, /* [26] */
	BFW_NX5_sm_buf_statcfg_buf_mask3  = 1, /* [27] */
	BFW_NX5_sm_buf_statcfg_buf_mask4  = 1, /* [28] */
	BFW_NX5_sm_buf_statcfg_buf_mask5  = 1, /* [29] */
	BFW_NX5_sm_buf_statcfg_buf_mask6  = 1, /* [30] */
	BFW_NX5_sm_buf_statcfg_buf_mask7  = 1  /* [31] */
};

typedef struct NX5_SM_BUF_STATCFG_BIT_Ttag {
	unsigned int buf_full_0 : BFW_NX5_sm_buf_statcfg_buf_full_0; /* Buffer of SM0 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_1 : BFW_NX5_sm_buf_statcfg_buf_full_1; /* Buffer of SM1 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_2 : BFW_NX5_sm_buf_statcfg_buf_full_2; /* Buffer of SM2 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_3 : BFW_NX5_sm_buf_statcfg_buf_full_3; /* Buffer of SM3 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_4 : BFW_NX5_sm_buf_statcfg_buf_full_4; /* Buffer of SM4 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_5 : BFW_NX5_sm_buf_statcfg_buf_full_5; /* Buffer of SM5 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_6 : BFW_NX5_sm_buf_statcfg_buf_full_6; /* Buffer of SM6 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_full_7 : BFW_NX5_sm_buf_statcfg_buf_full_7; /* Buffer of SM7 in use by xPEC is full, if 1 buffer method is activated.     */
	unsigned int buf_nr_0   : BFW_NX5_sm_buf_statcfg_buf_nr_0;   /* Buffer number in use by xPEC of SM0, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_1   : BFW_NX5_sm_buf_statcfg_buf_nr_1;   /* Buffer number in use by xPEC of SM1, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_2   : BFW_NX5_sm_buf_statcfg_buf_nr_2;   /* Buffer number in use by xPEC of SM2, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_3   : BFW_NX5_sm_buf_statcfg_buf_nr_3;   /* Buffer number in use by xPEC of SM3, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_4   : BFW_NX5_sm_buf_statcfg_buf_nr_4;   /* Buffer number in use by xPEC of SM4, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_5   : BFW_NX5_sm_buf_statcfg_buf_nr_5;   /* Buffer number in use by xPEC of SM5, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_6   : BFW_NX5_sm_buf_statcfg_buf_nr_6;   /* Buffer number in use by xPEC of SM6, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_nr_7   : BFW_NX5_sm_buf_statcfg_buf_nr_7;   /* Buffer number in use by xPEC of SM7, if 3 buffer method is activated.      */
	                                                             /* Usually set by BUF_MAN (not by software).                                  */
	unsigned int buf_mask0  : BFW_NX5_sm_buf_statcfg_buf_mask0;  /* Write mask: change only bits of SM0:                                       */
	                                                             /* Depending on sm0_cfg_mode.buf_method, mask acts on buf_nr_0 or buf_full_0. */
	unsigned int buf_mask1  : BFW_NX5_sm_buf_statcfg_buf_mask1;  /* Write mask: change only bits of SM1:                                       */
	                                                             /* Depending on sm1_cfg_mode.buf_method, mask acts on buf_nr_1 or buf_full_1. */
	unsigned int buf_mask2  : BFW_NX5_sm_buf_statcfg_buf_mask2;  /* Write mask: change only bits of SM2:                                       */
	                                                             /* Depending on sm2_cfg_mode.buf_method, mask acts on buf_nr_2 or buf_full_2. */
	unsigned int buf_mask3  : BFW_NX5_sm_buf_statcfg_buf_mask3;  /* Write mask: change only bits of SM3:                                       */
	                                                             /* Depending on sm3_cfg_mode.buf_method, mask acts on buf_nr_3 or buf_full_3. */
	unsigned int buf_mask4  : BFW_NX5_sm_buf_statcfg_buf_mask4;  /* Write mask: change only bits of SM4:                                       */
	                                                             /* Depending on sm4_cfg_mode.buf_method, mask acts on buf_nr_4 or buf_full_4. */
	unsigned int buf_mask5  : BFW_NX5_sm_buf_statcfg_buf_mask5;  /* Write mask: change only bits of SM5:                                       */
	                                                             /* Depending on sm5_cfg_mode.buf_method, mask acts on buf_nr_5 or buf_full_5. */
	unsigned int buf_mask6  : BFW_NX5_sm_buf_statcfg_buf_mask6;  /* Write mask: change only bits of SM6:                                       */
	                                                             /* Depending on sm6_cfg_mode.buf_method, mask acts on buf_nr_6 or buf_full_6. */
	unsigned int buf_mask7  : BFW_NX5_sm_buf_statcfg_buf_mask7;  /* Write mask: change only bits of SM7:                                       */
	                                                             /* Depending on sm7_cfg_mode.buf_method, mask acts on buf_nr_7 or buf_full_7. */
} NX5_SM_BUF_STATCFG_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SM_BUF_STATCFG_BIT_T bf;
} NX5_SM_BUF_STATCFG_T;

/* --------------------------------------------------------------------- */
/* Register sm_read_event */
/* => Read Event status bits of all SM, process channel: */
/*    Writable in parallel with mask by all xPECs and ARM. */
/*    Reset by FMMUSM at first_byte_addressed and write_allowed. */
/*    Read/Write access by xPEC at adr_xpec_sr11 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_read_event    0x0000012CU
#define Adr_NX5_fmmusm_sm_read_event 0x018E552CU
#define Adr_NX5_sm_read_event        0x018E552CU
#define DFLT_VAL_NX5_sm_read_event   0x00000000U

#define MSK_NX5_sm_read_event_read_event_0          0x00000001U
#define SRT_NX5_sm_read_event_read_event_0          0
#define DFLT_VAL_NX5_sm_read_event_read_event_0     0x00000000U
#define MSK_NX5_sm_read_event_read_event_1          0x00000002U
#define SRT_NX5_sm_read_event_read_event_1          1
#define DFLT_VAL_NX5_sm_read_event_read_event_1     0x00000000U
#define MSK_NX5_sm_read_event_read_event_2          0x00000004U
#define SRT_NX5_sm_read_event_read_event_2          2
#define DFLT_VAL_NX5_sm_read_event_read_event_2     0x00000000U
#define MSK_NX5_sm_read_event_read_event_3          0x00000008U
#define SRT_NX5_sm_read_event_read_event_3          3
#define DFLT_VAL_NX5_sm_read_event_read_event_3     0x00000000U
#define MSK_NX5_sm_read_event_read_event_4          0x00000010U
#define SRT_NX5_sm_read_event_read_event_4          4
#define DFLT_VAL_NX5_sm_read_event_read_event_4     0x00000000U
#define MSK_NX5_sm_read_event_read_event_5          0x00000020U
#define SRT_NX5_sm_read_event_read_event_5          5
#define DFLT_VAL_NX5_sm_read_event_read_event_5     0x00000000U
#define MSK_NX5_sm_read_event_read_event_6          0x00000040U
#define SRT_NX5_sm_read_event_read_event_6          6
#define DFLT_VAL_NX5_sm_read_event_read_event_6     0x00000000U
#define MSK_NX5_sm_read_event_read_event_7          0x00000080U
#define SRT_NX5_sm_read_event_read_event_7          7
#define DFLT_VAL_NX5_sm_read_event_read_event_7     0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask0      0x00010000U
#define SRT_NX5_sm_read_event_read_event_mask0      16
#define DFLT_VAL_NX5_sm_read_event_read_event_mask0 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask1      0x00020000U
#define SRT_NX5_sm_read_event_read_event_mask1      17
#define DFLT_VAL_NX5_sm_read_event_read_event_mask1 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask2      0x00040000U
#define SRT_NX5_sm_read_event_read_event_mask2      18
#define DFLT_VAL_NX5_sm_read_event_read_event_mask2 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask3      0x00080000U
#define SRT_NX5_sm_read_event_read_event_mask3      19
#define DFLT_VAL_NX5_sm_read_event_read_event_mask3 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask4      0x00100000U
#define SRT_NX5_sm_read_event_read_event_mask4      20
#define DFLT_VAL_NX5_sm_read_event_read_event_mask4 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask5      0x00200000U
#define SRT_NX5_sm_read_event_read_event_mask5      21
#define DFLT_VAL_NX5_sm_read_event_read_event_mask5 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask6      0x00400000U
#define SRT_NX5_sm_read_event_read_event_mask6      22
#define DFLT_VAL_NX5_sm_read_event_read_event_mask6 0x00000000U
#define MSK_NX5_sm_read_event_read_event_mask7      0x00800000U
#define SRT_NX5_sm_read_event_read_event_mask7      23
#define DFLT_VAL_NX5_sm_read_event_read_event_mask7 0x00000000U

enum {
	BFW_NX5_sm_read_event_read_event_0     = 1, /* [0] */
	BFW_NX5_sm_read_event_read_event_1     = 1, /* [1] */
	BFW_NX5_sm_read_event_read_event_2     = 1, /* [2] */
	BFW_NX5_sm_read_event_read_event_3     = 1, /* [3] */
	BFW_NX5_sm_read_event_read_event_4     = 1, /* [4] */
	BFW_NX5_sm_read_event_read_event_5     = 1, /* [5] */
	BFW_NX5_sm_read_event_read_event_6     = 1, /* [6] */
	BFW_NX5_sm_read_event_read_event_7     = 1, /* [7] */
	BFW_NX5_sm_read_event_reserved1        = 8, /* [15:8] */
	BFW_NX5_sm_read_event_read_event_mask0 = 1, /* [16] */
	BFW_NX5_sm_read_event_read_event_mask1 = 1, /* [17] */
	BFW_NX5_sm_read_event_read_event_mask2 = 1, /* [18] */
	BFW_NX5_sm_read_event_read_event_mask3 = 1, /* [19] */
	BFW_NX5_sm_read_event_read_event_mask4 = 1, /* [20] */
	BFW_NX5_sm_read_event_read_event_mask5 = 1, /* [21] */
	BFW_NX5_sm_read_event_read_event_mask6 = 1, /* [22] */
	BFW_NX5_sm_read_event_read_event_mask7 = 1, /* [23] */
	BFW_NX5_sm_read_event_reserved2        = 8  /* [31:24] */
};

typedef struct NX5_SM_READ_EVENT_BIT_Ttag {
	unsigned int read_event_0     : BFW_NX5_sm_read_event_read_event_0;     /* SM0 read event                     */
	unsigned int read_event_1     : BFW_NX5_sm_read_event_read_event_1;     /* SM1 read event                     */
	unsigned int read_event_2     : BFW_NX5_sm_read_event_read_event_2;     /* SM2 read event                     */
	unsigned int read_event_3     : BFW_NX5_sm_read_event_read_event_3;     /* SM3 read event                     */
	unsigned int read_event_4     : BFW_NX5_sm_read_event_read_event_4;     /* SM4 read event                     */
	unsigned int read_event_5     : BFW_NX5_sm_read_event_read_event_5;     /* SM5 read event                     */
	unsigned int read_event_6     : BFW_NX5_sm_read_event_read_event_6;     /* SM6 read event                     */
	unsigned int read_event_7     : BFW_NX5_sm_read_event_read_event_7;     /* SM7 read event                     */
	unsigned int reserved1        : BFW_NX5_sm_read_event_reserved1;        /* reserved                           */
	unsigned int read_event_mask0 : BFW_NX5_sm_read_event_read_event_mask0; /* write mask: change only bit of SM0 */
	unsigned int read_event_mask1 : BFW_NX5_sm_read_event_read_event_mask1; /* write mask: change only bit of SM1 */
	unsigned int read_event_mask2 : BFW_NX5_sm_read_event_read_event_mask2; /* write mask: change only bit of SM2 */
	unsigned int read_event_mask3 : BFW_NX5_sm_read_event_read_event_mask3; /* write mask: change only bit of SM3 */
	unsigned int read_event_mask4 : BFW_NX5_sm_read_event_read_event_mask4; /* write mask: change only bit of SM4 */
	unsigned int read_event_mask5 : BFW_NX5_sm_read_event_read_event_mask5; /* write mask: change only bit of SM5 */
	unsigned int read_event_mask6 : BFW_NX5_sm_read_event_read_event_mask6; /* write mask: change only bit of SM6 */
	unsigned int read_event_mask7 : BFW_NX5_sm_read_event_read_event_mask7; /* write mask: change only bit of SM7 */
	unsigned int reserved2        : BFW_NX5_sm_read_event_reserved2;        /* reserved                           */
} NX5_SM_READ_EVENT_BIT_T;

typedef union {
	unsigned int            val;
	NX5_SM_READ_EVENT_BIT_T bf;
} NX5_SM_READ_EVENT_T;

/* --------------------------------------------------------------------- */
/* Register sm_write_event */
/* => Write Event status bits of all SM, process channel */
/*    Writable in parallel with mask by all xPECs and ARM. */
/*    Reset by FMMUSM at first_byte_addressed and read_allowed. */
/*    Read/Write access by xPEC at adr_xpec_sr12 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_write_event    0x00000130U
#define Adr_NX5_fmmusm_sm_write_event 0x018E5530U
#define Adr_NX5_sm_write_event        0x018E5530U
#define DFLT_VAL_NX5_sm_write_event   0x00000000U

#define MSK_NX5_sm_write_event_write_event_0          0x00000001U
#define SRT_NX5_sm_write_event_write_event_0          0
#define DFLT_VAL_NX5_sm_write_event_write_event_0     0x00000000U
#define MSK_NX5_sm_write_event_write_event_1          0x00000002U
#define SRT_NX5_sm_write_event_write_event_1          1
#define DFLT_VAL_NX5_sm_write_event_write_event_1     0x00000000U
#define MSK_NX5_sm_write_event_write_event_2          0x00000004U
#define SRT_NX5_sm_write_event_write_event_2          2
#define DFLT_VAL_NX5_sm_write_event_write_event_2     0x00000000U
#define MSK_NX5_sm_write_event_write_event_3          0x00000008U
#define SRT_NX5_sm_write_event_write_event_3          3
#define DFLT_VAL_NX5_sm_write_event_write_event_3     0x00000000U
#define MSK_NX5_sm_write_event_write_event_4          0x00000010U
#define SRT_NX5_sm_write_event_write_event_4          4
#define DFLT_VAL_NX5_sm_write_event_write_event_4     0x00000000U
#define MSK_NX5_sm_write_event_write_event_5          0x00000020U
#define SRT_NX5_sm_write_event_write_event_5          5
#define DFLT_VAL_NX5_sm_write_event_write_event_5     0x00000000U
#define MSK_NX5_sm_write_event_write_event_6          0x00000040U
#define SRT_NX5_sm_write_event_write_event_6          6
#define DFLT_VAL_NX5_sm_write_event_write_event_6     0x00000000U
#define MSK_NX5_sm_write_event_write_event_7          0x00000080U
#define SRT_NX5_sm_write_event_write_event_7          7
#define DFLT_VAL_NX5_sm_write_event_write_event_7     0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask0      0x00010000U
#define SRT_NX5_sm_write_event_write_event_mask0      16
#define DFLT_VAL_NX5_sm_write_event_write_event_mask0 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask1      0x00020000U
#define SRT_NX5_sm_write_event_write_event_mask1      17
#define DFLT_VAL_NX5_sm_write_event_write_event_mask1 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask2      0x00040000U
#define SRT_NX5_sm_write_event_write_event_mask2      18
#define DFLT_VAL_NX5_sm_write_event_write_event_mask2 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask3      0x00080000U
#define SRT_NX5_sm_write_event_write_event_mask3      19
#define DFLT_VAL_NX5_sm_write_event_write_event_mask3 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask4      0x00100000U
#define SRT_NX5_sm_write_event_write_event_mask4      20
#define DFLT_VAL_NX5_sm_write_event_write_event_mask4 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask5      0x00200000U
#define SRT_NX5_sm_write_event_write_event_mask5      21
#define DFLT_VAL_NX5_sm_write_event_write_event_mask5 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask6      0x00400000U
#define SRT_NX5_sm_write_event_write_event_mask6      22
#define DFLT_VAL_NX5_sm_write_event_write_event_mask6 0x00000000U
#define MSK_NX5_sm_write_event_write_event_mask7      0x00800000U
#define SRT_NX5_sm_write_event_write_event_mask7      23
#define DFLT_VAL_NX5_sm_write_event_write_event_mask7 0x00000000U

enum {
	BFW_NX5_sm_write_event_write_event_0     = 1, /* [0] */
	BFW_NX5_sm_write_event_write_event_1     = 1, /* [1] */
	BFW_NX5_sm_write_event_write_event_2     = 1, /* [2] */
	BFW_NX5_sm_write_event_write_event_3     = 1, /* [3] */
	BFW_NX5_sm_write_event_write_event_4     = 1, /* [4] */
	BFW_NX5_sm_write_event_write_event_5     = 1, /* [5] */
	BFW_NX5_sm_write_event_write_event_6     = 1, /* [6] */
	BFW_NX5_sm_write_event_write_event_7     = 1, /* [7] */
	BFW_NX5_sm_write_event_reserved1         = 8, /* [15:8] */
	BFW_NX5_sm_write_event_write_event_mask0 = 1, /* [16] */
	BFW_NX5_sm_write_event_write_event_mask1 = 1, /* [17] */
	BFW_NX5_sm_write_event_write_event_mask2 = 1, /* [18] */
	BFW_NX5_sm_write_event_write_event_mask3 = 1, /* [19] */
	BFW_NX5_sm_write_event_write_event_mask4 = 1, /* [20] */
	BFW_NX5_sm_write_event_write_event_mask5 = 1, /* [21] */
	BFW_NX5_sm_write_event_write_event_mask6 = 1, /* [22] */
	BFW_NX5_sm_write_event_write_event_mask7 = 1, /* [23] */
	BFW_NX5_sm_write_event_reserved2         = 8  /* [31:24] */
};

typedef struct NX5_SM_WRITE_EVENT_BIT_Ttag {
	unsigned int write_event_0     : BFW_NX5_sm_write_event_write_event_0;     /* SM0 write event                    */
	unsigned int write_event_1     : BFW_NX5_sm_write_event_write_event_1;     /* SM1 write event                    */
	unsigned int write_event_2     : BFW_NX5_sm_write_event_write_event_2;     /* SM2 write event                    */
	unsigned int write_event_3     : BFW_NX5_sm_write_event_write_event_3;     /* SM3 write event                    */
	unsigned int write_event_4     : BFW_NX5_sm_write_event_write_event_4;     /* SM4 write event                    */
	unsigned int write_event_5     : BFW_NX5_sm_write_event_write_event_5;     /* SM5 write event                    */
	unsigned int write_event_6     : BFW_NX5_sm_write_event_write_event_6;     /* SM6 write event                    */
	unsigned int write_event_7     : BFW_NX5_sm_write_event_write_event_7;     /* SM7 write event                    */
	unsigned int reserved1         : BFW_NX5_sm_write_event_reserved1;         /* reserved                           */
	unsigned int write_event_mask0 : BFW_NX5_sm_write_event_write_event_mask0; /* write mask: change only bit of SM0 */
	unsigned int write_event_mask1 : BFW_NX5_sm_write_event_write_event_mask1; /* write mask: change only bit of SM1 */
	unsigned int write_event_mask2 : BFW_NX5_sm_write_event_write_event_mask2; /* write mask: change only bit of SM2 */
	unsigned int write_event_mask3 : BFW_NX5_sm_write_event_write_event_mask3; /* write mask: change only bit of SM3 */
	unsigned int write_event_mask4 : BFW_NX5_sm_write_event_write_event_mask4; /* write mask: change only bit of SM4 */
	unsigned int write_event_mask5 : BFW_NX5_sm_write_event_write_event_mask5; /* write mask: change only bit of SM5 */
	unsigned int write_event_mask6 : BFW_NX5_sm_write_event_write_event_mask6; /* write mask: change only bit of SM6 */
	unsigned int write_event_mask7 : BFW_NX5_sm_write_event_write_event_mask7; /* write mask: change only bit of SM7 */
	unsigned int reserved2         : BFW_NX5_sm_write_event_reserved2;         /* reserved                           */
} NX5_SM_WRITE_EVENT_BIT_T;

typedef union {
	unsigned int             val;
	NX5_SM_WRITE_EVENT_BIT_T bf;
} NX5_SM_WRITE_EVENT_T;

/* --------------------------------------------------------------------- */
/* Register sm_first_byte_addressed */
/* => First byte addressed status bits of all SM, process channel: */
/*    Set by HW, if first byte was addressed. */
/*    Reset by SW (xPEC or ARM), by writing 1 on appropriate bit (usually after FCSok/fail). */
/*    Resetable in parallel by all xPECs and ARM. */
/*    Bits 31:8 are read only versions of other registers for faster update of register area. */
/*    Read/Write access by xPEC at adr_xpec_sr13 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_first_byte_addressed    0x00000134U
#define Adr_NX5_fmmusm_sm_first_byte_addressed 0x018E5534U
#define Adr_NX5_sm_first_byte_addressed        0x018E5534U
#define DFLT_VAL_NX5_sm_first_byte_addressed   0x00000000U

#define MSK_NX5_sm_first_byte_addressed_fba_0              0x00000001U
#define SRT_NX5_sm_first_byte_addressed_fba_0              0
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_0         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_1              0x00000002U
#define SRT_NX5_sm_first_byte_addressed_fba_1              1
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_1         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_2              0x00000004U
#define SRT_NX5_sm_first_byte_addressed_fba_2              2
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_2         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_3              0x00000008U
#define SRT_NX5_sm_first_byte_addressed_fba_3              3
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_3         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_4              0x00000010U
#define SRT_NX5_sm_first_byte_addressed_fba_4              4
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_4         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_5              0x00000020U
#define SRT_NX5_sm_first_byte_addressed_fba_5              5
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_5         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_6              0x00000040U
#define SRT_NX5_sm_first_byte_addressed_fba_6              6
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_6         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_fba_7              0x00000080U
#define SRT_NX5_sm_first_byte_addressed_fba_7              7
#define DFLT_VAL_NX5_sm_first_byte_addressed_fba_7         0x00000000U
#define MSK_NX5_sm_first_byte_addressed_write_event_0      0x00000100U
#define SRT_NX5_sm_first_byte_addressed_write_event_0      8
#define DFLT_VAL_NX5_sm_first_byte_addressed_write_event_0 0x00000000U
#define MSK_NX5_sm_first_byte_addressed_read_event_0       0x00000200U
#define SRT_NX5_sm_first_byte_addressed_read_event_0       9
#define DFLT_VAL_NX5_sm_first_byte_addressed_read_event_0  0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_full_0         0x00000800U
#define SRT_NX5_sm_first_byte_addressed_buf_full_0         11
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_full_0    0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_nr_0           0x00003000U
#define SRT_NX5_sm_first_byte_addressed_buf_nr_0           12
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_nr_0      0x00000000U
#define MSK_NX5_sm_first_byte_addressed_write_event_1      0x00004000U
#define SRT_NX5_sm_first_byte_addressed_write_event_1      14
#define DFLT_VAL_NX5_sm_first_byte_addressed_write_event_1 0x00000000U
#define MSK_NX5_sm_first_byte_addressed_read_event_1       0x00008000U
#define SRT_NX5_sm_first_byte_addressed_read_event_1       15
#define DFLT_VAL_NX5_sm_first_byte_addressed_read_event_1  0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_full_1         0x00020000U
#define SRT_NX5_sm_first_byte_addressed_buf_full_1         17
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_full_1    0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_nr_1           0x000c0000U
#define SRT_NX5_sm_first_byte_addressed_buf_nr_1           18
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_nr_1      0x00000000U
#define MSK_NX5_sm_first_byte_addressed_write_event_2      0x00100000U
#define SRT_NX5_sm_first_byte_addressed_write_event_2      20
#define DFLT_VAL_NX5_sm_first_byte_addressed_write_event_2 0x00000000U
#define MSK_NX5_sm_first_byte_addressed_read_event_2       0x00200000U
#define SRT_NX5_sm_first_byte_addressed_read_event_2       21
#define DFLT_VAL_NX5_sm_first_byte_addressed_read_event_2  0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_full_2         0x00800000U
#define SRT_NX5_sm_first_byte_addressed_buf_full_2         23
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_full_2    0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_nr_2           0x03000000U
#define SRT_NX5_sm_first_byte_addressed_buf_nr_2           24
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_nr_2      0x00000000U
#define MSK_NX5_sm_first_byte_addressed_write_event_3      0x04000000U
#define SRT_NX5_sm_first_byte_addressed_write_event_3      26
#define DFLT_VAL_NX5_sm_first_byte_addressed_write_event_3 0x00000000U
#define MSK_NX5_sm_first_byte_addressed_read_event_3       0x08000000U
#define SRT_NX5_sm_first_byte_addressed_read_event_3       27
#define DFLT_VAL_NX5_sm_first_byte_addressed_read_event_3  0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_full_3         0x20000000U
#define SRT_NX5_sm_first_byte_addressed_buf_full_3         29
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_full_3    0x00000000U
#define MSK_NX5_sm_first_byte_addressed_buf_nr_3           0xc0000000U
#define SRT_NX5_sm_first_byte_addressed_buf_nr_3           30
#define DFLT_VAL_NX5_sm_first_byte_addressed_buf_nr_3      0x00000000U

enum {
	BFW_NX5_sm_first_byte_addressed_fba_0         = 1, /* [0] */
	BFW_NX5_sm_first_byte_addressed_fba_1         = 1, /* [1] */
	BFW_NX5_sm_first_byte_addressed_fba_2         = 1, /* [2] */
	BFW_NX5_sm_first_byte_addressed_fba_3         = 1, /* [3] */
	BFW_NX5_sm_first_byte_addressed_fba_4         = 1, /* [4] */
	BFW_NX5_sm_first_byte_addressed_fba_5         = 1, /* [5] */
	BFW_NX5_sm_first_byte_addressed_fba_6         = 1, /* [6] */
	BFW_NX5_sm_first_byte_addressed_fba_7         = 1, /* [7] */
	BFW_NX5_sm_first_byte_addressed_write_event_0 = 1, /* [8] */
	BFW_NX5_sm_first_byte_addressed_read_event_0  = 1, /* [9] */
	BFW_NX5_sm_first_byte_addressed_reserved1     = 1, /* [10] */
	BFW_NX5_sm_first_byte_addressed_buf_full_0    = 1, /* [11] */
	BFW_NX5_sm_first_byte_addressed_buf_nr_0      = 2, /* [13:12] */
	BFW_NX5_sm_first_byte_addressed_write_event_1 = 1, /* [14] */
	BFW_NX5_sm_first_byte_addressed_read_event_1  = 1, /* [15] */
	BFW_NX5_sm_first_byte_addressed_reserved2     = 1, /* [16] */
	BFW_NX5_sm_first_byte_addressed_buf_full_1    = 1, /* [17] */
	BFW_NX5_sm_first_byte_addressed_buf_nr_1      = 2, /* [19:18] */
	BFW_NX5_sm_first_byte_addressed_write_event_2 = 1, /* [20] */
	BFW_NX5_sm_first_byte_addressed_read_event_2  = 1, /* [21] */
	BFW_NX5_sm_first_byte_addressed_reserved3     = 1, /* [22] */
	BFW_NX5_sm_first_byte_addressed_buf_full_2    = 1, /* [23] */
	BFW_NX5_sm_first_byte_addressed_buf_nr_2      = 2, /* [25:24] */
	BFW_NX5_sm_first_byte_addressed_write_event_3 = 1, /* [26] */
	BFW_NX5_sm_first_byte_addressed_read_event_3  = 1, /* [27] */
	BFW_NX5_sm_first_byte_addressed_reserved4     = 1, /* [28] */
	BFW_NX5_sm_first_byte_addressed_buf_full_3    = 1, /* [29] */
	BFW_NX5_sm_first_byte_addressed_buf_nr_3      = 2  /* [31:30] */
};

typedef struct NX5_SM_FIRST_BYTE_ADDRESSED_BIT_Ttag {
	unsigned int fba_0         : BFW_NX5_sm_first_byte_addressed_fba_0;         /* SM0 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_1         : BFW_NX5_sm_first_byte_addressed_fba_1;         /* SM1 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_2         : BFW_NX5_sm_first_byte_addressed_fba_2;         /* SM2 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_3         : BFW_NX5_sm_first_byte_addressed_fba_3;         /* SM3 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_4         : BFW_NX5_sm_first_byte_addressed_fba_4;         /* SM4 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_5         : BFW_NX5_sm_first_byte_addressed_fba_5;         /* SM5 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_6         : BFW_NX5_sm_first_byte_addressed_fba_6;         /* SM6 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int fba_7         : BFW_NX5_sm_first_byte_addressed_fba_7;         /* SM7 matches first byte of its address area                        */
	                                                                            /* 0: match only for first address (byte) of SM-address-area (len=1) */
	unsigned int write_event_0 : BFW_NX5_sm_first_byte_addressed_write_event_0; /* read only version of sm_write_event.write_event_0                 */
	unsigned int read_event_0  : BFW_NX5_sm_first_byte_addressed_read_event_0;  /* read only version of sm_read_event.read_event_0                   */
	unsigned int reserved1     : BFW_NX5_sm_first_byte_addressed_reserved1;     /* reserved                                                          */
	unsigned int buf_full_0    : BFW_NX5_sm_first_byte_addressed_buf_full_0;    /* read only version of sm_buf_statcfg.buf_full_0                    */
	unsigned int buf_nr_0      : BFW_NX5_sm_first_byte_addressed_buf_nr_0;      /* read only version of sm_buf_statcfg.buf_nr_0                      */
	unsigned int write_event_1 : BFW_NX5_sm_first_byte_addressed_write_event_1; /* read only version of sm_write_event.write_event_1                 */
	unsigned int read_event_1  : BFW_NX5_sm_first_byte_addressed_read_event_1;  /* read only version of sm_read_event.read_event_1                   */
	unsigned int reserved2     : BFW_NX5_sm_first_byte_addressed_reserved2;     /* reserved                                                          */
	unsigned int buf_full_1    : BFW_NX5_sm_first_byte_addressed_buf_full_1;    /* read only version of sm_buf_statcfg.buf_full_1                    */
	unsigned int buf_nr_1      : BFW_NX5_sm_first_byte_addressed_buf_nr_1;      /* read only version of sm_buf_statcfg.buf_nr_1                      */
	unsigned int write_event_2 : BFW_NX5_sm_first_byte_addressed_write_event_2; /* read only version of sm_write_event.write_event_2                 */
	unsigned int read_event_2  : BFW_NX5_sm_first_byte_addressed_read_event_2;  /* read only version of sm_read_event.read_event_2                   */
	unsigned int reserved3     : BFW_NX5_sm_first_byte_addressed_reserved3;     /* reserved                                                          */
	unsigned int buf_full_2    : BFW_NX5_sm_first_byte_addressed_buf_full_2;    /* read only version of sm_buf_statcfg.buf_full_2                    */
	unsigned int buf_nr_2      : BFW_NX5_sm_first_byte_addressed_buf_nr_2;      /* read only version of sm_buf_statcfg.buf_nr_2                      */
	unsigned int write_event_3 : BFW_NX5_sm_first_byte_addressed_write_event_3; /* read only version of sm_write_event.write_event_3                 */
	unsigned int read_event_3  : BFW_NX5_sm_first_byte_addressed_read_event_3;  /* read only version of sm_read_event.read_event_3                   */
	unsigned int reserved4     : BFW_NX5_sm_first_byte_addressed_reserved4;     /* reserved                                                          */
	unsigned int buf_full_3    : BFW_NX5_sm_first_byte_addressed_buf_full_3;    /* read only version of sm_buf_statcfg.buf_full_3                    */
	unsigned int buf_nr_3      : BFW_NX5_sm_first_byte_addressed_buf_nr_3;      /* read only version of sm_buf_statcfg.buf_nr_3                      */
} NX5_SM_FIRST_BYTE_ADDRESSED_BIT_T;

typedef union {
	unsigned int                      val;
	NX5_SM_FIRST_BYTE_ADDRESSED_BIT_T bf;
} NX5_SM_FIRST_BYTE_ADDRESSED_T;

/* --------------------------------------------------------------------- */
/* Register sm_last_byte_addressed */
/* => Last byte addressed status bits of all SM, process channel: */
/*    Set by HW, if last byte was addressed. */
/*    Reset by SW (xPEC or ARM), by writing 1 on appropriate bit (usually after FCSok/fail). */
/*    Resetable in parallel by all xPECs and ARM. */
/*    Bits 31:8 are read only versions of other registers for faster update of register area. */
/*    Read/Write access by xPEC at adr_xpec_sr14 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_last_byte_addressed    0x00000138U
#define Adr_NX5_fmmusm_sm_last_byte_addressed 0x018E5538U
#define Adr_NX5_sm_last_byte_addressed        0x018E5538U
#define DFLT_VAL_NX5_sm_last_byte_addressed   0x00000000U

#define MSK_NX5_sm_last_byte_addressed_lba_0              0x00000001U
#define SRT_NX5_sm_last_byte_addressed_lba_0              0
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_0         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_1              0x00000002U
#define SRT_NX5_sm_last_byte_addressed_lba_1              1
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_1         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_2              0x00000004U
#define SRT_NX5_sm_last_byte_addressed_lba_2              2
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_2         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_3              0x00000008U
#define SRT_NX5_sm_last_byte_addressed_lba_3              3
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_3         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_4              0x00000010U
#define SRT_NX5_sm_last_byte_addressed_lba_4              4
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_4         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_5              0x00000020U
#define SRT_NX5_sm_last_byte_addressed_lba_5              5
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_5         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_6              0x00000040U
#define SRT_NX5_sm_last_byte_addressed_lba_6              6
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_6         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_lba_7              0x00000080U
#define SRT_NX5_sm_last_byte_addressed_lba_7              7
#define DFLT_VAL_NX5_sm_last_byte_addressed_lba_7         0x00000000U
#define MSK_NX5_sm_last_byte_addressed_write_event_4      0x00000100U
#define SRT_NX5_sm_last_byte_addressed_write_event_4      8
#define DFLT_VAL_NX5_sm_last_byte_addressed_write_event_4 0x00000000U
#define MSK_NX5_sm_last_byte_addressed_read_event_4       0x00000200U
#define SRT_NX5_sm_last_byte_addressed_read_event_4       9
#define DFLT_VAL_NX5_sm_last_byte_addressed_read_event_4  0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_full_4         0x00000800U
#define SRT_NX5_sm_last_byte_addressed_buf_full_4         11
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_full_4    0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_nr_4           0x00003000U
#define SRT_NX5_sm_last_byte_addressed_buf_nr_4           12
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_nr_4      0x00000000U
#define MSK_NX5_sm_last_byte_addressed_write_event_5      0x00004000U
#define SRT_NX5_sm_last_byte_addressed_write_event_5      14
#define DFLT_VAL_NX5_sm_last_byte_addressed_write_event_5 0x00000000U
#define MSK_NX5_sm_last_byte_addressed_read_event_5       0x00008000U
#define SRT_NX5_sm_last_byte_addressed_read_event_5       15
#define DFLT_VAL_NX5_sm_last_byte_addressed_read_event_5  0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_full_5         0x00020000U
#define SRT_NX5_sm_last_byte_addressed_buf_full_5         17
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_full_5    0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_nr_5           0x000c0000U
#define SRT_NX5_sm_last_byte_addressed_buf_nr_5           18
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_nr_5      0x00000000U
#define MSK_NX5_sm_last_byte_addressed_write_event_6      0x00100000U
#define SRT_NX5_sm_last_byte_addressed_write_event_6      20
#define DFLT_VAL_NX5_sm_last_byte_addressed_write_event_6 0x00000000U
#define MSK_NX5_sm_last_byte_addressed_read_event_6       0x00200000U
#define SRT_NX5_sm_last_byte_addressed_read_event_6       21
#define DFLT_VAL_NX5_sm_last_byte_addressed_read_event_6  0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_full_6         0x00800000U
#define SRT_NX5_sm_last_byte_addressed_buf_full_6         23
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_full_6    0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_nr_6           0x03000000U
#define SRT_NX5_sm_last_byte_addressed_buf_nr_6           24
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_nr_6      0x00000000U
#define MSK_NX5_sm_last_byte_addressed_write_event_7      0x04000000U
#define SRT_NX5_sm_last_byte_addressed_write_event_7      26
#define DFLT_VAL_NX5_sm_last_byte_addressed_write_event_7 0x00000000U
#define MSK_NX5_sm_last_byte_addressed_read_event_7       0x08000000U
#define SRT_NX5_sm_last_byte_addressed_read_event_7       27
#define DFLT_VAL_NX5_sm_last_byte_addressed_read_event_7  0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_full_7         0x20000000U
#define SRT_NX5_sm_last_byte_addressed_buf_full_7         29
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_full_7    0x00000000U
#define MSK_NX5_sm_last_byte_addressed_buf_nr_7           0xc0000000U
#define SRT_NX5_sm_last_byte_addressed_buf_nr_7           30
#define DFLT_VAL_NX5_sm_last_byte_addressed_buf_nr_7      0x00000000U

enum {
	BFW_NX5_sm_last_byte_addressed_lba_0         = 1, /* [0] */
	BFW_NX5_sm_last_byte_addressed_lba_1         = 1, /* [1] */
	BFW_NX5_sm_last_byte_addressed_lba_2         = 1, /* [2] */
	BFW_NX5_sm_last_byte_addressed_lba_3         = 1, /* [3] */
	BFW_NX5_sm_last_byte_addressed_lba_4         = 1, /* [4] */
	BFW_NX5_sm_last_byte_addressed_lba_5         = 1, /* [5] */
	BFW_NX5_sm_last_byte_addressed_lba_6         = 1, /* [6] */
	BFW_NX5_sm_last_byte_addressed_lba_7         = 1, /* [7] */
	BFW_NX5_sm_last_byte_addressed_write_event_4 = 1, /* [8] */
	BFW_NX5_sm_last_byte_addressed_read_event_4  = 1, /* [9] */
	BFW_NX5_sm_last_byte_addressed_reserved1     = 1, /* [10] */
	BFW_NX5_sm_last_byte_addressed_buf_full_4    = 1, /* [11] */
	BFW_NX5_sm_last_byte_addressed_buf_nr_4      = 2, /* [13:12] */
	BFW_NX5_sm_last_byte_addressed_write_event_5 = 1, /* [14] */
	BFW_NX5_sm_last_byte_addressed_read_event_5  = 1, /* [15] */
	BFW_NX5_sm_last_byte_addressed_reserved2     = 1, /* [16] */
	BFW_NX5_sm_last_byte_addressed_buf_full_5    = 1, /* [17] */
	BFW_NX5_sm_last_byte_addressed_buf_nr_5      = 2, /* [19:18] */
	BFW_NX5_sm_last_byte_addressed_write_event_6 = 1, /* [20] */
	BFW_NX5_sm_last_byte_addressed_read_event_6  = 1, /* [21] */
	BFW_NX5_sm_last_byte_addressed_reserved3     = 1, /* [22] */
	BFW_NX5_sm_last_byte_addressed_buf_full_6    = 1, /* [23] */
	BFW_NX5_sm_last_byte_addressed_buf_nr_6      = 2, /* [25:24] */
	BFW_NX5_sm_last_byte_addressed_write_event_7 = 1, /* [26] */
	BFW_NX5_sm_last_byte_addressed_read_event_7  = 1, /* [27] */
	BFW_NX5_sm_last_byte_addressed_reserved4     = 1, /* [28] */
	BFW_NX5_sm_last_byte_addressed_buf_full_7    = 1, /* [29] */
	BFW_NX5_sm_last_byte_addressed_buf_nr_7      = 2  /* [31:30] */
};

typedef struct NX5_SM_LAST_BYTE_ADDRESSED_BIT_Ttag {
	unsigned int lba_0         : BFW_NX5_sm_last_byte_addressed_lba_0;         /* SM0 matches last byte of its address area         */
	unsigned int lba_1         : BFW_NX5_sm_last_byte_addressed_lba_1;         /* SM1 matches last byte of its address area         */
	unsigned int lba_2         : BFW_NX5_sm_last_byte_addressed_lba_2;         /* SM2 matches last byte of its address area         */
	unsigned int lba_3         : BFW_NX5_sm_last_byte_addressed_lba_3;         /* SM3 matches last byte of its address area         */
	unsigned int lba_4         : BFW_NX5_sm_last_byte_addressed_lba_4;         /* SM4 matches last byte of its address area         */
	unsigned int lba_5         : BFW_NX5_sm_last_byte_addressed_lba_5;         /* SM5 matches last byte of its address area         */
	unsigned int lba_6         : BFW_NX5_sm_last_byte_addressed_lba_6;         /* SM6 matches last byte of its address area         */
	unsigned int lba_7         : BFW_NX5_sm_last_byte_addressed_lba_7;         /* SM7 matches last byte of its address area         */
	unsigned int write_event_4 : BFW_NX5_sm_last_byte_addressed_write_event_4; /* read only version of sm_write_event.write_event_4 */
	unsigned int read_event_4  : BFW_NX5_sm_last_byte_addressed_read_event_4;  /* read only version of sm_read_event.read_event_4   */
	unsigned int reserved1     : BFW_NX5_sm_last_byte_addressed_reserved1;     /* reserved                                          */
	unsigned int buf_full_4    : BFW_NX5_sm_last_byte_addressed_buf_full_4;    /* read only version of sm_buf_statcfg.buf_full_4    */
	unsigned int buf_nr_4      : BFW_NX5_sm_last_byte_addressed_buf_nr_4;      /* read only version of sm_buf_statcfg.buf_nr_4      */
	unsigned int write_event_5 : BFW_NX5_sm_last_byte_addressed_write_event_5; /* read only version of sm_write_event.write_event_5 */
	unsigned int read_event_5  : BFW_NX5_sm_last_byte_addressed_read_event_5;  /* read only version of sm_read_event.read_event_5   */
	unsigned int reserved2     : BFW_NX5_sm_last_byte_addressed_reserved2;     /* reserved                                          */
	unsigned int buf_full_5    : BFW_NX5_sm_last_byte_addressed_buf_full_5;    /* read only version of sm_buf_statcfg.buf_full_5    */
	unsigned int buf_nr_5      : BFW_NX5_sm_last_byte_addressed_buf_nr_5;      /* read only version of sm_buf_statcfg.buf_nr_5      */
	unsigned int write_event_6 : BFW_NX5_sm_last_byte_addressed_write_event_6; /* read only version of sm_write_event.write_event_6 */
	unsigned int read_event_6  : BFW_NX5_sm_last_byte_addressed_read_event_6;  /* read only version of sm_read_event.read_event_6   */
	unsigned int reserved3     : BFW_NX5_sm_last_byte_addressed_reserved3;     /* reserved                                          */
	unsigned int buf_full_6    : BFW_NX5_sm_last_byte_addressed_buf_full_6;    /* read only version of sm_buf_statcfg.buf_full_6    */
	unsigned int buf_nr_6      : BFW_NX5_sm_last_byte_addressed_buf_nr_6;      /* read only version of sm_buf_statcfg.buf_nr_6      */
	unsigned int write_event_7 : BFW_NX5_sm_last_byte_addressed_write_event_7; /* read only version of sm_write_event.write_event_7 */
	unsigned int read_event_7  : BFW_NX5_sm_last_byte_addressed_read_event_7;  /* read only version of sm_read_event.read_event_7   */
	unsigned int reserved4     : BFW_NX5_sm_last_byte_addressed_reserved4;     /* reserved                                          */
	unsigned int buf_full_7    : BFW_NX5_sm_last_byte_addressed_buf_full_7;    /* read only version of sm_buf_statcfg.buf_full_7    */
	unsigned int buf_nr_7      : BFW_NX5_sm_last_byte_addressed_buf_nr_7;      /* read only version of sm_buf_statcfg.buf_nr_7      */
} NX5_SM_LAST_BYTE_ADDRESSED_BIT_T;

typedef union {
	unsigned int                     val;
	NX5_SM_LAST_BYTE_ADDRESSED_BIT_T bf;
} NX5_SM_LAST_BYTE_ADDRESSED_T;

/* --------------------------------------------------------------------- */
/* Register sm_served */
/* => Served status bits of all SM, process channel: */
/*    Set by HW, if SM gives write_allowed or read_allowed. */
/*    Reset by SW (xPEC or ARM), by writing 1 on appropriate bit (usually after FCSok/fail). */
/*    Read/Write access by xPEC at adr_xpec_sr15 */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_sm_served    0x0000013CU
#define Adr_NX5_fmmusm_sm_served 0x018E553CU
#define Adr_NX5_sm_served        0x018E553CU
#define DFLT_VAL_NX5_sm_served   0x00000000U

#define MSK_NX5_sm_served_srvd_0                    0x00000001U
#define SRT_NX5_sm_served_srvd_0                    0
#define DFLT_VAL_NX5_sm_served_srvd_0               0x00000000U
#define MSK_NX5_sm_served_srvd_1                    0x00000002U
#define SRT_NX5_sm_served_srvd_1                    1
#define DFLT_VAL_NX5_sm_served_srvd_1               0x00000000U
#define MSK_NX5_sm_served_srvd_2                    0x00000004U
#define SRT_NX5_sm_served_srvd_2                    2
#define DFLT_VAL_NX5_sm_served_srvd_2               0x00000000U
#define MSK_NX5_sm_served_srvd_3                    0x00000008U
#define SRT_NX5_sm_served_srvd_3                    3
#define DFLT_VAL_NX5_sm_served_srvd_3               0x00000000U
#define MSK_NX5_sm_served_srvd_4                    0x00000010U
#define SRT_NX5_sm_served_srvd_4                    4
#define DFLT_VAL_NX5_sm_served_srvd_4               0x00000000U
#define MSK_NX5_sm_served_srvd_5                    0x00000020U
#define SRT_NX5_sm_served_srvd_5                    5
#define DFLT_VAL_NX5_sm_served_srvd_5               0x00000000U
#define MSK_NX5_sm_served_srvd_6                    0x00000040U
#define SRT_NX5_sm_served_srvd_6                    6
#define DFLT_VAL_NX5_sm_served_srvd_6               0x00000000U
#define MSK_NX5_sm_served_srvd_7                    0x00000080U
#define SRT_NX5_sm_served_srvd_7                    7
#define DFLT_VAL_NX5_sm_served_srvd_7               0x00000000U
#define MSK_NX5_sm_served_any_proc_read_match       0x00000100U
#define SRT_NX5_sm_served_any_proc_read_match       8
#define DFLT_VAL_NX5_sm_served_any_proc_read_match  0x00000000U
#define MSK_NX5_sm_served_any_proc_write_match      0x00000200U
#define SRT_NX5_sm_served_any_proc_write_match      9
#define DFLT_VAL_NX5_sm_served_any_proc_write_match 0x00000000U

enum {
	BFW_NX5_sm_served_srvd_0               = 1,  /* [0] */
	BFW_NX5_sm_served_srvd_1               = 1,  /* [1] */
	BFW_NX5_sm_served_srvd_2               = 1,  /* [2] */
	BFW_NX5_sm_served_srvd_3               = 1,  /* [3] */
	BFW_NX5_sm_served_srvd_4               = 1,  /* [4] */
	BFW_NX5_sm_served_srvd_5               = 1,  /* [5] */
	BFW_NX5_sm_served_srvd_6               = 1,  /* [6] */
	BFW_NX5_sm_served_srvd_7               = 1,  /* [7] */
	BFW_NX5_sm_served_any_proc_read_match  = 1,  /* [8] */
	BFW_NX5_sm_served_any_proc_write_match = 1,  /* [9] */
	BFW_NX5_sm_served_reserved1            = 22  /* [31:10] */
};

typedef struct NX5_SM_SERVED_BIT_Ttag {
	unsigned int srvd_0               : BFW_NX5_sm_served_srvd_0;               /* SM0 address area was read or write accessed by xPEC                                */
	unsigned int srvd_1               : BFW_NX5_sm_served_srvd_1;               /* SM1 address area was read or write accessed by xPEC                                */
	unsigned int srvd_2               : BFW_NX5_sm_served_srvd_2;               /* SM2 address area was read or write accessed by xPEC                                */
	unsigned int srvd_3               : BFW_NX5_sm_served_srvd_3;               /* SM3 address area was read or write accessed by xPEC                                */
	unsigned int srvd_4               : BFW_NX5_sm_served_srvd_4;               /* SM4 address area was read or write accessed by xPEC                                */
	unsigned int srvd_5               : BFW_NX5_sm_served_srvd_5;               /* SM5 address area was read or write accessed by xPEC                                */
	unsigned int srvd_6               : BFW_NX5_sm_served_srvd_6;               /* SM6 address area was read or write accessed by xPEC                                */
	unsigned int srvd_7               : BFW_NX5_sm_served_srvd_7;               /* SM7 address area was read or write accessed by xPEC                                */
	unsigned int any_proc_read_match  : BFW_NX5_sm_served_any_proc_read_match;  /* Any read access was allowed, i.e. any SM matched for read or direct read access    */
	unsigned int any_proc_write_match : BFW_NX5_sm_served_any_proc_write_match; /* Any write access was allowed, i.e. any SM matched for write or direct write access */
	unsigned int reserved1            : BFW_NX5_sm_served_reserved1;            /* reserved                                                                           */
} NX5_SM_SERVED_BIT_T;

typedef union {
	unsigned int        val;
	NX5_SM_SERVED_BIT_T bf;
} NX5_SM_SERVED_T;


/* ===================================================================== */

/* Area of buf_man */

/* ===================================================================== */

#define Addr_NX5_buf_man      0x018E5600U
#define NX5_NETX_BUF_MAN_AREA 0x018E5600U

/* --------------------------------------------------------------------- */
/* Register buf_man_xpec0 */
/* => BMU port of 1st master (xPEC0): */
/*    This register address allows to access 16 buffer controllers, where each one handles buffer numbers (0..3) between up */
/*    to three processors. Due to the complex functionality in one register address, bits have different meaning depending on */
/*    request type and mode. */
/*    Getting a new buffer always happens with two command accesses: */
/*    1st: Write access: Tell the buf_manager the channel(s) (0..15) and whether you request read or write buffer. */
/*         Wait for two clock cycles, until new buffer number is calculated after any write access. */
/*    2nd: Read access: Read the buffer number (0..3). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_buf_man_xpec0     0x00000000U
#define Adr_NX5_buf_man_buf_man_xpec0 0x018E5600U
#define Adr_NX5_buf_man_xpec0         0x018E5600U
#define DFLT_VAL_NX5_buf_man_xpec0    0x00000007U

#define MSK_NX5_buf_man_xpec0_buf_nr              0x0000000fU
#define SRT_NX5_buf_man_xpec0_buf_nr              0
#define DFLT_VAL_NX5_buf_man_xpec0_buf_nr         0x00000007U
#define MSK_NX5_buf_man_xpec0_req_type            0x00000060U
#define SRT_NX5_buf_man_xpec0_req_type            5
#define DFLT_VAL_NX5_buf_man_xpec0_req_type       0x00000000U
#define MSK_NX5_buf_man_xpec0_semaphore_mode      0x00000080U
#define SRT_NX5_buf_man_xpec0_semaphore_mode      7
#define DFLT_VAL_NX5_buf_man_xpec0_semaphore_mode 0x00000000U
#define MSK_NX5_buf_man_xpec0_parallel_mode       0x00000100U
#define SRT_NX5_buf_man_xpec0_parallel_mode       8
#define DFLT_VAL_NX5_buf_man_xpec0_parallel_mode  0x00000000U
#define MSK_NX5_buf_man_xpec0_reset               0x00000200U
#define SRT_NX5_buf_man_xpec0_reset               9
#define DFLT_VAL_NX5_buf_man_xpec0_reset          0x00000000U
#define MSK_NX5_buf_man_xpec0_sm_update_en        0x00000400U
#define SRT_NX5_buf_man_xpec0_sm_update_en        10
#define DFLT_VAL_NX5_buf_man_xpec0_sm_update_en   0x00000000U
#define MSK_NX5_buf_man_xpec0_sm_update_dis       0x00000800U
#define SRT_NX5_buf_man_xpec0_sm_update_dis       11
#define DFLT_VAL_NX5_buf_man_xpec0_sm_update_dis  0x00000000U

enum {
	BFW_NX5_buf_man_xpec0_buf_nr         = 4,  /* [3:0] */
	BFW_NX5_buf_man_xpec0_reserved1      = 1,  /* [4] */
	BFW_NX5_buf_man_xpec0_req_type       = 2,  /* [6:5] */
	BFW_NX5_buf_man_xpec0_semaphore_mode = 1,  /* [7] */
	BFW_NX5_buf_man_xpec0_parallel_mode  = 1,  /* [8] */
	BFW_NX5_buf_man_xpec0_reset          = 1,  /* [9] */
	BFW_NX5_buf_man_xpec0_sm_update_en   = 1,  /* [10] */
	BFW_NX5_buf_man_xpec0_sm_update_dis  = 1,  /* [11] */
	BFW_NX5_buf_man_xpec0_reserved2      = 20  /* [31:12] */
};

typedef struct NX5_BUF_MAN_XPEC0_BIT_Ttag {
	unsigned int buf_nr         : BFW_NX5_buf_man_xpec0_buf_nr;         /* Write access: number of buf_manager controller (0..15)                                           */
	                                                                    /* Read access:  number of buffer (0..m+1), where m is the number of masters using this buf_manager */
	unsigned int reserved1      : BFW_NX5_buf_man_xpec0_reserved1;      /* reserved                                                                                         */
	unsigned int req_type       : BFW_NX5_buf_man_xpec0_req_type;       /* Request type bits are write-only:                                                                */
	                                                                    /* 00: request read buffer (or semaphore)                                                           */
	unsigned int semaphore_mode : BFW_NX5_buf_man_xpec0_semaphore_mode; /* Activate 'semaphore mode' for this buf_nr by writing 1 to this bit.                              */
	                                                                    /* To return from semaphore-mode reset this channel.                                                */
	unsigned int parallel_mode  : BFW_NX5_buf_man_xpec0_parallel_mode;  /* Activate parallel mode by writing 1 to this bit (other bits are ignored).                        */
	                                                                    /* To return to normal mode, write 0xffff0000 to this register.                                     */
	unsigned int reset          : BFW_NX5_buf_man_xpec0_reset;          /* Reset channel.                                                                                   */
	unsigned int sm_update_en   : BFW_NX5_buf_man_xpec0_sm_update_en;   /* Activate SM_auto_update mode by writing 1 to this bit:                                           */
	                                                                    /* In SM_auto_update mode the requested buffer numbers of buffer managers 0..7 will automatically   */
	unsigned int sm_update_dis  : BFW_NX5_buf_man_xpec0_sm_update_dis;  /* De-activate SM_auto_update mode by writing 1 to this bit.                                        */
	unsigned int reserved2      : BFW_NX5_buf_man_xpec0_reserved2;      /* reserved                                                                                         */
} NX5_BUF_MAN_XPEC0_BIT_T;

typedef union {
	unsigned int            val;
	NX5_BUF_MAN_XPEC0_BIT_T bf;
} NX5_BUF_MAN_XPEC0_T;

/* --------------------------------------------------------------------- */
/* Register buf_man_xpec1 */
/* => BMU port of 2nd master (xPEC1): */
/*    This register address allows to access 16 buffer controllers, where each one handles buffer numbers (0..3) between up */
/*    to three processors. Due to the complex functionality in one register address, bits have different meaning depending on */
/*    request type and mode. */
/*    Getting a new buffer always happens with two command accesses: */
/*    1st: Write access: Tell the buf_manager the channel(s) (0..15) and whether you request read or write buffer. */
/*         Wait for two clock cycles, until new buffer number is calculated after any write access. */
/*    2nd: Read access: Read the buffer number (0..4). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_buf_man_xpec1     0x00000004U
#define Adr_NX5_buf_man_buf_man_xpec1 0x018E5604U
#define Adr_NX5_buf_man_xpec1         0x018E5604U
#define DFLT_VAL_NX5_buf_man_xpec1    0x00000007U

#define MSK_NX5_buf_man_xpec1_buf_nr              0x0000000fU
#define SRT_NX5_buf_man_xpec1_buf_nr              0
#define DFLT_VAL_NX5_buf_man_xpec1_buf_nr         0x00000007U
#define MSK_NX5_buf_man_xpec1_req_type            0x00000060U
#define SRT_NX5_buf_man_xpec1_req_type            5
#define DFLT_VAL_NX5_buf_man_xpec1_req_type       0x00000000U
#define MSK_NX5_buf_man_xpec1_semaphore_mode      0x00000080U
#define SRT_NX5_buf_man_xpec1_semaphore_mode      7
#define DFLT_VAL_NX5_buf_man_xpec1_semaphore_mode 0x00000000U
#define MSK_NX5_buf_man_xpec1_parallel_mode       0x00000100U
#define SRT_NX5_buf_man_xpec1_parallel_mode       8
#define DFLT_VAL_NX5_buf_man_xpec1_parallel_mode  0x00000000U
#define MSK_NX5_buf_man_xpec1_reset               0x00000200U
#define SRT_NX5_buf_man_xpec1_reset               9
#define DFLT_VAL_NX5_buf_man_xpec1_reset          0x00000000U
#define MSK_NX5_buf_man_xpec1_sm_update_en        0x00000400U
#define SRT_NX5_buf_man_xpec1_sm_update_en        10
#define DFLT_VAL_NX5_buf_man_xpec1_sm_update_en   0x00000000U
#define MSK_NX5_buf_man_xpec1_sm_update_dis       0x00000800U
#define SRT_NX5_buf_man_xpec1_sm_update_dis       11
#define DFLT_VAL_NX5_buf_man_xpec1_sm_update_dis  0x00000000U

enum {
	BFW_NX5_buf_man_xpec1_buf_nr         = 4,  /* [3:0] */
	BFW_NX5_buf_man_xpec1_reserved1      = 1,  /* [4] */
	BFW_NX5_buf_man_xpec1_req_type       = 2,  /* [6:5] */
	BFW_NX5_buf_man_xpec1_semaphore_mode = 1,  /* [7] */
	BFW_NX5_buf_man_xpec1_parallel_mode  = 1,  /* [8] */
	BFW_NX5_buf_man_xpec1_reset          = 1,  /* [9] */
	BFW_NX5_buf_man_xpec1_sm_update_en   = 1,  /* [10] */
	BFW_NX5_buf_man_xpec1_sm_update_dis  = 1,  /* [11] */
	BFW_NX5_buf_man_xpec1_reserved2      = 20  /* [31:12] */
};

typedef struct NX5_BUF_MAN_XPEC1_BIT_Ttag {
	unsigned int buf_nr         : BFW_NX5_buf_man_xpec1_buf_nr;         /* Write access: number of buf_manager controller (0..15)                                           */
	                                                                    /* Read access:  number of buffer (0..m+1), where m is the number of masters using this buf_manager */
	unsigned int reserved1      : BFW_NX5_buf_man_xpec1_reserved1;      /* reserved                                                                                         */
	unsigned int req_type       : BFW_NX5_buf_man_xpec1_req_type;       /* Request type bits are write-only:                                                                */
	                                                                    /* 00: request read buffer (or semaphore)                                                           */
	unsigned int semaphore_mode : BFW_NX5_buf_man_xpec1_semaphore_mode; /* Activate 'semaphore mode' for this buf_nr by writing 1 to this bit.                              */
	                                                                    /* To return from semaphore-mode reset this channel.                                                */
	unsigned int parallel_mode  : BFW_NX5_buf_man_xpec1_parallel_mode;  /* Activate parallel mode by writing 1 to this bit (other bits are ignored).                        */
	                                                                    /* To return to normal mode, write 0xffff0000 to this register.                                     */
	unsigned int reset          : BFW_NX5_buf_man_xpec1_reset;          /* Reset channel.                                                                                   */
	unsigned int sm_update_en   : BFW_NX5_buf_man_xpec1_sm_update_en;   /* Activate SM_auto_update mode by writing 1 to this bit:                                           */
	                                                                    /* In SM_auto_update mode the requested buffer numbers of buffer managers 0..7 will automatically   */
	unsigned int sm_update_dis  : BFW_NX5_buf_man_xpec1_sm_update_dis;  /* De-activate SM_auto_update mode by writing 1 to this bit.                                        */
	unsigned int reserved2      : BFW_NX5_buf_man_xpec1_reserved2;      /* reserved                                                                                         */
} NX5_BUF_MAN_XPEC1_BIT_T;

typedef union {
	unsigned int            val;
	NX5_BUF_MAN_XPEC1_BIT_T bf;
} NX5_BUF_MAN_XPEC1_T;

/* --------------------------------------------------------------------- */
/* Register buf_man_dpm */
/* => BMU-port of 3rd master (DPM): */
/*    This register address allows to access 16 buffer controllers, where each one handles buffer numbers (0..3) between up */
/*    to three processors. Due to the complex functionality in one register address, bits have different meaning depending on */
/*    request type and mode. */
/*    Getting a new buffer always happens with two command accesses: */
/*    1st: Write access: Tell the buf_manager the channel(s) (0..15) and whether you request read or write buffer. */
/*         Wait for two clock cycles, until new buffer number is calculated after any write access. */
/*    2nd: Read access: Read the buffer number (0..3). */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_buf_man_dpm     0x00000008U
#define Adr_NX5_buf_man_buf_man_dpm 0x018E5608U
#define Adr_NX5_buf_man_dpm         0x018E5608U
#define DFLT_VAL_NX5_buf_man_dpm    0x00000007U

#define MSK_NX5_buf_man_dpm_buf_nr              0x0000000fU
#define SRT_NX5_buf_man_dpm_buf_nr              0
#define DFLT_VAL_NX5_buf_man_dpm_buf_nr         0x00000007U
#define MSK_NX5_buf_man_dpm_req_type            0x00000060U
#define SRT_NX5_buf_man_dpm_req_type            5
#define DFLT_VAL_NX5_buf_man_dpm_req_type       0x00000000U
#define MSK_NX5_buf_man_dpm_semaphore_mode      0x00000080U
#define SRT_NX5_buf_man_dpm_semaphore_mode      7
#define DFLT_VAL_NX5_buf_man_dpm_semaphore_mode 0x00000000U
#define MSK_NX5_buf_man_dpm_parallel_mode       0x00000100U
#define SRT_NX5_buf_man_dpm_parallel_mode       8
#define DFLT_VAL_NX5_buf_man_dpm_parallel_mode  0x00000000U
#define MSK_NX5_buf_man_dpm_reset               0x00000200U
#define SRT_NX5_buf_man_dpm_reset               9
#define DFLT_VAL_NX5_buf_man_dpm_reset          0x00000000U

enum {
	BFW_NX5_buf_man_dpm_buf_nr         = 4,  /* [3:0] */
	BFW_NX5_buf_man_dpm_reserved1      = 1,  /* [4] */
	BFW_NX5_buf_man_dpm_req_type       = 2,  /* [6:5] */
	BFW_NX5_buf_man_dpm_semaphore_mode = 1,  /* [7] */
	BFW_NX5_buf_man_dpm_parallel_mode  = 1,  /* [8] */
	BFW_NX5_buf_man_dpm_reset          = 1,  /* [9] */
	BFW_NX5_buf_man_dpm_reserved2      = 22  /* [31:10] */
};

typedef struct NX5_BUF_MAN_DPM_BIT_Ttag {
	unsigned int buf_nr         : BFW_NX5_buf_man_dpm_buf_nr;         /* Write access: number of buf_manager controller (0..15)                                           */
	                                                                  /* Read access:  number of buffer (0..m+1), where m is the number of masters using this buf_manager */
	unsigned int reserved1      : BFW_NX5_buf_man_dpm_reserved1;      /* reserved                                                                                         */
	unsigned int req_type       : BFW_NX5_buf_man_dpm_req_type;       /* Request type bits are write-only:                                                                */
	                                                                  /* 00: request read buffer (or semaphore)                                                           */
	unsigned int semaphore_mode : BFW_NX5_buf_man_dpm_semaphore_mode; /* Activate 'semaphore mode' for this buf_nr by writing 1 to this bit.                              */
	                                                                  /* To return from semaphore-mode reset this channel.                                                */
	unsigned int parallel_mode  : BFW_NX5_buf_man_dpm_parallel_mode;  /* Activate parallel mode by writing 1 to this bit (other bits are ignored).                        */
	                                                                  /* To return to normal mode, write 0xffff0000 to this register.                                     */
	unsigned int reset          : BFW_NX5_buf_man_dpm_reset;          /* Reset channel.                                                                                   */
	unsigned int reserved2      : BFW_NX5_buf_man_dpm_reserved2;      /* reserved                                                                                         */
} NX5_BUF_MAN_DPM_BIT_T;

typedef union {
	unsigned int          val;
	NX5_BUF_MAN_DPM_BIT_T bf;
} NX5_BUF_MAN_DPM_T;


/* ===================================================================== */

/* Area of intlogic_mirror_hi */

/* ===================================================================== */

#define Addr_NX5_intlogic_mirror_hi 0xFF800000U

/* ===================================================================== */

/* AREA xc_extbus_sel */
/* Area of  */

/* ===================================================================== */


/* --------------------------------------------------------------------- */
/* Register xc_extbus_sel_ctrl */
/* => External XC-bus-selection register - FPGA/EVA-Board version only!!! */
/*    Bus coding: */
/*    0000 : PHY1 */
/*    0001 : PHY2 */
/*    0010 : MMC */
/*    0011 : ProfiBus */
/*    0100 : CAN */
/*    0101 : ASI */
/*    1111 : nothing selected */
/*    Each XC-block can be assigned to one of these busses by setting the according bit-arear to the */
/*    value, the bus is coded with. */
/*    NO bus MUST be assigned to more than one XC-Block! */
/* => Mode: R/W */
/* --------------------------------------------------------------------- */

#define REL_Adr_NX5_xc_extbus_sel_ctrl  0x00000000U
#define DFLT_VAL_NX5_xc_extbus_sel_ctrl 0x00003210U

#define MSK_NX5_xc_extbus_sel_ctrl_xmac0_sel      0x0000000fU
#define SRT_NX5_xc_extbus_sel_ctrl_xmac0_sel      0
#define DFLT_VAL_NX5_xc_extbus_sel_ctrl_xmac0_sel 0x00000000U
#define MSK_NX5_xc_extbus_sel_ctrl_xmac1_sel      0x000000f0U
#define SRT_NX5_xc_extbus_sel_ctrl_xmac1_sel      4
#define DFLT_VAL_NX5_xc_extbus_sel_ctrl_xmac1_sel 0x00000010U
#define MSK_NX5_xc_extbus_sel_ctrl_xmac2_sel      0x00000f00U
#define SRT_NX5_xc_extbus_sel_ctrl_xmac2_sel      8
#define DFLT_VAL_NX5_xc_extbus_sel_ctrl_xmac2_sel 0x00000200U
#define MSK_NX5_xc_extbus_sel_ctrl_xmac3_sel      0x0000f000U
#define SRT_NX5_xc_extbus_sel_ctrl_xmac3_sel      12
#define DFLT_VAL_NX5_xc_extbus_sel_ctrl_xmac3_sel 0x00003000U

enum {
	BFW_NX5_xc_extbus_sel_ctrl_xmac0_sel = 4,  /* [3:0] */
	BFW_NX5_xc_extbus_sel_ctrl_xmac1_sel = 4,  /* [7:4] */
	BFW_NX5_xc_extbus_sel_ctrl_xmac2_sel = 4,  /* [11:8] */
	BFW_NX5_xc_extbus_sel_ctrl_xmac3_sel = 4,  /* [15:12] */
	BFW_NX5_xc_extbus_sel_ctrl_reserved1 = 16  /* [31:16] */
};

typedef struct NX5_XC_EXTBUS_SEL_CTRL_BIT_Ttag {
	unsigned int xmac0_sel : BFW_NX5_xc_extbus_sel_ctrl_xmac0_sel; /* selects the external bus, assigned to xMAC0 (default PHY1)     */
	unsigned int xmac1_sel : BFW_NX5_xc_extbus_sel_ctrl_xmac1_sel; /* selects the external bus, assigned to xMAC1 (default PHY2)     */
	unsigned int xmac2_sel : BFW_NX5_xc_extbus_sel_ctrl_xmac2_sel; /* selects the external bus, assigned to xMAC2 (default MMC)      */
	unsigned int xmac3_sel : BFW_NX5_xc_extbus_sel_ctrl_xmac3_sel; /* selects the external bus, assigned to xMAC3 (default ProfiBus) */
	unsigned int reserved1 : BFW_NX5_xc_extbus_sel_ctrl_reserved1; /* reserved                                                       */
} NX5_XC_EXTBUS_SEL_CTRL_BIT_T;

typedef union {
	unsigned int                 val;
	NX5_XC_EXTBUS_SEL_CTRL_BIT_T bf;
} NX5_XC_EXTBUS_SEL_CTRL_T;




/*********************************************************************/
/* area structure definitions                                        */
/*********************************************************************/


typedef struct NX5_ASIC_CTRL_AREA_Ttag
{
  volatile unsigned long  ulIo_status;
  volatile unsigned long  ulIo_config;
  volatile unsigned long aulReserved0[1];
  volatile unsigned long  ulReset_ctrl;
  volatile unsigned long aulReserved1[1];
  volatile unsigned long  ulArmclk_rate_mul_add;
  volatile unsigned long aulReserved2[1];
  volatile unsigned long aulFbclk_rate_mul_add[2];
  volatile unsigned long  ulClock_enable;
  volatile unsigned long aulReserved3[2];
  volatile unsigned long  ulOnly_porn;
  volatile unsigned long  ulNetx_version;
  volatile unsigned long  ulDpm_wdg;
  volatile unsigned long aulReserved4[1];
  volatile unsigned long  ulTrigger_boot_dma;
  volatile unsigned long aulReserved5[11];
  volatile unsigned long  ulAsic_ctrl_access_key;
  volatile unsigned long aulNetx_lock_reserved[2];
  volatile unsigned long aulReserved6[1];
  volatile unsigned long  ulNetx_lock_reserved_start;
  volatile unsigned long aulReserved7[30];
  volatile unsigned long  ulNetx_lock_reserved_end;
} NX5_ASIC_CTRL_AREA_T;

typedef struct NX5_ZPU_AREA_Ttag
{
  volatile unsigned long  ulZpu_counter;
  volatile unsigned long  ulZpu_irq_raw;
  volatile unsigned long  ulZpu_irq_masked;
  volatile unsigned long  ulZpu_irq_mask_set;
  volatile unsigned long  ulZpu_irq_mask_rst;
  volatile unsigned long  ulZpu_irq_vector;
  volatile unsigned long  ulZpu_emulate_offset;
  volatile unsigned long  ulZpu_pc;
  volatile unsigned long  ulZpu_sp;
  volatile unsigned long  ulZpu_status;
  volatile unsigned long  ulZpu_ctrl;
} NX5_ZPU_AREA_T;

typedef struct NX5_PIO_AREA_Ttag
{
  volatile unsigned long  ulPio_in;
  volatile unsigned long  ulPio_out;
  volatile unsigned long  ulPio_oe;
} NX5_PIO_AREA_T;

typedef struct NX5_MIIMU_AREA_Ttag
{
  volatile unsigned long  ulMiimu_reg;
  volatile unsigned long  ulMiimu_sw_en;
  volatile unsigned long  ulMiimu_sw_mdc;
  volatile unsigned long  ulMiimu_sw_mdo;
  volatile unsigned long  ulMiimu_sw_mdoe;
  volatile unsigned long  ulMiimu_sw_mdi;
} NX5_MIIMU_AREA_T;

typedef struct NX5_SPI_AREA_Ttag
{
  volatile unsigned long aulSpi_cr[2];
  volatile unsigned long  ulSpi_dr;
  volatile unsigned long  ulSpi_sr;
  volatile unsigned long  ulSpi_cpsr;
  volatile unsigned long  ulSpi_imsc;
  volatile unsigned long  ulSpi_ris;
  volatile unsigned long  ulSpi_mis;
  volatile unsigned long  ulSpi_icr;
  volatile unsigned long  ulSpi_dmacr;
  volatile unsigned long aulReserved0[2];
  volatile unsigned long  ulSpi_data_register;
  volatile unsigned long  ulSpi_status_register;
  volatile unsigned long  ulSpi_control_register;
  volatile unsigned long  ulSpi_interrupt_control_register;
} NX5_SPI_AREA_T;

typedef struct NX5_SYSTIME_AREA_Ttag
{
  volatile unsigned long  ulSystime_ns;
  volatile unsigned long  ulSystime_s;
  volatile unsigned long  ulSystime_border;
  volatile unsigned long  ulSystime_count_value;
  volatile unsigned long  ulSystime_s_compare_value;
  volatile unsigned long  ulSystime_s_compare_enable;
  volatile unsigned long  ulSystime_s_compare_irq;
} NX5_SYSTIME_AREA_T;

typedef struct NX5_DPM_AREA_Ttag
{
  volatile unsigned long  ulDpm_cfg0x0;
  volatile unsigned long aulReserved0[3];
  volatile unsigned long  ulDpm_addr_cfg;
  volatile unsigned long  ulDpm_timing_cfg;
  volatile unsigned long  ulDpm_rdy_cfg;
  volatile unsigned long  ulDpm_status;
  volatile unsigned long  ulDpm_status_err_auto_reset;
  volatile unsigned long  ulDpm_status_err_addr;
  volatile unsigned long aulReserved1[6];
  struct
  {
    volatile unsigned long  ulEnd;
    volatile unsigned long  ulMap;
  } asDpm_win[5];
  volatile unsigned long aulReserved2[6];
  volatile unsigned long  ulDpm_irq_raw;
  volatile unsigned long  ulDpm_irq_fiq_mask;
  volatile unsigned long  ulDpm_irq_irq_mask;
  volatile unsigned long  ulDpm_irq_fiq_masked;
  volatile unsigned long  ulDpm_irq_irq_masked;
  volatile unsigned long  ulDpm_fiq_irq_pad_ctrl;
  volatile unsigned long aulReserved3[2];
  volatile unsigned long  ulDpm_io_cfg_misc;
  volatile unsigned long aulReserved4[3];
  volatile unsigned long aulDpm_pio_out[2];
  volatile unsigned long aulDpm_pio_oe[2];
  volatile unsigned long aulDpm_pio_in[2];
  volatile unsigned long aulReserved5[13];
  volatile unsigned long  ulDpm_netx_version;
} NX5_DPM_AREA_T;

typedef struct NX5_XC_AREA_Ttag
{
  volatile unsigned long  ulXc_base;
} NX5_XC_AREA_T;

typedef struct NX5_XPEC_AREA_Ttag
{
  volatile unsigned long aulXpec_r[8];
  volatile unsigned long aulUsr[2];
  volatile unsigned long  ulRange45;
  volatile unsigned long  ulRange67;
  volatile unsigned long aulTimer[4];
  volatile unsigned long  ulUrx_count;
  volatile unsigned long  ulUtx_count;
  volatile unsigned long  ulXpec_pc;
  volatile unsigned long  ulZero;
  volatile unsigned long  ulXpec_statcfg;
  volatile unsigned long  ulEc_maska;
  volatile unsigned long  ulEc_maskb;
  volatile unsigned long aulEc_mask[10];
  volatile unsigned long  ulTimer4;
  volatile unsigned long  ulTimer5;
  volatile unsigned long  ulIrq;
  volatile unsigned long  ulXpec_systime_ns;
  volatile unsigned long  ulFifo_data;
  volatile unsigned long  ulXpec_systime_s;
  volatile unsigned long  ulXpec_adc;
  volatile unsigned long aulXpec_sr[16];
  volatile unsigned long aulStatcfg[4];
  volatile unsigned long aulUrtx[4];
  volatile unsigned long  ulXpu_hold_pc;
  volatile unsigned long aulReserved0[4031];
  volatile unsigned long  ulPram_start;
  volatile unsigned long aulReserved1[2047];
  volatile unsigned long  ulDram_start;
} NX5_XPEC_AREA_T;

typedef struct NX5_XMAC_AREA_Ttag
{
  volatile unsigned long  ulXmac_rpu_program_start;
  volatile unsigned long aulReserved0[254];
  volatile unsigned long  ulXmac_rpu_program_end;
  volatile unsigned long  ulXmac_tpu_program_start;
  volatile unsigned long aulReserved1[254];
  volatile unsigned long  ulXmac_tpu_program_end;
  volatile unsigned long aulXmac_sr[16];
  volatile unsigned long  ulXmac_status_shared0;
  volatile unsigned long  ulXmac_config_shared0;
  volatile unsigned long  ulXmac_status_shared1;
  volatile unsigned long  ulXmac_config_shared1;
  volatile unsigned long aulReserved2[4];
  volatile unsigned long aulXmac_urx_utx[2];
  volatile unsigned long aulReserved3[2];
  volatile unsigned long  ulXmac_urx;
  volatile unsigned long  ulXmac_utx;
  volatile unsigned long  ulXmac_rx;
  volatile unsigned long  ulXmac_other_rx;
  volatile unsigned long  ulXmac_rx_hw;
  volatile unsigned long  ulXmac_rx_hw_count;
  volatile unsigned long  ulXmac_tx;
  volatile unsigned long  ulXmac_tx_hw;
  volatile unsigned long  ulXmac_tx_hw_count;
  volatile unsigned long  ulXmac_tx_sent;
  volatile unsigned long  ulXmac_rpu_pc;
  volatile unsigned long  ulXmac_tpu_pc;
  volatile unsigned long aulXmac_wr[10];
  volatile unsigned long  ulXmac_sys_time;
  volatile unsigned long  ulXmac_sys_time_upper;
  volatile unsigned long aulXmac_cmp_status[4];
  volatile unsigned long  ulXmac_alu_flags;
  volatile unsigned long  ulXmac_status_int;
  volatile unsigned long  ulXmac_stat_bits;
  volatile unsigned long  ulXmac_status_mii;
  volatile unsigned long  ulXmac_status_mii2;
  volatile unsigned long  ulXmac_other_status_mii2;
  volatile unsigned long  ulXmac_config_mii;
  volatile unsigned long  ulXmac_config_rx_nibble_fifo;
  volatile unsigned long  ulXmac_config_tx_nibble_fifo;
  volatile unsigned long  ulXmac_config_sbu;
  volatile unsigned long  ulXmac_sbu_rate_mul_add;
  volatile unsigned long  ulXmac_sbu_rate_mul_start;
  volatile unsigned long  ulXmac_sbu_rate_mul;
  volatile unsigned long  ulXmac_start_sample_pos;
  volatile unsigned long  ulXmac_stop_sample_pos;
  volatile unsigned long  ulXmac_config_obu;
  volatile unsigned long  ulXmac_obu_rate_mul_add;
  volatile unsigned long  ulXmac_obu_rate_mul_start;
  volatile unsigned long  ulXmac_obu_rate_mul;
  volatile unsigned long  ulXmac_start_trans_pos;
  volatile unsigned long  ulXmac_stop_trans_pos;
  volatile unsigned long  ulXmac_rpu_count1;
  volatile unsigned long  ulXmac_rpu_count2;
  volatile unsigned long  ulXmac_tpu_count1;
  volatile unsigned long  ulXmac_tpu_count2;
  volatile unsigned long  ulXmac_rx_count;
  volatile unsigned long  ulXmac_tx_count;
  volatile unsigned long  ulXmac_rpm_mask0;
  volatile unsigned long  ulXmac_rpm_val0;
  volatile unsigned long  ulXmac_rpm_mask1;
  volatile unsigned long  ulXmac_rpm_val1;
  volatile unsigned long  ulXmac_tpm_mask0;
  volatile unsigned long  ulXmac_tpm_val0;
  volatile unsigned long  ulXmac_tpm_mask1;
  volatile unsigned long  ulXmac_tpm_val1;
  volatile unsigned long aulReserved4[20];
  volatile unsigned long  ulXmac_rx_tx_nof_bits;
  volatile unsigned long  ulXmac_rx_crc32_l;
  volatile unsigned long  ulXmac_rx_crc32_h;
  volatile unsigned long  ulXmac_rx_crc32_cfg;
  volatile unsigned long  ulXmac_tx_crc32_l;
  volatile unsigned long  ulXmac_tx_crc32_h;
  volatile unsigned long  ulXmac_tx_crc32_cfg;
  volatile unsigned long  ulXmac_rx_crc_polynomial_l;
  volatile unsigned long  ulXmac_rx_crc_polynomial_h;
  volatile unsigned long  ulXmac_rx_crc_l;
  volatile unsigned long  ulXmac_rx_crc_h;
  volatile unsigned long  ulXmac_rx_crc_cfg;
  volatile unsigned long  ulXmac_tx_crc_polynomial_l;
  volatile unsigned long  ulXmac_tx_crc_polynomial_h;
  volatile unsigned long  ulXmac_tx_crc_l;
  volatile unsigned long  ulXmac_tx_crc_h;
  volatile unsigned long  ulXmac_tx_crc_cfg;
  volatile unsigned long  ulXmac_rpu_hold_pc;
  volatile unsigned long  ulXmac_tpu_hold_pc;
} NX5_XMAC_AREA_T;

typedef struct NX5_POINTER_FIFO_AREA_Ttag
{
  volatile unsigned long  ulPfifo_base;
  volatile unsigned long aulReserved0[31];
  volatile unsigned long  ulPfifo_border_base;
  volatile unsigned long aulReserved1[31];
  volatile unsigned long  ulPfifo_reset;
  volatile unsigned long  ulPfifo_full;
  volatile unsigned long  ulPfifo_empty;
  volatile unsigned long  ulPfifo_overflow;
  volatile unsigned long  ulPfifo_underrun;
  volatile unsigned long aulReserved2[27];
  volatile unsigned long  ulPfifo_fill_level_base;
} NX5_POINTER_FIFO_AREA_T;

typedef struct NX5_XPEC_IRQ_REGISTERS_AREA_Ttag
{
  volatile unsigned long aulIrq_xpec[2];
} NX5_XPEC_IRQ_REGISTERS_AREA_T;

typedef struct NX5_XC_MEM_PROT_AREA_Ttag
{
  volatile unsigned long aulXpec_ram_low[2];
  volatile unsigned long aulReserved0[2];
  volatile unsigned long aulXpec_ram_high[2];
  volatile unsigned long aulReserved1[58];
  volatile unsigned long  ulProt_key_enable;
  volatile unsigned long  ulProt_key_disable;
  volatile unsigned long  ulProt_status;
} NX5_XC_MEM_PROT_AREA_T;

typedef struct NX5_XC_DEBUG_AREA_Ttag
{
  volatile unsigned long  ulXc_debug_config;
} NX5_XC_DEBUG_AREA_T;

typedef struct NX5_TRIGGER_SAMPLE_UNIT_AREA_Ttag
{
  volatile unsigned long  ulTrigger_sample_config;
  volatile unsigned long  ulTrigger_sample_status;
  volatile unsigned long  ulTrigger_sample_irq;
  volatile unsigned long  ulTrigger_activate;
  volatile unsigned long  ulTrigger_impulse_length;
  volatile unsigned long  ulTrigger_0_starttime_ns;
  volatile unsigned long aulReserved0[1];
  volatile unsigned long  ulTrigger_1_starttime_ns;
  volatile unsigned long aulReserved1[1];
  volatile unsigned long aulTrigger__cyc_time[2];
  volatile unsigned long  ulSample_mode;
  volatile unsigned long  ulSample_0_pos_systime_ns;
  volatile unsigned long aulReserved2[1];
  volatile unsigned long  ulSample_0_neg_systime_ns;
  volatile unsigned long aulReserved3[1];
  volatile unsigned long  ulSample_1_pos_systime_ns;
  volatile unsigned long aulReserved4[1];
  volatile unsigned long  ulSample_1_neg_systime_ns;
  volatile unsigned long aulReserved5[1];
  volatile unsigned long  ulSercos3_timing_delay_mst_1;
  volatile unsigned long  ulSercos3_timing_delay_mst_2;
  volatile unsigned long  ulSercos3_ring_delay;
  volatile unsigned long  ulSercos3_sync_count_1;
  volatile unsigned long  ulSercos3_sync_count_2;
  volatile unsigned long aulSercos3_tcnt_[4];
  volatile unsigned long  ulSercos3_tdiv_clk;
  volatile unsigned long  ulSercos3_dtdiv_clk;
  volatile unsigned long  ulSercos3_ndiv_clk;
  volatile unsigned long  ulSercos3_divclk_length;
  volatile unsigned long  ulSercos3_divclk_config;
  volatile unsigned long  ulSercos3_tcnt_max;
  volatile unsigned long  ulSercos3_tmx;
} NX5_TRIGGER_SAMPLE_UNIT_AREA_T;

typedef struct NX5_FMMUSM_AREA_Ttag
{
  struct
  {
    volatile unsigned long  ulCfg_log_startaddr;
    volatile unsigned long  ulCfg_length;
    volatile unsigned long  ulCfg_phys_startaddr;
    volatile unsigned long  ulCfg_enable;
  } asFmmu[8];
  struct
  {
    volatile unsigned long  ulCfg_adr_len;
    volatile unsigned long  ulCfg_mode;
  } asSm[8];
  volatile unsigned long aulReserved0[4];
  volatile unsigned long  ulPhys_addr_offset;
  volatile unsigned long  ulPhys_last_addr;
  volatile unsigned long  ulFmmusm_xpec_nr;
  volatile unsigned long aulReserved1[9];
  volatile unsigned long  ulFmmusm_read_addr_in;
  volatile unsigned long  ulFmmusm_write_addr_in;
  volatile unsigned long  ulSm_read_addr_out;
  volatile unsigned long  ulSm_write_addr_out;
  volatile unsigned long  ulFmmu_read_bit_rol_pos;
  volatile unsigned long  ulFmmu_read_bit_mask;
  volatile unsigned long  ulFmmu_write_bit_rol_pos;
  volatile unsigned long  ulFmmu_write_bit_mask;
  volatile unsigned long  ulFmmusm_len_en;
  volatile unsigned long  ulFmmusm_status_out;
  volatile unsigned long  ulSm_buf_statcfg;
  volatile unsigned long  ulSm_read_event;
  volatile unsigned long  ulSm_write_event;
  volatile unsigned long  ulSm_first_byte_addressed;
  volatile unsigned long  ulSm_last_byte_addressed;
  volatile unsigned long  ulSm_served;
} NX5_FMMUSM_AREA_T;

typedef struct NX5_BUF_MAN_AREA_Ttag
{
  volatile unsigned long aulBuf_man_xpec[2];
  volatile unsigned long  ulBuf_man_dpm;
} NX5_BUF_MAN_AREA_T;

typedef struct NX5_XC_EXTBUS_SEL_AREA_Ttag
{
  volatile unsigned long  ulXc_extbus_sel_ctrl;
} NX5_XC_EXTBUS_SEL_AREA_T;


#endif
