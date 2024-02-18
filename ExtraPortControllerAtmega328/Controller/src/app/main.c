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
#include <eeprom.h>
#include "shifter/595_driver.h"
#include <i2c.h>
#include <i2cext.h>
#include <util/twi.h>

void populateROM16bit(void);
void populateROM();
static uint8_t data[512];
int i = 0;

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
	// test();
	sei();
}

void TWI_Receiv_irq(uint8_t value, size_t bytes, int id) 
{
	data[id] = value;
	// PORTD++;
}

void TWI_Transmit_irq(volatile uint8_t * pdata, uint8_t command, size_t bytes) 
{
	*pdata = 0x12;
	// PORTD = bytes;
}

void config()
{
	DDRD = 255;
	PORTD = 0;
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
	// SREG |= (1 << SREG_I);
	I2C_Slave_Init(I2C_CL_100KHz, 1);
	//I2C_InterruptEnable();
	// TWCR |= (1 << TWIE);
	// I2C_Slave_Read_Byte();
	// _delay_ms(10);

	// I2C_Read(I2C_ACK);
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

void populateROM16bit() {
	const size_t MAX_PROC_SIZE = 1024;
	unsigned char buffer[MAX_PROC_SIZE];
	R_on();
	DEN_on();
	RD_on();
	WR_off();

	for (int i = 0, k = 0; i < 8; i++) {
		EEPROM_Read_Page(k, buffer, MAX_PROC_SIZE, 0);
		for (int j = 0; j < MAX_PROC_SIZE; j++, k++) {
			uint32_t addr = ((k & 1) == 1)? (k & 0xfffff) : (k | 0x100000);
			int value = (k & 1)? (buffer[j] << 8) : buffer[j];
			// Map from top of memory "0xFE000" due to length of 8192 bytes
			if (k >= 0x400)
				addr+=0xFE000;
			// Set address memory
			write_port(addr);
			ALE_on();
			ALE_off();
			DEN_off();
			// Set data memory
			write_port(value);
			WR_off();
			_delay_loop_1(20);
			WR_on();
			DEN_on();
		}
	}
}

void populateROM() {
	const size_t MAX_PROC_SIZE = 1024;
	unsigned char buffer[MAX_PROC_SIZE];
	R_on();
	DEN_on();
	RD_on();
	WR_off();
	for (int i = 0, k = 0; i < 8; i++) {
		EEPROM_Read_Page(k, buffer, MAX_PROC_SIZE, 0);
		for (int j = 0; j < MAX_PROC_SIZE; j++, k++) {
			// Set address memory
			uint32_t addr = k;
			if (k >= 0x400)
				addr+=0xFE000;
			write_port(addr);
			ALE_on();
			ALE_off();
			DEN_off();
			// Set data memory
			write_port(buffer[j]);
			WR_off();
			WR_on();
			DEN_on();
		}
	}
}
