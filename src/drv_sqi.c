/***************************************************************************
 *   Copyright (C) 2010 by Hilscher GmbH                                   *
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

#include "drv_sqi.h"

#include "mmio.h"
#include "netx_io_areas.h"

static const MMIO_CFG_T aatMmioValues[3][4] =
{
#if ASIC_TYP==10
	/*
	 * Chip select 0
	 */
	{
		0xffU,                          /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	},

	/*
	 * Chip select 1
	 */
	{
		MMIO_CFG_spi0_cs1n,             /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	},

	/*
	 * Chip select 2
	 */
	{
		MMIO_CFG_spi0_cs2n,             /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	}
#elif ASIC_TYP==56
	/*
	 * Chip select 0
	 */
	{
		0xffU,                          /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	},

	/*
	 * Chip select 1
	 */
	{
		0xffU,                          /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	},

	/*
	 * Chip select 2
	 */
	{
		MMIO_CFG_spi0_cs2n,             /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	}
#else
#       error "The SQI driver does not support this ASIC type!"
#endif
};


/*-------------------------------------------------------------------------*/

/* BootSPI_ExchangeByte
 *
 * Description:
 *   Send and receive one byte on the SPI bus.
 *
 * Parameters:
 *
 *   unsigned char out_byte = byte to send
 *
 * Return:
 *   unsigned char          = received byte
 *
 * Notes:
 *   This function has no timeout. If the transfer hangs for some reason, it will never return.
 */
static unsigned char qsi_spi_exchange_byte(const SPI_CFG_T *ptCfg, unsigned char uiByte)
{
	HOSTDEF(ptSqiArea);
	unsigned long ulValue;
	unsigned char ucByte;


	/* set mode to "full duplex" */
	ulValue  = ptCfg->ulTrcBase;
	ulValue |= 3 << HOSTSRT(sqi_tcr_duplex);
	/* start the transfer */
	ulValue |= HOSTMSK(sqi_tcr_start_transfer);
	ptSqiArea->ulSqi_tcr = ulValue;

	/* send byte */
	ptSqiArea->ulSqi_dr = uiByte;

	/* Wait for one byte in the FIFO. */
	do
	{
		ulValue  = ptSqiArea->ulSqi_sr;
		ulValue &= HOSTMSK(sqi_sr_busy);
	} while( ulValue!=0 );

	/* grab byte */
	ucByte = (unsigned char)(ptSqiArea->ulSqi_dr);
	return ucByte;
}


/*-------------------------------------------------------------------------*/


static unsigned long qsi_get_device_speed_representation(unsigned int uiSpeed)
{
	unsigned long ulDevSpeed;
	unsigned long ulInputFilter;


	/* ulSpeed is in kHz */

	/* limit speed to upper border */
	if( uiSpeed>50000 )
	{
		uiSpeed = 50000;
	}

	/* convert speed to "multiply add value" */
	ulDevSpeed  = uiSpeed * 4096;

	/* NOTE: do not round up here */
	ulDevSpeed /= 100000;

	/* use input filtering? */
	ulInputFilter = 0;
	if( ulDevSpeed<=0x0200 )
	{
		ulInputFilter = HOSTMSK(sqi_cr0_filter_in);
	}

	/* shift to register position */
	ulDevSpeed <<= HOSTSRT(sqi_cr0_sck_muladd);

	/* add filter bit */
	ulDevSpeed |= ulInputFilter;

	return ulDevSpeed;
}


static int qsi_slave_select(const SPI_CFG_T *ptCfg, int fIsSelected)
{
	HOSTDEF(ptSqiArea);
	int iResult;
	unsigned long uiChipSelect;
	unsigned long ulValue;


	iResult = 0;

	/* Get the chip select value. */
	uiChipSelect  = 0;
	if( fIsSelected!=0 )
	{
		uiChipSelect  = ptCfg->uiChipSelect << HOSTSRT(sqi_cr1_fss);
		uiChipSelect &= HOSTMSK(sqi_cr1_fss);
	}

	/* get control register contents */
	ulValue  = ptSqiArea->aulSqi_cr[1];

	/* compare the active selection with the requested one */
	if( (ulValue&HOSTMSK(sqi_cr1_fss))==uiChipSelect )
	{
		/* the slave is already selected */
		/* NOTE: of course it does not hurt to select it again, but
		   the chip select is also used to reset the buffer counter */
		iResult = -1;
	}
	else
	{
		/* mask out the slave select bits */
		ulValue &= ~HOSTMSK(sqi_cr1_fss);

		/* mask in the new slave id */
		ulValue |= uiChipSelect;

		/* write back new value */
		ptSqiArea->aulSqi_cr[1] = ulValue;
	}

	return iResult;
}


#if 0
static int qsi_send_idle(const SPI_CFG_T *ptCfg, size_t sizIdleChars)
{
	unsigned long ulValue;


	if( sizIdleChars>0 )
	{
		/* convert the number of idle bytes to cycles */
		sizIdleChars <<= 3U;
		--sizIdleChars;
		uprintf("send %d cycles\n", sizIdleChars);

		/* set mode to "send dummy" */
		ulValue  = ptCfg->ulTrcBase;
		ulValue |= 0 << HOSTSRT(sqi_tcr_duplex);
		/* set the transfer size */
		ulValue |= sizIdleChars << HOSTSRT(sqi_tcr_transfer_size);
		/* start the transfer */
		ulValue |= HOSTMSK(sqi_tcr_start_transfer);
		ptSqiArea->ulSqi_tcr = ulValue;

		/* wait until the transfer is done */
		do
		{
			ulValue  = ptSqiArea->ulSqi_sr;
			ulValue &= HOSTMSK(sqi_sr_busy);
		} while( ulValue!=0 );
		uprintf("done\n");
	}

	return 0;
}
#else
static int qsi_send_idle(const SPI_CFG_T *ptCfg, size_t sizIdleChars)
{
	while( sizIdleChars>0 )
	{
		qsi_spi_exchange_byte(ptCfg, 0x00);
		--sizIdleChars;
	}
	return 0;
}
#endif


#if 0
static int qsi_receive_data(const SPI_CFG_T *ptCfg, unsigned char *pucData, size_t sizData)
{
	unsigned long ulValue;
	unsigned char *pucDataEnd;


	if( sizData>0 )
	{
		/* set mode to "half duplex receive" */
		ulValue  = ptCfg->ulTrcBase;
		ulValue |= 1 << HOSTSRT(sqi_tcr_duplex);
		/* set the transfer size */
		ulValue |= (sizData-1) << HOSTSRT(sqi_tcr_transfer_size);
		/* start the transfer */
		ulValue |= HOSTMSK(sqi_tcr_start_transfer);
		ptSqiArea->ulSqi_tcr = ulValue;

		/* get end address */
		pucDataEnd = pucData + sizData;

		while( pucData<pucDataEnd )
		{
			/* wait for one byte in the fifo */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_not_empty);
			} while( ulValue==0 );

			/* grab byte */
			*pucData = (unsigned char)(ptSqiArea->ulSqi_dr);
			++pucData;
		}

		/* wait until the transfer is done */
		do
		{
			ulValue  = ptSqiArea->ulSqi_sr;
			ulValue &= HOSTMSK(sqi_sr_busy);
		} while( ulValue!=0 );
	}

	return 0;
}
#else
static int qsi_receive_data(const SPI_CFG_T *ptCfg, unsigned char *pucData, size_t sizData)
{
	while( sizData>0 )
	{
		*(pucData++) = qsi_spi_exchange_byte(ptCfg, 0x00);
		--sizData;
	}
	return 0;
}
#endif


#if 0
static int qsi_send_data(const SPI_CFG_T *ptCfg, const unsigned char *pucData, size_t sizData)
{
	unsigned long ulValue;
	const unsigned char *pucDataEnd;


	if( sizData>0 )
	{
		/* set mode to "half duplex transmit" */
		ulValue  = ptCfg->ulTrcBase;
		ulValue |= 2 << HOSTSRT(sqi_tcr_duplex);
		/* set the transfer size */
		ulValue |= (sizData-1) << HOSTSRT(sqi_tcr_transfer_size);
		/* start the transfer */
		ulValue |= HOSTMSK(sqi_tcr_start_transfer);
		ptSqiArea->ulSqi_tcr = ulValue;

		pucDataEnd = pucData + sizData;

		while( pucData<pucDataEnd )
		{
			/* wait for tx fifo not full */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_tx_fifo_not_full);
			} while( ulValue==0 );

			/* push byte into the fifo */
			ptSqiArea->ulSqi_dr = *(pucData++);
		}

		/* wait until the transfer is done */
		do
		{
			ulValue  = ptSqiArea->ulSqi_sr;
			ulValue &= HOSTMSK(sqi_sr_busy);
		} while( ulValue!=0 );
	}

	return 0;
}
#else
static int qsi_send_data(const SPI_CFG_T *ptCfg, const unsigned char *pucData, size_t sizData)
{
	while( sizData>0 )
	{
		qsi_spi_exchange_byte(ptCfg, *(pucData++));
		--sizData;
	}
	return 0;
}
#endif


#if 0
static int qsi_exchange_data(const SPI_CFG_T *ptCfg, const unsigned char *pucDataOut, unsigned char *pucDataIn, size_t sizData)
{
	unsigned long ulValue;
	const unsigned char *pucOutCnt;
	const unsigned char *pucOutEnd;
	unsigned char *pucInCnt;
	unsigned char *pucInEnd;


	if( sizData>0 )
	{
		/* set mode to "full duplex" */
		ulValue  = ptCfg->ulTrcBase;
		ulValue |= 3 << HOSTSRT(sqi_tcr_duplex);
		/* set the transfer size */
		ulValue |= (sizData-1) << HOSTSRT(sqi_tcr_transfer_size);
		/* start the transfer */
		ulValue |= HOSTMSK(sqi_tcr_start_transfer);
		ptSqiArea->ulSqi_tcr = ulValue;

		pucOutCnt = pucDataOut;
		pucOutEnd = pucDataOut + sizData;
		pucInCnt = pucDataIn;
		pucInEnd = pucDataIn + sizData;

		do
		{
			/* Some data left to send? */
			if( pucOutCnt<pucOutEnd )
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_tx_fifo_not_full);
				if( ulValue!=0 )
				{
					/* push byte into the fifo */
					ptSqiArea->ulSqi_dr = *(pucOutCnt++);
				}
			}

			/* Still want data? */
			if( pucInCnt<pucInEnd )
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_not_empty);
				if( ulValue!=0 )
				{
					/* grab byte */
					*(pucInCnt++) = (unsigned char)(ptSqiArea->ulSqi_dr);
				}
			}
		} while( pucOutCnt<pucOutEnd && pucInCnt<pucInEnd );

		/* wait until the transfer is done */
		do
		{
			ulValue  = ptSqiArea->ulSqi_sr;
			ulValue &= HOSTMSK(sqi_sr_busy);
		} while( ulValue!=0 );
	}

	return 0;
}
#else
static int qsi_exchange_data(const SPI_CFG_T *ptCfg, const unsigned char *pucDataOut, unsigned char *pucDataIn, size_t sizData)
{
	while( sizData>0 )
	{
		*(pucDataIn++) = qsi_spi_exchange_byte(ptCfg, *(pucDataOut++));
		--sizData;
	}
	return 0;
}
#endif

static void qsi_set_new_speed(const SPI_CFG_T *ptCfg __attribute__((unused)), unsigned long ulDeviceSpecificSpeed)
{
	HOSTDEF(ptSqiArea);
	unsigned long ulValue;


	ulDeviceSpecificSpeed &= HOSTMSK(sqi_cr0_sck_muladd) | HOSTMSK(sqi_cr0_filter_in);

	ulValue  = ptSqiArea->aulSqi_cr[0];
	ulValue &= ~(HOSTMSK(sqi_cr0_sck_muladd)|HOSTMSK(sqi_cr0_filter_in));
	ulValue |= ulDeviceSpecificSpeed;
	ptSqiArea->aulSqi_cr[0] = ulValue;
}


static void qsi_deactivate(const SPI_CFG_T *ptCfg)
{
	HOSTDEF(ptSqiArea);
	unsigned long ulValue;


	/* deactivate IRQs */
	ptSqiArea->ulSqi_irq_mask = 0;
	/* clear all pending IRQs */
	ulValue  = HOSTMSK(sqi_irq_clear_RORIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RTIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_TXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_rxneic);
	ulValue |= HOSTMSK(sqi_irq_clear_rxfic);
	ulValue |= HOSTMSK(sqi_irq_clear_txeic);
	ulValue |= HOSTMSK(sqi_irq_clear_trans_end);
	ptSqiArea->ulSqi_irq_clear = ulValue;
	/* deactivate IRQ routing to the CPUs */
	ptSqiArea->ulSqi_irq_cpu_sel = 0;

	/* deactivate DMAs */
	ptSqiArea->ulSqi_dmacr = 0;

	/* deactivate XIP */
	ptSqiArea->ulSqi_sqirom_cfg = 0;

	ptSqiArea->ulSqi_tcr = 0;
	ptSqiArea->ulSqi_pio_oe = 0;
	ptSqiArea->ulSqi_pio_out = 0;

	/* deactivate the unit */
	ptSqiArea->aulSqi_cr[0] = 0;
	ptSqiArea->aulSqi_cr[1] = 0;

	/* activate the SPI pins */
	mmio_deactivate(ptCfg->aucMmio, sizeof(ptCfg->aucMmio), aatMmioValues[ptCfg->uiChipSelect]);
}


int boot_drv_sqi_init(SPI_CFG_T *ptCfg, const SPI_CONFIGURATION_T *ptSpiCfg)
{
	HOSTDEF(ptSqiArea);
	unsigned long ulValue;
	int iResult;
	unsigned int uiIdleCfg;
	unsigned char ucIdleChar;
	unsigned int uiChipSelect;


	iResult = 0;

	/* Get the chip select value. */
	uiChipSelect = ptSpiCfg->uiChipSelect;

	ptCfg->ulSpeed = ptSpiCfg->ulInitialSpeedKhz;   /* initial device speed in kHz */
	ptCfg->uiIdleCfg = ptSpiCfg->uiIdleCfg;         /* the idle configuration */
	ptCfg->tMode = ptSpiCfg->uiMode;                /* bus mode */
	ptCfg->uiChipSelect = 1U<<uiChipSelect;         /* chip select */

	/* set the function pointers */
	ptCfg->pfnSelect = qsi_slave_select;
	ptCfg->pfnSendIdle = qsi_send_idle;
	ptCfg->pfnSendData = qsi_send_data;
	ptCfg->pfnReceiveData = qsi_receive_data;
	ptCfg->pfnExchangeData = qsi_exchange_data;
	ptCfg->pfnSetNewSpeed = qsi_set_new_speed;
	ptCfg->pfnExchangeByte = qsi_spi_exchange_byte;
	ptCfg->pfnGetDeviceSpeedRepresentation = qsi_get_device_speed_representation;
	ptCfg->pfnDeactivate = qsi_deactivate;

	/* copy the MMIO pins */
	memcpy(ptCfg->aucMmio, ptSpiCfg->aucMmio, sizeof(ptSpiCfg->aucMmio));

	/* do not use IRQs in bootloader */
	ptSqiArea->ulSqi_irq_mask = 0;
	/* clear all pending IRQs */
	ulValue  = HOSTMSK(sqi_irq_clear_RORIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RTIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_TXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_rxneic);
	ulValue |= HOSTMSK(sqi_irq_clear_rxfic);
	ulValue |= HOSTMSK(sqi_irq_clear_txeic);
	ulValue |= HOSTMSK(sqi_irq_clear_trans_end);
	ptSqiArea->ulSqi_irq_clear = ulValue;
	/* do not route the IRQs to a CPU */
	ptSqiArea->ulSqi_irq_cpu_sel = 0;

	/* do not use DMAs */
	ptSqiArea->ulSqi_dmacr = 0;

	/* do not use XIP */
	ptSqiArea->ulSqi_sqirom_cfg = 0;

	/* set 8 bits */
	ulValue  = 7 << HOSTSRT(sqi_cr0_datasize);
	/* set speed and filter */
	ulValue |= qsi_get_device_speed_representation(ptCfg->ulSpeed);
	/* start in SPI mode: use only IO0 and IO1 for transfer */
	ulValue |= 0 << HOSTSRT(sqi_cr0_sio_cfg);
	/* set the clock polarity  */
	if( (ptCfg->tMode==SPI_MODE2) || (ptCfg->tMode==SPI_MODE3) )
	{
		ulValue |= HOSTMSK(sqi_cr0_sck_pol);
	}
	/* set the clock phase     */
	if( (ptCfg->tMode==SPI_MODE1) || (ptCfg->tMode==SPI_MODE3) )
	{
		ulValue |= HOSTMSK(sqi_cr0_sck_phase);
	}
	ptSqiArea->aulSqi_cr[0] = ulValue;


	/* manual chip select */
	ulValue  = HOSTMSK(sqi_cr1_fss_static);
	/* manual transfer start */
	ulValue |= HOSTMSK(sqi_cr1_spi_trans_ctrl);
	/* enable the interface */
	ulValue |= HOSTMSK(sqi_cr1_sqi_en);
	/* clear both FIFOs */
	ulValue |= HOSTMSK(sqi_cr1_rx_fifo_clr)|HOSTMSK(sqi_cr1_tx_fifo_clr);
	ptSqiArea->aulSqi_cr[1] = ulValue;


	uiIdleCfg = ptCfg->uiIdleCfg;

	/* set transfer control base */
	ulValue  = HOSTMSK(sqi_tcr_ms_bit_first);
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO1_OE)!=0 )
	{
		ulValue |= HOSTMSK(sqi_tcr_tx_oe);
	}
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO1_OUT)!=0 )
	{
		ulValue |= HOSTMSK(sqi_tcr_tx_out);
	}
	ptCfg->ulTrcBase = ulValue;
	ptSqiArea->ulSqi_tcr = ulValue;

	ulValue = 0;
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO2_OUT)!=0 )
	{
		ulValue |= HOSTMSK(sqi_pio_out_sio2);
	}
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO3_OUT)!=0 )
	{
		ulValue |= HOSTMSK(sqi_pio_out_sio3);
	}
	ptSqiArea->ulSqi_pio_out = ulValue;

	ulValue = 0;
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO2_OE)!=0 )
	{
		ulValue |= HOSTMSK(sqi_pio_oe_sio2);
	}
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO3_OE)!=0 )
	{
		ulValue |= HOSTMSK(sqi_pio_oe_sio3);
	}
	ptSqiArea->ulSqi_pio_oe = ulValue;

	/* set the idle char from the TX configuration */
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO1_OUT)!=0 )
	{
		ucIdleChar = 0xffU;
	}
	else
	{
		ucIdleChar = 0x00U;
	}
	ptCfg->ucIdleChar = ucIdleChar;

	/* activate the SPI pins */
	mmio_activate(ptCfg->aucMmio, sizeof(ptCfg->aucMmio), aatMmioValues[uiChipSelect]);

	return iResult;
}

