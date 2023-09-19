#ifndef __SHA384_H__
#define __SHA384_H__


typedef union SHA384_HASH_SUM_UNION
{
	unsigned char auc[48];
	unsigned long aul[48 / sizeof(unsigned long)];
} SHA384_HASH_SUM_T;


void sha384_initialize(void);
#define sha384_update_ul(ulData) {ptHashArea->ulHash_din = ulData;}
void sha384_finalize(unsigned long *pulHash, unsigned int sizHash, unsigned long ulDataSizeDw);


#endif  /* __SHA384_H__ */

