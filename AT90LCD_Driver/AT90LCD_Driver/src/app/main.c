/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "lcd.h"

void config() 
{
	LCDConsoleInit(LCD_SERIAL_MODE);
	consoleWriteCommand(LCD_WRITE, 'Q');
	consoleWriteCommand(LCD_WRITE, 'u');
	consoleWriteCommand(LCD_WRITE, 'e');
	consoleWriteCommand(LCD_WRITE, ' ');
	consoleWriteCommand(LCD_WRITE, 'h');
	consoleWriteCommand(LCD_WRITE, 'a');
	consoleWriteCommand(LCD_WRITE, 'c');
	consoleWriteCommand(LCD_WRITE, 'e');
	consoleWriteCommand(LCD_WRITE, 's');
	consoleWriteCommand(LCD_WRITE, '?');
}

void loop() 
{}

int main(void)
{
	config();
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

