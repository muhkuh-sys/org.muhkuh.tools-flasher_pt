/***************************************************************************
 *   Copyright (C) 2010 by Hilscher GmbH                                   *
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

#include "mmio.h"


void mmio_activate(const unsigned char *pucMmioPins, size_t sizMmioPins, const MMIO_CFG_T *ptMmioValues)
{
	HOSTDEF(ptAsicCtrlArea)
	HOSTDEF(ptMmioCtrlArea)
	const unsigned char *pucCnt;
	const unsigned char *pucEnd;
	unsigned int uiMmioPin;
	MMIO_CFG_T tMmioCfg;


	/* loop over all pins */
	pucCnt = pucMmioPins;
	pucEnd = pucCnt + sizMmioPins;
	do
	{
		/* get the mmio config */
		tMmioCfg = *(ptMmioValues++);
		/* get the pin index */
		uiMmioPin = *(pucCnt++);
		/* is the index valid? */
		if( tMmioCfg!=0xffU && uiMmioPin!=0xffU )
		{
			/* activate the pin */
			ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
			ptMmioCtrlArea->aulMmio_cfg[uiMmioPin] = tMmioCfg;
		}
	} while( pucCnt<pucEnd );
}


void mmio_deactivate(const unsigned char *pucMmioPins, size_t sizMmioPins, const MMIO_CFG_T *ptMmioValues)
{
	HOSTDEF(ptAsicCtrlArea)
	HOSTDEF(ptMmioCtrlArea)
	const unsigned char *pucCnt;
	const unsigned char *pucEnd;
	unsigned int uiMmioPin;
	MMIO_CFG_T tMmioCfg;


	/* loop over all pins */
	pucCnt = pucMmioPins;
	pucEnd = pucCnt + sizMmioPins;
	do
	{
		/* get the mmio config */
		tMmioCfg = *(ptMmioValues++);
		/* get the pin index */
		uiMmioPin = *(pucCnt++);
		/* is the index valid? */
		if( tMmioCfg!=0xffU && uiMmioPin!=0xffU )
		{
			/* deactivate the pin */
			ptAsicCtrlArea->ulAsic_ctrl_access_key = ptAsicCtrlArea->ulAsic_ctrl_access_key;
			ptMmioCtrlArea->aulMmio_cfg[uiMmioPin] = MMIO_CFG_DISABLE;
		}
	} while( pucCnt<pucEnd );
}

