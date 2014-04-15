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
	SMC_NO_OPERATION           = 0,  /* no operation */
	SMC_ACTIVATE_CHIP_SELECT   = 1,  /* activate chip select */
	SMC_DEACTIVATE_CHIP_SELECT = 2,  /* deactivate the chip select line */
	SMC_EXCHANGE_DATA          = 3,
	SMC_SEND_DATA              = 4,
	SMC_RECEIVE_DATA           = 5,
	SMC_SEND_IDLE_BYTES        = 6,
	SMC_MASK_BUFFER            = 7,
	SMC_COMPARE_BUFFER         = 8,
	SMC_JUMP                   = 9,
	SMC_JUMP_EQUAL             = 10,
	SMC_JUMP_NOT_EQUAL         = 11,
	SMC_JUMP_ZERO              = 12,
	SMC_JUMP_NOT_ZERO          = 13
} SPI_MACRO_CMD_T;



NETX_CONSOLEAPP_RESULT_T spi_macro_player(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter);



#endif  /* __SPI_MACRO_PLAYER_H__ */

