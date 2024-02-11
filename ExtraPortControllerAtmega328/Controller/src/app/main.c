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
#include "eeprom/eeprom.h"
#include "shifter/595_driver.h"

void populateROM16bit(void);
void populateROM();

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

void config()
{
	// Configuring INT0 as rising edge detection
	EICRA |= (1 << ISC01) | (1 << ISC00);
	// Enabling INT0 interrupt
	EIMSK |= (1 << INT0);
	READY_on();
	_delay_ms(100);
	PORT_Init();
	EEPROM_init();
	reset_port();
	HOLD_on();
	OE_on();
	MR_on();
	// write_port(0xffffff);
	_delay_loop_1(5);
	
	
	sei();

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
