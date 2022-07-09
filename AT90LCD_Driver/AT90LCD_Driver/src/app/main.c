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
	LCDInit(TRUE);
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

