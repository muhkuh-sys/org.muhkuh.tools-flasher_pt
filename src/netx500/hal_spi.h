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
#include "netx_io_areas.h"

#ifndef __HAL_SPI__
#define __HAL_SPI__


typedef enum
{
  HAL_SPI_MODE0 = 0,
  HAL_SPI_MODE1 = 1,
  HAL_SPI_MODE2 = 2,
  HAL_SPI_MODE3 = 3
} HAL_SPI_MODE_t;

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


typedef struct HAL_SPI_Ttag
{
	PSPI_AREA_T    ptSpiRegBase;    /* base address of spi block 	*/
	unsigned int   uiIdleChar;			/* Idle character 						*/
	unsigned long  ulSpeed;
	HAL_SPI_MODE_t tMode;
} HAL_SPI_T;


void HalSPI_Init        (const HAL_SPI_T *ptHalSpi);
int  HalSPI_SendIdles   (const HAL_SPI_T *ptHalSpi, unsigned int  uiCnt);
int  HalSPI_BlockIo     (const HAL_SPI_T *ptHalSpi, unsigned long ulLength,   const unsigned char *pucOutBuffer, unsigned char *pucInBuffer);
int  HalSPI_ExchangeByte(const HAL_SPI_T *ptHalSpi, unsigned int  uiSendByte, unsigned int        *puiRecByte);
void HalSPI_SlaveSelect (const HAL_SPI_T *ptHalSpi, unsigned int  uiSlaveId);
unsigned long   HalSpiGetSupportedSpeed(unsigned long ulSpeed);
HAL_SPI_SPEED_t HalSpiGetDeviceSpeedRepresentation(unsigned long ulSpeed);

#endif	/* __HAL_SPI__ */
