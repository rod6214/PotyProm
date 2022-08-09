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
#include "global.h"
#include "lcd_driver.h"

void reset_lcd_sequence() 
{
    pointer = 0;
    starting_sequence = 0;
}

void config()
{
	INPUT_PORT = 0;
	INPUT_TRIS = 0;
	EICRA = (1 << ISC01) | (1 << ISC00);
	EIMSK = (1 << INT0);
	LCDConsoleInit(LCD_SERIAL_MODE);
  _delay_loop_1(200);
	// consoleWriteCommand(LCD_WRITE, 'T');
	sei();
}

void loop() 
{
	if (!execute_proc) 
	{
			return;
	}

	command = _buffer[0];
	bytes = _buffer[1];

	int dataReceived = pointer - 2;
			
	if (dataReceived == bytes) 
	{
		switch(command) 
		{
			case LCD_WRITE:
			{
					for(int i = 0; i < bytes; i++) 
					{
							consoleWriteCommand(LCD_WRITE, _buffer[i + 2]);
					}
			}
			break;
			case RETURN_HOME:
			{
					consoleWriteCommand(LCD_COMMAND, RETURN_HOME);
			}
			break;
			case CLEAR_DISPLAY:
			{
					consoleWriteCommand(LCD_COMMAND, 1);
			}
			break;
			case SET_ADDRESS:
			{
				setAddress(_buffer[2]);
			}
			break;
			case DISPLAY_ON:
			{
					consoleWriteCommand(LCD_COMMAND, DISPLAY_ON);
			}
			break;
			case LCD_RESET:
			{
					reset_lcd();
			}
			break;
			default:
			{
					reset_lcd_sequence();
			}
			break;
		}
	}

	pointer = 0;
	starting_sequence = 0;
	execute_proc = FALSE;
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

