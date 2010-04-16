/***************************************************************************
 *   Copyright (C) 2005, 2006, 2007, 2008, 2009 by Hilscher GmbH           *
 *                                                                         *
 *   Author: Christoph Thelen (cthelen@hilscher.com)                       *
 *                                                                         *
 *   Redistribution or unauthorized use without expressed written          *
 *   agreement from the Hilscher GmbH is forbidden.                        *
 ***************************************************************************/

#ifndef __CONSOLE_IO_H__
#define __CONSOLE_IO_H__


#include <stdarg.h>
#include <stddef.h>


typedef enum
{
	CONSOLE_LINEFEED_LF,		/* for Unix, Linux, Amiga, BeOS and MacOS X */
	CONSOLE_LINEFEED_CR,		/* for Apple II, old MacOS, OS-9 and C64 */
	CONSOLE_LINEFEED_CRLF		/* for Dos, Windows, CP/M, OS/2, and Symbian */
} CONSOLE_LINEFEED_T;


void uprintf(const char *pcFmt, ...);
void hexdump(const unsigned char *pcData, size_t sizData);


#endif	/* __CONSOLE_IO_H__ */
