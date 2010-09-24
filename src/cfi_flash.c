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

#include <string.h>

#include "cfi_flash.h"

#include "netx_io_areas.h"
#include "strata.h"
#include "spansion.h"
#include "uprintf.h"


#if CFG_DEBUGMSG!=0
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
	CFI_SETUP_1x08		= 0x01,
	CFI_SETUP_2x08		= 0x02,
	CFI_SETUP_1x16		= 0x04,
	CFI_SETUP_2x16		= 0x08,
	CFI_SETUP_1x32		= 0x10
} CFI_SETUP_T;


typedef union
{
	unsigned char *puc;
	unsigned short *pus;
	unsigned long *pul;
	unsigned long ul;
} ADR_T;

typedef union
{
	volatile unsigned char *puc;
	volatile unsigned short *pus;
	volatile unsigned long *pul;
	volatile unsigned long ul;
} VADR_T;

// ///////////////////////////////////////////////////// 
//! Structure definition for FLASH width and pairing test cases
// ///////////////////////////////////////////////////// 
typedef struct tagCFI_CHECK_CONDITIONS
{
	BUS_WIDTH_T tBits;        /* Bus width for this pattern. */
	int fPaired;              /* Pairing of FLASHes for pattern. */
	unsigned int uiQueryLen;  /* Length of the pattern in bytes. */
	const char *szQuery;      /* Pattern to look for in memory at given offset. */
	CFI_SETUP_T tSetup;       /* Setup id of this config. */
} CFI_CHECK_CONDITIONS;


// ///////////////////////////////////////////////////// 
//! Structure used for identifying bus width and 
//! pairing of CFI FLASHes
// ///////////////////////////////////////////////////// 
static const CFI_CHECK_CONDITIONS s_atCFIChecks[] =
{
/* Only netX500, netX100 and netX50 support a 32bit memory interface. */
#if ASIC_TYP==500 || ASIC_TYP==100 || ASIC_TYP==50
//	{BUS_WIDTH_32Bit,  FALSE,  12,  "Q\0\0\0R\0\0\0Y\0\0\0",  CFI_SETUP_1x32 },  /* 1x 32Bit Flash */

	{BUS_WIDTH_32Bit,  TRUE,   12,  "Q\0Q\0R\0R\0Y\0Y\0",     CFI_SETUP_2x16 },  /* 2x 16Bit Flash */
#endif
//	{BUS_WIDTH_16Bit,  FALSE,  10,  "Q\0??R\0??Y\0",          CFI_SETUP_1x16 },  /* 1x 16Bit Flash */
	{BUS_WIDTH_16Bit,  FALSE,   6,  "Q\0R\0Y\0",              CFI_SETUP_1x16 },  /* 1x 16Bit Flash */

	{BUS_WIDTH_16Bit,  TRUE,    6,  "QQRRYY",                 CFI_SETUP_2x08 },  /* 2x 8Bit Flash */
	{ BUS_WIDTH_8Bit,  FALSE,   3,  "QRY",                    CFI_SETUP_1x08 }   /* 8 Bit Flash   */
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
	volatile unsigned char *pucFlash;
	const unsigned char *pucCmpBuf;
	unsigned char ucFlashData;
	unsigned char ucCmpData;


	DEBUGMSG(ZONE_FUNCTION, ("+CFIMemCmp(): pvFlash=0x%08x, pvCmpBuf=0x%08x, ulLen=%d\n", pvFlash, pvCmpBuf, ulLen));

	iRet = 0;

	pucFlash  = (volatile unsigned char*)pvFlash;
	pucCmpBuf = (const unsigned char*)pvCmpBuf;

	while( ulLen>0 )
	{
		ucCmpData = *(pucCmpBuf++);
		ucFlashData = *(pucFlash++);

		DEBUGMSG(ZONE_VERBOSE, (".CFIMemCmp(): Pattern: 0x%02x, Flash: 0x%02x.\n", ucCmpData, ucFlashData));

		if( ucCmpData!='?' && ucCmpData!=ucFlashData )
		{
			iRet = -1;
			break;
		}

		--ulLen;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFIMemCmp(): iRet=%d\n", iRet));

	return iRet;
}

// ///////////////////////////////////////////////////// 
//! Writes a command to the given flash with the indicated width and pairing
//!  \param pbFlashAddr Address inside flash, to write command to (ATTENTION: Alignment is not checked)
//!  \param bWidth Width of the FLASH 
//!  \param fPaired TRUE if two devices are paired to build one flash
//!  \param bCommand Command to write to FLASH
// ///////////////////////////////////////////////////// 
static void CFI_FlashWriteCommand(volatile unsigned char *pucFlashAddr, BUS_WIDTH_T tBits, int fPaired, unsigned int uiCommand)
{
	unsigned long ulValue;
	VADR_T tAdr;


	DEBUGMSG(ZONE_FUNCTION, ("+CFI_FlashWriteCommand(): pucFlashAddr=0x%08x, tBits=%d, fPaired=%d, uiCommand=0x%08x\n", pucFlashAddr, tBits, fPaired, uiCommand));

	/* set the address */
	tAdr.puc = pucFlashAddr;

	switch(tBits)
	{
	case BUS_WIDTH_8Bit:
		/* 8bits cannot be paired */
		*(tAdr.puc) = (unsigned char)uiCommand;
		break;

	case BUS_WIDTH_16Bit:
		ulValue = (unsigned long)uiCommand;
		if( fPaired!=0 )
		{
			ulValue |= ulValue << 8U;
		}
		*(tAdr.pus) = (unsigned short)ulValue;
		break;

	case BUS_WIDTH_32Bit:
		ulValue = uiCommand;
		if( fPaired!=0 )
		{
			ulValue |= ulValue << 16U;
		}
		*(tAdr.pul) = ulValue;
		break;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_FlashWriteCommand()\n"));
}


static int get_query_information(FLASH_DEVICE *ptFlashDevice, CFI_QUERY_INFORMATION *ptQueryInformation)
{
	int iResult;
	BUS_WIDTH_T tBits;
	VADR_T tVAdr;
	unsigned char *pucCnt;
	unsigned char *pucEnd;
	int iPaired;
	unsigned long ulValue;
	unsigned char ucFlash0;
	unsigned char ucFlash1;


	/* Assume success. */
	iResult = 0;

	tBits = ptFlashDevice->tBits;

	/* Get the source address. */
	tVAdr.puc = ptFlashDevice->pbFlashBase + (CFI_QUERY_INFO_OFFSET<<tBits);

	/* Get the destination start and end address. */
	pucCnt = (unsigned char*)ptQueryInformation;
	pucEnd = pucCnt + sizeof(CFI_QUERY_INFORMATION);

	iPaired = ptFlashDevice->fPaired;

	/* Copy the data and check paired information. */
	switch(tBits)
	{
	case BUS_WIDTH_8Bit:
		do
		{
			*(pucCnt++) = *(tVAdr.puc++);
		} while( pucCnt<pucEnd );
		break;

	case BUS_WIDTH_16Bit:
		do
		{
			ulValue = *(tVAdr.pus++);
			ucFlash0 = (unsigned char)(ulValue&0xffU);
			if( iPaired!=0 )
			{
				ucFlash1 = (unsigned char)((ulValue>>8)&0xffU);
				if( ucFlash0!=ucFlash1 )
				{
					DEBUGMSG(ZONE_ERROR, ("The paired flashes do not match! This is not supported.\n"));
					iResult = 1;
					break;
				}
			}
			*(pucCnt++) = ucFlash0;

		} while( pucCnt<pucEnd );
		break;

	case BUS_WIDTH_32Bit:
		do
		{
			ulValue = *(tVAdr.pul++);
			ucFlash0 = (unsigned char)(ulValue&0xffU);
			ucFlash1 = (unsigned char)((ulValue>>16)&0xffU);
			if( iPaired!=0 )
			{
				if( ucFlash0!=ucFlash1 )
				{
					DEBUGMSG(ZONE_ERROR, ("The paired flashes do not match! This is not supported.\n"));
					iResult = 1;
					break;
				}
			}
			*(pucCnt++) = ucFlash0;
		} while( pucCnt<pucEnd );
		break;
	}

	hexdump(ptQueryInformation, sizeof(CFI_QUERY_INFORMATION));

	return iResult;
}

static int CFI_QueryFlashLayout(FLASH_DEVICE *ptFlashDevice, const PARFLASH_CONFIGURATION_T *ptCfg)
{
	volatile unsigned char *pucFlashBase;
	CFI_QUERY_INFORMATION tQueryInformation;
	unsigned long ulFlashSize = 0;
	unsigned long ulCurSector = 0;
	unsigned long ulCurOffset = 0;
	unsigned int uiCnt;
	int fRet;
	BUS_WIDTH_T tBits;
	int fPaired;


	DEBUGMSG(ZONE_FUNCTION, ("+CFI_QueryFlashLayout(): ptFlashDevice=0x%08x\n", ptFlashDevice));

	pucFlashBase = ptFlashDevice->pbFlashBase;
	tBits = ptFlashDevice->tBits;
	fPaired = ptFlashDevice->fPaired;

	ptFlashDevice->pfnSetup(ptCfg, tBits);
	CFI_FlashWriteCommand(pucFlashBase, tBits, fPaired, READ_ARRAY_CMD);

	/* Enter Query mode */
	CFI_FlashWriteCommand(pucFlashBase + (READ_QUERY_CMD_OFFSET<<tBits), tBits, fPaired, READ_QUERY_CMD);

	/* Copy the query information to a local copy. */
	fRet = get_query_information(ptFlashDevice, &tQueryInformation);
	if( fRet==0 )
	{
		/* check byte QRY pattern, to see if flash has entered valid CFI Query mode */
		DEBUGMSG(ZONE_VERBOSE, (".CFI_QueryFlashLayout(): abCfiId=[%02x, %02x, %02x]\n", tQueryInformation.abQueryIdent[0], tQueryInformation.abQueryIdent[1], tQueryInformation.abQueryIdent[2]));

		if( tQueryInformation.abQueryIdent[0]=='Q' && tQueryInformation.abQueryIdent[1]=='R' && tQueryInformation.abQueryIdent[2]=='Y' )
		{
			DEBUGMSG(ZONE_VERBOSE, (".CFI_QueryFlashLayout(): Ok, QRY magic found.\n"));

			int iCurRegion = 0;

			ulFlashSize = 1U << tQueryInformation.bDeviceSize;

			if( fPaired )
			{
				ulFlashSize *= 2;
			}

			ptFlashDevice->ulFlashSize   = ulFlashSize;

			/* cycle through geometry options, until all blocks are evaluated */
			for(iCurRegion = 0; iCurRegion < tQueryInformation.bEraseBlockRegions; iCurRegion++)
			{
				unsigned long  ulBlockInfo = tQueryInformation.aulEraseBlockInformations[ulCurSector];
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

			ptFlashDevice->usVendorCommandSet   = tQueryInformation.usVendorCommandSet;
			ptFlashDevice->ulMaxBufferWriteSize = 1U << tQueryInformation.usMaxBufferWriteSize;

			fRet = TRUE;
		}
		else
		{
			fRet = FALSE;
			DEBUGMSG(ZONE_ERROR, ("!CFI_QueryFlashLayout(): Error, no QRY magic found.\n"));
		}
	}

	/* reset flash to read mode */
	CFI_FlashWriteCommand(pucFlashBase, tBits, fPaired, READ_ARRAY_CMD);

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_QueryFlashLayout(): fRet=%d\n", fRet));

	return fRet;
}


// ///////////////////////////////////////////////////// 
//! Identifies a CFI compliant FLASH device
//! This routine will enter all data into the ptFlashDevice structure
//! that can be read from FLASH.
//!  \param ptFlashDevice Returned FALSH info on success. Base address pointer must be inserted before calling this function
//!  \return TRUE if identified successfully
// ///////////////////////////////////////////////////// 
int CFI_IdentifyFlash(FLASH_DEVICE* ptFlashDevice, PARFLASH_CONFIGURATION_T *ptCfg)
{
	int             fRet         = FALSE;
	int             fPaired;
	BUS_WIDTH_T tBits;
	int             iPaired;
	unsigned int    uiCnt;
	unsigned char   *pbFlashBase;
	unsigned long   ulDetectedTypes;


	DEBUGMSG(ZONE_FUNCTION, ("+CFI_IdentifyFlash(): ptFlashDevice=0x%08x\n", ptFlashDevice));

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
			tBits = s_atCFIChecks[uiCnt].tBits;
			iPaired = s_atCFIChecks[uiCnt].fPaired;
			DEBUGMSG(ZONE_VERBOSE, (".Trying  bits: %02d, paired: %d\n", 8U<<tBits, iPaired));

			/* set bus width to query size */
			ptFlashDevice->pfnSetup(ptCfg, tBits);

			/* try to switch all possible combinations to array read mode */
			CFI_FlashWriteCommand(pbFlashBase,  BUS_WIDTH_8Bit, FALSE, READ_ARRAY_CMD);
			CFI_FlashWriteCommand(pbFlashBase, BUS_WIDTH_16Bit, TRUE,  READ_ARRAY_CMD);
			CFI_FlashWriteCommand(pbFlashBase, BUS_WIDTH_32Bit, TRUE,  READ_ARRAY_CMD);

			CFI_FlashWriteCommand(pbFlashBase + (READ_QUERY_CMD_OFFSET<<tBits), tBits, iPaired, READ_QUERY_CMD);

			if(CFIMemCmp(pbFlashBase + (CFI_QUERY_INFO_OFFSET<<tBits),
			             s_atCFIChecks[uiCnt].szQuery,
			             s_atCFIChecks[uiCnt].uiQueryLen) == 0)
			{
				ulDetectedTypes |= s_atCFIChecks[uiCnt].tSetup;
				DEBUGMSG(ZONE_VERBOSE, (".Ok, found magic!\n"));
			}
		}

		DEBUGMSG(ZONE_VERBOSE, (".Detection state: 0x%08x\n", ulDetectedTypes));

		/* reset found flashes to read mode */
		CFI_FlashWriteCommand(pbFlashBase,  BUS_WIDTH_8Bit, FALSE, READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pbFlashBase, BUS_WIDTH_16Bit, TRUE,  READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pbFlashBase, BUS_WIDTH_32Bit, TRUE,  READ_ARRAY_CMD);

		switch( ulDetectedTypes )
		{
		case CFI_SETUP_1x08:                                    /* NOTE: !!!untested!!! */
			fRet     = TRUE;
			fPaired  = FALSE;
			tBits    = BUS_WIDTH_8Bit;
			break;

		case CFI_SETUP_2x08:                                    /* does this ever happen? */
		case CFI_SETUP_1x08 | CFI_SETUP_2x08:                   /* NOTE: !!!untested!!!   */
			fRet     = TRUE;
			fPaired  = TRUE;
			tBits    = BUS_WIDTH_16Bit;
			break;

		case CFI_SETUP_1x16:                                    /* netx10 spansion16 */
		case CFI_SETUP_1x08 | CFI_SETUP_1x16:                   /* single spansion16, single strata16 */
			fRet     = TRUE;
			fPaired  = FALSE;
			tBits    = BUS_WIDTH_16Bit;
			break;

		case CFI_SETUP_2x16:                                    /* does this ever happen? */
		case CFI_SETUP_1x08 | CFI_SETUP_2x16:                   /* paired strata16        */
		case CFI_SETUP_1x08 | CFI_SETUP_1x16 | CFI_SETUP_2x16:  /* paired strata16        */
			fRet     = TRUE;
			fPaired  = TRUE;
			tBits    = BUS_WIDTH_32Bit;
			break;

		case CFI_SETUP_1x32:                                    /* does this ever happen? */
		case CFI_SETUP_1x08 | CFI_SETUP_1x32:                   /* NOTE: !!!untested!!!   */
			fRet     = TRUE;
			fPaired  = FALSE;
			tBits    = BUS_WIDTH_32Bit;
			break;

		default:
			fRet = FALSE;
			DEBUGMSG(ZONE_VERBOSE, ("!Unknown flash setup!\n"));
			break;
		}

		if( fRet==TRUE )
		{
			/* set flash parameters */
			ptFlashDevice->tBits = tBits;
			ptFlashDevice->fPaired = fPaired;

			DEBUGMSG(ZONE_VERBOSE, (".Found bits: %02d, paired: %d\n", 8U<<tBits, fPaired));

			fRet = CFI_QueryFlashLayout(ptFlashDevice, ptCfg);
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
					DEBUGMSG(ZONE_ERROR, ("!CFI_IdentifyFlash(): Error, unknown vendor command set: 0x%08x.\n", uiCommandSet));
					fRet = FALSE;
					break;
				}
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_IdentifyFlash(): fRet=%d\n", fRet));

	return fRet;
}

