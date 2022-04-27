/*
 * io_handle.c
 *
 * Created: 4/25/2022 1:28:55 PM
 *  Author: Nelson
 */ 
#include <avr/io.h>
#include "io_handle.h"

void set_address_low_as_highZ()
{
	DDRB = 0;
	PORTB = 0;
}

void set_address_high_as_highZ()
{
	DDRC = 0;
	PORTC = 0;
}

void set_port_data_as_highZ()
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
	set_port_data_as_highZ();
	return PORTD;
}

void ctrl_init() 
{
	set_address_low_as_highZ();
	set_address_high_as_highZ();
	set_port_data_as_highZ();
	ctrl_high();
	DDRE = DDRE | (1 << DDE2) | (1 << DDE3) | (1 << DDE4);
}

void ctrl_high() 
{
	PORTE = PORTE | ((1 << PORTE2));
	PORTE = PORTE | ((1 << PORTE3));
	PORTE = PORTE | ((1 << PORTE4));
}
	
void ctrl_low()
{
	PORTE = PORTE & (~(1 << PORTE2));
	PORTE = PORTE & (~(1 << PORTE3));
	PORTE = PORTE & (~(1 << PORTE4));
}

void ctrl_chip_enable(int value) 
{
	// Port E2
	if (value) 
	{
		PORTE = PORTE & (~(1 << PORTE2));
	}
	else 
	{
		PORTE = PORTE | (1 << PORTE2);
	}
}
	
void ctrl_output_enable(int value) 
{
	// Port E3
	if (value)
	{
		PORTE = PORTE & (~(1 << PORTE3));
	}
	else
	{
		PORTE = PORTE | (1 << PORTE3);
	}
}

void ctrl_write_enable(int value) 
{
	// Port E4
	if (value)
	{
		PORTE = PORTE & (~(1 << PORTE4));
	}
	else
	{
		PORTE = PORTE | (1 << PORTE4);
	}
}
