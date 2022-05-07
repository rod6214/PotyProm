/*
 * io_mem.c
 *
 * Created: 5/1/2022 2:29:07 PM
 *  Author: Nelson
 */ 
# define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "io_mem.h"

void set_address_low_as_input() 
{
	PORTC = 0;
	_delay_loop_1(2);
	DDRC = 0;
	_delay_loop_1(2);
}

void set_address_high_as_input()
{
	PORTA = 0;
	_delay_loop_1(2);
	DDRA = 0;
	_delay_loop_1(2);
}

void set_data_as_input()
{
	PORTD = PORTD & (~252);
	_delay_loop_1(1);
	PORTB = PORTB & (~24);
	_delay_loop_1(1);
	DDRD = DDRD & (~252);
	_delay_loop_1(1);
	DDRB = DDRB & (~24);
	_delay_loop_1(1);
}

void set_address_low_as_output()
{
	PORTC = 0;
	_delay_loop_1(2);
	DDRC = 255;
	_delay_loop_1(2);
}

void set_address_high_as_output()
{
	PORTA = 0;
	_delay_loop_1(2);
	DDRA = 255;
	_delay_loop_1(2);
}

void set_data_as_output()
{
	PORTD = PORTD & (~252);
	_delay_loop_1(1);
	PORTB = PORTB & (~24);
	_delay_loop_1(1);
	DDRD = DDRD | (252);
	_delay_loop_1(3);
	DDRB = DDRB | (24);
	_delay_loop_1(3);
}

void set_address_low(char addressl) 
{
	__asm__ volatile (
	"out %1, %0" "\n\t"
	"nop " "\n\t"
	"nop" "\n\t"
	"nop"
	: 
	: "r" (addressl), "I" (0x15)
	);
}

void set_address_high(char addressh)
{
	__asm__ volatile (
	"out %1, %0" "\n\t"
	"nop " "\n\t"
	"nop" "\n\t"
	"nop"
	:
	: "r" (addressh), "I" (0x1B)
	);
}

void reset_ctrl() 
{
	PORTB |= ((1 << PB0) | (1 << PB1) | (1 << PB2));
}


char get_data() 
{
	char datah = 0;
	char datal = 0;
	datah = PIND & 252;
	datal = (PINB & 24) >> 3;
	return datah | datal;
}

void set_data(char data) 
{
	char resetOldDataD = PORTD & (~252);
	char resetOldDataB = PORTB & (~24); 
	PORTD = resetOldDataD | (data & 252);
	PORTB = resetOldDataB | ((data & 3) << 3);
	_delay_loop_1(20);
}
	
void set_chip_enable(int value)
{
	if (!value) 
	{
		PORTB = PORTB | ((1 << PB0));
	}
	else 
	{
		PORTB = PORTB & (~(1 << PB0));
	}
}

void set_output_enable(int value) 
{
	if (!value)
	{
		PORTB = PORTB | ((1 << PB1));
	}
	else
	{
		PORTB = PORTB & (~(1 << PB1));
	}
}

void set_write_enable(int value)
{
	if (!value)
	{
		PORTB = PORTB | ((1 << PB2));
	}
	else
	{
		PORTB = PORTB & (~(1 << PB2));
	}
}

void init_ctrl_mem()
{
	deactivate_ports();
	reset_ctrl();
	_delay_loop_1(20);
	DDRB = DDRB | ((1 << DDB0) | (1 << DDB1) | (1 << DDB2));
	_delay_loop_1(20);
}

void deactivate_ports()
{
	_delay_loop_1(20);
	set_address_high_as_input();
	set_address_low_as_input();
	_delay_loop_1(20);
	set_data_as_input();
	_delay_loop_1(20);
}

