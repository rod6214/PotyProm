/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 

#include "configs.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <i2c.h>
#include <i2cext.h>
#include <util/twi.h>

static uint8_t data[512];

void TWI_Receiv_irq(uint8_t value, size_t bytes, int id) 
{
	data[id] = value;
}

void TWI_Transmit_irq(volatile uint8_t * pdata, uint8_t command, size_t bytes) 
{
	if (command == READ_EXT_MEMORY) 
	{
		DDRD = 0;
		*pdata = PIND;
	}
}

void config()
{
	// DDRD = 255;
	// PORTD = 0;
	MCUCR |= (1 << PUD);
	// data[0] = 0x33;
	// data[0] = 2;
	// data[1] = 2;
	// data[2] = 2;
	// data[3] = 2;
	// data[4] = 2;
	// EEPROM_init();
	I2C_Register_Receiving_Callback(TWI_Receiv_irq);
	I2C_Register_Transmition_Callback(TWI_Transmit_irq);
	sei();
	I2C_Slave_Init(I2C_CL_100KHz, 1);
}

void loop() 
{
	// test();
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
