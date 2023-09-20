#include "sha384.h"

#include <string.h>

#include "netx_io_areas.h"


/* Why SHA384 instead of SHA512: https://en.wikipedia.org/wiki/Length_extension_attack */

#if ASIC_TYP==ASIC_TYP_NETX90
#       define HASH_CFG_MODE_SHA1_160 0
#       define HASH_CFG_MODE_SHA2_224 1
#       define HASH_CFG_MODE_SHA2_256 2
#       define HASH_CFG_MODE_SHA2_384 3
#       define HASH_CFG_MODE_SHA2_512 4
#       define HASH_CFG_MODE_MD5      5
#else
#       error "Unsupported ASIC_TYP!"
#endif


void sha384_initialize(void)
{
	HOSTDEF(ptHashArea);
	unsigned long ulValue;


	/* Reset the unit and select SHA384.
	 * NOTE: the reset bit will be cleared by the hardware.
	 */
	ulValue  = HOSTMSK(hash_cfg_reset);
	ulValue |= HASH_CFG_MODE_SHA2_384 << HOSTSRT(hash_cfg_mode);
	ptHashArea->ulHash_cfg = ulValue;
}



void sha384_finalize(unsigned char *pucHash, unsigned long ulDataSizeByte)
{
	HOSTDEF(ptHashArea);
	unsigned long long ullBits;
	unsigned long ulValue;
	unsigned long ulValueRev;
	unsigned long ulPadByte;
	unsigned int uiCnt;


	/* Pad the data. */
	ulPadByte = ulDataSizeByte & 0x7fU;
	if( ulPadByte<112 )
	{
		ulPadByte = 119U - ulPadByte;
	}
	else
	{
		ulPadByte = 247U - ulPadByte;
	}

	/* Start the padding data with a '1' bit. */
	*((volatile unsigned char*)(&(ptHashArea->ulHash_din))) = 0x80U;
	/* Continue with a lot of '0' bits. */
	while( ulPadByte!=0 )
	{
		*((volatile unsigned char*)(&(ptHashArea->ulHash_din))) = 0x00U;
		--ulPadByte;
	}

	/* Convert the number of DWORDs to bits. */
	ullBits = ((unsigned long long)ulDataSizeByte) * 8U;
	ulValue = ((unsigned long)((ullBits >> 32U) & 0xffffffffU));
	ulValueRev = ((ulValue & 0x000000ffU) << 24U) |
	             ((ulValue & 0x0000ff00U) <<  8U) |
	             ((ulValue & 0x00ff0000U) >>  8U) |
	             ((ulValue & 0xff000000U) >> 24U);
	ptHashArea->ulHash_din = ulValueRev;

	/* Clear the IRQ before writing the last data element. */
	ptHashArea->ulHash_irq_raw = HOSTMSK(hash_irq_raw_hash_ready);

	ulValue = ((unsigned long)( ullBits         & 0xffffffffU ));
	ulValueRev = ((ulValue & 0x000000ffU) << 24U) |
	             ((ulValue & 0x0000ff00U) <<  8U) |
	             ((ulValue & 0x00ff0000U) >>  8U) |
	             ((ulValue & 0xff000000U) >> 24U);
	ptHashArea->ulHash_din = ulValueRev;

	/* Wait for the hash calculation. */
	do
	{
		ulValue  = ptHashArea->ulHash_irq_raw;
		ulValue &= HOSTMSK(hash_irq_raw_hash_ready);
	} while( ulValue==0 );

	/* Copy the hash to the buffer. */
	for(uiCnt=0; uiCnt<(sizeof(SHA384_HASH_SUM_T)/sizeof(unsigned long)); uiCnt++)
	{
		ulValue = ptHashArea->aulHash_dout[uiCnt];
		*(pucHash++) = (unsigned char)( ulValue         & 0x000000ffU);
		*(pucHash++) = (unsigned char)((ulValue >>  8U) & 0x000000ffU);
		*(pucHash++) = (unsigned char)((ulValue >> 16U) & 0x000000ffU);
		*(pucHash++) = (unsigned char)((ulValue >> 24U) & 0x000000ffU);
	}
}
