/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "standard.h"
#include "io_uart.h"

#define MAX_MEMORY 1024
char _buffer[MAX_MEMORY + 5];
int _idx = 0;

int isBusy = FALSE;


ISR(USART0_TX_vect)
{
	cli();
	// data_sent = TRUE;
	sei();
}

ISR(USART0_RX_vect)
{
	cli();
	int data = usart_receive();
	PORTA = data;
	// _buffer[_idx] = usart_receive();
	// _idx++;
	sei();
}

void config()
{
	PORTA = 0;
	DDRA = 255;
}

void loop() 
{
}

