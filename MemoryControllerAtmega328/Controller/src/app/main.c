/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "SPI/SPI_routines.h"
#include "SD_Driver/SD_routines.h"
#include "FAT32/FAT32.h"


void config()
{
	// DDRB = (1 << PIN0) | (1 << PIN1) | (1 << PIN6) | (1 << PIN7);
	// DDRC = 0;
	// DDRD = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4);
	// PORTD = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	// PORTB = 0;
	// PCMSK1 = (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	// // PCMSK2 = (1 << PCINT21);
	// PCICR = (1 << PCIE1);
	// // PCICR = (1 << PCIE1) | (1 << PCIE2);
	// sei();
}


void loop() 
{
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

