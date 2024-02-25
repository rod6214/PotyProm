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

unsigned char intel_isr[3];

// This is INTA_2
ISR(INT0_vect) {
	cli();
	sei();
}

// This is EX_INT
ISR(INT1_vect) {
	cli();
	uint8_t value = 0x0f & PINB;
	set_vector(value);
	sei();
}

void config() {
	// Configuring INT0 as rising edge detection
	EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC10) | (1 << ISC11);
	// Enabling INT0 interrupt
	EIMSK |= (1 << INT0) | (1 << INT1);
	vector_controller_init();

	memcpy_P(intel_isr, intel_vectors, 3);

	// Activate all interrupts
	sei();
}

int main(void)
{
	config();

    // /* Replace with your application code */
    while (1) 
    {
		set_vector(0);
    }
}
