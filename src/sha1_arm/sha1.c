/*
 * SHA-1 implementation optimized for ARM
 *
 * Copyright:   (C) 2005 by Nicolas Pitre <nico@cam.org>
 * Created:     September 17, 2005
 */

#include <string.h>
#include "sha1.h"

extern void sha_transform(uint32_t *hash, const unsigned char *data, uint32_t *W);

void SHA1_Init(SHA_CTX *c)
{
	c->len = 0;
	c->hash[0] = 0x67452301;
	c->hash[1] = 0xefcdab89;
	c->hash[2] = 0x98badcfe;
	c->hash[3] = 0x10325476;
	c->hash[4] = 0xc3d2e1f0;
}

void SHA1_Update(SHA_CTX *c, const void *p, unsigned long n)
{
	uint32_t workspace[80];
	unsigned int partial;
	unsigned long done;

	partial = c->len & 0x3f;
	c->len += n;
	if ((partial + n) >= 64) {
		if (partial) {
			done = 64 - partial;
			memcpy(c->buffer + partial, p, done);
			sha_transform(c->hash, c->buffer, workspace);
			partial = 0;
		} else
			done = 0;
		while (n >= done + 64) {
			sha_transform(c->hash, ((const unsigned char*)p) + done, workspace);
			done += 64;
		}
	} else
		done = 0;
	if (n - done)
		memcpy(c->buffer + partial, ((const unsigned char*)p) + done, n - done);
}


void SHA1_Final(unsigned char *hash, SHA_CTX *c)
{
	uint64_t bitlen;
	uint32_t bitlen_hi, bitlen_lo; 
	unsigned int i, offset, padlen;
	unsigned char bits[8];
	static const unsigned char padding[64] = { 0x80, };

	bitlen = c->len << 3;
	offset = c->len & 0x3f;
	padlen = ((offset < 56) ? 56 : (64 + 56)) - offset;
	SHA1_Update(c, padding, padlen);

	// convert bitlen to 64-bit big endian
	bitlen_hi = (unsigned char) (bitlen >> 32);
	bitlen_lo = bitlen & 0xffffffff;
	bits[0] = (unsigned char) (bitlen_hi >> 24);
	bits[1] = (unsigned char) (bitlen_hi >> 16);
	bits[2] = (unsigned char) (bitlen_hi >> 8);
	bits[3] = (unsigned char) bitlen_hi;
	bits[4] = (unsigned char) (bitlen_lo >> 24);
	bits[5] = (unsigned char) (bitlen_lo >> 16);
	bits[6] = (unsigned char) (bitlen_lo >> 8);
	bits[7] = (unsigned char) bitlen_lo;
	SHA1_Update(c, bits, 8); 

	for (i = 0; i < 5; i++) {
		uint32_t v = c->hash[i];
		hash[0] = (unsigned char) (v >> 24);
		hash[1] = (unsigned char) (v >> 16);
		hash[2] = (unsigned char) (v >> 8);
		hash[3] = (unsigned char) v;
		hash += 4;
	}
}
