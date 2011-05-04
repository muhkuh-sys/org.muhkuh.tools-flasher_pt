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

#ifndef __UPRINTF_H__
#define __UPRINTF_H__


#include <stdarg.h>
#include <stddef.h>


typedef enum
{
	CONSOLE_LINEFEED_LF,            /* for Unix, Linux, Amiga, BeOS and MacOS X */
	CONSOLE_LINEFEED_CR,            /* for Apple II, old MacOS, OS-9 and C64 */
	CONSOLE_LINEFEED_CRLF           /* for Dos, Windows, CP/M, OS/2, and Symbian */
} CONSOLE_LINEFEED_T;


void uprintf(const char *pcFmt, ...);
void hexdump(const unsigned char *pcData, size_t sizData);


#endif  /* __UPRINTF_H__ */
