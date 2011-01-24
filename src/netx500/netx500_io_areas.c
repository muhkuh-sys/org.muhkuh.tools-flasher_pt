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


/*
************************************************************
*   Inclusion Area
************************************************************
*/

#include "netx500_io_areas.h"

NX500_ASIC_CTRL_AREA_T * const ptAsicCtrlArea = (NX500_ASIC_CTRL_AREA_T * const)Addr_NX500_asic_ctrl;
NX500_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea = (NX500_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX500_ext_asyncmem_ctrl;
NX500_EXTMEM_PRIORITY_CTRL_AREA_T * const ptExtmemPriorityCtrlArea = (NX500_EXTMEM_PRIORITY_CTRL_AREA_T * const)Addr_NX500_extmem_priority_ctrl;
NX500_WATCHDOG_AREA_T * const ptWatchdogArea = (NX500_WATCHDOG_AREA_T * const)Addr_NX500_watchdog;
NX500_GPIO_AREA_T * const ptGpioArea = (NX500_GPIO_AREA_T * const)Addr_NX500_gpio;
NX500_PIO_AREA_T * const ptPioArea = (NX500_PIO_AREA_T * const)Addr_NX500_pio;
NX500_UART_AREA_T * const ptUart0Area = (NX500_UART_AREA_T * const)Addr_NX500_uart0;
NX500_UART_AREA_T * const ptUart1Area = (NX500_UART_AREA_T * const)Addr_NX500_uart1;
NX500_UART_AREA_T * const ptUart2Area = (NX500_UART_AREA_T * const)Addr_NX500_uart2;
NX500_MIIMU_AREA_T * const ptMiimuArea = (NX500_MIIMU_AREA_T * const)Addr_NX500_miimu;
NX500_SPI_AREA_T * const ptSpiArea = (NX500_SPI_AREA_T * const)Addr_NX500_spi;
NX500_I2C_AREA_T * const ptI2cArea = (NX500_I2C_AREA_T * const)Addr_NX500_i2c;
NX500_CRC_AREA_T * const ptCrcArea = (NX500_CRC_AREA_T * const)Addr_NX500_crc;
NX500_SYSTIME_AREA_T * const ptSystimeArea = (NX500_SYSTIME_AREA_T * const)Addr_NX500_systime;
NX500_RTC_AREA_T * const ptRtcArea = (NX500_RTC_AREA_T * const)Addr_NX500_rtc;
NX500_HOST_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptHostControlledDmaRegisterBlockArea = (NX500_HOST_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const)Addr_NX500_host_controlled_dma_register_block;
NX500_HOST_CONTROLLED_GLOBAL_REGISTER_BLOCK_AREA_T * const ptHostControlledGlobalRegisterBlockArea = (NX500_HOST_CONTROLLED_GLOBAL_REGISTER_BLOCK_AREA_T * const)Addr_NX500_host_controlled_global_register_block;
NX500_HOST_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptHostControlledHandshakeRegisterBlockArea = (NX500_HOST_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const)Addr_NX500_host_controlled_handshake_register_block;
NX500_NETX_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptNetxControlledDmaRegisterBlockArea = (NX500_NETX_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const)Addr_NX500_netx_controlled_dma_register_block;
NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const ptNetxControlledGlobalRegisterBlock1Area = (NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const)Addr_NX500_netx_controlled_global_register_block_1;
NX500_NETX_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptNetxControlledHandshakeRegistrtBlockArea = (NX500_NETX_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const)Addr_NX500_netx_controlled_handshake_register_block;
NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const ptNetxControlledGlobalRegisterBlock2Area = (NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const)Addr_NX500_netx_controlled_global_register_block_2;
NX500_LCD_CTRL_AREA_T * const ptLcdCtrlArea = (NX500_LCD_CTRL_AREA_T * const)Addr_NX500_lcd_ctrl;
NX500_USB_CORE_AREA_T * const ptUsbCoreArea = (NX500_USB_CORE_AREA_T * const)Addr_NX500_usb_core;
NX500_USB_FIFO_AREA_T * const ptUsbFifoArea = (NX500_USB_FIFO_AREA_T * const)Addr_NX500_usb_fifo;
NX500_XC_AREA_T * const ptXcArea = (NX500_XC_AREA_T * const)Addr_NX500_xc;
NX500_XMAC_AREA_T * const ptXmac0Area = (NX500_XMAC_AREA_T * const)Addr_NX500_xmac0;
NX500_XMAC_AREA_T * const ptXmac1Area = (NX500_XMAC_AREA_T * const)Addr_NX500_xmac1;
NX500_XMAC_AREA_T * const ptXmac2Area = (NX500_XMAC_AREA_T * const)Addr_NX500_xmac2;
NX500_XMAC_AREA_T * const ptXmac3Area = (NX500_XMAC_AREA_T * const)Addr_NX500_xmac3;
NX500_POINTER_FIFO_AREA_T * const ptPointerFifoArea = (NX500_POINTER_FIFO_AREA_T * const)Addr_NX500_pointer_fifo;
NX500_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea = (NX500_XPEC_IRQ_REGISTERS_AREA_T * const)Addr_NX500_xpec_irq_registers;
NX500_XC_MEM_PROT_AREA_T * const ptXcMemProtArea = (NX500_XC_MEM_PROT_AREA_T * const)Addr_NX500_xc_mem_prot;
NX500_XC_DEBUG_AREA_T * const ptXcDebugArea = (NX500_XC_DEBUG_AREA_T * const)Addr_NX500_xc_debug;
NX500_XPEC_AREA_T * const ptXpec0Area = (NX500_XPEC_AREA_T * const)Addr_NX500_xpec0;
NX500_XPEC_AREA_T * const ptXpec1Area = (NX500_XPEC_AREA_T * const)Addr_NX500_xpec1;
NX500_XPEC_AREA_T * const ptXpec2Area = (NX500_XPEC_AREA_T * const)Addr_NX500_xpec2;
NX500_XPEC_AREA_T * const ptXpec3Area = (NX500_XPEC_AREA_T * const)Addr_NX500_xpec3;
NX500_XC_EXTBUS_SEL_AREA_T * const ptExtbusSelArea = (NX500_XC_EXTBUS_SEL_AREA_T * const)Addr_NX500_xc_extbus_sel;
NX500_VIC_AREA_T * const ptVicArea = (NX500_VIC_AREA_T * const)Addr_NX500_vic;
NX500_HIF_AHBLS6_AREA_T * const ptHifAhbls6Area = (NX500_HIF_AHBLS6_AREA_T * const)Addr_NX500_hif_ahbls6;

