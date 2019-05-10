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

#if ASIC_TYP==ASIC_TYP_NETX4000
#include "portcontrol.h"
#endif

/* Note: This scheme works only for a single SQI unit. */
#if ASIC_TYP==ASIC_TYP_NETX10
static const HOSTMMIODEF aatMmioValues[3][4] =
{
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
		NX10_MMIO_CFG_spi0_cs1n,        /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	},

	/*
	 * Chip select 2
	 */
	{
		NX10_MMIO_CFG_spi0_cs2n,        /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	}
};
#elif ASIC_TYP==ASIC_TYP_NETX56
static const HOSTMMIODEF aatMmioValues[3][4] =
{
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
		NX56_MMIO_CFG_spi0_cs2n,        /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	}
};
#elif ASIC_TYP==ASIC_TYP_NETX4000
static const HOSTMMIODEF aatMmioValues[1][4] =
{
	/* Both SQI ports on the netX4000 are not routed through the MMIO matrix. */
	/*
	 * Chip select 0
	 */
	 /* no MMMIOs used on SCIT board */
	{
		0xffU,                          /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	}
};


#if 0
/* This tables shows the port control indices for the SQI0 pins.
 * There is only CS0. All other chip selects are not routed to the outside.
 */
static const unsigned short ausPortcontrol_Index_SQI0_CS0[6] =
{
	PORTCONTROL_INDEX( 1,  0),      // SQI0_CLK
	PORTCONTROL_INDEX( 1,  1),      // SQI0_MOSI
	PORTCONTROL_INDEX( 1,  2),      // SQI0_MISO
	PORTCONTROL_INDEX( 1,  3),      // SQI0_SIO2
	PORTCONTROL_INDEX( 1,  4),      // SQI0_SIO3
	PORTCONTROL_INDEX( 1,  5)       // SQI0_CS0N
};


/* This tables shows the port control indices for the SQI1 pins.
 * There is only CS0. All other chip selects are not routed to the outside.
 */
static const unsigned short ausPortcontrol_Index_SQI1_CS0[6] =
{
	PORTCONTROL_INDEX(10,  3),      // SQI1_CLK
	PORTCONTROL_INDEX(10,  4),      // SQI1_MOSI
	PORTCONTROL_INDEX(10,  5),      // SQI1_MISO
	PORTCONTROL_INDEX(10,  6),      // SQI1_SIO2
	PORTCONTROL_INDEX(10,  7),      // SQI1_SIO3
	PORTCONTROL_INDEX(10,  8)       // SQI1_CS0N
};
#endif

#elif ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
static const HOSTMMIODEF aatMmioValues[1][4] =
{
	/* The SQI port on the netX90 is not routed through the MMIO matrix. */
	/*
	 * Chip select 0
	 */
	{
		0xffU,                          /* chip select */
		0xffU,                          /* clock */
		0xffU,                          /* MISO */
		0xffU                           /* MOSI */
	}
};


#else
#       error "The SQI driver does not support this ASIC type!"
#endif


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
static unsigned char qsi_spi_exchange_byte(const FLASHER_SPI_CFG_T *ptCfg, unsigned char ucByteSend)
{
	HOSTADEF(SQI) * ptSqiArea;
	unsigned long ulValue;
	unsigned char ucByteReceive;

	ptSqiArea = ptCfg->pvUnit;

	/* set mode to "full duplex" */
	ulValue  = ptCfg->ulTrcBase;
	ulValue |= 3 << HOSTSRT(sqi_tcr_duplex);
	/* start the transfer */
	ulValue |= HOSTMSK(sqi_tcr_start_transfer);
	ptSqiArea->ulSqi_tcr = ulValue;

	/* send byte */
	ptSqiArea->ulSqi_dr = ucByteSend;

	/* Wait for one byte in the FIFO. */
	do
	{
		ulValue  = ptSqiArea->ulSqi_sr;
		ulValue &= HOSTMSK(sqi_sr_busy);
	} while( ulValue!=0 );

	/* grab byte */
	ucByteReceive = (unsigned char)(ptSqiArea->ulSqi_dr);
	return ucByteReceive;
}


/*-------------------------------------------------------------------------*/


static unsigned long qsi_get_device_speed_representation(const FLASHER_SPI_CFG_T *ptCfg, unsigned int uiSpeed)
{
	unsigned long ulDevSpeed;
	unsigned long ulInputFilter;
	unsigned long ulMaximumSpeedKhz;


	/* ulSpeed is in kHz */

	/* Limit the speed. */
	ulMaximumSpeedKhz = ptCfg->ulMaximumSpeedKhz;
	if( uiSpeed>ulMaximumSpeedKhz )
	{
		uiSpeed = ulMaximumSpeedKhz;
	}

	/* Limit the speed to the maximum possible value of the hardware. */
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


static int qsi_slave_select(const FLASHER_SPI_CFG_T *ptCfg, int fIsSelected)
{
	HOSTADEF(SQI) * ptSqiArea;
	int iResult;
	unsigned long uiChipSelect;
	unsigned long ulValue;

	ptSqiArea = ptCfg->pvUnit;

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

	/* mask out the slave select bits */
	ulValue &= ~HOSTMSK(sqi_cr1_fss);

	/* mask in the new slave id */
	ulValue |= uiChipSelect;

	/* write back new value */
	ptSqiArea->aulSqi_cr[1] = ulValue;

	return iResult;
}


#if 0
static int qsi_send_idle(const FLASHER_SPI_CFG_T *ptCfg, size_t sizIdleChars)
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
static int qsi_send_idle(const FLASHER_SPI_CFG_T *ptCfg, size_t sizIdleChars)
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
static int qsi_receive_data(const FLASHER_SPI_CFG_T *ptCfg, unsigned char *pucData, size_t sizData)
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
static int qsi_receive_data(const FLASHER_SPI_CFG_T *ptCfg, unsigned char *pucData, size_t sizData)
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
static int qsi_send_data(const FLASHER_SPI_CFG_T *ptCfg, const unsigned char *pucData, size_t sizData)
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
static int qsi_send_data(const FLASHER_SPI_CFG_T *ptCfg, const unsigned char *pucData, size_t sizData)
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
static int qsi_exchange_data(const FLASHER_SPI_CFG_T *ptCfg, const unsigned char *pucDataOut, unsigned char *pucDataIn, size_t sizData)
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
static int qsi_exchange_data(const FLASHER_SPI_CFG_T *ptCfg, const unsigned char *pucDataOut, unsigned char *pucDataIn, size_t sizData)
{
	while( sizData>0 )
	{
		*(pucDataIn++) = qsi_spi_exchange_byte(ptCfg, *(pucDataOut++));
		--sizData;
	}
	return 0;
}
#endif

static void qsi_set_new_speed(const FLASHER_SPI_CFG_T *ptCfg, unsigned long ulDeviceSpecificSpeed)
{
	HOSTADEF(SQI) * ptSqiArea;
	unsigned long ulValue;

	ptSqiArea = ptCfg->pvUnit;

	ulDeviceSpecificSpeed &= HOSTMSK(sqi_cr0_sck_muladd) | HOSTMSK(sqi_cr0_filter_in);

	ulValue  = ptSqiArea->aulSqi_cr[0];
	ulValue &= ~(HOSTMSK(sqi_cr0_sck_muladd)|HOSTMSK(sqi_cr0_filter_in));
	ulValue |= ulDeviceSpecificSpeed;
	ptSqiArea->aulSqi_cr[0] = ulValue;
}


static void qsi_deactivate(const FLASHER_SPI_CFG_T *ptCfg)
{
	HOSTADEF(SQI) * ptSqiArea;
#if ASIC_TYP==ASIC_TYP_NETX56
	HOSTDEF(ptAsicCtrlArea);
#endif
	unsigned long ulValue;

	ptSqiArea = ptCfg->pvUnit;

	/* Deactivate IRQs. */
	ptSqiArea->ulSqi_irq_mask = 0;

	/* Clear all pending IRQs. */
	ulValue  = HOSTMSK(sqi_irq_clear_RORIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RTIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_TXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_rxneic);
	ulValue |= HOSTMSK(sqi_irq_clear_rxfic);
	ulValue |= HOSTMSK(sqi_irq_clear_txeic);
	ulValue |= HOSTMSK(sqi_irq_clear_trans_end);
	ptSqiArea->ulSqi_irq_clear = ulValue;

#if ASIC_TYP==ASIC_TYP_NETX10 || ASIC_TYP==ASIC_TYP_NETX56
	/* Deactivate IRQ routing to the CPUs. */
	ptSqiArea->ulSqi_irq_cpu_sel = 0;
#endif

	/* Deactivate DMAs. */
	ptSqiArea->ulSqi_dmacr = 0;

	/* Deactivate XIP. */
	ptSqiArea->ulSqi_sqirom_cfg = 0;

	ptSqiArea->ulSqi_tcr = 0;
	ptSqiArea->ulSqi_pio_oe = 0;
	ptSqiArea->ulSqi_pio_out = 0;

	/* Deactivate the unit. */
	ptSqiArea->aulSqi_cr[0] = 0;
	ptSqiArea->aulSqi_cr[1] = 0;

	/* Deactivate the SPI pins. */
	mmio_deactivate(ptCfg->aucMmio, sizeof(ptCfg->aucMmio), aatMmioValues[ptCfg->uiChipSelect]);

#if ASIC_TYP==ASIC_TYP_NETX56
	/* Deactivate the SIO2 and SIO3 pins. */
	ulValue  = ptAsicCtrlArea->ulIo_config2;
	ulValue &= ~HOSTMSK(io_config2_sel_sqi);
	ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
	ptAsicCtrlArea->ulIo_config2 = ulValue;
#endif
}


int flasher_drv_sqi_init(FLASHER_SPI_CFG_T *ptCfg, const FLASHER_SPI_CONFIGURATION_T *ptSpiCfg, unsigned int uiSqiUnit)
{
	HOSTADEF(SQI) *ptSqiArea;

#if ASIC_TYP==ASIC_TYP_NETX56
	HOSTDEF(ptAsicCtrlArea);
#elif ASIC_TYP==ASIC_TYP_NETX4000
#       if 0
	const unsigned short *pusPortControlIndex;
#       endif
#endif
	unsigned long ulValue;
	int iResult;
	unsigned int uiIdleCfg;
	unsigned char ucIdleChar;
	unsigned int uiChipSelect;


	ptSqiArea = NULL;
#if ASIC_TYP==ASIC_TYP_NETX10 || ASIC_TYP==ASIC_TYP_NETX56
	if( uiSqiUnit==0 )
	{
		ptSqiArea = (HOSTADEF(SQI)*)HOSTADDR(sqi);
	}

#elif ASIC_TYP==ASIC_TYP_NETX4000
	if( uiSqiUnit==0 )
	{
		ptSqiArea = (HOSTADEF(SQI)*)HOSTADDR(SQI0);
#if 0
		pusPortControlIndex = ausPortcontrol_Index_SQI0_CS0;
#endif
	}
	else if( uiSqiUnit==1 )
	{
		ptSqiArea = (HOSTADEF(SQI)*)HOSTADDR(SQI1);
#if 0
		pusPortControlIndex = ausPortcontrol_Index_SQI1_CS0;
#endif
	}

#elif ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
	if( uiSqiUnit==0 )
	{
		ptSqiArea = (HOSTADEF(SQI)*)HOSTADDR(sqi);
	}
#endif

	if( ptSqiArea==NULL )
	{
		/* Error: the unit is invalid! */
		iResult = -1;
	}
	else
	{
		iResult = 0;

		ptCfg->pvUnit = ptSqiArea;

		/* Get the chip select value. */
		uiChipSelect = ptSpiCfg->uiChipSelect;

		ptCfg->ulSpeed = ptSpiCfg->ulInitialSpeedKhz;            /* initial device speed in kHz */
		ptCfg->ulMaximumSpeedKhz = ptSpiCfg->ulMaximumSpeedKhz;  /* The maximum allowed speed on the interface. */
		ptCfg->uiIdleCfg = ptSpiCfg->uiIdleCfg;                  /* the idle configuration */
		ptCfg->tMode = ptSpiCfg->uiMode;                         /* bus mode */
		ptCfg->uiChipSelect = 1U<<uiChipSelect;                  /* chip select */

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

		/* Set up the port control unit. */
#if 0
		pusPortControlIndex = ausPortcontrol_Index_SQI0_CS0;
		portcontrol_apply(pusPortControlIndex, ptSpiCfg->ausPortControl, sizeof(ptSpiCfg->ausPortControl)/sizeof(ptSpiCfg->ausPortControl[0]));
#endif

		/* Do not use IRQs in flasher. */
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

#if ASIC_TYP==ASIC_TYP_NETX10 || ASIC_TYP==ASIC_TYP_NETX56
		/* Do not route the IRQs to a CPU. */
		ptSqiArea->ulSqi_irq_cpu_sel = 0;
#endif

		/* Do not use DMAs. */
		ptSqiArea->ulSqi_dmacr = 0;

		/* Do not use XIP. */
		ptSqiArea->ulSqi_sqirom_cfg = 0;

		/* Set 8 bits. */
		ulValue  = 7 << HOSTSRT(sqi_cr0_datasize);
		/* Set speed and filter. */
		ulValue |= qsi_get_device_speed_representation(ptCfg, ptCfg->ulSpeed);
		/* Start in SPI mode: use only IO0 and IO1 for transfer. */
		ulValue |= 0 << HOSTSRT(sqi_cr0_sio_cfg);
		/* Set the clock polarity. */
		if( (ptCfg->tMode==FLASHER_SPI_MODE2) || (ptCfg->tMode==FLASHER_SPI_MODE3) )
		{
			ulValue |= HOSTMSK(sqi_cr0_sck_pol);
		}
		/* Set the clock phase. */
		if( (ptCfg->tMode==FLASHER_SPI_MODE1) || (ptCfg->tMode==FLASHER_SPI_MODE3) )
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

#if ASIC_TYP==ASIC_TYP_NETX56
		/* Activate the SIO2 and SIO3 pins. */
		ulValue  = ptAsicCtrlArea->ulIo_config2;
		ulValue |= HOSTMSK(io_config2_sel_sqi);
		ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
		ptAsicCtrlArea->ulIo_config2 = ulValue;
#endif
	}

	return iResult;
}

