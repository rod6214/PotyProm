    .thumb
	.syntax unified
    .section .text

.equ PID_PIOD, 0x4000
.equ PID_PIOB, 0x1000
.equ PORT0, 1
.equ PORT27, 0x8000000

.equ PIO_PER_D, 0x400E1400
.equ PIO_OER_PIOD, 0x400E1410
.equ PIO_SODR_PIOD, 0x400E1430
.equ PIO_CODR_PIOD, 0x400E1434
.equ PIO_OWER_PD, 0x400E14A0

.equ PIO_PER_B, 0x400E1000
.equ PIO_OER_PIOB, 0x400E1010
.equ PIO_SODR_PIOB, 0x400E1030
.equ PIO_CODR_PIOB, 0x400E1034
.equ PIO_OWER_PB, 0x400E10A0

.equ PMC_PCER0, 0x400E0610
.equ MATRIX_MCFG1, 0x400E0404
.equ MATRIX_SCFG8, 0x400E04A0
.equ MATRIX_PRAS8, 0x400E04c0
.equ PCER0_CFG, PID_PIOD

    .section .so_vectors
    .word __start +1
    b __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    .word __start +1
    b __so_syscall +1
    
    .section .so_start
__start:
    
    ldr r0, =PIO_PER_D          @ Load PIO D controller address
    mov r1, PORT0
    ldr r2, =PIO_OER_PIOD       @ Load ouput control address
    ldr r3, =PIO_OWER_PD        @ Load write enable address for port D
    bl __set_output_port+1      @ Call output port function
    
    ldr r0, =PIO_PER_B          @ Load PIO B controller address
    mov r1, PORT27
    ldr r2, =PIO_OER_PIOB       @ Load ouput control address
    ldr r3, =PIO_OWER_PB        @ Load write enable address for port B
    bl __set_output_port+1      @ Call output port function

    ldr r0, =PCER0_CFG                  @ Load peripherical clock configuration
    bl __activate_peripheral_clock+1    @ Call peripherical clock function

    @ldr r4, =PIO_CODR_PIOD
    @svc 0x27
__end:
    ldr r0, =PIO_SODR_PIOB
    mov r1, PORT27
    bl __set_port
    ldr r0, =PIO_CODR_PIOB
    mov r1, PORT27
    bl __set_port
    bl __end+1
__so_syscall:
    @ ldr r0, [lr, #-2]
    push {lr}
    nop
    pop {pc}
__set_port:
    @ Params:
    @ r0: *XODR, r1: PORT
    push {lr}
    str r1, [r0]
    pop {pc}
__activate_peripheral_clock:
    push {lr}
    @ Params:
    @ r0: PCERx
    ldr r1, =PMC_PCER0          @ Load peripherical clock address for PIO x
    str r0, [r5]                @ Enable peripherical clock
    pop {pc}
__set_output_port:
    @ Params:
    @ r0: *PIOx, r1: PORT, r2: *OE, r3: *OWER
    push {lr}
    str r1, [r0]                @ Enable PIO x controller
    str r1, [r2]                @ Enable output enable
    str r1, [r3]                @ Enable writing output
    pop {pc}
    