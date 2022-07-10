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

static void initPorts(int serialMode);

static void initPorts(int serialMode) {
    DDRB |= (1 << CS_PIN);
    DDRB |= (1 << CLK_PIN);
    DDRB |= (1 << DATA_PIN);
    DDRB |= (1 << LCD_RESET_PIN);
    DDRB |= (1 << PSB_PIN);

    PORTB &= ~(1 << CS_PIN);
    PORTB &= ~(1 << CLK_PIN);
    PORTB &= ~(1 << DATA_PIN);
    if (serialMode & LCD_SERIAL_MODE)
    {
        PORTB &= ~(1 << PSB_PIN);
    }
    else
    {
        PORTB |= (1 << PSB_PIN);
    }
}

void LCDConsoleInit(int serialMode) {
    initPorts(serialMode);
    initPorts(serialMode);

	_delay_loop_1(50);

    // Activate LCD
    chip_select(1);

    // Reset LCD
    reset_lcd();
	
	// Clear and sync LCD
    LCD_clearDisplay();
	// consoleWriteCommand(LCD_COMMAND, 0x01);
	// Set pointer or reset AC (Address Counter)
	consoleWriteCommand(LCD_COMMAND, 2);
	// Turn display on
	consoleWriteCommand(LCD_COMMAND, 12);
	// Set eight bits mode
	consoleWriteCommand(LCD_COMMAND, 48);
}

void consoleWriteCommand(char control, char instruction) {
    writeCommand(control, instruction);
    _delay_us(200);
}

void LCD_clearDisplay() {
    writeCommand(LCD_COMMAND, 0x01);
    _delay_ms(2);
}

void LCDGraphicsInit(int serialMode) {

    initPorts(serialMode);

	_delay_loop_1(50);

    // Activate LCD
    chip_select(1);

    // Reset LCD
    reset_lcd();
	
	// Clear and sync LCD
    LCD_clearDisplay();
	// writeCommand(LCD_COMMAND, 0x01);
	// Set pointer or reset AC (Address Counter)
	writeCommand(LCD_COMMAND, 0x02);
	// Turn display on
	writeCommand(LCD_COMMAND, 0x08);
	// Set eight bits mode
	writeCommand(LCD_COMMAND, 0x30);
    // Set extended
    writeCommand(0x00, 0x34);
    // Set graphics mode
    writeCommand(0x00, 0x36);
	// if (serialMode) 
    // {
    //     // // Set extended
    //     writeCommand(0x00, 0x34);

    //     // // Set graphics mode
    //     writeCommand(0x00, 0x36);
        
    //     clearGraphicsLCD();
        
    //     // Set vertical
    //     writeCommand(0x00, 0x80 | 0);
    //     // Set horizontal
    //     writeCommand(0x00, 0x80 | 0);
    //     // Set data byte MSB
    //     writeCommand(0x01, 0xFF);
    //     // Set data byte LSB
    //     writeCommand(0x01, 0xFF);
    // }

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

void writeCommand(char control, char instruction) {
	int data = ((((int)(0xF0 & instruction)) << 8) | ((0x0F & instruction) << 4));
	dataToSerial(((int)(0xF8 | (control << 1))), data);
}

char dataToSerial(int numberH, int numberL) {
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

    // if (numberH & 4) {
    //     int inputData = 0;
    //     DDRB &= ~(1 << DATA_PIN);
    //     _delay_loop_1(50);
    //     while(counter < 16) {
    //         inputData = inputData >> 1;
    //         PORTB |= (1 << CLK_PIN);
    //         _delay_us(5);
    //         PORTB &= ~(1 << CLK_PIN);
    //         _delay_us(5);
    //         if (PINB1) {
    //             inputData |= 128;
    //         }
    //         counter++;
    //     }
    //     DDRB |= (1 << DATA_PIN);
    //     return ((char)(0xF000 & inputData) >> 8) | ((char)(0xF0 & inputData) >> 4);
    // }

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

    return 0;
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
