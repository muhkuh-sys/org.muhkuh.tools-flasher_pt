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


#include "netx50_regdef.h"

#ifndef __NETX50_IO_AREAS_H__
#define __NETX50_IO_AREAS_H__


typedef struct
{
	volatile unsigned long ulSdram_general_ctrl;
	volatile unsigned long ulSdram_timing_ctrl;
} NX50_SDRAM_AREA_T;


#define NX50_DEF_ptAsicCtrlArea NX50_ASIC_CTRL_AREA_T * const ptAsicCtrlArea = (NX50_ASIC_CTRL_AREA_T * const)Addr_NX50_asic_ctrl;
#define NX50_DEF_ptSdramArea NX50_SDRAM_AREA_T * const ptSdramArea = (NX50_SDRAM_AREA_T * const)Addr_NX50_ext_sdram_ctrl;
#define NX50_DEF_ptExtAsyncmemCtrlArea NX50_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea = (NX50_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX50_ext_asyncmem_ctrl;
#define NX50_DEF_ptExtmemPriorityCtrlArea NX50_EXTMEM_PRIORITY_CTRL_AREA_T * const ptExtmemPriorityCtrlArea = (NX50_EXTMEM_PRIORITY_CTRL_AREA_T * const)Addr_NX50_extmem_priority_ctrl;
#define NX50_DEF_ptWatchdogArea NX50_WATCHDOG_AREA_T * const ptWatchdogArea = (NX50_WATCHDOG_AREA_T * const)Addr_NX50_watchdog;
#define NX50_DEF_ptGpioArea NX50_GPIO_AREA_T * const ptGpioArea = (NX50_GPIO_AREA_T * const)Addr_NX50_gpio;
/* #define NX50_DEF_ptIolinkArea NX50_IOLINK_AREA_T * const ptIolinkArea = (NX50_IOLINK_AREA_T * const)Addr_NX50_iolink; */
#define NX50_DEF_ptPioArea NX50_PIO_AREA_T * const ptPioArea = (NX50_PIO_AREA_T * const)Addr_NX50_pio;
#define NX50_DEF_ptUart0Area NX50_UART_AREA_T * const ptUart0Area = (NX50_UART_AREA_T * const)Addr_NX50_uart0;
#define NX50_DEF_ptUart1Area NX50_UART_AREA_T * const ptUart1Area = (NX50_UART_AREA_T * const)Addr_NX50_uart1;
#define NX50_DEF_ptUart2Area NX50_UART_AREA_T * const ptUart2Area = (NX50_UART_AREA_T * const)Addr_NX50_uart2;
#define NX50_DEF_ptMiimuArea NX50_MIIMU_AREA_T * const ptMiimuArea = (NX50_MIIMU_AREA_T * const)Addr_NX50_miimu;
#define NX50_DEF_ptSpi0Area NX50_SPI_AREA_T * const ptSpi0Area = (NX50_SPI_AREA_T * const)Addr_NX50_spi0;
#define NX50_DEF_ptSpi1Area NX50_SPI_AREA_T * const ptSpi1Area = (NX50_SPI_AREA_T * const)Addr_NX50_spi1;
#define NX50_DEF_ptI2cArea NX50_I2C_AREA_T * const ptI2cArea = (NX50_I2C_AREA_T * const)Addr_NX50_i2c;
#define NX50_DEF_ptCcdcArea NX50_CCDC_AREA_T * const ptCcdcArea = (NX50_CCDC_AREA_T * const)Addr_NX50_ccdc;
#define NX50_DEF_ptCrcArea NX50_CRC_AREA_T * const ptCrcArea = (NX50_CRC_AREA_T * const)Addr_NX50_crc;
#define NX50_DEF_ptSystimeArea NX50_SYSTIME_AREA_T * const ptSystimeArea = (NX50_SYSTIME_AREA_T * const)Addr_NX50_systime;
#define NX50_DEF_ptMmioCtrlArea NX50_MMIO_CTRL_AREA_T * const ptMmioCtrlArea = (NX50_MMIO_CTRL_AREA_T * const)Addr_NX50_mmio_ctrl;
#define NX50_DEF_ptHostControlledDmaRegisterBlockArea NX50_HOST_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptHostControlledDmaRegisterBlockArea = (NX50_HOST_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const)Addr_NX50_host_controlled_dma_register_block;
#define NX50_DEF_ptHostControlledGlobalRegisterBlockArea NX50_HOST_CONTROLLED_GLOBAL_REGISTER_BLOCK_AREA_T * const ptHostControlledGlobalRegisterBlockArea = (NX50_HOST_CONTROLLED_GLOBAL_REGISTER_BLOCK_AREA_T * const)Addr_NX50_host_controlled_global_register_block;
#define NX50_DEF_ptHostControlledHandshakeRegisterBlockArea NX50_HOST_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptHostControlledHandshakeRegisterBlockArea = (NX50_HOST_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const)Addr_NX50_host_controlled_handshake_register_block;
#define NX50_DEF_ptNetxControlledDmaRegisterBlockArea NX50_NETX_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptNetxControlledDmaRegisterBlockArea = (NX50_NETX_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const)Addr_NX50_netx_controlled_dma_register_block;
#define NX50_DEF_ptNetxControlledGlobalRegisterBlock1Area NX50_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const ptNetxControlledGlobalRegisterBlock1Area = (NX50_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const)Addr_NX50_netx_controlled_global_register_block_1;
#define NX50_DEF_ptNetxControlledHandshakeRegisterBlockArea NX50_NETX_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptNetxControlledHandshakeRegisterBlockArea = (NX50_NETX_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const)Addr_NX50_netx_controlled_handshake_register_block;
#define NX50_DEF_ptNetxControlledGlobalRegisterBlock2Area NX50_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const ptNetxControlledGlobalRegisterBlock2Area = (NX50_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const)Addr_NX50_netx_controlled_global_register_block_2;
#define NX50_DEF_ptDmacCh0Area NX50_DMAC_CH_AREA_T * const ptDmacCh0Area = (NX50_DMAC_CH_AREA_T * const)Addr_NX50_dmac_ch0;
#define NX50_DEF_ptDmacCh1Area NX50_DMAC_CH_AREA_T * const ptDmacCh1Area = (NX50_DMAC_CH_AREA_T * const)Addr_NX50_dmac_ch1;
#define NX50_DEF_ptDmacCh2Area NX50_DMAC_CH_AREA_T * const ptDmacCh2Area = (NX50_DMAC_CH_AREA_T * const)Addr_NX50_dmac_ch2;
#define NX50_DEF_ptDmacCh3Area NX50_DMAC_CH_AREA_T * const ptDmacCh3Area = (NX50_DMAC_CH_AREA_T * const)Addr_NX50_dmac_ch3;
#define NX50_DEF_ptDmacRegArea NX50_DMAC_REG_AREA_T * const ptDmacRegArea = (NX50_DMAC_REG_AREA_T * const)Addr_NX50_dmac_reg;
#define NX50_DEF_ptUsbCoreArea NX50_USB_CORE_AREA_T * const ptUsbCoreArea = (NX50_USB_CORE_AREA_T * const)Addr_NX50_usb_core;
#define NX50_DEF_ptUsbFifoArea NX50_USB_FIFO_AREA_T * const ptUsbFifoArea = (NX50_USB_FIFO_AREA_T * const)Addr_NX50_usb_fifo;
#define NX50_DEF_ptXpec0Area NX50_XPEC_AREA_T * const ptXpec0Area = (NX50_XPEC_AREA_T * const)Addr_NX50_xpec0;
#define NX50_DEF_ptXpec1Area NX50_XPEC_AREA_T * const ptXpec1Area = (NX50_XPEC_AREA_T * const)Addr_NX50_xpec1;
#define NX50_DEF_ptXmac0Area NX50_XMAC_AREA_T * const ptXmac0Area = (NX50_XMAC_AREA_T * const)Addr_NX50_xmac0;
#define NX50_DEF_ptXmac1Area NX50_XMAC_AREA_T * const ptXmac1Area = (NX50_XMAC_AREA_T * const)Addr_NX50_xmac1;
#define NX50_DEF_ptPointerFifoArea NX50_POINTER_FIFO_AREA_T * const ptPointerFifoArea = (NX50_POINTER_FIFO_AREA_T * const)Addr_NX50_pointer_fifo;
#define NX50_DEF_ptXpecIrqRegistersArea NX50_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea = (NX50_XPEC_IRQ_REGISTERS_AREA_T * const)Addr_NX50_xpec_irq_registers;
#define NX50_DEF_ptXcMemProtArea NX50_XC_MEM_PROT_AREA_T * const ptXcMemProtArea = (NX50_XC_MEM_PROT_AREA_T * const)Addr_NX50_xc_mem_prot;
#define NX50_DEF_ptXcDebugArea NX50_XC_DEBUG_AREA_T * const ptXcDebugArea = (NX50_XC_DEBUG_AREA_T * const)Addr_NX50_xc_debug;
#define NX50_DEF_ptTriggerSampleUnitArea NX50_TRIGGER_SAMPLE_UNIT_AREA_T * const ptTriggerSampleUnitArea = (NX50_TRIGGER_SAMPLE_UNIT_AREA_T * const)Addr_NX50_trigger_sample_unit;
#define NX50_DEF_ptFmmusmArea NX50_FMMUSM_AREA_T * const ptFmmusmArea = (NX50_FMMUSM_AREA_T * const)Addr_NX50_fmmusm;
#define NX50_DEF_ptBufManArea NX50_BUF_MAN_AREA_T * const ptBufManArea = (NX50_BUF_MAN_AREA_T * const)Addr_NX50_buf_man;
#define NX50_DEF_ptXcExtbusSelArea NX50_XC_EXTBUS_SEL_AREA_T * const ptXcExtbusSelArea = (NX50_XC_EXTBUS_SEL_AREA_T * const)Addr_NX50_xc_extbus_sel;
#define NX50_DEF_ptVicArea NX50_VIC_AREA_T * const ptVicArea = (NX50_VIC_AREA_T * const)Addr_NX50_vic;


typedef enum
{
	MMIO_CFG_xm0_io0		= 0x00,
	MMIO_CFG_xm0_io1		= 0x01,
	MMIO_CFG_xm0_io2		= 0x02,
	MMIO_CFG_xm0_io3		= 0x03,
	MMIO_CFG_xm0_io4		= 0x04,
	MMIO_CFG_xm0_io5		= 0x05,
	MMIO_CFG_xm0_rx			= 0x06,
	MMIO_CFG_xm0_tx_oe		= 0x07,
	MMIO_CFG_xm0_tx_out		= 0x08,
	MMIO_CFG_xm1_io0		= 0x09,
	MMIO_CFG_xm1_io1		= 0x0a,
	MMIO_CFG_xm1_io2		= 0x0b,
	MMIO_CFG_xm1_io3		= 0x0c,
	MMIO_CFG_xm1_io4		= 0x0d,
	MMIO_CFG_xm1_io5		= 0x0e,
	MMIO_CFG_xm1_rx			= 0x0f,
	MMIO_CFG_xm1_tx_oe		= 0x10,
	MMIO_CFG_xm1_tx_out		= 0x11,
	MMIO_CFG_gpio0			= 0x12,
	MMIO_CFG_gpio1			= 0x13,
	MMIO_CFG_gpio2			= 0x14,
	MMIO_CFG_gpio3			= 0x15,
	MMIO_CFG_gpio4			= 0x16,
	MMIO_CFG_gpio5			= 0x17,
	MMIO_CFG_gpio6			= 0x18,
	MMIO_CFG_gpio7			= 0x19,
	MMIO_CFG_gpio8			= 0x1a,
	MMIO_CFG_gpio9			= 0x1b,
	MMIO_CFG_gpio10			= 0x1c,
	MMIO_CFG_gpio11			= 0x1d,
	MMIO_CFG_gpio12			= 0x1e,
	MMIO_CFG_gpio13			= 0x1f,
	MMIO_CFG_gpio14			= 0x20,
	MMIO_CFG_gpio15			= 0x21,
	MMIO_CFG_gpio16			= 0x22,
	MMIO_CFG_gpio17			= 0x23,
	MMIO_CFG_gpio18			= 0x24,
	MMIO_CFG_gpio19			= 0x25,
	MMIO_CFG_gpio20			= 0x26,
	MMIO_CFG_gpio21			= 0x27,
	MMIO_CFG_gpio22			= 0x28,
	MMIO_CFG_gpio23			= 0x29,
	MMIO_CFG_gpio24			= 0x2a,
	MMIO_CFG_gpio25			= 0x2b,
	MMIO_CFG_gpio26			= 0x2c,
	MMIO_CFG_gpio27			= 0x2d,
	MMIO_CFG_gpio28			= 0x2e,
	MMIO_CFG_gpio29			= 0x2f,
	MMIO_CFG_gpio30			= 0x30,
	MMIO_CFG_gpio31			= 0x31,
	MMIO_CFG_phy0_led0		= 0x32,
	MMIO_CFG_phy0_led1		= 0x33,
	MMIO_CFG_phy0_led2		= 0x34,
	MMIO_CFG_phy0_led3		= 0x35,
	MMIO_CFG_phy1_led0		= 0x36,
	MMIO_CFG_phy1_led1		= 0x37,
	MMIO_CFG_phy1_led2		= 0x38,
	MMIO_CFG_phy1_led3		= 0x39,
	MMIO_CFG_mii_mdc		= 0x3a,
	MMIO_CFG_mii_mdio		= 0x3b,
	MMIO_CFG_mii0_col		= 0x3c,
	MMIO_CFG_mii0_crs		= 0x3d,
	MMIO_CFG_mii0_led0		= 0x3e,
	MMIO_CFG_mii0_led1		= 0x3f,
	MMIO_CFG_mii0_led2		= 0x40,
	MMIO_CFG_mii0_led3		= 0x41,
	MMIO_CFG_mii0_rxclk		= 0x42,
	MMIO_CFG_mii0_rxd0		= 0x43,
	MMIO_CFG_mii0_rxd1		= 0x44,
	MMIO_CFG_mii0_rxd2		= 0x45,
	MMIO_CFG_mii0_rxd3		= 0x46,
	MMIO_CFG_mii0_rxdv		= 0x47,
	MMIO_CFG_mii0_rxer		= 0x48,
	MMIO_CFG_mii0_txclk		= 0x49,
	MMIO_CFG_mii0_txd0		= 0x4a,
	MMIO_CFG_mii0_txd1		= 0x4b,
	MMIO_CFG_mii0_txd2		= 0x4c,
	MMIO_CFG_mii0_txd3		= 0x4d,
	MMIO_CFG_mii0_txen		= 0x4e,
	MMIO_CFG_mii0_txer		= 0x4f,
	MMIO_CFG_mii1_col		= 0x50,
	MMIO_CFG_mii1_crs		= 0x51,
	MMIO_CFG_mii1_led0		= 0x52,
	MMIO_CFG_mii1_led1		= 0x53,
	MMIO_CFG_mii1_led2		= 0x54,
	MMIO_CFG_mii1_led3		= 0x55,
	MMIO_CFG_mii1_rxclk		= 0x56,
	MMIO_CFG_mii1_rxd0		= 0x57,
	MMIO_CFG_mii1_rxd1		= 0x58,
	MMIO_CFG_mii1_rxd2		= 0x59,
	MMIO_CFG_mii1_rxd3		= 0x5a,
	MMIO_CFG_mii1_rxdv		= 0x5b,
	MMIO_CFG_mii1_rxer		= 0x5c,
	MMIO_CFG_mii1_txclk		= 0x5d,
	MMIO_CFG_mii1_txd0		= 0x5e,
	MMIO_CFG_mii1_txd1		= 0x5f,
	MMIO_CFG_mii1_txd2		= 0x60,
	MMIO_CFG_mii1_txd3		= 0x61,
	MMIO_CFG_mii1_txen		= 0x62,
	MMIO_CFG_mii1_txer		= 0x63,
	MMIO_CFG_pio0			= 0x64,
	MMIO_CFG_pio1			= 0x65,
	MMIO_CFG_pio2			= 0x66,
	MMIO_CFG_pio3			= 0x67,
	MMIO_CFG_pio4			= 0x68,
	MMIO_CFG_pio5			= 0x69,
	MMIO_CFG_pio6			= 0x6a,
	MMIO_CFG_pio7			= 0x6b,
	MMIO_CFG_spi0_cs2n		= 0x6c,
	MMIO_CFG_spi1_clk		= 0x6d,
	MMIO_CFG_spi1_cs0n		= 0x6e,
	MMIO_CFG_spi1_cs1n		= 0x6f,
	MMIO_CFG_spi1_cs2n		= 0x70,
	MMIO_CFG_spi1_miso		= 0x71,
	MMIO_CFG_spi1_mosi		= 0x72,
	MMIO_CFG_i2c_scl_mmio		= 0x73,
	MMIO_CFG_i2c_sda_mmio		= 0x74,
	MMIO_CFG_xc_sample0		= 0x75,
	MMIO_CFG_xc_sample1		= 0x76,
	MMIO_CFG_xc_trigger0		= 0x77,
	MMIO_CFG_xc_trigger1		= 0x78,
	MMIO_CFG_uart0_cts		= 0x79,
	MMIO_CFG_uart0_rts		= 0x7a,
	MMIO_CFG_uart0_rxd		= 0x7b,
	MMIO_CFG_uart0_txd		= 0x7c,
	MMIO_CFG_uart1_cts		= 0x7d,
	MMIO_CFG_uart1_rts		= 0x7e,
	MMIO_CFG_uart1_rxd		= 0x7f,
	MMIO_CFG_uart1_txd		= 0x80,
	MMIO_CFG_uart2_cts		= 0x81,
	MMIO_CFG_uart2_rts		= 0x82,
	MMIO_CFG_uart2_rxd		= 0x83,
	MMIO_CFG_uart2_txd		= 0x84,
	MMIO_CFG_usb_id_dig		= 0x85,
	MMIO_CFG_usb_id_pullup_ctrl	= 0x86,
	MMIO_CFG_usb_rpd_ena		= 0x87,
	MMIO_CFG_usb_rpu_ena		= 0x88,
	MMIO_CFG_ccd_data0		= 0x89,
	MMIO_CFG_ccd_data1		= 0x8a,
	MMIO_CFG_ccd_data2		= 0x8b,
	MMIO_CFG_ccd_data3		= 0x8c,
	MMIO_CFG_ccd_data4		= 0x8d,
	MMIO_CFG_ccd_data5		= 0x8e,
	MMIO_CFG_ccd_data6		= 0x8f,
	MMIO_CFG_ccd_data7		= 0x90,
	MMIO_CFG_ccd_pixclk		= 0x91,
	MMIO_CFG_ccd_line_valid		= 0x92,
	MMIO_CFG_ccd_frame_valid	= 0x93,
	MMIO_CFG_INPUT			= 0xff
} MMIO_CFG_T;

#define MMIO_CFG_DISABLE MMIO_CFG_INPUT


#endif  /*  __NETX50_IO_AREAS_H__ */
