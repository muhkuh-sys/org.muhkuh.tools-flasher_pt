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

#include "rdyrun.h"

#if ASIC_TYP==500 || ASIC_TYP==100
#	include "netx_io_areas.h"
#elif ASIC_TYP==56 || ASIC_TYP==50 || ASIC_TYP==10
#	include "i2c_hifsta.h"
#endif

/* ------------------------------------- */

void setRdyRunLed(RDYRUN_LED_T tMode)
{
#if ASIC_TYP==500 || ASIC_TYP==100
	HOSTDEF(ptNetxControlledGlobalRegisterBlock1Area);
	unsigned long ulBlinki;


	switch(tMode)
	{
	default:
	case RDYRUN_LED_OFF:
		ulBlinki = 0x030c0000;
		break;
	
	case RDYRUN_LED_GREEN:
		ulBlinki = 0x030c0002;
		break;
	
	case RDYRUN_LED_RED:
		ulBlinki = 0x030c0001;
		break;
	}
	
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulBlinki;
#elif ASIC_TYP==56 || ASIC_TYP==50 || ASIC_TYP==10
	switch(tMode)
	{
	default:
	case RDYRUN_LED_OFF:
		i2c_hifsta_rdy_off_run_off();
		break;
	
	case RDYRUN_LED_GREEN:
		i2c_hifsta_rdy_on_run_off();
		break;
	
	case RDYRUN_LED_RED:
		i2c_hifsta_rdy_off_run_on();
		break;
	}
#endif
}

/* ------------------------------------- */
