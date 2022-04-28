/*
 * AvrRomProgrammer.c
 *
 * Created: 4/25/2022 1:46:44 AM
 * Author : Nelson
 */ 

#include <avr/io.h>

#include <avr/interrupt.h>
#include "io_handle.h"

#define MAX_MEMORY 3072
char write_buffer[MAX_MEMORY];
char read_buffer[MAX_MEMORY];
int read_idx = 0;
int write_idx_z = 0;
int write_idx = 0;
int step = COMMAND_STEP;
int command = 0;
int bytes = 0;
int data_sent = FALSE;

char test_buffer[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

void write_mem(int address, char data);
char read_mem(int address);
char usart_receive();
void usart_send(char data);

#define wait_host() while(!data_sent); data_sent=FALSE

ISR(USART0_TX_vect) 
{
	cli();
	data_sent = TRUE;
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
	int received_data = usart_receive();

	switch(step) 
	{
		case COMMAND_STEP:
		{
			command = received_data;
			step = LOW_BYTE_STEP;
			PORTB = COMMAND_STEP;
		}
		break;
		case LOW_BYTE_STEP:
		{
			bytes = received_data;
			step = HIGH_BYTE_STEP;
			PORTB = LOW_BYTE_STEP;
		}
		break;
		case HIGH_BYTE_STEP:
		{
			bytes |= (received_data << 8);
			step = DATA_STEP;
			PORTB = HIGH_BYTE_STEP;
		}
		break;
		case DATA_STEP:
		{
			PORTB = DATA_STEP;
			if (command == WRITE_MEMORY) 
			{
				// Save to the buffer
				write_buffer[write_idx + write_idx_z] = usart_receive();
				write_idx_z++;
				if (write_idx_z >= bytes || write_idx_z >= MAX_MEMORY)
				{
					write_idx_z = 0;
				}
			}
		}
		break;
	}
	sei();
}

void write_mem(int address, char data) 
{
	// TODO: Verify the time needed by the memory
	//char addrl = LOW_BYTE(address);
	//char addrh = HIGH_BYTE(address);
	//set_address_low(addrl);
	//set_address_high(addrh);
	//set_data(data);
	
}
	
char read_mem(int address)
{
	// TODO: Verify the time needed by the memory
	//char addrl = LOW_BYTE(address);
	//char addrh = HIGH_BYTE(address);
	//set_address_low(addrl);
	//set_address_high(addrh);
	//ctrl_chip_enable(TRUE);
	//ctrl_output_enable(TRUE);
	//_delay_loop_1(2);
	//char data = get_data();
	//_delay_loop_1(2);
	//ctrl_chip_enable(FALSE);
	//_delay_loop_1(1);
	//ctrl_output_enable(FALSE);
	//set_address_low_as_highZ();
	//set_address_high_as_highZ();
	//set_port_data_as_highZ();
	//return data;
	return test_buffer[address];
}

void usart_send(char data)
{
	UDR0 = data;
}
	
char usart_receive()
{
	return UDR0;
}

void config()
{
	// Port E0 & E1 are RX & TX respectively
	PORTE = 0;
	DDRE = (1 << DDE1);
	DDRB = 255;
	PORTB = 0;
	//ctrl_init();
	// Deactivate pull down
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	/************************************************************************/
	/*   UBRR0 = fosc/(8*BAUD) - 1                                          */
	/************************************************************************/
	UBRR0 = 207;
	//UBRR0 = 103;
	sei();
}
	
void loop() 
{
	if ((step == DATA_STEP) && (command == READ_MEMORY)) 
	{
		PORTB = bytes;
		// We must send the first frame later all reading process will follow
		// the remaining frames from TX interrupt.
		// Begin to read the memory
		
		for (int i = 0; i < bytes && i < MAX_MEMORY; i++)
		{
			// Read memory
			char data = read_mem(read_idx + i);
			read_buffer[read_idx + i] = data;
		}
		
		int current_index = read_idx;
		
		for (int i = 0; i < bytes && i < MAX_MEMORY; i++, read_idx++)
		{
			// Send data to the host
			char data = read_buffer[current_index + i];
			//char data = 5;
			usart_send(data);
			wait_host();
		}
		
		if (read_idx >= bytes)
		{
			// Finish the process
			read_idx=0;
			step=NULL;
			command=NULL;
		}
	}
	//usart_send(0x45);
	switch(command)
	{
		//case READ_MEMORY:
		//{
			//// We must send the first frame later all reading process will follow
			//// the remaining frames from TX interrupt.
			//// Begin to read the memory
			//
			//for (int i = 0; i < bytes && i < MAX_MEMORY; i++)
			//{
				//// Read memory
				//char data = read_mem(read_idx + i);
				//read_buffer[read_idx + i] = data;
			//}
			//
			//int current_index = read_idx;
			//
			//for (int i = 0; i < bytes && i < MAX_MEMORY; i++, read_idx++)
			//{
				//// Send data to the host
				//char data = read_buffer[current_index + i];
				//usart_send(data);
				////wait_host();
			//}
			//
			//if (read_idx >= bytes)
			//{
				//// Finish the process
				//read_idx=0;
				//step=COMMAND_STEP;
				//break;
			//}
		//}
		//break;
		//case WRITE_MEMORY:
		//{
			//for (int i = 0; i < bytes && i < MAX_MEMORY; i++, write_idx++)
			//{
				//// Write memory
				//char data = write_buffer[write_idx + i];
				//write_mem(write_idx + i, data);
			//}
			//
			//if (write_idx >= bytes)
			//{
				//// Finish the process
				//write_idx=0;
				//step=COMMAND_STEP;
				//break;
			//}
			//
			//// Send a ready command to the host or ACK
			//usart_send(ACK);
			//wait_host();
		//}
		//break;
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

