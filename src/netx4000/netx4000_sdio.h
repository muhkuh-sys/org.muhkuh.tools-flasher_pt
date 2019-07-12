#ifndef __NETX4000_SDIO_H__
#define __NETX4000_SDIO_H__

#include "netx_consoleapp.h"

typedef struct SDIO_OPTIONS_STRUCT
{
	unsigned long   ulPowerUpTimeoutTicks;
	unsigned long   ulResetDelayTicks;
	unsigned long   ulInitialSpeedKHz;
	unsigned long   ulMaximumSpeedKHz;
	unsigned long   ulInitialClockGenerationUs;
	unsigned short ausPortControl[8];
	unsigned char   ucHwTimeoutExponentInitialization;
	unsigned char   ucHwTimeoutExponentTransfer;
} SDIO_OPTIONS_T;


typedef struct SDIO_HANDLE_STRUCT
{
	const SDIO_OPTIONS_T *ptSdioOptions;
	unsigned long ulCurrentSpeedKHz;
	unsigned int  uiCardIsHC;
	unsigned int  uiCardIsMMC;
	unsigned long ulHwCommandTimeoutExponent;
	unsigned long ulSwCommandTimeoutUs;
	unsigned long ulRCA;
	
	unsigned long ulSizeKB;
} SDIO_HANDLE_T;

int sdio_detect(SDIO_HANDLE_T *ptSdioHandle, const SDIO_OPTIONS_T *ptSdioOptions);
int sdio_read_sector(SDIO_HANDLE_T *ptSdioHandle, unsigned long ulSectorId, unsigned long *pulRead);



#endif  /* __NETX4000_SDIO_H__ */

