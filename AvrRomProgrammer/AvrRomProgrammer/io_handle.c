/*
 * io_handle.c
 *
 * Created: 4/25/2022 1:28:55 PM
 *  Author: Nelson
 */ 
#include <avr/io.h>

void set_portB_as_highZ()
{
	DDRB = 0;
	PORTB = 0;
}

void set_portC_as_highZ()
{
	DDRC = 0;
	PORTC = 0;
}

void set_portD_as_highZ()
{
	DDRD = 0;
	PORTD = 0;
}

void set_address_low(char addressL)
{
	DDRB = 1;
	PORTB = 0;
}

void set_address_high(char addressH)
{
	DDRC = 1;
	PORTC = 0;
}

void set_data(char data)
{
	DDRD = 1;
	PORTD = 0;
}

char get_data() 
{
	set_portD_as_highZ();
	return PORTD;
}
