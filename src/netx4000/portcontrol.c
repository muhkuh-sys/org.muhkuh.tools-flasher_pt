
#include "portcontrol.h"

#include "netx_io_areas.h"
/*#include "options.h"*/


#if CFG_DEBUGMSG==1
/*#       include "uprintf_debug.h"*/

#       define DEBUGZONE(n)  (g_t_romloader_options.t_debug_settings.ul_portcontrol&(0x00000001<<(n)))

	/*
	 * These defines must match the ZONE_* defines
	 */
#       define DBG_ZONE_ERROR		0
#       define DBG_ZONE_WARNING	1
#       define DBG_ZONE_FUNCTION	2
#       define DBG_ZONE_INIT		3
#       define DBG_ZONE_VERBOSE	7

#       define ZONE_ERROR		DEBUGZONE(DBG_ZONE_ERROR)
#       define ZONE_WARNING		DEBUGZONE(DBG_ZONE_WARNING)
#       define ZONE_FUNCTION		DEBUGZONE(DBG_ZONE_FUNCTION)
#       define ZONE_INIT		DEBUGZONE(DBG_ZONE_INIT)
#       define ZONE_VERBOSE		DEBUGZONE(DBG_ZONE_VERBOSE)

#       define DEBUGMSG(cond,...) ((void)((cond)?(uprintf_debug(__VA_ARGS__)),1:0))
#else
#       define DEBUGMSG(cond,...) ((void)0)
#endif



void portcontrol_init(void)
{
	size_t sizCfgCnt;
	size_t sizCfgEnd;
	unsigned long ulValue;
	volatile unsigned long *pulPortControl;


	DEBUGMSG(ZONE_FUNCTION, "+portcontrol_init\n");

	pulPortControl = (volatile unsigned long*)HOSTADDR(PORTCONTROL);

	/* Loop over all entries in the options table. */
	sizCfgCnt = 0;
	sizCfgEnd = sizeof(g_t_romloader_options.ausPortControlDefault) / sizeof(g_t_romloader_options.ausPortControlDefault[0]);
	while( sizCfgCnt<sizCfgEnd )
	{
		ulValue = g_t_romloader_options.ausPortControlDefault[sizCfgCnt];
		if( ulValue!=PORTCONTROL_SKIP )
		{
			pulPortControl[sizCfgCnt] = ulValue;
		}
		++sizCfgCnt;
	}

	DEBUGMSG(ZONE_FUNCTION, "-portcontrol_init\n");
}



void portcontrol_apply(const unsigned short *pusIndex, const unsigned short *pusConfiguration, size_t sizConfiguration)
{
	const unsigned short *pusIndexCnt;
	const unsigned short *pusIndexEnd;
	const unsigned short *pusConfigurationCnt;
	unsigned long ulConfiguration;
	unsigned long ulOffset;
	volatile unsigned long *pulPortControl;


	DEBUGMSG(ZONE_FUNCTION, "+portcontrol_apply(0x%08x, 0x%08x, %d)\n", pusIndex, pusConfiguration, sizConfiguration);

	pulPortControl = (volatile unsigned long*)HOSTADDR(PORTCONTROL);

	pusIndexCnt = pusIndex;
	pusIndexEnd = pusIndex + sizConfiguration;
	pusConfigurationCnt = pusConfiguration;
	while( pusIndexCnt<pusIndexEnd )
	{
		/* Get the value. */
		ulOffset = (unsigned long)(*(pusIndexCnt++));
		ulConfiguration = (unsigned long)(*(pusConfigurationCnt++));

		if( ulConfiguration!=PORTCONTROL_SKIP && ulOffset!=PORTCONTROL_SKIP )
		{
			/* Write the configuration. */
			DEBUGMSG(ZONE_VERBOSE, "P[0x%04x] = 0x%08x\n", ulOffset, ulConfiguration);
			pulPortControl[ulOffset] = ulConfiguration;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, "-portcontrol_apply\n");
}



void portcontrol_apply_mmio(const unsigned char *pucMmioIndex, const unsigned short *pusConfiguration, size_t sizConfiguration)
{
	const unsigned char *pucMmioIndexCnt;
	const unsigned char *pucMmioIndexEnd;
	const unsigned short *pusConfigurationCnt;
	unsigned long ulConfiguration;
	unsigned long ulOffset;
	volatile unsigned long *pulPortControl;


	DEBUGMSG(ZONE_FUNCTION, "+portcontrol_apply_mmio(0x%08x, 0x%08x, %d)\n", pucMmioIndex, pusConfiguration, sizConfiguration);

	pulPortControl = (volatile unsigned long*)HOSTADDR(PORTCONTROL);

	pucMmioIndexCnt = pucMmioIndex;
	pucMmioIndexEnd = pucMmioIndex + sizConfiguration;
	pusConfigurationCnt = pusConfiguration;
	while( pucMmioIndexCnt<pucMmioIndexEnd )
	{
		ulOffset = (unsigned long)(*(pucMmioIndexCnt++));
		ulConfiguration = (unsigned long)(*(pusConfigurationCnt++));

		if( ulOffset!=0xffU && ulConfiguration!=PORTCONTROL_SKIP )
		{
			/* MMIO0 is at 16,11.
			 * From MMIO1 on the pins start at 3,0 and continue sequentially. */
			if( ulOffset==0 )
			{
				ulOffset += PORTCONTROL_INDEX(16,11);
			}
			else
			{
				ulOffset += PORTCONTROL_INDEX( 3, 0);
			}

			/* Write the configuration. */
			DEBUGMSG(ZONE_VERBOSE, "P[0x%04x] = 0x%08x\n", ulOffset, ulConfiguration);
			pulPortControl[ulOffset] = ulConfiguration;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, "-portcontrol_apply_mmio\n");
}



void portcontrol_restore(const unsigned short *pusIndex, size_t sizConfiguration)
{
	const unsigned short *pusIndexCnt;
	const unsigned short *pusIndexEnd;
	unsigned long ulConfiguration;
	unsigned long ulOffset;
	volatile unsigned long *pulPortControl;


	DEBUGMSG(ZONE_FUNCTION, "+portcontrol_restore(0x%08x, %d)\n", pusIndex, sizConfiguration);

	pulPortControl = (volatile unsigned long*)HOSTADDR(PORTCONTROL);

	pusIndexCnt = pusIndex;
	pusIndexEnd = pusIndex + sizConfiguration;
	while( pusIndexCnt<pusIndexEnd )
	{
		/* Get the value. */
		ulOffset = (unsigned long)(*(pusIndexCnt++));
		ulConfiguration = (unsigned long)(g_t_romloader_options.ausPortControlDefault[ulOffset]);

		if( ulConfiguration!=PORTCONTROL_SKIP && ulOffset!=PORTCONTROL_SKIP )
		{
			/* Write the configuration. */
			DEBUGMSG(ZONE_VERBOSE, "P[0x%04x] = 0x%08x\n", ulOffset, ulConfiguration);
			pulPortControl[ulOffset] = ulConfiguration;
		}
	}

	DEBUGMSG(ZONE_FUNCTION, "-portcontrol_restore\n");
}



void portcontrol_restore_mmio(const unsigned char *pucMmioIndex, size_t sizConfiguration)
{
	const unsigned char *pucMmioIndexCnt;
	const unsigned char *pucMmioIndexEnd;
	unsigned long ulConfiguration;
	unsigned long ulOffset;
	volatile unsigned long *pulPortControl;


	DEBUGMSG(ZONE_FUNCTION, "+portcontrol_restore_mmio(0x%08x, %d)\n", pucMmioIndex, sizConfiguration);

	pulPortControl = (volatile unsigned long*)HOSTADDR(PORTCONTROL);

	pucMmioIndexCnt = pucMmioIndex;
	pucMmioIndexEnd = pucMmioIndex + sizConfiguration;
	while( pucMmioIndexCnt<pucMmioIndexEnd )
	{
		/* Get the value. */
		ulOffset = (unsigned long)(*(pucMmioIndexCnt++));
		if( ulOffset!=0xffU )
		{
			/* MMIO0 is at 16,11.
			 * From MMIO1 on the pins start at 3,0 and continue sequentially. */
			if( ulOffset==0 )
			{
				ulOffset += PORTCONTROL_INDEX(16,11);
			}
			else
			{
				ulOffset += PORTCONTROL_INDEX( 3, 0);
			}

			ulConfiguration = (unsigned long)(g_t_romloader_options.ausPortControlDefault[ulOffset]);
			if( ulConfiguration!=PORTCONTROL_SKIP )
			{
				/* Write the configuration. */
				DEBUGMSG(ZONE_VERBOSE, "P[0x%04x] = 0x%08x\n", ulOffset, ulConfiguration);
				pulPortControl[ulOffset] = ulConfiguration;
			}
		}
	}

	DEBUGMSG(ZONE_FUNCTION, "-portcontrol_restore_mmio\n");
}
