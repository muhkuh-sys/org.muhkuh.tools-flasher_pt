/***************************************************************************
 *   Copyright (C) 2012 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "systime.h"

#define DEV_FREQUENCY 100000000


void systime_init(void)
{
	HOSTDEF(ptSystimeArea)


	/* set systime border to 1ms */
	ptSystimeArea->ulSystime_border = (DEV_FREQUENCY/100U)-1U;
	ptSystimeArea->ulSystime_count_value = 10U<<28U;

#if ASIC_TYP==50
	/* disable systime compare */
	ptSystimeArea->ulSystime_s_compare_enable = 0;

	/* reset any pending systime irqs */
	ptSystimeArea->ulSystime_s_compare_irq = 1;
#endif
}


unsigned long systime_get_ms(void)
{
	HOSTDEF(ptSystimeArea)


	return ptSystimeArea->ulSystime_s;
}


int systime_elapsed(unsigned long ulStart, unsigned long ulDuration)
{
	HOSTDEF(ptSystimeArea)


	unsigned long ulDiff;


	/* get the time difference */
	ulDiff = ptSystimeArea->ulSystime_s - ulStart;

	return (ulDiff>=ulDuration);
}

