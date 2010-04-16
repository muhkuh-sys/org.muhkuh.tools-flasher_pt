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
  File          : CFIFlash.c
 ----------------------------------------------------------------------------
  Description:

      CFIFlash.c : Implementation of CFI identification routines
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
#include "netx_io_areas.h"
#include "strata.h"
#include "spansion.h"
#include "uprintf.h"
#include <string.h>


#ifdef DEBUG
	/* show all messages by default */
	static unsigned long s_ulCurSettings = 0xffffffff;

	#define DEBUGZONE(n)  (s_ulCurSettings&(0x00000001<<(n)))

	//
	// These defines must match the ZONE_* defines
	//
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
#else  // DEBUG
	#define DEBUGMSG(cond,printf_exp) ((void)0)
#endif // DEBUG


// ///////////////////////////////////////////////////// 
//! \file CFIFlash.c
//!  Implementation of CFI identification routines
// ////////////////////////////////////////////////////



typedef enum 
{
	CFISETUP_1x08		= 0x01,
	CFISETUP_2x08		= 0x02,
	CFISETUP_1x16		= 0x04,
	CFISETUP_2x16		= 0x08,
	CFISETUP_1x32		= 0x10
} tCFISETUP;


// ///////////////////////////////////////////////////// 
//! Structure definition for FLASH width and pairing test cases
// ///////////////////////////////////////////////////// 
typedef struct tagCFI_CHECK_CONDITIONS
{
  unsigned long ulOffset;   //!< offset the pattern is expected at
  unsigned int  uiWidth;    //!< bus width for pattern (if detected)
  int           fPaired;    //!< pairing of FLASHes for pattern (if detected)
  unsigned char bQueryLen;  //!< length of the string to query (needed as there are 0-chars in the identification)
  const char*   szQuery;    //!< pattern to look for in memory at given offset
  tCFISETUP     tSetup;     //!< setup id of this config
} CFI_CHECK_CONDITIONS;


// ///////////////////////////////////////////////////// 
//! Structure used for identifying bus width and 
//! pairing of CFI FLASHes
// ///////////////////////////////////////////////////// 
static const CFI_CHECK_CONDITIONS s_atCFIChecks[] =
{
//	{0x40,	32,	FALSE,	12,	"Q\0\0\0R\0\0\0Y\0\0\0",	CFISETUP_1x32 },	/* 1x 32Bit Flash */

	{0x40,	32,	TRUE,	12,	"Q\0Q\0R\0R\0Y\0Y\0",		CFISETUP_2x16 },	/* 2x 16Bit Flash */
//	{0x20,	16,	FALSE,	10,	"Q\0??R\0??Y\0",		CFISETUP_1x16 },	/* 1x 16Bit Flash */
	{0x20,	16,	FALSE, 6,	"Q\0R\0Y\0",			CFISETUP_1x16 },	/* 1x 16Bit Flash */

	{0x20,	16,	TRUE,	 6,	"QQRRYY",			CFISETUP_2x08 },	/* 2x 8Bit Flash */
	{0x10,	 8,	FALSE, 3,	"QRY",				CFISETUP_1x08 }		/* 8 Bit Flash   */
};

#define ARRAY_SIZE(a)   (sizeof(a) / sizeof(a[0]))

// ///////////////////////////////////////////////////// 
//! Compares memory buffers for CFI detection routines.
//! It uses '?' as wildcard
//!  \param pvFlash Pointer to flash address to verify
//!  \param pvCmpBuf Buffer containing expected flash content (This buffer may contain '?' placeholder)
//!  \param ulLen Length of comparison
//!  \return 0 if equal, -1 on mismatch
// ///////////////////////////////////////////////////// 
static int CFIMemCmp(volatile void* pvFlash, const void* pvCmpBuf, unsigned long ulLen)
{
	int iRet;
	volatile unsigned char *pbFlash;
	const unsigned char    *pbCmpBuf;
	unsigned char           ucFlashData;
	unsigned char           ucCmpData;


	DEBUGMSG(ZONE_FUNCTION, ("+CFIMemCmp(): pvFlash=0x$8, pvCmpBuf=0x$8, ulLen=0x$\n", pvFlash, pvCmpBuf, ulLen));

	iRet = 0;

	pbFlash  = (volatile unsigned char*)pvFlash;
	pbCmpBuf = (const unsigned char*)pvCmpBuf;

	while( ulLen>0 )
	{
		ucCmpData   = *(pbCmpBuf++);
		ucFlashData = *(pbFlash++);

		DEBUGMSG(ZONE_VERBOSE, (".CFIMemCmp(): Pattern: 0x$2, Flash: 0x$2.\n", ucCmpData, ucFlashData));

		if( ucCmpData!='?' && ucCmpData!=ucFlashData )
		{
			iRet = -1;
			break;
		}

		--ulLen;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFIMemCmp(): iRet=0x$\n", iRet));

	return iRet;
}

// ///////////////////////////////////////////////////// 
//! Writes a command to the given flash with the indicated width and pairing
//!  \param pbFlashAddr Address inside flash, to write command to (ATTENTION: Alignment is not checked)
//!  \param bWidth Width of the FLASH 
//!  \param fPaired TRUE if two devices are paired to build one flash
//!  \param bCommand Command to write to FLASH
// ///////////////////////////////////////////////////// 
static void CFI_FlashWriteCommand(unsigned char* pucFlashAddr, unsigned int uiWidth, int fPaired, unsigned int uiCommand)
{
	unsigned long  ulValue;
	union
	{
		volatile unsigned char  *pucPtr;
		volatile unsigned short *pusPtr;
		volatile unsigned long  *pulPtr;
	} uPtr;


	DEBUGMSG(ZONE_FUNCTION, ("+CFI_FlashWriteCommand(): pucFlashAddr=0x$8, uiWidth=0x$, fPaired=0x$, uiCommand=0x$\n", pucFlashAddr, uiWidth, fPaired, uiCommand));

	/* set the address */
	uPtr.pucPtr = pucFlashAddr;

	switch(uiWidth)
	{
	case 8:
		/* 8bits cannot be paired */
		*(uPtr.pucPtr) = (unsigned char)uiCommand;
		break;

	case 16:
		ulValue = (unsigned long)uiCommand;
		if( fPaired!=0 )
		{
			ulValue |= ulValue << 8U;
		}
		*(uPtr.pusPtr) = (unsigned short)ulValue;
		break;

	case 32:
		ulValue = uiCommand;
		if( fPaired!=0 )
		{
			ulValue |= ulValue << 16U;
		}
		*(uPtr.pulPtr) = ulValue;
		break;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_FlashWriteCommand()\n"));
}


static int CFI_QueryFlashLayout(FLASH_DEVICE *ptFlashDevice, PFN_FLASHSETUP pfnSetup)
{
	unsigned char *pbFlashBase;
	PCFI_QUERY_INFORMATION ptQueryInformation;
	unsigned char abCfiId[3];
	unsigned long ulFlashSize = 0;
	unsigned long ulCurSector = 0;
	unsigned long ulCurOffset = 0;
	unsigned int uiCnt;
	int fRet;
        int fPaired;

	DEBUGMSG(ZONE_FUNCTION, ("+CFI_QueryFlashLayout(): ptFlashDevice=0x$8, pfnSetup=0x$8\n", ptFlashDevice, pfnSetup));

	pbFlashBase = ptFlashDevice->pbFlashBase;
	fPaired     = ptFlashDevice->fPaired;

	ptQueryInformation = (PCFI_QUERY_INFORMATION)&ptFlashDevice->pbFlashBase[CFI_QUERY_INFO_OFFSET];

	/* if we are using paired flashes, we assume both are identical and only query the first one */
	pfnSetup(8);
	CFI_FlashWriteCommand(pbFlashBase, 8, FALSE, READ_ARRAY_CMD);
	
	/* Enter Query mode */
	CFI_FlashWriteCommand(pbFlashBase + READ_QUERY_CMD_OFFSET, 8, FALSE, READ_QUERY_CMD);

	/* check byte QRY pattern, to see if flash has entered valid CFI Query mode */
	abCfiId[0] = pbFlashBase[CFI_QUERY_INFO_OFFSET];
	abCfiId[1] = pbFlashBase[CFI_QUERY_INFO_OFFSET+1];
	abCfiId[2] = pbFlashBase[CFI_QUERY_INFO_OFFSET+2];

	DEBUGMSG(ZONE_VERBOSE, (".CFI_QueryFlashLayout(): abCfiId=[$2, $2, $2]\n", abCfiId[0], abCfiId[1], abCfiId[2]));

	if( abCfiId[0]=='Q' && abCfiId[1]=='R' && abCfiId[2]=='Y' )
	{
		DEBUGMSG(ZONE_VERBOSE, (".CFI_QueryFlashLayout(): Ok, QRY magic found.\n"));

		int iCurRegion = 0;

		ulFlashSize = 1U << ptQueryInformation->bDeviceSize;

		if( fPaired )
		{
			ulFlashSize *= 2;
		}

		ptFlashDevice->ulFlashSize   = ulFlashSize;

		/* cycle through geometry options, until all blocks are evaluated */
		for(iCurRegion = 0; iCurRegion < ptQueryInformation->bEraseBlockRegions; iCurRegion++)
		{
			unsigned long  ulBlockInfo = ptQueryInformation->aulEraseBlockInformations[ulCurSector];
			unsigned short usBlocks    = (unsigned short)(ulBlockInfo & 0x0000FFFF);
			unsigned int   uiBlockSize = (ulBlockInfo & 0xFFFF0000U) >> 16U;

			if( fPaired )
			{
				uiBlockSize *= 2U;
			}

			for(uiCnt = 0; uiCnt <= usBlocks; uiCnt++)
			{
				unsigned long ulBlockByteSize = 0;

				if(0 == uiBlockSize)
				{
					ulBlockByteSize = 0x80;
				}
				else
				{
					ulBlockByteSize = uiBlockSize * 0x100U;
				}

				ptFlashDevice->atSectors[ulCurSector].ulOffset = ulCurOffset;
				ptFlashDevice->atSectors[ulCurSector].ulSize   = ulBlockByteSize;
				++ulCurSector;

				ulCurOffset += ulBlockByteSize;
			}
		}

		ptFlashDevice->ulSectorCnt = ulCurSector;

		ptFlashDevice->usVendorCommandSet   = ptQueryInformation->usVendorCommandSet;
		ptFlashDevice->ulMaxBufferWriteSize = 1U << ptQueryInformation->usMaxBufferWriteSize;

		fRet = TRUE;
	}
	else
	{
		fRet = FALSE;
		DEBUGMSG(ZONE_ERROR, ("!CFI_QueryFlashLayout(): Error, no QRY magic found.\n"));
	}

	/* reset flash to read mode */
	CFI_FlashWriteCommand(pbFlashBase, 8, FALSE, READ_ARRAY_CMD);

	pfnSetup(ptFlashDevice->uiWidth);

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_QueryFlashLayout(): fRet=0x$\n", fRet));

	return fRet;
}


// ///////////////////////////////////////////////////// 
//! Identifies a CFI compliant FLASH device
//! This routine will enter all data into the ptFlashDevice structure
//! that can be read from FLASH.
//!  \param ptFlashDevice Returned FALSH info on success. Base address pointer must be inserted before calling this function
//!  \return TRUE if identified successfully
// ///////////////////////////////////////////////////// 
int CFI_IdentifyFlash(FLASH_DEVICE* ptFlashDevice, PFN_FLASHSETUP pfnSetup)
{
	int             fRet         = FALSE;
	unsigned int    uiFlashWidth;
	int             fPaired      = FALSE;
	unsigned int    uiBits;
	int             iPaired;
	unsigned int    uiCnt;
	unsigned char   *pbFlashBase;
	unsigned long   ulDetectedTypes;


	DEBUGMSG(ZONE_FUNCTION, ("+CFI_IdentifyFlash(): ptFlashDevice=0x$8, pfnSetup=0x$\n", ptFlashDevice, pfnSetup));

	if( ptFlashDevice==NULL )
	{
    		fRet = FALSE;
	}
	else
	{
		pbFlashBase  = ptFlashDevice->pbFlashBase;

		/* check if we find patterns of QRY response to identify flash width and pairing */
		ulDetectedTypes = 0;
		for(uiCnt = 0; uiCnt < ARRAY_SIZE(s_atCFIChecks); ++uiCnt)
		{
			uiBits = s_atCFIChecks[uiCnt].uiWidth;
			iPaired = s_atCFIChecks[uiCnt].fPaired;
			uprintf(".Trying  bits: $2, paired: $1\n", uiBits, iPaired);

			/* set bus width to query size */
			pfnSetup(uiBits);

			/* try to switch all possible combinations to array read mode */
			CFI_FlashWriteCommand(pbFlashBase,  8, FALSE, READ_ARRAY_CMD);
			CFI_FlashWriteCommand(pbFlashBase, 16, TRUE,  READ_ARRAY_CMD);
			CFI_FlashWriteCommand(pbFlashBase, 32, TRUE,  READ_ARRAY_CMD);

			CFI_FlashWriteCommand(pbFlashBase + READ_QUERY_CMD_OFFSET * (uiBits>>3U), uiBits, iPaired, READ_QUERY_CMD);

			if(CFIMemCmp(pbFlashBase + s_atCFIChecks[uiCnt].ulOffset,
			              s_atCFIChecks[uiCnt].szQuery,
			              s_atCFIChecks[uiCnt].bQueryLen) == 0)
			{
				ulDetectedTypes |= s_atCFIChecks[uiCnt].tSetup;
				uprintf(".Ok, found magic!\n");
			}
		}

		uprintf(".Detection state: $8\n", ulDetectedTypes);

		/* reset found flashes to read mode */
		CFI_FlashWriteCommand(pbFlashBase,  8, FALSE, READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pbFlashBase, 16, TRUE,  READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pbFlashBase, 32, TRUE,  READ_ARRAY_CMD);

		switch( ulDetectedTypes )
		{
		case CFISETUP_1x08:					/* NOTE: !!!untested!!! */
			fRet		    = TRUE;
			fPaired		  = FALSE;
			uiFlashWidth	= 8;
			break;

		case CFISETUP_2x08:					            /* does this ever happen? */
		case CFISETUP_1x08 | CFISETUP_2x08:			/* NOTE: !!!untested!!!   */
			fRet		    = TRUE;
			fPaired		  = TRUE;
			uiFlashWidth	= 16;
			break;

		case CFISETUP_1x16:					            /* does this ever happen?             */
		case CFISETUP_1x08 | CFISETUP_1x16:			/* single spansion16, single strata16 */
			fRet		    = TRUE;
			fPaired		  = FALSE;
			uiFlashWidth	= 16;
			break;

		case CFISETUP_2x16:					                        /* does this ever happen? */
		case CFISETUP_1x08 | CFISETUP_2x16:			            /* paired strata16        */
		case CFISETUP_1x08 | CFISETUP_1x16 | CFISETUP_2x16:	/* paired strata16        */
			fRet		    = TRUE;
			fPaired		  = TRUE;
			uiFlashWidth	= 32;
			break;

		case CFISETUP_1x32:					            /* does this ever happen? */
		case CFISETUP_1x08 | CFISETUP_1x32:			/* NOTE: !!!untested!!!   */
			fRet		    = TRUE;
			fPaired		  = FALSE;
			uiFlashWidth	= 32;
			break;

		default:
			fRet = FALSE;
			uprintf("!Unknown flash setup, please send this log to cthelen@hilscher.com with some info about your setup.\n");
			break;
		}

		if( fRet==TRUE )
		{
			/* set flash parameters */
			ptFlashDevice->uiWidth  = uiFlashWidth;
			ptFlashDevice->fPaired = fPaired;

			uprintf(".Found bits: $2, paired: $1\n", uiFlashWidth, fPaired);

			fRet = CFI_QueryFlashLayout(ptFlashDevice, pfnSetup);
		}
	}

	if( fRet==TRUE )
	{
		unsigned int uiCommandSet;
		
		/* Check if it is a supported type */
		uiCommandSet = ptFlashDevice->usVendorCommandSet;
		switch( uiCommandSet )
		{
		case CFI_FLASH_100_INTEL_STD:
		case CFI_FLASH_100_INTEL_EXT:
			DEBUGMSG(ZONE_VERBOSE, (".CFI_IdentifyFlash(): Intel command set detected.\n"));
			fRet = IntelIdentifyFlash(ptFlashDevice);
			break;

		case CFI_FLASH_100_AMD_STD:
		case CFI_FLASH_100_AMD_EXT:
			DEBUGMSG(ZONE_VERBOSE, (".CFI_IdentifyFlash(): AMD command set detected.\n"));
			fRet = SpansionIdentifyFlash(ptFlashDevice);
			break;     

		default:
			DEBUGMSG(ZONE_ERROR, ("!CFI_IdentifyFlash(): Error, unknown vendor command set: 0x$.\n", uiCommandSet));
			fRet = FALSE;
			break;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_IdentifyFlash(): fRet=0x$\n", fRet));

	return fRet;
}

