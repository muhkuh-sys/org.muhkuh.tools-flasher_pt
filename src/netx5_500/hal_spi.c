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


#include <string.h>
#include "hal_spi.h"

#include "netx500/netx500_regdef.h"
#include "netx5_500/netx5_io_areas.h"


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
int HalSPI_Init(HAL_SPI_T *ptHalSpi, unsigned int uiUnit)
{
	NX5_SPI_AREA_T *ptSpiRegBase;
	unsigned long ulVal;
	volatile unsigned long ulDummy;
	int iResult;


	iResult = 1;

	/* get the base address of the SPI interface */
	if( uiUnit==0 )
	{
		ptSpiRegBase = (NX5_SPI_AREA_T*)(Addr_NX500_hif_ahbls6+NX5_DPM_OFFSET_SPI);
	}
	else
	{
		iResult = 0;
	}

	if( iResult!=0 )
	{
		ptHalSpi->ptSpiRegBase = ptSpiRegBase;

		/* set 8 bits */
		ulVal  = 7 << SRT_NX5_spi_cr0_datasize;
		/* set speed and filter */
		ulVal |= ptHalSpi->ulSpeed;


		/* set the clock polarity  */
		/* mode 2 and 3 have spo=1 */
		if( (ptHalSpi->tMode==HAL_SPI_MODE2) || (ptHalSpi->tMode==HAL_SPI_MODE3) )
		{
			ulVal |= MSK_NX5_spi_cr0_SPO;
		}

		/* set the clock phase     */
		/* mode 0 and 2 have sph=1 */
		if( (ptHalSpi->tMode==HAL_SPI_MODE1) || (ptHalSpi->tMode==HAL_SPI_MODE3) )
		{
			ulVal |= MSK_NX5_spi_cr0_SPH;
		}

		/* write the value to the config register */
		ptSpiRegBase->aulSpi_cr[0] = ulVal;

		/* manual chipselect */
		ulVal  = MSK_NX5_spi_cr1_fss_static;
		/* enable the interface */
		ulVal |= MSK_NX5_spi_cr1_SSE;
		ptSpiRegBase->aulSpi_cr[1] = ulVal;

		/* do not use irqs in bootloader */
		ptSpiRegBase->ulSpi_imsc = 0;

		/* clear input fifo */
		while( (ptSpiRegBase->ulSpi_sr&MSK_NX5_spi_sr_rx_fifo_level)!=0 )
		{
			/* get one byte from the fifo */
			ulDummy = ptSpiRegBase->ulSpi_dr;
		}
	}

	return iResult;
}


/*****************************************************************************/
/*! This function clear the SPI bus
* The function clear the SPI bus.   
*   \param ptHalSpi   The Parameter Set for the SPI Interface
*
*                     ptSpiRegBase  Pointer to the SPI Register Block
*                     uiIdleChar    Idle Character
*                     ulSpeed       SPI Clock Speed
*                     tMode         Bus Mode
*   \return iResult   ToDo*/
/*****************************************************************************/
int HalSPI_ClearBus(const HAL_SPI_T *ptHalSpi)
{
	int iCnt;
	int iResult;


	/* send 10 HalSPI_IdleByte */
	iCnt = 0;
	do
	{
		iResult = HalSPI_ExchangeByte(ptHalSpi, ptHalSpi->uiIdleChar, NULL);
		++iCnt;
	} while( iCnt<10 && iResult!=0 );

	/* return result */
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
*   \param  ulLength        Lenght of the Block
*   \param  *pucOutBuffer   Pointer to the SPI Output Buffer
*   \param  *pucInBuffer    Pointer to the SPI Input Buffer
*   \return 1               Result = 1 all ok; Result = 0 failure.           */
/*****************************************************************************/
int HalSPI_BlockIo(const HAL_SPI_T *ptHalSpi, unsigned long ulLength, const unsigned char *pucOutBuffer, unsigned char *pucInBuffer)
{
	unsigned long ulCnt;
	unsigned int uiByte;


	if( ulLength==0 )
	{
		return 1;
	}

	/* send data */
	ulCnt = ulLength;
	do
	{
		if( pucOutBuffer!=NULL )
		{
			uiByte = *(pucOutBuffer++);
		}
		else
		{
			uiByte = ptHalSpi->uiIdleChar;
		}
		HalSPI_ExchangeByte(ptHalSpi, uiByte, &uiByte);

		if( pucInBuffer!=NULL )
		{
			*(pucInBuffer++) = (unsigned char)uiByte;
		}
	} while( --ulCnt!=0 );
	
	return 1;
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
int HalSPI_ExchangeByte(const HAL_SPI_T *ptHalSpi, unsigned int uiOutByte, unsigned int *puiRecByte)
{
	NX5_SPI_AREA_T *ptRegs;
	unsigned long ulVal;


	/* get the base address of tghe SPI interface */
	ptRegs = ptHalSpi->ptSpiRegBase;

	/* write byte to spi bus */
	ptRegs->ulSpi_dr = uiOutByte;

	/* wait for operation finish */
	do
	{
		ulVal  = ptRegs->ulSpi_sr;
		ulVal &= MSK_NX5_spi_sr_BSY;
	} while( ulVal!=0 );

	/* wait for one byte in the fifo */
	do
	{
		ulVal = ptRegs->ulSpi_sr & MSK_NX5_spi_sr_rx_fifo_level;
	} while( ulVal==0 );

	/* get the response */
	ulVal  = ptRegs->ulSpi_dr;
	ulVal &= MSK_NX5_spi_dr_data;

	/* return the response */
	if( puiRecByte!=NULL )
	{
		*puiRecByte = ulVal;
	}

	/* ok! */
	return 1;
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
	/* send idle bytes */
	return HalSPI_BlockIo(ptHalSpi, uiCnt, NULL, NULL);
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
	NX5_SPI_AREA_T *ptRegs;
	unsigned long ulVal;


	/* get the base address of the SPI interface */
	ptRegs = ptHalSpi->ptSpiRegBase;

	/* limit the slave id to valid range */
	uiSlaveId <<= SRT_NX5_spi_cr1_fss;
	uiSlaveId  &= MSK_NX5_spi_cr1_fss;

	/* get control register contents */
	ulVal  = ptRegs->aulSpi_cr[1];

	/* mask out the slave select bits */
	ulVal &= ~MSK_NX5_spi_cr1_fss;

	/* mask in the new slave id */
	ulVal |= uiSlaveId;

	/* write back new value */
	ptRegs->aulSpi_cr[1] = ulVal;
}


/*****************************************************************************/ 
/*! This function identify the slave speed
* The function tries to identify the speed of the used SPI-Slave device
*
*   \param  ulSpeed   Speed
*   \param  Return    Device Speed                                           */
/*****************************************************************************/ 
unsigned long HalSpiGetDeviceSpeedRepresentation(unsigned long ulSpeed)
{
	unsigned long ulDevSpeed;
	unsigned long ulInputFilter;


	/* ulSpeed is in kHz */

	/* limit speed to upper border */
	if( ulSpeed>25000 )
	{
		ulSpeed = 25000;
	}

	/* convert speed to "multiply add value" */
	ulDevSpeed  = ulSpeed * 4096;

	/* NOTE: do not round up here */
	ulDevSpeed /= 100000;

	/* use input filtering? */
	ulInputFilter = 0;
	if( ulDevSpeed<=0x0200 )
	{
		ulInputFilter = MSK_NX5_spi_cr0_filter_in;
	}

	/* shift to register position */
	ulDevSpeed <<= SRT_NX5_spi_cr0_sck_muladd;

	/* add filter bit */
	ulDevSpeed |= ulInputFilter;

	return ulDevSpeed;
}

