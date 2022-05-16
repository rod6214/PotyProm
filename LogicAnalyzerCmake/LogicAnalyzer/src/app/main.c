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
        }
		else {}
    }
}

