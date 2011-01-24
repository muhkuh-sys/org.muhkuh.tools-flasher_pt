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


#include "netx50_regdef.h"

#ifndef __NETX50_IO_AREAS_H__
#define __NETX50_IO_AREAS_H__


typedef struct
{
	volatile unsigned long ulSdram_general_ctrl;
	volatile unsigned long ulSdram_timing_ctrl;
} NX50_SDRAM_AREA_T;


extern NX50_ASIC_CTRL_AREA_T * const ptAsicCtrlArea;
extern NX50_SDRAM_AREA_T * const ptSdramArea;
extern NX50_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea;
extern NX50_EXTMEM_PRIORITY_CTRL_AREA_T * const ptExtmemPriorityCtrlArea;
extern NX50_WATCHDOG_AREA_T * const ptWatchdogArea;
extern NX50_GPIO_AREA_T * const ptGpioArea;
extern NX50_PIO_AREA_T * const ptPioArea;
extern NX50_UART_AREA_T * const ptUart0Area;
extern NX50_UART_AREA_T * const ptUart1Area;
extern NX50_UART_AREA_T * const ptUart2Area;
extern NX50_MIIMU_AREA_T * const ptMiimuArea;
extern NX50_SPI_AREA_T * const ptSpi0Area;
extern NX50_SPI_AREA_T * const ptSpi1Area;
extern NX50_I2C_AREA_T * const ptI2cArea;
extern NX50_CCDC_AREA_T * const ptCcdcArea;
extern NX50_CRC_AREA_T * const ptCrcArea;
extern NX50_SYSTIME_AREA_T * const ptSystimeArea;
extern NX50_MMIO_CTRL_AREA_T * const ptMmioCtrlArea;
extern NX50_HOST_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptHostControlledDmaRegisterBlockArea;
extern NX50_HOST_CONTROLLED_GLOBAL_REGISTER_BLOCK_AREA_T * const ptHostControlledGlobalRegisterBlockArea;
extern NX50_HOST_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptHostControlledHandshakeRegisterBlockArea;
extern NX50_NETX_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptNetxControlledDmaRegisterBlockArea;
extern NX50_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const ptNetxControlledGlobalRegisterBlock1Area;
extern NX50_NETX_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptNetxControlledHandshakeRegisterBlockArea;
extern NX50_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const ptNetxControlledGlobalRegisterBlock2Area;
extern NX50_DMAC_CH_AREA_T * const ptDmacCh0Area;
extern NX50_DMAC_CH_AREA_T * const ptDmacCh1Area;
extern NX50_DMAC_CH_AREA_T * const ptDmacCh2Area;
extern NX50_DMAC_CH_AREA_T * const ptDmacCh3Area;
extern NX50_DMAC_REG_AREA_T * const ptDmacRegArea;
extern NX50_USB_CORE_AREA_T * const ptUsbCoreArea;
extern NX50_USB_FIFO_AREA_T * const ptUsbFifoArea;
extern NX50_XPEC_AREA_T * const ptXpec0Area;
extern NX50_XPEC_AREA_T * const ptXpec1Area;
extern NX50_XMAC_AREA_T * const ptXmac0Area;
extern NX50_XMAC_AREA_T * const ptXmac1Area;
extern NX50_POINTER_FIFO_AREA_T * const ptPointerFifoArea;
extern NX50_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea;
extern NX50_XC_MEM_PROT_AREA_T * const ptXcMemProtArea;
extern NX50_XC_DEBUG_AREA_T * const ptXcDebugArea;
extern NX50_TRIGGER_SAMPLE_UNIT_AREA_T * const ptTriggerSampleUnitArea;
extern NX50_FMMUSM_AREA_T * const ptFmmusmArea;
extern NX50_BUF_MAN_AREA_T * const ptBufManArea;
extern NX50_XC_EXTBUS_SEL_AREA_T * const ptXcExtbusSelArea;
extern NX50_VIC_AREA_T * const ptVicArea;


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
