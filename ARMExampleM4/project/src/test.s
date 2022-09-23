	.thumb
	.syntax unified

    .section .text
    .word __StackTop
    .word _start +1
    
_start:
    ldr r3, =#0x20000001
    blx r3
    nop
__looping:
    nop
    nop
    b __looping
