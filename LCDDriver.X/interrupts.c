#define _XTAL_FREQ 48000000
#include <xc.h>
#include "global.h"
#include "lcd.h"
//#define CLEAR_DISPLAY 13
// #define INPUT_DATA 17

int pointer = 0;
int execute_proc = FALSE;
char lcdBuffer[16];
int starting_sequence = 0;
char _buffer[MAX_MEMORY + 5];
char start_tokens[] = {241, 33, 78, 91};
// char start_tokens[] = {01, 02, 03, 04};
int bytes;
char command;
#define PACKAGE_SIZE 3

void __interrupt(high_priority) high_isr(void)
{
    di();
    clearInt0F();
    _delay_loop_1(2);
    char bit3 = (PORTB & (1 << _PORTB_RB7_POSITION));
    char bit4 = (PORTA & (1 << _PORTA_RA0_POSITION));
	char bit5 = (PORTA & (1 << _PORTA_RA1_POSITION));
    
    char data = PORTC;
    
    if (bit3) {
        data |= (1 << _PORTB_RB3_POSITION);
    }
    
    if (bit4) {
        data |= (1 << _PORTB_RB4_POSITION);
    }
    
    if (bit5) {
        data |= (1 << _PORTB_RB5_POSITION);
    }
//    consoleWriteCommand(LCD_WRITE, 'T');
    if (starting_sequence > 3) 
	{
		_buffer[pointer] = data;
		pointer++;
        if (pointer == PACKAGE_SIZE) 
        {
            execute_proc = TRUE;
        }
	}
	else if (start_tokens[starting_sequence] == data) 
	{
		starting_sequence++;
	}
	else 
	{
		starting_sequence = 0;
	}
    
    
    
//    if (pointer == 0) {
//        LCD_clearDisplay();
//    }
    
//    consoleWriteCommand(LCD_WRITE, 'T');
    
//    if (pointer < 16) {
//        lcdBuffer[pointer] = data;
//        pointer++;
//    }
//    if (data & 17) {
//        PORTA |= (1 << _PORTA_RA2_POSITION);
//    } 
//
//    consoleWriteCommand(LCD_WRITE, data);
    
//    PORTA &= ~(1 << _PORTA_RA2_POSITION);
//	if ((data == CLEAR_DISPLAY)) {
//		LCD_clearDisplay();
//	}
//	else if ((data == INPUT_DATA) || (pointer > 0)) {
//		if (pointer == 1) {
//            PORTA &= ~(1 << _PORTA_RA2_POSITION);
//			consoleWriteCommand(LCD_WRITE, data);
//		}
//		pointer++;
//		if (pointer > 1) {
//			pointer = 0;
//		}
//        else {
//            PORTA |= (1 << _PORTA_RA2_POSITION);
//        }
//	}
    ei();
}

void __interrupt(low_priority) low_isr(void)
{
	// ;
}