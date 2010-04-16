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


#include "spi_flash_types.h"

/* uncomment the next line to disable some strange flashes with byte program only */
#define __NO_1BYTEPERPAGE_FLASHES__

const SPIFLASH_ATTRIBUTES_T atKnownSpiFlashTypes[] =
{
        /* Atmel AT26DF161A */
        {
                                 .acName = "AT26DF161A\0",                              /* name                       */
                                 .ulSize = 2097152,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0x06},                                      /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0x01, 0x00},                                /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x46, 0x01, 0x00}               /* id_magic                   */
        },

        /* Atmel AT26DF161 */
        {
                                 .acName = "AT26DF161\0",                               /* name                       */
                                 .ulSize = 2097152,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0x06},                                      /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0x01, 0x00},                                /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x46, 0x00, 0x00}               /* id_magic                   */
        },

        /* Atmel AT26DF321 */
        {
                                 .acName = "AT26DF321\0",                               /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0x06},                                      /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0x01, 0x00},                                /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x47, 0x00, 0x00}               /* id_magic                   */
        },

        /* Atmel AT45DB081D */
        {
                                 .acName = "AT45DB081D\0",                              /* name                       */
                                 .ulSize = 1081344,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 264,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 4,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7, 0x94, 0x80, 0x9a},                    /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xa4,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x25, 0x00, 0x00}               /* id_magic                   */
        },

        /* Atmel AT45DB161D */
        {
                                 .acName = "AT45DB161D\0",                              /* name                       */
                                 .ulSize = 2162688,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 528,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 4,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7, 0x94, 0x80, 0x9a},                    /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xac,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x26, 0x00, 0x00}               /* id_magic                   */
        },

        /* Atmel AT45DB321C configuration */
        /* NOTE: this must be before the ATDB321B typ, or this will never match */
        {
                                 .acName = "AT45DB321C\0",                              /* name                       */
                                 .ulSize = 4325376,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 528,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xb4,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x27, 0x00, 0x00}               /* id_magic                   */
        },

        /* Atmel AT45DB321D */
        /* NOTE: this must be before the ATDB321B typ, or this will never match */
        {
                                 .acName = "AT45DB321D\0",                              /* name                       */
                                 .ulSize = 4325376,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 528,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 4,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7, 0x94, 0x80, 0x9a},                    /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xb4,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x27, 0x01, 0x00}               /* id_magic                   */
        },

        /* Atmel AT45DB642D */
        {
                                 .acName = "AT45DB642D\0",                              /* name                       */
                                 .ulSize = 8650752,                                     /* size                       */
                                .ulClock = 50000,                                       /* minClock                   */
                             .ulPageSize = 1056,                                        /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 4,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7, 0x94, 0x80, 0x9a},                    /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xbc,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x28, 0x00, 0x00}               /* id_magic                   */
        },

        /* NexFlash NX25P10 */
        {
                                 .acName = "NX25P10\0",                                 /* name                       */
                                 .ulSize = 131072,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xef, 0x10}         /* id_magic                   */
        },

        /* NexFlash NX25P20 */
        {
                                 .acName = "NX25P20\0",                                 /* name                       */
                                 .ulSize = 262144,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xef, 0x11}         /* id_magic                   */
        },

        /* NexFlash NX25P40 */
        {
                                 .acName = "NX25P40\0",                                 /* name                       */
                                 .ulSize = 524288,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xef, 0x12}         /* id_magic                   */
        },
#ifndef __NO_1BYTEPERPAGE_FLASHES__
        /* SST SST25LF20A or SST25VF020 */
        {
                                 .acName = "SST25xF20\0",                               /* name                       */
                                 .ulSize = 262144,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 1,                                           /* pageSize                   */
                          .ulSectorPages = 4096,                                        /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = { 0x50 },                                    /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = { 0x01, 0x00 },                              /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xbf, 0x43}         /* id_magic                   */
        },

        /* SST SST25LF40A or SST25VF040 */
        {
                                 .acName = "SST25xF40\0",                               /* name                       */
                                 .ulSize = 524288,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 1,                                           /* pageSize                   */
                          .ulSectorPages = 4096,                                        /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = { 0x50 },                                    /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = { 0x01, 0x00 },                              /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xbf, 0x44}         /* id_magic                   */
        },

        /* SST SST25LF80A */
        {
                                 .acName = "SST25LF80A\0",                              /* name                       */
                                 .ulSize = 1048576,                                     /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 1,                                           /* pageSize                   */
                          .ulSectorPages = 4096,                                        /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = { 0x50 },                                    /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = { 0x01, 0x00 },                              /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xbf, 0x80}         /* id_magic                   */
        },

        /* SST SST25VF010 or SST25VF010A */
        {
                                 .acName = "SST25VF010\0",                              /* name                       */
                                 .ulSize = 131072,                                      /* size                       */
                                .ulClock = 200000,                                      /* minClock                   */
                             .ulPageSize = 1,                                           /* pageSize                   */
                          .ulSectorPages = 4096,                                        /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = { 0x50 },                                    /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = { 0x01, 0x00 },                              /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xbf, 0x49}         /* id_magic                   */
        },

        /* SST SST25VF512 or SST25VF512A */
        {
                                 .acName = "SST25VF512\0",                              /* name                       */
                                 .ulSize = 65536,                                       /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 1,                                           /* pageSize                   */
                          .ulSectorPages = 4096,                                        /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x60},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = { 0x50 },                                    /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = { 0x01, 0x00 },                              /* initCmd1                   */
                             .uiIdLength = 6,                                           /* id_length                  */
                              .aucIdSend = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00},        /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff},        /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0xbf, 0x48}         /* id_magic                   */
        },
#endif
        /* PMC PM25LV512 */
        {
                                 .acName = "PM25LV512\0",                               /* name                       */
                                 .ulSize = 65536,                                       /* size                       */
                                .ulClock = 25000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd7,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 7,                                           /* id_length                  */
                              .aucIdSend = {0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff},  /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0x9d, 0x7b, 0x7f}   /* id_magic                   */
        },

        /* PMC PM25LV010 */
        {
                                 .acName = "PM25LV010\0",                               /* name                       */
                                 .ulSize = 131072,                                      /* size                       */
                                .ulClock = 25000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd7,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 7,                                           /* id_length                  */
                              .aucIdSend = {0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff},  /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0x9d, 0x7c, 0x7f}   /* id_magic                   */
        },

        /* Saifun SA25F005 */
        {
                                 .acName = "SA25F005\0",                                /* name                       */
                                 .ulSize = 65536,                                       /* size                       */
                                .ulClock = 25000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 128,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0xab, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0x05}               /* id_magic                   */
        },

        /* Saifun SA25F010 */
        /* NOTE: the obsolete ST M25P10 will also match, it is not recommended (has no page erase) */
        {
                                 .acName = "SA25F010\0",                                /* name                       */
                                 .ulSize = 131072,                                      /* size                       */
                                .ulClock = 25000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 128,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0xab, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0x10}               /* id_magic                   */
        },

        /* Saifun SA25F020 */
        /* NOTE: the obsolete ST M25P20 will also match, it is not recommended (has no page erase) */
        {
                                 .acName = "SA25F020\0",                                /* name                       */
                                 .ulSize = 262144,                                      /* size                       */
                                .ulClock = 25000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 128,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0xab, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0x11}               /* id_magic                   */
        },

	/* M25P40 */
	/* NOTE: this is compatible to the Saifun SA25F040. The only difference is the clock speed. */
	/* The SA25F040 supports up to 50MHz, but the M25P40 'only' runs at 25MHz. */
        {
                                 .acName = "M25P40\0",                                  /* name                       */
                                 .ulSize = 524288,                                      /* size                       */
                                .ulClock = 25000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 5,                                           /* id_length                  */
                              .aucIdSend = {0xab, 0x00, 0x00, 0x00, 0x00},              /* id_send                    */
                              .aucIdMask = {0x00, 0x00, 0x00, 0x00, 0xff},              /* id_mask                    */
                             .aucIdMagic = {0x00, 0x00, 0x00, 0x00, 0x12}               /* id_magic                   */
        },

        /* ST M45PE20  */ 
        {
                                 .acName = "M45PE20\0",                                 /* name                       */
                                 .ulSize = 262144,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0xdb,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x0a,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x20, 0x40, 0x12}                     /* id_magic                   */
        },

        /* ST M45PE40 */
        {
                                 .acName = "M45PE40\0",                                 /* name                       */
                                 .ulSize = 524288,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0xdb,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x0a,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x20, 0x40, 0x13}                     /* id_magic                   */
        },

        /* ST M45PE80 */
        {
                                 .acName = "M45PE80\0",                                 /* name                       */
                                 .ulSize = 1048576,                                     /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0xdb,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x0a,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x20, 0x40, 0x14}                     /* id_magic                   */
        },

        /* ST M25P32 */
        {
                                 .acName = "M25P32\0",                                  /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x20, 0x20, 0x16}                     /* id_magic                   */
        },

        /* ST M25P64 */
        {
                                 .acName = "M25P64\0",                                  /* name                       */
                                 .ulSize = 8388608,                                     /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x20, 0x20, 0x17}                     /* id_magic                   */
        },

        /* ST M25PE80 */
        {
                                 .acName = "M25PE80\0",                                 /* name                       */
                                 .ulSize = 1048576,                                     /* size                       */
                                .ulClock = 50000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0xdb,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x20, 0x80, 0x14}                     /* id_magic                   */
        },

        /* Spansion S25FL016A */
        {
                                 .acName = "S25FL016A\0",                               /* name                       */
                                 .ulSize = 2097152,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x01, 0x02, 0x14}                     /* id_magic                   */
        },

        /* Spansion S25FL032A */
        {
                                 .acName = "S25FL032A\0",                               /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 33000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x01, 0x02, 0x15}                     /* id_magic                   */
        },

        /* Winbond W25Q80 */
        {
                                 .acName = "W25Q80\0",                                  /* name                       */
                                 .ulSize = 1048576,                                     /* size                       */
                                .ulClock = 80000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xef, 0x40, 0x14}                     /* id_magic                   */
        },

        /* Winbond W25Q16 */
        {
                                 .acName = "W25Q16\0",                                  /* name                       */
                                 .ulSize = 2097152,                                     /* size                       */
                                .ulClock = 80000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xef, 0x40, 0x15}                     /* id_magic                   */
        },

        /* Winbond W25Q32 */
        {
                                 .acName = "W25Q32\0",                                  /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 80000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xef, 0x40, 0x16}                     /* id_magic                   */
        },

        /* EON EN25P32 */
        {
                                 .acName = "EN25P32\0",                                 /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 66000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 256,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0xd8,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1c, 0x20, 0x16}                     /* id_magic                   */
        },

        /* Macronix MX25L1605D */
        {
                                 .acName = "MX25L1605D\0",                              /* name                       */
                                 .ulSize = 2097152,                                     /* size                       */
                                .ulClock = 66000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xc2, 0x20, 0x15}                     /* id_magic                   */
        },

        /* Macronix MX25L3205D */
        {
                                 .acName = "MX25L3205D\0",                              /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 66000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xc2, 0x20, 0x16}                     /* id_magic                   */
        },

        /* Macronix MX25L6405D */
        {
                                 .acName = "MX25L6405D\0",                              /* name                       */
                                 .ulSize = 8388608,                                     /* size                       */
                                .ulClock = 66000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xc2, 0x20, 0x17}                     /* id_magic                   */
        },

        /* Winbond W25X32 */
        {
                                 .acName = "W25X32\0",                                  /* name                       */
                                 .ulSize = 4194304,                                     /* size                       */
                                .ulClock = 75000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 16,                                          /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x20,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0xc7},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 4,                                           /* id_length                  */
                              .aucIdSend = {0x9f, 0x00, 0x00, 0x00},                    /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff, 0xff},                    /* id_mask                    */
                             .aucIdMagic = {0x00, 0xef, 0x30, 0x16}                     /* id_magic                   */
        },

        /* Atmel AT25F1024A */
        {
                                 .acName = "AT25F1024A\0",                              /* name                       */
                                 .ulSize = 131072,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 256,                                         /* pageSize                   */
                          .ulSectorPages = 128,                                         /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_LINEAR,                         /* address mode               */
                           .ucReadOpcode = 0x03,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 0,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x06,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x00,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x52,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 1,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0x62},                                      /* erase chip command         */
                       .ucPageProgOpcode = 0x02,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x00,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x00,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x00,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0x05,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0x01,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x00,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 1,                                           /* initCmd0_length            */
                            .aucInitCmd0 = { 0x06 },                                    /* initCmd0                   */
                      .uiInitCmd1_length = 2,                                           /* initCmd1_length            */
                            .aucInitCmd1 = { 0x01, 0x02 },                              /* initCmd1                   */
                             .uiIdLength = 3,                                           /* id_length                  */
                              .aucIdSend = {0x15, 0x00, 0x00},                          /* id_send                    */
                              .aucIdMask = {0x00, 0xff, 0xff},                          /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1f, 0x60}                           /* id_magic                   */
        },

        /* Atmel AT45DB011B */
        {
                                 .acName = "AT45DB011B\0",                              /* name                       */
                                 .ulSize = 135168,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 264,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x8c,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 2,                                           /* id_length                  */
                              .aucIdSend = {0xd7, 0x00},                                /* id_send                    */
                              .aucIdMask = {0x00, 0x3c},                                /* id_mask                    */
                             .aucIdMagic = {0x00, 0x0c}                                 /* id_magic                   */
        },

        /* Atmel AT45DB021B */
        {
                                 .acName = "AT45DB021B\0",                              /* name                       */
                                 .ulSize = 270336,                                      /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 264,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x94,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 2,                                           /* id_length                  */
                              .aucIdSend = {0xd7, 0x00},                                /* id_send                    */
                              .aucIdMask = {0x00, 0x3c},                                /* id_mask                    */
                             .aucIdMagic = {0x00, 0x14}                                 /* id_magic                   */
        },

        /* Atmel AT45DB041B */
        {
                                 .acName = "AT45DB041B\0",                              /* name                       */
                                 .ulSize = 540672,                                      /* size                       */
                                .ulClock = 15000,                                       /* minClock                   */
                             .ulPageSize = 264,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0x9c,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 2,                                           /* id_length                  */
                              .aucIdSend = {0xd7, 0x00},                                /* id_send                    */
                              .aucIdMask = {0x00, 0x3c},                                /* id_mask                    */
                             .aucIdMagic = {0x00, 0x1c}                                 /* id_magic                   */
        },

        /* Atmel AT45DB081B */
        {
                                 .acName = "AT45DB081B\0",                              /* name                       */
                                 .ulSize = 1081344,                                     /* size                       */
                                .ulClock = 15000,                                       /* minClock                   */
                             .ulPageSize = 264,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xa4,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 2,                                           /* id_length                  */
                              .aucIdSend = {0xd7, 0x00},                                /* id_send                    */
                              .aucIdMask = {0x00, 0x3c},                                /* id_mask                    */
                             .aucIdMagic = {0x00, 0x24}                                 /* id_magic                   */
        },

        /* Atmel AT45DB161B */
        {
                                 .acName = "AT45DB161B\0",                              /* name                       */
                                 .ulSize = 2162688,                                     /* size                       */
                                .ulClock = 15000,                                       /* minClock                   */
                             .ulPageSize = 528,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xac,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 2,                                           /* id_length                  */
                              .aucIdSend = {0xd7, 0x00},                                /* id_send                    */
                              .aucIdMask = {0x00, 0x3c},                                /* id_mask                    */
                             .aucIdMagic = {0x00, 0x2c}                                 /* id_magic                   */
        },

        /* Atmel AT45DB321B */
        /* NOTE: this must be after the AT45DB321C and D typ, or both will match here */
        {
                                 .acName = "AT45DB321B\0",                              /* name                       */
                                 .ulSize = 4325376,                                     /* size                       */
                                .ulClock = 20000,                                       /* minClock                   */
                             .ulPageSize = 528,                                         /* pageSize                   */
                          .ulSectorPages = 8,                                           /* sectorSize                 */
                               .tAdrMode = SPIFLASH_ADR_PAGESIZE_BITSHIFT,              /* address mode               */
                           .ucReadOpcode = 0xe8,                                        /* readOpcode                 */
                    .ucReadOpcodeDCBytes = 4,                                           /* readOpcodeDCBytes          */
                    .ucWriteEnableOpcode = 0x00,                                        /* writeEnableOpcode          */
                      .ucErasePageOpcode = 0x81,                                        /* erase page                 */
                    .ucEraseSectorOpcode = 0x50,                                        /* eraseSectorOpcode          */
                      .uiEraseChipCmdLen = 0,                                           /* erase chip command length  */
                        .aucEraseChipCmd = {0},                                         /* erase chip command         */
                       .ucPageProgOpcode = 0x00,                                        /* pageProgOpcode             */
                           .ucBufferFill = 0x84,                                        /* buffer fill opcode         */
                    .ucBufferWriteOpcode = 0x88,                                        /* buffer write opcode        */
               .ucEraseAndPageProgOpcode = 0x82,                                        /* eraseAndPageProgOpcode     */
                     .ucReadStatusOpcode = 0xd7,                                        /* readStatusOpcode           */
                      .ucStatusReadyMask = 0xbc,                                        /* statusReadyMask            */
                     .ucStatusReadyValue = 0xb4,                                        /* statusReadyValue           */
                      .uiInitCmd0_length = 0,                                           /* initCmd0_length            */
                            .aucInitCmd0 = {0},                                         /* initCmd0                   */
                      .uiInitCmd1_length = 0,                                           /* initCmd1_length            */
                            .aucInitCmd1 = {0},                                         /* initCmd1                   */
                             .uiIdLength = 3,                                           /* id_length                  */
                              .aucIdSend = {0xd7, 0x00},                                /* id_send                    */
                              .aucIdMask = {0x00, 0x3c},                                /* id_mask                    */
                             .aucIdMagic = {0x00, 0x34}                                 /* id_magic                   */
        },
};


const size_t sizKnownSpiFlashTypes_len = sizeof(atKnownSpiFlashTypes)/sizeof(SPIFLASH_ATTRIBUTES_T);

