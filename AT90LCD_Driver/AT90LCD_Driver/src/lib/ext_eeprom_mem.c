/*
 * ext_eeprom_mem.c
 *
 * Created: 5/7/2022 7:38:20 PM
 *  Author: Nelson
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "io_mem.h"
#include "ext_eeprom_mem.h"

static EEPROM_t eeprom;

char read_mem(int address)
{
	int mode = get_mode();
	if (mode == MEM_ADDR_WITH_REGISTERS)
	{
		set_address(address);
	}
	else 
	{
		char addressl = LOW_BYTE(address);
		char addressh = HIGH_BYTE(address);
		set_address_low(addressl);
		set_address_high(addressh);
	}
	
	_delay_loop_1(5);
	set_chip_enable(TRUE);
	_delay_loop_1(5);
	set_output_enable(TRUE);
	_delay_loop_1(5);
	char data = 0;
	int i = 0;
	while(i < 5)
	{
		data = get_data();
		i++;
		_delay_loop_1(5);
	}
	set_chip_enable(FALSE);
	_delay_loop_1(5);
	set_output_enable(FALSE);
	_delay_loop_1(5);
	return data;
}

void write_mem(int address, char data)
{
	int mode = get_mode();
	if (mode == MEM_ADDR_WITH_REGISTERS)
	{
		set_address(address);
	}
	else 
	{
		char addressl = LOW_BYTE(address);
		char addressh = HIGH_BYTE(address);
		set_address_low(addressl);
		set_address_high(addressh);
	}
	
	_delay_ms(5);
	set_write_enable(TRUE);
	_delay_ms(1);
	set_data(data);
	_delay_ms(10);
	set_write_enable(FALSE);
	_delay_ms(5);
}


void prepare_for_read()
{
	_delay_loop_1(20);
	set_data_as_input();
	_delay_loop_1(20);
}

void prepare_for_write()
{
	_delay_loop_1(20);
	set_data_as_output();
	_delay_loop_1(20);
	set_chip_enable(TRUE);
	_delay_loop_1(20);
	set_output_enable(FALSE);
	_delay_loop_1(20);
}


EEPROM_t* get_eeprom(char* buffer) 
{
	eeprom.bytesl = buffer[1];
	eeprom.bytesh = buffer[2];
	eeprom.offsetl = buffer[3];
	eeprom.offseth = buffer[4];
	return &eeprom;
}
