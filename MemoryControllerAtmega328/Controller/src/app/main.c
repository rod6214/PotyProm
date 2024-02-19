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

void populateROM16bit(void);
void populateROM();


void ERROR() 
{
	PORTB = 1;
}

ISR(INT0_vect) {
	cli();
	OE_off();
	R_on();
	CONTROL_Activate();
	// populateROM();
	populateROM16bit();
	PORT_Deactivate();
	CONTROL_Deactivate();
	HOLD_off();
	sei();
}

static uint8_t data[] = {0x22, 0x23, 0x22, 0x23, 0x22, 0x23, 0x22, 0x23, 0x22, 0x23, 0x22, 0x23, 0x22, 0x23, 0x22, 0x23};
static uint8_t rom_data[16];

void config()
{
	PORTB = 0;
	PORTD = 0;
	DDRB = (1 << PORT0);
	DDRD = 255;
	_delay_ms(50);
	MCUCR |= (1 << PUD);
	
	Command_t cmd = {
		3, data, 1, 0xff88, 100
	};

	I2C_Master_Init(I2C_CL_100KHz);

	if (I2C_Send_Command(cmd)) 
	{
		PORTB |= (1 << PORT0);
	}

	if (I2C_Read_Command(cmd)) 
	{
		PORTB |= (1 << PORT0);
	}

	cmd.command = READ_EXT_MEMORY;

	if (I2C_Read_Command(cmd)) 
	{
		PORTB |= (1 << PORT0);
	}


	EEPROM_Read_Page(0,rom_data,16,0);

	// EEPROM_Write(0, 0x36, 0);

	// EEPROM_Write_Page(0, data, 16, 0);
	
	// Configuring INT0 as rising edge detection
	// EICRA |= (1 << ISC01) | (1 << ISC00);
	// // Enabling INT0 interrupt
	// EIMSK |= (1 << INT0);
	// READY_on();
	// _delay_ms(100);
	//PORT_Init();

	// DDRD = 255;
	// PORTD = 0;

	// EEPROM_init(I2C_CL_100KHz);

	// I2C_Master_Start();

	// I2C_Write(1 << 1, I2C_ACK);

	// //I2C_Master_Start();

	// I2C_Write(1, I2C_ACK);
	// //I2C_Master_Write(0);

	// // _delay_ms(10);

	// I2C_Write(2, I2C_ACK);

	// I2C_Master_Stop();

	// I2C_Master_Start();

	// I2C_Write(1 << 1 | 1, I2C_ACK);

	// PORTD = I2C_Read(I2C_NACK);

	// I2C_Master_Stop();
	// reset_port();
	// HOLD_on();
	// OE_on();
	// MR_on();
	// // write_port(0xffffff);
	// _delay_loop_1(5);
	
	
	// sei();

	// OE_off();
	// populateROM16bit();
	// PORT_Deactivate();
	// HOLD_off();
	// PORT_Deactivate();
	// READY_on();
	// populateROM();

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
