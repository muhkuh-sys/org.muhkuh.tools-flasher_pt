	.extern netx_consoleapp_main
	.global start

	.text

#include "asic_types.h"

#if ASIC_TYP==ASIC_TYP_NETIOL
/* The netIOL has a RISCV CPU. 
 *
 * The init code expects the address of the program parameters in reg a0 
 * and stores the return value in this address.  
 *
 * Note: This init code does not return, but ends in an ebreak.
 * It also does not save and restore any registers (stack pointer etc.).
 * Thus, it's only suitable for use with JTAG. 
*/

    .func start, start
    .type start, STT_FUNC
start:
	/* Set own stack position. */
	la      x2, stack_top
	
	/* Push a0 (parameter address). */
	addi    sp, sp, -4
	sw      a0, 0(sp)
	
	/* Clear the .bss section (zero init). */
	la      x26, __bss_start__
	la      x27, __bss_end__
clear_bss:
	sw      x0, 0(x26)
	addi    x26, x26, 4
	ble     x26, x27, clear_bss
	
	/* Call the program. */
	jal     ra, netx_consoleapp_main

	/* The return value (status) is in a0. */
	/* Pop the parameter address and store the return value. */
	lw      a1, 0(sp)
	sw      a0, 0(a1)
	addi    sp, sp, 4
	

	/* for now, just break */
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	ebreak 
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	/* loop endlessly */
debug_stop:
	jal     x0, debug_stop

.end


#else
/*-----------------------------------*/

/* The Cortex-M4 in the netX90 is a THUMB-only CPU.
 * All others start in 32 bit mode.
 */
#if ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
	.syntax unified
	.thumb
#else
	.arm
#endif


    .func start, start
    .type start, STT_FUNC
start:
	push    {r0, r1, r2, lr}

	/* Save the stack position of the ROM. */
	mov     r1, sp

	/* Set own stack position. */
	ldr     r2, =stack_top
	mov     sp, r2

	/* Save the ROM stack position and some additional registers. */
	push    {r0, r1, r3}

	/* Clear the .bss section. */
	mov     r1, #0
	ldr     r2, =__bss_start__
	ldr     r3, =__bss_end__
clear_bss:
	str     r1, [r2], #4
	cmp     r2, r3
	bmi     clear_bss

	/* Jump to the main routine. */
	blx     netx_consoleapp_main

	/* Move the result to r2. */
	mov     r2, r0

	/* Restore the ROM stack position. */
	pop     {r0, r1, r3}
	mov     sp, r1

	/* Store the result in the structure. */
	str     r2, [r0, #0]

	/* Restore the rest of the registers. */
	pop     {r0, r1, r2, lr}
	bx      lr

  .endfunc

/*-----------------------------------*/

  .end
#endif
