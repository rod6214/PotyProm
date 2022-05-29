
/*
 * test.s
 *
 * Created: 5/5/2022 2:00:45 AM
 *  Author: Nelson
 */ 
    .section .text
    .globl asm_main
    .type asm_main, @function

    .equ PINA, 0x19
    .equ DDRA, 0x1A
    .equ PORTA, 0x1B
    .equ PINB, 0x16
    .equ DDRB, 0x17
    .equ PORTB, 0x18
    .equ PINC, 0x13
    .equ DDRC, 0x14
    .equ PORTC, 0x15
    .equ ACUM, R1 
    .equ PCL, R2
    .equ PCH, R3
    .equ IDX, R4
    .equ IDY, R5
    .equ STS, R6
    .equ IR, R16
    .equ OP1, R7
    .equ OP2, R8
    .equ OP3, R9
    ; Instruction set
    .equ ADCI, 0x69
    .equ ADCA, 0x6D
    .equ ADCZ, 0x65
    .equ JMPA, 0x4C
    .equ JMP_ABS, 0x7C
    .equ JMP_IND, 0x6C
    .equ LDAI, 0xA9
    .equ LDXI, 0xA2
    .equ STAA, 0x6D
    .equ STXA, 0x8E

asm_main:
    ldi R16, 255
    ldi R17, 0
    out PORTA, R17 ; Clear port a register
    out PORTB, R17 ; Clear port b register
    out PORTC, R17 ; Clear port c register
    out DDRA, R16 ; Set port a as output
    out DDRB, R16 ; Set port b as output
    out DDRC, R17 ; Set port c as input

    out PORTC, R2 ; Load address low from PC
    out PORTA, R3 ; Load address high from PC
    in R16, PORTB ; fetch instruction
    
    
    ; execute instruction
    rcall instruction_exec
    ; increment pc register
    rjmp asm_main

instruction_exec:
    cpi R16, ADCI ; Compare with IR 
    breq ADCI_decoder
case2:
    cpi R16, ADCI ; Compare with IR 
    breq ADCA_decoder
case3:
    cpi R16, ADCI ; Compare with IR 
    breq ADCZ_decoder
case4:
    cpi R16, ADCI ; Compare with IR 
    breq JMPA_decoder
case5:
    cpi R16, ADCI ; Compare with IR 
    breq JMP_ABS_decoder
case6:
    cpi R16, ADCI ; Compare with IR 
    breq JMP_IND_decoder
case7:
    cpi R16, ADCI ; Compare with IR 
    breq LDAI_decoder
case8:
    cpi R16, ADCI ; Compare with IR 
    breq LDXI_decoder
case9:
    cpi R16, ADCI ; Compare with IR 
    breq STAA_decoder
case10:
    cpi R16, ADCI ; Compare with IR 
    breq STXA_decoder
ADCI_decoder:
ADCA_decoder:
ADCZ_decoder:
JMPA_decoder:
JMP_ABS_decoder:
JMP_IND_decoder:
LDAI_decoder:
LDXI_decoder:
STAA_decoder:
STXA_decoder:
finish:
    ret
