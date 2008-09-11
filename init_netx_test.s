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

        .section .text
        .arm

        .extern netx_consoleapp_init
        .extern top_of_ownstack

        .global NetxConsoleParameter_Init
        .global start

@--------------------------------------

  .func start

start:
        @ save registers on debug console stack
        STMFD   sp!, {r0, r1, r2, lr}

        @ save pointer to netx parameter block
        @ the parameter bock is passed from the netx debug console
        ldr     r1, =NetxConsoleParameter_Init
        str     r0, [r1]

        @ save debug console stack position
        mov     r0, sp
        ldr     r1, =blstack_save
        str     r0, [r1]

        @ set own stack position
        ldr     r0, =top_of_ownstack
        mov     sp, r0

        @ clear .bss section with 0
        mov     r0, #0
        ldr     r1, =__bss_start__
        ldr     r2, =__bss_end__
LoopZI:
        cmp     r1, r2
        strlo   r0, [r1], #4
        blo     LoopZI

        @ call test main routine
        bl      CallNetxMain

        @ restore debug console stack
        ldr     r1, =blstack_save
        ldr     r0, [r1]
        mov     sp, r0

        @ restore registers from debug console stack and return
        ldmfd   sp!, {r0, r1, r2, lr}
        bx      lr

CallNetxMain:
        ldr     r0, =netx_consoleapp_init
        bx      r0

  .endfunc

@--------------------------------------

        .align 4

NetxConsoleParameter_Init:
        .word 0

blstack_save:
        .word 0

@--------------------------------------

  .end

