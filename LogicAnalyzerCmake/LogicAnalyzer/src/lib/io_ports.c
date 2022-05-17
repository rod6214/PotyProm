/*
 * io_ports.c
 *
 * Created: 5/15/2022 7:29:03 PM
 *  Author: Nelson
 */
#include <avr/io.h>
#include "io_ports.h"


void set_porta(char value)
{
    PORTA = value;
}

void set_portc(char value)
{
    PORTC = value;
}

void set_portl(char value)
{
    PORTL = value;
}

void set_porta_direction(char pins) 
{
    DDRA = pins;
}

void set_portc_direction(char pins) 
{
    DDRC = pins;
}

void set_portl_direction(char pins) 
{
    DDRL = pins;
}

char read_porta() 
{
    return PINA;
}

char read_portc()
{
    return PINC;
}

char read_portl() 
{
    return PINL;
}

char read_registerA() 
{
    return PORTA;
}

char read_registerC()
{
    return PORTC;
}

char read_registerL()
{
    return PORTL;
}

void inc_porta()
{
    PORTA++;
}

void inc_portc()
{
    PORTC++;
}

void inc_portl()
{
    PORTL++;
}

void clear_porta()
{
    PORTA = 0;
}

void clear_portc()
{
    PORTC = 0;
}

void clear_portl()
{
    PORTL = 0;
}

void dec_porta()
{
    PORTA--;
}

void dec_portc()
{
    PORTC--;
}

void dec_portl()
{
    PORTL--;
}

void set_pin(volatile uint8_t* port, uint8_t pin) 
{
    *port = *port | (1 << (volatile uint8_t)pin);
}

void clear_pin(volatile uint8_t* port, uint8_t pin) 
{
    *port = *port & (~(1 << (volatile uint8_t)pin));
}
