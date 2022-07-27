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

int execute_proc = FALSE;

void reset_lcd_sequence() 
{
    pointer = 0;
    starting_sequence = 0;
}

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
    INTCON2bits.INTEDG0 = 1;
    LCDConsoleInit(LCD_SERIAL_MODE);
    _delay(200);
//    setAddress(0);
//    consoleWriteCommand(LCD_WRITE, 'T');
    ei();
    eint0();
}

void loop() 
{
    if (!execute_proc) 
    {
        return;
    }

    command = _buffer[0];
    bytes = _buffer[1];

    int dataReceived = pointer - 2;
        
    if (dataReceived == bytes) 
    {
        // consoleWriteCommand(LCD_WRITE, 'H');

        // if (bytes == 78) 
        // {
        //     consoleWriteCommand(LCD_WRITE, '1');
        // }

        // if (command == 10) 
        // {
        //     consoleWriteCommand(LCD_WRITE, '2');
        // }
        switch(command) 
        {
            case LCD_WRITE:
            {
                for(int i = 0; i < bytes; i++) 
                {
                    consoleWriteCommand(LCD_WRITE, _buffer[i + 2]);
                }
            }
            break;
            case RETURN_HOME:
            {
                consoleWriteCommand(LCD_COMMAND, RETURN_HOME);
            }
            break;
            case CLEAR_DISPLAY:
            {
                consoleWriteCommand(LCD_COMMAND, CLEAR_DISPLAY);
            }
            break;
            case SET_ADDRESS:
            {
                consoleWriteCommand(LCD_COMMAND, SET_ADDRESS);
            }
            break;
            case DISPLAY_ON:
            {
                consoleWriteCommand(LCD_COMMAND, DISPLAY_ON);
            }
            break;
            case LCD_RESET:
            {
                reset_lcd();
            }
            break;
            default:
            {
                reset_lcd_sequence();
            }
            break;
        }
    }
//    if (pointer == 16) {
//        for (int i = 0; i < 16; i++) {
//            char data = lcdBuffer[i];
//            consoleWriteCommand(LCD_WRITE, data);
//        }
//        pointer = 0;
//        for (int i = 0; i < 16; i++) {
//            lcdBuffer[i] = 0;
//        }
//    }
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
