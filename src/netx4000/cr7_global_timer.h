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

 #ifndef __CR7_PRIVATE_TIMER_H__
#define __CR7_PRIVATE_TIMER_H__

#if ASIC_ENV==ASIC_ENV_SCIT_BOARD
/* The CR7 runs with 1/10 of the real speed. This is 50ns. */
#       define NX4000_GLOBAL_TIMER_TICK_NS 50

#       define CR7_GLOBAL_TIMER_US_TO_TICKS(ulDelayUs)  (((unsigned long long)ulDelayUs)*20ULL)
#       define CR7_GLOBAL_TIMER_MS_TO_TICKS(ulDelayMs)  (((unsigned long long)ulDelayMs)*20000ULL)
#else
/* The global timer seems to run on half of the peripheral clock. This is 5ns in the simulation. */
#       define NX4000_GLOBAL_TIMER_TICK_NS 5

#       define CR7_GLOBAL_TIMER_US_TO_TICKS(ulDelayUs)  (((unsigned long long)ulDelayUs)*200ULL)
#       define CR7_GLOBAL_TIMER_MS_TO_TICKS(ulDelayMs)  (((unsigned long long)ulDelayMs)*200000ULL)
#endif




typedef struct TIMER_HANDLE_STRUCT
{
	unsigned long long ullStart;
	unsigned long long ullDuration;
} TIMER_HANDLE_T;


void cr7_global_timer_initialize(void);

int cr7_global_timer_elapsed(TIMER_HANDLE_T *ptHandle);
unsigned long long cr7_global_timer_get_ticks(void);

void cr7_global_timer_start_ticks(TIMER_HANDLE_T *ptHandle, unsigned long ulDelayTicks);
void cr7_global_timer_start_us(TIMER_HANDLE_T *ptHandle, unsigned long ulDelayUs);
void cr7_global_timer_start_ms(TIMER_HANDLE_T *ptHandle, unsigned long ulDelayMs);

void cr7_global_timer_delay_ticks(unsigned long ulDelayTicks);
void cr7_global_timer_delay_us(unsigned long ulDelayUs);
void cr7_global_timer_delay_ms(unsigned long ulDelayMs);


#endif  /* __CR7_PRIVATE_TIMER_H__ */

