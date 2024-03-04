#include <avr/interrupt.h>
#include "arduino_generics.h"

void digitalWrite(uint8_t pin, uint8_t val)
{
	uint8_t bit = pin;
	volatile uint8_t *out;

    out = &PORTB;

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

	SREG = oldSREG;
}

void pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t bit = pin;
	// uint8_t port = DDRB;
	volatile uint8_t *reg, *out;

	reg = &DDRB;
	out = &PORTB;

	if (mode == INPUT) { 
		uint8_t oldSREG = SREG;
                cli();
		*reg &= ~bit;
		*out &= ~bit;
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
                cli();
		*reg &= ~bit;
		*out |= bit;
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
                cli();
		*reg |= bit;
		SREG = oldSREG;
	}
}