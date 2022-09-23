    .thumb
	.syntax unified
    .section .text
__start:
    nop
    nop
    nop
    @ ldr r3, =__start+1
    @ bx r3
    bl __start+1
    