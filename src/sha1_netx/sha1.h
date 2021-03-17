#ifndef __sha1_H__
#define __sha1_H__

#include <stdint.h>


typedef struct SHA_CTX_STRUCT
{
	uint64_t len;
} SHA_CTX;


typedef union PTR_UNION
{
	const void *pv;
	unsigned long ul;
	const unsigned char *puc;
	const unsigned long *pul;
} PTR_T;

typedef union BUF_UNION
{
	unsigned char auc[20];
	unsigned long aul[20/sizeof(unsigned long)];
} BUF_T;

void SHA1_Init(SHA_CTX *c);
void SHA1_Update(SHA_CTX *c, const void *p, unsigned long n);
void SHA1_Final(unsigned char *hash, SHA_CTX *c);

#endif