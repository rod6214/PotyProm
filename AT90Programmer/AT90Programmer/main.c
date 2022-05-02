/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
# define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"

#define MAX_MEMORY 128
char write_buffer[MAX_MEMORY];
char read_buffer[MAX_MEMORY];
int read_idx = 0;
int write_idx_z = 0;
int write_idx = 0;
int step = NULL;
int command = 0;
int bytes = 0;
int data_sent = FALSE;
int isBusy = 0;

void write_mem(int address, char data);
char read_mem(int address);
char usart_receive();
void usart_send(char data);
void usart_start();
void usart_stop();

#define wait_host() while(!data_sent); data_sent=FALSE

ISR(USART_TX_vect)
{
	cli();
	data_sent = TRUE;
	sei();
}

ISR(USART_RX_vect)
{
	/************************************************************************************************/
	/* Max length per FRAME is 3k*8                                                                 */
	/*  ___0___  _____1____  _____2____  _________3_________              ________N_________        */
	/* /COMMAND\/  BYTES L \/  BYTES H \/		 3k         \............/		 3k         \       */
	/* \ 8bit  /\   8bit   /\   8bit   /\      FRAME        /            \       FRAME      /       */
	/************************************************************************************************/
	
	cli();
	char received_data = usart_receive();
	//PORTC = usart_receive();
	
	//if (received_data != 0) {
		//PORTC = (char)received_data;
	//}
	//PORTC = received_data;
	//received_data == READ_MEMORY;
	//PORTC++;
	if (((received_data == READ_MEMORY) || (received_data == WRITE_MEMORY))) 
	{
		step = COMMAND_STEP;
	}

	switch(step)
	{
		case COMMAND_STEP:
		{
			command = received_data;
			step = LOW_BYTE_STEP;
			//PORTC = received_data;
		}
		break;
		case LOW_BYTE_STEP:
		{
			bytes = received_data;
			step = HIGH_BYTE_STEP;
			//PORTC = received_data;
			
		}
		break;
		case HIGH_BYTE_STEP:
		{
			bytes |= (received_data << 8);
			step = DATA_STEP;
			//PORTC = received_data;
		}
		break;
		case DATA_STEP:
		{
			// if (command == WRITE_MEMORY)
			// {
			// 	// Save to the buffer
			// 	write_buffer[write_idx + write_idx_z] = (char)received_data;
			// 	write_idx_z++;
			// 	if (write_idx_z >= bytes || write_idx_z >= MAX_MEMORY)
			// 	{
			// 		write_idx_z = 0;
			// 		isBusy = TRUE;
			// 	}
			// }
		}
		break;
		default:
		{
			step = NULL;
		}
		break;
	}
	sei();
}

char read_mem(int address) 
{
	set_data_high_z();
	char addressl = (char)(0xff & address);
	char addressh = (char)(((0xff00) & address) >> 8);
	set_address_low(addressl);
	set_address_high(addressh);
	set_chip_enable(TRUE);
	set_output_enable(TRUE);
	char data = get_data();
	_delay_loop_1(10);
	set_chip_enable(FALSE);
	set_output_enable(FALSE);
	set_address_low_Z();
	set_address_high_Z();
	return data;
}

void usart_start() 
{
	/************************************************************************/
	/*   UBRR0 = fosc/(16*BAUD) - 1                                         */
	/************************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE) | (1 << UCSZ2);
	//UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE);
	_delay_loop_1(1);
	UBRRL = 25;
	_delay_loop_1(1);
}

void usart_stop()
{}

void usart_send(char data)
{
	UCSRB = UCSRB | (1 << TXB8);
	UDR = data;
}

char usart_receive()
{
	return UDR;
}

void config()
{
	usart_start();
	//DDRC = 255;
	//_delay_loop_1(1);
	//PORTC = 0;
	init_ctrl_mem();
	_delay_loop_1(100);
	step = NULL;
	isBusy = 0;
	read_idx = 0;
	sei();
}

void loop() 
{
	// Only for testing//////
	//if (bytes == 0)
	//bytes = 32767;
	//step = DATA_STEP;
	//command = READ_MEMORY;
	////////////////////////
	if (step == DATA_STEP)
	{
		if (command == READ_MEMORY)
		{			
			for (long i = 0; read_idx < bytes && i < MAX_MEMORY; i++, read_idx++)
			{
				// Send data to the host
				char data = read_mem(read_idx);
				_delay_loop_1(1);
				usart_send(data);
				wait_host();
			}
			
			if (read_idx >= bytes)
			{
				// Finish the process
				read_idx=0;
				step=COMMAND_STEP;
				command=NULL;
			}
		}
		else if (command == WRITE_MEMORY)
		{
			// for (int i = 0; i < bytes && i < MAX_MEMORY; i++, write_idx++)
			// {
			// 	// Write memory
			// 	char data = write_buffer[write_idx + i];
			// 	write_mem(write_idx + i, data);
			// }
			
			// if (write_idx >= bytes)
			// {
			// 	// Finish the process
			// 	write_idx=0;
			// 	step=COMMAND_STEP;
			// 	break;
			// }
			
			// // Send a ready command to the host or ACK
			// usart_send(ACK);
			// wait_host();
		}
	}
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

