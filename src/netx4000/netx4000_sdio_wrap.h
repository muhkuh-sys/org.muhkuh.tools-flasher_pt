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

#ifndef __NETX4000_SDIO_WRAP__
#define __NETX4000_SDIO_WRAP__

#include "flasher_interface.h"
#if CFG_INCLUDE_SHA1!=0
#       include "sha1.h"
#endif
 

NETX_CONSOLEAPP_RESULT_T sdio_detect_wrap(SDIO_HANDLE_T *ptSdioHandle);
NETX_CONSOLEAPP_RESULT_T sdio_read(CMD_PARAMETER_READ_T *ptParams);
NETX_CONSOLEAPP_RESULT_T sdio_write(CMD_PARAMETER_FLASH_T *ptParams);
NETX_CONSOLEAPP_RESULT_T sdio_verify(CMD_PARAMETER_VERIFY_T *ptParams, unsigned long *pulVerifyResult);
NETX_CONSOLEAPP_RESULT_T sdio_erase(CMD_PARAMETER_ERASE_T *ptParams);
NETX_CONSOLEAPP_RESULT_T sdio_is_erased(CMD_PARAMETER_ISERASED_T *ptParams, unsigned long *pulIsErasedResult);

NETX_CONSOLEAPP_RESULT_T sdio_get_erase_area(CMD_PARAMETER_GETERASEAREA_T *ptParameter);
#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T sdio_sha1(CMD_PARAMETER_CHECKSUM_T *ptParams, SHA_CTX *ptSha1Context);
#endif
#endif /* __NETX4000_SDIO_WRAP__ */

