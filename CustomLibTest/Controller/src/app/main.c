/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/twi.h>


void ERROR() 
{
	PORTB = 1;
}

ISR(INT0_vect) {}

void config()
{
}


void loop() 
{
}

int main(void)
{
	config();
    // /* Replace with your application code */
    while (1) 
    {
		// loop();
    }
}
