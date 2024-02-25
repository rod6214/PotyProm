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

#define DOE PINB0
#define Deactivate_Buffer() (DDRD=0)
#define Activate_Buffer() (DDRD=255)

void TWI_Receiv_irq(uint8_t value, uint16_t command, size_t bytes, int id) 
{
	if (command == WRITE_EXT_MEMORY) 
	{
		Activate_Buffer();
		PORTD = value;
	}
	else if (command == ENABLE_DATA_BUFFER) 
	{
		Deactivate_Buffer();
	}
	else if (command == DISABLED_DATA_BUFFER) 
	{
		Activate_Buffer();
	}
}

void TWI_Transmit_irq(volatile uint8_t * pdata, uint16_t command, size_t bytes) 
{
	if (command == READ_EXT_MEMORY) 
	{
		if (DDRD == 255)
			DDRD = 0;
		*pdata = PIND;
	}
}

void config()
{
	DDRD = 0;
	MCUCR |= (1 << PUD);
	I2C_Register_Receiving_Callback(TWI_Receiv_irq);
	I2C_Register_Transmition_Callback(TWI_Transmit_irq);
	sei();
	I2C_Slave_Init(I2C_CL_100KHz, 1);
	// DDRD = 255;
}

void loop() 
{
}

int main(void)
{
	config();
    while (1) 
    {
		loop();
    }
}
