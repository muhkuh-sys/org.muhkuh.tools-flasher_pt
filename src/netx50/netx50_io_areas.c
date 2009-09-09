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

      IO Area for the netX50
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

#include "netx50_io_areas.h"


const PI2C_AREA_T                       ptNetXI2CArea               = (PI2C_AREA_T)                     Addr_NX50_i2c;               /* Pointer to I2C Master Control Register         */
const PSPI_AREA_T                       ptNetXSpi0Area              = (PSPI_AREA_T)                     Addr_NX50_spi0;              /* Pointer to SPI Control Register 0              */
const PUART_AREA_T                      ptNetXUartArea              = (PUART_AREA_T)                    Addr_NX50_uart0;             /* Pointer to UART Register                       */
const PGPIO_AREA_T                      ptNetXGpioArea              = (PGPIO_AREA_T)                    Addr_NX50_gpio;              /* Pointer to GPIO Register                       */
const PNETX_GLOBAL_REG_BLOCK_2_AREA_T   ptNetXGlobalRegBlock2Area   = (PNETX_GLOBAL_REG_BLOCK_2_AREA_T) Addr_NX50_netx_controlled_global_register_block_2;
const PNETX_GLOBAL_REG_BLOCK_1_AREA_T   ptNetXGlobalRegBlock1Area   = (PNETX_GLOBAL_REG_BLOCK_1_AREA_T) Adr_NX50_sta_netx;
