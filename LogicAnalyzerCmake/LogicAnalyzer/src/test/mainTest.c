
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
	serial_set_command(data);
	sei();
}

void config()
{
    usart_start();
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
}
