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
  File          : flasher_ext.c                                                 
 ----------------------------------------------------------------------------    
  Description:                                                                   
                                                                                 
      Extension Flash Functions                                                       
 ----------------------------------------------------------------------------    
  Todo:                                                                          
                                                                                 
 ----------------------------------------------------------------------------    
  Known Problems:                                                                
                                                                                 
    -                                                                            
                                                                                 
 ----------------------------------------------------------------------------    
 ***************************************************************************/    
                                                                                 
                                                                                 
/*                                                                               
************************************************************                     
*   Inclusion Area                                                               
************************************************************                     
*/                                                                               

#include "cfi_flash.h"
#include "flasher_ext.h"
#include "parflash_common.h"
#include "netx_io_areas.h"


/*****************************************************************************/
/*! setup_flash_ext                                                              
*		Setup the extension bus flash            
*   \param uiWidth   ToDo                        													*/                
/*****************************************************************************/
static void setup_flash_ext(unsigned int uiWidth)
{
	unsigned long ulIoRegMode0;
	unsigned long ulExtBusConfig;


	if( uiWidth==8 )
	{
		ulIoRegMode0   = 0xFFFFFFFF;
		ulExtBusConfig = 0x0012F781;
	}
	else
	{
		ulIoRegMode0   = 0xFFFFFFFF;
		ulExtBusConfig = 0x0012F783;
	}

	ptNetXGlobalRegBlock2Area->ulIo_reg_mode0	= ulIoRegMode0;
	ptNetXGlobalRegBlock2Area->ulIo_reg_mode1	= 0x000E7EFF;

	ptNetXGlobalRegBlock2Area->ulIf_conf1		= 0x10000000;
/*	ptNetXGlobalRegBlock2Area->ulIf_conf2		= 0x60000000; */

	ptNetXGlobalRegBlock2Area->ulIo_reg_drv_en0	= 0xFFFFFFFF;
	ptNetXGlobalRegBlock2Area->ulIo_reg_drv_en1	= 0x000E7EFF;

	ptNetXGlobalRegBlock2Area->ulExp_bus_reg	= ulExtBusConfig;
}


/*****************************************************************************/
/*! ext_flash                                                              
*		Flash file into the extension bus flash
*           
*   \param *pbData						Pointer to the data, which should bbe flashed
*		\param  ulDataByteLen 	  Lenght of the data's													 */                
/*****************************************************************************/
NETX_CONSOLEAPP_RESULT_T ext_flash(const unsigned char *pbData, unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADR(hif_ahbls6_BASE);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_ext);
        if( iRes==0 )
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_writeImage(&tFlashDevice, 0, pbData, ulDataByteLen);
        return tResult;
}

/*****************************************************************************/
/*! ext_erase                                                              
*		Erase the flash on the extension bus
*           
*		\param  ulDataByteLen 	  Lenght of the data's													 */                
/*****************************************************************************/
NETX_CONSOLEAPP_RESULT_T ext_erase(unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADR(hif_ahbls6_BASE);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_ext);
        if( iRes==0 )
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_erase(&tFlashDevice, 0, ulDataByteLen);
        return tResult;
}


/*****************************************************************************/
/*! ext_read                                                              
*		Read the flash on the extension bus
*           
*   \param *pbData						Pointer to the data, which should be read
*		\param  ulDataByteLen 	  Lenght of the data's													 */
/*****************************************************************************/
NETX_CONSOLEAPP_RESULT_T ext_read(unsigned char *pbData, unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADR(hif_ahbls6_BASE);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_ext);
        if( iRes==0 )
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_read(&tFlashDevice, 0, pbData, ulDataByteLen);
        return tResult;
}


/*****************************************************************************/
/*! ext_verify                                                              
*		Verify the flash on the extension bus
*           
*   \param *pbData						Pointer to the data, which should be read
*		\param  ulDataByteLen 	  Lenght of the data's													 */
/*****************************************************************************/
NETX_CONSOLEAPP_RESULT_T ext_verify(const unsigned char *pbData, unsigned long ulDataByteLen)
{
        FLASH_DEVICE tFlashDevice;
        NETX_CONSOLEAPP_RESULT_T tResult;
        int iRes;


        /*  try to detect flash */
        tFlashDevice.pbFlashBase = (unsigned char*)HOSTADR(hif_ahbls6_BASE);
        iRes = CFI_IdentifyFlash(&tFlashDevice, setup_flash_ext);
        if( iRes==0 )
        {
                /*  failed to identify flash */
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        tResult = parflash_verify(&tFlashDevice, 0, pbData, ulDataByteLen);
        return tResult;
}
