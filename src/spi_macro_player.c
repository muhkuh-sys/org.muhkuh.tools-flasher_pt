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
	#define DBG_ZONE_ERROR		0
	#define DBG_ZONE_WARNING	1
	#define DBG_ZONE_FUNCTION	2
	#define DBG_ZONE_INIT		3
	#define DBG_ZONE_VERBOSE	7

	#define ZONE_ERROR		DEBUGZONE(DBG_ZONE_ERROR)
	#define ZONE_WARNING		DEBUGZONE(DBG_ZONE_WARNING)
	#define ZONE_FUNCTION		DEBUGZONE(DBG_ZONE_FUNCTION)
	#define ZONE_INIT		DEBUGZONE(DBG_ZONE_INIT)
	#define ZONE_VERBOSE		DEBUGZONE(DBG_ZONE_VERBOSE)

	#define DEBUGMSG(cond,...) ((void)((cond)?(uprintf(__VA_ARGS__)),1:0))
#else
	#define DEBUGMSG(cond,...) ((void)0)
#endif

#if 0
static void qsi_seq_reset_input_buffer(QSI_CFG_T *ptQsiCfg)
{
	DEBUGMSG(ZONE_VERBOSE, ". reset the input buffer.\n");

	ptQsiCfg->sizBufferPos = 0;
	memset(ptQsiCfg->uBuffer.auc, 0, sizeof(ptQsiCfg->uBuffer.auc));
}


static void qsi_receive(QSI_CFG_T *ptQsiCfg, unsigned int uiParameter)
{
	HOSTDEF(ptSqiArea)
	unsigned long ulValue;
	unsigned char ucByte;
	size_t sizBufferPos;
	unsigned long ulData;
	unsigned int uiByteCnt;


	/* set mode to "receive" */
	ulValue  = ptQsiCfg->tCfg.ulTrcBase;
	ulValue |= 1 << HOSTSRT(sqi_tcr_duplex);
	/* set the transfer size */
	ulValue |= uiParameter << HOSTSRT(sqi_tcr_transfer_size);
	/* start the transfer */
	ulValue |= HOSTMSK(sqi_tcr_start_transfer);
	ptSqiArea->ulSqi_tcr = ulValue;

	/* get buffer position */
	sizBufferPos = ptQsiCfg->sizBufferPos;

	/* check the mode */
	if( (ptQsiCfg->tCfg.ulTrcBase&HOSTMSK(sqi_tcr_mode))==0 )
	{
		/* mode 0 : the fifo size is 8 bit */
		do
		{
			/* wait for one byte in the fifo */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_not_empty);
			} while( ulValue==0 );
			/* grab byte */
			ucByte = (unsigned char)(ptSqiArea->ulSqi_dr);
			ptQsiCfg->uBuffer.auc[sizBufferPos] = ucByte;
			DEBUGMSG(ZONE_VERBOSE, ". rec $%02x\n", ucByte);
			/* move and wrap buffer pointer */
			++sizBufferPos;
			sizBufferPos &= 0x0f;
		} while( (uiParameter--)>0 );
	}
	else
	{
		/* DSI/QSI mode : the fifo size is 32 bit */
		++uiParameter;
		do
		{
			/* wait for one byte in the fifo */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_not_empty);
			} while( ulValue==0 );

			/* get the dword */
			ulData = ptSqiArea->ulSqi_dr;
			DEBUGMSG(ZONE_VERBOSE, "received dw: $%08x\n", ulData);

			/* process the dword */
			uiByteCnt = 4;
			do
			{
				/* grab byte */
				ucByte = (unsigned char)ulData;
				ptQsiCfg->uBuffer.auc[sizBufferPos] = ucByte;
				DEBUGMSG(ZONE_VERBOSE, ". rec $%02x\n", ucByte);
				/* move to next byte */
				ulData >>= 8;
				--uiByteCnt;
				/* move and wrap buffer pointer */
				++sizBufferPos;
				sizBufferPos &= 0x0f;
				/* one byte processed */
				--uiParameter;
			} while( uiParameter!=0 && uiByteCnt!=0 );
		} while( uiParameter!=0 );
	}

	/* update buffer position */
	ptQsiCfg->sizBufferPos = sizBufferPos;

	/* wait until the transfer is done */
	do
	{
		ulValue  = ptSqiArea->ulSqi_sr;
		ulValue &= HOSTMSK(sqi_sr_busy);
	} while( ulValue!=0 );
}


static void qsi_send(QSI_CFG_T *ptQsiCfg, unsigned int uiParameter, const unsigned char *pucData)
{
	HOSTDEF(ptSqiArea)
	unsigned long ulValue;
	unsigned char ucSend;
	unsigned int uiShiftCnt;
	unsigned long ulSend;


	DEBUGMSG(ZONE_VERBOSE, ". sending %d bytes\n", uiParameter+1);

	/* set mode to "send" */
	ulValue  = ptQsiCfg->tCfg.ulTrcBase;
	ulValue |= 2 << HOSTSRT(sqi_tcr_duplex);
	/* set the transfer size */
	ulValue |= uiParameter << HOSTSRT(sqi_tcr_transfer_size);
	/* start the transfer */
	ulValue |= HOSTMSK(sqi_tcr_start_transfer);
	ptSqiArea->ulSqi_tcr = ulValue;

	/* check the mode */
	if( (ptQsiCfg->tCfg.ulTrcBase&HOSTMSK(sqi_tcr_mode))==0 )
	{
		/* mode 0 : the fifo size is 8 bit */
		do
		{
			/* wait for space in the fifo */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_full);
			} while( ulValue!=0 );

			/* send byte */
			ucSend = *(pucData++);
			ptSqiArea->ulSqi_dr = ucSend;
			DEBUGMSG(ZONE_VERBOSE, ". send $%02x\n", ucSend);
		} while( (uiParameter--)>0 );
	}
	else
	{
		/* DSI/QSI mode : the FIFO size is 32 bit */
		++uiParameter;
		do
		{
			/* collect a DWORD */
			ulSend = 0;
			uiShiftCnt = 0;
			do
			{
				ulSend |= ((unsigned long)(*(pucData++))) << (uiShiftCnt<<3U);
				++uiShiftCnt;
				--uiParameter;
			} while( uiParameter!=0 && uiShiftCnt<4 );

			/* wait for space in the FIFO */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_full);
			} while( ulValue!=0 );
			/* send DWORD */
			ptSqiArea->ulSqi_dr = ulSend;
			DEBUGMSG(ZONE_VERBOSE, ". send $%08x\n", ulSend);
		} while( uiParameter!=0 );
	}

	/* wait until the transfer is done */
	do
	{
		ulValue  = ptSqiArea->ulSqi_sr;
		ulValue &= HOSTMSK(sqi_sr_busy);
	} while( ulValue!=0 );
}


static int execute_sequence(QSI_CFG_T *ptCfg, const unsigned char *pucSeq)
{
	int iResult;
	size_t sizSeq;
	unsigned char ucCmd;
	QSI_CMD_T tQsiCmd;
	unsigned int uiParameter;
	const unsigned char *pucCnt;
	const unsigned char *pucEnd;


	/* expect success */
	iResult = 0;

	qsi_seq_reset_input_buffer(ptCfg);

	/* get the sequence size */
	sizSeq = *(pucSeq++);

	pucCnt = pucSeq;
	pucEnd = pucCnt + sizSeq;
	while( iResult==0 && pucCnt<pucEnd )
	{
		ucCmd = *(pucCnt++);
		if( ucCmd<0xe0U )
		{
			tQsiCmd = ucCmd & 0xf8U;
			uiParameter = ucCmd & 0x07U;
		}
		else
		{
			tQsiCmd = ucCmd & 0xf0U;
			uiParameter = ucCmd & 0x0fU;
		}
		switch( tQsiCmd )
		{
		case QSI_MODE:
			qsi_seq_set_mode(ptCfg, uiParameter);
			break;


		case QSI_ADR:
			/* send address bytes specified in bits 0-3 starting msb */
			qsi_seq_send_address(ptCfg, uiParameter);
			break;


		case QSI_CMP:
		case QSI_CMP_FATAL:
			/* a value of 0 means 1 byte */
			++uiParameter;
			/* compare the bytes in the buffer */
			if( pucCnt+uiParameter>pucEnd )
			{
				/* the sequence does not fit into the remaining buffer */
				/* this is an error in the seqnence */
				DEBUGMSG(ZONE_ERROR, "! cmp argument too large!\n");
				iResult = -1;
			}
			else
			{
				/* compare the sequence */
				iLastCompareResult = qsi_seq_compare(ptCfg, uiParameter, pucCnt);
				if( tQsiCmd==QSI_CMP_FATAL && iLastCompareResult!=0 )
				{
					iResult = -1;
				}
				pucCnt += uiParameter;
			}
			break;


		case QSI_MASK:
			/* a value of 0 means 1 byte */
			++uiParameter;
			/* mask the bytes in the buffer */
			if( pucCnt+uiParameter>pucEnd )
			{
				/* the skip size does not fit into the remaining buffer */
				/* this is an error in the seqence */
				DEBUGMSG(ZONE_ERROR, "! mask argument too large!\n");
				iResult = -1;
			}
			else
			{
				qsi_seq_mask(ptCfg, uiParameter, pucCnt);
				pucCnt += uiParameter;
			}
			break;


		case QSI_SEND_NNN:
		case QSI_SEND_SNN:
		case QSI_SEND_SDN:
		case QSI_SEND_SDD:
			/* transfer n dummy bytes of 0x00 */
			if( tQsiCmd!=QSI_SEND_NNN )
			{
				if( ptCfg->tCfg.pfnSelect(&(ptCfg->tCfg), 1)==0 )
				{
					DEBUGMSG(ZONE_VERBOSE, ". select the slave.\n");
					qsi_seq_reset_input_buffer(ptCfg);
				}
			}
			qsi_send(ptCfg, uiParameter, pucCnt);
			pucCnt += uiParameter + 1;
			if( tQsiCmd>=QSI_SEND_SDN )
			{
				DEBUGMSG(ZONE_VERBOSE, ". deselect the slave\n");
				ptCfg->tCfg.pfnSelect(&(ptCfg->tCfg), 0);
				if( tQsiCmd>=QSI_SEND_SDD )
				{
					ptCfg->tCfg.pfnSendIdle(&(ptCfg->tCfg), 0);
				}
			}
			break;


		case QSI_RECEIVE_NNN:
		case QSI_RECEIVE_SNN:
		case QSI_RECEIVE_SDN:
		case QSI_RECEIVE_SDD:
			/* receive bytes */
			if( tQsiCmd!=QSI_RECEIVE_NNN )
			{
				if( ptCfg->tCfg.pfnSelect(&(ptCfg->tCfg), 1)==0 )
				{
					DEBUGMSG(ZONE_VERBOSE, ". select the slave.\n");
					qsi_seq_reset_input_buffer(ptCfg);
				}
			}
			qsi_receive(ptCfg, uiParameter);
			if( tQsiCmd>=QSI_RECEIVE_SDN )
			{
				DEBUGMSG(ZONE_VERBOSE, ". deselect the slave\n");
				ptCfg->tCfg.pfnSelect(&(ptCfg->tCfg), 0);
				if( tQsiCmd>=QSI_RECEIVE_SDD )
				{
					ptCfg->tCfg.pfnSendIdle(&(ptCfg->tCfg), 0);
				}
			}
			break;


		case QSI_DUMMY_NNN:
		case QSI_DUMMY_SNN:
		case QSI_DUMMY_SDN:
		case QSI_DUMMY_SDD:
			/* transfer n dummy bytes of 0x00 */
			if( tQsiCmd!=QSI_DUMMY_NNN )
			{
				if( ptCfg->tCfg.pfnSelect(&(ptCfg->tCfg), 1)==0 )
				{
					DEBUGMSG(ZONE_VERBOSE, ". select the slave.\n");
					qsi_seq_reset_input_buffer(ptCfg);
				}
			}
			ptCfg->tCfg.pfnSendIdle(&(ptCfg->tCfg), uiParameter);
			if( tQsiCmd>=QSI_DUMMY_SDN )
			{
				DEBUGMSG(ZONE_VERBOSE, ". deselect the slave\n");
				ptCfg->tCfg.pfnSelect(&(ptCfg->tCfg), 0);
				if( tQsiCmd>=QSI_DUMMY_SDD )
				{
					ptCfg->tCfg.pfnSendIdle(&(ptCfg->tCfg), 0);
				}
			}
			break;


		case QSI_SKIP_EQ:
		case QSI_SKIP_NE:
			/* a value of 0 means 1 byte */
			++uiParameter;
			/* skip n bytes if last cmp was equal */
			if( pucCnt+uiParameter>pucEnd )
			{
				/* the skip size does not fit into the remaining buffer */
				/* this is an error in the seqence */
				DEBUGMSG(ZONE_ERROR, "! skip argument too large!\n");
				iResult = -1;
			}
			else
			{
				if( (tQsiCmd==QSI_SKIP_EQ && iLastCompareResult==0) || (tQsiCmd==QSI_SKIP_NE && iLastCompareResult!=0) )
				{
					DEBUGMSG(ZONE_VERBOSE, ". Skipping %d bytes\n", uiParameter);
					pucCnt += uiParameter;
				}
				else
				{
					DEBUGMSG(ZONE_VERBOSE, ". Not skipping.\n");
				}
			}
			break;


		default:
			DEBUGMSG(ZONE_ERROR, "! unknown command: $%02x\n", tQsiCmd);
			iResult = -1;
			break;
		}
	}

	return iResult;
}


unsigned long aulBuffer[16];

#endif


static NETX_CONSOLEAPP_RESULT_T execute_sequence(CMD_PARAMETER_SPIMACROPLAYER_T *ptParameter, SPI_CFG_T *ptSpiDev)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	int iResult;
	unsigned char aucSend[6];
	unsigned char aucRecv[6];
	


	aucSend[0] = 0x9f;
	aucSend[1] = 0x00;
	aucSend[2] = 0x00;
	aucSend[3] = 0x00;
	aucSend[4] = 0x00;
	aucSend[5] = 0x00;

	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	/* Deselect the chip. */
	ptSpiDev->pfnSelect(ptSpiDev, 0);

	/* Send 8 idle bytes to clear the bus. */
	iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 8);
	if( iResult!=0 )
	{
		uprintf("ERROR: Failed to send idle bytes: %d.\n", iResult);
	}
	else
	{
		/* Select the slave. */
		ptSpiDev->pfnSelect(ptSpiDev, 1);

		/* Send id magic and receive response. */
		iResult = ptSpiDev->pfnExchangeData(ptSpiDev, aucSend, aucRecv, sizeof(aucRecv));
		if( iResult!=0 )
		{
			uprintf("ERROR: Failed to send bytes: %d.\n", iResult);
		}
		else
		{
			hexdump(aucRecv, sizeof(aucRecv));
			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}

		/* Deselect slave */
		ptSpiDev->pfnSelect(ptSpiDev, 0);
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

#if CFG_DEBUGMSG==1
	ulDebugMessages = 0xffffffff;
#endif

	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	ptSpiCfg = &(ptParameter->tSpi);

	/* Get the driver. */
	iResult = board_get_spi_driver(ptSpiCfg, &tSpiDev);
	if( iResult!=0 )
	{
		uprintf("Failed to init the board driver!\n");
	}
	else
	{
		tResult = execute_sequence(ptParameter, &tSpiDev);
	}

	return tResult;
}



