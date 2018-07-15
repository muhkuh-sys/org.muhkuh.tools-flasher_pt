/***************************************************************************
 *   Copyright (C) 2016 by Hilscher GmbH                                   *
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

#ifndef __INTERNAL_FLASH_H__
#define __INTERNAL_FLASH_H__


typedef enum INTERNAL_FLASH_TYPE_ENUM
{
	INTERNAL_FLASH_TYPE_Unknown = 0,
	INTERNAL_FLASH_TYPE_MAZ_V0 = 1    /* The internal flash from the netX90_MPW. */
} INTERNAL_FLASH_TYPE_T;



typedef struct INTERNAL_FLASH_CONFIGURATION_STRUCT
{
	unsigned int uiUnit;
	unsigned int uiChipSelect;
} INTERNAL_FLASH_CONFIGURATION_T;



typedef enum INTERNAL_FLASH_AREA_ENUM
{
	INTERNAL_FLASH_AREA_Unknown       =  0,
	INTERNAL_FLASH_AREA_Flash0_Main   =  1,
	INTERNAL_FLASH_AREA_Flash0_Info   =  2,
	INTERNAL_FLASH_AREA_Flash0_InfoK  =  3,
	INTERNAL_FLASH_AREA_Flash1_Main   =  4,
	INTERNAL_FLASH_AREA_Flash1_Info   =  5,
	INTERNAL_FLASH_AREA_Flash1_InfoK  =  6,
	INTERNAL_FLASH_AREA_Flash2_Main   =  7,
	INTERNAL_FLASH_AREA_Flash2_Info   =  8,
	INTERNAL_FLASH_AREA_Flash2_InfoK  =  9,
	INTERNAL_FLASH_AREA_Flash01_Main  = 10
} INTERNAL_FLASH_AREA_T;



typedef struct INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_STRUCT
{
	int iMain0_Info1_InfoK2;
	unsigned long ulSizeInBytes;
	INTERNAL_FLASH_AREA_T tArea;
} INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T;



typedef struct INTERNAL_FLASH_STRUCT
{
	INTERNAL_FLASH_TYPE_T tType;
	union
	{
		INTERNAL_FLASH_ATTRIBUTES_MAZ_V0_T tMazV0;
	} uAttributes;
} INTERNAL_FLASH_T;


#endif  /* __INTERNAL_FLASH_H__ */
