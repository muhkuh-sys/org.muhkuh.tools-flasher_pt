
#include "sha1.h"
#include "netx_io_areas.h"

void SHA1_Init(SHA_CTX *c)
{
	HOSTDEF(ptHashArea);
	unsigned long ulValue;


	/* Reset the unit and set the mode to 0 (SHA1)
	 * The reset bit will be cleared automatically.
	 */
	ulValue  = HOSTMSK(hash_cfg_reset);
	ulValue |= 0U << HOSTSRT(hash_cfg_mode);
	ptHashArea->ulHash_cfg = ulValue;

	/* Acknowledge any pending IRQ. */
	ulValue  = HOSTMSK(hash_irq_raw_hash_ready);
	ulValue |= HOSTMSK(hash_irq_raw_fifo_underrun);
	ulValue |= HOSTMSK(hash_irq_raw_fifo_overflow);
	ptHashArea->ulHash_irq_raw = ulValue;

	c->len = 0ULL;
}



void SHA1_Update(SHA_CTX *c, const void *p, unsigned long n)
{
	HOSTDEF(ptHashArea);
	PTR_T tCnt;
	PTR_T tEnd;


	/* Set the start and end pointer. */
	tCnt.pv = p;
	tEnd.ul = tCnt.ul + n;

	/* Process bytes at the start of the buffer while the address is not a
	 * multiple of 32 bits.
	 */
	while( (tCnt.ul&3U)!=0 && tCnt.ul<tEnd.ul )
	{
		*((volatile unsigned char*)HOSTADR(hash_din)) = *(tCnt.puc++);
	}

	/* Process 32bit values as long as enough data is avaiable. */
	while( (tCnt.ul+4U)<=tEnd.ul )
	{
		ptHashArea->ulHash_din = *(tCnt.pul++);
	}

	/* Process bytes at the end of the buffer while the address is not a
	 * multiple of 32 bits.
	 */
	while( tCnt.ul<tEnd.ul )
	{
		*((volatile unsigned char*)HOSTADR(hash_din)) = *(tCnt.puc++);
	}

	/* Add the length to the counter of processed bytes. */
	c->len += n;
}



void SHA1_Final(unsigned char *hash, SHA_CTX *c)
{
	HOSTDEF(ptHashArea);
	unsigned long ulLastChunkSize;
	unsigned int uiPadSize;
	uint64_t ullDataBits;
	unsigned char ucPadding;
	unsigned int uiCnt;
	unsigned long ulValue;
	BUF_T tBuf;


	/* Get the size of the last data block. */
	ulLastChunkSize = ((unsigned long)(c->len & 0x000000000000003fULL));
	uiPadSize = (ulLastChunkSize < 56) ? (56 - ulLastChunkSize) : (120 - ulLastChunkSize);

	/* The first padding byte is 0x80. */
	ucPadding = 0x80U;
	while( uiPadSize>0 )
	{
		/* Add the padding byte to the FIFO. */
		*((volatile unsigned char*)HOSTADR(hash_din)) = ucPadding;

		--uiPadSize;

		/* All other padding bytes except the first one are 0x00. */
		ucPadding = 0x00;
	}

	/* Create the length information block.
	 * It is the number of processed bits in big endian.
	 */
	ullDataBits = c->len * 8ULL;
	tBuf.auc[0] = (unsigned char)((ullDataBits >> 56U) & 0xffU);
	tBuf.auc[1] = (unsigned char)((ullDataBits >> 48U) & 0xffU);
	tBuf.auc[2] = (unsigned char)((ullDataBits >> 40U) & 0xffU);
	tBuf.auc[3] = (unsigned char)((ullDataBits >> 32U) & 0xffU);
	tBuf.auc[4] = (unsigned char)((ullDataBits >> 24U) & 0xffU);
	tBuf.auc[5] = (unsigned char)((ullDataBits >> 16U) & 0xffU);
	tBuf.auc[6] = (unsigned char)((ullDataBits >>  8U) & 0xffU);
	tBuf.auc[7] = (unsigned char)( ullDataBits         & 0xffU);
	ptHashArea->ulHash_din = tBuf.aul[0];

	/* Clear the IRQ before writing the last data element. */
	ptHashArea->ulHash_irq_raw = HOSTMSK(hash_irq_raw_hash_ready);

	ptHashArea->ulHash_din = tBuf.aul[1];

	/* Wait for the hash calculation. */
	do
	{
		ulValue  = ptHashArea->ulHash_irq_raw;
		ulValue &= HOSTMSK(hash_irq_raw_hash_ready);
	} while( ulValue==0 );

	/* Copy the hash to the buffer. */
	for(uiCnt=0; uiCnt<(20U/sizeof(unsigned long)); ++uiCnt)
	{
		tBuf.aul[uiCnt] = ptHashArea->aulHash_dout[uiCnt];
	}
	for(uiCnt=0; uiCnt<20U; ++uiCnt)
	{
		hash[uiCnt] = tBuf.auc[uiCnt];
	}
}
