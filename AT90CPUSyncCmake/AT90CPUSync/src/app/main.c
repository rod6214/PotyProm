/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "io_uart.h"
#include "ext_eeprom_mem.h"

#define MAX_MEMORY 64
#define MODE_ONLY_PROGRAMMER 78

char _buffer[MAX_MEMORY + 5];
int _idx = 0;
int command = 0;
int data_sent = FALSE;
int execute_proc = FALSE;
int starting_sequence = 0;
int isModeProgramming = FALSE;
char start_tokens[] = {241, 33, 78, 91};

int circuitMode = NULL;

#define wait_host() while(!data_sent); data_sent=FALSE

void start_system();
void start_program_memory();
void debug_mode(int active);
void program_mode(int active);
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
	circuitMode = MODE_ONLY_PROGRAMMER;
	int controlMode = circuitMode != MODE_ONLY_PROGRAMMER ? 
	MEM_ADDR_WITH_REGISTERS : NULL;
	usart_start();
	// // Use a shift register as low address bits
	init_ctrl_mem(controlMode);
	// init_ctrl_mem(MEM_ADDR_LOW_REGISTER);
	// init_ctrl_mem(MEM_ADDR_LOW_PORTC);
	prepare_cpu_card();
	_delay_loop_1(100);
	_idx = 0;
	execute_proc = FALSE;
	start_system();
	sei();
	// set_address_as_output();
	// set_address(30869);
}

void start_system()
{
	if (circuitMode != MODE_ONLY_PROGRAMMER) 
	{
		// PC5 RESET
		// PC6 NMI
		// PC7 CPU BUFFER
		// PD6 PROGRAM SIGNAL MODE
		// PD7 DEBUG SIGNAL MODE
		_delay_loop_1(4);
		PORTC = PORTC | (1 << PC5);
		_delay_loop_1(4);
		PORTC = PORTC | (1 << PC6);
		_delay_loop_1(8);
		PORTC = PORTC | (1 << PC7);
		_delay_loop_1(8);
		PORTD = PORTD | (1 << PD7);
		_delay_loop_1(8);
	}
	else 
	{
		PORTB &= ~(1 << PB6) & ~(1 << PB7) & ~(1 << PB0);
		// INIT START SEQUENCE
		// PB6 HALT
		// PB7 RESET
		// PB0 NMI
		_delay_loop_1(8);
		PORTB = PORTB | (1 << PB6);
		_delay_loop_1(4);
		PORTB = PORTB | (1 << PB7);
		_delay_loop_1(4);
		PORTB = PORTB | (1 << PB0);
		_delay_loop_1(4);
	}
	isModeProgramming = FALSE;
}

void start_program_memory()
{
	if (circuitMode != MODE_ONLY_PROGRAMMER) 
	{
		PORTC = PORTC & ~(1 << PC5);
		_delay_loop_1(4);
		PORTC = PORTC & ~(1 << PC7);
		_delay_loop_1(100);
	}
	else 
	{
		// RESET
		// PORTB = PORTB & ~(1 << PB7);
		_delay_loop_1(8);
	}
	isModeProgramming = TRUE;
}

void debug_mode(int active)
{
	if (circuitMode == MODE_ONLY_PROGRAMMER)
	{
		// ACTIVATE HALT
		PORTB = PORTB & ~(1 << PB6);
		_delay_loop_1(4);
		PORTB = PORTB | (1 << PB7);
		return;
	}

	if (active) 
	{
		PORTD = PORTD & ~(1 << PD7);
	}
	else 
	{
		PORTD = PORTD | (1 << PD7);
	}
	
	_delay_loop_1(8);
}

void program_mode(int active)
{
	/**
	 * @brief Construct a new if object
	 * PB6: HALT
	 * PB7: RESET
	 */
	if (circuitMode == MODE_ONLY_PROGRAMMER)
	{
		// ACTIVATE HALT
		PORTB &= ~(1 << PB6);
		_delay_ms(5);
		PORTB &= ~(1 << PB7);
		return;
	}

	if (active) 
	{
		PORTD = PORTD | (1 << PD6);
	}
	else 
	{
		PORTD = PORTD & ~(1 << PD6);
	}
	
	_delay_loop_1(8);
}

void prepare_cpu_card()
{
	if (circuitMode != MODE_ONLY_PROGRAMMER) 
	{
		// // Clear all signals
		PORTC &= ~(1 << PC5) & ~(1 << PC6) & ~(1 << PC7);
		PORTD &= ~(1 << PD7) & ~(1 << PD6);
		// Set control pins as outputs
		DDRC |= (1 << PC5) | (1 << PC6) | (1 << PC7);
		DDRD |= (1 << PD7) | (1 << PD6);
	}
	else 
	{
		// PB7 RESET
		// PB6 HALT
		SPCR = 4;
		_delay_loop_1(4);
		PORTB &= ~(1 << PB6) & ~(1 << PB7);
		DDRB |= (1 << DDB6) | (1 << DDB7);
	}
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
		
		if (command == WRITE_MEMORY && isModeProgramming)
		{
			reset_ctrl();
			prepare_for_write();
			_delay_loop_1(100);
			
			EEPROM_t* pEeprom = get_eeprom(_buffer);

			for (int i = 0; i < pEeprom->bytes; i++)
			{
				char data = _buffer[i + 5];
				write_mem(i + pEeprom->offset, data);
				
			}
			
			_delay_ms(10);
			reset_ctrl();
			usart_send(ACK);
			wait_host();
		}
		else if (command == READ_MEMORY && isModeProgramming)
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
			program_mode(TRUE);
			// debug_mode(TRUE);
			start_program_memory();
			set_address_as_output();
			usart_send(ACK);
			wait_host();
		}
		else if (command == DEBUG_MODE) 
		{
			set_address_as_input();
			debug_mode(TRUE);
			// program_mode(FALSE);
			usart_send(ACK);
			// start_system();
			wait_host();
		}
		else if (command == RUN_MODE) 
		{
			set_address_as_input();
			// debug_mode(FALSE);
			// program_mode(FALSE);
			start_system();
			usart_send(ACK);
			wait_host();
		}
		else 
		{
			usart_send(ERROR);
			wait_host();
		}
		
		command = NULL;
		_idx = 0;
		execute_proc = FALSE;
		starting_sequence = 0;
		// deactivate_ports();
		deactivate_port_data();
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

