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

#ifndef __FLASHER_HEADER_H__
#define __FLASHER_HEADER_H__

/*-----------------------------------*/

#define FLASHER_MAGIC0  0x6e
#define FLASHER_MAGIC1  0x78
#define FLASHER_MAGIC2  0x66
#define FLASHER_MAGIC3  0x6c

/* chiptyp defines */
typedef enum
{
	FLASHER_CHIPTYP0_NETX500           = 0x00000001,
	FLASHER_CHIPTYP0_NETX100           = 0x00000002,
	FLASHER_CHIPTYP0_NETX50            = 0x00000004,
	FLASHER_CHIPTYP0_NETX5             = 0x00000008,
	FLASHER_CHIPTYP0_NETX10            = 0x00000010,
	FLASHER_CHIPTYP0_NETX56            = 0x00000020,
	FLASHER_CHIPTYP0_NETX4000_RELAXED  = 0x00000040,
	FLASHER_CHIPTYP0_NETX4000_FULL     = 0x00000080,
	FLASHER_CHIPTYP0_NETX90_MPW        = 0x00000100
} eFLASHER_CHIPTYP0;


/* interface defines */
typedef enum
{
	FLASHER_IF0_NETX500_PFSRAM           = 0x00000001,
	FLASHER_IF0_NETX500_PFEXT            = 0x00000002,
	FLASHER_IF0_NETX500_SPI              = 0x00000004,
	FLASHER_IF0_NETX500_I2C              = 0x00000008,
	FLASHER_IF0_NETX500_MMC              = 0x00000010,
	FLASHER_IF0_NETX50_PFSRAM            = 0x00000020,
	FLASHER_IF0_NETX50_PFEXT             = 0x00000040,
	FLASHER_IF0_NETX50_SPI               = 0x00000080,
	FLASHER_IF0_NETX50_I2C               = 0x00000100,
	FLASHER_IF0_NETX50_MMC               = 0x00000200,
	FLASHER_IF0_NETX10_PFSRAM            = 0x00000400,
	FLASHER_IF0_NETX10_SPI               = 0x00000800,
	FLASHER_IF0_NETX10_I2C               = 0x00001000,
	FLASHER_IF0_NETX10_MMC               = 0x00002000,
	FLASHER_IF0_NETX56_PFSRAM            = 0x00004000,
	FLASHER_IF0_NETX56_SPI               = 0x00008000,
	FLASHER_IF0_NETX56_I2C               = 0x00010000,
	FLASHER_IF0_NETX56_MMC               = 0x00020000,
	FLASHER_IF0_NETX4000_RELAXED_PFSRAM  = 0x00040000,
	FLASHER_IF0_NETX4000_RELAXED_SPI     = 0x00080000,
	FLASHER_IF0_NETX4000_RELAXED_I2C     = 0x00100000,
	FLASHER_IF0_NETX4000_RELAXED_MMC     = 0x00200000,
	FLASHER_IF0_NETX4000_RELAXED_NAND    = 0x00400000,
	FLASHER_IF0_NETX4000_FULL_PFSRAM     = 0x00800000,
	FLASHER_IF0_NETX4000_FULL_SPI        = 0x01000000,
	FLASHER_IF0_NETX4000_FULL_I2C        = 0x02000000,
	FLASHER_IF0_NETX4000_FULL_MMC        = 0x04000000,
	FLASHER_IF0_NETX4000_FULL_NAND       = 0x08000000,
	FLASHER_IF0_NETX90_MPW_SPI           = 0x10000000
} eFLASHER_IF0;

/*-----------------------------------*/

typedef unsigned long (*PFN_START)(unsigned long ulParameter);

typedef struct FLASHER_VERSION_STRUCT
{
	const char    abMagic[4];

	unsigned long ulVersionMajor;
	unsigned long ulVersionMinor;
	unsigned long ulVersionMicro;
	const char    acVersionVcs[16];

	unsigned long *pulLoadAddress;
	PFN_START pfnExecutionAddress;

	unsigned char *pucBuffer_Parameter;
	unsigned char *pucBuffer_DeviceDescription;
	unsigned char *pucBuffer_Data;
	unsigned char *pucBuffer_End;

	unsigned long aulChiptyp[2];
	unsigned long aulIf[4];
} FLASHER_VERSION_T;

extern const FLASHER_VERSION_T flasher_version __attribute__ ((section (".version_info")));


/*-----------------------------------*/

extern unsigned long __LOAD_ADDRESS__[1];
unsigned long start(unsigned long ulParameter);
extern unsigned char __BUFFER_START__[1];
extern unsigned char __BUFFER_END__[1];

/*-----------------------------------*/

#endif  /* __FLASHER_HEADER_H__ */

