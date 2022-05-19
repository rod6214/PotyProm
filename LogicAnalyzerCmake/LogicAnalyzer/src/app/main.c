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
#include "serial.h"
#include "io_ports.h"
#include "external_int.h"

void read_processor();
void reset_processor();
void send_invalid_command_error();
int edge_state = 0;
// int memory_read = FALSE;
char pinValue = '\0';
int system_ready = FALSE;

ISR(USART0_TX_vect)
{
	cli();
    set_as_sent();
	sei();
}

ISR(USART0_RX_vect)
{
	cli();
	char data = usart_receive();
	serial_process_input(data);
	sei();
}

ISR(INT4_vect) 
{
	disable_int4();
	clear_int4_flag();
	edge_state++;
}

void config()
{
	usart_start();
    init_serial();
    set_porta(0);
    set_portc(0);
	set_portl(0);
	// set_pin(&PORTC, PIN_RESET);
	// set_portl_direction(255);
    set_porta_direction(0);
    set_portc_direction((1 << PIN_READY));
	sense_on_rising_edge_int4();
	_delay_loop_1(10);
	// enable_int4();
    sei();
}

void loop() 
{
	// if (((PINC & (1 << PIN_SYSTEM_RDY)) == (1 << PIN_SYSTEM_RDY)) && !system_ready) 
	// {
	// 	enable_int4();
	// 	system_ready = TRUE;
	// }

	int idx = get_pointer_value();
    if (idx < 6)
    {
        return;
    }
    else 
    {
        reset_pointer();
    }

    int status = serial_get_status();
    if (status == PENDING) 
    {
        int command = serial_get_command();

		// if (command == READ_PROCESSOR) 
		// {
		// 	// set_pin(&PORTC, PIN_READY);
		// 	// _delay_loop_1(1);
		// 	// clear_pin(&PORTC, PIN_READY);
		// 	// read_processor();
		// }
		// else 
		if (command == READ_VARIABLE) 
		{
			
			enable_int4();
			while(edge_state == 0);
			set_pin(&PORTC, PIN_READY);
			enable_int4();
			while(edge_state == 1);
			clear_pin(&PORTC, PIN_READY);
			edge_state=0;
			_delay_loop_1(10);
			pinValue = PINA;
			char portState[] = { pinValue };
			serial_send_data(portState, 1);
			command = NULL;
			// memory_read = FALSE;
		}
		else 
		{
			send_invalid_command_error();
		}
    }
}

void read_processor() 
{
	// set_pin(&PORTC, PIN_RESET);
	// set_pin(&PORTC, PIN_SCK);
	// set_pin(&PORTC, PIN_READY);
	// _delay_us(10);
	// clear_pin(&PORTC, PIN_SCK);
    // char pinValue;
	// int i = 0;
	// while(i < 50) 
	// {
	// 	pinValue = PINA;
	// 	i++;
	// }
	// char portState[] = { pinValue };
	// serial_send_data(portState, 1);
}

// void reset_processor() 
// {
// 	set_pin(&PORTC, PIN_SCK);
// 	set_pin(&PORTC, PIN_READY);
// 	_delay_us(10);
// 	clear_pin(&PORTC, PIN_SCK);
// 	clear_pin(&PORTC, PIN_RESET);
// 	_delay_us(10);
// 	set_pin(&PORTC, PIN_SCK);
// 	_delay_us(10);
// 	char pinValue;
// 	int i = 0;
// 	while(i < 50) 
// 	{
// 		pinValue = PINA;
// 		_delay_us(1);
// 		i++;
// 	}
// 	char portState[] = { pinValue };
// 	serial_send_data(portState, 1);
// }

void send_invalid_command_error() 
{
    serial_set_command(ERROR);
    serial_send_data("Invalid command error.", 22);
}
