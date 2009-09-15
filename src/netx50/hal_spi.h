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
  File          : Hal_SPI.c                                                 
 ----------------------------------------------------------------------------   
  Description:                                                                  
                                                                                
      SPI Functions for the netX50                                                            
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
#include "netx_io_areas.h"


#ifndef __HAL_SPI__
#define __HAL_SPI__

/*
************************************************************
*   Defines for the SPI Interface
************************************************************
*/
#define SPI_MHZ2SPEED(freq) ((unsigned long)(((freq*4096)/100)+0.5))

typedef enum
{
	HAL_SPI_MODE0,
	HAL_SPI_MODE1,
	HAL_SPI_MODE2,
	HAL_SPI_MODE3
} HAL_SPI_MODE_t;

typedef struct
{
	NX50_SPI_AREA_T *ptSpiRegBase;	/* pointer to the spi register block */
	unsigned int uiIdleChar;	/* Idle character */
	unsigned long ulSpeed;		/* device speed in MHz */
	HAL_SPI_MODE_t tMode;		/* bus mode */
} HAL_SPI_T;


/*
************************************************************
*   Function Prototypes, Global
************************************************************
*/
int  HalSPI_Init         (HAL_SPI_T *ptHalSpi, unsigned int uiUnit);
int   HalSPI_ClearBus     (const HAL_SPI_T *ptHalSpi);
int   HalSPI_BlockIo      (const HAL_SPI_T *ptHalSpi, unsigned long ulLength,  const unsigned char *pbOutBuffer, unsigned char *pbInBuffer);
int   HalSPI_ExchangeByte (const HAL_SPI_T *ptHalSpi, unsigned int  uiOutByte, unsigned int *puiRecByte);
int   HalSPI_SendIdles    (const HAL_SPI_T *ptHalSpi, unsigned int  uiCnt);
void  HalSPI_SlaveSelect  (const HAL_SPI_T *ptHalSpi, unsigned int  uiSlaveId);
unsigned long HalSpiGetDeviceSpeedRepresentation(unsigned long ulSpeed);

#endif  /* __HAL_SPI__ */

