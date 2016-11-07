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

ENTRY(start)

MEMORY
{
	ASSERT_EMPTY(rwx): ORIGIN = 0x00000000, LENGTH = 0
	INTRAM(rwx):       ORIGIN = 0x00024000, LENGTH = 0x0001c000
	IOVECTORS(rw):     ORIGIN = 0x2009FFF0, LENGTH = 0x00000010
}


/* Section Definitions */
SECTIONS
{
	/* NOTE: include all sections here which should be empty. */
	.assert_empty (NOLOAD) :
	{
		*(.data*)
		*(.glue*)
		*(.vfp11_veneer)
		*(.v4_bx)
		*(.iplt)
		*(.rel.dyn)
		*(.rel.iplt)
		*(.igot.plt)
	} >ASSERT_EMPTY

	.code :
	{
		__LOAD_ADDRESS__ = . ;
		KEEP( *(.version_info) )
		*(.text* .rodata*)
	} >INTRAM


	.bss :
	{
		/* .bss section which is used for uninitialized data */
		__bss_start__ = . ;

		*(.bss COMMON)

		__bss_end__ = . ;
		__BUFFER_START__ = .;
	} >INTRAM

	/* NOTE: do not put anything between the bss and the stack section. Here goes the buffer. */

	.stack ORIGIN(INTRAM)+LENGTH(INTRAM)-0x1000 :
	{
		__BUFFER_END__ = .;
		. = . + 0x1000;
		PROVIDE (stack_top = .);
	} >INTRAM


	/*.serialvectors 0x0809fff0 (NOLOAD) :*/
	.serialvectors ORIGIN(IOVECTORS) (NOLOAD) :
	{
		PROVIDE ( tSerialVectors = . );
		. = . + 0x10;
	} >IOVECTORS


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

