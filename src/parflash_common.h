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

#include "netx_consoleapp.h"
#include "cfi_flash.h"


#ifndef __PARFLASH_COMMON_H__
#define __PARFLASH_COMMON_H__


NETX_CONSOLEAPP_RESULT_T parflash_writeImage(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, const unsigned char *pbData, unsigned long ulDataByteLen);
NETX_CONSOLEAPP_RESULT_T parflash_erase(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, unsigned long ulDataByteLen);
NETX_CONSOLEAPP_RESULT_T parflash_read(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, unsigned char *pbData, unsigned long ulDataByteLen);
NETX_CONSOLEAPP_RESULT_T parflash_verify(FLASH_DEVICE_T *ptFlashDev, unsigned long ulStartSector, const unsigned char *pbData, unsigned long ulDataByteLen);


#endif	/* __PARFLASH_COMMON_H__ */
