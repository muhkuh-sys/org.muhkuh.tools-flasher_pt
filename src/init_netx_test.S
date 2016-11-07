	.extern netx_consoleapp_main
	.global start

	.text

#include "asic_types.h"

@--------------------------------------

@ The Cortex-M4 in the netX90 is a THUMB-only CPU.
@ All others start in 32 bit mode.
#if ASIC_TYP==ASIC_TYP_NETX90_MPW
	.syntax unified
	.thumb
#else
	.arm
#endif


    .func start, start
    .type start, STT_FUNC
start:
	push    {r0, r1, r2, lr}

	@ Save the stack position of the ROM.
	mov     r1, sp

	@ Set own stack position
	ldr     r2, =stack_top
	mov     sp, r2

	@ Save the ROM stack position and some additional registers.
	push    {r0, r1, r3}

	@ Clear the .bss section.
	mov     r1, #0
	ldr     r2, =__bss_start__
	ldr     r3, =__bss_end__
clear_bss:
	str     r1, [r2], #4
	cmp     r2, r3
	bmi     clear_bss

	@ Jump to the main routine.
	blx     netx_consoleapp_main

	@ Move the result to r2.
	mov     r2, r0

	@ Restore the ROM stack position.
	pop     {r0, r1, r3}
	mov     sp, r1

	@ Store the result in the structure.
	str     r2, [r0, #0]

	@ Restore the rest of the registers.
	pop     {r0, r1, r2, lr}
	bx      lr

  .endfunc

@--------------------------------------

  .end

