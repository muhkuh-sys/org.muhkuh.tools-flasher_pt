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

#include "drv_spi.h"

#include "mmio.h"
#include "netx_io_areas.h"



static const MMIO_CFG_T aatMmioValues[3][4] =
{
	/*
	 * Chip select 0
	 */
	{
		MMIO_CFG_spi1_cs0n,		/* chip select */
		MMIO_CFG_spi1_clk,		/* clock */
		MMIO_CFG_spi1_miso,		/* miso */
		MMIO_CFG_spi1_mosi		/* mosi */
	},

	/*
	 * Chip select 1
	 */
	{
		MMIO_CFG_spi1_cs1n,		/* chip select */
		MMIO_CFG_spi1_clk,		/* clock */
		MMIO_CFG_spi1_miso,		/* miso */
		MMIO_CFG_spi1_mosi		/* mosi */
	},

	/*
	 * Chip select 2
	 */
	{
		MMIO_CFG_spi1_cs2n,		/* chip select */
		MMIO_CFG_spi1_clk,		/* clock */
		MMIO_CFG_spi1_miso,		/* miso */
		MMIO_CFG_spi1_mosi		/* mosi */
	}
};


static unsigned char spi_exchange_byte(const SPI_CFG_T *ptCfg __attribute__ ((unused)), unsigned char ucByte)
{
	unsigned long ulValue;


	/* send byte */
	ptSpiArea->ulSpi_dr = ucByte;

	/* wait for one byte in the fifo */
	do
	{
		ulValue  = ptSpiArea->ulSpi_sr;
		ulValue &= HOSTMSK(spi_sr_RNE);
	} while( ulValue==0 );

	/* grab byte */
	ucByte = (unsigned char)(ptSpiArea->ulSpi_dr);
	return ucByte;
}

/*-----------------------------------*/


static unsigned long spi_get_device_speed_representation(unsigned int uiSpeed)
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
		ulInputFilter = HOSTMSK(spi_cr0_filter_in);
	}

	/* shift to register position */
	ulDevSpeed <<= HOSTSRT(spi_cr0_sck_muladd);

	/* add filter bit */
	ulDevSpeed |= ulInputFilter;

	return ulDevSpeed;
}


static int spi_slave_select(const SPI_CFG_T *ptCfg, int fIsSelected)
{
	int iResult;
	unsigned long uiChipSelect;
	unsigned long ulValue;


	iResult = 0;

	/* get the chipselect value */
	uiChipSelect  = 0;
	if( fIsSelected!=0 )
	{
		uiChipSelect  = ptCfg->uiChipSelect << HOSTSRT(spi_cr1_fss);
		uiChipSelect &= HOSTMSK(spi_cr1_fss);
	}

	/* get control register contents */
	ulValue  = ptSpiArea->aulSpi_cr[1];

	/* compare the active selection with the requested one */
	if( (ulValue&HOSTMSK(spi_cr1_fss))==uiChipSelect )
	{
		/* the slave is already selected */
		/* NOTE: of course it does not hurt to select it again, but
		   the chip select is also used to reset the buffer counter */
		iResult = -1;
	}
	else
	{
		/* mask out the slave select bits */
		ulValue &= ~HOSTMSK(spi_cr1_fss);

		/* mask in the new slave id */
		ulValue |= uiChipSelect;

		/* write back new value */
		ptSpiArea->aulSpi_cr[1] = ulValue;
	}

	return iResult;
}


static int spi_send_idle(const SPI_CFG_T *ptCfg, size_t sizBytes)
{
	unsigned char ucIdleChar;


	/* get the idle byte */
	ucIdleChar = ptCfg->ucIdleChar;
	while( sizBytes>0 )
	{
		spi_exchange_byte(ptCfg, ucIdleChar);
		--sizBytes;
	}

	return 0;
}


static int spi_send_data(const SPI_CFG_T *ptCfg, const unsigned char *pucData, size_t sizData)
{
	const unsigned char *pucDataEnd;


	/* send data */
	pucDataEnd = pucData + sizData;
	while( pucData<pucDataEnd )
	{
		spi_exchange_byte(ptCfg, *(pucData++));
	}

	return 0;
}


static int spi_receive_data(const SPI_CFG_T *ptCfg, unsigned char *pucData, size_t sizData)
{
	unsigned char ucIdleChar;
	unsigned char *pucDataEnd;


	/* get the idle byte */
	ucIdleChar = ptCfg->ucIdleChar;

	/* send data */
	pucDataEnd = pucData + sizData;
	while( pucData<pucDataEnd )
	{
		*pucData = spi_exchange_byte(ptCfg, ucIdleChar);
		++pucData;
	}

	return 0;
}


static int spi_exchange_data(const SPI_CFG_T *ptCfg, const unsigned char *pucOutData, unsigned char *pucInData, size_t sizData)
{
	unsigned char ucIdleChar;
	unsigned char *pucInDataEnd;


	/* get the idle byte */
	ucIdleChar = ptCfg->ucIdleChar;

	/* send data */
	pucInDataEnd = pucInData + sizData;
	while( pucInData<pucInDataEnd )
	{
		*pucInData = spi_exchange_byte(ptCfg, *(pucOutData++));
		++pucInData;
	}

	return 0;
}


static void spi_set_new_speed(unsigned long ulDeviceSpecificSpeed)
{
	unsigned long ulValue;


	ulDeviceSpecificSpeed &= HOSTMSK(spi_cr0_sck_muladd) | HOSTMSK(spi_cr0_filter_in);

	ulValue  = ptSpiArea->aulSpi_cr[0];
	ulValue &= ~(HOSTMSK(spi_cr0_sck_muladd)|HOSTMSK(spi_cr0_filter_in));
	ulValue |= ulDeviceSpecificSpeed;
	ptSpiArea->aulSpi_cr[0] = ulValue;
}


static void spi_deactivate(const SPI_CFG_T *ptCfg)
{
	unsigned long ulValue;


	/* deactivate irqs */
	ptSpiArea->ulSpi_imsc = 0;
	/* clear all pending irqs */
	ulValue  = HOSTMSK(spi_icr_RORIC);
	ulValue |= HOSTMSK(spi_icr_RTIC);
	ulValue |= HOSTMSK(spi_icr_RXIC);
	ulValue |= HOSTMSK(spi_icr_TXIC);
	ulValue |= HOSTMSK(spi_icr_rxneic);
	ulValue |= HOSTMSK(spi_icr_rxfic);
	ulValue |= HOSTMSK(spi_icr_txeic);
	ptSpiArea->ulSpi_icr = ulValue;
	/* deactivate irq routing to the cpus */
	ptSpiArea->ulSpi_irq_cpu_sel = 0;

	/* deactivate dmas */
	ptSpiArea->ulSpi_dmacr = 0;

	/* deactivate the unit */
	ptSpiArea->aulSpi_cr[0] = 0;
	ptSpiArea->aulSpi_cr[1] = 0;

	/* activate the spi pins */
	mmio_deactivate(ptCfg->aucMmio, sizeof(ptCfg->aucMmio), aatMmioValues[ptCfg->uiChipSelect]);
}


int boot_drv_spi_init(SPI_CFG_T *ptCfg, const SPI_CONFIGURATION_T *ptSpiCfg, unsigned int uiChipSelect)
{
	unsigned long ulValue;
	int iResult;
	unsigned int uiIdleCfg;
	unsigned char ucIdleChar;


	iResult = 0;

	ptCfg->ulSpeed = ptSpiCfg->ulInitialSpeedKhz;	/* initial device speed in kHz */
	ptCfg->uiIdleCfg = ptSpiCfg->uiIdleCfg;		/* the idle configuration */
	ptCfg->tMode = ptSpiCfg->uiMode;		/* bus mode */
	ptCfg->uiChipSelect = 1U<<uiChipSelect;		/* chip select */

	/* set the function pointers */
	ptCfg->pfnSelect = spi_slave_select;
	ptCfg->pfnSendIdle = spi_send_idle;
	ptCfg->pfnSendData = spi_send_data;
	ptCfg->pfnReceiveData = spi_receive_data;
	ptCfg->pfnExchangeData = spi_exchange_data;
	ptCfg->pfnSetNewSpeed = spi_set_new_speed;
	ptCfg->pfnExchangeByte = spi_exchange_byte;
	ptCfg->pfnGetDeviceSpeedRepresentation = spi_get_device_speed_representation;
	ptCfg->pfnDeactivate = spi_deactivate;

	/* copy the mmio pins */
	memcpy(ptCfg->aucMmio, ptSpiCfg->aucMmio, sizeof(ptSpiCfg->aucMmio));

	/* do not use irqs in bootloader */
	ptSpiArea->ulSpi_imsc = 0;
	/* clear all pending irqs */
	ulValue  = HOSTMSK(spi_icr_RORIC);
	ulValue |= HOSTMSK(spi_icr_RTIC);
	ulValue |= HOSTMSK(spi_icr_RXIC);
	ulValue |= HOSTMSK(spi_icr_TXIC);
	ulValue |= HOSTMSK(spi_icr_rxneic);
	ulValue |= HOSTMSK(spi_icr_rxfic);
	ulValue |= HOSTMSK(spi_icr_txeic);
	ptSpiArea->ulSpi_icr = ulValue;
	/* do not route the irqs to a cpu */
	ptSpiArea->ulSpi_irq_cpu_sel = 0;

	/* do not use dmas */
	ptSpiArea->ulSpi_dmacr = 0;

	/* set 8 bits */
	ulValue  = 7 << HOSTSRT(spi_cr0_datasize);
	/* set speed and filter */
	ulValue |= spi_get_device_speed_representation(ptCfg->ulSpeed);
	/* set the clock polarity  */
	if( (ptCfg->tMode==SPI_MODE2) || (ptCfg->tMode==SPI_MODE3) )
	{
		ulValue |= HOSTMSK(spi_cr0_SPO);
	}
	/* set the clock phase     */
	if( (ptCfg->tMode==SPI_MODE1) || (ptCfg->tMode==SPI_MODE3) )
	{
		ulValue |= HOSTMSK(spi_cr0_SPH);
	}
	ptSpiArea->aulSpi_cr[0] = ulValue;


	/* manual chipselect */
	ulValue  = HOSTMSK(spi_cr1_fss_static);
	/* enable the interface */
	ulValue |= HOSTMSK(spi_cr1_SSE);
	/* clear both fifos */
	ulValue |= HOSTMSK(spi_cr1_rx_fifo_clr)|HOSTMSK(spi_cr1_tx_fifo_clr);
	ptSpiArea->aulSpi_cr[1] = ulValue;

	/* transfer control base is unused in this driver */
	ptCfg->ulTrcBase = 0;

	/* set the idle char from the tx config */
	uiIdleCfg = ptCfg->uiIdleCfg;
	if( (uiIdleCfg&MSK_SQI_CFG_IDLE_IO1_OUT)!=0 )
	{
		ucIdleChar = 0xffU;
	}
	else
	{
		ucIdleChar = 0x00U;
	}
	ptCfg->ucIdleChar = ucIdleChar;

	/* activate the spi pins */
	mmio_activate(ptCfg->aucMmio, sizeof(ptCfg->aucMmio), aatMmioValues[uiChipSelect]);

	return iResult;
}

