
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "global.h"
#include "lcd_driver.h"

int pointer = 0;
int execute_proc = FALSE;
int starting_sequence = 0;
char _buffer[MAX_MEMORY + 5];
char command;
int bytes;
char start_tokens[] = {241, 33, 78, 91};
/*
COMMAND
BYTES
DATA[]
*/
ISR(INT0_vect)
{
	cli();
    char data = INPUT_PIN;
    if (starting_sequence > 3) 
	{
		_buffer[pointer] = data;
		pointer++;
        if (pointer == PACKAGE_SIZE) 
        {
            execute_proc = TRUE;
        }
	}
	else if (start_tokens[starting_sequence] == data) 
	{
		starting_sequence++;
	}
	else 
	{
		starting_sequence = 0;   
	}
    resetFlag();
    // consoleWriteCommand(LCD_WRITE, 'T');
	sei();
}
