	.thumb
	.syntax unified
// PMC Clock generator Main Oscillator Register
.equ CKGR_MOR, 0x400E0620
.equ OSCILLATOR_CFG, 0x1373801
.equ PMC_SR, 0x400E0668
.equ CKGR_PLLAR, 0x400E0628
.equ PLL_CFG, 0x200E3802
.equ PMC_MCKR, 0x400E0630
.equ VTOR_SYSTEM, 0xE000ED08

    @ .section .text
    .section .vectors
    .word _estack
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word _start +1
    .word __syscall +1
    
_start:
    bl __clock+1            @ Call Clock configuration subroutine
    svc 0                   @ Call syscall for configuring new vector table
    ldr r3, =#0x200000f5    @ Load entry point address
    bx r3                   @ Goto the entry point
__looping:
    b __looping
__syscall:
    push {lr}
    ldr r3, =VTOR_SYSTEM
    ldr r2, =#0x20000000
    str r2, [r3]
    pop {pc}
__clock:
    push {lr}
    ldr r0, =OSCILLATOR_CFG     @ Load oscillator configuration
    ldr r1, =CKGR_MOR           @ Load the main oscillator register address
    str r0, [r1]                @ Store configuration into the oscillator register
__wait_clock:
    ldr r1, =PMC_SR             @ Load power management status register address
    and r0, r1, #1              @ Test bit 0 (MOSCXTS)
    beq __wait_clock            @ If clock is not stabilized continue looping
    ldr r0, =PLL_CFG            @ Load pll configuration register 
    ldr r1, =CKGR_PLLAR         @ Load pll register address
    str r0, [r1]                @ Store configuration into pll register
__wait_pll:
    ldr r1, =PMC_SR             @ Load power managenemnt status register address
    and r0, r1, #2              @ Test bit 1
    beq __wait_pll              @ If lock bit is not 1, continue looping
    mov r0, #2                  @ Load configuration to select PLLA as source oscillator
    ldr r1, =PMC_MCKR           @ Load master clock register address
    str r0, [r1]                @ Store configuration into the master clock register address
__wait_msck:
    ldr r1, =PMC_SR
    and r0, r1, #8
    beq __wait_msck
    pop {pc}                    @ End main clock configuration
