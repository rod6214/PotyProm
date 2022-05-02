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
long read_idx = 0;
long write_idx_z = 0;
long write_idx = 0;
int step = COMMAND_STEP;
int command = 0;
long bytes = 0;
int data_sent = FALSE;
int isBusy = FALSE;

 //char test_buffer[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

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

	if (!isBusy) 
	{
		switch(step) 
		{
			case COMMAND_STEP:
			{
				command = received_data;
				step = LOW_BYTE_STEP;
			}
			break;
			case LOW_BYTE_STEP:
			{
				bytes = received_data;
				step = HIGH_BYTE_STEP;
			}
			break;
			case HIGH_BYTE_STEP:
			{
				bytes |= (received_data << 8);
				//bytes = 28671;
				step = DATA_STEP;
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
		}
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
	char addrl = LOW_BYTE(address);
	char addrh = HIGH_BYTE(address);
	set_address_low(addrl);
	set_address_high(addrh);
	ctrl_chip_enable(TRUE);
	_delay_loop_1(1);
	ctrl_output_enable(TRUE);
	_delay_loop_1(20);
	char data = get_data();
	_delay_loop_1(20);
	ctrl_chip_enable(FALSE);
	_delay_loop_1(1);
	ctrl_output_enable(FALSE);
	set_address_low_as_highZ();
	set_address_high_as_highZ();
	set_port_data_as_highZ();
	return data;
	 //return test_buffer[address];
	 //return 0;
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
	DDRA = 255;
	PORTA = 255;
	DDRC = 255;
	PORTC = 255;
	DDRL = 255;
	PORTL = 255;
	DDRD = 255;
	PORTD = 255;
	DDRG = 255;
	PORTG = 255;
	// Port E0 & E1 are RX & TX respectively
	DDRE = 0;
	PORTE = 0;
	DDRE = DDRE | (1 << DDE1);
	// DDRB = 255;
	DDRB = (1 << DDB7);
	 PORTB = 0;
	ctrl_init();
	// Deactivate pull down
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	/************************************************************************/
	/*   UBRR0 = fosc/(8*BAUD) - 1                                          */
	/************************************************************************/
	UBRR0 = 207;
	//UBRR0 = 103;
	_delay_loop_1(1);
	sei();
}


	
void loop() 
{
	
	int data = (PORTA & (1));
	_delay_loop_1(1);
	if (data)
	{
		//PORTB = PORTB | (1 << PORTB7);
		PORTB = 1;
	}
	else 
	{
		PORTB = 0;
		//PORTB = PORTB & (~(1 << PORTB7));
	}
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
			// We must send the first frame later all reading process will follow
			// the remaining frames from TX interrupt.
			// Begin to read the memory
			//for (int i = 0; i < bytes && i < MAX_MEMORY; i++)
			//{
				//// Read memory
				//read_buffer[i] = read_mem(read_idx + i);
			//}
			
			//for (long i = 0; read_idx < bytes && i < MAX_MEMORY; i++, read_idx++)
			//{
				//// Send data to the host
				////char data = read_buffer[i];
				//char data = read_mem(read_idx);
				//_delay_loop_1(1);
				//usart_send(data);
				//wait_host();
				////if (read_idx == 32766)
				////{
					////PORTB = data;
				////}
				//
			//}
//
			//if (read_idx >= bytes)
			//{
				//// Finish the process
				//read_idx=0;
				//step=COMMAND_STEP;
				//command=NULL;
			//}
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
	//config();

    //while (1) 
    //{
		//loop();
    //}
}

