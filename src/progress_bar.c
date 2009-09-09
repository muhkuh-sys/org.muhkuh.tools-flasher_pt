/***************************************************************************
 *   Copyright (C) 2008 by Hilscher GmbH                                   *
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
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "progress_bar.h"
#include "uprintf.h"
#include "netx_io_areas.h"

/* ------------------------------------- */
/*  100 Mhz */
#define DEV_FREQUENCY 100000000L

/* ------------------------------------- */

static unsigned long ulProgressBar_MaxValue;

/* ------------------------------------- */

void progress_bar_restart_counter(void);
void progress_bar_show_progress  (unsigned long ulPosition);

/* ------------------------------------- */

void progress_bar_init(unsigned long ulMaxvalue)
{
	/*  remember max value */
	ulProgressBar_MaxValue = ulMaxvalue;

	/*  setup gpio counter */
	ptNetXGpioArea->aul_gpio_counter_ctrl[0] = 0;
	/*  wait for 0.5 sec */
	ptNetXGpioArea->aul_gpio_counter_max[0] = (DEV_FREQUENCY/2);

	/*  show initial position */
	progress_bar_show_progress(0);

	/*  start counter */
	progress_bar_restart_counter();
}

void progress_bar_set_position(unsigned long ulPosition)
{
	/*  is the counter still running? */
	if( (ptNetXGpioArea->aul_gpio_counter_ctrl[0] & HOSTMSK(gpio_counter0_ctrl_run))==0 )
	{
		/*  counter already stopped -> time to print the progress */
		progress_bar_show_progress(ulPosition);

		/*  restart counter */
		progress_bar_restart_counter();
	}
}

void progress_bar_finalize(void)
{
	progress_bar_show_progress(ulProgressBar_MaxValue);
}

/* ------------------------------------- */

void progress_bar_restart_counter(void)
{
	/*  Clear the current timer value */
	ptNetXGpioArea->aul_gpio_counter_cnt[0] = 0;
	/*  Enable the timer */
	ptNetXGpioArea->aul_gpio_counter_ctrl[0] = HOSTMSK(gpio_counter0_ctrl_run)|HOSTMSK(gpio_counter0_ctrl_once);
}

void progress_bar_show_progress(unsigned long ulPosition)
{
	uprintf("% $8/$8\n", ulPosition, ulProgressBar_MaxValue);
}

/* ------------------------------------- */

