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


#define SPI_MACRO_RECEIVE_BUFFER_SIZE 16



typedef struct SPI_MACRO_STRUCT
{
	SPI_CFG_T *ptSpiDev;
	const unsigned char *pucMacroStart;
	const unsigned char *pucMacroCnt;
	const unsigned char *pucMacroEnd;

	unsigned int uiFlag_Equal;
	unsigned int uiFlag_Zero;

	unsigned char aucReceiveBuffer[SPI_MACRO_RECEIVE_BUFFER_SIZE];
} SPI_MACRO_T;


typedef int (*PFN_SPI_MACRO_HANDLER_T)(SPI_MACRO_T *ptCfg);

typedef struct SPI_MACRO_HANDLER_TABLE_STRUCT
{
	SPI_MACRO_CMD_T tCmd;
	PFN_SPI_MACRO_HANDLER_T pfnHandler;
} SPI_MACRO_HANDLER_TABLE_T;


/*-------------------------------------------------------------------------*/


static int SMC_Handler_NoOperation(SPI_MACRO_T *ptCfg __attribute__((unused)))
{
	uprintf("[SMC] no operation\n");
	return 0;
}



static int SMC_Handler_ActivateChipSelect(SPI_MACRO_T *ptCfg)
{
	int iResult;
	SPI_CFG_T *ptSpiDev;


	uprintf("[SMC] activate chip select\n");
	ptSpiDev = ptCfg->ptSpiDev;
	iResult = ptSpiDev->pfnSelect(ptSpiDev, 1);

	return iResult;
}



static int SMC_Handler_DeactivateChipSelect(SPI_MACRO_T *ptCfg)
{
	int iResult;
	SPI_CFG_T *ptSpiDev;


	uprintf("[SMC] deactivate chip select\n");
	ptSpiDev = ptCfg->ptSpiDev;
	iResult = ptSpiDev->pfnSelect(ptSpiDev, 1);

	return iResult;
}



static int SMC_Handler_ExchangeData(SPI_MACRO_T *ptCfg)
{
	int iResult;
	SPI_CFG_T *ptSpiDev;
	const unsigned char *pucCnt;
	size_t sizData;


	uprintf("[SMC] exchange data\n");

	ptSpiDev = ptCfg->ptSpiDev;
	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs at least one parameter: the size. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting size, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the number of bytes. */
		sizData = (size_t)(*(pucCnt++));

		/* The number of bytes must not exceed the receive buffer size. */
		if( sizData>SPI_MACRO_RECEIVE_BUFFER_SIZE )
		{
			uprintf("ERROR: the number of bytes to exchange exceeds the size of the receive buffer: %d>%d\n", sizData, SPI_MACRO_RECEIVE_BUFFER_SIZE);
			iResult = -1;
		}
		else if( sizData==0 )
		{
			iResult = 0;
		}
		else
		{
			/* Are enough bytes left in the macro? */
			if( (pucCnt+sizData)>(ptCfg->pucMacroEnd) )
			{
				uprintf("ERROR: Expecting %d data bytes, but the macro is too short!\n", sizData);
				iResult = -1;
			}
			else
			{
				uprintf("[SMC] send:\n");
				hexdump(pucCnt, sizData);

				iResult = ptSpiDev->pfnExchangeData(ptSpiDev, pucCnt, ptCfg->aucReceiveBuffer, sizData);
				if( iResult!=0 )
				{
					uprintf("ERROR: failed to exchange data!\n");
					iResult = -1;
				}
				else
				{
					uprintf("[SMC] received:\n");
					hexdump(ptCfg->aucReceiveBuffer, sizData);

					pucCnt += sizData;

					iResult = 0;
				}
			}
		}
	}

	ptCfg->pucMacroCnt = pucCnt;

	return iResult;
}



static int SMC_Handler_SendData(SPI_MACRO_T *ptCfg)
{
	int iResult;
	SPI_CFG_T *ptSpiDev;
	const unsigned char *pucCnt;
	size_t sizData;


	uprintf("[SMC] send data\n");

	ptSpiDev = ptCfg->ptSpiDev;
	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs at least one parameter: the size. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting size, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the number of bytes. */
		sizData = (size_t)(*(pucCnt++));

		if( sizData==0 )
		{
			iResult = 0;
		}
		else
		{
			/* Are enough bytes left in the macro? */
			if( (pucCnt+sizData)>(ptCfg->pucMacroEnd) )
			{
				uprintf("ERROR: Expecting %d data bytes, but the macro is too short!\n", sizData);
				iResult = -1;
			}
			else
			{
				uprintf("[SMC] send:\n");
				hexdump(pucCnt, sizData);

				iResult = ptSpiDev->pfnSendData(ptSpiDev, pucCnt, sizData);
				if( iResult!=0 )
				{
					uprintf("ERROR: failed to send the data!\n");
					iResult = -1;
				}
				else
				{
					pucCnt += sizData;
					iResult = 0;
				}
			}
		}
	}

	ptCfg->pucMacroCnt = pucCnt;

	return iResult;
}



static int SMC_Handler_ReceiveData(SPI_MACRO_T *ptCfg)
{
	int iResult;
	SPI_CFG_T *ptSpiDev;
	const unsigned char *pucCnt;
	size_t sizData;


	uprintf("[SMC] receive data\n");

	ptSpiDev = ptCfg->ptSpiDev;
	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the size. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting size, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the number of bytes. */
		sizData = (size_t)(*(pucCnt++));

		/* The number of bytes must not exceed the receive buffer size. */
		if( sizData>SPI_MACRO_RECEIVE_BUFFER_SIZE )
		{
			uprintf("ERROR: the number of bytes to receive exceeds the size of the receive buffer: %d>%d\n", sizData, SPI_MACRO_RECEIVE_BUFFER_SIZE);
			iResult = -1;
		}
		else if( sizData==0 )
		{
			iResult = 0;
		}
		else
		{
			iResult = ptSpiDev->pfnReceiveData(ptSpiDev, ptCfg->aucReceiveBuffer, sizData);
			if( iResult!=0 )
			{
				uprintf("ERROR: failed to receive data!\n");
				iResult = -1;
			}
			else
			{
				uprintf("[SMC] received:\n");
				hexdump(ptCfg->aucReceiveBuffer, sizData);

				iResult = 0;
			}
		}
	}

	ptCfg->pucMacroCnt = pucCnt;

	return iResult;
}



static int SMC_Handler_SendIdleBytes(SPI_MACRO_T *ptCfg)
{
	int iResult;
	SPI_CFG_T *ptSpiDev;
	const unsigned char *pucCnt;
	size_t sizData;


	uprintf("[SMC] send idle bytes\n");

	ptSpiDev = ptCfg->ptSpiDev;
	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the size. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting size, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the number of bytes. */
		sizData = (size_t)(*(pucCnt++));

		iResult = ptSpiDev->pfnSendIdle(ptSpiDev, sizData);
		if( iResult!=0 )
		{
			uprintf("ERROR: failed to send idle bytes data!\n");
			iResult = -1;
		}
		else
		{
			iResult = 0;
		}
	}

	ptCfg->pucMacroCnt = pucCnt;

	return iResult;
}



static int SMC_Handler_MaskBuffer(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizData;
	size_t sizCnt;
	unsigned char ucData;
	unsigned int uiZero;


	uprintf("[SMC] mask buffer\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs at least one parameter: the size. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting size, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the number of bytes. */
		sizData = (size_t)(*(pucCnt++));

		/* The number of bytes must not exceed the receive buffer size. */
		if( sizData>SPI_MACRO_RECEIVE_BUFFER_SIZE )
		{
			uprintf("ERROR: the number of bytes to mask exceeds the size of the receive buffer: %d>%d\n", sizData, SPI_MACRO_RECEIVE_BUFFER_SIZE);
			iResult = -1;
		}
		else if( sizData==0 )
		{
			iResult = 0;
		}
		else
		{
			/* Are enough bytes left in the macro? */
			if( (pucCnt+sizData)>(ptCfg->pucMacroEnd) )
			{
				uprintf("ERROR: Expecting %d data bytes, but the macro is too short!\n", sizData);
				iResult = -1;
			}
			else
			{
				uprintf("[SMC] buffer:\n");
				hexdump(ptCfg->aucReceiveBuffer, sizData);

				uprintf("[SMC] mask:\n");
				hexdump(pucCnt, sizData);

				/* Expect that all masked bytes will be zero. */
				uiZero = 1;
				sizCnt = 0;
				do
				{
					ucData  = ptCfg->aucReceiveBuffer[sizCnt];
					ucData &= pucCnt[sizCnt];
					ptCfg->aucReceiveBuffer[sizCnt] = ucData;

					if( ucData!=0x00 )
					{
						/* This byte is not zero. */
						uiZero = 0;
					}

					++sizCnt;
				} while( sizCnt<sizData );

				/* Set the new zero flag. */
				ptCfg->uiFlag_Zero = uiZero;

				uprintf("[SMC] result:\n");
				hexdump(ptCfg->aucReceiveBuffer, sizData);

				pucCnt += sizData;

				iResult = 0;
			}
		}
	}

	ptCfg->pucMacroCnt = pucCnt;

	return iResult;
}



static int SMC_Handler_CompareBuffer(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizData;
	size_t sizCnt;
	unsigned char ucData;
	unsigned int uiEqual;


	uprintf("[SMC] compare buffer\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs at least one parameter: the size. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting size, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the number of bytes. */
		sizData = (size_t)(*(pucCnt++));

		/* The number of bytes must not exceed the receive buffer size. */
		if( sizData>SPI_MACRO_RECEIVE_BUFFER_SIZE )
		{
			uprintf("ERROR: the number of bytes to compare exceeds the size of the receive buffer: %d>%d\n", sizData, SPI_MACRO_RECEIVE_BUFFER_SIZE);
			iResult = -1;
		}
		else if( sizData==0 )
		{
			iResult = 0;
		}
		else
		{
			/* Are enough bytes left in the macro? */
			if( (pucCnt+sizData)>(ptCfg->pucMacroEnd) )
			{
				uprintf("ERROR: Expecting %d data bytes, but the macro is too short!\n", sizData);
				iResult = -1;
			}
			else
			{
				uprintf("[SMC] buffer:\n");
				hexdump(ptCfg->aucReceiveBuffer, sizData);

				uprintf("[SMC] compare:\n");
				hexdump(pucCnt, sizData);

				/* Expect that all bytes will match. */
				uiEqual = 1;
				sizCnt = 0;
				do
				{
					ucData = ptCfg->aucReceiveBuffer[sizCnt];
					if( ucData!=pucCnt[sizCnt] )
					{
						/* This byte does not match. */
						uiEqual = 0;
					}

					++sizCnt;
				} while( sizCnt<sizData );

				/* Set the new zero flag. */
				ptCfg->uiFlag_Equal = uiEqual;

				pucCnt += sizData;

				iResult = 0;
			}
		}
	}

	ptCfg->pucMacroCnt = pucCnt;

	return iResult;
}



static int SMC_Handler_Jump(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizOffset;


	uprintf("[SMC] jump\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the offset. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting offset, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the offset. */
		sizOffset = (size_t)(*(pucCnt++));

		/* Set the new pointer. */
		ptCfg->pucMacroCnt = ptCfg->pucMacroStart + sizOffset;

		iResult = 0;
	}

	return iResult;
}



static int SMC_Handler_JumpEqual(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizOffset;


	uprintf("[SMC] jump equal\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the offset. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting offset, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the offset. */
		sizOffset = (size_t)(*(pucCnt++));

		if( ptCfg->uiFlag_Equal!=0 )
		{
			/* Set the new pointer. */
			ptCfg->pucMacroCnt = ptCfg->pucMacroStart + sizOffset;
		}

		iResult = 0;
	}

	return iResult;
}



static int SMC_Handler_JumpNotEqual(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizOffset;


	uprintf("[SMC] jump not equal\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the offset. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting offset, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the offset. */
		sizOffset = (size_t)(*(pucCnt++));

		if( ptCfg->uiFlag_Equal==0 )
		{
			/* Set the new pointer. */
			ptCfg->pucMacroCnt = ptCfg->pucMacroStart + sizOffset;
		}

		iResult = 0;
	}

	return iResult;
}



static int SMC_Handler_JumpZero(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizOffset;


	uprintf("[SMC] jump zero\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the offset. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting offset, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the offset. */
		sizOffset = (size_t)(*(pucCnt++));

		if( ptCfg->uiFlag_Zero!=0 )
		{
			/* Set the new pointer. */
			ptCfg->pucMacroCnt = ptCfg->pucMacroStart + sizOffset;
		}

		iResult = 0;
	}

	return iResult;
}



static int SMC_Handler_JumpNotZero(SPI_MACRO_T *ptCfg)
{
	int iResult;
	const unsigned char *pucCnt;
	size_t sizOffset;


	uprintf("[SMC] jump not zero\n");

	pucCnt = ptCfg->pucMacroCnt;

	/* The command needs one parameter: the offset. */
	if( (pucCnt+1)>(ptCfg->pucMacroEnd) )
	{
		uprintf("ERROR: Expecting offset, but the macro is too short!\n");
		iResult = -1;
	}
	else
	{
		/* Get the offset. */
		sizOffset = (size_t)(*(pucCnt++));

		if( ptCfg->uiFlag_Zero==0 )
		{
			/* Set the new pointer. */
			ptCfg->pucMacroCnt = ptCfg->pucMacroStart + sizOffset;
		}

		iResult = 0;
	}

	return iResult;
}

/*-------------------------------------------------------------------------*/


static const SPI_MACRO_HANDLER_TABLE_T atCmdHandler[] =
{
	{ SMC_NO_OPERATION,           SMC_Handler_NoOperation },
	{ SMC_ACTIVATE_CHIP_SELECT,   SMC_Handler_ActivateChipSelect },
	{ SMC_DEACTIVATE_CHIP_SELECT, SMC_Handler_DeactivateChipSelect },
	{ SMC_EXCHANGE_DATA,          SMC_Handler_ExchangeData },
	{ SMC_SEND_DATA,              SMC_Handler_SendData },
	{ SMC_RECEIVE_DATA,           SMC_Handler_ReceiveData },
	{ SMC_SEND_IDLE_BYTES,        SMC_Handler_SendIdleBytes },
	{ SMC_MASK_BUFFER,            SMC_Handler_MaskBuffer },
	{ SMC_COMPARE_BUFFER,         SMC_Handler_CompareBuffer },
	{ SMC_JUMP,                   SMC_Handler_Jump },
	{ SMC_JUMP_EQUAL,             SMC_Handler_JumpEqual },
	{ SMC_JUMP_NOT_EQUAL,         SMC_Handler_JumpNotEqual },
	{ SMC_JUMP_ZERO,              SMC_Handler_JumpZero },
	{ SMC_JUMP_NOT_ZERO,          SMC_Handler_JumpNotZero }
};


static NETX_CONSOLEAPP_RESULT_T execute_sequence(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter, SPI_CFG_T *ptSpiDev)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	SPI_MACRO_T tSpiMacro;
	int iResult;
	const SPI_MACRO_HANDLER_TABLE_T *ptCnt;
	const SPI_MACRO_HANDLER_TABLE_T *ptEnd;
	SPI_MACRO_CMD_T tCmd;
	PFN_SPI_MACRO_HANDLER_T pfnHandler;


	/* Be optimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_OK;

	tSpiMacro.ptSpiDev = ptSpiDev;
	tSpiMacro.pucMacroStart = ptParameter->pucBuffer;
	tSpiMacro.pucMacroCnt = ptParameter->pucBuffer;
	tSpiMacro.pucMacroEnd = ptParameter->pucBuffer + ptParameter->sizBuffer;
	tSpiMacro.uiFlag_Equal = 0;
	tSpiMacro.uiFlag_Zero = 0;
	memset(tSpiMacro.aucReceiveBuffer, 0, SPI_MACRO_RECEIVE_BUFFER_SIZE);

	ptEnd = atCmdHandler + (sizeof(atCmdHandler)/sizeof(atCmdHandler[0]));

	/* Loop over the complete macro buffer. */
	while( tSpiMacro.pucMacroCnt<tSpiMacro.pucMacroEnd )
	{
		tCmd = (SPI_MACRO_CMD_T)(*(tSpiMacro.pucMacroCnt++));

		ptCnt = atCmdHandler;
		pfnHandler = NULL;
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
			uprintf("ERROR: Unknown command: 0x%02x\n", tCmd);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			break;
		}
		else
		{
			/* Call the handler. */
			iResult = pfnHandler(&tSpiMacro);
			if( iResult!=0 )
			{
				uprintf("ERROR: Failed to execute the command 0x%02x!\n");
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				break;
			}
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T spi_macro_player(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;
	SPI_CONFIGURATION_T *ptSpiCfg;
	SPI_CFG_T tSpiDev;


	uprintf("*** SPI Macro Player ***\n");
	uprintf("Macro:\n");
	hexdump(ptParameter->pucBuffer, ptParameter->sizBuffer);

#if CFG_DEBUGMSG==1
	ulDebugMessages = 0xffffffff;
#endif

	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	ptSpiCfg = &(ptParameter->tSpi);

	/* Get the driver. */
	iResult = board_get_spi_driver(ptSpiCfg, &tSpiDev);
	if( iResult!=0 )
	{
		uprintf("Failed to initialize the board driver!\n");
	}
	else
	{
		tResult = execute_sequence(ptParameter, &tSpiDev);
	}

	return tResult;
}


