
/*
 * test.s
 *
 * Created: 9/5/2022 12:40:35 AM
 *  Author: Nelson
 */ 
 .text
 .global system_call
 system_call:
	push {r3, lr}
	nop
	pop {r3, pc}
