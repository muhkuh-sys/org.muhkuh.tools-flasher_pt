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
  File          : spi_flash.h                                                   
 ---------------------------------------------------------------------------- 
  Description:                                                                
                                                                              
      SPI Flash Functions
 ---------------------------------------------------------------------------- 
  Todo:                                                                       
                                                                              
 ---------------------------------------------------------------------------- 
  Known Problems:                                                             
                                                                              
    -                                                                         
                                                                              
 ---------------------------------------------------------------------------- 
 ***************************************************************************/ 

#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#include "spi.h"
#include "spi_flash_types.h"

/* ------------------------------------- */

typedef struct SPI_FLASH_Ttag
{
	SPIFLASH_ATTRIBUTES_T tAttributes;	/* attributes of the flash      */
	SPI_CFG_T tSpiDev;			/* spi device and it's settings */
	unsigned long ulSectorSize;		/* size of one sector in bytes  */
	unsigned int uiSlaveId;			/* SPI Slave Id of the flash    */
	unsigned int uiPageAdrShift;		/* bitshift for the page part of the address, 0 means no page / byte split  */
	unsigned int uiSectorAdrShift;		/* bitshift for one sector, 0 means no page / byte split                    */
} SPI_FLASH_T;

/*-----------------------------------*/

int Drv_SpiInitializeFlash        (const SPI_CONFIGURATION_T *ptSpiCfg, SPI_FLASH_T *ptFlash);
int Drv_SpiEraseFlashPage         (const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress);
int Drv_SpiEraseFlashSector       (const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress);
int Drv_SpiEraseFlashMultiSectors (const SPI_FLASH_T *ptFlash, unsigned long ulLinearStartAddress, unsigned long ulLinearEndAddress);
int Drv_SpiEraseFlashComplete     (const SPI_FLASH_T *ptFlash);
int Drv_SpiWriteFlashPages        (const SPI_FLASH_T *ptFlash, unsigned long ulOffs, const unsigned char *pabSrc, unsigned long ulNum);
int Drv_SpiReadFlash              (const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, unsigned char       *pucData, size_t sizData);
int Drv_SpiEraseAndWritePage      (const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, const unsigned char *pucData, size_t sizData);
int Drv_SpiWritePage              (const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, const unsigned char *pucData, size_t sizData);

#endif
