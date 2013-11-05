/***************************************************************************
 *   Copyright (C) 2013 by Hilscher GmbH                                   *
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


#include <stddef.h>

#include "flasher_interface.h"
#include "netx_consoleapp.h"


#ifndef __SPI_MACRO_PLAYER_H__
#define __SPI_MACRO_PLAYER_H__


typedef enum SPI_MACRO_CMD_ENUM
{
	SMP_SEND_NNN     = 1,  /* exchange bytes */
	SMP_SEND_SNN     = 2,  /* chip select, exchange bytes */
	SMP_SEND_SDN     = 3,  /* chip select, exchange bytes, chip deselect */
	SMP_SEND_SDD     = 4,  /* chip select, exchange bytes, chip deselect, 1 dummy transfer */
	SMP_RECEIVE_NNN  = 5,  /* exchange bytes */
	SMP_RECEIVE_SNN  = 6,  /* chip select, exchange bytes */
	SMP_RECEIVE_SDN  = 7,  /* chip select, exchange bytes, chip deselect */
	SMP_RECEIVE_SDD  = 8,  /* chip select, exchange bytes, chip deselect, 1 dummy transfer */
	SMP_DUMMY_NNN    = 9,  /* transfer n dummy bytes of 0x00 */
	SMP_DUMMY_SNN    = 10, /* transfer n dummy bytes of 0x00 */
	SMP_DUMMY_SDN    = 11, /* transfer n dummy bytes of 0x00 */
	SMP_DUMMY_SDD    = 12  /* transfer n dummy bytes of 0x00 */
} SPI_MACRO_CMD_T;



NETX_CONSOLEAPP_RESULT_T spi_macro_player(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter);



#endif  /* __SPI_MACRO_PLAYER_H__ */

