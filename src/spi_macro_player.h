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
	SMC_INITIALIZE             = 0,
	SMC_CHIP_SELECT            = 1,
	SMC_EXCHANGE_DATA          = 2,
	SMC_SEND_DATA              = 3,
	SMC_RECEIVE_DATA           = 4,
	SMC_SEND_IDLE_BYTES        = 5
} SPI_MACRO_CMD_T;



typedef struct SPI_MACRO_PARAMETER_INIT_STRUCT
{
	SPI_CONFIGURATION_T tSpi;
} SPI_MACRO_PARAMETER_INIT_T;


typedef struct SPI_MACRO_PARAMETER_CHIPSELECT_STRUCT
{
	int iActive;
} SPI_MACRO_PARAMETER_CHIPSELECT_T;


typedef struct SPI_MACRO_PARAMETER_EXCHANGE_STRUCT
{
	const unsigned char *pucTxBuffer;
	unsigned char *pucRxBuffer;
	size_t sizBuffer;
} SPI_MACRO_PARAMETER_EXCHANGE_T;


typedef struct SPI_MACRO_PARAMETER_SEND_STRUCT
{
	const unsigned char *pucTxBuffer;
	size_t sizTxBuffer;
} SPI_MACRO_PARAMETER_SEND_T;


typedef struct SPI_MACRO_PARAMETER_RECEIVE_STRUCT
{
	unsigned char *pucRxBuffer;
	size_t sizRxBuffer;
} SPI_MACRO_PARAMETER_RECEIVE_T;


typedef struct SPI_MACRO_PARAMETER_IDLE_STRUCT
{
	size_t sizIdleBytes;
} SPI_MACRO_PARAMETER_IDLE_T;


typedef union SPI_MACRO_PARAMETER_UNION
{
	SPI_MACRO_PARAMETER_INIT_T tInit;
	SPI_MACRO_PARAMETER_CHIPSELECT_T tChipSelect;
	SPI_MACRO_PARAMETER_EXCHANGE_T tExchangeData;
	SPI_MACRO_PARAMETER_SEND_T tSendData;
	SPI_MACRO_PARAMETER_RECEIVE_T tReceiveData;
	SPI_MACRO_PARAMETER_IDLE_T tIdleBytes;
} SPI_MACRO_PARAMETER_T;


typedef struct CMD_PARAMETER_SPIMACROPLAYER_STRUCT
{
	unsigned long ulCommand;
	SPI_CFG_T *ptSpiDev;
	SPI_MACRO_PARAMETER_T uCfg;
} CMD_PARAMETER_SPIMACROPLAYER_T;


NETX_CONSOLEAPP_RESULT_T spi_macro_player(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter);



#endif  /* __SPI_MACRO_PLAYER_H__ */

