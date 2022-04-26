/*
 * io_handle.c
 *
 * Created: 4/25/2022 1:28:55 PM
 *  Author: Nelson
 */ 
#include <avr/io.h>
#include "io_handle.h"

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

void ctrl_chip_enable(int value) 
{
	// Port E2
	if (value) 
	{
		PORTE = PORTE | (1 << PORTE2);
	}
	else 
	{
		PORTE = PORTE & (~(1 << PORTE2));
	}
}
	
void ctrl_output_enable(int value) 
{
	// Port E3
	if (value)
	{
		PORTE = PORTE | (1 << PORTE3);
	}
	else
	{
		PORTE = PORTE & (~(1 << PORTE3));
	}
}

void ctrl_write_enable(int value) 
{
	// Port E4
	if (value)
	{
		PORTE = PORTE | (1 << PORTE4);
	}
	else
	{
		PORTE = PORTE & (~(1 << PORTE4));
	}
}
