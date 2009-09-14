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
extern NX500_SPI_AREA_T * const ptNetXSpi0Area;
extern NX500_GPIO_AREA_T * const ptNetXGpioArea;
extern NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_1_AREA_T * const ptNetXGlobalRegBlock1Area;
extern NX500_NETX_CONTROLLED_GLOBAL_REGISTER_BLOCK_2_AREA_T * const ptNetXGlobalRegBlock2Area;


#endif  /*  __NETX500_IO_AREAS_H__ */
