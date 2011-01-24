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

ENTRY(start)

MEMORY
{
	ROMVECTOR(rx)	: ORIGIN = 0x00000000, LENGTH = 0x00000004
	INTRAM(rwx)	: ORIGIN = 0x00000004, LENGTH = 0x00017ffc
	INTROM(rx)	: ORIGIN = 0x08200000, LENGTH = 0x00010000
	INTROM_HI(rx)	: ORIGIN = 0xff200000, LENGTH = 0x00010000
	DATATCM(rw)	: ORIGIN = 0x04000000, LENGTH = 0x00001000
	SDRAM(rwx)	: ORIGIN = 0x80000000, LENGTH = 0x00020000
}


/* Section Definitions */
SECTIONS
{
	/* bootloader reserved area */
	.bootloader 0x00000000 :
	{
		. = . + 0x8000;
	} >INTRAM


	.code 0x00008000 :
	{
		__LOAD_ADDRESS__ = . ;
		*(.init_code)
		*(.version_info)
		*(.text)
		*(.glue*)
		*(.vfp11_veneer)
		*(.v4_bx)

		/* .rodata section which is used for read-only data (constants) */
		*(.rodata*)

		*(.data)
	} >INTRAM


	.bss :
	{
		__bss_start__ = . ;

		*(.bss)
		*(COMMON)

		__bss_end__ = . ;
	} >INTRAM


	.stack 0x00014000 :
	{
		. = . + 0x3000;
		PROVIDE (stack_top = .);
	} >INTRAM


	.testparameter 0x00017000 :
	{
		. = . + 0x0100;
	} >INTRAM


	.serialvectors ORIGIN(DATATCM)+LENGTH(DATATCM)-0x10 :
	{
		PROVIDE ( tSerialVectors = . );
		. = . + 0x10;
	} >DATATCM


	/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	/* DWARF debug sections.
	 * Symbols in the DWARF debugging sections are relative to the beginning
	 * of the section so we begin them at 0.
	 */
	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
}

