/*
 * AvrRomProgrammer.c
 *
 * Created: 4/25/2022 1:46:44 AM
 * Author : Nelson
 */ 
#define F_CPU 12E6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_handle.h"

#define MAX_MEMORY 3072
char r_buffer[MAX_MEMORY];
char x_buffer[MAX_MEMORY];
int r_idx = 0;
int x_idx = 0;
int step = 0;
int commad = 0;

void write_mem();
void read_mem();

ISR(USART0_TX_vect) 
{
	cli();
	sei();
}
	
ISR(USART0_RX_vect) 
{
	/************************************************************************************************/
	/* Max length per FRAME is 3k*8                                                                 */
	/*  ___0___  _____1____  _____2____  _________3_________              ________N_________        */
	/* /COMMAND\/  BYTES L \/  BYTES H \/		 3k         \............/		 3k         \       */
	/* \ 8bit  /\   8bit   /\   8bit   /\      FRAME        /            \       FRAME      /       */
	/************************************************************************************************/
	cli();
	switch(step) 
	{
		case COMMAND_STEP:
		{}
		break;
		case LOW_BYTE_STEP:
		{}
		break;
		case HIGH_BYTE_STEP:
		{}
		break;
		case DATA_STEP:
		{
			switch(commad) 
			{
				case READ_MEMORY:
				{
					// We must send the first frame later all reading process will follow 
					// the remaining frames from TX interrupt.
				}
				break;
				case WRITE_MEMORY:
				{
					// We must attend all writing process from here.
				}
				break;
			}
		}
		break;
	}
	// PORTB = UDR0;
	//r_buffer[r_idx] = UDR0;
	//if (r_idx >= MAX_MEMORY) 
	//{
		//r_idx = 0;
	//}
	//else 
	//{
		//r_idx++;
	//}
	sei();
}

void write_mem() 
{
	while(r_idx != 0) 
	{
		char addrl = LOW_BYTE(r_idx);
		char addrh = HIGH_BYTE(r_idx);
		set_address_low(addrl);
		set_address_high(addrh);
		set_data(r_buffer[r_idx]);
		r_idx--;
	}
}
	
void read_mem()
{
	while(x_idx < MAX_MEMORY)
	{
		char addrl = LOW_BYTE(x_idx);
		char addrh = HIGH_BYTE(x_idx);
		set_address_low(addrl);
		set_address_high(addrh);
		x_buffer[x_idx] = get_data();
		x_idx++;
	}
}

void config()
{
	DDRE = 1 << DDE1;
	PORTE = 0;
	
	DDRB = 255;
	PORTB = 0;
	// Deactivate pull down
	//MCU = 0;
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	/************************************************************************/
	/*   UBRR0 = fosc/(8*BAUD) - 1                                          */
	/************************************************************************/
	UBRR0 = 207;
	sei();
}
	
void loop() 
{
	//if (PORTE == 1 << PE1)
	//{
		//PORTE = 0;
	//}
	//else
	//{
		//PORTE = 1 << PE1;
	//}
	//
	//if (PORTB)
	//{
		//PORTB = 0;
	//}
	//else
	//{
		//PORTB = 1 << PB7;
	//}
	_delay_ms(500);
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

