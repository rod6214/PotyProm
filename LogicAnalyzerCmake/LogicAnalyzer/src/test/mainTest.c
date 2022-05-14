
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

static const char* _msg = "There can only be one root content control inside the GroupBox. If you would like to add.";

void config()
{
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
    char* buffer = serial_get_buffer();
    int len = serial_count();
    for(int i = 0; i < len; i++) 
    {
        buffer[i] = _msg[i];
    }
    serial_send_response();
}
