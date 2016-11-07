/* Cortex M systick delay routine. */

#include "cortexm_systick.h"


typedef struct CORTEXM_SYSTICK_STRUCT
{
	unsigned long ulSystCsr;
	unsigned long ulSystRvr;
	unsigned long ulSystCvr;
	unsigned long ulSystCalib;
} CORTEXM_SYSTICK_T;

/* RO
 * Returns 1 if timer counted to 0 since last time this register
 * was read. COUNTFLAG is set by a count transition from 1
 * => 0. COUNTFLAG is cleared on read or by a write to the
 * Current Value register.
 */
#define MSK_CORTEXM_SYSTICK_SYSTCSR_COUNTFLAG 0x00010000U
#define SRT_CORTEXM_SYSTICK_SYSTCSR_COUNTFLAG 16

/* R/W
 * 0: clock source is (optional) external reference clock
 * 1: core clock used for SysTick
 * If no external clock provided, this bit will read as 1 and
 * ignore writes.
 */
#define MSK_CORTEXM_SYSTICK_SYSTCSR_CLKSOURCE 0x00000004U
#define SRT_CORTEXM_SYSTICK_SYSTCSR_CLKSOURCE 2

/* R/W
 * If 1, counting down to 0 will cause the SysTick exception to
 * be pended. Clearing the SysTick Current Value register by a
 * register write in software will not cause SysTick to be
 * pended.
 */
#define MSK_CORTEXM_SYSTICK_SYSTCSR_TICKINT   0x00000002U
#define SRT_CORTEXM_SYSTICK_SYSTCSR_TICKINT   1

/* R/W
 * 0: the counter is disabled
 * 1: the counter will operate in a multi-shot manner.
 */
#define MSK_CORTEXM_SYSTICK_SYSTCSR_ENABLE    0x00000001U
#define SRT_CORTEXM_SYSTICK_SYSTCSR_ENABLE    0


/* R/W
 * Value to load into the Current Value register when the counter
 * reaches 0.
 */
#define MSK_CORTEXM_SYSTICK_SYSTRVR_RELOAD    0x00ffffffU
#define SRT_CORTEXM_SYSTICK_SYSTRVR_RELOAD    0


/* R/W
 * Current counter value. This is the value of the counter at the time
 * it is sampled. The counter does not provide read-modify-write
 * protection.The register is write-clear. A software write of any
 * value will clear the register to 0. Unsupported bits RAZ (see
 * SysTick Reload Value register).
 */
#define MSK_CORTEXM_SYSTICK_SYSTCVR_CURRENT   0xffffffffU
#define SRT_CORTEXM_SYSTICK_SYSTCVR_CURRENT   0


/* RO
 * If reads as 1, the Reference clock is not provided – the
 * CLKSOURCE bit of the SysTick Control and Status register will
 * be forced to 1 and cannot be cleared to 0.
 */
#define MSK_CORTEXM_SYSTICK_SYSTCALIB_NOREF   0x80000000U
#define SRT_CORTEXM_SYSTICK_SYSTCALIB_NOREF   31

/* RO
 * If reads as 1, the calibration value for 10ms is inexact (due to clock
 * frequency).
 */
#define MSK_CORTEXM_SYSTICK_SYSTCALIB_SKEW    0x40000000U
#define SRT_CORTEXM_SYSTICK_SYSTCALIB_SKEW    30

/* RO
 * An optional Reload value to be used for 10ms (100Hz) timing,
 * subject to system clock skew errors. If the value reads as 0, the
 * calibration value is not known.
 */
#define MSK_CORTEXM_SYSTICK_SYSTCALIB_TENMS   0x00ffffffU
#define SRT_CORTEXM_SYSTICK_SYSTCALIB_TENMS   0


int systick_delay_us(unsigned long ulDelayUs)
{
	CORTEXM_SYSTICK_T *ptSysTick = (CORTEXM_SYSTICK_T*)(0xE000E010);
	unsigned long ulValue;
	unsigned long ulCalib1us;
	unsigned long ulDelay;
	int iResult;


	/* Be pessimistic. */
	iResult = -1;

	/* Get the calibration value for 10ms. */
	ulValue   = ptSysTick->ulSystCalib;
	ulValue  &= MSK_CORTEXM_SYSTICK_SYSTCALIB_TENMS;
	ulValue >>= SRT_CORTEXM_SYSTICK_SYSTCALIB_TENMS;

	/* The value is 0 if there is no calibration data. */
	if( ulValue!=0 )
	{
		ulCalib1us = ulValue / 10000;
		ulDelay  = ulCalib1us * ulDelayUs;

		/* Check for an overflow. */
		if( ulDelay>=ulDelayUs && (ulDelay&(~MSK_CORTEXM_SYSTICK_SYSTRVR_RELOAD))==0 )
		{
			/* Stop the counter. */
			ptSysTick->ulSystCsr = 0;
			/* Count down and then stop (i.e. do not reload the timer). */
			ptSysTick->ulSystRvr = ulDelay;
			/* Trigger a counter reload. */
			ptSysTick->ulSystCvr = 0;

			/* Start the counter. */
			ptSysTick->ulSystCsr = MSK_CORTEXM_SYSTICK_SYSTCSR_ENABLE;

			/* Wait until the counter is stopped. */
			do
			{
				ulValue  = ptSysTick->ulSystCsr;
				ulValue &= MSK_CORTEXM_SYSTICK_SYSTCSR_COUNTFLAG;
			} while( ulValue==0 );

			iResult = 0;
		}
	}

	return iResult;
}
