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


#ifndef __parflash_common_h__
#define __parflash_common_h__


NETX_CONSOLEAPP_RESULT_T parflash_writeImage(PFLASH_DEVICE ptFlashDev, unsigned long ulStartSector, const unsigned char *pbData, unsigned long ulDataByteLen);
NETX_CONSOLEAPP_RESULT_T parflash_erase     (PFLASH_DEVICE ptFlashDev, unsigned long ulStartSector, unsigned long ulDataByteLen);
NETX_CONSOLEAPP_RESULT_T parflash_read      (PFLASH_DEVICE ptFlashDev, unsigned long ulStartSector, unsigned char *pbData, unsigned long ulDataByteLen);
NETX_CONSOLEAPP_RESULT_T parflash_verify    (PFLASH_DEVICE ptFlashDev, unsigned long ulStartSector, const unsigned char *pbData, unsigned long ulDataByteLen);


#endif	// __parflash_common_h__
