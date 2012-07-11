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


#include "flasher_header.h"

#include "flasher_interface.h"
#include "flasher_version.h"
#include "netx_consoleapp.h"


const FLASHER_VERSION_T flasher_version =
{
	.abMagic = { FLASHER_MAGIC0, FLASHER_MAGIC1, FLASHER_MAGIC2, FLASHER_MAGIC3 },

	.ulVersionMaj = FLASHER_VERSION_MAJ,
	.ulVersionMin = FLASHER_VERSION_MIN,
	.acVersionVcs = FLASHER_VERSION_VCS,

	.pulLoadAddress = __LOAD_ADDRESS__,
	.pfnExecutionAddress = start,

	.pucBuffer_Parameter = __BUFFER_START__,
	.pucBuffer_DeviceDescription = __BUFFER_START__ + sizeof(NETX_CONSOLEAPP_PARAMETER_T) + sizeof(tFlasherInputParameter),
	.pucBuffer_Data = __BUFFER_START__ + sizeof(NETX_CONSOLEAPP_PARAMETER_T) + sizeof(tFlasherInputParameter) + sizeof(DEVICE_DESCRIPTION_T),
	.pucBuffer_End = __BUFFER_END__,

	.aulChiptyp =
	{
		FLASHER_CHIPTYP0_NETX56,

		0
	},
	.aulIf =
	{
		FLASHER_IF0_NETX56_PFSRAM |
		FLASHER_IF0_NETX56_SPI,

		0,

		0,

		0
	}
};

/*-----------------------------------*/

