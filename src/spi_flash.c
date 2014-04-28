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

#include <string.h>

#include "exodecr.h"
#include "flasher_header.h"
#include "uprintf.h"
#include "progress_bar.h"

#include "spi_flash.h"
#include "sfdp.h"


#if ASIC_TYP==10 || ASIC_TYP==56
/* netX10 and netX56 have a SQI and a SPI unit. */
#	include "drv_sqi.h"
#	include "drv_spi_hsoc_v2.h"
#elif ASIC_TYP==50
#	include "drv_spi_hsoc_v2.h"
#elif ASIC_TYP==100 || ASIC_TYP==500
#	include "drv_spi_hsoc_v1.h"
#endif


#if CFG_DEBUGMSG!=0

	/* show all messages by default */
	static unsigned long s_ulCurSettings = 0xffffffff;

	#define DEBUGZONE(n)  (s_ulCurSettings&(0x00000001<<(n)))

	/* NOTE: These defines must match the ZONE_* defines. */
	#define DBG_ZONE_ERROR      0
	#define DBG_ZONE_WARNING    1
	#define DBG_ZONE_FUNCTION   2
	#define DBG_ZONE_INIT       3
	#define DBG_ZONE_VERBOSE    7

	#define ZONE_ERROR          DEBUGZONE(DBG_ZONE_ERROR)
	#define ZONE_WARNING        DEBUGZONE(DBG_ZONE_WARNING)
	#define ZONE_FUNCTION       DEBUGZONE(DBG_ZONE_FUNCTION)
	#define ZONE_INIT           DEBUGZONE(DBG_ZONE_INIT)
	#define ZONE_VERBOSE        DEBUGZONE(DBG_ZONE_VERBOSE)

	#define DEBUGMSG(cond,printf_exp) ((void)((cond)?(uprintf printf_exp),1:0))
#else  /* CFG_DEBUGMSG!=0 */
	#define DEBUGMSG(cond,printf_exp) ((void)0)
#endif /* CFG_DEBUGMSG!=0 */

// #define DBG_CALL_FAILED_VAL(n, v)  uprintf("! ERROR: %s: %s failed with %d\n", __func__, (n), (v));
// #define DBG_ERROR(str)             uprintf("! ERROR: %s: %s\n", __func__, (str));
// #define DBG_ERROR_VAL(str, v)      uprintf("! ERROR: %s: " str "\n", __func__, (v));

#define DBG_CALL_FAILED_VAL(n, v)  DEBUGMSG(ZONE_ERROR, ("! ERROR: %s: %s failed with %d\n", __func__, (n), (v)));
#define DBG_ERROR(str)             DEBUGMSG(ZONE_ERROR, ("! ERROR: %s: %s\n", __func__, (str)));
//#define DBG_ERROR_VAL(str, v)      DEBUGMSG(ZONE_ERROR, ("! ERROR: %s: " str "\n", __func__, (v)));

#define DBG_ERROR_VAL(format, ...) DEBUGMSG(ZONE_ERROR, ("! ERROR: %s: " format "\n", __func__, __VA_ARGS__));



#define DBG_ENTER                  DEBUGMSG(ZONE_FUNCTION, ("+%s\n", __func__));
#define DBG_LEAVE                  DEBUGMSG(ZONE_FUNCTION, ("-%s\n", __func__));
#define DBG_LEAVE_RET              DEBUGMSG(ZONE_FUNCTION, ("-%s return value = 0x%08x\n", __func__, iResult));
#define DBG_ENTER_VAL(str, v)      DEBUGMSG(ZONE_FUNCTION, ("+%s " str "\n", __func__, (v)));
#define DBG_LEAVE_VAL(str, v)      DEBUGMSG(ZONE_FUNCTION, ("-%s " str "\n", __func__, (v)));


/*! getMaskLength
    Calculate the minimum mask for an input parameter and return the
    number of bits used for this mask. The mask always starts at bit 0.
    \param ulVal   Value to get the masklength from

    \return        Number of bits used for the mask
*/
static unsigned int getMaskLength(unsigned long ulVal)
{
	unsigned long ulMask   = 0;
	unsigned int  uiBitCnt = 0;


	//DEBUGMSG(ZONE_FUNCTION, ("+getMaskLength(): ulVal=0x%08x\n", ulVal));
	DBG_ENTER_VAL("ulVal=0x%08x", ulVal);

	/*  generate mask and count used bits */
	while(ulMask < ulVal)
	{
		/* shift in one more '1' to the mask value */
		ulMask <<= 1;
		ulMask |= 1;
		/* count the new digit */
		++uiBitCnt;
	}

	//DEBUGMSG(ZONE_FUNCTION, ("-getMaskLength(): uiBitCnt=0x%08x\n", uiBitCnt));
	DBG_LEAVE_VAL("uiBitCnt=0x%08x", uiBitCnt);
	return uiBitCnt;
}


/*! getDeviceAddress
    Convert the linear input address to the device's addressing mode

    \param ptFls            pointer to the instance of the spi flash
    \param ulLinearAddress  linear address

    \return                 device specific address
*/
static unsigned long getDeviceAddress(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress)
{
	unsigned long ulDeviceAddress = 0;
	unsigned long ulPageNr;
	unsigned long ulByteOffset;


	DEBUGMSG(ZONE_FUNCTION, ("+getDeviceAddress(): ptFlash=0x%08x, ulLinearAddress=0x%08x\n", ptFlash, ulLinearAddress));

	/* is the pagesize a multiple of 256? -> no page-byte split is needed */
	switch(ptFlash->tAttributes.tAdrMode)
	{
	case SPIFLASH_ADR_LINEAR:
		/* linear addressing */
		ulDeviceAddress = ulLinearAddress;
		break;

	case SPIFLASH_ADR_PAGESIZE_BITSHIFT:
		/* bitshift derived from the pagesize */

		/*  get the page number of the address */
		ulPageNr = ulLinearAddress / ptFlash->tAttributes.ulPageSize;

		/*  get the byte ulOffsModuloet of the address */
		ulByteOffset = ulLinearAddress % ptFlash->tAttributes.ulPageSize;

		/*  shift the sector number to the right position */
		ulDeviceAddress = (ulPageNr << ptFlash->uiPageAdrShift) | ulByteOffset;
		break;

	default:
		/* unknown addressing mode! */
		//uprintf("ERROR: getDeviceAddress: unknown addressing mode: 0x%08x. This check was already passed in Drv_SpiInitializeFlash, the memory seems to be corrupted!\n", ptFlash->tAttributes.tAdrMode);
		DBG_ERROR_VAL("unknown addressing mode: 0x%08x. This check was already passed in Drv_SpiInitializeFlash, the memory seems to be corrupted!", ptFlash->tAttributes.tAdrMode)
		/* TODO: throw some fatal error here */
		break;
	}

	//DEBUGMSG(ZONE_FUNCTION, ("-getDeviceAddress(): ulDeviceAddress=0x%08x\n", ulDeviceAddress));
	DBG_LEAVE_VAL("ulDeviceAddress=0x%08x", ulDeviceAddress)
	return ulDeviceAddress;
}


/*! read_status
    read the status register

    \param   ptFls              Pointer to FLASH Control Block
    \param   ulLinearAddress    linear address

    \return  RX_OK              status successfully returned
*/
static int read_status(const SPI_FLASH_T *ptFlash, unsigned char *pucStatus)
{
	int iResult;
	const SPI_CFG_T *ptSpiDev;


	DEBUGMSG(ZONE_FUNCTION, ("+read_status(): ptFlash=0x%08x, pucStatus=0x%08x\n", ptFlash, pucStatus));

	/* get spi device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* select slave */
	ptSpiDev->pfnSelect(ptSpiDev, 1);

	/* send command */
	iResult = ptSpiDev->pfnSendData(ptSpiDev, &(ptFlash->tAttributes.ucReadStatusOpcode), 1);
	if( iResult!=0 )
	{
		//uprintf("ERROR: read_status: HalSPI_ExchangeByte failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("pfnSendData", iResult)
	}
	else
	{
		/*  receive status byte */
		iResult = ptSpiDev->pfnReceiveData(ptSpiDev, pucStatus, 1);
		if( iResult!=0 )
		{
			//uprintf("ERROR: read_status: Drv_SpiReceive failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("pfnReceiveData", iResult)
		}
	}

	/*  deselect slave */
	ptSpiDev->pfnSelect(ptSpiDev, 0);
	if( iResult==0 )
	{
		/* send 1 idlebyte */
		iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
		if( iResult!=0 )
		{
			//uprintf("ERROR: read_status: SendIdles failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("pfnSendIdle", iResult)
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-read_status(): iResult=%d, *pucStatus=0x%02x\n", iResult, *pucStatus));
	return iResult;
}


#if CFG_DEBUGMSG!=0
static int print_status(const SPI_FLASH_T *ptFlash)
{
	unsigned char ucStatus = 0;
	int iResult;

	DEBUGMSG(ZONE_FUNCTION, ("+print_status(const ptFlash=0x%08x\n", ptFlash));

	/*  read status and extract busy bit */
	iResult = read_status(ptFlash, &ucStatus);
	if( iResult==0 )
	{
		uprintf(". Status: 0x%02x\n", ucStatus);
	}

	DEBUGMSG(ZONE_FUNCTION, ("-print_status(): iResult=%d, ucStatus=0x%02x\n", iResult, ucStatus));
	return iResult;
}
#endif


/* NOTE: the external is defined in the imported object. */
extern const char _binary_spi_flash_types_exo_end[];

/*! detect_flash
*   Convert the linear input address to the device's addressing mode
*
*   \param   ptFls              pointer to the instance of the spi flash
*   \param   ulLinearAddress    linear address                  
*                                                                              
*   \return  RX_OK              status successfully returned
*/
static int detect_flash(SPI_FLASH_T *ptFlash, const SPIFLASH_ATTRIBUTES_T **pptFlashAttr)
{
	int           iResult = 1;
	int           fFoundId;
	unsigned int  uiCnt;
	unsigned char aucIdResp[SPIFLASH_ID_SIZE];
	const SPIFLASH_ATTRIBUTES_T *ptSc;
	const SPIFLASH_ATTRIBUTES_T *ptSe;
	const SPIFLASH_ATTRIBUTES_T *ptSr;
	SPI_CFG_T *ptSpiDev;
	union
	{
		char *pc;
		const SPIFLASH_ATTRIBUTES_T *pt;
	} uSpiTypes;
	const unsigned int uiUseDetectList = 1;
	const unsigned int uiUseSfdp = 1;


	DEBUGMSG(ZONE_FUNCTION, ("+detect_flash(): ptFlash=0x%08x\n", ptFlash));

	/* No parameters yet. */
	ptSr = NULL;

	iResult = 0;

	if( uiUseDetectList!=0 )
	{
		/* Depack the list of known flash devices. */
		uSpiTypes.pc = exo_decrunch(_binary_spi_flash_types_exo_end, (char*)(flasher_version.pucBuffer_End));

		/* get spi device */
		ptSpiDev = &ptFlash->tSpiDev;

		/* loop over all entries in the list of known flash types */
		ptSc = uSpiTypes.pt;
		ptSe = ptSc + NUMBER_OF_SPIFLASH_ATTRIBUTES;

		/* init found flag in case of an empty list */
		fFoundId = (1==0);
		while(ptSc < ptSe)
		{
			/* deselect all chips */
			ptSpiDev->pfnSelect(ptSpiDev, 0);

			/* send 8 idle bytes to clear the bus */
			iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 8);
			if( iResult!=0 )
			{
				//uprintf("ERROR: detect_flash: HalSPI_SendIdles failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("pfnSendIdle", iResult)
					break;
			}

			/* select the slave */
			ptSpiDev->pfnSelect(ptSpiDev, 1);

			/* send id magic and receive response */
			DEBUGMSG(ZONE_VERBOSE, ("detect_flash: probe for %s\n", ptSc->acName));

			iResult = ptSpiDev->pfnExchangeData(ptSpiDev, ptSc->aucIdSend, aucIdResp, ptSc->ucIdLength);

			/* deselect slave */
			ptSpiDev->pfnSelect(ptSpiDev, 0);

			/* did the send and receive operation fail? */
			if( iResult!=0 )
			{
				//uprintf("ERROR: detect_flash: HalSPI_BlockIo failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("pfnExchangeData", iResult)
					break;
			}

#if CFG_DEBUGMSG!=0
			if( ZONE_VERBOSE )
			{
				uprintf("Send     : ");
				uiCnt = 0;
				while( uiCnt<ptSc->ucIdLength )
				{
					uprintf("%02x ", ptSc->aucIdSend[uiCnt]);
					++uiCnt;
				}
				uprintf("\nReceived : ");
				uiCnt = 0;
				while( uiCnt<ptSc->ucIdLength )
				{
					uprintf("%02x ", aucIdResp[uiCnt]);
					++uiCnt;
				}
				uprintf("\nMasked   : ");
				uiCnt = 0;
				while( uiCnt<ptSc->ucIdLength )
				{
					uprintf("%02x ", aucIdResp[uiCnt]&ptSc->aucIdMask[uiCnt]);
					++uiCnt;
				}
				uprintf("\nMagic    : ");
				uiCnt = 0;
				while( uiCnt<ptSc->ucIdLength )
				{
					uprintf("%02x ", ptSc->aucIdMagic[uiCnt]);
					++uiCnt;
				}
				uprintf("\n");
			}
#endif

			/* assume success */
			fFoundId = (1==1);

			/* do a bitwise 'and' of the input data and the mask IdMask and compare */
			/* the result to the magic sequence IdMagic */
			uiCnt = ptSc->ucIdLength;
			while(uiCnt > 0)
			{
				--uiCnt;
				fFoundId &= ((aucIdResp[uiCnt]&ptSc->aucIdMask[uiCnt]) == ptSc->aucIdMagic[uiCnt]);
				if(!fFoundId )
				{
					/* magic does not match */
					break;
				}
			}

			/* did the complete magic match? */
			if(fFoundId)
			{
				/* yes */
				ptSr = ptSc;
				break;
			}

			/* no, magic did not match. try next type */
			++ptSc;
		}
	}

	/* Do not override optimized settings from the detect list. */
	if( ptSr==NULL )
	{
		if( uiUseSfdp!=0 )
		{
			/* Try to detect the device parameters with SFDP. */
			ptSr = sfdp_detect(ptFlash);
		}
	}

	/* return result only if the pointer is not NULL */
	if( pptFlashAttr!=NULL )
	{
		/* return detected flash */
		*pptFlashAttr = ptSr;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-detect_flash(): iResult=%d  ptSr=0x%08x.\n", iResult, ptSr));
	return iResult;
}


/*! send_simple_cmd
*   Send a command which has no response. In detail it does this:
*               deselect the slave,
*               send one idle byte,
*               select the slave,
*               send the command,
*               deselect the slave,
*               send one idle byte
*               
*   \param   ptFls             pointer to the instance of the spi flash
*   \param   pbCmd             pointer to the byte array holding the command
*   \param   uiCmdLen          command length in bytes
*                                                                              
*   \return  RX_OK             status successfully returned                  */
static int send_simple_cmd(const SPI_FLASH_T *ptFlash, const unsigned char *pucCmd, size_t sizCmdLen)
{
	int   iResult;
	const SPI_CFG_T *ptSpiDev;


	DEBUGMSG(ZONE_FUNCTION, ("+send_simple_cmd(): ptFlash=0x%08x, pucCmd=0x%08x, sizCmdLen=0x%08x\n", ptFlash, pucCmd, sizCmdLen));

	/* get spi device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* deselect all slaves */
	ptSpiDev->pfnSelect(ptSpiDev, 0);

	/* send 1 idlebyte */
	iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
	if( iResult!=0 )
	{
		//uprintf("ERROR: send_simple_cmd: HalSPI_SendIdles failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("pfnSendIdle", iResult)
	}
	else
	{
		/* select slave */
		ptSpiDev->pfnSelect(ptSpiDev, 1);

		/* send data and receive response */
		iResult = ptSpiDev->pfnSendData(ptSpiDev, pucCmd, sizCmdLen);
		if( iResult!=0 )
		{
			//uprintf("ERROR: send_simple_cmd: HalSPI_BlockIo failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("pfnSendData", iResult)
		}

		/* deselect slave */
		ptSpiDev->pfnSelect(ptSpiDev, 0);

		if( iResult==0 )
		{
			/* send 1 idlebyte */
			iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
			if( iResult!=0 )
			{
				//uprintf("ERROR: send_simple_cmd: HalSPI_SendIdles failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("pfnSendIdle", iResult)
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-send_simple_cmd(): iResult=%d\n", iResult));
	return iResult;
}


/*! write_enable
*   unlock the flash's write protection
*               
*   \param   ptFlash           Pointer to flash Control Block
*   \return  iResult           =0 success, <>0 error                         */

static int write_enable(const SPI_FLASH_T *ptFlash)
{
	int iResult;
	unsigned char ucOpcode;

	DEBUGMSG(ZONE_FUNCTION, ("+write_enable(): ptFlash=0x%08x\n", ptFlash));
	
	/*  does the device support write protection? */
	ucOpcode = ptFlash->tAttributes.ucWriteEnableOpcode;
	
	if( ucOpcode!=0 )
	{
		/* send the 'write enable' command */
		iResult = send_simple_cmd(ptFlash, &ucOpcode, 1);
		if( iResult!=0 )
		{
			//uprintf("ERROR: write_enable: send_simple_command failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("send_simple_cmd", iResult)
		}
	} 
	else 
	{
		iResult = 0;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-write_enable(): iResult=%d.\n", iResult));
	return iResult;
}


/*! wait_for_ready
*   wait for the flash to finish a write operation
*               
*   \param   ptFls             Pointer to FLASH Control Block
*   \return  RX_OK             FLASH is idle and ready for next operation    */
static int wait_for_ready(const SPI_FLASH_T *ptFlash)
{
	unsigned char ucStatus;
	int iResult;


	DEBUGMSG(ZONE_FUNCTION, ("+wait_for_ready(): ptFlash=0x%08x\n", ptFlash));
	
	do
	{
		/*  read status and extract busy bit */
		iResult = read_status(ptFlash, &ucStatus);
		if( iResult!=0 )
		{
			//uprintf("ERROR: wait_for_ready: read_status failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("read_status", iResult)
			break;
		}

		/* get relevant bits */
		ucStatus &= ptFlash->tAttributes.ucStatusReadyMask;

		progress_bar_check_timer();
		
		/* wait until the remaining status bits match the expected value */
	} while( ucStatus!=ptFlash->tAttributes.ucStatusReadyValue );
	
	DEBUGMSG(ZONE_FUNCTION, ("-wait_for_ready(): iResult=%d.\n", iResult));
	return iResult;
}


/* TODO: move this to the board.c file. */
int board_get_spi_driver(const SPI_CONFIGURATION_T *ptSpiCfg, SPI_CFG_T *ptSpiDev)
{
	int iResult;


#if ASIC_TYP==500 || ASIC_TYP==100
	switch( ptSpiCfg->uiUnit )
	{
	case 0:
		ptSpiDev->ptUnit = (HOSTADEF(SPI)*)HOSTADDR(spi);
		iResult = boot_drv_spi_init(ptSpiDev, ptSpiCfg);
		break;

	default:
		iResult = -1;
		break;
	}
#elif ASIC_TYP==50
	switch( ptSpiCfg->uiUnit )
	{
	case 0:
		ptSpiDev->ptUnit = (HOSTADEF(SPI)*)HOSTADDR(spi0);
		iResult = boot_drv_spi_init(ptSpiDev, ptSpiCfg);
		break;

	case 1:
		ptSpiDev->ptUnit = (HOSTADEF(SPI)*)HOSTADDR(spi1);
		iResult = boot_drv_spi_init(ptSpiDev, ptSpiCfg);
		break;

	default:
		iResult = -1;
		break;
	}
#elif ASIC_TYP==10 || ASIC_TYP==56
	switch( ptSpiCfg->uiUnit )
	{
	case 0:
		iResult = boot_drv_sqi_init(ptSpiDev, ptSpiCfg);
		break;

	case 1:
		ptSpiDev->ptUnit = (HOSTADEF(SPI)*)HOSTADDR(spi_motion);
		iResult = boot_drv_spi_init(ptSpiDev, ptSpiCfg);
		break;

	default:
		iResult = -1;
		break;
	}
#else
	//uprintf("ERROR: Drv_SpiInitializeFlash: unknown asic type %d. Forgot to extend this function for a new asic?\n", ASIC_TYP);
	DBG_ERROR_VAL("unknown asic type %d. Forgot to extend this function for a new asic?", ASIC_TYP)
	iResult = -1;
#endif

	return iResult;
}


/*! Drv_SpiInitializeFlash
*   Initializes the FLASH
*               
*   \param  ptFls   Pointer to FLASH Control Block
*                                                                              
*   \return  RX_OK                   FLASH successfully initialized
*            Drv_SpiS_INVALID        Specified Flash Control Block invalid
*            Drv_SpiS_UNKNOWN_FLASH  failed to detect the serial FLASH
*/
int Drv_SpiInitializeFlash(const SPI_CONFIGURATION_T *ptSpiCfg, SPI_FLASH_T *ptFlash)
{
	int   iResult;
	const SPIFLASH_ATTRIBUTES_T *ptFlashAttr;
	SPI_CFG_T *ptSpiDev;
	unsigned int uiCmdLen;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiInitializeFlash(): ptSpiCfg=%08x, ptFlash=0x%08x\n", ptSpiCfg, ptFlash));

	/* no flash detected yet */
	ptFlashAttr = NULL;

	/* get device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* Get the driver. */
	iResult = board_get_spi_driver(ptSpiCfg, ptSpiDev);
	if( iResult!=0 )
	{
		//uprintf("ERROR: Drv_SpiInitializeFlash: HalSPI_Init failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("boot_drv_spi_init", iResult)
	}
	else
	{
		/* try to autodetect the flash */
		iResult = detect_flash(ptFlash, &ptFlashAttr);
		if( iResult!=0 )
		{
			//uprintf("ERROR: Drv_SpiInitializeFlash: detect_flash failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("detect_flash", iResult)
		}
		else
		{
			/* was a spi flash detected? */
			if(NULL == ptFlashAttr)
			{
				/* failed to detect flash */
				iResult = -1;
			}
			else
			{
				/* yes, detected spi flash -> copy all attributes */
				memcpy(&ptFlash->tAttributes, ptFlashAttr, sizeof(SPIFLASH_ATTRIBUTES_T));

				/* set higher speed for the device */
				ptSpiDev->ulSpeed = ptSpiDev->pfnGetDeviceSpeedRepresentation(ptFlash->tAttributes.ulClock);
				ptSpiDev->pfnSetNewSpeed(ptSpiDev, ptSpiDev->ulSpeed);

				/* send the init commands */
				uiCmdLen = ptFlash->tAttributes.ucInitCmd0_length;
				if( uiCmdLen!=0 )
				{
					iResult = send_simple_cmd(ptFlash, ptFlash->tAttributes.aucInitCmd0, uiCmdLen);
					if( iResult!=0 )
					{
						//uprintf("ERROR: Drv_SpiInitializeFlash: send_simple_cmd failed with %d.\n", iResult);
						DBG_CALL_FAILED_VAL("send_simple_cmd", iResult)
					}
				}
				uiCmdLen = ptFlash->tAttributes.ucInitCmd1_length;
				if( iResult==0 && uiCmdLen!=0 )
				{
					iResult = send_simple_cmd(ptFlash, ptFlash->tAttributes.aucInitCmd1, uiCmdLen);
					if( iResult!=0 )
					{
						//uprintf("ERROR: Drv_SpiInitializeFlash: send_simple_cmd failed with %d.\n", iResult);
						DBG_CALL_FAILED_VAL("send_simple_cmd", iResult)
					}
				}

				if( iResult==0 )
				{
					ptFlash->ulSectorSize = ptFlash->tAttributes.ulPageSize * ptFlash->tAttributes.ulSectorPages;

					/* get the number of bits used for the pagesize */
					ptFlash->uiPageAdrShift   = getMaskLength(ptFlash->tAttributes.ulPageSize - 1);
					ptFlash->uiSectorAdrShift = getMaskLength(ptFlash->ulSectorSize - 1);

					/* check the addressing mode */
					switch(ptFlash->tAttributes.tAdrMode)
					{
					case SPIFLASH_ADR_LINEAR:
					case SPIFLASH_ADR_PAGESIZE_BITSHIFT:
						/* all valid settings */
						break;

					default:
						/* unknown addressing mode! */
						/* the flash configuration is invalid */
						//uprintf("ERROR: Drv_SpiInitializeFlash: flash addressing mode is invalid: 0x%08x.\n", ptFlash->tAttributes.tAdrMode);
						DBG_ERROR_VAL("flash addressing mode is invalid: 0x%08x.", ptFlash->tAttributes.tAdrMode)
						iResult = -1;
					}
				}
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiInitializeFlash(): iResult=%d.\n", iResult));
	return iResult;
}

#if 0
/*! Drv_SpiEraseFlashPage
*   Erases a Page in the specified serial FLASH
*
*   \param   ptFls                           Pointer to FLASH Control Block
*
*   \return  RX_OK                           Erasure successful
*            Drv_SpiS_ERASURE_NOT_SUPPORTED  Erase function not supported or configured
*/
int Drv_SpiEraseFlashPage(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress)
{
	int iResult;
	unsigned char abCmd[4];
	unsigned long ulDeviceAddress;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiEraseFlashPage(): ptFlash=0x%08x, ulLinearAddress=0x%08x\n", ptFlash, ulLinearAddress));

	/* NOTE: DrvSflEraseAndWritePage calls this function if the flash has no bEraseAndPageProgOpcode */

	if(ptFlash->tAttributes.ucErasePageOpcode == 0x00)
	{
		/* the device has no direct opcode to erase a page, but maybe it has the bEraseAndPageProgOpcode opcode */
		if(ptFlash->tAttributes.ucEraseAndPageProgOpcode == 0x00)
		{
			/* the spi flash does not support erasing single pages */
			iResult = -1;
			//uprintf("ERROR: Drv_SpiEraseFlashPage: erase page is not supported.\n");
			DBG_ERROR("erase page is not supported.");
		}
		else
		{
			/* erase the page by writing 0xff */

			/* not yet... */
			iResult = -1;
			//uprintf("ERROR: Drv_SpiEraseFlashPage: erase page is not supported.\n");
			DBG_ERROR("erase page is not supported.");
		}
	}
	else
	{
		/* unlock write operations */
		iResult = write_enable(ptFlash);
		if( iResult!=0 )
		{
			//uprintf("ERROR: Drv_SpiEraseFlashPage: DrvSflWriteEnable failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("write_enable", iResult)
		}
		else
		{
			/* convert linear address to device address */
			ulDeviceAddress = getDeviceAddress(ptFlash, ulLinearAddress);
			/* cut off the byteoffset */
			ulDeviceAddress &= ~((1U<<ptFlash->uiPageAdrShift)-1U);

			/* set the page erase opcode */
			abCmd[0] = ptFlash->tAttributes.ucErasePageOpcode;
			/*  byte 1-3 is the page address */
			abCmd[1] = (unsigned char)((ulDeviceAddress>>16)&0xff);
			abCmd[2] = (unsigned char)((ulDeviceAddress>>8 )&0xff);
			abCmd[3] = (unsigned char)( ulDeviceAddress     &0xff);

			/* send command */
			iResult = send_simple_cmd(ptFlash, abCmd, 4);
			if( iResult!=0 )
			{
				//uprintf("ERROR: Drv_SpiEraseFlashPage: send_simple_cmd failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("send_simple_cmd", iResult)
			}
			else
			{
				/* wait for operation finish */
				iResult = wait_for_ready(ptFlash);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiEraseFlashPage: DrvSflWaitReady failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("wait_for_ready", iResult)
				}
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiEraseFlashPage(): iResult=%d.\n", iResult));
	return iResult;
}
#endif
/*! Drv_SpiEraseFlashSector
*   Erases a Sector in the specified serial FLASH
*
*   \param      ptFls                           Pointer to FLASH Control Block
*   \param      ulLinearAddress                 linear address of the sector to be erased
*
*   \return     RX_OK                           Erasure successful
*               Drv_SpiS_ERASURE_NOT_SUPPORTED  Erase function not supported or configured
*/
int Drv_SpiEraseFlashSector(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress)
{
	int iResult;
	unsigned char abCmd[4];
	unsigned long ulDeviceAddress;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiEraseFlashSector(): ptFlash=0x%08x, ulLinearAddress=0x%08x\n", ptFlash, ulLinearAddress));

	/* unlock write operations */
	iResult = write_enable(ptFlash);
	if( iResult!=0 )
	{
		//uprintf("ERROR: Drv_SpiEraseFlashSector: DrvSflWriteEnable failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("write_enable", iResult)
	}
	else
	{
#if CFG_DEBUGMSG!=0
		/* show initial status */
		iResult = print_status(ptFlash);
		if( iResult==0 )
		{
#endif
			/* convert linear address to device address */
			ulDeviceAddress = getDeviceAddress(ptFlash, ulLinearAddress);

			/* cut off the byteoffset */
			ulDeviceAddress &= ~((1U<<ptFlash->uiSectorAdrShift)-1U);

			/* set the sector erase opcode */
			abCmd[0] = ptFlash->tAttributes.ucEraseSectorOpcode;
			/* byte 1-3 is the sector address */
			abCmd[1] = (unsigned char)((ulDeviceAddress>>16)&0xff);
			abCmd[2] = (unsigned char)((ulDeviceAddress>>8 )&0xff);
			abCmd[3] = (unsigned char)( ulDeviceAddress     &0xff);

			/* send command */
			iResult = send_simple_cmd(ptFlash, abCmd, 4);
			if( iResult!=0 )
			{
				//uprintf("ERROR: Drv_SpiEraseFlashPage: send_simple_cmd failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("send_simple_cmd", iResult)
			}
			else
			{
				/* wait for operation finish */
				iResult = wait_for_ready(ptFlash);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiEraseFlashSector: wait_for_ready failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("wait_for_ready", iResult)
				}
			}
#if CFG_DEBUGMSG!=0
		}
#endif
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiEraseFlashSector(): iResult=%d.\n", iResult));
	return iResult;
}

#if 0
/*! Drv_SpiEraseFlashMultiSectors
*   Erases a sequence of sectors in the flash
*
*   \param   ptFls                           Pointer to FLASH Control Block
*   \param   ulLinearStartAddress            linear start address of the sectors to be erased
*   \param   ulLinearEndAddress              linear end address of the sectors to be erased
*
*   \return  RX_OK                           Erasure successful
*            Drv_SpiS_ERASURE_NOT_SUPPORTED  Erase function not supported or configured
*/
int Drv_SpiEraseFlashMultiSectors(const SPI_FLASH_T *ptFlash, unsigned long ulLinearStartAddress, unsigned long ulLinearEndAddress)
{
	int iResult;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiEraseFlashMultiSectors(): ptFlash=0x%08x, ulLinearStartAddress=0x%08x, ulLinearEndAddress=0x%08x\n", ptFlash, ulLinearStartAddress, ulLinearEndAddress));

	/* init result, assume success */
	iResult = 0;

	/* loop over all sectors */
	while(ulLinearStartAddress < ulLinearEndAddress)
	{
		/* delete sector */
		iResult = Drv_SpiEraseFlashSector(ptFlash, ulLinearStartAddress);
		if( iResult!=0 )
		{
			//uprintf("ERROR: Drv_SpiEraseFlashMultiSectors: Drv_SpiEraseFlashSector failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("Drv_SpiEraseFlashSector", iResult)
			break;
		}

		/* next sector */
		ulLinearStartAddress += ptFlash->ulSectorSize;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiEraseFlashMultiSectors(): iResult=%d.\n", iResult));
	return iResult;
}
#endif
#if 0
/*! Drv_SpiEraseFlashComplete
*   Erases the complete flash
*
*   \param   ptFls   Pointer to FLASH Control Block
*
*   \return  RX_OK   Erasure successful
*/
int Drv_SpiEraseFlashComplete(const SPI_FLASH_T *ptFlash)
{
	int iResult;
	unsigned int      uiEraseChipCmdLen;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiEraseFlashComplete(): ptFlash=0x%08x\n", ptFlash));

	uiEraseChipCmdLen = ptFlash->tAttributes.uiEraseChipCmdLen;
	if(0x00 != uiEraseChipCmdLen)
	{
		/* unlock write operations */
		iResult = write_enable(ptFlash);
		if( iResult!=0 )
		{
			//uprintf("ERROR: Drv_SpiEraseFlashComplete: write_enable failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("write_enable", iResult)
		}
		else
		{
			/* send command */
			iResult = send_simple_cmd(ptFlash, ptFlash->tAttributes.aucEraseChipCmd, uiEraseChipCmdLen);
			if( iResult!=0 )
			{
				//uprintf("ERROR: Drv_SpiEraseFlashComplete: send_simple_cmd failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("send_simple_cmd", iResult)
			}
			else
			{
				/* wait for operation finish */
				iResult = wait_for_ready(ptFlash);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiEraseFlashComplete: DrvSflWaitReady failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("wait_for_ready", iResult)
				}
			}
		}
	}
	else
	{
		/* the flash does not support erasing the whole device at once, delete it in sector steps */
		iResult = Drv_SpiEraseFlashMultiSectors(ptFlash, 0, ptFlash->tAttributes.ulSize);
		if( iResult!=0 )
		{
			//uprintf("ERROR: Drv_SpiEraseFlashComplete: Drv_SpiEraseFlashMultiSectors failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("Drv_SpiEraseFlashMultiSectors", iResult)
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiEraseFlashComplete(): iResult=%d.\n", iResult));
	return iResult;
}
#endif

#if 0
/*! Drv_SpiWriteFlashPages
*   write 1 or more pages to the flash
*
*   \param   ptFls   Pointer to FLASH Control Block
*   \param   ulOffs  Offset within the FLASH to write data to
*   \param   pabSrc  Pointer to Source data that shall be written
*   \param   ulNum   Number of data in multiples of bytes to write
*
*   \return  RX_OK   Erasure successful
*/
int Drv_SpiWriteFlashPages(const SPI_FLASH_T *ptFlash, unsigned long ulOffs, const unsigned char *pabSrc, unsigned long ulNum)
{
	int iResult      = 1;
	unsigned long    ulPageSize;
	const unsigned char *dc, *de;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiWriteFlashPages(): ptFlash=0x%08x, ulOffs=0x%08x, pabSrc=0x%08x, ulNum=%d\n", ptFlash, ulOffs, pabSrc, ulNum));

	/* test parameters, is there data to write? */
	if( (0 == ulNum) || (NULL == pabSrc) )
	{
		return 1;
	}

	/* set pointers to start and end of data */
	/* dc is the startpointer */
	dc           = pabSrc;

	/* de is the endpointer */
	de           = dc + ulNum;

	/* get pagesize */
	ulPageSize   = ptFlash->tAttributes.ulPageSize;

	/* the startaddress must be page aligned */
	if(0 != (ulOffs % ulPageSize))
	{
		//uprintf("ERROR: Drv_SpiWriteFlashPages: startaddress is not page aligned.\n");
		DBG_ERROR("startaddress is not page aligned.")
		iResult = -1;
	}
	else
	{
		/* check size for alignment */
		if(0 != (ulNum % ulPageSize))
		{
			//uprintf("ERROR: Drv_SpiWriteFlashPages: endaddress is not page aligned.\n");
			DBG_ERROR("endaddress is not page aligned.")
			iResult = -1;
		}
		else
		{
			/*  transfer complete pages */
			while(dc < de)
			{
				/*  write bytes to flash */
				iResult = Drv_SpiEraseAndWritePage(ptFlash, ulOffs, dc, ulPageSize);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiWriteFlashPages: DrvSflWritePage failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("Drv_SpiEraseAndWritePage", iResult)
					break;
				}

				/*  advance data pointer */
				dc += ulPageSize;

				/*  advance address */
				ulOffs += ulPageSize;
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiWriteFlashPages(): iResult=%d.\n", iResult));
	return iResult;
}
#endif

/*! Drv_SpiReadFlash
*   Reads a byte block from a FLASH
*
*   \param   ptFls    Pointer to FLASH Control Block
*   \param   ulOffs   Offset within the FLASH to write data from
*   \param   pabDest  Pointer to Destination the read data that shall be written to
*   \param   ulNum    Number of data in multiples of bytes to write
*
*   \return  RX_OK    Programming successful
*/

int Drv_SpiReadFlash(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, unsigned char *pucData, size_t sizData)
{
	int           iResult;
	unsigned long ulDeviceAddress;
	unsigned char abCmd[4];
	const SPI_CFG_T *ptSpiDev;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiReadFlash(): ptFlash=0x%08x, ulLinearAddress=0x%08x, pucData=0x%08x, sizData=%d\n", ptFlash, ulLinearAddress, pucData, sizData));

	/* get spi device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* deselect all slaves */
	ptSpiDev->pfnSelect(ptSpiDev, 0);

	/* send 1 idlebyte */
	iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
	if( iResult!=0 )
	{
		//uprintf("ERROR: Drv_SpiReadFlash: HalSPI_SendIdles failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("SendIdle", iResult);
	}
	else
	{
		/* select slave */
		ptSpiDev->pfnSelect(ptSpiDev, 1);

		/* convert linear addressto device specific addressing */
		ulDeviceAddress = getDeviceAddress(ptFlash, ulLinearAddress);

		/*  first byte of the command is the read bOpcode */
		abCmd[0] = ptFlash->tAttributes.ucReadOpcode;
		/*  byte 1-3 is the address */
		abCmd[1] = (unsigned char)((ulDeviceAddress>>16U)&0xffU);
		abCmd[2] = (unsigned char)((ulDeviceAddress>> 8U)&0xffU);
		abCmd[3] = (unsigned char)( ulDeviceAddress      &0xffU);

		/* send data and receive response */
		iResult = ptSpiDev->pfnSendData(ptSpiDev, abCmd, 4);
		if( iResult!=0 )
		{
			//uprintf("ERROR: Drv_SpiReadFlash: HalSPI_BlockIo failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("SendData", iResult);
		}
		else
		{
			/* send some DC bytes */
			iResult = ptSpiDev->pfnSendIdle(ptSpiDev, ptFlash->tAttributes.ucReadOpcodeDCBytes);
			if( iResult!=0 )
			{
				//uprintf("ERROR: Drv_SpiReadFlash: HalSPI_SendIdles failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("SendIdle", iResult);
			}
			else
			{
				/* receive the data */
				iResult = ptSpiDev->pfnReceiveData(ptSpiDev, pucData, sizData);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiReadFlash: HalSPI_BlockIo failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("ReceiveData", iResult);
				}
			}
		}

		/* deselect slave */
		ptSpiDev->pfnSelect(ptSpiDev, 0);

		/* send 1 idlebyte */
		if( iResult==0 )
		{
			iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
			if( iResult!=0 )
			{
				//uprintf("ERROR: send_simple_cmd: HalSPI_SendIdles failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("SendIdle", iResult);
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiReadFlash(): iResult=%d.\n", iResult));
	return iResult;
}

#if 0
/*! DrvSflEraseAndWritePage
*   erase a page and write new data
*
*   \param   ptFls      Pointer to FLASH Control Block
*   \param   ulAddress  Address offset where to write data to
*   \param   ulLength   Number of bytes to be written
*   \param   pabBuffer  Pointer to source buffer containing the data to write
*
*   \return  RX_OK      if write operation succeeded
*/
int Drv_SpiEraseAndWritePage(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, const unsigned char *pucData, size_t sizData)
{
	int             iResult;
	size_t sizPage;
	unsigned long   ulDeviceAddress;
	unsigned char   aucCmd[4];
	unsigned char   ucCmd;
	const SPI_CFG_T *ptSpiDev;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiEraseAndWritePage(): ptFlash=0x%08x, ulLinearAddress=0x%08x, pucData=0x%08x, sizData=%d\n", ptFlash, ulLinearAddress, pucData, sizData));

	/* get spi device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* check startaddress and size for page alignment */
	sizPage = ptFlash->tAttributes.ulPageSize;
	if(0 != (ulLinearAddress % sizPage))
	{
		//uprintf("ERROR: Drv_SpiEraseAndWritePage: startaddress is not page aligned.\n");
		DBG_ERROR("startaddress is not page aligned.");
		iResult = -1;
	}
	else
	{
		/* this function can only write exactly one page */
		if( sizData!=sizPage )
		{
			//uprintf("ERROR: Drv_SpiEraseAndWritePage: size is not page aligned.\n");
			DBG_ERROR("size is not page aligned.");
			iResult = -1;
		}
		else
		{
			/* does the flash support eraseAndWrite in one opcode? */
			ucCmd = ptFlash->tAttributes.ucEraseAndPageProgOpcode;
			if(0 == ucCmd)
			{
				/* no, eraseAndWrite is not supported. try page erase instead */
				iResult = Drv_SpiEraseFlashPage(ptFlash, ulLinearAddress);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiEraseAndWritePage: Drv_SpiEraseFlashPage failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("Drv_SpiEraseFlashPage", iResult);
				}
				else
				{
					/* write the page */
					iResult = Drv_SpiWritePage(ptFlash, ulLinearAddress, pucData, sizData);
					if( iResult!=0 )
					{
						//uprintf("ERROR: Drv_SpiEraseAndWritePage: Drv_SpiWritePage failed with %d.\n", iResult);
						DBG_CALL_FAILED_VAL("Drv_SpiWritePage", iResult);
					}
				}
			}
			else
			{
				/* yes, eraseAndWrite is supported */

				/* unlock write operations */
				iResult = write_enable(ptFlash);
				if( iResult!=0 )
				{
					//uprintf("ERROR: Drv_SpiEraseAndWritePage: DrvSflWriteEnable failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("write_enable", iResult);
				}
				else
				{
					/* select slave */
					ptSpiDev->pfnSelect(ptSpiDev, 1);

					/* send command */

					/*  translate the address to the device format */
					ulDeviceAddress = getDeviceAddress(ptFlash, ulLinearAddress);

					/*  first byte of the command is the write bOpcode */
					aucCmd[0] = ptFlash->tAttributes.ucEraseAndPageProgOpcode;
					/*  byte 1-3 is the address */
					aucCmd[1] = (unsigned char)((ulDeviceAddress>>16U)&0xffU);
					aucCmd[2] = (unsigned char)((ulDeviceAddress>> 8U)&0xffU);
					aucCmd[3] = (unsigned char)( ulDeviceAddress      &0xffU);

					iResult = ptSpiDev->pfnSendData(ptSpiDev, aucCmd, 4);
					if( iResult!=0 )
					{
						//uprintf("ERROR: Drv_SpiEraseAndWritePage: HalSPI_BlockIo failed with %d.\n", iResult);
						DBG_CALL_FAILED_VAL("pfnSendData", iResult);
					}
					else
					{
						/* send data */
						iResult = ptSpiDev->pfnSendData(ptSpiDev, pucData, sizData);
						if( iResult!=0 )
						{
							//uprintf("ERROR: Drv_SpiEraseAndWritePage: HalSPI_BlockIo failed with %d.\n", iResult);
							DBG_CALL_FAILED_VAL("pfnSendData", iResult);
						}
					}

					/* deselect slave */
					ptSpiDev->pfnSelect(ptSpiDev, 0);

					if( iResult==0 )
					{
						iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
						if( iResult!=0 )
						{
							//uprintf("ERROR: Drv_SpiEraseAndWritePage: Drv_SpiSendIdle failed with %d.\n", iResult);
							DBG_CALL_FAILED_VAL("pfnSendIdle", iResult);
						}
						else
						{
							/* wait until the write operation is finished */
							iResult = wait_for_ready(ptFlash);
							if( iResult!=0 )
							{
								//uprintf("ERROR: Drv_SpiEraseAndWritePage: DrvSflWaitReady failed with %d.\n", iResult);
								DBG_CALL_FAILED_VAL("wait_for_ready", iResult);
							}
						}
					}
				}
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiEraseAndWritePage(): iResult=%d.\n", iResult));
	return iResult;
}
#endif


static int write_single_opcode(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, const unsigned char *pabBuffer)
{
	int             iResult;
	unsigned long   ulDeviceAddress;
	unsigned char   aucCmd[4];
	const SPI_CFG_T *ptSpiDev;


	DEBUGMSG(ZONE_FUNCTION, ("+write_single_opcode(): ptFlash=0x%08x, ulLinearAddress=0x%08x, pabBuffer=0x%08x\n", ptFlash, ulLinearAddress, pabBuffer));

	/* get spi device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* unlock write operations */
	iResult = write_enable(ptFlash);
	if( iResult!=0 )
	{
		//uprintf("ERROR: write_single_opcode: write_enable failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("write_enable", iResult);
	}
	else
	{
#if CFG_DEBUGMSG!=0
		iResult = print_status(ptFlash);
		if( iResult==0 )
		{
#endif
			/* select slave */
			ptSpiDev->pfnSelect(ptSpiDev, 1);

			/* send command */

			/*  translate the address to the device format */
			ulDeviceAddress = getDeviceAddress(ptFlash, ulLinearAddress);

			/*  first byte of the command is the write bOpcode */
			aucCmd[0] = ptFlash->tAttributes.ucPageProgOpcode;
			/*  byte 1-3 is the address */
			aucCmd[1] = (unsigned char)((ulDeviceAddress>>16U)&0xffU);
			aucCmd[2] = (unsigned char)((ulDeviceAddress>> 8U)&0xffU);
			aucCmd[3] = (unsigned char)( ulDeviceAddress      &0xffU);

			iResult = ptSpiDev->pfnSendData(ptSpiDev, aucCmd, 4);
			if( iResult!=0 )
			{
				//uprintf("ERROR: write_single_opcode: HalSPI_BlockIo failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("pfnSendData", iResult);
			}
			else
			{
				/* send data */
				iResult = ptSpiDev->pfnSendData(ptSpiDev, pabBuffer, ptFlash->tAttributes.ulPageSize);
				if( iResult!=0 )
				{
					//uprintf("ERROR: write_single_opcode: HalSPI_BlockIo failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("pfnSendData", iResult);
				}
			}

			/* deselect slave */
			ptSpiDev->pfnSelect(ptSpiDev, 0);

			if( iResult==0 )
			{
				iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
				if( iResult!=0 )
				{
					//uprintf("ERROR: write_single_opcode: HalSPI_SendIdles failed with %d.\n", iResult);
					DBG_CALL_FAILED_VAL("pfnSendIdle", iResult);
				}
				else
				{
					/* wait until the write operation is finished */
					iResult = wait_for_ready(ptFlash);
					if( iResult!=0 )
					{
						//uprintf("ERROR: write_single_opcode: wait_for_ready failed with %d.\n", iResult);
						DBG_CALL_FAILED_VAL("wait_for_ready", iResult);
					}
				}
			}
#if CFG_DEBUGMSG!=0
		}
#endif
	}

	DEBUGMSG(ZONE_FUNCTION, ("-write_single_opcode(): iResult=%d.\n", iResult));
	return iResult;
}


static int write_via_buffer(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, const unsigned char *pabBuffer)
{
	int             iResult;
	unsigned long   ulDeviceAddress;
	unsigned char   aucCmd[4];
	const SPI_CFG_T *ptSpiDev;


	DEBUGMSG(ZONE_FUNCTION, ("+write_via_buffer(): ptFlash=0x%08x, ulLinearAddress=0x%08x, pabBuffer=0x%08x\n", ptFlash, ulLinearAddress, pabBuffer));

	/* get spi device */
	ptSpiDev = &ptFlash->tSpiDev;

	/* select slave */
	ptSpiDev->pfnSelect(ptSpiDev, 1);

	/* send command */

	/* first byte of the command is the write Opcode */
	aucCmd[0] = ptFlash->tAttributes.ucBufferFill;
	/* byte 1-3 is the byte offset in the buffer */
	aucCmd[1] = 0U;
	aucCmd[2] = 0U;
	aucCmd[3] = 0U;

	iResult = ptSpiDev->pfnSendData(ptSpiDev, aucCmd, 4);
	if( iResult!=0 )
	{
		//uprintf("ERROR: write_via_buffer: HalSPI_BlockIo failed with %d.\n", iResult);
		DBG_CALL_FAILED_VAL("pfnSendData", iResult);
	}
	else
	{
		/* send data */
		iResult = ptSpiDev->pfnSendData(ptSpiDev, pabBuffer, ptFlash->tAttributes.ulPageSize);
		if( iResult!=0 )
		{
			//uprintf("ERROR: write_via_buffer: HalSPI_BlockIo failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("pfnSendData", iResult);
		}
	}

	/* deselect slave */
	ptSpiDev->pfnSelect(ptSpiDev, 0);

	if( iResult==0 )
	{
		iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
		if( iResult!=0 )
		{
			//uprintf("ERROR: write_via_buffer: HalSPI_SendIdles failed with %d.\n", iResult);
			DBG_CALL_FAILED_VAL("pfnSendIdle", iResult);
		}
		else
		{
			/* unlock write operations */
			iResult = write_enable(ptFlash);
			if( iResult!=0 )
			{
				//uprintf("ERROR: write_via_buffer: write_enable failed with %d.\n", iResult);
				DBG_CALL_FAILED_VAL("write_enable", iResult);
			}
			else
			{
#if 0
				iResult = print_status(ptFlash);
				if( iResult!=0 )
				{
#endif
					/* select slave */
					ptSpiDev->pfnSelect(ptSpiDev, 1);

					/* write buffer to main memory */

					/* translate the address to the device format */
					ulDeviceAddress = getDeviceAddress(ptFlash, ulLinearAddress);

					/* first byte of the command is the write bOpcode */
					aucCmd[0] = ptFlash->tAttributes.ucBufferWriteOpcode;
					/* byte 1-3 is the address */
					aucCmd[1] = (unsigned char)((ulDeviceAddress>>16U)&0xffU);
					aucCmd[2] = (unsigned char)((ulDeviceAddress>> 8U)&0xffU);
					aucCmd[3] = (unsigned char)( ulDeviceAddress      &0xffU);

					iResult = ptSpiDev->pfnSendData(ptSpiDev, aucCmd, 4);
					if( iResult!=0 )
					{
						//uprintf("ERROR: write_via_buffer: HalSPI_BlockIo failed with %d.\n", iResult);
						DBG_CALL_FAILED_VAL("pfnSendData", iResult);
					}

					/* deselect slave */
					ptSpiDev->pfnSelect(ptSpiDev, 0);

					if( iResult==0 )
					{
						iResult = ptSpiDev->pfnSendIdle(ptSpiDev, 1);
						if( iResult!=0 )
						{
							//uprintf("ERROR: write_via_buffer: HalSPI_SendIdles failed with %d.\n", iResult);
							DBG_CALL_FAILED_VAL("pfnSendIdle", iResult);
						}
						else
						{
							/* wait until the write operation is finished */
							iResult = wait_for_ready(ptFlash);
							if( iResult!=0 )
							{
								//uprintf("ERROR: write_via_buffer: wait_for_ready failed with %d.\n", iResult);
								DBG_CALL_FAILED_VAL("wait_for_ready", iResult);
							}
						}
					}
#if 0
				}
#endif
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-write_via_buffer(): iResult=%d.\n", iResult));
	return iResult;
}


int Drv_SpiWritePage(const SPI_FLASH_T *ptFlash, unsigned long ulLinearAddress, const unsigned char *pucData, size_t sizData)
{
	int iResult;
	size_t sizPage;


	DEBUGMSG(ZONE_FUNCTION, ("+Drv_SpiWritePage(): ptFlash=0x%08x, ulLinearAddress=0x%08x, pucData=0x%08x, sizData=0x%08x\n", ptFlash, ulLinearAddress, pucData, sizData));

	/* check startaddress and size for page alignment */
	sizPage = ptFlash->tAttributes.ulPageSize;
	if(0 != (ulLinearAddress % sizPage))
	{
		//uprintf("ERROR: Drv_SpiWritePage: startaddress is not page aligned.\n");
		DBG_ERROR("startaddress is not page aligned.");
		iResult = -1;
	}
	else
	{
		/* this function can only write exactly one page */
		if( sizData!=sizPage )
		{
			//uprintf("ERROR: Drv_SpiWritePage: size is not page aligned.\n");
			DBG_ERROR("size is not page aligned.");
			iResult = -1;
		}
		else
		{
			/* does the flash support write in one opcode? */
			if(0 != ptFlash->tAttributes.ucPageProgOpcode)
			{
				iResult = write_single_opcode(ptFlash, ulLinearAddress, pucData);
			}
			else if(ptFlash->tAttributes.ucBufferFill!=0  && ptFlash->tAttributes.ucBufferWriteOpcode!=0)
			{
				iResult = write_via_buffer(ptFlash, ulLinearAddress, pucData);
			}
			else
			{
				//uprintf("ERROR: Drv_SpiWritePage: write without previous erase is not supported.\n");
				DBG_ERROR("write without previous erase is not supported.");
				iResult = -1;
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-Drv_SpiWritePage(): iResult=%d.\n", iResult));
	return iResult;
}


typedef struct ADR_MODE_NAME_STRUCT
{
	SPIFLASH_ADR_T tAdrMode;
	const char *pcAdrMode;
} ADR_MODE_NAME_T;


static const ADR_MODE_NAME_T atAdrModeName[2] =
{
	{ SPIFLASH_ADR_LINEAR,              "linear" },
	{ SPIFLASH_ADR_PAGESIZE_BITSHIFT,   "pagesize bitshift" }
};


const char *spi_flash_get_adr_mode_name(SPIFLASH_ADR_T tAdrMode)
{
	const char *pcResult = "";
	const ADR_MODE_NAME_T *ptCnt;
	const ADR_MODE_NAME_T *ptEnd;


	ptCnt = atAdrModeName;
	ptEnd = ptCnt + (sizeof(atAdrModeName) / sizeof(atAdrModeName[0]));
	while( ptCnt<ptEnd )
	{
		if( tAdrMode==ptCnt->tAdrMode )
		{
			pcResult = ptCnt->pcAdrMode;
			break;
		}
	}

	return pcResult;
}


