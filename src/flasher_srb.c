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

#include "cfi_flash.h"
#include "flasher_srb.h"
#include "netx_io_areas.h"
#include "parflash_common.h"
#include "uprintf.h"


/*  ///////////////////////////////////////////////////// */
/* ! Sets up the flash with the given parameters. */
/* !  \param bWidth Bus width to set (8, 16, 32Bits) */
/*  ///////////////////////////////////////////////////// */
static void setup_flash_srb(unsigned int uiWidth)
{
#if ASIC_TYP==500 || ASIC_TYP==100 || ASIC_TYP==50
        unsigned long* pulFlashCtrl = (unsigned long*)(HOSTADR(extsram0_ctrl));
        unsigned long  ulRegValue   = ((DEFAULT_PREPAUSE   << HOSTSRT(extsram0_ctrl_WSPrePauseExtMem0))  & HOSTMSK(extsram0_ctrl_WSPrePauseExtMem0))  |
                                ((DEFAULT_POSTPAUSE  << HOSTSRT(extsram0_ctrl_WSPostPauseExtMem0)) & HOSTMSK(extsram0_ctrl_WSPostPauseExtMem0)) |
                                ((DEFAULT_WAITSTATES << HOSTSRT(extsram0_ctrl_WSExtMem0))          & HOSTMSK(extsram0_ctrl_WSExtMem0));

        switch(uiWidth)
        {
        case 8:
                default:
                break;

        case 16:
                ulRegValue |= (0x01 << HOSTSRT(extsram0_ctrl_WidthExtMem0)) & HOSTMSK(extsram0_ctrl_WidthExtMem0);
                break;

        case 32:
                ulRegValue |= (0x02 << HOSTSRT(extsram0_ctrl_WidthExtMem0)) & HOSTMSK(extsram0_ctrl_WidthExtMem0);
                break;
        }

        *pulFlashCtrl = ulRegValue;
#elif ASIC_TYP==10
#endif
}


/* ------------------------------------- */

static char acCfiId[17];

NETX_CONSOLEAPP_RESULT_T srb_flash(const unsigned char *pbData, unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;
        int iCnt;


        /*  set parflash baseaddress */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram0);

        /*  try to detect flash */
        uprintf(". Detecting CFI flash at 0x%08x...\n", tFlashDevice.pbFlashBase);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_srb);
        if( iRes==0 )
        {
                /*  failed to identify flash */
                uprintf("! failed to detect CFI flash\n");
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        /*  show some info */
        for(iCnt=0; iCnt<16; ++iCnt)
        {
                acCfiId[iCnt] = tFlashDevice.szIdent[iCnt];
        }
        acCfiId[16] = 0x00;
        uprintf(". found device '");
        uprintf(acCfiId);
        uprintf("'\n");

        tResult = parflash_writeImage(&tFlashDevice, 0, pbData, ulDataByteLen);
        return tResult;
}


NETX_CONSOLEAPP_RESULT_T srb_erase(unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram0);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_srb);
        if( iRes==0 ) 
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_erase(&tFlashDevice, 0, ulDataByteLen);
        return tResult;
}


NETX_CONSOLEAPP_RESULT_T srb_read(unsigned char *pbData, unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram0);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_srb);
        if( iRes==0 ) 
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_read(&tFlashDevice, 0, pbData, ulDataByteLen);
        return tResult;
}


NETX_CONSOLEAPP_RESULT_T srb_verify(const unsigned char *pbData, unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADDR(extsram0);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_srb);
        if( iRes==0 ) 
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_verify(&tFlashDevice, 0, pbData, ulDataByteLen);
        return tResult;
}


/* ------------------------------------- */

