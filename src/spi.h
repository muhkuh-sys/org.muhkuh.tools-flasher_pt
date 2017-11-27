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


#define MSK_SQI_CFG_IDLE_IO1_OE         0x01
#define SRT_SQI_CFG_IDLE_IO1_OE         0
#define MSK_SQI_CFG_IDLE_IO1_OUT        0x02
#define SRT_SQI_CFG_IDLE_IO1_OUT        1
#define MSK_SQI_CFG_IDLE_IO2_OE         0x04
#define SRT_SQI_CFG_IDLE_IO2_OE         2
#define MSK_SQI_CFG_IDLE_IO2_OUT        0x08
#define SRT_SQI_CFG_IDLE_IO2_OUT        3
#define MSK_SQI_CFG_IDLE_IO3_OE         0x10
#define SRT_SQI_CFG_IDLE_IO3_OE         4
#define MSK_SQI_CFG_IDLE_IO3_OUT        0x20
#define SRT_SQI_CFG_IDLE_IO3_OUT        5

/**
 * SPI mode.
 */
typedef enum FLASHER_SPI_MODE_ENUM
{
	FLASHER_SPI_MODE0 = 0,
	FLASHER_SPI_MODE1 = 1,
	FLASHER_SPI_MODE2 = 2,
	FLASHER_SPI_MODE3 = 3
} FLASHER_SPI_MODE_T;

/**
 * Initial configuration of the SPI interface, used as input for spi_detect.
 */
typedef struct FLASHER_SPI_CONFIGURATION_STRUCT
{
	unsigned int uiUnit;              /**< @brief SPI unit number. */
	unsigned int uiChipSelect;        /**< @brief The chip select of the SPI unit. */
	unsigned long ulInitialSpeedKhz;  /**< @brief The initial speed during identification. */
	unsigned long ulMaximumSpeedKhz;  /**< @brief The maximum speed possible on the selected SPI interface. */
	unsigned int uiIdleCfg;           /**< @brief Idle config. */
	unsigned int uiMode;              /**< @brief SPI mode (0-3). */
	unsigned char aucMmio[4];         /**< @brief MMIO config. All 0 for SPI channel 0. */
} FLASHER_SPI_CONFIGURATION_T;


/* predef for the functions */
struct FLASHER_SPI_CFG_STRUCT;

typedef int (*PFN_FLASHER_SPI_INIT)(struct FLASHER_SPI_CFG_STRUCT *psCfg, const FLASHER_SPI_CONFIGURATION_T *ptSpiCfg, unsigned int uiChipSelect);
typedef int (*PFN_FLASHER_SPI_SLAVE_SELECT_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, int fIsSelected);
typedef int (*PFN_FLASHER_SEND_IDLE_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, size_t sizIdleChars);
typedef int (*PFN_FLASHER_SEND_DATA_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, const unsigned char *pucData, size_t sizData);
typedef int (*PFN_FLASHER_RECEIVE_DATA_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, unsigned char *pucData, size_t sizData);
typedef int (*PFN_FLASHER_EXCHANGE_DATA_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, const unsigned char *pucOutData, unsigned char *pucInData, size_t sizData);
typedef void (*PFN_FLASHER_SET_NEW_SPEED_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, unsigned long ulDeviceSpecificSpeed);
typedef unsigned char (*PFN_FLASHER_EXCHANGE_BYTE_T)(const struct FLASHER_SPI_CFG_STRUCT *ptCfg, unsigned char ucByte);
typedef unsigned long (*PFN_FLASHER_GET_DEVICE_SPEED_REPRESENTATION_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg, unsigned int uiSpeed);
typedef void (*PFN_FLASHER_DEACTIVATE_T)(const struct FLASHER_SPI_CFG_STRUCT *psCfg);

/**
 * Configuration of the SPI interface. It is filled during spi_detect.
 */
typedef struct FLASHER_SPI_CFG_STRUCT
{
	void *pvUnit;                     /**< @brief Pointer to the SQI or SPI register block. */
	unsigned long ulSpeed;            /**< @brief Device speed in kHz. */
	unsigned long ulMaximumSpeedKhz;  /**< @brief The maximum allowed speed on the interface. */
	unsigned int uiIdleCfg;           /**< @brief the idle configuration. */
	FLASHER_SPI_MODE_T tMode;         /**< @brief bus mode. */
	unsigned int uiChipSelect;        /**< @brief chip select. */

	PFN_FLASHER_SPI_SLAVE_SELECT_T pfnSelect;
	PFN_FLASHER_SEND_IDLE_T pfnSendIdle;
	PFN_FLASHER_SEND_DATA_T pfnSendData;
	PFN_FLASHER_RECEIVE_DATA_T pfnReceiveData;
	PFN_FLASHER_EXCHANGE_DATA_T pfnExchangeData;
	PFN_FLASHER_SET_NEW_SPEED_T pfnSetNewSpeed;
	PFN_FLASHER_EXCHANGE_BYTE_T pfnExchangeByte;
	PFN_FLASHER_GET_DEVICE_SPEED_REPRESENTATION_T pfnGetDeviceSpeedRepresentation;
	PFN_FLASHER_DEACTIVATE_T pfnDeactivate;

	unsigned char ucIdleChar;       /**< @brief the idle character. */
	unsigned long ulTrcBase;        /**< @brief the base bits of the transfer control register. */
	unsigned char aucMmio[4];       /**< @brief MMIO pins. */
} FLASHER_SPI_CFG_T;


#endif  /* __SPI_H__ */

