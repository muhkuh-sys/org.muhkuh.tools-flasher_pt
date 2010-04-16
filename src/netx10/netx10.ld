/*---------------------------------------------------------------------------
  Author : Christoph Thelen

           Hilscher GmbH, Copyright (c) 2010, All Rights Reserved

           Redistribution or unauthorized use without expressed written 
           agreement from the Hilscher GmbH is forbidden
---------------------------------------------------------------------------*/

ENTRY(start)

MEMORY
{
	INTRAM2_ITCM(rwx)	: ORIGIN = 0x00020000, LENGTH = 0x00010000
	INTRAM0_DTCM(rwx)	: ORIGIN = 0x04000000, LENGTH = 0x00010000
	INTRAM3_DTCM(rwx)	: ORIGIN = 0x04030000, LENGTH = 0x00010000
}


/* Section Definitions */
SECTIONS
{
	.code ORIGIN(INTRAM2_ITCM) :
	{
		*(.init_code)
		*(.text)
		*(.glue*)
		*(.vfp11_veneer)
		*(.v4_bx)
	} >INTRAM2_ITCM


	.data ORIGIN(INTRAM3_DTCM) : AT(ORIGIN(INTRAM2_ITCM)+SIZEOF(.code))
	{
		__data_start__ = . ;

		/* ro data */
		*(.rodata*)

		/* rw data */
		*(.data)

		__data_end__ = . ;
	} >INTRAM3_DTCM
	__data_loadaddr__ = LOADADDR(.data) ;


	.serial_vectors ORIGIN(INTRAM0_DTCM)+LENGTH(INTRAM0_DTCM)-0x10 :
	{
		tSerialVectors = . ;
		. = . + 0x10;
	} >INTRAM0_DTCM

	.bss :
	{
		/* zero-initialized data */

		__bss_start__ = . ;

		*(.bss)
		*(COMMON)

		__bss_end__ = . ;
	} >INTRAM3_DTCM


	/* set the top of the stack to the end of INTRAM1 */
	stack_top = ORIGIN(INTRAM3_DTCM) + LENGTH(INTRAM3_DTCM) ;


	/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	/* DWARF debug sections.
		Symbols in the DWARF debugging sections are relative to the beginning
		of the section so we begin them at 0.  */
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

