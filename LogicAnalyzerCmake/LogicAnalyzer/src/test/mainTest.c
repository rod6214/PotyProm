
/*
 * mainTest.c
 *
 * Created: 5/14/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "standard.h"
#include "io_uart.h"
#include "serial.h"
#include "io_ports.h"

void read_string();
void read_processor();
void turn_on_pinC1();
void turn_off_pinC1();
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

        if (command == READ_STRING) 
        {
            read_string();
        }
        else if (command == TURN_ON_PINC1) 
        {
            turn_on_pinC1();
        }
        else if (command == TURN_OFF_PINC1) 
        {
            turn_off_pinC1();
        }
        // else if (command == READ_PROCESSOR) 
        // {

        // }
        else 
        {
            send_invalid_command_error();
        }
    }
}

void read_string() 
{
    serial_send_data("There can only be one root content control inside the GroupBox. If you would like to add.", 89);
}

void turn_on_pinC1() 
{
    set_pin(&PORTC, PINC1);
    char* ibuffer = serial_get_buffer();
    ibuffer[0] = PORTC & (1 << PINC1) ? TRUE : FALSE;
    serial_send_response();
}

void turn_off_pinC1() 
{
    clear_pin(&PORTC, PINC1);
    char* ibuffer = serial_get_buffer();
    ibuffer[0] = PORTC & (1 << PINC1) ? TRUE : FALSE;
    serial_send_response();
}

void send_invalid_command_error() 
{
    serial_set_command(ERROR);
    serial_send_data("Invalid command error.", 22);
}

void read_processor()
{
}
