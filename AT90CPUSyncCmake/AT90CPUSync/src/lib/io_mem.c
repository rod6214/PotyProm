/*
 * io_mem.c
 *
 * Created: 5/1/2022 2:29:07 PM
 *  Author: Nelson
 */ 
# define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "io_mem.h"

IO_MEM_t io_mem;

/**
 * @brief Set the address low as input object
 * When it works with a register to address low address 
 */

void set_address_low_as_input() 
{
	if (io_mem.mode == MEM_ADDR_LOW_PORTC) 
	{
		PORTC = 0;
		_delay_loop_1(2);
		DDRC = 0;
		_delay_loop_1(2);
	}
	else if (io_mem.mode == MEM_ADDR_LOW_REGISTER) 
	{
		PORTC |= (1 << PC0);
	}
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
	if (io_mem.mode == MEM_ADDR_LOW_PORTC) 
	{
		PORTC = 0;
		_delay_loop_1(2);
		DDRC = 255;
		_delay_loop_1(2);
	}
	else if (io_mem.mode == MEM_ADDR_LOW_REGISTER) 
	{
		PORTC &= ~(1 << PC0);
	}
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
	if (io_mem.mode == MEM_ADDR_LOW_PORTC) 
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
	else if (io_mem.mode == MEM_ADDR_LOW_REGISTER) 
	{
		char data = addressl;

		// PC0: OUTPUT ENABLE
		// PC1: LATCH CLOCK
		// PC2: SERIAL INPUT DATA A
		// PC3: SHIFT CLOCK
		// PC4: RESET
		PORTC &= ~(1 << PC4);
		_delay_loop_1(1);
		PORTC |= (1 << PC4);
		_delay_loop_1(1);

		for(int i = 0; i < 8; i++, data >>= 1) 
		{
			if ((data & 1) == 1) 
			{
				PORTC |= (1 << PC2);
			}
			else 
			{
				PORTC &= ~(1 << PC2);
			}
			_delay_loop_1(1);
			PORTC |= (1 << PC3);
			_delay_loop_1(1);
			PORTC &= ~(1 << PC3);
			_delay_loop_1(1);
		}

		_delay_loop_1(1);
		PORTC |= (1 << PC1);
		_delay_loop_1(1);
		PORTC &= ~(1 << PC1);
		_delay_loop_1(1);

		_delay_us(1);
	}
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

void init_ctrl_mem(int mode)
{
	io_mem.mode = mode;
	deactivate_ports();
	reset_ctrl();
	_delay_loop_1(20);
	DDRB = DDRB | ((1 << DDB0) | (1 << DDB1) | (1 << DDB2));
	_delay_loop_1(20);

	if (io_mem.mode == MEM_ADDR_LOW_REGISTER) 
	{
		// PC0: OUTPUT ENABLE
		// PC1: LATCH CLOCK
		// PC2: SERIAL INPUT DATA A
		// PC3: SHIFT CLOCK
		// PC4: RESET
		DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4);
		PORTC |= (1 << PC0) | (1 << PC4); 
		PORTC |=  (1 << PC4); 
		// PORTC &= ~(1 << PC1) & ~(1 << PC2) & ~(1 << PC3);
	}
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

