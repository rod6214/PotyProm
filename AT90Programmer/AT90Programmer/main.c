/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
# define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"

#define MAX_MEMORY 64
char write_buffer[MAX_MEMORY];
char read_buffer[MAX_MEMORY];
int read_idx = 0;
int write_idx_z = 0;
int write_idx = 0;
//int bytes = 0;
int offset = 0;
int step = NULL;
int command = 0;
int data_sent = FALSE;
int isBusy = FALSE;
char received_data;
int serial_attended = FALSE;
int execute_proc = FALSE;

void write_mem(int address, char data);
char read_mem(int address);
char usart_receive();
void usart_send(char data);
void usart_start();
void usart_stop();

#define wait_host() while(!data_sent); data_sent=FALSE
#define USART_TX_vect			_VECTOR(13)
#define USART_RX_vect			_VECTOR(11)
#define UCSRB   _SFR_IO8(0x0A)
#define UBRRL   _SFR_IO8(0x09)
#define    UCSZ2        2

ISR(USART_TX_vect)
{
	cli();
	data_sent = TRUE;
	sei();
}

ISR(USART_RX_vect)
{
	cli();
	serial_attended = FALSE;
	write_buffer[write_idx] = usart_receive();
	write_idx++;
	sei();
}

char read_mem(int address) 
{
	char addressl = LOW_BYTE(address);
	char addressh = HIGH_BYTE(address);
	set_address_low(addressl);
	set_address_high(addressh);
	_delay_us(5);
	set_chip_enable(TRUE);
	_delay_us(5);
	set_output_enable(TRUE);
	_delay_us(5);
	char data = 0;
	int i = 0;
	while(i < 255) 
	{
		data = get_data();
		i++;
		_delay_us(1);
	}
	set_chip_enable(FALSE);
	_delay_us(5);
	set_output_enable(FALSE);
	_delay_us(5);
	return data;
}

void write_mem(int address, char data) 
{
	char addressl = LOW_BYTE(address);
	char addressh = HIGH_BYTE(address);
	set_address_low(addressl);
	set_address_high(addressh);
	_delay_ms(5);
	set_write_enable(TRUE);
	_delay_ms(1);
	set_data(data);
	_delay_ms(10);
	set_write_enable(FALSE);
	_delay_ms(5);
}


void prepare_for_read() 
{
	_delay_loop_1(20);
	set_address_high_as_output();
	set_address_low_as_output();
	_delay_loop_1(20);
	set_data_as_input();
	_delay_loop_1(20);
}

void prepare_for_write() 
{
	_delay_loop_1(20);
	set_address_high_as_output();
	set_address_low_as_output();
	_delay_loop_1(20);
	set_data_as_output();
	_delay_ms(50);
	set_chip_enable(TRUE);
	_delay_ms(50);
	set_output_enable(FALSE);
	_delay_ms(50);
}

void usart_start() 
{
	/************************************************************************/
	/*   UBRR0 = fosc/(16*BAUD) - 1                                         */
	/************************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE) | (1 << UCSZ2);
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
	init_ctrl_mem();
	_delay_loop_1(100);
	step = NULL;
	//isBusy = 0;
	write_idx_z = 0;
	write_idx = 0;
	read_idx = 0;
	execute_proc = FALSE;
	sei();
}

//char i_test = 0;
//int started = FALSE;

void loop() 
{
	//DDRC = 255;
	//PORTC = 255;
	//set_data_high_z();
	//if (!started)
	//{
		////prepare_for_read();
		//prepare_for_write();
		//started = TRUE;
	//}
	//else 
	//{
		//set_data(i_test);
		//i_test++;
		//_delay_ms(100);
	//}
	
	//_delay_ms(2);
	//char addressl = LOW_BYTE(i);
	//char addressh = HIGH_BYTE(i);
	//set_address_low(255);
	//set_address_high(255);
	//set_data(255);
	//_delay_ms(2);
	//set_chip_enable(TRUE);
	//_delay_ms(2);
	//set_output_enable(TRUE);
	//_delay_ms(5);
	//get_data();
	//set_chip_enable(FALSE);
	//_delay_ms(2);
	//set_output_enable(FALSE);
	//
	//if (i > 255)
		//i = 0;
	//else
		//i++;
	if (write_idx >= 64)
	{
		usart_send(ACK);
		wait_host();
		execute_proc = TRUE;
	}
	
	if (execute_proc) 
	{
		char command = write_buffer[0];
		
		if (command == WRITE_MEMORY)
		{
			reset_ctrl();
			prepare_for_write();
			_delay_loop_1(100);
			
			int bytesl = write_buffer[1];
			int bytesh = write_buffer[2];
			int bytes = (bytesh << 8) | bytesl;

			for (int i = 0; i < bytes; i++)
			{
				char data = write_buffer[i + 3];
				write_mem(i, data);
				_delay_ms(10);
			}
			
			reset_ctrl();
			usart_send(ACK);
			wait_host();
		}
		else if (command == READ_MEMORY)
		{
			reset_ctrl();
			prepare_for_read();
			_delay_loop_1(100);
			
			int bytesl = write_buffer[1];
			int bytesh = write_buffer[2];
			int bytes = (bytesh <<= 8) | bytesl;
			
			for (int i = 0; i < bytes; i++)
			{
				char data = read_mem(i);
				_delay_loop_1(1);
				usart_send(data);
				wait_host();
			}
			
			reset_ctrl();
		}
		
		step = NULL;
		command = NULL;
		write_idx = 0;
		execute_proc = FALSE;
		deactivate_ports();
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

