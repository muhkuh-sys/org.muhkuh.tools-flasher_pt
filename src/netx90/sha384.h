#ifndef __SHA384_H__
#define __SHA384_H__


typedef union SHA384_HASH_SUM_UNION
{
	unsigned char auc[48];
	unsigned long aul[48 / sizeof(unsigned long)];
} SHA384_HASH_SUM_T;


void sha384_initialize(void);
#define sha384_update_uc(ucData) {*((volatile unsigned char*)(&(ptHashArea->ulHash_din))) = ucData;}
void sha384_finalize(unsigned char *pucHash, unsigned long ulDataSizeByte);


#endif  /* __SHA384_H__ */

