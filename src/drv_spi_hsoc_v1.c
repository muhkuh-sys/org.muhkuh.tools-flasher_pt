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

#include "drv_spi_hsoc_v1.h"

#include "netx_io_areas.h"



static unsigned char spi_exchange_byte(const SPI_CFG_T *ptCfg, unsigned char ucByte)
{
	HOSTADEF(SPI) *ptSpiUnit;
	unsigned long ulValue;


	/* Get the pointer to the registers. */
	ptSpiUnit = ptCfg->ptUnit;

	/* write byte to spi bus */
	ptSpiUnit->ulSpi_data_register = ucByte | HOSTMSK(spi_data_register_dr_valid0);

	/* Wait until all bytes are clocked out. There will be a byte in the
	 * receive buffer */
	/* TODO: limit the polling time, this will wait forever! On timeout return -1 . */
	do
	{
		ulValue  = ptSpiUnit->ulSpi_status_register;
		ulValue &= HOSTMSK(spi_status_register_SR_out_fuel_val);
	} while( ulValue!=0 );

	/* Get the received byte. */
	ucByte = (unsigned char)(ptSpiUnit->ulSpi_data_register);
	return ucByte;
}


/*-----------------------------------*/


typedef enum
{
  HAL_SPI_SPEED_0_05MHz   = 1,
  HAL_SPI_SPEED_0_1MHz    = 2,
  HAL_SPI_SPEED_0_2MHz    = 3,
  HAL_SPI_SPEED_0_5MHz    = 4,
  HAL_SPI_SPEED_1_0MHz    = 5,
  HAL_SPI_SPEED_1_25MHz   = 6,
  HAL_SPI_SPEED_2_0MHz    = 7,
  HAL_SPI_SPEED_2_5MHz    = 8,
  HAL_SPI_SPEED_3_3MHz    = 9,
  HAL_SPI_SPEED_5_0MHz    = 10,
  HAL_SPI_SPEED_10_0MHz   = 11,
  HAL_SPI_SPEED_12_5MHz   = 12,
  HAL_SPI_SPEED_16_6MHz   = 13,
  HAL_SPI_SPEED_25_0MHz   = 14,
  HAL_SPI_SPEED_50_0MHz   = 15
} HAL_SPI_SPEED_t;


typedef struct
{
	unsigned long ulSpeed;
	HAL_SPI_SPEED_t tSpiClock;
} SPI_KHZ_TO_CLOCK_T;

/* Speed steps for netX100/500. */
/* NOTE: the speeds *must* be listed in ascending order, i.e. slowest first. */
static const SPI_KHZ_TO_CLOCK_T aulSpeedSteps[] =
{
	{    50, HAL_SPI_SPEED_0_05MHz },
	{   100, HAL_SPI_SPEED_0_1MHz  },
	{   200, HAL_SPI_SPEED_0_2MHz  },
	{   500, HAL_SPI_SPEED_0_5MHz  },
	{  1000, HAL_SPI_SPEED_1_0MHz  },
	{  1250, HAL_SPI_SPEED_1_25MHz },
	{  2000, HAL_SPI_SPEED_2_0MHz  },
	{  2500, HAL_SPI_SPEED_2_5MHz  },
	{  3333, HAL_SPI_SPEED_3_3MHz  },
	{  5000, HAL_SPI_SPEED_5_0MHz  },
	{ 10000, HAL_SPI_SPEED_10_0MHz },
	{ 12500, HAL_SPI_SPEED_12_5MHz },
	{ 16666, HAL_SPI_SPEED_16_6MHz },
	{ 25000, HAL_SPI_SPEED_25_0MHz },
	{ 50000, HAL_SPI_SPEED_50_0MHz }
};

static unsigned long spi_get_device_speed_representation(const SPI_CFG_T *ptCfg, unsigned int uiSpeed)
{
	unsigned int uiCnt;
	unsigned long ulDevSpeed;
	unsigned long ulMaximumSpeedKhz;


	/* Limit the speed. */
	ulMaximumSpeedKhz = ptCfg->ulMaximumSpeedKhz;
	if( uiSpeed>ulMaximumSpeedKhz )
	{
		uiSpeed = ulMaximumSpeedKhz;
	}

	/* Start at the end of the list. There are the largest values. */
	uiCnt = sizeof(aulSpeedSteps)/sizeof(aulSpeedSteps[0]);

	/* Get the minimum matching entry. */
	do
	{
		--uiCnt;
		if( uiSpeed>=aulSpeedSteps[uiCnt].ulSpeed )
		{
			break;
		}
	} while( uiCnt!=0 );

	/* Return the supported speed. */
	ulDevSpeed   = aulSpeedSteps[uiCnt].tSpiClock;
	ulDevSpeed <<= HOSTSRT(spi_control_register_CR_speed);

	return ulDevSpeed;
}


/*-----------------------------------*/


static int spi_slave_select(const SPI_CFG_T *ptCfg, int fIsSelected)
{
	HOSTADEF(SPI) *ptSpiUnit;
	unsigned long ulValue;


	/* Get the pointer to the registers. */
	ptSpiUnit = ptCfg->ptUnit;

	/* get control register contents */
	ulValue = ptSpiUnit->ulSpi_control_register;
	
	/* mask out the slave select bits */
	ulValue &= ~HOSTMSK(spi_control_register_CR_ss);
	
	/* mask in the new slave id */
	if( fIsSelected!=0 )
	{
		ulValue |= ptCfg->uiChipSelect << HOSTSRT(spi_control_register_CR_ss);
	}
	
	/* clear in and out fifo */
	ulValue |= HOSTMSK(spi_control_register_CR_clr_infifo)|HOSTMSK(spi_control_register_CR_clr_outfifo);
	
	/* write back new value */
	ptSpiUnit->ulSpi_control_register = ulValue;

	return 0;
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
	unsigned char *pucInDataEnd;


	/* send data */
	pucInDataEnd = pucInData + sizData;
	while( pucInData<pucInDataEnd )
	{
		*pucInData = spi_exchange_byte(ptCfg, *(pucOutData++));
		++pucInData;
	}

	return 0;
}


static void spi_set_new_speed(const SPI_CFG_T *ptCfg, unsigned long ulDeviceSpecificSpeed)
{
	HOSTADEF(SPI) *ptSpiUnit;
	unsigned long ulValue;


	/* Get the pointer to the registers. */
	ptSpiUnit = ptCfg->ptUnit;

	ulDeviceSpecificSpeed &= HOSTMSK(spi_control_register_CR_speed);

	ulValue  = ptSpiUnit->ulSpi_control_register;
	ulValue &= ~HOSTMSK(spi_control_register_CR_speed);
	ulValue |= ulDeviceSpecificSpeed;
	ptSpiUnit->ulSpi_control_register = ulValue;
}


static void spi_deactivate(const SPI_CFG_T *ptCfg)
{
	HOSTADEF(SPI) *ptSpiUnit;
	unsigned long ulValue;


	/* Get the pointer to the registers. */
	ptSpiUnit = ptCfg->ptUnit;
	/* Soft reset spi and clear both fifos. */
	ulValue  = HOSTMSK(spi_control_register_CR_softreset);
	ulValue |= HOSTMSK(spi_control_register_CR_clr_infifo);
	ulValue |= HOSTMSK(spi_control_register_CR_clr_outfifo);
	ptSpiUnit->ulSpi_control_register = ulValue;

	/* Disable the spi interface. */
	ptSpiUnit->ulSpi_control_register = 0;

	/* Reset status bits. */
	ptSpiUnit->ulSpi_status_register = 0;

	/* Do not use irqs for. */
	ptSpiUnit->ulSpi_interrupt_control_register = 0;
}


int boot_drv_spi_init(SPI_CFG_T *ptCfg, const SPI_CONFIGURATION_T *ptSpiCfg)
{
	unsigned long ulValue;
	int iResult;
	unsigned int uiIdleCfg;
	unsigned char ucIdleChar;
	HOSTADEF(SPI) *ptSpiUnit;
	unsigned int uiChipSelect;


	iResult = 0;

	/* Get the pointer to the registers. */
	ptSpiUnit = ptCfg->ptUnit;

	/* Get the chip select value. */
	uiChipSelect = ptSpiCfg->uiChipSelect;
	ptCfg->ulSpeed = ptSpiCfg->ulInitialSpeedKhz;            /* initial device speed in kHz */
	ptCfg->ulMaximumSpeedKhz = ptSpiCfg->ulMaximumSpeedKhz;  /* The maximum allowed speed on the interface. */
	ptCfg->uiIdleCfg = ptSpiCfg->uiIdleCfg;                  /* the idle configuration */
	ptCfg->tMode = ptSpiCfg->uiMode;                         /* bus mode */
	ptCfg->uiChipSelect = 1U<<uiChipSelect;                  /* chip select */

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

	/* soft reset spi and clear both fifos */
	ulValue  = HOSTMSK(spi_control_register_CR_softreset);
	ulValue |= HOSTMSK(spi_control_register_CR_clr_infifo);
	ulValue |= HOSTMSK(spi_control_register_CR_clr_outfifo);
	ptSpiUnit->ulSpi_control_register = ulValue;

	/* configure the spi interface */
	ulValue  = HOSTMSK(spi_control_register_CR_read);                /* Enable reading data from SPI_MISO. */
	ulValue |= HOSTMSK(spi_control_register_CR_write);               /* Enable writing data to SPI_MOSI. */
	ulValue |= HOSTMSK(spi_control_register_CR_ms);                  /* Set the unit to master mode. */
	ulValue |= (7<<HOSTSRT(spi_control_register_CR_burst));          /* Set the burst size to the maximum. */
	ulValue |= (0<<HOSTSRT(spi_control_register_CR_burstdelay));     /* No burst delay. */
	ulValue |= HOSTMSK(spi_control_register_CR_en);                  /* Enable the interface. */
	ulValue |= spi_get_device_speed_representation(ptCfg, ptCfg->ulSpeed);  /* clock divider for SCK */

	/* Set the clock polarity. */
	/* Mode 2 and 3 have cpol=1 . */
	if( (ptCfg->tMode==SPI_MODE2) || (ptCfg->tMode==SPI_MODE3) )
	{
		ulValue |= HOSTMSK(spi_control_register_CR_cpol);
	}

	/* Set the clock phase. */
	/* Mode 0 and 2 have ncpha=1 . */
	if( (ptCfg->tMode==SPI_MODE0) || (ptCfg->tMode==SPI_MODE2) )
	{
		ulValue |= HOSTMSK(spi_control_register_CR_ncpha);
	}

	/* Write value to control register. */
	ptSpiUnit->ulSpi_control_register = ulValue;

	/* Reset status bits. */
	ptSpiUnit->ulSpi_status_register = 0;

	/* Do not use irqs for now. */
	ptSpiUnit->ulSpi_interrupt_control_register = 0;


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

	return iResult;
}

