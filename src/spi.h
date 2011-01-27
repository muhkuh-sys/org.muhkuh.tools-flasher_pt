/***************************************************************************
 *   Copyright (C) 2010 by Hilscher GmbH                                   *
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


#ifndef __SPI_H__
#define __SPI_H__

#include <stddef.h>

#include "netx_io_areas.h"


#define MSK_SQI_CFG_IDLE_IO1_OE         0x01U
#define SRT_SQI_CFG_IDLE_IO1_OE         0
#define MSK_SQI_CFG_IDLE_IO1_OUT        0x02U
#define SRT_SQI_CFG_IDLE_IO1_OUT        1
#define MSK_SQI_CFG_IDLE_IO2_OE         0x04U
#define SRT_SQI_CFG_IDLE_IO2_OE         2
#define MSK_SQI_CFG_IDLE_IO2_OUT        0x08U
#define SRT_SQI_CFG_IDLE_IO2_OUT        3
#define MSK_SQI_CFG_IDLE_IO3_OE         0x10U
#define SRT_SQI_CFG_IDLE_IO3_OE         4
#define MSK_SQI_CFG_IDLE_IO3_OUT        0x20U
#define SRT_SQI_CFG_IDLE_IO3_OUT        5


typedef enum
{
	SPI_MODE0 = 0,
	SPI_MODE1 = 1,
	SPI_MODE2 = 2,
	SPI_MODE3 = 3
} SPI_MODE_T;


typedef struct
{
	unsigned int uiUnit;
	unsigned int uiChipSelect;
	unsigned long ulInitialSpeedKhz;
	unsigned int uiIdleCfg;
	unsigned int uiMode;
	unsigned char aucMmio[4];
} SPI_CONFIGURATION_T;


/* predef for the functions */
struct SPI_CFG_Ttag;

typedef int (*PFN_SPI_INIT)(struct SPI_CFG_Ttag *psCfg, const SPI_CONFIGURATION_T *ptSpiCfg, unsigned int uiChipSelect);
typedef int (*PFN_SPI_SLAVE_SELECT_T)(const struct SPI_CFG_Ttag *psCfg, int fIsSelected);
typedef int (*PFN_SEND_IDLE_T)(const struct SPI_CFG_Ttag *psCfg, size_t sizIdleChars);
typedef int (*PFN_SEND_DATA_T)(const struct SPI_CFG_Ttag *psCfg, const unsigned char *pucData, size_t sizData);
typedef int (*PFN_RECEIVE_DATA_T)(const struct SPI_CFG_Ttag *psCfg, unsigned char *pucData, size_t sizData);
typedef int (*PFN_EXCHANGE_DATA_T)(const struct SPI_CFG_Ttag *psCfg, const unsigned char *pucOutData, unsigned char *pucInData, size_t sizData);
typedef void (*PFN_SET_NEW_SPEED_T)(const struct SPI_CFG_Ttag *psCfg, unsigned long ulDeviceSpecificSpeed);
typedef unsigned char (*PFN_EXCHANGE_BYTE_T)(const struct SPI_CFG_Ttag *ptCfg, unsigned char ucByte);
typedef unsigned long (*PFN_GET_DEVICE_SPEED_REPRESENTATION_T)(unsigned int uiSpeed);
typedef void (*PFN_DEACTIVATE_T)(const struct SPI_CFG_Ttag *psCfg);


typedef struct SPI_CFG_Ttag
{
	HOSTADEF(SPI) *ptUnit;          /* Pointer to the spi unit, i.e. the register block. */
	unsigned long ulSpeed;          /* device speed in kHz */
	unsigned int uiIdleCfg;         /* the idle configuration */
	SPI_MODE_T tMode;               /* bus mode */
	unsigned int uiChipSelect;      /* chip select */

	PFN_SPI_SLAVE_SELECT_T pfnSelect;
	PFN_SEND_IDLE_T pfnSendIdle;
	PFN_SEND_DATA_T pfnSendData;
	PFN_RECEIVE_DATA_T pfnReceiveData;
	PFN_EXCHANGE_DATA_T pfnExchangeData;
	PFN_SET_NEW_SPEED_T pfnSetNewSpeed;
	PFN_EXCHANGE_BYTE_T pfnExchangeByte;
	PFN_GET_DEVICE_SPEED_REPRESENTATION_T pfnGetDeviceSpeedRepresentation;
	PFN_DEACTIVATE_T pfnDeactivate;

	unsigned char ucIdleChar;       /* the idle character */
	unsigned long ulTrcBase;        /* the base bits of the transfer control register */
	unsigned char aucMmio[4];       /* mmio pins */
} SPI_CFG_T;


#endif  /* __SPI_H__ */

