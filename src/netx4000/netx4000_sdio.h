/***************************************************************************
 *   Copyright (C) 2019 by Hilscher GmbH                                   *
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
 *   License along with this program. If not, see                          *
 *   <https://www.gnu.org/licenses/>.                                      *
 ***************************************************************************/

#ifndef __NETX4000_SDIO_H__
#define __NETX4000_SDIO_H__

#include "netx_consoleapp.h"

typedef struct SDIO_OPTIONS_STRUCT
{
	unsigned long   ulPowerUpTimeoutTicks;
	unsigned long   ulResetDelayTicks;
	unsigned long   ulInitialSpeedKHz;
	unsigned long   ulMaximumSpeedKHz;
	unsigned long   ulInitialClockGenerationUs;
	unsigned short ausPortControl[8];
	unsigned char   ucHwTimeoutExponentInitialization;
	unsigned char   ucHwTimeoutExponentTransfer;
} SDIO_OPTIONS_T;


typedef struct SDIO_HANDLE_STRUCT
{
	const SDIO_OPTIONS_T *ptSdioOptions;
	unsigned long ulCurrentSpeedKHz;
	unsigned int  uiCardIsHC;
	unsigned int  uiCardIsMMC;
	unsigned long ulHwCommandTimeoutExponent;
	unsigned long ulSwCommandTimeoutUs;
	unsigned long ulRCA;
	
	unsigned long ulSizeKB;
} SDIO_HANDLE_T;

int sdio_detect(SDIO_HANDLE_T *ptSdioHandle, const SDIO_OPTIONS_T *ptSdioOptions);
int sdio_read_sector(const SDIO_HANDLE_T *ptSdioHandle, unsigned long ulSectorId, unsigned long *pulRead);
int sdio_write_sector(const SDIO_HANDLE_T *ptSdioHandle, unsigned long ulSectorId, unsigned long *pulRead);



#endif  /* __NETX4000_SDIO_H__ */

