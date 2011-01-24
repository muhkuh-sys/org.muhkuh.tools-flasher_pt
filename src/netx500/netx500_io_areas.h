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

/***************************************************************************
  File          : netx_io_areas.c
 ----------------------------------------------------------------------------
  Description:

      IO Area for the netX100/500
 ----------------------------------------------------------------------------
  Todo:

 ----------------------------------------------------------------------------
  Known Problems:

    -

 ----------------------------------------------------------------------------
 ***************************************************************************/


/*
************************************************************
*   Inclusion Area
************************************************************
*/

#include "netx500_regdef.h"

#ifndef __NETX500_IO_AREAS_H__
#define __NETX500_IO_AREAS_H__


extern NX500_ASIC_CTRL_AREA_T * const ptAsicCtrlArea;
extern NX500_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea;
extern NX500_EXTMEM_PRIORITY_CTRL_AREA_T * const ptExtmemPriorityCtrlArea;
extern NX500_WATCHDOG_AREA_T * const ptWatchdogArea;
extern NX500_GPIO_AREA_T * const ptGpioArea;
extern NX500_PIO_AREA_T * const ptPioArea;
extern NX500_UART_AREA_T * const ptUart0Area;
extern NX500_UART_AREA_T * const ptUart1Area;
extern NX500_UART_AREA_T * const ptUart2Area;
extern NX500_MIIMU_AREA_T * const ptMiimuArea;
extern NX500_SPI_AREA_T * const ptSpiArea;
extern NX500_I2C_AREA_T * const ptI2cArea;
extern NX500_CRC_AREA_T * const ptCrcArea;
extern NX500_SYSTIME_AREA_T * const ptSystimeArea;
extern NX500_RTC_AREA_T * const ptRtcArea;
extern NX500_HOST_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptHostControlledDmaRegisterBlockArea;
extern NX500_HOST_CONTROLLED_GLOBAL_REGISTER_BLOCK_AREA_T * const ptHostControlledGlobalRegisterBlockArea;
extern NX500_HOST_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptHostControlledHandshakeRegisterBlockArea;
extern NX500_NETX_CONTROLLED_DMA_REGISTER_BLOCK_AREA_T * const ptNetxControlledDmaRegisterBlockArea;
extern NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const ptNetxControlledGlobalRegisterBlock1Area;
extern NX500_NETX_CONTROLLED_HANDSHAKE_REGISTER_BLOCK_AREA_T * const ptNetxControlledHandshakeRegistrtBlockArea;
extern NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const ptNetxControlledGlobalRegisterBlock2Area;
extern NX500_LCD_CTRL_AREA_T * const ptLcdCtrlArea;
extern NX500_USB_CORE_AREA_T * const ptUsbCoreArea;
extern NX500_USB_FIFO_AREA_T * const ptUsbFifoArea;
extern NX500_XC_AREA_T * const ptXcArea;
extern NX500_XMAC_AREA_T * const ptXmac0Area;
extern NX500_XMAC_AREA_T * const ptXmac1Area;
extern NX500_XMAC_AREA_T * const ptXmac2Area;
extern NX500_XMAC_AREA_T * const ptXmac3Area;
extern NX500_POINTER_FIFO_AREA_T * const ptPointerFifoArea;
extern NX500_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea;
extern NX500_XC_MEM_PROT_AREA_T * const ptXcMemProtArea;
extern NX500_XC_DEBUG_AREA_T * const ptDebugArea;
extern NX500_XPEC_AREA_T * const ptXpec0Area;
extern NX500_XPEC_AREA_T * const ptXpec1Area;
extern NX500_XPEC_AREA_T * const ptXpec2Area;
extern NX500_XPEC_AREA_T * const ptXpec3Area;
extern NX500_XC_EXTBUS_SEL_AREA_T * const ptExtbusSelArea;
extern NX500_VIC_AREA_T * const ptVicArea;
extern NX500_HIF_AHBLS6_AREA_T * const ptHifAhbls6Area;


#endif  /*  __NETX500_IO_AREAS_H__ */
