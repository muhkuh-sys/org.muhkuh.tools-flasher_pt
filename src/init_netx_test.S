
	.section .text
	.arm

	.extern test_main

	.global netx_consoleapp_init
	.global NetxConsoleParameter_Init
	.global start

@--------------------------------------

  .func start

start:
	stmfd   sp!, {r0, r1, r2, lr}

	@ save pointer to netx parameter block
	ldr     r1, =NetxConsoleParameter_Init
	str     r0, [r1]

	@ save debug console stack position
	mov     r0, sp
	ldr     r1, =blstack_save
	str     r0, [r1]

	@ set own stack position
	ldr     r0, =stack_top
	mov     sp, r0

	@ clear .bss section (zero init)
	mov     r0, #0
	ldr     r1, =__bss_start__
	ldr     r2, =__bss_end__
clear_bss:
	cmp     r1, r2
	strlo   r0, [r1], #4
	blo     clear_bss

	bl      call_test_main

	@ restore debug console stack
	ldr     r1, =blstack_save
	ldr     r0, [r1]
	mov     sp, r0

	ldmfd   sp!, {r0, r1, r2, lr}
	bx      lr

call_test_main:
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

