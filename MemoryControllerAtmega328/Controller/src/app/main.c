/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "eeprom/eeprom.h"
#include "shifter/595_driver.h"

void config()
{
	// PORTD = 0;
	// DDRD = 255;
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
	// PORTB = 0x00;		  //pull-up on for pushbutton
  	// DDRB  = 0xef;		  //MISO line i/p, rest o/p
	// EEPROM_init();
	// EEPROM_Write(0, 2, 0);
	PORT_Init();
	reset_port();
	OE_off();
	MR_on();
	write_port(262657, 0);
}


void loop() 
{
	// DDRD = 0xff;
}

int main(void)
{
	config();
	// DDRD = 0x22;
	// PORTD = 0xff;
    // /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

