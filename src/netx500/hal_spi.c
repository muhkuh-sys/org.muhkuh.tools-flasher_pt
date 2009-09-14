/***************************************************************************    
 *   Copyright (C) 2008 by Hilscher GmbH                                   *    
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
/***************************************************************************    
  File          : hal_spi.c                                                     
 ----------------------------------------------------------------------------   
  Description:                                                                  
                                                                                
      SPI Functions for the netX100/500                                              
 ----------------------------------------------------------------------------   
  Todo:                                                                         
                                                                                
 ----------------------------------------------------------------------------   
  Known Problems:                                                               
                                                                                
    -                                                                           
                                                                                
 ----------------------------------------------------------------------------   
 ***************************************************************************/   
                                                                                
                                                                                
/*                                                                              
************************************************************                    
*   Inclusion Area                                                              
************************************************************                    
*/                                                                              

#include <string.h>

#include "hal_spi.h"
#include "netx_io_areas.h"


typedef struct
{
	unsigned long ulSpeed;
	HAL_SPI_SPEED_t tSpiClock;
} SPI_KHZ_TO_CLOCK_T;

/* speed steps for netX100/500 */
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
	{ 25000, HAL_SPI_SPEED_25_0MHz }
	/* NOTE: do not use 50MHz, this does not work */
};


/*****************************************************************************/
/*! This function initialize the SPI interface                                 
* The function initiallize the SPI with the entered parameters.                
*   \param ptHalSpi   The Parameter Set for the SPI Interface                  
*                                                                              
*                     ptSpiRegBase  Pointer to the SPI Register Block          
*                     uiIdleChar    Idle Character                             
*                     ulSpeed       SPI Clock Speed                            
*                     tMode         Bus Mode                                 */
/*****************************************************************************/
void HalSPI_Init(const HAL_SPI_T *ptHalSpi)
{
	NX500_SPI_AREA_T *ptSpiRegBase;
	unsigned long ulVal;


	/* get the base address */
	ptSpiRegBase = ptHalSpi->ptSpiRegBase;

	/* soft reset spi and clear both fifos */
	ptSpiRegBase->ulSpi_control_register = HOSTMSK(spi_control_register_CR_softreset) |
						       HOSTMSK(spi_control_register_CR_clr_infifo)|
						       HOSTMSK(spi_control_register_CR_clr_outfifo);

	/* configure the spi interface */
	ulVal =	HOSTMSK(spi_control_register_CR_read)  |				    /* enable read              */
			HOSTMSK(spi_control_register_CR_write) |				    /* enable write             */
			HOSTMSK(spi_control_register_CR_ms)    |				    /* me master                */
			(7<<HOSTSRT(spi_control_register_CR_burst)) |	    /* max possible burst block */
			(0<<HOSTSRT(spi_control_register_CR_burstdelay))|	/* 0 SCLK burst delay       */
			HOSTMSK(spi_control_register_CR_en) |				      /* enable spi interface     */
			ptHalSpi->ulSpeed<<1;							            /* clock divider for SCK    */

	/* set the clock polarity */
	/* mode 2 and 3 have cpol=1 */
	if( (ptHalSpi->tMode==HAL_SPI_MODE2) || (ptHalSpi->tMode==HAL_SPI_MODE3) )
	{
		ulVal |= HOSTMSK(spi_control_register_CR_cpol);
	}

	/* set the clock phase */
	/* mode 0 and 2 have ncpha=1 */
	if( (ptHalSpi->tMode==HAL_SPI_MODE0) || (ptHalSpi->tMode==HAL_SPI_MODE2) )
	{
		ulVal |= HOSTMSK(spi_control_register_CR_ncpha);
	}

	/* write value to control register */
	ptSpiRegBase->ulSpi_control_register = ulVal;

	/* reset status bits */
	ptSpiRegBase->ulSpi_status_register = 0;

	/* do not use irqs for now */
	ptSpiRegBase->ulSpi_interrupt_control_register = 0;
}


/*****************************************************************************/
/*! This function sends IDLE Bytes                                             
* The function sends IDLE Bytes to the Bus to bring the SPI bus into a defined 
* condition                                                                    
*   \param ptHalSpi   The Parameter Set for the SPI Interface                  
*                                                                              
*                     ptSpiRegBase  Pointer to the SPI Register Block          
*                     uiIdleChar    Idle Character                             
*                     ulSpeed       SPI Clock Speed                            
*                     tMode         Bus Mode                                   
*                                                                              
*   \param  uiCnt       ToDo number of IDLE Bits???                            
*   \return ToDo           */                                                  
/*****************************************************************************/
int HalSPI_SendIdles(const HAL_SPI_T *ptHalSpi, unsigned int uiCnt)
{
	/* send 10 idle bytes */
	return HalSPI_BlockIo(ptHalSpi, uiCnt, NULL, NULL);
}


/*****************************************************************************/
/*! This function ToDo                                                         
* The function  ToDo                                                           
*   \param ptHalSpi   The Parameter Set for the SPI Interface                  
*                                                                              
*                     ptSpiRegBase  Pointer to the SPI Register Block          
*                     uiIdleChar    Idle Character                             
*                     ulSpeed       SPI Clock Speed                            
*                     tMode         Bus Mode                                   
*                                                                              
*   \param  ulLength        Lenght of the Block                                
*   \param  *pucOutBuffer   Pointer to the SPI Output Buffer                   
*   \param  *pucInBuffer    Pointer to the SPI Input Buffer                    
*   \return 1               Result = 1 all ok; Result = 0 failure.           */
/*****************************************************************************/
int HalSPI_BlockIo(const HAL_SPI_T *ptHalSpi, unsigned long ulLength, const unsigned char *pucOutBuffer, unsigned char *pucInBuffer)
{
	unsigned int  uiOutputByte = 0;
	unsigned long ulCnt;
	unsigned int  uiInputByte;
           int  iResult;


	/* transfer nothing? */
	if( ulLength==0 )
	{
		return 1;
	}

	/* send data or idle chars? */
	if( pucOutBuffer==NULL )
	{
		/* no output array passed -> send idle chars */
		uiOutputByte = ptHalSpi->uiIdleChar;
	}

	ulCnt = ulLength;
	do
	{
		/* send data? */
		if( pucOutBuffer!=NULL )
		{
			/* yes -> get next byte */
			uiOutputByte = *(pucOutBuffer++);
		}

		/* send and receive one byte */
		iResult = HalSPI_ExchangeByte(ptHalSpi, uiOutputByte, &uiInputByte);
		/* check for error */
		if( !iResult )
		{
			break;
		}

		if( pucInBuffer!=NULL )
		{
			*(pucInBuffer++) = (unsigned char)uiInputByte;
		}
	} while( --ulCnt!=0 );

	return iResult;
}


/*****************************************************************************/ 
/*! This function ToDo                                                          
* The function  ToDo                                                            
*   \param ptHalSpi   The Parameter Set for the SPI Interface                   
*                                                                               
*                     ptSpiRegBase  Pointer to the SPI Register Block           
*                     uiIdleChar    Idle Character                              
*                     ulSpeed       SPI Clock Speed                             
*                     tMode         Bus Mode                                    
*                                                                               
*   \param  uiOutByte       Output Byte to write on the SPI Bus                 
*   \param  *puiRecByte     ToDo                                                
*   \return 1               Result = 1 all ok; Result = 0 failure.           */ 
/*****************************************************************************/ 
int HalSPI_ExchangeByte(const HAL_SPI_T *ptHalSpi, unsigned int uiSendByte, unsigned int *puiRecByte)
{
	NX500_SPI_AREA_T *ptSpiRegBase;
	unsigned long ulOutFuel;
	unsigned int uiRecByte;


	/* get the base address */
	ptSpiRegBase = ptHalSpi->ptSpiRegBase;

	/* limit input value to byte size */
	uiSendByte &= 0xff;

	/* write byte to spi bus */
	ptSpiRegBase->ulSpi_data_register = uiSendByte | HOSTMSK(spi_data_register_dr_valid0);

	/* wait until all bytes are clocked out. There will be a byte in the
	 * receive buffer */
	/* TODO: limit the polling time, this will wait forever! On timeout return -1 . */
	do
	{
		ulOutFuel   = ptSpiRegBase->ulSpi_status_register & HOSTMSK(spi_status_register_SR_out_fuel_val);
	} while( ulOutFuel!=0 );

	/* get the received byte */
	uiRecByte = ptSpiRegBase->ulSpi_data_register & HOSTMSK(spi_data_register_data_byte_0);

    /* return the received byte only if a valid pointer was passed */
    if( puiRecByte!=NULL )
    {
      *puiRecByte = uiRecByte;
    }

    /* receive ok */
	return 1;
}


/*****************************************************************************/
/*! This function selects the slave device                                     
* The function selects the SPI-slave device                                    
*                                                                              
*   \param ptHalSpi   The Parameter Set for the SPI Interface                  
*                                                                              
*                     ptSpiRegBase  Pointer to the SPI Register Block          
*                     uiIdleChar    Idle Character                             
*                     ulSpeed       SPI Clock Speed                            
*                     tMode         Bus Mode                                   
*                                                                              
*   \param  uiSlaveId   Number of the used slave device                      */
/*****************************************************************************/
void HalSPI_SlaveSelect(const HAL_SPI_T *ptHalSpi, unsigned int uiSlaveId)
{
	NX500_SPI_AREA_T *ptSpiRegBase;
	unsigned long ulVal;


	/* get the base address */
	ptSpiRegBase = ptHalSpi->ptSpiRegBase;

	/* get control register contents */
	ulVal = ptSpiRegBase->ulSpi_control_register;
	
	/* mask out the slave select bits */
	ulVal &= ~HOSTMSK(spi_control_register_CR_ss);
	
	/* mask in the new slave id */
	ulVal |= uiSlaveId<<HOSTSRT(spi_control_register_CR_ss);
	
	/* clear in and out fifo */
	ulVal |= HOSTMSK(spi_control_register_CR_clr_infifo)|HOSTMSK(spi_control_register_CR_clr_outfifo);
	
	/* write back new value */
	ptSpiRegBase->ulSpi_control_register = ulVal;
}


/*****************************************************************************/
/*! This function identify the slave speed                                     
* The function tries to identify the speed of the used SPI-Slave device        
*                                                                              
*   \param  ulSpeed   Speed                                                    
*   \param  Return    Device Speed                                           */
/*****************************************************************************/
unsigned long HalSpiGetSupportedSpeed(unsigned long ulSpeed)
{
	unsigned long ulDeviceSpecificSpeed;
	unsigned int uiCnt;


	/* start at the end of the list */
	uiCnt = sizeof(aulSpeedSteps)/sizeof(aulSpeedSteps[0]);

	/* get the minimum matching entry */
	do
	{
		--uiCnt;
		ulDeviceSpecificSpeed = aulSpeedSteps[uiCnt].ulSpeed;
		if( ulSpeed>=ulDeviceSpecificSpeed )
		{
			break;
		}
	} while( uiCnt!=0 );

	/* return the supported speed */
	return ulDeviceSpecificSpeed;
}


/*****************************************************************************/
/*! This function identify the slave speed                                     
* The function tries to identify the speed of the used SPI-Slave device        
*                                                                              
*   \param  ulSpeed   Speed                                                    
*   \param  Return    Device Speed                                           */
/*****************************************************************************/
HAL_SPI_SPEED_t HalSpiGetDeviceSpeedRepresentation(unsigned long ulSpeed)
{
	unsigned int uiCnt;


	/* start at the end of the list */
	uiCnt = sizeof(aulSpeedSteps)/sizeof(aulSpeedSteps[0]);

	/* get the minimum matching entry */
	do
	{
		--uiCnt;
		if( ulSpeed>=aulSpeedSteps[uiCnt].ulSpeed )
		{
			break;
		}
	} while( uiCnt!=0 );

	/* return the supported  */
	return aulSpeedSteps[uiCnt].tSpiClock;
}
