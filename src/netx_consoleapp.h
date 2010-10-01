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

#ifndef __NETX_CONSOLEAPP_H__
#define __NETX_CONSOLEAPP_H__

/*-------------------------------------------------------------------------*/

typedef enum {
        NETX_CONSOLEAPP_RESULT_OK = 0,
        NETX_CONSOLEAPP_RESULT_ERROR = 1
} NETX_CONSOLEAPP_RESULT_T;

typedef struct {
        unsigned int ulReturnValue;
        void *pvInitParams;
        void *pvReturnMessage;
} NETX_CONSOLEAPP_PARAMETER_T;

/*-------------------------------------------------------------------------*/

void netx_consoleapp_init(void);
NETX_CONSOLEAPP_RESULT_T netx_consoleapp_main(NETX_CONSOLEAPP_PARAMETER_T *ptTestParam);
NETX_CONSOLEAPP_PARAMETER_T *netx_consoleapp_getParameters(void);

/*-------------------------------------------------------------------------*/

#endif  /* __NETX_TEST_H__ */
