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


#include <string.h>

#include "spi_macro_player.h"

#include "netx_io_areas.h"
#include "spi_flash.h"
#include "uprintf.h"


#if CFG_DEBUGMSG==1
	static unsigned long ulDebugMessages;
	#define DEBUGZONE(n)  (ulDebugMessages&(0x00000001<<(n)))

	/*
	 * These defines must match the ZONE_* defines
	 */
	#define DBG_ZONE_ERROR          0
	#define DBG_ZONE_WARNING        1
	#define DBG_ZONE_FUNCTION       2
	#define DBG_ZONE_INIT           3
	#define DBG_ZONE_VERBOSE        7

	#define ZONE_ERROR              DEBUGZONE(DBG_ZONE_ERROR)
	#define ZONE_WARNING            DEBUGZONE(DBG_ZONE_WARNING)
	#define ZONE_FUNCTION           DEBUGZONE(DBG_ZONE_FUNCTION)
	#define ZONE_INIT               DEBUGZONE(DBG_ZONE_INIT)
	#define ZONE_VERBOSE            DEBUGZONE(DBG_ZONE_VERBOSE)

	#define DEBUGMSG(cond,...) ((void)((cond)?(uprintf(__VA_ARGS__)),1:0))
#else
	#define DEBUGMSG(cond,...) ((void)0)
#endif


/*-------------------------------------------------------------------------*/


typedef int (*PFN_SPI_MACRO_HANDLER_T)(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev);

typedef struct SPI_MACRO_HANDLER_TABLE_STRUCT
{
	SPI_MACRO_CMD_T tCmd;
	PFN_SPI_MACRO_HANDLER_T pfnHandler;
} SPI_MACRO_HANDLER_TABLE_T;


/*-------------------------------------------------------------------------*/


static int SMC_Handler_Initialize(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev)
{
	int iResult;
	const FLASHER_SPI_CONFIGURATION_T *ptSpiCfg;


	uprintf("[SMC] initialize\n");

	ptSpiCfg = &(ptCfg->tInit.tSpi);

	/* Clear the complete configuration. */
	memset(ptSpiDev, 0, sizeof(FLASHER_SPI_CFG_T));

	/* Get the driver. */
	iResult = board_get_spi_driver(ptSpiCfg, ptSpiDev);

	return iResult;
}



static int SMC_Handler_ChipSelect(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev)
{
	int iResult;


	uprintf("[SMC] chip select: %d\n", ptCfg->tChipSelect.iActive);

	iResult = ptSpiDev->pfnSelect(ptSpiDev, ptCfg->tChipSelect.iActive);

	return iResult;
}



static int SMC_Handler_ExchangeData(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev)
{
	int iResult;


	uprintf("[SMC] exchange data\n");

	uprintf("[SMC] send:\n");
	hexdump(ptCfg->tExchangeData.pucTxBuffer, ptCfg->tExchangeData.sizBuffer);

	iResult = ptSpiDev->pfnExchangeData(ptSpiDev, ptCfg->tExchangeData.pucTxBuffer, ptCfg->tExchangeData.pucRxBuffer, ptCfg->tExchangeData.sizBuffer);
	if( iResult!=0 )
	{
		uprintf("ERROR: failed to exchange data!\n");
	}
	else
	{
		uprintf("[SMC] received:\n");
		hexdump(ptCfg->tExchangeData.pucRxBuffer, ptCfg->tExchangeData.sizBuffer);
	}

	return iResult;
}



static int SMC_Handler_SendData(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev)
{
	int iResult;


	uprintf("[SMC] send data:\n");
	hexdump(ptCfg->tSendData.pucTxBuffer, ptCfg->tSendData.sizTxBuffer);

	iResult = ptSpiDev->pfnSendData(ptSpiDev, ptCfg->tSendData.pucTxBuffer, ptCfg->tSendData.sizTxBuffer);
	if( iResult!=0 )
	{
		uprintf("ERROR: failed to send the data!\n");
	}

	return iResult;
}



static int SMC_Handler_ReceiveData(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev)
{
	int iResult;


	uprintf("[SMC] receive %d bytes to 0x%08x\n", ptCfg->tReceiveData.sizRxBuffer, ptCfg->tReceiveData.pucRxBuffer);

	iResult = ptSpiDev->pfnReceiveData(ptSpiDev, ptCfg->tReceiveData.pucRxBuffer, ptCfg->tReceiveData.sizRxBuffer);
	if( iResult!=0 )
	{
		uprintf("ERROR: failed to receive data!\n");
	}
	else
	{
		uprintf("[SMC] received:\n");
		hexdump(ptCfg->tReceiveData.pucRxBuffer, ptCfg->tReceiveData.sizRxBuffer);
	}

	return iResult;
}



static int SMC_Handler_SendIdleBytes(const SPI_MACRO_PARAMETER_T *ptCfg, FLASHER_SPI_CFG_T *ptSpiDev)
{
	int iResult;


	uprintf("[SMC] send %d idle bytes\n", ptCfg->tIdleBytes.sizIdleBytes);

	iResult = ptSpiDev->pfnSendIdle(ptSpiDev, ptCfg->tIdleBytes.sizIdleBytes);
	if( iResult!=0 )
	{
		uprintf("ERROR: failed to send idle bytes data!\n");
	}

	return iResult;
}



/*-------------------------------------------------------------------------*/


static const SPI_MACRO_HANDLER_TABLE_T atCmdHandler[] =
{
	{ SMC_INITIALIZE,         SMC_Handler_Initialize },
	{ SMC_CHIP_SELECT,        SMC_Handler_ChipSelect },
	{ SMC_EXCHANGE_DATA,      SMC_Handler_ExchangeData },
	{ SMC_SEND_DATA,          SMC_Handler_SendData },
	{ SMC_RECEIVE_DATA,       SMC_Handler_ReceiveData },
	{ SMC_SEND_IDLE_BYTES,    SMC_Handler_SendIdleBytes }
};


NETX_CONSOLEAPP_RESULT_T spi_macro_player(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;
	unsigned long ulValue;
	SPI_MACRO_CMD_T tCmd;
	const SPI_MACRO_HANDLER_TABLE_T *ptCnt;
	const SPI_MACRO_HANDLER_TABLE_T *ptEnd;
	PFN_SPI_MACRO_HANDLER_T pfnHandler;


#if CFG_DEBUGMSG==1
	ulDebugMessages = 0xffffffff;
#endif

	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	ulValue = ptParameter->ulCommand;
	iResult = -1;
	switch( ulValue )
	{
	case SMC_INITIALIZE:
	case SMC_CHIP_SELECT:
	case SMC_EXCHANGE_DATA:
	case SMC_SEND_DATA:
	case SMC_RECEIVE_DATA:
	case SMC_SEND_IDLE_BYTES:
		tCmd = (SPI_MACRO_CMD_T)ulValue;
		iResult = 0;
		break;
	}

	if( iResult!=0 )
	{
		uprintf("Unknown command: 0x%08x\n", ulValue);
	}
	else
	{
		/* Get the command handler. */
		pfnHandler = NULL;
		ptCnt = atCmdHandler;
		ptEnd = atCmdHandler + (sizeof(atCmdHandler)/sizeof(atCmdHandler[0]));
		while( ptCnt<ptEnd )
		{
			if( ptCnt->tCmd==tCmd )
			{
				pfnHandler = ptCnt->pfnHandler;
				break;
			}
			++ptCnt;
		}

		if( pfnHandler==NULL )
		{
			uprintf("No handler for command!\n");
		}
		else
		{
			iResult = pfnHandler(&(ptParameter->uCfg), ptParameter->ptSpiDev);
			if( iResult==0 )
			{
				tResult = NETX_CONSOLEAPP_RESULT_OK;
			}
		}
	}

	return tResult;
}


