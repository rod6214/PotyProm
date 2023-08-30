/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "io_uart.h"
#include "ext_eeprom_mem.h"

#define MAX_MEMORY 64
#define MODE_ONLY_PROGRAMMER 78
#define BUFFER_LENGTH 16

int8_t _counter = 1;
int8_t _shifter = 1;
int8_t _state = 0;
int8_t _port = 0;
int _sampleCounter = 0;
int8_t _buffer[BUFFER_LENGTH];

#define CLK_T PIN6
#define MR_T PIN5
#define BUSSY PIN4

ISR(PCINT1_vect) 
{
	cli();
	if (_counter == BUFFER_LENGTH)
	{
		PORTD |= (1 << BUSSY);
		_counter = 0;
	}

	int8_t sample = PINC & 15;
	// _sampleCounter control keypad sensibility
	if (_sampleCounter < 256)
	{
		_sampleCounter++;
		return;
	}
	
	if (sample == 0x7) 
	{
		if (_state == 0x7) 
		{
			_port = 0xf;
		}
		else if (_state == 0xb)
		{
			_port = 0;
		}
		else if (_state == 0xd)
		{
			_port = 0xe;
		}
		else if (_state == 0xe)
		{
			_port = 0xd;
		}
		// _buffer[_counter] = _port;
		// _counter++;
	}
	else if (sample == 0xb)
	{
		if (_state == 0x7) 
		{
			_port = 0x7;
		}
		else if (_state == 0xb)
		{
			_port = 0x8;
		}
		else if (_state == 0xd)
		{
			_port = 0x9;
		}
		else if (_state == 0xe)
		{
			_port = 0xc;
		}
		// _buffer[_counter] = _port;
		// _counter++;
	}
	else if (sample == 0xd)
	{
		if (_state == 0x7) 
		{
			_port = 0x4;
		}
		else if (_state == 0xb)
		{
			_port = 0x5;
		}
		else if (_state == 0xd)
		{
			_port = 0x6;
		}
		else if (_state == 0xe)
		{
			_port = 0xb;
		}
		// _buffer[_counter] = _port;
		// _counter++;
	}
	else if (sample == 0xe)
	{
		if (_state == 0x7) 
		{
			_port = 0x1;
		}
		else if (_state == 0xb)
		{
			_port = 0x2;
		}
		else if (_state == 0xd)
		{
			_port = 0x3;
		}
		else if (_state == 0xe)
		{
			_port = 0xa;
		}
		// _buffer[_counter] = _port;
		// _counter++;
	}

	_sampleCounter = 0;
	sei();
}

ISR(PCINT2_vect)
{
	cli();
	if ((PIND & (1 << PIN5))) 
	{
		if (_counter > 0)
		{
			_counter--;
		}
		else 
		{
			PORTD &= ~(1 << BUSSY);
		}
	}
	sei();
}

void config()
{
	DDRB = (1 << PIN0) | (1 << PIN1) | (1 << PIN6) | (1 << PIN7);
	DDRC = 0;
	DDRD = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4);
	PORTD = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	PORTB = 0;
	PCMSK1 = (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	// PCMSK2 = (1 << PCINT21);
	PCICR = (1 << PCIE1);
	// PCICR = (1 << PCIE1) | (1 << PCIE2);
	sei();
}

void convertToPortB(int8_t value) 
{
	int8_t ac = value;
	
	if ((value & (1 << PIN2))) 
	{
		ac |= (1 << PIN6);
	}
	else 
	{
		ac &= ~(1 << PIN6);
	}

	if ((value & (1 << PIN3))) 
	{
		ac |= (1 << PIN7);
	}
	else 
	{
		ac &= ~(1 << PIN7);
	}
	PORTB = ac;
}

void loop() 
{
	// PORTB = _buffer[_counter - 1];
	// PORTB = _port;
	convertToPortB(_port);
	
	if (_shifter == 16)
		_shifter = 1;
	_state = (~(_shifter)) & 15;
	if (_state == 0x7) 
	{
		PORTD |= 15;
		PORTD &= ~(1 << PIN3);
	}
	else if (_state == 0xb)
	{
		PORTD |= 15;
		PORTD &= ~(1 << PIN2);
	}
	else if (_state == 0xd)
	{
		PORTD |= 15;
		PORTD &= ~(1 << PIN1);
	}
	else if (_state == 0xe)
	{
		PORTD |= 15;
		PORTD &= ~(1 << PIN0);
	}
	_shifter <<= 1;
}

int main(void)
{
	config();
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

