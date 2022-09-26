    .thumb
	.syntax unified
    .section .text

    .section .so_vectors
    .word __start +1
    b main+1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    b __syscall_handler +1

    .section .so_fn
    .globl __syscall
__syscall:
    push {lr}
    svc 0x37
    pop {pc}
__start:
    b __start+1
    