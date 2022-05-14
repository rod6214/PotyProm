
/*
 * interrupts.c
 *
 * Created: 5/14/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "standard.h"
#include "io_uart.h"
#include "serial.h"

#define MAX_MEMORY 1024
#define MAX_COMMAND_BUFFER 6

char _buffer[MAX_MEMORY];
char _command_buffer[MAX_COMMAND_BUFFER];
int _idx = 0;
int data_sent = FALSE;
int isBusy = FALSE;
#define wait_host() while(!data_sent); data_sent=FALSE

ISR(USART0_TX_vect)
{
	cli();
	data_sent = TRUE;
	sei();
}

ISR(USART0_RX_vect)
{
	cli();
	int data = usart_receive();
	serial_set_command(data);
	sei();
}
