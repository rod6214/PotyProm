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

void read_processor();
void reset_processor();
void send_invalid_command_error();

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

void config()
{
	usart_start();
    init_serial();
    set_porta(0);
    set_portc(0);
	set_pin(&PORTC, PIN_RESET);
    set_porta_direction(0);
    set_portc_direction((1 << PIN_SCK) | (1 << PIN_READY) | (1 << PIN_RESET));
    sei();
}

void loop() 
{
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

        if (command == READ_PROCESSOR) 
        {   
			read_processor(); 
        }
		else if (command == RESET_PROCESSOR) 
		{
			reset_processor();
		}
		else 
		{
			send_invalid_command_error();
		}
    }
}

void read_processor() 
{
	set_pin(&PORTC, PIN_RESET);
	set_pin(&PORTC, PIN_SCK);
	set_pin(&PORTC, PIN_READY);
	_delay_us(10);
	clear_pin(&PORTC, PIN_SCK);
	clear_pin(&PORTC, PIN_READY);
    char pinValue;
	int i = 0;
	while(i < 50) 
	{
		pinValue = PINA;
		_delay_us(1);
		i++;
	}
	char portState[] = { pinValue };
	serial_send_data(portState, 1);
}

void reset_processor() 
{
	set_pin(&PORTC, PIN_SCK);
	set_pin(&PORTC, PIN_READY);
	_delay_us(10);
	clear_pin(&PORTC, PIN_SCK);
	clear_pin(&PORTC, PIN_RESET);
	_delay_us(10);
	set_pin(&PORTC, PIN_SCK);
	_delay_us(10);
	char pinValue;
	int i = 0;
	while(i < 50) 
	{
		pinValue = PINA;
		_delay_us(1);
	}
	char portState[] = { pinValue };
	serial_send_data(portState, 1);
}

void send_invalid_command_error() 
{
    serial_set_command(ERROR);
    serial_send_data("Invalid command error.", 22);
}
