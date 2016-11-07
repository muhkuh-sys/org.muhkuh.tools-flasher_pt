/*************************************************************************** 
 *   Copyright (C) 2016 by Hilscher GmbH                                   *
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


#include "board.h"

#include "units.h"


/*-------------------------------------------------------------------------*/


static const UNIT_TABLE_T tUnitTable_BusSPI =
{
	.sizEntries = 4,
	.atEntries =
	{
		{ 0,  "SQI",       (void * const)HOSTADDR(sqi) },
		{ 1,  "SPI0_APP",  (void * const)HOSTADDR(spi0_app) },
		{ 2,  "SPI1_APP",  (void * const)HOSTADDR(spi1_app) },
		{ 3,  "SPI2_APP",  (void * const)HOSTADDR(spi2_app) }
	}
};


const BUS_TABLE_T tBusTable =
{
	.sizEntries = 1,
	.atEntries =
	{
		{ BUS_SPI,       "Serial Flash",        &tUnitTable_BusSPI }
	}
};


/*-------------------------------------------------------------------------*/


NETX_CONSOLEAPP_RESULT_T board_init(void)
{
	return NETX_CONSOLEAPP_RESULT_OK;
}

