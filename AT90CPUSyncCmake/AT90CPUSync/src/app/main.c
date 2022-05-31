/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "io_uart.h"
#include "ext_eeprom_mem.h"

#define MAX_MEMORY 64
char _buffer[MAX_MEMORY + 5];
int _idx = 0;
int command = 0;
int data_sent = FALSE;
int execute_proc = FALSE;
int starting_sequence = 0;
char start_tokens[] = {241, 33, 78, 91};

#define wait_host() while(!data_sent); data_sent=FALSE

void start_system();
void start_program();
void debug_mode();
void prepare_cpu_card();

ISR(USART_TX_vect)
{
	cli();
	data_sent = TRUE;
	sei();
}

ISR(USART_RX_vect)
{
	cli();
	char data = usart_receive();
	if (starting_sequence > 3) 
	{
		_buffer[_idx] = data;
		_idx++;
	}
	else if (start_tokens[starting_sequence] == data) 
	{
		starting_sequence++;
	}
	else 
	{
		starting_sequence = 0;
	}
	sei();
}

void config()
{
	usart_start();
	// // Use a shift register as low address bits
	init_ctrl_mem(MEM_ADDR_LOW_REGISTER);
	// init_ctrl_mem(MEM_ADDR_LOW_PORTC);
	prepare_cpu_card();
	_delay_loop_1(100);
	_idx = 0;
	execute_proc = FALSE;
	start_system();
	sei();
}

void start_system()
{
	// PC5 RESET
	// PC6 NMI
	// PC7 CPU BUFFER
	_delay_loop_1(4);
	PORTC = PORTC | (1 << PC5);
	_delay_loop_1(4);
	PORTC = PORTC | (1 << PC6);
	_delay_loop_1(8);
	PORTC = PORTC | (1 << PC7);
	_delay_loop_1(8);
}

void start_program()
{
	PORTC = PORTC & ~(1 << PC5);
	_delay_loop_1(4);
	PORTC = PORTC & ~(1 << PC7);
	_delay_loop_1(100);
}

void debug_mode()
{
}

void prepare_cpu_card()
{
	// // Clear all signals
	PORTC &= ~(1 << PC5) & ~(1 << PC6) & ~(1 << PC7);
	// Set control pins as outputs
	DDRC |= (1 << PC5) | (1 << PC6) | (1 << PC7);
}

void loop() 
{
	if (_idx >= 64)
	{
		usart_send(ACK);
		wait_host();
		execute_proc = TRUE;
	}
	
	if (execute_proc) 
	{
		char command = _buffer[0];
		
		if (command == WRITE_MEMORY)
		{
			reset_ctrl();
			prepare_for_write();
			_delay_loop_1(100);
			
			EEPROM_t* pEeprom = get_eeprom(_buffer);

			for (int i = 0; i < pEeprom->bytes; i++)
			{
				char data = _buffer[i + 5];
				write_mem(i + pEeprom->offset, data);
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
			_delay_loop_1(5);
			
			EEPROM_t* pEeprom = get_eeprom(_buffer);
			
			for (int i = 0; i < pEeprom->bytes; i++)
			{
				char data = read_mem(i + pEeprom->offset);
				_delay_loop_1(1);
				usart_send(data);
				wait_host();
			}
			
			reset_ctrl();
		}
		else if (command == PROGRAM_MODE) 
		{
			start_program();
			usart_send(ACK);
			wait_host();
		}
		// else if (command == DEBUG_MODE) 
		// {
		// 	// TODO: Make this option selectable, now this is activated by default
		// }
		else if (command == RUN_MODE) 
		{
			// TODO: Add logic for run mode, it is momentarily deactivated
			start_system();
			usart_send(ACK);
			wait_host();
		}
		
		command = NULL;
		_idx = 0;
		execute_proc = FALSE;
		starting_sequence = 0;
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

