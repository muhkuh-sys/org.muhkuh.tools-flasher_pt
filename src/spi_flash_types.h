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

#ifndef __SPI_FLASH_TYPES_H__
#define __SPI_FLASH_TYPES_H__


#include <stddef.h>


/*
   The T_SPIFLASH_ADR enumeration defines the addressing mode for a spi flash.

   * SPIFLASH_ADR_LINEAR is linear addressing, it's like a normal memory. It is
     used for devices with a power-of-2 pagesize.
   * SPIFLASH_ADR_PAGESIZE_BITSHIFT is used for devices with other pagesizes
     than power-of-2. The address is a combination of the page offset and the
     shifted page number. The page number is shifted by the maximum number of
     bits the page offset can occupy.
     This addressing mode is used for Atmel flashes.
*/
typedef enum SPIFLASH_ADR_Ttag
{
	SPIFLASH_ADR_LINEAR,					    /* linear addressing */
	SPIFLASH_ADR_PAGESIZE_BITSHIFT		/* bitshift derived from the pagesize */
} SPIFLASH_ADR_T;


/*
   The structure SPIFLASH_ATTRIBUTES_T defines the attributes and commands for
   an spi flash. It provides the identify sequence for the device and the
   commands to erase, read and write data.
*/

/* size of the spiFlashAttributes name field */
#define SPIFLASH_NAMESIZE 16

/* size of the erase chip command field */
#define SPIFLASH_ERASECHIPSIZE 4

/* size of the spiFlashAttributes init fields */
#define SPIFLASH_INITSIZE 4

/* size of the spiFlashAttributes id fields */
#define SPIFLASH_IDSIZE 8

typedef struct SPIFLASH_ATTRIBUTES_Ttag
{
	char		acName[SPIFLASH_NAMESIZE];			/* name of the flash, 0 terminated                              */
	unsigned long	ulSize;						/* size of the flash memory in bytes                            */
	unsigned long	ulClock;					/* maximum speed in kHz                                         */
	unsigned long	ulPageSize;					/* size of one page in bytes                                    */
	unsigned long	ulSectorPages;					/* size of one sector in pages                                  */
	SPIFLASH_ADR_T	tAdrMode;					/* addressing mode                                              */
	unsigned char	ucReadOpcode;					/* opcode for 'continuous array read' command                   */
	unsigned char	ucReadOpcodeDCBytes;				/* don't care bytes after readOpcode and address                */
	unsigned char	ucWriteEnableOpcode;				/* opcode for 'write enable' command, 0x00 means no write protect mechanism */
	unsigned char	ucErasePageOpcode;				/* opcode for 'erase page'                                      */
	unsigned char	ucEraseSectorOpcode;				/* opcode for 'erase sector'                                    */
	unsigned int	uiEraseChipCmdLen;				/* length of the 'erase chip' command, 0 means not available    */
	unsigned char	aucEraseChipCmd[SPIFLASH_ERASECHIPSIZE];	/* command to erase the complete chip                           */
	unsigned char	ucPageProgOpcode;				/* opcode for 'page program (without buildin erase)'            */
	unsigned char	ucBufferFill;					/* opcode for 'fill buffer with data'                           */
	unsigned char	ucBufferWriteOpcode;				/* opcode for 'write buffer to flash'                           */
	unsigned char	ucEraseAndPageProgOpcode;			/* opcode for 'page program with buildin erase'                 */
	unsigned char	ucReadStatusOpcode;				/* opcode for 'read status register'                            */
	unsigned char	ucStatusReadyMask;				/* the bitmask indicating device busy                           */
	unsigned char	ucStatusReadyValue;				/* eor bitmask for device busy                                  */
	unsigned int	uiInitCmd0_length;				/* length of the first init command in bytes                    */
	unsigned char	aucInitCmd0[SPIFLASH_INITSIZE];			/* first command string to init the device                      */
	unsigned int	uiInitCmd1_length;				/* length of the second init command in bytes                   */
	unsigned char	aucInitCmd1[SPIFLASH_INITSIZE];			/* second command string to init the device                     */
	unsigned int	uiIdLength;					/* length in bytes of the id_send, id_mask and id_magic fields  */
	unsigned char	aucIdSend[SPIFLASH_IDSIZE];			/* command string to request the id                             */
	unsigned char	aucIdMask[SPIFLASH_IDSIZE];			/* mask for the device id. the data received from the id_send command will be anded with this field */
	unsigned char	aucIdMagic[SPIFLASH_IDSIZE];			/* magic sequence of this device                                */
} SPIFLASH_ATTRIBUTES_T;

/* array of all known flash types */
extern const SPIFLASH_ATTRIBUTES_T atKnownSpiFlashTypes[];

/* number of elements in the array */
extern const size_t sizKnownSpiFlashTypes_len;


#endif	/* __SPI_FLASH_TYPES_H__ */

