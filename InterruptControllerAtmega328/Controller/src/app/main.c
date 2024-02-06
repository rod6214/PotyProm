/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "configs.h"
#include "intports.h"
#include "compiler.h"


unsigned char intel_isr[VECTOR_LENGTH];

// This is INTA_2
// ISR(INT0_vect) {
// 	cli();
// 	// READY_off();
// 	// VOE_off();
// 	// READY_on();
// 	// while(((PIND) & (1 << INTA_2_PIN)));
// 	// VOE_on();
// 	sei();
// }

// This is EX_INT
ISR(INT1_vect) {
	cli();
	LATCH_on();
	if (0x01 & PINB) {
		set_vector(intel_isr[0]);
	}
	else if (0x02 & PINB) {
		set_vector(intel_isr[1]);
	}
	else if (0x04 & PINB) {
		set_vector(intel_isr[2]);
	}
	else if (0x08 & PINB) {
		set_vector(intel_isr[3]);
	}
	LATCH_off();
	sei();
	INT_on();
	INT_off();
}

void config() {
	// Configuring INT0 as rising edge detection
	EICRA = (1 << ISC01) | (1 << ISC00) | (1 << ISC10) | (1 << ISC11);
	// EICRA |= (1 << ISC10) | (1 << ISC11);
	// EICRA |= (1 << ISC10) | (1 << ISC11);
	// Enabling INT0 interrupt
	// EIMSK |= (1 << INT0) | (1 << INT1);
	EIMSK |= (1 << INT1);
	vector_controller_init();

	memcpy_P(intel_isr, intel_vectors, VECTOR_LENGTH);

	READY_on();
	// Activate all interrupts
	sei();
}

int main(void)
{
	config();

    // /* Replace with your application code */
    while (1) 
    {
		// set_vector(0);
    }
}
