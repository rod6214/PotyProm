/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(USART0_TX_vect)
{
	cli();
	sei();
}

ISR(USART0_RX_vect)
{
	cli();
	sei();
}

void config()
{
	PORTB = 0;
	DDRB = (1 << DD0);
}

void loop() 
{
	if (PORTB & (1 << PB0)) 
	{
		PORTB &= ~(1 << PB0);
	}
	else 
	{
		PORTB |= (1 << PB0);
	}
	_delay_ms(200);
}

