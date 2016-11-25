#include "internal_flash_maz_v0.h"
#include "netx_io_areas.h"
#include "uprintf.h"


/* This unit is only available on the netX90 MPW chip. */
#if ASIC_TYP==ASIC_TYP_NETX90_MPW

#define IFLASH_MODE_READ        0U
#define IFLASH_MODE_PROGRAM     1U
#define IFLASH_MODE_ERASE       2U
#define IFLASH_MODE_MASS_ERASE  3U
#define IFLASH_MODE_MANUAL      4U


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

	/* Select the main memory or info page. */
	iMain0_Info1 = ptAttr->iMain0_Info1;
	ulValue = 0;
	if( iMain0_Info1!=0 )
	{
		ulValue = HOSTMSK(iflash_ifren_cfg_ifren);
	}
	ptIFlashCfgArea->ulIflash_ifren_cfg = ulValue;

	/* Reset the flash. This clears the "read" caches. */
	ptIFlashCfgArea->ulIflash_reset = HOSTMSK(iflash_reset_reset);
	ptIFlashCfgArea->ulIflash_reset = 0;
}



static void iflash_start_and_wait(NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea)
{
	unsigned long ulValue;


	/* Start the erase operation. */
	ptIFlashCfgArea->ulIflash_access = HOSTMSK(iflash_access_run);

	/* Wait for the erase operation to finish. */
	do
	{
		ulValue  = ptIFlashCfgArea->ulIflash_access;
		ulValue &= HOSTMSK(iflash_access_run);
	} while( ulValue!=0 );
}



static NETX_CONSOLEAPP_RESULT_T internal_flash_erase_block(const INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T *ptAttr, unsigned long ulOffset)
{
	NX90_IFLASH_CFG_AREA_T *ptIFlashCfgArea;
	unsigned long ulRowSize;
	unsigned long ulXAddr;
	unsigned long ulYAddr;


	ulRowSize = ptAttr->ulRowSizeInBytes;
	ulXAddr = ulOffset / ulRowSize;
	ulYAddr = 0;

	ptIFlashCfgArea = ptAttr->pvControllerArea;

	/* Select "program" mode and set the address to 0. */
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

	return NETX_CONSOLEAPP_RESULT_OK;
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
	}

	/* Set the flash type. */
	ptParameter->ptDeviceDescription->uInfo.tInternalFlashInfo.tType = tFlashType;

	return tResult;
}



NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_flash(CMD_PARAMETER_FLASH_T *ptParameter)
{
	uprintf("! not yet....\n");
	return NETX_CONSOLEAPP_RESULT_ERROR;
}



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
					tResult = internal_flash_erase_block(ptAttr, ulOffset);
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
