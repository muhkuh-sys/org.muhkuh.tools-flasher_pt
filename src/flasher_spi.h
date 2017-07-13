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


#ifndef __FLASHER_SPI_H__
#define __FLASHER_SPI_H__

#include "netx_consoleapp.h"
#include "spi_flash.h"
#if CFG_INCLUDE_SHA1!=0
#       include "sha1.h"
#endif


NETX_CONSOLEAPP_RESULT_T spi_flash(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulFlashStartAdr, unsigned long ulDataByteSize, const unsigned char *pucDataStartAdr);
NETX_CONSOLEAPP_RESULT_T spi_erase(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr);
NETX_CONSOLEAPP_RESULT_T spi_read(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, unsigned char *pucData);
#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T spi_sha1(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, SHA_CTX *ptSha1Context);
#endif
NETX_CONSOLEAPP_RESULT_T spi_verify(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulFlashStartAdr, unsigned long ulFlashEndAdr, const unsigned char *pucData, void **ppvReturnMessage);

NETX_CONSOLEAPP_RESULT_T spi_detect(FLASHER_SPI_CONFIGURATION_T *ptSpiConfiguration, FLASHER_SPI_FLASH_T *ptFlashDescription);
NETX_CONSOLEAPP_RESULT_T spi_isErased(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, void **ppvReturnMessage);
NETX_CONSOLEAPP_RESULT_T spi_getEraseArea(const FLASHER_SPI_FLASH_T *ptFlashDescription, unsigned long ulStartAdr, unsigned long ulEndAdr, unsigned long *pulStartAdr, unsigned long *pulEndAdr);

#endif  /* __FLASHER_SPI_H__ */
