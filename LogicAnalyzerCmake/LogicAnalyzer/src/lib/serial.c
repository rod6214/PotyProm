/*
 * serial.c
 *
 * Created: 5/14/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include "io_uart.h"
#include "standard.h"
#include "serial.h"
#if defined (SERIAL_CONSOLE)
static char _buffer[1030];
static int command_idx;
static int step = NOT_STARTED;

struct 
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
    char* pData;
}* _data_buffer = _buffer;

int serial_set_command(char byte) 
{
    if (step == NOT_STARTED)
        return NOT_STARTED;
    if (step == PENDING)
        return PENDING;
    _buffer[command_idx++] = byte;
    if (step >= command_idx)
    {
        step = PENDING;
        command_idx = 0;
    }
    return IN_PROCESS;
}

int serial_get_command() 
{
    return _data_buffer->command;
}

void init_serial() 
{
    command_idx = 0;
    step = READY;
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
    return _data_buffer->pData;
}

void serial_send_response() 
{
    int len = serial_count();
    _data_buffer->command = ACK;
    _data_buffer->offset = 0;

    for(int i = 0; i < len + 6; i++) 
    {
        char data = _buffer[i];
        usart_send(data);
    }
    step = READY;
}
#endif