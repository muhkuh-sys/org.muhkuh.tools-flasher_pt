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

#include "cfi_flash.h"

#include "netx_io_areas.h"
#include "strata.h"
#include "spansion.h"
#include "uprintf.h"


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


typedef struct tagCFI_CHECK_CONDITIONS
{
	BUS_WIDTH_T tBits;              /* Bus width for this pattern. */
	int fPaired;                    /* Pairing of FLASHes for pattern. */
	unsigned int uiQueryLen;        /* Length of the pattern in bytes. */
	const char *szQuery;            /* Pattern to look for in memory at given offset. */
	CFI_SETUP_T tSetup;             /* Setup id of this config. */
} CFI_CHECK_CONDITION_T;


typedef struct
{
	unsigned long ulCondition;      /* A combination of several CFI_SETUP_T values. */
	int iPaired;                    /* TRUE if the setup is made of 2 flashes. */
	BUS_WIDTH_T tBits;              /* Bus width of the flash connection. */
	CFI_SETUP_T tSetup;             /* Bus width and paired information. */
} CFI_SETUP_CONDITION_T;


static const CFI_CHECK_CONDITION_T s_atCFIChecks[] =
{
/* Only netX500 and netX50 support a 32bit memory interface. */
#if ASIC_TYP==ASIC_TYP_NETX500 || ASIC_TYP==ASIC_TYP_NETX50
/*	{BUS_WIDTH_32Bit,  FALSE,  12,  "Q\0\0\0R\0\0\0Y\0\0\0",  CFI_SETUP_1x32 }, */

	{BUS_WIDTH_32Bit,  TRUE,   12,  "Q\0Q\0R\0R\0Y\0Y\0",     CFI_SETUP_2x16 },
#endif
/*	{BUS_WIDTH_16Bit,  FALSE,  10,  "Q\0??R\0??Y\0",          CFI_SETUP_1x16 }, */
	{BUS_WIDTH_16Bit,  FALSE,   6,  "Q\0R\0Y\0",              CFI_SETUP_1x16 },
	
	{BUS_WIDTH_16Bit,  TRUE,    6,  "QQRRYY",                 CFI_SETUP_2x08 },
	{ BUS_WIDTH_8Bit,  FALSE,   3,  "QRY",                    CFI_SETUP_1x08 }
};


static const CFI_SETUP_CONDITION_T s_atCFISetupConditions[] =
{
	{CFI_SETUP_1x08,
	                 FALSE,  BUS_WIDTH_8Bit,   CFI_SETUP_1x08 },    /* NOTE: !!!untested!!! */

	{CFI_SETUP_2x08,
	                  TRUE,  BUS_WIDTH_16Bit,  CFI_SETUP_2x08 },    /* NOTE: !!!untested!!! */
	                  
	{CFI_SETUP_1x16,
	                 FALSE,  BUS_WIDTH_16Bit,  CFI_SETUP_1x16 },    /* netx10 spansion16 */

	{CFI_SETUP_1x08 | CFI_SETUP_1x16,
	                 FALSE,  BUS_WIDTH_16Bit,  CFI_SETUP_1x16 },    /* single spansion16, single strata16 */

	{CFI_SETUP_2x16,
	                  TRUE,  BUS_WIDTH_32Bit,  CFI_SETUP_2x16 },    /* NOTE: !!!untested!!! */

	{CFI_SETUP_1x08 | CFI_SETUP_2x16,
	                  TRUE,  BUS_WIDTH_32Bit,  CFI_SETUP_2x16 },    /* paired strata16 */

	{CFI_SETUP_1x08 | CFI_SETUP_1x16 | CFI_SETUP_2x16,
	                  TRUE,  BUS_WIDTH_32Bit,  CFI_SETUP_2x16 },    /* paired strata16 */

	{CFI_SETUP_1x32,
	                 FALSE,  BUS_WIDTH_32Bit,  CFI_SETUP_1x32 },    /* NOTE: !!!untested!!! */

	{CFI_SETUP_1x08 | CFI_SETUP_1x32,
	                 FALSE,  BUS_WIDTH_32Bit,  CFI_SETUP_1x32 }     /* NOTE: !!!untested!!! */
};


#define ARRAY_SIZE(a)   (sizeof(a) / sizeof(a[0]))

/*---------------------------------------------------------------------------
   Compares memory buffers for CFI detection routines.
   It uses '?' as wildcard
     \param pvFlash Pointer to flash address to verify
     \param pvCmpBuf Buffer containing expected flash content
            (This buffer may contain '?' placeholder)
     \param ulLen Length of comparison
     \return 0 if equal, -1 on mismatch
---------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------
    Writes a command to the given flash with the indicated width and pairing
     \param pbFlashAddr Address inside flash, to write command to (ATTENTION: Alignment is not checked)
     \param bWidth Width of the FLASH 
     \param fPaired TRUE if two devices are paired to build one flash
     \param bCommand Command to write to FLASH
---------------------------------------------------------------------------*/
static void CFI_FlashWriteCommand(volatile unsigned char *pucFlashAddr, size_t sizOffset, CFI_SETUP_T tSetup, unsigned int uiCommand)
{
	VADR_T tAdr;


	DEBUGMSG(ZONE_FUNCTION, ("+CFI_FlashWriteCommand(): pucFlashAddr=0x%08x, sizOffset=%d, tSetup=%d, uiCommand=0x%08x\n", pucFlashAddr, sizOffset, tSetup, uiCommand));

	/* set the address */
	tAdr.puc = pucFlashAddr;

	switch(tSetup)
	{
	case CFI_SETUP_1x08:
		DEBUGMSG(ZONE_FUNCTION, (".CFI_FlashWriteCommand() 1x08: 0x%08x <- 0x%08x\n", &tAdr.puc[sizOffset], (unsigned char)uiCommand));
		tAdr.puc[sizOffset] = (unsigned char)uiCommand;
		break;

	case CFI_SETUP_2x08:
		DEBUGMSG(ZONE_FUNCTION, (".CFI_FlashWriteCommand() 2x08: 0x%08x <- 0x%08x\n", &tAdr.pus[sizOffset], (unsigned short)(uiCommand|(uiCommand<<8U))));
		tAdr.pus[sizOffset] = (unsigned short)(uiCommand|(uiCommand<<8U));
		break;

	case CFI_SETUP_1x16:
		DEBUGMSG(ZONE_FUNCTION, (".CFI_FlashWriteCommand() 1x16: 0x%08x <- 0x%08x\n", &tAdr.pus[sizOffset], (unsigned short)uiCommand));
		tAdr.pus[sizOffset] = (unsigned short)uiCommand;
		break;

	case CFI_SETUP_2x16:
		DEBUGMSG(ZONE_FUNCTION, (".CFI_FlashWriteCommand() 2x16: 0x%08x <- 0x%08x\n", &tAdr.pul[sizOffset], uiCommand | (uiCommand<<16U)));
		tAdr.pul[sizOffset] = uiCommand | (uiCommand<<16U);
		break;

	case CFI_SETUP_1x32:
		DEBUGMSG(ZONE_FUNCTION, (".CFI_FlashWriteCommand() 1x32: 0x%08x <- 0x%08x\n", &tAdr.pul[sizOffset], uiCommand));
		tAdr.pul[sizOffset] = uiCommand;
		break;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_FlashWriteCommand()\n"));
}


static const CFI_SETUP_CONDITION_T *get_setup_from_condition(unsigned long ulCondition)
{
	const CFI_SETUP_CONDITION_T *ptCnt;
	const CFI_SETUP_CONDITION_T *ptEnd;
	const CFI_SETUP_CONDITION_T *ptHit;


	ptCnt = s_atCFISetupConditions;
	ptEnd = s_atCFISetupConditions + sizeof(s_atCFISetupConditions)/sizeof(CFI_SETUP_CONDITION_T);
	ptHit = NULL;
	while(ptCnt<ptEnd)
	{
		if( ptCnt->ulCondition==ulCondition )
		{
			ptHit = ptCnt;
			break;
		}
		else
		{
			++ptCnt;
		}
	}

	return ptHit;
}


/*---------------------------------------------------------------------------
	Reads a byte from flash in CFI mode.
	Reads a byte from offset sizCfiOffset of the flash to *pucDest, 
	adjusting for 8/16/32 bits and paired/nonpaired.
	CFI mode must be enabled.
	If paired flashes are used, the bytes read from the two flashes must be 
	identical.

	\param ptFlashDevice pointer to flash description
	\param pucDest       destination address
	\param sizCFIOffset  byte offset in a single flash, such that QRY is at 0x10, 0x11, 0x12
	\return TRUE if successful, FALSE otherwise
---------------------------------------------------------------------------*/

static int CFI_getbyte(FLASH_DEVICE_T *ptFlashDevice, unsigned char *pucDest, size_t sizCfiOffset)
{
	int iResult;
	VADR_T tVAdr;
	unsigned long ulValue;
	unsigned char ucFlash0;
	unsigned char ucFlash1;

	/* Assume success. */
	iResult = TRUE;

	/* get the base address */
	tVAdr.puc = ptFlashDevice->pucFlashBase;

	/* Copy the data and check paired information. */
	switch(ptFlashDevice->tBits)
	{
	case BUS_WIDTH_8Bit:
		tVAdr.puc += sizCfiOffset;
		ulValue = *(tVAdr.puc);
		ucFlash0 = (unsigned char)(ulValue&0xffU);
		ucFlash1 = (unsigned char) 0; /* avoid 'uninitialized' warning */
		break;

	case BUS_WIDTH_16Bit:
		tVAdr.pus += sizCfiOffset;
		ulValue = *(tVAdr.pus);
		ucFlash0 = (unsigned char)(ulValue&0xffU);
		ucFlash1 = (unsigned char)((ulValue>>8)&0xffU);
		break;
	
	case BUS_WIDTH_32Bit:
		tVAdr.pul += sizCfiOffset;
		ulValue = *(tVAdr.pul);
		ucFlash0 = (unsigned char)(ulValue&0xffU);
		ucFlash1 = (unsigned char)((ulValue>>16)&0xffU);
		break;

	default:
		uprintf("!CFI_getbyte: illegal bus width\n");
		iResult = FALSE; // Error: illegal bus width
	}
	
	if (iResult == TRUE) {
		DEBUGMSG(ZONE_VERBOSE, (".CFI_getbyte() offset = 0x%08x dest = %08x byte = %02x\n", 
			sizCfiOffset, pucDest, ucFlash0));
	
		if( ptFlashDevice->fPaired!=0 && ucFlash0!=ucFlash1 )
		{
			uprintf("!The paired flashes do not match! This is not supported.\n");
			uprintf("!address = 0x%08x ulValue=0x%08x\n", tVAdr.pul, ulValue);
			iResult = FALSE; // Error: paired flashes do not match
		}
		else
		{
			*pucDest = ucFlash0;
		}
	}
	
	return iResult;
}


/*---------------------------------------------------------------------------
	Copies bytes from flash in CFI mode.
	Copies size bytes starting at offset sizCfiOffset in flash to pucDest,
	adjusting for 8/16/32 bits and paired/nonpaired.
	CFI mode must be enabled.
	If paired flashes are used, the bytes read from the two flashes must be 
	identical.

	\param ptFlashDevice pointer to flash description
	\param pucDest       destination address
	\param sizCFIOffset  byte offset in a single flash, such that QRY is at 0x10, 0x11, 0x12
	\param size          number of bytes to copy
	\return TRUE if successful, FALSE otherwise
---------------------------------------------------------------------------*/

static int CFI_memcpy(FLASH_DEVICE_T *ptFlashDevice, unsigned char *pucDest, size_t sizCfiOffset, size_t size)
{
	int iResult;
	unsigned char *pucEnd;
	
	DEBUGMSG(ZONE_FUNCTION, ("+CFI_memcpy() src offset = 0x%08x dest addr= %08x size = %08x\n", 
		sizCfiOffset, pucDest, size));
		
	/* assume success */
	iResult = TRUE;
	
	/* Get the destination end address. */
	pucEnd = pucDest + size;
	
	while( pucDest<pucEnd && iResult == TRUE)
	{
		iResult = CFI_getbyte(ptFlashDevice, pucDest, sizCfiOffset);
		++sizCfiOffset;
		++pucDest;
	}
	
	DEBUGMSG(ZONE_FUNCTION, ("-CFI_memcpy() result = %08x", iResult));
	
	return iResult;
}



static unsigned long detect_setup_condition(FLASH_DEVICE_T* ptFlashDevice, PARFLASH_CONFIGURATION_T *ptCfg)
{
	unsigned char *pucFlashBase;
	unsigned long ulDetectedTypes;
	const CFI_CHECK_CONDITION_T *ptCnt;
	const CFI_CHECK_CONDITION_T *ptEnd;
	BUS_WIDTH_T tBits;
	CFI_SETUP_T tSetup;
	int iCmpResult;


	pucFlashBase  = ptFlashDevice->pucFlashBase;
	
	/* check if we find patterns of QRY response to identify flash width and pairing */
	ulDetectedTypes = 0;
	ptCnt = s_atCFIChecks;
	ptEnd = s_atCFIChecks + sizeof(s_atCFIChecks)/sizeof(s_atCFIChecks[0]);
	while(ptCnt<ptEnd)
	{
		tBits = ptCnt->tBits;
		tSetup = ptCnt->tSetup;
		uprintf(".Trying  bits: %02d, paired: %d\n", 8U<<tBits, ptCnt->fPaired);

		/* set bus width to query size */
		ptFlashDevice->pfnSetup(ptCfg, tBits);

		/* try to switch all possible combinations to array read mode */
		CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, CFI_SETUP_1x08,  READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, CFI_SETUP_2x08,  READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, CFI_SETUP_2x16,  READ_ARRAY_CMD);
		CFI_FlashWriteCommand(pucFlashBase, READ_QUERY_CMD_OFFSET, tSetup, READ_QUERY_CMD);
		
		iCmpResult = CFIMemCmp(pucFlashBase + (CFI_QUERY_INFO_OFFSET<<tBits), ptCnt->szQuery, ptCnt->uiQueryLen);
		if( iCmpResult==0 )
		{
			ulDetectedTypes |= ptCnt->tSetup;
			uprintf(".Ok, found magic!\n");
		}

		++ptCnt;
	}

	/* reset found flashes to read mode */
	CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, CFI_SETUP_1x08, READ_ARRAY_CMD);
	CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, CFI_SETUP_2x08, READ_ARRAY_CMD);
	CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, CFI_SETUP_2x16, READ_ARRAY_CMD);

	uprintf(".Detection state: 0x%08x\n", ulDetectedTypes);
	return ulDetectedTypes;
}


static int read_geometry(FLASH_DEVICE_T *ptFlashDevice, CFI_QUERY_INFORMATION *ptQueryInformation)
{
	int iResult;
	unsigned int uiPairedShift;
	unsigned int uiEraseBlockRegions;
	unsigned int uiEraseBlockRegionsCnt;
	unsigned long ulBlockInfo;
	unsigned long ulBlocks;
	unsigned long ulBlockSize;
	unsigned long ulBlockByteSize;
	unsigned long ulCurSector;
	unsigned long ulCurOffset;


	DEBUGMSG(ZONE_FUNCTION, ("+read_geometry(): ptFlashDevice=0x%08x, ptQueryInformation=0x%08x\n", ptFlashDevice, ptQueryInformation));

	/* Be optimistic. */
	iResult = TRUE;

	/* Generate the size multiplier for paired flashes. */
	if( ptFlashDevice->fPaired!=0 )
	{
		uiPairedShift = 1;
	}
	else
	{
		uiPairedShift = 0;
	}

	/* Get the number of erase blocks. */
	uiEraseBlockRegions = ptQueryInformation->bEraseBlockRegions;
	if( uiEraseBlockRegions>MAX_SECTORS )
	{
		iResult = FALSE;
	}
	else
	{
		/* Init the sector counter and offset. */
		ulCurSector = 0;
		ulCurOffset = 0;

		/* Loop over all geometry infos. */
		uiEraseBlockRegionsCnt = 0;
		while( uiEraseBlockRegionsCnt<uiEraseBlockRegions )
		{
			/* Extract the number of blocks and their size from the info dword. */
			ulBlockInfo = ptQueryInformation->aulEraseRegionInfo[uiEraseBlockRegionsCnt];
			++uiEraseBlockRegionsCnt;

			/* Get the number of blocks in this entry. */
			ulBlocks = (ulBlockInfo & 0xFFFFU) + 1U;

			/* Get the size of each block. */
			ulBlockSize   = ulBlockInfo >> 16U;
			ulBlockSize <<= uiPairedShift;
			DEBUGMSG(ZONE_VERBOSE, (".read_geometry(): packed: 0x%08x, blocks: 0x%04x, pages: 0x%08x\n", ulBlockInfo, ulBlocks, ulBlockSize));

			/* Loop over all blocks. NOTE: ulBlocks can not be 0 here. */
			do
			{
				/* Is still enough space in the sector table? */
				if( ulCurSector>MAX_SECTORS )
				{
					/* No -> do not process more sectors. */
					iResult = FALSE;
					break;
				}

				/* Get the size of the erase block in bytes. */
				if( ulBlockSize==0 )
				{
					ulBlockByteSize = 0x80;
				}
				else
				{
					ulBlockByteSize = ulBlockSize * 0x100U;
				}

				ptFlashDevice->atSectors[ulCurSector].ulOffset = ulCurOffset;
				ptFlashDevice->atSectors[ulCurSector].ulSize   = ulBlockByteSize;

				DEBUGMSG(ZONE_VERBOSE, (".read_geometry(): sector %d, offset: 0x%08x, size: 0x%08x\n", ulCurSector, ulCurOffset, ulBlockByteSize));

				++ulCurSector;

				ulCurOffset += ulBlockByteSize;
			} while( --ulBlocks>0 );
		}

		ptFlashDevice->ulSectorCnt = ulCurSector;
	}

	DEBUGMSG(ZONE_FUNCTION, ("-read_geometry(): iResult=%d\n", iResult));
	return iResult;
}


/*---------------------------------------------------------------------------
	Reads and evaluates CFI data if available:
	
	- command set
	- flash size
	- sector layout
	- write buffer size
	
	\param ptFlashDevice pointer to flash description
	\param ptCfg         unit/chip select/allowed bit widths    
	\param tBits         bit width
	\param fPaired       flag indicating if paired flashes are used
	\return TRUE if successful, FALSE otherwise

---------------------------------------------------------------------------*/

static int query_flash_layout(FLASH_DEVICE_T *ptFlashDevice, const PARFLASH_CONFIGURATION_T *ptCfg, BUS_WIDTH_T tBits, int fPaired)
{
	int iResult;
	
	CFI_QUERY_INFORMATION tQueryInformation;
	unsigned long ulFlashSize;

	volatile unsigned char *pucFlashBase;
	CFI_SETUP_T tSetup;
	unsigned char* pucEraseInfo;
	size_t sizEraseInfoSize;

	DEBUGMSG(ZONE_FUNCTION, ("+query_flash_layout(): ptFlashDevice=0x%08x\n", ptFlashDevice));
	
	pucFlashBase = ptFlashDevice->pucFlashBase;
	tSetup = ptFlashDevice->tSetup;

	ptFlashDevice->pfnSetup(ptCfg, tBits);

	/* reset flash to read mode */
	CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, tSetup, READ_ARRAY_CMD);

	/* Enter Query mode */
	CFI_FlashWriteCommand(pucFlashBase, READ_QUERY_CMD_OFFSET, tSetup, READ_QUERY_CMD);

	/* Copy the query information to a local copy. */
	iResult = CFI_memcpy(ptFlashDevice, (unsigned char*)&tQueryInformation, CFI_QUERY_INFO_OFFSET, CFI_QUERY_BASE_SIZE);
	uprintf(".get_query_information(): CFI base data:\n");
	hexdump((unsigned char*)&tQueryInformation, CFI_QUERY_BASE_SIZE);

	if( iResult==TRUE )
	{
		/* check byte QRY pattern, to see if flash has entered valid CFI Query mode */
		uprintf(".query_flash_layout(): abCfiId=[%02x, %02x, %02x]\n",
			 tQueryInformation.abQueryIdent[0], 
			 tQueryInformation.abQueryIdent[1], 
			 tQueryInformation.abQueryIdent[2]);
		if( tQueryInformation.abQueryIdent[0]=='Q' && 
			tQueryInformation.abQueryIdent[1]=='R' && 
			tQueryInformation.abQueryIdent[2]=='Y' )
		{
			uprintf(".query_flash_layout(): Ok, QRY magic found.\n");

			ulFlashSize = 1U << tQueryInformation.bDeviceSize;
			if( fPaired )
			{
				ulFlashSize *= 2;
			}
			ptFlashDevice->ulFlashSize   = ulFlashSize;
			ptFlashDevice->usVendorCommandSet   = tQueryInformation.usVendorCommandSet;
			ptFlashDevice->ulMaxBufferWriteSize = 1U << tQueryInformation.usMaxBufferWriteSize;

			
			/* read & decode erase region info */
			pucEraseInfo = (unsigned char*)&tQueryInformation.aulEraseRegionInfo;
			sizEraseInfoSize = ((size_t)tQueryInformation.bEraseBlockRegions) * 4;
			iResult = CFI_memcpy(ptFlashDevice, pucEraseInfo, CFI_QUERY_INFO_OFFSET + CFI_QUERY_BASE_SIZE, sizEraseInfoSize);
			uprintf(".get_query_information(): CFI erase block region info:\n");
			hexdump(pucEraseInfo, sizEraseInfoSize);
			
			if( iResult==TRUE )
			{
				iResult = read_geometry(ptFlashDevice, &tQueryInformation);
			}
			
			ptFlashDevice->fPriExtQueryValid = 0;

			if( iResult==TRUE && 
				tQueryInformation.usPrimaryAlgorithmExt != 0 &&
				(tQueryInformation.usVendorCommandSet == CFI_FLASH_100_AMD_STD ||
					tQueryInformation.usVendorCommandSet == CFI_FLASH_100_AMD_EXT)
				)
			{
			/* If there is an extended query entry, copy the base part 
			   (the version-independent part, but Spansion-specific);
			   We currently only use the extquery data for Spansion flashes, and
			   We don't need the remainder at the moment. */
				iResult = CFI_memcpy(ptFlashDevice, 
					(unsigned char*) &ptFlashDevice->tPriExtQuery, 
					tQueryInformation.usPrimaryAlgorithmExt, 
					CFI_SPANSION_EXTQUERY_BASE_SIZE);
				
				if( iResult==TRUE &&
					ptFlashDevice->tPriExtQuery.tSpansion.abExtQueryIdent[0] == 'P' &&
					ptFlashDevice->tPriExtQuery.tSpansion.abExtQueryIdent[1] == 'R' &&
					ptFlashDevice->tPriExtQuery.tSpansion.abExtQueryIdent[2] == 'I')
				{
					uprintf("CFI_QueryFlashLayout(): found extended query structure AMD V%c.%c\n",
						ptFlashDevice->tPriExtQuery.tSpansion.bMajorVer, 
						ptFlashDevice->tPriExtQuery.tSpansion.bMinorVer);
					ptFlashDevice->fPriExtQueryValid = 1;
				}
				else
				{
					uprintf("CFI_QueryFlashLayout(): Could not read extended query structure\n");
				}
			}
			
		}
		else
		{
			iResult = FALSE;
			uprintf("!query_flash_layout(): Error, no QRY magic found.\n");
		}
	}
	
	/* reset flash to read mode */
	CFI_FlashWriteCommand(pucFlashBase, READ_ARRAY_OFFSET, tSetup, READ_ARRAY_CMD);

	DEBUGMSG(ZONE_FUNCTION, ("-query_flash_layout(): iResult=%d\n", iResult));
	return iResult;
}


/*---------------------------------------------------------------------------
    Identifies a CFI compliant FLASH device
    This routine will enter all data into the ptFlashDevice structure
    that can be read from FLASH.
     \param ptFlashDevice Returned FALSH info on success. Base address pointer must be inserted before calling this function
     \return TRUE if identified successfully
---------------------------------------------------------------------------*/
int CFI_IdentifyFlash(FLASH_DEVICE_T* ptFlashDevice, PARFLASH_CONFIGURATION_T *ptCfg)
{
	int iResult;
	unsigned long ulSetupCondition;
	const CFI_SETUP_CONDITION_T *ptSetupConditions;
	unsigned int uiCommandSet;
	BUS_WIDTH_T tBits;
	int iPaired;

	DEBUGMSG(ZONE_FUNCTION, ("+CFI_IdentifyFlash(): ptFlashDevice=0x%08x\n", ptFlashDevice));

	if( ptFlashDevice==NULL )
	{
		iResult = FALSE;
	}
	else
	{
		ulSetupCondition = detect_setup_condition(ptFlashDevice, ptCfg);

		ptSetupConditions = get_setup_from_condition(ulSetupCondition);
		if( ptSetupConditions==NULL )
		{
			iResult = FALSE;
		}
		else
		{
			tBits = ptSetupConditions->tBits;
			iPaired = ptSetupConditions->iPaired;

			/* set flash parameters */
			ptFlashDevice->tBits = tBits;
			ptFlashDevice->fPaired = iPaired;
			ptFlashDevice->tSetup = ptSetupConditions->tSetup;

			uprintf(".Found bits: %02d, paired: %d\n", 8U<<tBits, iPaired);

			iResult = query_flash_layout(ptFlashDevice, ptCfg, tBits, iPaired);
			if( iResult==TRUE )
			{
				/* Check if it is a supported type */
				uiCommandSet = ptFlashDevice->usVendorCommandSet;
				switch( uiCommandSet )
				{
				case CFI_FLASH_100_INTEL_STD:
				case CFI_FLASH_100_INTEL_EXT:
					uprintf(".CFI_IdentifyFlash(): Intel command set detected.\n");
					iResult = IntelIdentifyFlash(ptFlashDevice);
					break;

				case CFI_FLASH_100_AMD_STD:
				case CFI_FLASH_100_AMD_EXT:
					uprintf(".CFI_IdentifyFlash(): AMD command set detected.\n");
					iResult = SpansionIdentifyFlash(ptFlashDevice);
					break;     

				default:
					uprintf("!CFI_IdentifyFlash(): Error, unknown vendor command set: 0x%08x.\n", uiCommandSet);
					iResult = FALSE;
					break;
				}
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, ("-CFI_IdentifyFlash(): iResult=%d\n", iResult));
	return iResult;
}

const SECTOR_INFO_T *cfi_find_matching_sector(const FLASH_DEVICE_T *ptFlashDescription, unsigned long ulAddress)
{
	size_t sizIndex = cfi_find_matching_sector_index(ptFlashDescription, ulAddress);
	if (sizIndex != 0xffffffffU)
	{
		return &ptFlashDescription->atSectors[sizIndex];
	}
	else
	{
		return NULL;
	}
}

size_t cfi_find_matching_sector_index(const FLASH_DEVICE_T *ptFlashDescription, unsigned long ulAddress)
{
	const SECTOR_INFO_T *ptSec = ptFlashDescription->atSectors;
	size_t sizIndex = 0;
	
	while(sizIndex < ptFlashDescription->ulSectorCnt)
	{
		if (ptSec->ulOffset <= ulAddress && ulAddress < (ptSec->ulOffset + ptSec->ulSize))
		{
			return sizIndex;
		}
		++ptSec, ++sizIndex;
	}
	
	return 0xffffffffU;
}

