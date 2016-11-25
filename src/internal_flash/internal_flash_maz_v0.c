#include "internal_flash_maz_v0.h"
#include "netx_io_areas.h"
#include "uprintf.h"


/* This unit is only available on the netX90 MPW chip. */
#if ASIC_TYP==ASIC_TYP_NETX90_MPW

#define IFLASH_MAZ_V0_PAGE_SIZE_BYTES 16U
#define IFLASH_MAZ_V0_PAGE_SIZE_DWORD 4U

#define IFLASH_MODE_READ        0U
#define IFLASH_MODE_PROGRAM     1U
#define IFLASH_MODE_ERASE       2U
#define IFLASH_MODE_MASS_ERASE  3U
#define IFLASH_MODE_MANUAL      4U


typedef union IFLASH_PAGE_BUFFER_UNION
{
	unsigned char auc[IFLASH_MAZ_V0_PAGE_SIZE_BYTES];
	unsigned long aul[IFLASH_MAZ_V0_PAGE_SIZE_DWORD];
} IFLASH_PAGE_BUFFER_T;


static NETX_CONSOLEAPP_RESULT_T check_command_area(const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr, unsigned long ulOffsetStart, unsigned long ulOffsetEnd)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	unsigned long ulFlashSize;


	/* Be pessimistic... */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	if( ulOffsetStart>ulOffsetEnd )
	{
		uprintf("! The start address is larger than the end address.\n");
		uprintf("! Start address: 0x%08x\n", ulOffsetStart);
		uprintf("! End address:   0x%08x\n", ulOffsetEnd);
	}
	else
	{
		/* Get the start and size of the data area. */
		ulFlashSize = ptAttr->ulSizeInBytes;

		/* Is the start and end inside the flash area? */
		if( (ulOffsetStart>=ulFlashSize) || (ulOffsetEnd>ulFlashSize) )
		{
			uprintf("! The requested area exceeds the flash size.");
			uprintf("! Requested area: [%d, %d[\n", ulOffsetStart, ulOffsetEnd);
			uprintf("! Available area: [0, %d[\n", ulFlashSize);
		}
		else
		{
			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}
	}

	return tResult;
}



static NETX_CONSOLEAPP_RESULT_T iflash_get_areas(unsigned int uiUnit, INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptFlashAttributes)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	HOSTDEF(ptIflashCfg0ComArea);
	HOSTDEF(ptIflashCfg1ComArea);
	HOSTDEF(ptIflashCfg2Area);
	NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea;
	void *pvDataArea;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	ptIFlashCfgArea = NULL;
	pvDataArea = NULL;

	switch(uiUnit)
	{
	case 0:
		tResult = NETX_CONSOLEAPP_RESULT_OK;
		ptIFlashCfgArea = ptIflashCfg0ComArea;
		pvDataArea = (void*)HOSTADDR(intflash0);
		break;

	case 1:
		tResult = NETX_CONSOLEAPP_RESULT_OK;
		ptIFlashCfgArea = ptIflashCfg1ComArea;
		pvDataArea = (void*)HOSTADDR(intflash1);
		break;

	case 2:
		tResult = NETX_CONSOLEAPP_RESULT_OK;
		ptIFlashCfgArea = ptIflashCfg2Area;
		pvDataArea = (void*)HOSTADDR(intflash2);
		break;
	}

	ptFlashAttributes->pvControllerArea = ptIFlashCfgArea;
	ptFlashAttributes->pvDataArea = pvDataArea;

	return tResult;
}



static void internal_flash_select_read_mode_and_clear_caches(const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr)
{
	NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea;
	int iMain0_Info1;
	unsigned long ulValue;


	/* Get the controller area. */
	ptIFlashCfgArea = ptAttr->pvControllerArea;

	/* Reset the flash. This clears the "read" caches. */
	ptIFlashCfgArea->ulIflash_reset = HOSTMSK(iflash_reset_reset);
	ptIFlashCfgArea->ulIflash_reset = 0;

	/* Select the main memory or info page. */
	iMain0_Info1 = ptAttr->iMain0_Info1;
	ulValue = 0;
	if( iMain0_Info1!=0 )
	{
		ulValue = HOSTMSK(iflash_ifren_cfg_ifren);
	}
	ptIFlashCfgArea->ulIflash_ifren_cfg = ulValue;

	/* Set the TMR line to 1. */
	ptIFlashCfgArea->ulIflash_special_cfg = HOSTMSK(iflash_special_cfg_tmr);

	/* Select "read" mode. */
	ptIFlashCfgArea->ulIflash_mode_cfg = IFLASH_MODE_READ;

	/* Clear also the CPU caches. */
	__asm__("DSB");
	__asm__("ISB");
}



static void iflash_start_and_wait(NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea)
{
	unsigned long ulValue;


	/* Start the operation. */
	ptIFlashCfgArea->ulIflash_access = HOSTMSK(iflash_access_run);

	/* Wait for the operation to finish. */
	do
	{
		ulValue  = ptIFlashCfgArea->ulIflash_access;
		ulValue &= HOSTMSK(iflash_access_run);
	} while( ulValue!=0 );
}



static unsigned long is_block_erased(const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr, unsigned long ulOffsetInBytes)
{
	const unsigned long *pulFlashDataArea;
	const unsigned long *pulCnt;
	const unsigned long *pulEnd;
	unsigned long ulValue;


	pulFlashDataArea = ptAttr->pvDataArea;
	pulCnt = pulFlashDataArea + (ulOffsetInBytes / sizeof(unsigned long));
	pulEnd = pulCnt + (ptAttr->ulEraseBlockSizeInBytes / sizeof(unsigned long));
	ulValue = 0xffffffffU;
	do
	{
		ulValue &= *(pulCnt++);
	} while( pulCnt<pulEnd );

	return ulValue;
}



static NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_erase_block(const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr, unsigned long ulOffsetInBytes)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea;
	unsigned long ulMisalignmentInBytes;
	unsigned long ulXAddr;
	unsigned long ulYAddr;
	unsigned long ulValue;


	/* Is the offset aligned to the page start? */
	ulMisalignmentInBytes = ulOffsetInBytes % ptAttr->ulEraseBlockSizeInBytes;
	if( ulMisalignmentInBytes!=0 )
	{
		uprintf("! Refuse to erase non-aligned block at offset 0x%08x. The correct offset for the aligned block would be 0x08x.\n", ulOffsetInBytes, ulOffsetInBytes - ulMisalignmentInBytes);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		/* Check if the block is already erased. */
		ulValue = is_block_erased(ptAttr, ulOffsetInBytes);
		if( ulValue==0xffffffffU )
		{
			uprintf(". The erase block at offset 0x%08x is already clear. Skipping the ERASE command.\n", ulOffsetInBytes);
			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}
		else
		{
			ulXAddr = ulOffsetInBytes / ptAttr->ulRowSizeInBytes;
			ulYAddr = 0;

			ptIFlashCfgArea = ptAttr->pvControllerArea;

			/* Select "erase" mode. */
			ptIFlashCfgArea->ulIflash_mode_cfg = IFLASH_MODE_ERASE;

			/* Set the X address. */
			ptIFlashCfgArea->ulIflash_xadr = ulXAddr;

			/* Program one column. */
			ptIFlashCfgArea->ulIflash_yadr = ulYAddr;

			/* Select the main memory. */
			ptIFlashCfgArea->ulIflash_ifren_cfg = 0;

			/* Start erasing. */
			iflash_start_and_wait(ptIFlashCfgArea);

			/* Go back to the read mode. */
			internal_flash_select_read_mode_and_clear_caches(ptAttr);

			/* Check if the block is now erased. */
			ulValue = is_block_erased(ptAttr, ulOffsetInBytes);
			if( ulValue!=0xffffffffU )
			{
				uprintf("! The erase block at offset 0x%08x was not erased.\n", ulOffsetInBytes);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			}
			else
			{
				tResult = NETX_CONSOLEAPP_RESULT_OK;
			}
		}
	}

	return tResult;
}



static NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_flash_page(const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr, unsigned long ulOffset, IFLASH_PAGE_BUFFER_T tDataToBeFlashed)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea;
	unsigned long ulMisalignment;
	unsigned long ulRowSize;
	unsigned long ulXAddr;
	unsigned long ulYAddr;
	int iMain0_Info1;
	unsigned long ulValue;
	const unsigned char *pucFlashDataArray;
	int iCmpResult;
	unsigned int uiCnt;
	unsigned long ulDifference;
	IFLASH_PAGE_BUFFER_T tExistingDataInFlash;
	IFLASH_PAGE_BUFFER_T tDifference;


	/* Is the offset aligned to the page start? */
	ulMisalignment = ulOffset % IFLASH_MAZ_V0_PAGE_SIZE_BYTES;
	if( ulMisalignment!=0 )
	{
		uprintf("! Refuse to program non-aligned page at offset 0x%08x. The correct offset for the aligned page would be 0x08x.\n", ulOffset, ulOffset - ulMisalignment);
		tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	}
	else
	{
		/* Get a pointer to the data array of the flash. */
		pucFlashDataArray = ptAttr->pvDataArea;

		/* Get the old contents of the flash. */
		memcpy(tExistingDataInFlash.auc, pucFlashDataArray + ulOffset, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);

		/* Compare the data to be programmed with the flash contents. */
		iCmpResult = memcmp(tExistingDataInFlash.aul, tDataToBeFlashed.aul, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);
		if( iCmpResult==0 )
		{
			/* The requested data is already in the flash. Do not program again. */
			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}
		else
		{
			/* Check if the requested data will only change bits from 1 to 0.
			 *
			 * Get the difference first. "tDifference" will have
			 * all bits set to 1 which differ between the flash
			 * contents and the requested data.
			 *
			 * The flash contents must have all bits of the
			 * difference set to 1. This can be checked by
			 * masking the flash contents with the difference.
			 * The result must be the difference.
			 */

			/* Get the difference between the flash contents and
			 * the data to program.
			 */
			for(uiCnt=0; uiCnt<IFLASH_MAZ_V0_PAGE_SIZE_DWORD; ++uiCnt)
			{
				tDifference.aul[uiCnt] = tExistingDataInFlash.aul[uiCnt] ^ tDataToBeFlashed.aul[uiCnt];
			}

			tResult = NETX_CONSOLEAPP_RESULT_OK;

			/* Check if all bits from the difference are set to 1
			 * in the flash.
			 */
			for(uiCnt=0; uiCnt<IFLASH_MAZ_V0_PAGE_SIZE_DWORD; ++uiCnt)
			{
				ulDifference = tDifference.aul[uiCnt];
				ulValue = tExistingDataInFlash.aul[uiCnt] & ulDifference;
				if( ulValue!=ulDifference )
				{
					uprintf("! Invalid program request: trying to set bits from 0 to 1 at offset 0x%08x.\n", ulOffset + uiCnt * sizeof(unsigned long));
					uprintf("! Flash contents:  0x%08x\n", tExistingDataInFlash.aul[uiCnt]);
					uprintf("! Data to program: 0x%08x\n", tDataToBeFlashed.aul[uiCnt]);
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				}
			}
			if( tResult==NETX_CONSOLEAPP_RESULT_OK )
			{
				/* Convert the offset to an X and Y component. */
				ulRowSize = ptAttr->ulRowSizeInBytes;
				ulXAddr = ulOffset / ulRowSize;
				ulYAddr  = ulOffset;
				ulYAddr -= (ulXAddr * ulRowSize);
				ulYAddr /= IFLASH_MAZ_V0_PAGE_SIZE_BYTES;

				/* Get a pointer to the flash controller. */
				ptIFlashCfgArea = ptAttr->pvControllerArea;

				/* Set the TMR line to 1. */
				ptIFlashCfgArea->ulIflash_special_cfg = HOSTMSK(iflash_special_cfg_tmr);

				/* Select "program" mode. */
				ptIFlashCfgArea->ulIflash_mode_cfg = IFLASH_MODE_PROGRAM;

				/* Set the X and Y address. */
				ptIFlashCfgArea->ulIflash_xadr = ulXAddr;
				ptIFlashCfgArea->ulIflash_yadr = ulYAddr;

				/* Select the main memory or info page. */
				iMain0_Info1 = ptAttr->iMain0_Info1;
				ulValue = 0;
				if( iMain0_Info1!=0 )
				{
					ulValue = HOSTMSK(iflash_ifren_cfg_ifren);
				}
				ptIFlashCfgArea->ulIflash_ifren_cfg = ulValue;

				/* Set the data for the "program" operation. */
				ptIFlashCfgArea->aulIflash_din[0] = tDataToBeFlashed.aul[0];
				ptIFlashCfgArea->aulIflash_din[1] = tDataToBeFlashed.aul[1];
				ptIFlashCfgArea->aulIflash_din[2] = tDataToBeFlashed.aul[2];
				ptIFlashCfgArea->aulIflash_din[3] = tDataToBeFlashed.aul[3];

				/* Start programming. */
				iflash_start_and_wait(ptIFlashCfgArea);

				/* Go back to the read mode. */
				internal_flash_select_read_mode_and_clear_caches(ptAttr);

				/* Verify the data. */
				memcpy(tExistingDataInFlash.auc, pucFlashDataArray + ulOffset, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);
				iCmpResult = memcmp(tExistingDataInFlash.aul, tDataToBeFlashed.aul, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);
				if( iCmpResult==0 )
				{
					/* The requested data was written to the flash. */
					tResult = NETX_CONSOLEAPP_RESULT_OK;
				}
				else
				{
					uprintf("! Verify error at offset 0x%08x.\n", ulOffset);
					uprintf("Expected data:\n");
					hexdump(tDataToBeFlashed.auc, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);
					uprintf("Flash contents:\n");
					hexdump(tExistingDataInFlash.auc, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);

					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
				}
			}
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_detect(CMD_PARAMETER_DETECT_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	INTERNAL_FLASH_TYPE_T tFlashType;
	DEVICE_DESCRIPTION_T *ptDeviceDescription;
	INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned int uiUnit;
	unsigned int uiChipSelect;


	/* Be pessimistic. */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;
	tFlashType = INTERNAL_FLASH_TYPE_Unknown;

	/* Get a pointer to the device description and the flash attributes. */
	ptDeviceDescription = ptParameter->ptDeviceDescription;
	ptAttr = &(ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

	/* Set the default values. */
	ptAttr->pvControllerArea = NULL;
	ptAttr->pvDataArea = NULL;
	ptAttr->iMain0_Info1 = 0;
	ptAttr->ulSizeInBytes = 0;
	ptAttr->ulRowSizeInBytes = 0;
	ptAttr->ulEraseBlockSizeInBytes = 0;

	/* Check the unit. */
	uiUnit = ptParameter->uSourceParameter.tInternalFlash.uiUnit;
	tResult = iflash_get_areas(uiUnit, ptAttr);
	if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
	{
		uprintf("! Invalid unit: %d\n", uiUnit);
	}
	else
	{
		/* Chip select 0 is the main memory area. Chip select 1 is the info page. */
		uiChipSelect = ptParameter->uSourceParameter.tInternalFlash.uiChipSelect;
		if( uiChipSelect==0 )
		{
			ptAttr->iMain0_Info1 = 0;
			ptAttr->ulSizeInBytes = 0x80000;
			ptAttr->ulRowSizeInBytes = 0x200;
			ptAttr->ulEraseBlockSizeInBytes = 0x1000;

			tResult = NETX_CONSOLEAPP_RESULT_OK;
			tFlashType = INTERNAL_FLASH_TYPE_MAZ_V0;
		}
		else if( uiChipSelect==1 )
		{
			ptAttr->iMain0_Info1 = 1;
			ptAttr->ulSizeInBytes = 0x1000;
			ptAttr->ulRowSizeInBytes = 0x200;
			ptAttr->ulEraseBlockSizeInBytes = 0x1000;

			tResult = NETX_CONSOLEAPP_RESULT_OK;
			tFlashType = INTERNAL_FLASH_TYPE_MAZ_V0;
		}
		else
		{
			uprintf("! Invalid chip select: %d\n", uiChipSelect);
			tResult = NETX_CONSOLEAPP_RESULT_ERROR;
		}

		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			internal_flash_select_read_mode_and_clear_caches(ptAttr);
		}
	}

	/* Set the flash type. */
	ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType = tFlashType;

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_flash(CMD_PARAMETER_FLASH_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;
	const unsigned char *pucFlashDataArea; /* This is the data area of the flash. */
	const unsigned char *pucDataToBeFlashed; /* This is the data to be flashed. */
	unsigned long ulOffset;
	unsigned long ulPageStartOffset;
	unsigned long ulChunkOffset;
	unsigned long ulChunkSize;
	unsigned long ulDataSize;
	IFLASH_PAGE_BUFFER_T tFlashBuffer; /* This is the buffer for the data to flash. */


	/* Be pessimistic... */
	tResult = NETX_CONSOLEAPP_RESULT_ERROR;

	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ulOffsetStart + ptParameter->ulDataByteSize;

	/* Silently ignore erase requests with a size of 0 bytes. */
	if( ulOffsetStart==ulOffsetEnd )
	{
		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		/* Get a pointer to the flash attributes. */
		ptAttr = &(ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

		tResult = check_command_area(ptAttr, ulOffsetStart, ulOffsetEnd);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* Get a pointer to the data area of the flash. */
			pucFlashDataArea = ptAttr->pvDataArea;

			/* Get a pointer to the data to be flashed. */
			pucDataToBeFlashed = ptParameter->pucData;

			ulOffset = ulOffsetStart;

			/* Does the area start in the middle of a page? */
			ulChunkOffset = ulOffset % IFLASH_MAZ_V0_PAGE_SIZE_BYTES;
			if( ulChunkOffset!=0 )
			{
				/* Yes -> modify the last part of a page. */

				/* Get the start offset of the page. */
				ulPageStartOffset = ulOffset - ulChunkOffset;

				/* Get the old contents of the page. */
				memcpy(tFlashBuffer.auc, pucFlashDataArea + ulPageStartOffset, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);

				/* Add the new part to the buffer. */
				ulChunkSize = IFLASH_MAZ_V0_PAGE_SIZE_BYTES - ulChunkOffset;
				ulDataSize = ulOffsetEnd - ulOffset;
				if( ulChunkSize>ulDataSize )
				{
					ulChunkSize = ulDataSize;
				}
				memcpy(tFlashBuffer.auc + ulChunkOffset, pucDataToBeFlashed, ulChunkSize);

				/* Flash the chunk. */
				tResult = internal_flash_maz_v0_flash_page(ptAttr, ulPageStartOffset, tFlashBuffer);
				if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
				{
					uprintf("! Failed to flash the page at offset 0x%08x.\n", ulPageStartOffset);
				}
				else
				{
					ulOffset += ulChunkSize;
					pucDataToBeFlashed += ulChunkSize;
				}
			}

			if( tResult==NETX_CONSOLEAPP_RESULT_OK )
			{
				/* Write all complete pages. */
				while( (ulOffset+IFLASH_MAZ_V0_PAGE_SIZE_BYTES)<=ulOffsetEnd )
				{
					memcpy(tFlashBuffer.auc, pucDataToBeFlashed, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);
					tResult = internal_flash_maz_v0_flash_page(ptAttr, ulOffset, tFlashBuffer);
					if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
					{
						uprintf("! Failed to flash the page at offset 0x%08x.\n", ulOffset);
						break;
					}
					else
					{
						ulOffset += IFLASH_MAZ_V0_PAGE_SIZE_BYTES;
						pucDataToBeFlashed += IFLASH_MAZ_V0_PAGE_SIZE_BYTES;
					}
				}
			}

			if( tResult==NETX_CONSOLEAPP_RESULT_OK )
			{
				/* Is a part of the last page left? */
				ulChunkSize = ulOffsetEnd - ulOffset;
				if( ulChunkSize!=0 )
				{
					/* Get the old contents of the page. */
					memcpy(tFlashBuffer.auc, pucFlashDataArea + ulOffset, IFLASH_MAZ_V0_PAGE_SIZE_BYTES);

					/* Add the new part to the buffer. */
					memcpy(tFlashBuffer.auc, pucDataToBeFlashed, ulChunkSize);

					/* Flash the chunk. */
					tResult = internal_flash_maz_v0_flash_page(ptAttr, ulOffset, tFlashBuffer);
					if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
					{
						uprintf("! Failed to flash the page at offset 0x%08x.\n", ulOffset);
					}
					else
					{
						ulOffset += ulChunkSize;
						pucDataToBeFlashed += ulChunkSize;
					}
				}
			}
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_erase(CMD_PARAMETER_ERASE_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;
	unsigned long ulEraseBlockSize;
	unsigned long ulBlockOffset;
	unsigned long ulOffset;


	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ptParameter->ulEndAdr;

	/* Silently ignore erase requests with a size of 0 bytes. */
	if( ulOffsetStart==ulOffsetEnd )
	{
		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		/* Get a pointer to the flash attributes. */
		ptAttr = &(ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

		tResult = check_command_area(ptAttr, ulOffsetStart, ulOffsetEnd);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* The offset must be aligned to the erase block size. */
			ulEraseBlockSize = ptAttr->ulEraseBlockSizeInBytes;
			ulBlockOffset = ulOffsetStart % ulEraseBlockSize;
			if( ulBlockOffset!=0 )
			{
				uprintf("! The erase start is not aligned to the erase blocks.\n");
				uprintf("! Requested erase start: 0x%08x\n", ulOffsetStart);
				uprintf("! Erase block start:     0x%08x\n", ulOffsetStart - ulBlockOffset);
				tResult = NETX_CONSOLEAPP_RESULT_ERROR;
			}
			else
			{
				ulOffset = ulOffsetStart;
				do
				{
					tResult = internal_flash_maz_v0_erase_block(ptAttr, ulOffset);
					if( tResult!=NETX_CONSOLEAPP_RESULT_OK )
					{
						break;
					}
					ulOffset += ulEraseBlockSize;
				} while( ulOffset<ulOffsetEnd );
			}
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_read(CMD_PARAMETER_READ_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;
	unsigned long ulLength;
	const unsigned char *pucFlashArea;
	const unsigned char *pucFlashStart;
	unsigned char *pucBufferStart;
	unsigned long ulOffset;


	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ptParameter->ulEndAdr;

	/* Silently ignore read requests with a size of 0 bytes. */
	if( ulOffsetStart==ulOffsetEnd )
	{
		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		/* Get a pointer to the flash attributes. */
		ptAttr = &(ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

		tResult = check_command_area(ptAttr, ulOffsetStart, ulOffsetEnd);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* Get the start and size of the data area. */
			pucFlashArea = (const unsigned char*)(ptAttr->pvDataArea);
			pucFlashStart = pucFlashArea + ulOffsetStart;

			/* Set the flash to read mode. */
			internal_flash_select_read_mode_and_clear_caches(ptAttr);

			/* Copy the data block to the destination buffer.*/
			pucBufferStart = ptParameter->pucData;

			/* Copy the data block to the destination buffer.*/
			ulOffset = 0;
			ulLength = ulOffsetEnd - ulOffsetStart;
			do
			{
				pucBufferStart[ulOffset] = pucFlashStart[ulOffset];
				++ulOffset;
			} while( ulOffset<ulLength );

			tResult = NETX_CONSOLEAPP_RESULT_OK;
		}
	}

	return tResult;
}


#       if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_sha1(CMD_PARAMETER_CHECKSUM_T *ptParameter, SHA_CTX *ptSha1Context)
{
	uprintf("! not yet....\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}
#       endif


NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_verify(CMD_PARAMETER_VERIFY_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;
	const unsigned char *pucFlashArea;
	const unsigned char *pucFlashStart;
	unsigned char *pucBufferStart;
	unsigned char ucFlashData;
	unsigned char ucBufferData;
	unsigned long ulOffset;
	unsigned long ulLength;


	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ptParameter->ulEndAdr;

	/* Silently ignore read requests with a size of 0 bytes. */
	if( ulOffsetStart==ulOffsetEnd )
	{
		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		/* Get a pointer to the flash attributes. */
		ptAttr = &(ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

		tResult = check_command_area(ptAttr, ulOffsetStart, ulOffsetEnd);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* Get the start and size of the data area. */
			pucFlashArea = (const unsigned char*)(ptAttr->pvDataArea);
			pucFlashStart = pucFlashArea + ulOffsetStart;

			/* Set the flash to read mode. */
			internal_flash_select_read_mode_and_clear_caches(ptAttr);

			/* Be optimistic... */
			tResult = NETX_CONSOLEAPP_RESULT_OK;

			/* Compare the data from the buffer with the flash contents. */
			pucBufferStart = ptParameter->pucData;

			ulOffset = 0;
			ulLength = ulOffsetEnd - ulOffsetStart;
			do
			{
				ucFlashData = pucFlashStart[ulOffset];
				ucBufferData = pucBufferStart[ulOffset];
				if( ucFlashData!=ucBufferData )
				{
					uprintf(". verify error at offset 0x%08x. buffer: 0x%02x, flash: 0x%02x.\n", ulOffsetStart + ulOffset, ucBufferData, ucFlashData);
					tResult = NETX_CONSOLEAPP_RESULT_ERROR;
					break;
				}

				++ulOffset;
			} while( ulOffset<ulLength );

			ptConsoleParams->pvReturnMessage = (void*)tResult;
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_is_erased(CMD_PARAMETER_ISERASED_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;
	const unsigned char *pucFlashArea;
	const unsigned char *pucFlashStart;
	unsigned long ulOffset;
	unsigned long ulLength;
	unsigned char ucFlashData;


	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ptParameter->ulEndAdr;

	/* Silently ignore read requests with a size of 0 bytes. */
	if( ulOffsetStart==ulOffsetEnd )
	{
		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}
	else
	{
		/* Get a pointer to the flash attributes. */
		ptAttr = &(ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

		tResult = check_command_area(ptAttr, ulOffsetStart, ulOffsetEnd);
		if( tResult==NETX_CONSOLEAPP_RESULT_OK )
		{
			/* Get the start and size of the data area. */
			pucFlashArea = (const unsigned char*)(ptAttr->pvDataArea);
			pucFlashStart = pucFlashArea + ulOffsetStart;

			/* Set the flash to read mode. */
			internal_flash_select_read_mode_and_clear_caches(ptAttr);

			/* Be optimistic... */
			tResult = NETX_CONSOLEAPP_RESULT_OK;

			ulOffset = 0;
			ulLength = ulOffsetEnd - ulOffsetStart;
			do
			{
				ucFlashData = pucFlashStart[ulOffset];
				if( ucFlashData!=0xffU )
				{
					break;
				}

				++ulOffset;
			} while( ulOffset<ulLength );

			if( ucFlashData==0xff )
			{
				uprintf(". CLEAN! The area is erased.\n");
			}
			else
			{
				uprintf(". DIRTY! The area is not erased.\n");
			}
			ptConsoleParams->pvReturnMessage = (void*)((unsigned long)ucFlashData);
		}
	}

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_get_erase_area(CMD_PARAMETER_GETERASEAREA_T *ptParameter)
{
	NETX_CONSOLEAPP_RESULT_T tResult;
	const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr;
	unsigned long ulOffsetStart;
	unsigned long ulOffsetEnd;
	unsigned long ulEraseBlockSize;


	ulOffsetStart = ptParameter->ulStartAdr;
	ulOffsetEnd = ptParameter->ulEndAdr;

	/* Get a pointer to the flash attributes. */
	ptAttr = &(ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.uAttributes.tMazV0);

	tResult = check_command_area(ptAttr, ulOffsetStart, ulOffsetEnd);
	if( tResult==NETX_CONSOLEAPP_RESULT_OK )
	{
		/* NOTE: this code assumes that the serial flash has uniform erase block sizes. */
		ulEraseBlockSize = ptAttr->ulEraseBlockSizeInBytes;
		uprintf("erase block size: 0x%08x\n", ulEraseBlockSize);
		uprintf("0x%08x - 0x%08x\n", ulOffsetStart, ulOffsetEnd);

		/* Round down the start address. */
		ulOffsetStart /= ulEraseBlockSize;
		ulOffsetStart *= ulEraseBlockSize;

		/* Round up the end address. */
		ulOffsetEnd += ulEraseBlockSize - 1;
		ulOffsetEnd /= ulEraseBlockSize;
		ulOffsetEnd *= ulEraseBlockSize;

		uprintf("0x%08x - 0x%08x\n", ulOffsetStart, ulOffsetEnd);

		ptParameter->ulStartAdr = ulOffsetStart;
		ptParameter->ulEndAdr = ulOffsetEnd;

		tResult = NETX_CONSOLEAPP_RESULT_OK;
	}

	return tResult;
}

#else
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_detect(CMD_PARAMETER_DETECT_T *ptParameter __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_flash(CMD_PARAMETER_FLASH_T *ptParameter __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_erase(CMD_PARAMETER_ERASE_T *ptParameter __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_read(CMD_PARAMETER_READ_T *ptParameter __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}


#       if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_sha1(CMD_PARAMETER_CHECKSUM_T *ptParameter __attribute__((unused)), SHA_CTX *ptSha1Context __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}
#       endif


NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_verify(CMD_PARAMETER_VERIFY_T *ptParameter __attribute__((unused)), NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_is_erased(CMD_PARAMETER_ISERASED_T *ptParameter __attribute__((unused)), NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_get_erase_area(CMD_PARAMETER_GETERASEAREA_T *ptParameter __attribute__((unused)))
{
	uprintf("! Internal flash MAZ V0 is not available on this platform.\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}
#endif
