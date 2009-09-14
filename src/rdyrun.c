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

#include "netx_io_areas.h"
#include "rdyrun.h"

/* ------------------------------------- */

void setRdyRunLed(RDYRUN_LED_T tMode)
{
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

  case RDYRUN_LED_INV:
    ulBlinki  = ptNetXGlobalRegBlock1Area->ulSta_netx;
    ulBlinki &= 3;
    ulBlinki ^= 3;
    ulBlinki |= 0x030c0000;
    break;
  }

  ptNetXGlobalRegBlock1Area->ulSta_netx = ulBlinki;
}

/* ------------------------------------- */
