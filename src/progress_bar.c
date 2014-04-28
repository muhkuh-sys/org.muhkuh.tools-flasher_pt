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
#include "systime.h"

/* ------------------------------------- */

static unsigned long ulProgressBar_CurrentValue;
static unsigned long ulProgressBar_MaxValue;
static unsigned long ulProgressBar_TimerHandle;

/* ------------------------------------- */

static void progress_bar_show_progress(unsigned long ulPosition)
{
	uprintf("%% %08x/%08x\n", ulPosition, ulProgressBar_MaxValue);
}

/* ------------------------------------- */


void progress_bar_init(unsigned long ulMaxvalue)
{
	/*  remember max value */
	ulProgressBar_MaxValue = ulMaxvalue;

	/*  Init the timer handle. */
	ulProgressBar_TimerHandle = 0;

	/*  show initial position */
	progress_bar_show_progress(0);
}

void progress_bar_set_position(unsigned long ulPosition)
{
	ulProgressBar_CurrentValue = ulPosition;
	progress_bar_check_timer();
}

void progress_bar_check_timer()
{
	/*  is the counter still running? */
	if( systime_elapsed(ulProgressBar_TimerHandle, 100)!=0 )
	{
		/*  counter already stopped -> time to print the progress */
		progress_bar_show_progress(ulProgressBar_CurrentValue);

		/*  restart counter */
		ulProgressBar_TimerHandle = systime_get_ms();
	}
}


void progress_bar_finalize(void)
{
	progress_bar_show_progress(ulProgressBar_MaxValue);
}

/* ------------------------------------- */

