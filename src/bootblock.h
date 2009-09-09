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
  File          : bootblock.h
 ----------------------------------------------------------------------------
  Description:

      Bootblock definitions
 ----------------------------------------------------------------------------
  Todo:

 ----------------------------------------------------------------------------
  Known Problems:

    -

 ----------------------------------------------------------------------------
 ***************************************************************************/


/*
************************************************************
*   Defines
************************************************************
*/

#ifndef __BOOTBLOCK_H__
#define __BOOTBLOCK_H__

typedef enum
{
        BootBlockSrcType_OldStyle = 0,      /*  old style bootblock, no source identifier */
        BootBlockSrcType_SRamBus  = 1,      /*  parallel flash on sram bus                */
        BootBlockSrcType_SPI      = 2,      /*  serial flash on spi bus                   */
        BootBlockSrcType_I2C      = 3,      /*  serial eeprom on i2c bus                  */
        BootBlockSrcType_MMC      = 4,      /*  boot image on mmc/sd card                 */
        BootBlockSrcType_DPM      = 5,      /*  dpm boot mode                             */
        BootBlockSrcType_DPE      = 6,      /*  extended dpm boot mode                    */
        BootBlockSrcType_ExtBus   = 7       /*  parallel flash on extension bus           */
} tBootBlockSrcType;


#endif  /*  __BOOTBLOCK_H__ */
