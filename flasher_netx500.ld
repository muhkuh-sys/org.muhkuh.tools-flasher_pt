
MEMORY
{
        INTRAM(rwx)		: ORIGIN = 0x00000004, LENGTH = 0x0001fffc
        INTKERNELROM(rwx)	: ORIGIN = 0x00202000, LENGTH = 0x6000
	DATATCM(rw)		: ORIGIN = 0x10000000, LENGTH = 0x00002000
        SDRAM(rwx)		: ORIGIN = 0x80000000, LENGTH = 0x00020000
}


/* Section Definitions */
SECTIONS
{
        /* bootloader reserved area */
        .bootloader 0x00000000 :
        {
                . = . + 0x8000;
        } >INTRAM

	.startvector :
	{
                *(.init_code)
		*(.version_info)
	}

        .sec0 :
        {
                *(.text)

                *(.glue_7t)
                *(.glue_7)

                /* .rodata section which is used for read-only data (constants) */
                *(.rodata*)

                /* now let all the rest,typically non static variables, follow */
                *(COMMON)
        } >INTRAM


        /* .data section which is used for initialized data */
        . = ALIGN(4);
        _etext = . ;
        PROVIDE (etext = .);
        .data : AT (_etext)
        {
                _data = . ;
                *(.data)
        } >INTRAM

        .sec1 :
        {
                /* .bss section which is used for uninitialized data */
                . = ALIGN(4);
                __bss_start = . ;
                __bss_start__ = . ;

                *(.bss)

                . = ALIGN(4);
                __bss_end__ = . ;
                __bss_end__ = . ;
        } >INTRAM

        .testparameter 0x00018000 :
        {
                . = . + 0x0100;
        } >INTRAM

        .stack 0x00018100 :
        {
                . = . + 0x7f00;
                PROVIDE (top_of_ownstack = .);
        } >INTRAM

	.serialvectors 0x10001ff0 (NOLOAD) :
	{
		PROVIDE ( serial_vectors = . );
		. = . + 0x10;
	} >DATATCM


        . = ALIGN(4);
        _edata = . ;
        PROVIDE (edata = .);

        _end = .;
        PROVIDE (end = .);

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

