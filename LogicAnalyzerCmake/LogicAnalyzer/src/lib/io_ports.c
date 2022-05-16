/*
 * io_ports.c
 *
 * Created: 5/15/2022 7:29:03 PM
 *  Author: Nelson
 */
#include <avr/io.h>
#include "io_ports.h"

void set_porta_direction(char pins) 
{
    DDRA = pins;
}

void set_porta(char value)
{
    PORTA = value;
}

void set_portc_direction(char pins) 
{
    DDRC = pins;
}

void set_portc(char value)
{
    PORTC = value;
}

char read_porta() 
{
    return PINA;
}

char read_portc()
{
    return PINC;
}

char read_registerA() 
{
    return PORTA;
}

char read_registerC()
{
    return PORTC;
}

void set_pin(volatile uint8_t* port, uint8_t pin) 
{
    // volatile uint8_t* pp = (volatile uint8_t*)(uint16_t)port;
    // *pp = *pp | (1 << (volatile uint8_t)pin);
    *port = *port | (1 << (volatile uint8_t)pin);
}

void clear_pin(volatile uint8_t* port, uint8_t pin) 
{
    // volatile uint8_t* pp = (volatile uint8_t*)(uint16_t)port;
    // *pp = *pp & (~(1 << (volatile uint8_t)pin));
    *port = *port & (~(1 << (volatile uint8_t)pin));
}
