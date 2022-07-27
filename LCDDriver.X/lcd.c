/*
 * LcdUI.cpp
 *
 * Created: 1/8/2020 12:26:07 AM
 * Author : rod62
 */ 
#define _XTAL_FREQ 48000000
#include "global.h"
#include "lcd.h"

void initPorts(int16_t serialMode);

void initPorts(int16_t serialMode) {
    TRISB &= ~(1 << CS_PIN);
    TRISB &= ~(1 << CLK_PIN);
    TRISB &= ~(1 << DATA_PIN);
    TRISB &= ~(1 << LCD_RESET_PIN);
    TRISB &= ~(1 << PSB_PIN);

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

void LCDConsoleInit(int16_t serialMode) {
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
	consoleWriteCommand(LCD_COMMAND, RETURN_HOME);
	// Turn display on
	consoleWriteCommand(LCD_COMMAND, DISPLAY_ON);
	// Set eight bits mode
	consoleWriteCommand(LCD_COMMAND, SET_EIGHT_BIT);
}

void consoleWriteCommand(char control, char instruction) {
    writeCommand(control, instruction);
    __delay_us(200);
}

void LCD_clearDisplay() {
    writeCommand(LCD_COMMAND, 0x01);
    __delay_ms(2);
}

void LCDGraphicsInit(int16_t serialMode) {

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
	for(int16_t x = 0, y = 0; x < 8 * 64; x++) {
		int16_t Y = y % 32;
		int16_t X = ((y < 32) ? x % 8 : x % 8 + 8);
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

void setAddress(char address) {
    writeCommand(LCD_COMMAND, 128 | (127 & address));
    __delay_us(100);
}

void writeCommand(char _control, char instruction) {
	int16_t data = ((((int16_t)(0xF0 & instruction)) << 8) | ((0x0F & instruction) << 4));
	dataToSerial(((int16_t)(0xF8 | (_control << 1))), data);
//    dataToSerial16(((int16_t)(0xF8 | (_control << 1))), 0, data);
}

void writeCommand16(char command, int data) 
{
    char highPart = (char)(data >> 8);
    char lowPart = (char)(0xff & data);
    int16_t dataH = ((((int16_t)(0xF0 & highPart)) << 8) | ((0x0F & highPart) << 4));
    int16_t dataL = ((((int16_t)(0xF0 & lowPart)) << 8) | ((0x0F & lowPart) << 4));
//    dataToSerial16(((int16_t)(0xF8 | (command << 1))), dataH, dataL);
}

//void dataToSerial16(int16_t command, int16_t numberH, int16_t numberL) 
//{
//    int16_t counter = 0;
//
//    while(counter < 8) {
//        int16_t temp = (command & (1 << 7));
//        if (temp == (1 << 7)) {
//            PORTB |= (1 << DATA_PIN);
//        }
//        else {
//            PORTB &= ~(1 << DATA_PIN);
//        }
//
//        PORTB = PORTB | (1 << CLK_PIN);
//		__delay_us(5);
//        PORTB = PORTB & ~(1 << CLK_PIN);
//		__delay_us(5);
//		command = command << 1;
//		counter++;
//	}
//
//    counter = 0;
//    
//    while(counter < 16) {
//        int16_t temp = (numberH & (1 << 15));
//        if (temp == (1 << 15)) {
//            PORTB |= (1 << DATA_PIN);
//        }
//        else {
//            PORTB &= ~(1 << DATA_PIN);
//        }
//        PORTB = PORTB | (1 << CLK_PIN);
//		__delay_us(5);
//        PORTB = PORTB & ~(1 << CLK_PIN);
//		__delay_us(5);
//		numberH = numberH << 1;
//		counter++;
//	}
//    
//    counter = 0;
//    
//    while(counter < 16) {
//        int16_t temp = (numberL & (1 << 15));
//        if (temp == (1 << 15)) {
//            PORTB |= (1 << DATA_PIN);
//        }
//        else {
//            PORTB &= ~(1 << DATA_PIN);
//        }
//        PORTB = PORTB | (1 << CLK_PIN);
//		__delay_us(5);
//        PORTB = PORTB & ~(1 << CLK_PIN);
//		__delay_us(5);
//		numberL = numberL << 1;
//		counter++;
//	}
//}

char dataToSerial(int16_t numberH, int16_t numberL) {
	int16_t counter = 0;

    while(counter < 8) {
        int16_t temp = (numberH & (1 << 7));
        if (temp == (1 << 7)) {
            PORTB |= (1 << DATA_PIN);
        }
        else {
            PORTB &= ~(1 << DATA_PIN);
        }

        PORTB = PORTB | (1 << CLK_PIN);
		__delay_us(5);
        PORTB = PORTB & ~(1 << CLK_PIN);
		__delay_us(5);
		numberH = numberH << 1;
		counter++;
	}

    counter = 0;

//     if (numberH & 4) {
//         int inputData = 0;
//         DDRB &= ~(1 << DATA_PIN);
//         _delay_loop_1(50);
//         while(counter < 16) {
//             inputData = inputData >> 1;
//             PORTB |= (1 << CLK_PIN);
//             _delay_us(5);
//             PORTB &= ~(1 << CLK_PIN);
//             _delay_us(5);
//             if (PINB1) {
//                 inputData |= 128;
//             }
//             counter++;
//         }
//         DDRB |= (1 << DATA_PIN);
//         return ((char)(0xF000 & inputData) >> 8) | ((char)(0xF0 & inputData) >> 4);
//     }

	while(counter < 16) {
        int16_t temp = (numberL & (1 << 15));
        if (temp == (1 << 15)) {
            PORTB |= (1 << DATA_PIN);
        }
        else {
            PORTB &= ~(1 << DATA_PIN);
        }
        PORTB = PORTB | (1 << CLK_PIN);
		__delay_us(5);
        PORTB = PORTB & ~(1 << CLK_PIN);
		__delay_us(5);
		numberL = numberL << 1;
		counter++;
	}

    return 0;
}

void reset_lcd() {
    PORTB &= ~(1 << LCD_RESET_PIN);
    __delay_us(200);
    PORTB |= (1 << LCD_RESET_PIN);
    __delay_us(200);
}

void chip_select(int16_t value) {
    if (value) {
        PORTB |= (1 << CS_PIN);
    }
    else {
        PORTB &= ~(1 << CS_PIN);
    }
}

