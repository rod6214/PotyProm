/*
 * io_uart.c
 *
 * Created: 5/7/2022 7:29:03 PM
 *  Author: Nelson
 */ 
#define F_CPU 4000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "io_uart.h"

// #define UCSRB  _SFR_IO8(0x0A)
// #define UBRRL  _SFR_IO8(0x09)
// #define UCSZ2 2

void usart_start()
{
	/************************************************************************/
	/*   UBRR0 = fosc/(16*BAUD) - 1                                         */
	/************************************************************************/
	// UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE) | (1 << UCSZ2);
	UCR = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE) | (1 << CHR9);
	_delay_loop_1(1);
	// UBRRL = 25;
	// UBRR = 25;
	UBRR = 12;
	_delay_loop_1(1);
}

void usart_send(char data)
{
	// UCSRB = UCSRB | (1 << TXB8);
	UCR = UCR | (1 << TXB8);
	UDR = data;
}

char usart_receive()
{
	return UDR;
}
