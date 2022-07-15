/*
 * File:   main.c
 * Author: Nelson
 *
 * Created on July 10, 2022, 1:46 PM
 */

#define _XTAL_FREQ 48000000
#include <xc.h>
#include "global.h"
#include "lcd.h"

void config() 
{
    ADCON1bits.PCFG = 15;
    UCONbits.USBEN = 0;
    PORTC = 0;
    TRISB = 255;
    TRISC = 255;
    TRISA = 255;
    PORTA &= ~(1 << _PORTA_RA2_POSITION);
    TRISA &= ~(1 << _PORTA_RA2_POSITION);
    INTCON2bits.INTEDG0 = 0;
    LCDConsoleInit(LCD_SERIAL_MODE);
//    consoleWriteCommand(LCD_WRITE, 'H');
    ei();
    eint0();
}

void loop() 
{
    if (pointer == 16) {
        for (int i = 0; i < 16; i++) {
            char data = lcdBuffer[i];
            consoleWriteCommand(LCD_WRITE, data);
        }
        pointer = 0;
        for (int i = 0; i < 16; i++) {
            lcdBuffer[i] = 0;
        }
    }
}

int main(void)
{
	config();
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}
