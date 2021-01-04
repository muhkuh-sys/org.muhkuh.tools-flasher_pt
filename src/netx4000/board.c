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


#include "board.h"
#include "flasher_interface.h"

/*-------------------------------------------------------------------------*/

static const UNIT_DESCRIPTION_T atUnits[] =
{
	{ .ucBus=BUS_SPI,      .ucUnit=0, .ucCS=0, .ucFlags=0, .acId="SQI0_CS0" },
	{ .ucBus=BUS_SPI,      .ucUnit=0, .ucCS=1, .ucFlags=0, .acId="SQI0_CS1" },
	{ .ucBus=BUS_SPI,      .ucUnit=0, .ucCS=2, .ucFlags=0, .acId="SQI0_CS2" },
	{ .ucBus=BUS_SPI,      .ucUnit=1, .ucCS=0, .ucFlags=0, .acId="SQI1_CS0" },
	{ .ucBus=BUS_SPI,      .ucUnit=1, .ucCS=1, .ucFlags=0, .acId="SQI1_CS1" },
	{ .ucBus=BUS_SPI,      .ucUnit=1, .ucCS=2, .ucFlags=0, .acId="SQI1_CS2" },
	{ .ucBus=BUS_SPI,      .ucUnit=2, .ucCS=0, .ucFlags=0, .acId="SPI_CS0" },
	{ .ucBus=BUS_SPI,      .ucUnit=2, .ucCS=1, .ucFlags=0, .acId="SPI_CS1" },
	{ .ucBus=BUS_SPI,      .ucUnit=2, .ucCS=2, .ucFlags=0, .acId="SPI_CS2" },
	{ .ucBus=BUS_SPI,      .ucUnit=3, .ucCS=0, .ucFlags=0, .acId="SPI_XPIC3_CS0" },
	{ .ucBus=BUS_SPI,      .ucUnit=3, .ucCS=1, .ucFlags=0, .acId="SPI_XPIC3_CS1" },
	{ .ucBus=BUS_SPI,      .ucUnit=3, .ucCS=2, .ucFlags=0, .acId="SPI_XPIC3_CS2" },
	{ .ucBus=BUS_ParFlash, .ucUnit=0, .ucCS=0, .ucFlags=0, .acId="PFL_MEM_CS0" },
	{ .ucBus=BUS_ParFlash, .ucUnit=0, .ucCS=1, .ucFlags=0, .acId="PFL_MEM_CS1" },
	{ .ucBus=BUS_ParFlash, .ucUnit=0, .ucCS=2, .ucFlags=0, .acId="PFL_MEM_CS2" },
	{ .ucBus=BUS_ParFlash, .ucUnit=0, .ucCS=3, .ucFlags=0, .acId="PFL_MEM_CS3" },
	{ .ucBus=BUS_ParFlash, .ucUnit=1, .ucCS=0, .ucFlags=0, .acId="PFL_EXT_CS0" },
	{ .ucBus=BUS_ParFlash, .ucUnit=1, .ucCS=1, .ucFlags=0, .acId="PFL_EXT_CS1" },
	{ .ucBus=BUS_ParFlash, .ucUnit=1, .ucCS=2, .ucFlags=0, .acId="PFL_EXT_CS2" },
	{ .ucBus=BUS_ParFlash, .ucUnit=1, .ucCS=3, .ucFlags=0, .acId="PFL_EXT_CS3" },
	{ .ucBus=BUS_ParFlash, .ucUnit=2, .ucCS=0, .ucFlags=0, .acId="PFL_RAP_SRAM_CS0" },
	{ .ucBus=BUS_ParFlash, .ucUnit=2, .ucCS=1, .ucFlags=0, .acId="PFL_RAP_SRAM_CS1" },
	{ .ucBus=BUS_SDIO,     .ucUnit=0, .ucCS=0, .ucFlags=0, .acId="SDIO" }
};

/*-------------------------------------------------------------------------*/


NETX_CONSOLEAPP_RESULT_T board_init(void)
{
	return NETX_CONSOLEAPP_RESULT_OK;
}


void board_get_unit_description(const void **ppvBuffer, unsigned int *psizBuffer)
{
	*ppvBuffer = atUnits;
	*psizBuffer = sizeof(atUnits);
}
