/***************************************************************************
 *   Copyright (C) 2019 by Hilscher GmbH                                   *
 *   cthelen@hilscher.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program. If not, see                          *
 *   <https://www.gnu.org/licenses/>.                                      *
 ***************************************************************************/


#include "cr7_global_timer.h"

#include "netx_io_areas.h"



#define MSK_NX4000_cr7_global_timer_control_timer_enable      0x00000001U
#define SRT_NX4000_cr7_global_timer_control_timer_enable      0U

#define MSK_NX4000_cr7_global_timer_control_comp_enable       0x00000002U
#define SRT_NX4000_cr7_global_timer_control_comp_enable       1U

#define MSK_NX4000_cr7_global_timer_control_irq_enable        0x00000004U
#define SRT_NX4000_cr7_global_timer_control_irq_enable        2U

#define MSK_NX4000_cr7_global_timer_control_auto_increment    0x00000008U
#define SRT_NX4000_cr7_global_timer_control_auto_increment    3U

#define MSK_NX4000_cr7_global_timer_control_prescaler         0x0000ff00U
#define SRT_NX4000_cr7_global_timer_control_prescaler         8U


typedef struct CR7_GLOBAL_TIMER_STRUCT
{
	volatile unsigned long  ulCounterLo;
	volatile unsigned long  ulCounterHi;
	volatile unsigned long  ulControl;
	volatile unsigned long  ulInterruptStatus;
	volatile unsigned long  ulComparatorLo;
	volatile unsigned long  ulComparatorHi;
	volatile unsigned long  ulAutoIncrement;
} CR7_GLOBAL_TIMER_T;

#define Addr_NX4000_cr7_global_timer 0xfaf00200U
#define NX4000_DEF_ptCr7GlobalTimerArea CR7_GLOBAL_TIMER_T * const ptCr7GlobalTimerArea = (CR7_GLOBAL_TIMER_T * const)Addr_NX4000_cr7_global_timer;


void cr7_global_timer_initialize(void)
{
	HOSTDEF(ptCr7GlobalTimerArea);


	/* Stop the timer. */
	ptCr7GlobalTimerArea->ulControl = 0;

	/* Reset the timer value.
	 * NOTE: the order of the write operations seems to be important.
	 */
	ptCr7GlobalTimerArea->ulCounterLo = 0;
	ptCr7GlobalTimerArea->ulCounterHi = 0;

	/* Start the timer. */
	ptCr7GlobalTimerArea->ulControl = MSK_NX4000_cr7_global_timer_control_timer_enable;
}



unsigned long long cr7_global_timer_get_ticks(void)
{
	HOSTDEF(ptCr7GlobalTimerArea);
	union TIMER_VALUE_UNION
	{
		unsigned long ul[2];
		unsigned long long ull;
	} tTimerValue;
	unsigned long ulLastHiRead;
	unsigned long ulValue;


	/* NOTE: This routine looks quite sick, but the ARM TRM explicitly
	 * forbids 64bit access and describes this way.
	 *
	 * Looks like there is no latch register in this cheap shit.
	 */

	/* Read the upper DWORD. */
	ulValue = ptCr7GlobalTimerArea->ulCounterHi;

	do
	{
		/* Remember the result of the last read of the upper DWORD. */
		ulLastHiRead = ulValue;

		/* Read the lower DWORD. */
		tTimerValue.ul[0] = ptCr7GlobalTimerArea->ulCounterLo;

		/* Read the upper DWORD again. Try again if it changed while
		 * reading the lower part.
		 */
		ulValue = ptCr7GlobalTimerArea->ulCounterHi;
	} while( ulValue!=ulLastHiRead );
	tTimerValue.ul[1] = ulLastHiRead;

	/* Return the complete 64bit value of the timer. */
	return tTimerValue.ull;
}



int cr7_global_timer_elapsed(TIMER_HANDLE_T *ptHandle)
{
	unsigned long long ullDiff;


	/* Get the current timer value and get the difference to the start time. */
	ullDiff = cr7_global_timer_get_ticks() - ptHandle->ullStart;

	return (ullDiff>=ptHandle->ullDuration);
}



void cr7_global_timer_start_ticks(TIMER_HANDLE_T *ptHandle, unsigned long ulDelayTicks)
{
	/* Get the current tick value of the counter. */
	ptHandle->ullStart = cr7_global_timer_get_ticks();

	/* Set the duration in ticks. */
	ptHandle->ullDuration = ulDelayTicks;
}



void cr7_global_timer_start_us(TIMER_HANDLE_T *ptHandle, unsigned long ulDelayUs)
{
	/* Get the current tick value of the counter. */
	ptHandle->ullStart = cr7_global_timer_get_ticks();

	/* Convert the delay from microseconds to ticks. */
	ptHandle->ullDuration = CR7_GLOBAL_TIMER_US_TO_TICKS(ulDelayUs);
}



void cr7_global_timer_start_ms(TIMER_HANDLE_T *ptHandle, unsigned long ulDelayMs)
{
	/* Get the current tick value of the counter. */
	ptHandle->ullStart = cr7_global_timer_get_ticks();

	/* Convert the delay from milliseconds to ticks. */
	ptHandle->ullDuration = CR7_GLOBAL_TIMER_MS_TO_TICKS(ulDelayMs);
}



void cr7_global_timer_delay_ticks(unsigned long ulDelayTicks)
{
	TIMER_HANDLE_T tHandle;
	int iElapsed;


	/* Start the timer. */
	cr7_global_timer_start_ticks(&tHandle, ulDelayTicks);

	/* Delay. */
	do
	{
		iElapsed = cr7_global_timer_elapsed(&tHandle);
	} while( iElapsed==0 );
}



void cr7_global_timer_delay_us(unsigned long ulDelayUs)
{
	TIMER_HANDLE_T tHandle;
	int iElapsed;


	/* Start the timer. */
	cr7_global_timer_start_us(&tHandle, ulDelayUs);

	/* Delay. */
	do
	{
		iElapsed = cr7_global_timer_elapsed(&tHandle);
	} while( iElapsed==0 );
}



void cr7_global_timer_delay_ms(unsigned long ulDelayMs)
{
	TIMER_HANDLE_T tHandle;
	int iElapsed;


	/* Start the timer. */
	cr7_global_timer_start_ms(&tHandle, ulDelayMs);

	/* Delay. */
	do
	{
		iElapsed = cr7_global_timer_elapsed(&tHandle);
	} while( iElapsed==0 );
}


