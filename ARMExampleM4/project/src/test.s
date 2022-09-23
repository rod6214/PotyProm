	.thumb
	.syntax unified

    .section .text
    .word __StackTop
    .word _start +1
    
_start:
    nop
__looping:
    nop
    nop
    b __looping
