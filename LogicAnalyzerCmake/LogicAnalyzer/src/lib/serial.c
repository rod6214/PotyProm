/*
 * serial.c
 *
 * Created: 5/14/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include "io_uart.h"
#include "standard.h"
#include "serial.h"
#if defined (SERIAL_CONSOLE)
char _buffer[1030];
int command_idx = 0;
int step = NOT_STARTED;
char* pData;

typedef struct
{
    union 
    {
        struct 
        {
            char commandL;
            char commandH;
        };
        int command;
    };
    union 
    {
        struct 
        {
            char countL;
            char countH;
        };
        int count;
    };
    union 
    {
        struct 
        {
            char offsetL;
            char offsetH;
        };
        int offset;
    };
} Command_t;

Command_t* _data_buffer;

void serial_set_command(int command) 
{
    _data_buffer->command = command;
}

void serial_set_bytes(int count) 
{
    _data_buffer->count = count;
}

int serial_process_input(char byte) 
{
    if (step == NOT_STARTED)
        return NOT_STARTED;
    if (step == PENDING)
        return PENDING;
    if (step == READY && byte == 255)
        return INVALID;
    _buffer[command_idx] = byte;
    command_idx++;
    if (6 == command_idx)
    {
        step = PENDING;
        return PENDING;
    }
    else 
    {
        step = IN_PROCESS;
        return IN_PROCESS;
    }
    return NULL;
}

void reset_pointer() 
{
    command_idx = 0;
}

int get_pointer_value() 
{
    return command_idx;
}

int serial_get_command() 
{
    return _data_buffer->command;
}

void init_serial() 
{
    command_idx = 0;
    step = READY;
    _data_buffer = (Command_t*)&_buffer[0];
    pData = &_buffer[6];
}

int serial_count()
{
    return _data_buffer->count;
}

int serial_get_status() 
{
    return step;
}

char* serial_get_buffer() 
{
    return pData;
}

void serial_send_response() 
{
    int len = serial_count();

    for(int i = 0; i < len + 6; i++) 
    {
        char data = _buffer[i];
        usart_send(data);
        wait_host();
    }
    step = READY;
}

void serial_send_data(const char* data, int bytes) 
{
    char* ibuffer = serial_get_buffer();
    int len = serial_count();
    for(int i = 0; i < len; i++) 
    {
        ibuffer[i] = data[i];
    }
    serial_send_response();
}
#endif