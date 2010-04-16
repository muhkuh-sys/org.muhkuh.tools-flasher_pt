/*---------------------------------------------------------------------------
  Author : Christoph Thelen

           Hilscher GmbH, Copyright (c) 2006, All Rights Reserved

           Redistribution or unauthorized use without expressed written 
           agreement from the Hilscher GmbH is forbidden
---------------------------------------------------------------------------*/


#include <string.h>

#include "drv_sqi.h"

#include "netx_io_areas.h"
#include "tools.h"


static const MMIO_CFG_T aatMmioValues[3][4] =
{
	/*
	 * Chip select 0
	 */
	{
		0xffU,				/* chip select */
		0xffU,				/* clock */
		0xffU,				/* miso */
		0xffU				/* mosi */
	},

	/*
	 * Chip select 1
	 */
	{
		MMIO_CFG_spi0_cs1n,		/* chip select */
		0xffU,				/* clock */
		0xffU,				/* miso */
		0xffU				/* mosi */
	},

	/*
	 * Chip select 2
	 */
	{
		MMIO_CFG_spi0_cs2n,		/* chip select */
		0xffU,				/* clock */
		0xffU,				/* miso */
		0xffU				/* mosi */
	}
};


//-------------------------------------

/* BootSPI_ExchangeByte
 *
 * Description:
 *   Send and receive one byte on the spi bus.
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

	/* wait for one byte in the fifo */
	do
	{
		ulValue  = ptSqiArea->ulSqi_sr;
		ulValue &= HOSTMSK(sqi_sr_busy);
	} while( ulValue!=0 );

	/* grab byte */
	ucByte = (unsigned char)(ptSqiArea->ulSqi_dr);
	return ucByte;
}

//---------------------------------------------------------------------------


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
	int iResult;
	unsigned long uiChipSelect;
	unsigned long ulValue;


	iResult = 0;

	/* get the chipselect value */
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


static void qsi_send_idle(const SPI_CFG_T *ptCfg, unsigned int uiIdleChars)
{
	unsigned long ulValue;
	unsigned int uiShift;


	/* 0 means 1 cycle */
	++uiIdleChars;

	/* get the current mode */
	ulValue   = ptCfg->ulTrcBase;
	ulValue  &= HOSTMSK(sqi_tcr_mode);
	ulValue >>= HOSTSRT(sqi_tcr_mode);
	uiShift = 3U - ulValue;

	/* convert the number of idle bytes to cycles */
	uiIdleChars <<= uiShift;
	--uiIdleChars;

	/* set mode to "send dummy" */
	ulValue  = ptCfg->ulTrcBase;
	ulValue |= 0 << HOSTSRT(sqi_tcr_duplex);
	/* set the transfer size */
	ulValue |= uiIdleChars << HOSTSRT(sqi_tcr_transfer_size);
	/* start the transfer */
	ulValue |= HOSTMSK(sqi_tcr_start_transfer);
	ptSqiArea->ulSqi_tcr = ulValue;

	/* wait until the transfer is done */
	do
	{
		ulValue  = ptSqiArea->ulSqi_sr;
		ulValue &= HOSTMSK(sqi_sr_busy);
	} while( ulValue!=0 );
}


static unsigned long qsi_read_simple_chksum(const SPI_CFG_T *ptCfg, unsigned long *pulDst, size_t sizDword)
{
	unsigned long ulValue;
	int iCnt;
	unsigned long ulData;
	volatile unsigned long *pulCnt;
	volatile unsigned long *pulEnd;
	unsigned long ulChecksum;


	ulChecksum = 0;

	/* set mode to "receive" */
	ulValue  = ptCfg->ulTrcBase;
	ulValue |= 1 << HOSTSRT(sqi_tcr_duplex);
	/* set the transfer size */
	ulValue |= (sizDword*sizeof(unsigned long) - 1) << HOSTSRT(sqi_tcr_transfer_size);
	/* start the transfer */
	ulValue |= HOSTMSK(sqi_tcr_start_transfer);
	ptSqiArea->ulSqi_tcr = ulValue;

	/* get start and end address */
	pulCnt = pulDst;
	pulEnd = pulDst + sizDword;

	/* check the mode */
	if( (ptCfg->ulTrcBase&HOSTMSK(sqi_tcr_mode))==0 )
	{
		ulData = 0;

		/* mode 0 : the fifo size is 8 bit */
		while( pulCnt<pulEnd )
		{
			iCnt = 3;
			do
			{
				/* wait for one byte in the fifo */
				do
				{
					ulValue  = ptSqiArea->ulSqi_sr;
					ulValue &= HOSTMSK(sqi_sr_rx_fifo_not_empty);
				} while( ulValue==0 );
				/* grab byte */
				ulData >>= 8U;
				ulData  |= ptSqiArea->ulSqi_dr << 24U;
			} while( --iCnt>=0 );
			*pulCnt = ulData;
			ulChecksum += *(pulCnt++);
		}
	}
	else
	{
		/* DSI/QSI mode : the fifo size is 32 bit */
		while( pulCnt<pulEnd )
		{
			/* wait for one dword in the fifo */
			do
			{
				ulValue  = ptSqiArea->ulSqi_sr;
				ulValue &= HOSTMSK(sqi_sr_rx_fifo_not_empty);
			} while( ulValue==0 );

			/* get the dword */
			*pulCnt = ptSqiArea->ulSqi_dr;
			ulChecksum += *(pulCnt++);
		}
	}

	return ulChecksum;
}


static void qsi_set_new_speed(unsigned long ulDeviceSpecificSpeed)
{
	unsigned long ulValue;


	ulDeviceSpecificSpeed &= HOSTMSK(sqi_cr0_sck_muladd) | HOSTMSK(sqi_cr0_filter_in);

	ulValue  = ptSqiArea->aulSqi_cr[0];
	ulValue &= ~(HOSTMSK(sqi_cr0_sck_muladd)|HOSTMSK(sqi_cr0_filter_in));
	ulValue |= ulDeviceSpecificSpeed;
	ptSqiArea->aulSqi_cr[0] = ulValue;
}


static void qsi_deactivate(const SPI_CFG_T *ptCfg)
{
	unsigned long ulValue;


	/* deactivate irqs */
	ptSqiArea->ulSqi_irq_mask = 0;
	/* clear all pending irqs */
	ulValue  = HOSTMSK(sqi_irq_clear_RORIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RTIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_TXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_rxneic);
	ulValue |= HOSTMSK(sqi_irq_clear_rxfic);
	ulValue |= HOSTMSK(sqi_irq_clear_txeic);
	ulValue |= HOSTMSK(sqi_irq_clear_trans_end);
	ptSqiArea->ulSqi_irq_clear = ulValue;
	/* deactivate irq routing to the cpus */
	ptSqiArea->ulSqi_irq_cpu_sel = 0;

	/* deactivate dmas */
	ptSqiArea->ulSqi_dmacr = 0;

	/* deactivate xip */
	ptSqiArea->ulSqi_sqirom_cfg = 0;

	ptSqiArea->ulSqi_tcr = 0;
	ptSqiArea->ulSqi_pio_oe = 0;
	ptSqiArea->ulSqi_pio_out = 0;

	/* deactivate the unit */
	ptSqiArea->aulSqi_cr[0] = 0;
	ptSqiArea->aulSqi_cr[1] = 0;

	/* activate the spi pins */
	boot_spi_deactivate_mmio(ptCfg, aatMmioValues[ptCfg->uiChipSelect]);
}


int boot_drv_sqi_init(SPI_CFG_T *ptCfg, const BOOT_SPI_CONFIGURATION_T *ptSpiCfg, unsigned int uiChipSelect)
{
	unsigned long ulValue;
	int iResult;
	unsigned int uiIdleCfg;
	unsigned char ucIdleChar;


	iResult = 0;

	ptCfg->ulSpeed = ptSpiCfg->ulInitialSpeedKhz;	/* initial device speed in kHz */
	ptCfg->uiIdleCfg = ptSpiCfg->ucIdleCfg;		/* the idle configuration */
	ptCfg->tMode = ptSpiCfg->ucMode;		/* bus mode */
	ptCfg->uiChipSelect = 1U<<uiChipSelect;		/* chip select */

	/* set the function pointers */
	ptCfg->pfnSelect = qsi_slave_select;
	ptCfg->pfnSendIdle = qsi_send_idle;
	ptCfg->pfnReadSimpleChecksum = qsi_read_simple_chksum;
	ptCfg->pfnSetNewSpeed = qsi_set_new_speed;
	ptCfg->pfnExchangeByte = qsi_spi_exchange_byte;
	ptCfg->pfnGetDeviceSpeedRepresentation = qsi_get_device_speed_representation;
	ptCfg->pfnDeactivate = qsi_deactivate;

	/* copy the mmio pins */
	memcpy(ptCfg->aucMmio, ptSpiCfg->aucMmio, sizeof(ptSpiCfg->aucMmio));

	/* do not use irqs in bootloader */
	ptSqiArea->ulSqi_irq_mask = 0;
	/* clear all pending irqs */
	ulValue  = HOSTMSK(sqi_irq_clear_RORIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RTIC);
	ulValue |= HOSTMSK(sqi_irq_clear_RXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_TXIC);
	ulValue |= HOSTMSK(sqi_irq_clear_rxneic);
	ulValue |= HOSTMSK(sqi_irq_clear_rxfic);
	ulValue |= HOSTMSK(sqi_irq_clear_txeic);
	ulValue |= HOSTMSK(sqi_irq_clear_trans_end);
	ptSqiArea->ulSqi_irq_clear = ulValue;
	/* do not route the irqs to a cpu */
	ptSqiArea->ulSqi_irq_cpu_sel = 0;

	/* do not use dmas */
	ptSqiArea->ulSqi_dmacr = 0;

	/* do not use xip */
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


	/* manual chipselect */
	ulValue  = HOSTMSK(sqi_cr1_fss_static);
	/* manual transfer start */
	ulValue |= HOSTMSK(sqi_cr1_spi_trans_ctrl);
	/* enable the interface */
	ulValue |= HOSTMSK(sqi_cr1_sqi_en);
	/* clear both fifos */
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

	/* set the idle char from the tx config */
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
	boot_spi_activate_mmio(ptCfg, aatMmioValues[uiChipSelect]);

	return iResult;
}

