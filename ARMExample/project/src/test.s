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
    .word SysCall_Handler
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
    bl main
_looping:
    bx _looping
SysCall_Handler:
    push {r3, lr}
    bl syscall_c
    pop {r3, pc}
syscall_32:
    svc 0x32
    bx lr