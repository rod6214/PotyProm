/*
 * io_uart.c
 *
 * Created: 5/7/2022 7:29:03 PM
 *  Author: Nelson
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "io_uart.h"

void usart_start()
{
    /************************************************************************/
    /*   UBRR0 = fosc/(8*BAUD) - 1                                          */
    /************************************************************************/
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0 = 207;
    //UBRR0 = 103;
    _delay_loop_1(1);
}

void usart_send(char data)
{
    UDR0 = data;
}

char usart_receive()
{
    return UDR0;
}