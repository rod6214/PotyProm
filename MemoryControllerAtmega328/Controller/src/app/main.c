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
#include <eeprom.h>
#include <595_driver.h>
#include "configs.h"
#include <i2c.h>
#include <i2cext.h>
#include <util/twi.h>


void ERROR() 
{
	PORTB = 1;
}

ISR(INT0_vect) {
	cli();
	OE_off();
	R_on();
	CONTROL_Activate();
	// populateROM(L595_BUS_LENGTH_NORMAL);
	populateROM16bit(L595_BUS_LENGTH_NORMAL);
	PORT_Deactivate();
	CONTROL_Deactivate();
	HOLD_off();
	sei();
}

// static uint8_t data[] = {0x22};
// static uint8_t rom_data[16];

void config()
{
	// Configuring INT0 as rising edge detection
	EICRA |= (1 << ISC01) | (1 << ISC00);
	// Enabling INT0 interrupt
	EIMSK |= (1 << INT0);
	READY_on();
	_delay_ms(100);
	PORT_Init();
	EEPROM_init(I2C_CL_100KHz);
	reset_port();
	HOLD_on();
	OE_on();
	MR_on();
	// write_port(0xffffff);
	_delay_loop_1(5);
	sei();
}


void loop() 
{
	// DDRD = 0xff;
}

int main(void)
{
	config();
	// write_port(0x999999);
    // /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}
