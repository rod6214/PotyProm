/*
 * LcdUI.cpp
 *
 * Created: 1/8/2020 12:26:07 AM
 * Author : rod62
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


void LCDInit (int serialMode) {

    DDRB |= (1 << CS_PIN);
    DDRB |= (1 << CLK_PIN);
    DDRB |= (1 << DATA_PIN);
    DDRB |= (1 << LCD_RESET_PIN);
    DDRB |= (1 << PSB_PIN);

    PORTB &= ~(1 << CS_PIN);
    PORTB &= ~(1 << CLK_PIN);
    PORTB &= ~(1 << DATA_PIN);
    if (serialMode)
    {
        PORTB &= ~(1 << PSB_PIN);
    }
    else
    {
        PORTB |= (1 << PSB_PIN);
    }

	_delay_loop_1(50);

    // Activate LCD
    chip_select(1);

    // Reset LCD
    reset_lcd();
	
	// Clear and sync LCD
	writeCommand(0x00, 0x01);
	
	// Set pointer or reset AC (Address Counter)
	writeCommand(0x00, 0x02);
	
	// // Turn display on
	writeCommand(0x00, 0x08);
	
	// // Set eight bits mode
	writeCommand(0x00, 0x30);
	
	// // Set extended
	writeCommand(0x00, 0x34);

	// // Set graphics mode
	writeCommand(0x00, 0x36);
	
	clearGraphicsLCD();
	
	// Set vertical
	writeCommand(0x00, 0x80 | 0);
	// Set horizontal
	writeCommand(0x00, 0x80 | 0);
	// Set data byte MSB
	writeCommand(0x01, 0xFF);
	// Set data byte LSB
	writeCommand(0x01, 0xFF);

}

void clearGraphicsLCD() {
	for(int x = 0, y = 0; x < 8 * 64; x++) {
		int Y = y % 32;
		int X = ((y < 32) ? x % 8 : x % 8 + 8);
		// Set vertical
		writeCommand(0x00, 0x80 | ((char)Y));
		// Set horizontal
		writeCommand(0x00, 0x80 | ((char)X));
		// Set data byte MSB
		writeCommand(0x01, 0x00);
		// Set data byte LSB
		writeCommand(0x01, 0x00);
		if ((x + 1) % 8 == 0) {		
			y++;
		}
	}
}

void drawPointLCD() {}
	
void drawImageLCD() {}

void writeCommand(char control, char instruction) {
	int data = ((((int)(0xF0 & instruction)) << 8) | ((0x0F & instruction) << 4));
	dataToSerial(((int)(0xF8 | (control << 1))), data);
}

void dataToSerial(int numberH, int numberL) {
	int counter = 0;
    while(counter < 8) {
        int temp = (numberH & (1 << 7));
        if (temp == (1 << 7)) {
            PORTB |= (1 << DATA_PIN);
        }
        else {
            PORTB &= ~(1 << DATA_PIN);
        }
        PORTB = PORTB | (1 << CLK_PIN);
		_delay_us(5);
        PORTB = PORTB & ~(1 << CLK_PIN);
		_delay_us(5);
		numberH = numberH << 1;
		counter++;
	}

    counter = 0;

	while(counter < 16) {
        int temp = (numberL & (1 << 15));
        if (temp == (1 << 15)) {
            PORTB |= (1 << DATA_PIN);
        }
        else {
            PORTB &= ~(1 << DATA_PIN);
        }
        PORTB = PORTB | (1 << CLK_PIN);
		_delay_us(5);
        PORTB = PORTB & ~(1 << CLK_PIN);
		_delay_us(5);
		numberL = numberL << 1;
		counter++;
	}
}

void reset_lcd() {
    PORTB &= ~(1 << LCD_RESET_PIN);
    _delay_us(2);
    PORTB |= (1 << LCD_RESET_PIN);
    _delay_us(2);
}

void chip_select(int value) {
    if (value) {
        PORTB |= (1 << CS_PIN);
    }
    else {
        PORTB &= ~(1 << CS_PIN);
    }
}
