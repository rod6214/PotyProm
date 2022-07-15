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

int pointer = 0;

#define CLEAR_DISPLAY 13
#define INPUT_DATA 17

void prepare_ext_int();

ISR(INT0_vect)
{
	cli();
	_delay_loop_1(2);
	if ((PINC & 3) != 1) {
		return;
	}
	char data = PINA;
	if (data == CLEAR_DISPLAY) {
		LCD_clearDisplay();
	}
	else if (data == INPUT_DATA || pointer > 0) {
		if (pointer == 1) {
			consoleWriteCommand(LCD_WRITE, data);
		}
		pointer++;
		if (pointer > 1) {
			pointer = 0;
		}
	}
	sei();
}

void config() 
{
	LCDConsoleInit(LCD_SERIAL_MODE);
	prepare_ext_int();
	sei();
}

void prepare_ext_int() {
	DDRA = 0;
	DDRC = 0;
	MCUCR = (1 << ISC01);
	GIMSK = (1 << INT0);
	_delay_loop_1(10);
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

