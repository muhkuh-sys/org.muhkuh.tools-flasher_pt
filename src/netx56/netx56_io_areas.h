/***************************************************************************
 *   Copyright (C) 2012 by Hilscher GmbH                                   *
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

#ifndef __NETX56_IO_AREAS_H__
#define __NETX56_IO_AREAS_H__

#include "netx56_regdef.h"


typedef struct
{
	volatile unsigned long  ulSdram_general_ctrl;
	volatile unsigned long  ulSdram_timing_ctrl;
	volatile unsigned long  ulSdram_mr;
} NX56_SDRAM_AREA_T;

typedef struct
{
	volatile unsigned long aulHandshakeReg[16];
} NX56_HANDSHAKE_BLOCK_AREA_T;

typedef struct
{
	volatile unsigned long ulInt_phy_ctrl_miimu;
	volatile unsigned long ulInt_phy_ctrl_miimu_sw;
	volatile unsigned long ulInt_phy_ctrl_led;
	volatile unsigned long ulInt_phy_ctrl_enhanced_link_detection;
} NX56_INT_PHY_AREA_T;


#define NX56_DEF_ptArmBootVectorArea NX56_ARM_BOOT_VECTOR_AREA_T * const ptArmBootVectorArea = (NX56_ARM_BOOT_VECTOR_AREA_T * const)Addr_NX56_arm_boot_vector;

#define NX56_DEF_ptSrArea NX56_SR_AREA_T * const ptSrArea = (NX56_SR_AREA_T * const)Addr_NX56_sr_motion;

#define NX56_DEF_ptCordicArea NX56_CORDIC_AREA_T * const ptCordicArea = (NX56_CORDIC_AREA_T * const)Addr_NX56_cordic;

#define NX56_DEF_ptGpioMotionArea NX56_GPIO_AREA_T * const ptGpioMotionArea = (NX56_GPIO_AREA_T * const)Addr_NX56_gpio_motion;
#define NX56_DEF_ptGpioArea NX56_GPIO_AREA_T * const ptGpioArea = (NX56_GPIO_AREA_T * const)Addr_NX56_gpio;

#define NX56_DEF_ptXlink0Area NX56_XLINK_AREA_T * const ptXlink0Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink0;
#define NX56_DEF_ptXlink1Area NX56_XLINK_AREA_T * const ptXlink1Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink1;
#define NX56_DEF_ptXlink2Area NX56_XLINK_AREA_T * const ptXlink2Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink2;
#define NX56_DEF_ptXlink3Area NX56_XLINK_AREA_T * const ptXlink3Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink3;
#define NX56_DEF_ptXlink4Area NX56_XLINK_AREA_T * const ptXlink4Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink4;
#define NX56_DEF_ptXlink5Area NX56_XLINK_AREA_T * const ptXlink5Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink5;
#define NX56_DEF_ptXlink6Area NX56_XLINK_AREA_T * const ptXlink6Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink6;
#define NX56_DEF_ptXlink7Area NX56_XLINK_AREA_T * const ptXlink7Area = (NX56_XLINK_AREA_T * const)Addr_NX56_xlink7;

#define NX56_DEF_ptIoLinkIrqArea NX56_IO_LINK_IRQ_AREA_T * const ptIoLinkIrqArea = (NX56_IO_LINK_IRQ_AREA_T * const)Addr_NX56_io_link_irq;

#define NX56_DEF_ptSpiArea NX56_SPI_AREA_T * const ptSpiArea = (NX56_SPI_AREA_T * const)Addr_NX56_spi_motion;

#define NX56_DEF_ptXpicTimerArea NX56_XPIC_TIMER_AREA_T * const ptXpicTimerArea = (NX56_XPIC_TIMER_AREA_T * const)Addr_NX56_xpic_timer;

#define NX56_DEF_ptXpicVicArea NX56_XPIC_VIC_AREA_T * const ptXpicVicArea = (NX56_XPIC_VIC_AREA_T * const)Addr_NX56_xpic_vic;

#define NX56_DEF_ptXpicWdgArea NX56_XPIC_WDG_AREA_T * const ptXpicWdgArea = (NX56_XPIC_WDG_AREA_T * const)Addr_NX56_xpic_wdg;

#define NX56_DEF_ptRpec0Area NX56_XPEC_AREA_T * const ptRpec0Area = (NX56_XPEC_AREA_T * const)Addr_NX56_rpec0_regs;
#define NX56_DEF_ptTpec0Area NX56_XPEC_AREA_T * const ptTpec0Area = (NX56_XPEC_AREA_T * const)Addr_NX56_tpec0_regs;
#define NX56_DEF_ptRpec1Area NX56_XPEC_AREA_T * const ptRpec1Area = (NX56_XPEC_AREA_T * const)Addr_NX56_rpec1_regs;
#define NX56_DEF_ptTpec1Area NX56_XPEC_AREA_T * const ptTpec1Area = (NX56_XPEC_AREA_T * const)Addr_NX56_tpec1_regs;

#define NX56_DEF_ptXmac0Area NX56_XMAC_AREA_T * const ptXmac0Area = (NX56_XMAC_AREA_T * const)Addr_NX56_xmac0_regs;
#define NX56_DEF_ptXmac1Area NX56_XMAC_AREA_T * const ptXmac1Area = (NX56_XMAC_AREA_T * const)Addr_NX56_xmac1_regs;

#define NX56_DEF_ptPointerFifoArea NX56_POINTER_FIFO_AREA_T * const ptPointerFifoArea = (NX56_POINTER_FIFO_AREA_T * const)Addr_NX56_pointer_fifo;
#define NX56_DEF_ptPointerFifoMotionArea NX56_POINTER_FIFO_AREA_T * const ptPointerFifoMotionArea = (NX56_POINTER_FIFO_AREA_T * const)Addr_NX56_pointer_fifo_motion;

#define NX56_DEF_ptFmmusmArea NX56_FMMUSM_AREA_T * const ptFmmusmArea = (NX56_FMMUSM_AREA_T * const)Addr_NX56_fmmusm;

#define NX56_DEF_ptTriggerSampleUnitArea NX56_TRIGGER_SAMPLE_UNIT_AREA_T * const ptTriggerSampleUnitArea = (NX56_TRIGGER_SAMPLE_UNIT_AREA_T * const)Addr_NX56_trigger_sample_unit;

#define NX56_DEF_ptBufManArea NX56_BUF_MAN_AREA_T * const ptBufManArea = (NX56_BUF_MAN_AREA_T * const)Addr_NX56_buf_man;
#define NX56_DEF_ptBufManMotionArea NX56_BUF_MAN_AREA_T * const ptBufManMotionArea = (NX56_BUF_MAN_AREA_T * const)Addr_NX56_buf_man_motion;

#define NX56_DEF_ptXpecIrqRegistersArea NX56_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea = (NX56_XPEC_IRQ_REGISTERS_AREA_T * const)Addr_NX56_xpec_irq_registers;

#define NX56_DEF_ptXcDebugArea NX56_XC_DEBUG_AREA_T * const ptXcDebugArea = (NX56_XC_DEBUG_AREA_T * const)Addr_NX56_xc_debug;

#define NX56_DEF_ptXcStartStopArea NX56_XC_START_STOP_AREA_T * const ptXcStartStopArea = (NX56_XC_START_STOP_AREA_T * const)Addr_NX56_xc_start_stop;

#define NX56_DEF_ptDpmArea NX56_DPM_AREA_T * const ptDpmArea = (NX56_DPM_AREA_T * const)Addr_NX56_dpm;

#define NX56_DEF_ptAsicCtrlArea NX56_ASIC_CTRL_AREA_T * const ptAsicCtrlArea = (NX56_ASIC_CTRL_AREA_T * const)Addr_NX56_asic_ctrl;

#define NX56_DEF_ptMmioCtrlArea NX56_MMIO_CTRL_AREA_T * const ptMmioCtrlArea = (NX56_MMIO_CTRL_AREA_T * const)Addr_NX56_mmio_ctrl;

#define NX56_DEF_ptHandshakeCtrlArea NX56_HANDSHAKE_CTRL_AREA_T * const ptHandshakeCtrlArea = (NX56_HANDSHAKE_CTRL_AREA_T * const)Addr_NX56_handshake_ctrl;

#define NX56_DEF_ptXpicArea NX56_XPIC_AREA_T * const ptXpicArea = (NX56_XPIC_AREA_T * const)Addr_NX56_xpic_regs;

#define NX56_DEF_ptXpicDebugArea NX56_XPIC_DEBUG_AREA_T * const ptXpicDebugArea = (NX56_XPIC_DEBUG_AREA_T * const)Addr_NX56_xpic_debug;

#define NX56_DEF_ptIntPhyCtrl0Area NX56_INT_PHY_AREA_T * const ptIntPhyCtrl0Area = (NX56_INT_PHY_AREA_T * const)Addr_NX56_int_phy_ctrl0;
#define NX56_DEF_ptIntPhyCtrl1Area NX56_INT_PHY_AREA_T * const ptIntPhyCtrl1Area = (NX56_INT_PHY_AREA_T * const)Addr_NX56_int_phy_ctrl1;

#define NX56_DEF_ptMiimuArea NX56_MIIMU_AREA_T * const ptMiimuArea = (NX56_MIIMU_AREA_T * const)Addr_NX56_miimu;

#define NX56_DEF_ptHifIoCtrlArea NX56_HIF_IO_CTRL_AREA_T * const ptHifIoCtrlArea = (NX56_HIF_IO_CTRL_AREA_T * const)Addr_NX56_hif_io_ctrl;

#define NX56_DEF_ptCrcArea NX56_CRC_AREA_T * const ptCrcArea = (NX56_CRC_AREA_T * const)Addr_NX56_crc;

#define NX56_DEF_ptSystimeArea NX56_SYSTIME_AREA_T * const ptSystimeArea = (NX56_SYSTIME_AREA_T * const)Addr_NX56_systime;
#define NX56_DEF_ptSystimeUcArea NX56_SYSTIME_AREA_T * const ptSystimeUcArea = (NX56_SYSTIME_AREA_T * const)Addr_NX56_systime_uc;

#define NX56_DEF_ptWatchdogArea NX56_WATCHDOG_AREA_T * const ptWatchdogArea = (NX56_WATCHDOG_AREA_T * const)Addr_NX56_watchdog;

#define NX56_DEF_ptSqiArea NX56_SQI_AREA_T * const ptSqiArea = (NX56_SQI_AREA_T * const)Addr_NX56_sqi;

#define NX56_DEF_ptUart0Area NX56_UART_AREA_T * const ptUart0Area = (NX56_UART_AREA_T * const)Addr_NX56_uart0;
#define NX56_DEF_ptUart1Area NX56_UART_AREA_T * const ptUart1Area = (NX56_UART_AREA_T * const)Addr_NX56_uart1;
#define NX56_DEF_ptUart2Area NX56_UART_AREA_T * const ptUart2Area = (NX56_UART_AREA_T * const)Addr_NX56_uart2;

#define NX56_DEF_ptI2c0Area NX56_I2C_AREA_T * const ptI2c0Area = (NX56_I2C_AREA_T * const)Addr_NX56_i2c0;
#define NX56_DEF_ptI2c1Area NX56_I2C_AREA_T * const ptI2c1Area = (NX56_I2C_AREA_T * const)Addr_NX56_i2c1;

#define NX56_DEF_ptEthArea NX56_ETH_AREA_T * const ptEthArea = (NX56_ETH_AREA_T * const)Addr_NX56_eth;

#define NX56_DEF_ptUsbDevCtrlArea NX56_USB_DEV_CTRL_AREA_T * const ptUsbDevCtrlArea = (NX56_USB_DEV_CTRL_AREA_T * const)Addr_NX56_usb_dev_ctrl;

#define NX56_DEF_ptUsbDevFifoCtrlArea NX56_USB_DEV_FIFO_CTRL_AREA_T * const ptUsbDevFifoCtrlArea = (NX56_USB_DEV_FIFO_CTRL_AREA_T * const)Addr_NX56_usb_dev_fifo_ctrl;

#define NX56_DEF_ptUsbDevFifoArea NX56_USB_DEV_FIFO_AREA_T * const ptUsbDevFifoArea = (NX56_USB_DEV_FIFO_AREA_T * const)Addr_NX56_usb_dev_fifo;

#define NX56_DEF_ptCanctrlArea NX56_CANCTRL_AREA_T * const ptCanctrlArea = (NX56_CANCTRL_AREA_T * const)Addr_NX56_canctrl;

#define NX56_DEF_ptDmacCh0Area NX56_DMAC_CH_AREA_T * const ptDmacCh0Area = (NX56_DMAC_CH_AREA_T * const)Addr_NX56_dmac_ch0;
#define NX56_DEF_ptDmacCh1Area NX56_DMAC_CH_AREA_T * const ptDmacCh1Area = (NX56_DMAC_CH_AREA_T * const)Addr_NX56_dmac_ch0;
#define NX56_DEF_ptDmacCh2Area NX56_DMAC_CH_AREA_T * const ptDmacCh2Area = (NX56_DMAC_CH_AREA_T * const)Addr_NX56_dmac_ch0;

#define NX56_DEF_ptDmacRegArea NX56_DMAC_REG_AREA_T * const ptDmacRegArea = (NX56_DMAC_REG_AREA_T * const)Addr_NX56_dmac_reg;

#define NX56_DEF_ptExtAsyncmemCtrlArea NX56_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea = (NX56_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX56_ext_asyncmem_ctrl;
#define NX56_DEF_ptHifAsyncmemCtrlArea NX56_EXT_ASYNCMEM_CTRL_AREA_T * const ptHifAsyncmemCtrlArea = (NX56_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX56_hif_asyncmem_ctrl;

#define NX56_DEF_ptExtmemPriorityCtrlArea NX56_EXTMEM_PRIORITY_CTRL_AREA_T * const ptExtmemPriorityCtrlArea = (NX56_EXTMEM_PRIORITY_CTRL_AREA_T * const)Addr_NX56_extmem_priority_ctrl;

#define NX56_DEF_ptArmTimerArea NX56_ARM_TIMER_AREA_T * const ptArmTimerArea = (NX56_ARM_TIMER_AREA_T * const)Addr_NX56_arm_timer;

#define NX56_DEF_ptVicArea NX56_VIC_AREA_T * const ptVicArea = (NX56_VIC_AREA_T * const)Addr_NX56_vic;

#define NX56_DEF_ptNfifoArea NX56_NFIFO_AREA_T * const ptNfifoArea = (NX56_NFIFO_AREA_T * const)Addr_NX56_nfifo;

#define NX56_DEF_ptExtSdramArea NX56_SDRAM_AREA_T * const ptExtSdramArea = (NX56_SDRAM_AREA_T * const)Addr_NX56_ext_sdram_ctrl;
#define NX56_DEF_ptHifSdramArea NX56_SDRAM_AREA_T * const ptHifSdramArea = (NX56_SDRAM_AREA_T * const)Addr_NX56_hif_sdram_ctrl;

#define NX56_DEF_ptHandshakeArea NX56_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeArea = (NX56_HANDSHAKE_BLOCK_AREA_T * const)Addr_NX56_intramhs;
#define NX56_DEF_ptHandshakeDtcmArmMirrorArea NX56_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeDtcmArmMirrorArea = (NX56_HANDSHAKE_BLOCK_AREA_T * const)Addr_NX56_intramhs_arm_mirror;


typedef enum
{
	MMIO_CFG_xm0_io0                = 0x00,
	MMIO_CFG_xm0_io1                = 0x01,
	MMIO_CFG_xm0_io2                = 0x02,
	MMIO_CFG_xm0_io3                = 0x03,
	MMIO_CFG_xm0_io4                = 0x04,
	MMIO_CFG_xm0_io5                = 0x05,
	MMIO_CFG_xm0_rx                 = 0x06,
	MMIO_CFG_xm0_tx_out             = 0x07,
	MMIO_CFG_xm1_io0                = 0x08,
	MMIO_CFG_xm1_io1                = 0x09,
	MMIO_CFG_xm1_io2                = 0x0a,
	MMIO_CFG_xm1_io3                = 0x0b,
	MMIO_CFG_xm1_io4                = 0x0c,
	MMIO_CFG_xm1_io5                = 0x0d,
	MMIO_CFG_xm1_rx                 = 0x0e,
	MMIO_CFG_xm1_tx_out             = 0x0f,
	MMIO_CFG_gpio0                  = 0x10,
	MMIO_CFG_gpio1                  = 0x11,
	MMIO_CFG_gpio2                  = 0x12,
	MMIO_CFG_gpio3                  = 0x13,
	MMIO_CFG_gpio4                  = 0x14,
	MMIO_CFG_gpio5                  = 0x15,
	MMIO_CFG_gpio6                  = 0x16,
	MMIO_CFG_gpio7                  = 0x17,
	MMIO_CFG_gpio8                  = 0x18,
	MMIO_CFG_gpio9                  = 0x19,
	MMIO_CFG_gpio10                 = 0x1a,
	MMIO_CFG_gpio11                 = 0x1b,
	MMIO_CFG_gpio12                 = 0x1c,
	MMIO_CFG_gpio13                 = 0x1d,
	MMIO_CFG_gpio14                 = 0x1e,
	MMIO_CFG_gpio15                 = 0x1f,
	MMIO_CFG_gpio16                 = 0x20,
	MMIO_CFG_gpio17                 = 0x21,
	MMIO_CFG_gpio18                 = 0x22,
	MMIO_CFG_gpio19                 = 0x23,
	MMIO_CFG_gpio20                 = 0x24,
	MMIO_CFG_gpio21                 = 0x25,
	MMIO_CFG_gpio22                 = 0x26,
	MMIO_CFG_gpio23                 = 0x27,
	MMIO_CFG_gpio24                 = 0x28,
	MMIO_CFG_gpio25                 = 0x29,
	MMIO_CFG_gpio26                 = 0x2a,
	MMIO_CFG_gpio27                 = 0x2b,
	MMIO_CFG_gpio28                 = 0x2c,
	MMIO_CFG_gpio29                 = 0x2d,
	MMIO_CFG_gpio30                 = 0x2e,
	MMIO_CFG_gpio31                 = 0x2f,
	MMIO_CFG_phy0_led0              = 0x30,
	MMIO_CFG_phy0_led1              = 0x31,
	MMIO_CFG_phy0_led2              = 0x32,
	MMIO_CFG_phy0_led3              = 0x33,
	MMIO_CFG_phy1_led0              = 0x34,
	MMIO_CFG_phy1_led1              = 0x35,
	MMIO_CFG_phy1_led2              = 0x36,
	MMIO_CFG_phy1_led3              = 0x37,
	MMIO_CFG_mii_mdc                = 0x38,
	MMIO_CFG_mii_mdio               = 0x39,
	MMIO_CFG_spi0_cs2n              = 0x3a,
	MMIO_CFG_spi0_sio2_mmio         = 0x3b,
	MMIO_CFG_spi0_sio3_mmio         = 0x3c,
	MMIO_CFG_spi1_clk               = 0x3d,
	MMIO_CFG_spi1_cs0n              = 0x3e,
	MMIO_CFG_spi1_cs1n              = 0x3f,
	MMIO_CFG_spi1_cs2n              = 0x40,
	MMIO_CFG_spi1_miso              = 0x41,
	MMIO_CFG_spi1_mosi              = 0x42,
	MMIO_CFG_i2c0_scl_mmio          = 0x43,
	MMIO_CFG_i2c0_sda_mmio          = 0x44,
	MMIO_CFG_i2c1_scl               = 0x45,
	MMIO_CFG_i2c1_sda               = 0x46,
	MMIO_CFG_xc_sample0             = 0x47,
	MMIO_CFG_xc_sample1             = 0x48,
	MMIO_CFG_xc_trigger0            = 0x49,
	MMIO_CFG_xc_trigger1            = 0x4a,
	MMIO_CFG_uart0_ctsn             = 0x4b,
	MMIO_CFG_uart0_rtsn             = 0x4c,
	MMIO_CFG_uart0_rxd              = 0x4d,
	MMIO_CFG_uart0_txd              = 0x4e,
	MMIO_CFG_uart1_ctsn             = 0x4f,
	MMIO_CFG_uart1_rtsn             = 0x50,
	MMIO_CFG_uart1_rxd              = 0x51,
	MMIO_CFG_uart1_txd              = 0x52,
	MMIO_CFG_uart2_ctsn             = 0x53,
	MMIO_CFG_uart2_rtsn             = 0x54,
	MMIO_CFG_uart2_rxd              = 0x55,
	MMIO_CFG_uart2_txd              = 0x56,
	MMIO_CFG_can_rx                 = 0x57,
	MMIO_CFG_can_tx                 = 0x58,
	MMIO_CFG_mem_rdy                = 0x59,
	MMIO_CFG_pio0                   = 0x5a,
	MMIO_CFG_pio1                   = 0x5b,
	MMIO_CFG_pio2                   = 0x5c,
	MMIO_CFG_pio3                   = 0x5d,
	MMIO_CFG_pio4                   = 0x5e,
	MMIO_CFG_pio5                   = 0x5f,
	MMIO_CFG_pio6                   = 0x60,
	MMIO_CFG_pio7                   = 0x61,
	MMIO_CFG_PIO                    = 0x7f
} MMIO_CFG_T;

#define MMIO_CFG_DISABLE MMIO_CFG_PIO


#endif
