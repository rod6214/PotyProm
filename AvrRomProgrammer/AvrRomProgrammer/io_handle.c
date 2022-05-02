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
	DDRC = 0;
	PORTC = 0;
}

void set_address_high_as_highZ()
{
	DDRL = 0;
	PORTL = 0;
}

void set_port_data_as_highZ()
{
	DDRA = 0;
	PORTA = 0;
}

void set_address_low(char addressL)
{
	DDRC = 255;
	PORTC = addressL;
}

void set_address_high(char addressH)
{
	DDRL = 255;
	PORTL = addressH;
}

void set_data(char data)
{
	DDRA = 255;
	PORTA = data;
}

char get_data() 
{
	set_port_data_as_highZ();
	return PORTA;
}

void ctrl_init() 
{
	set_address_low_as_highZ();
	set_address_high_as_highZ();
	set_port_data_as_highZ();
	ctrl_high();
	DDRE = DDRE | (1 << DDE3) | (1 << DDE4) | (1 << DDE5);
}

void ctrl_high() 
{
	PORTE = PORTE | ((1 << PORTE3));
	PORTE = PORTE | ((1 << PORTE4));
	PORTE = PORTE | ((1 << PORTE5));
}
	
void ctrl_low()
{
	// Invalid state
	//PORTE = PORTE & (~(1 << PORTE3));
	//PORTE = PORTE & (~(1 << PORTE4));
	//PORTE = PORTE & (~(1 << PORTE5));
}

void ctrl_chip_enable(int value) 
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
	
void ctrl_output_enable(int value) 
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

void ctrl_write_enable(int value) 
{
	// Port E5
	if (value)
	{
		PORTE = PORTE & (~(1 << PORTE5));
	}
	else
	{
		PORTE = PORTE | (1 << PORTE5);
	}
}
