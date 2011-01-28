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

#include "units.h"

#include "board.h"


static const BUS_TABLE_ENTRY_T *find_bus_entry_by_id(BUS_T tBusId)
{
	const BUS_TABLE_ENTRY_T *ptCnt;
	const BUS_TABLE_ENTRY_T *ptEnd;
	const BUS_TABLE_ENTRY_T *ptHit;


	/* Search for the bus id. */
	ptCnt = tBusTable.atEntries;
	ptEnd = tBusTable.atEntries + tBusTable.sizEntries;
	ptHit = NULL;
	while( ptCnt<ptEnd )
	{
		if( ptCnt->tBusId==tBusId )
		{
			ptHit = ptCnt;
			break;
		}
		++ptCnt;
	}

	return ptHit;
}


size_t units_make_bus_table(unsigned char *pucBuffer, size_t sizBufferMaxSize)
{
	unsigned char *pucBufferCnt;
	unsigned char *pucBufferEnd;
	const BUS_TABLE_ENTRY_T *ptCnt;
	const BUS_TABLE_ENTRY_T *ptEnd;
	size_t sizEntrySize;


	/* Init the output pointer. */
	pucBufferCnt = pucBuffer;
	pucBufferEnd = pucBuffer + sizBufferMaxSize;

	if( sizBufferMaxSize>0 )
	{
		/* Write the number of entries. */
		*(pucBufferCnt++) = (unsigned char)tBusTable.sizEntries;

		/* Loop over all entries in the table. */
		ptCnt = tBusTable.atEntries;
		ptEnd = tBusTable.atEntries + tBusTable.sizEntries;
		while( ptCnt<ptEnd )
		{
			/* The entry's size is the bus id byte and the name with trailing 0. */
			sizEntrySize = 1 + strlen(ptCnt->pcName) + 1;
			if( pucBufferCnt+sizEntrySize>=pucBufferEnd )
			{
				break;
			}

			/* Write the entry's bus id. */
			*pucBufferCnt = (unsigned char)ptCnt->tBusId;

			/* Copy the name including the trailing 0. */
			memcpy(pucBufferCnt+1, ptCnt->pcName, sizEntrySize);

			pucBufferCnt += sizEntrySize;
			++ptCnt;
		}
	}

	return (size_t)(pucBufferCnt-pucBuffer);
}


size_t units_make_unit_table(BUS_T tBusId, unsigned char *pucBuffer, size_t sizBufferMaxSize)
{
	const BUS_TABLE_ENTRY_T *ptBus;
	const UNIT_TABLE_T *ptUnits;
	unsigned char *pucBufferCnt;
	unsigned char *pucBufferEnd;
	const UNIT_TABLE_ENTRY_T *ptCnt;
	const UNIT_TABLE_ENTRY_T *ptEnd;
	size_t sizEntrySize;


	/* Init the output pointer. */
	pucBufferCnt = pucBuffer;
	pucBufferEnd = pucBuffer + sizBufferMaxSize;

	ptBus = find_bus_entry_by_id(tBusId);
	if( ptBus!=NULL )
	{
		ptUnits = ptBus->ptUnits;
		if( ptUnits!=NULL )
		{
			if( sizBufferMaxSize>0 )
			{
				/* Write the number of entries. */
				*(pucBufferCnt++) = (unsigned char)ptUnits->sizEntries;

				/* Loop over all entries in the table. */
				ptCnt = ptUnits->atEntries;
				ptEnd = ptUnits->atEntries + ptUnits->sizEntries;
				while( ptCnt<ptEnd )
				{
					/* The entry's size is the unit id byte and the name with trailing 0. */
					sizEntrySize = 1 + strlen(ptCnt->pcName) + 1;
					if( pucBufferCnt+sizEntrySize>=pucBufferEnd )
					{
						break;
					}

					/* Write the entry's bus id. */
					*pucBufferCnt = (unsigned char)ptCnt->uiUnitIndex;

					/* Copy the name including the trailing 0. */
					memcpy(pucBufferCnt+1, ptCnt->pcName, sizEntrySize);

					pucBufferCnt += sizEntrySize;
					++ptCnt;
				}
			}
		}
	}

	return (size_t)(pucBufferCnt-pucBuffer);
}

