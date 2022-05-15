
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

// static const char* _msg = "There can only be one root content control inside the GroupBox. If you would like to add.";

void read_processor();

// #define MAX_MEMORY 1024
// #define MAX_COMMAND_BUFFER 6

// char _buffer[MAX_MEMORY];
// char _command_buffer[MAX_COMMAND_BUFFER];
// int _idx = 0;
// int isBusy = FALSE;

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
	serial_set_command(data);
	sei();
}

void config()
{
    usart_start();
    PORTA = 0;
    DDRA = 255;
    init_serial();
    sei();
}

void loop() 
{
    int status = serial_get_status();

    if (status == PENDING) 
    {
        int command = serial_get_command();

        if (command == READ_PROCESSOR) 
        {
            read_processor();
        }
    }
}

void read_processor() 
{
    serial_send_data("There can only be one root content control inside the GroupBox. If you would like to add.", 89);
    // char* dat = serial_get_buffer();
    // int len = serial_count();
    // for(int i = 0; i < len; i++) 
    // {
    //     dat[i] = _msg[i];
    // }
    // serial_send_response();
}
