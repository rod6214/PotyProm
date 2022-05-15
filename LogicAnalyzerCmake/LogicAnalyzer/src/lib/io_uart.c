/*
 * io_uart.c
 *
 * Created: 5/7/2022 7:29:03 PM
 *  Author: Nelson
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "standard.h"
#include "io_uart.h"

static int data_sent = FALSE;

void usart_start()
{
    /************************************************************************/
    /*   UBRR0 = fosc/(8*BAUD) - 1                                          */
    /************************************************************************/
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // UBRR0 = 207; // 9660
    UBRR0 = 103; // 19200
    _delay_loop_1(5);
}

void usart_send(char data)
{
    UDR0 = data;
}

char usart_receive()
{
    return UDR0;
}

void wait_host()
{
    while(!data_sent); 
    data_sent=FALSE;
}

void set_as_sent() 
{
    data_sent = TRUE;
}
