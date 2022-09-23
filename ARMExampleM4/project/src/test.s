    .cpu cortex-m4
    .thumb

    .text
    .section .vectors
    .align      2
    .globl      __exception_table

__exception_table:
    .word 0x20001000
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .word Reset_Handler
    .fill 0x3c, 0x01, 0 
Reset_Handler:
    nop
__looping:
    b __looping
