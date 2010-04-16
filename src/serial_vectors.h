/***************************************************************************
 *   Copyright (C) 2008 by Christoph Thelen                                *
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


#ifndef __SERIAL_VECTORS_H__
#define __SERIAL_VECTORS_H__

#if ASIC_TYP==10
typedef unsigned char	(*pfnSerialGet_t)	(unsigned int uiHandle);
typedef void		(*pfnSerialPut_t)	(unsigned int uiHandle, unsigned int iChar);
typedef unsigned int	(*pfnSerialPeek_t)	(unsigned int uiHandle);
typedef void		(*pfnSerialFlush_t)	(unsigned int uiHandle);

#define SERIAL_GET() tSerialVectors.fn.fnGet(0)
#define SERIAL_PUT(c) tSerialVectors.fn.fnPut(0,c)
#define SERIAL_PEEK() tSerialVectors.fn.fnPeek(0)
#define SERIAL_FLUSH() tSerialVectors.fn.fnFlush(0)

#else
typedef unsigned char	(*pfnSerialGet_t)	(void);
typedef void		(*pfnSerialPut_t)	(unsigned int iChar);
typedef unsigned int	(*pfnSerialPeek_t)	(void);
typedef void		(*pfnSerialFlush_t)	(void);

#define SERIAL_GET() tSerialVectors.fn.fnGet()
#define SERIAL_PUT(c) tSerialVectors.fn.fnPut(c)
#define SERIAL_PEEK() tSerialVectors.fn.fnPeek()
#define SERIAL_FLUSH() tSerialVectors.fn.fnFlush()

#endif

typedef struct
{
	pfnSerialGet_t fnGet;
	pfnSerialPut_t fnPut;
	pfnSerialPeek_t fnPeek;
	pfnSerialFlush_t fnFlush;
} SerialCommFn_t;

typedef union
{
	SerialCommFn_t fn;
	unsigned long aul[4];
} SerialCommUiFn_t;

extern SerialCommUiFn_t tSerialVectors;

#endif	/* __SERIAL_VECTORS_H__ */


