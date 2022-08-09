/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "io_uart.h"
#include "ext_eeprom_mem.h"

#define MAX_MEMORY 64
#define MODE_ONLY_PROGRAMMER 78


ISR(PCINT0_vect)
{
	cli();
	char input = (PINB & 6) >> 1;
	char output = PORTD;

	if (input == 0) {
		output &= ~(7);
		output |= 6;
	}
	else if (input == 1) {
		output &= ~(7);
		output |= 5;
	}
	else if (input == 2) {
		output &= ~(7);
		output |= 3;
	}
	
	PORTD = output;
	sei();
}

void config()
{
	SPCR = (1 << MSTR);
	TCCR1A = 0;
	// TCCR1B = 0;
	// TCCR1C = 0;
	// TCCR0A = 0;
	// TCCR0B = 0;
	DDRB = 0;
	DDRC = 0;
	DDRD = 255;
	PORTD = 7;
	PORTB = 0;
	_delay_loop_1(1);
	
	
	PCMSK0 = (1 << PCINT0);
	sei();
	PCICR = (1 << PCIE0);
}

void loop() 
{
}

int main(void)
{
	config();
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

