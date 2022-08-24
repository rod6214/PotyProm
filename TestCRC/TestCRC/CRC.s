
/*
 * CRC.s
 *
 * Created: 8/22/2022 11:12:03 PM
 *  Author: Nelson
 */ 
	
	.section .text
    .globl CRCFn
    .type CRCFn, @function
CRCFn:
	push r16
	push r17
	ldi r16, 40 ; load counter with 7
	ldi r17, 137 ; load coeficients of x^7 + x^3 + 1
	mov r8, r17 ; save in r8
	ldi r17, 128 ; load 0x80 to determine if we can shift the number into the operand register r7
	mov r9, r17 ; save in r9
	rcall _load_registers 
_crc_rotate:
	mov r17, r4
	and r17, r9
	brne _crc_xor_op ; if zero shift registers
	rcall _cr_rol 
	rjmp _crc_continue
_crc_xor_op: ; ifnot zero make xor operation
	eor r4, r8
	rjmp _crc_rotate
_crc_continue:
	dec r16
	brne _crc_rotate; skip if zero
	lsr r4
	mov r24, r4
	pop r17
	pop r16
	ret	
_load_registers:
	movw r26, r24 ; move pointer to X index
_cr_ld:
	ld r4, X+
	ld r3, X+
	ld r2, X+
	ld r1, X+
	ld r0, X+
	ret
_cr_rol:
	clc
	lsl r0
	rol r1
	rol r2
	rol r3
	rol r4
	nop
	ret



