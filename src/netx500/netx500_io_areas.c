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

#include "netx500_io_areas.h"


NX500_ASIC_CTRL_AREA_T * const					ptNetXAsicCtrlArea =		(NX500_ASIC_CTRL_AREA_T * const)Addr_NX500_asic_ctrl;
NX500_SPI_AREA_T * const					ptNetXSpi0Area =                (NX500_SPI_AREA_T * const) Addr_NX500_spi;
NX500_GPIO_AREA_T * const					ptNetXGpioArea =                (NX500_GPIO_AREA_T * const) Addr_NX500_gpio;
NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const	ptNetXGlobalRegBlock1Area =     (NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const)Addr_NX500_netx_controlled_global_register_block_1;
NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const	ptNetXGlobalRegBlock2Area =     (NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const)Addr_NX500_netx_controlled_global_register_block_2;

