/*************************************************************************** 
 *   Copyright (C) 2011 by Hilscher GmbH                                   * 
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


#include "flasher_interface.h"

#ifndef __UNITS_H__
#define __UNITS_H__


typedef struct
{
	unsigned int uiUnitIndex;
	const char *pcName;
	void * const pvUnit;
} UNIT_TABLE_ENTRY_T;

#define UNIT_TABLE_MAX_ENTRIES 4

typedef struct
{
	size_t sizEntries;
	const UNIT_TABLE_ENTRY_T atEntries[UNIT_TABLE_MAX_ENTRIES];
} UNIT_TABLE_T;



typedef struct
{
	BUS_T tBusId;
	const char *pcName;
	const UNIT_TABLE_T *ptUnits;
} BUS_TABLE_ENTRY_T;


#define BUS_TABLE_MAX_ENTRIES 4

typedef struct
{
	size_t sizEntries;
	const BUS_TABLE_ENTRY_T atEntries[BUS_TABLE_MAX_ENTRIES];
} BUS_TABLE_T;


/*-------------------------------------------------------------------------*/

size_t units_make_bus_table(unsigned char *pucBuffer, size_t sizBufferMaxSize);
size_t units_make_unit_table(BUS_T tBusId, unsigned char *pucBuffer, size_t sizBufferMaxSize);


#endif  /* __UNITS_H__ */

