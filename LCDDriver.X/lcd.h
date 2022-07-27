/* 
 * File:   lcd.h
 * Author: Nelson
 *
 * Created on July 10, 2022, 2:39 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * pserial.h
 *
 * Created: 1/8/2020 12:27:04 AM
 *  Author: rod62
 */ 


#ifndef PSERIAL_H_
#define PSERIAL_H_

#ifndef F_CPU
// #define F_CPU 12000000UL
#endif
// #define F_CPU 1000000UL
//#include <avr/io.h>
// #include <Arduino.h>
#include <xc.h>
#define GRAPHIC_ADDR_COMMAND 128
#define FUNCTION_SET_COMMAND(x, y, z) (32 | (x << 4) | (y << 2) | (z << 1))

#define BITS_8 1
#define BITS_4 0
#define EXTENDED 1
#define GDISPLAY 1
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#define _PARALLEL_ false
#define _SERIAL_ true

#define CS_PIN _PORTB_RB5_POSITION // Chip select signal
#define DATA_PIN _PORTB_RB4_POSITION //  Data signal
#define CLK_PIN _PORTB_RB3_POSITION // Clock signal
#define PSB_PIN _PORTB_RB2_POSITION // 1: Parallel bus mode, 0: Serial mode
#define LCD_RESET_PIN _PORTB_RB1_POSITION // Reset all the screen
#define LCD_RS 1
#define LCD_RW 2
#define LCD_READ (LCD_RW | LCD_RS)
#define LCD_WRITE (LCD_RS)
#define LCD_COMMAND 0
#define LCD_SERIAL_MODE 1
#define LCD_RESET 78
#define DISPLAY_ON 12
//#define DISPLAY_OFF 8
#define SET_EIGHT_BIT 32
#define SET_ADDRESS 32
//#define SHOW_CURSOR 2
#define RETURN_HOME 2
//#define SHOW_BLINK 1
#define CLEAR_DISPLAY 65
#define C_EON 4
#define C_RS 1
#define C_CLEAR 0
#define ISOLATE_ALL 4095
#define X_LIM 15
#define Y_LIM ISOLATE_ALL
#define set_Vertical(x) (GRAPHIC_ADDR_COMMAND | (127 & x))
#define set_Horizontal(x) (GRAPHIC_ADDR_COMMAND | (X_LIM & x))

extern char lcdBuffer[];
extern int pointer;
extern int starting_sequence;
extern int execute_proc;
extern int bytes;
extern char command;
extern char _buffer[];
char dataToSerial(int16_t numberH, int16_t numberL);
void writeCommand(char command, char instruction);
void consoleWriteCommand(char command, char instruction);
void LCDGraphicsInit(int16_t serialMode);
void LCDConsoleInit(int16_t serialMode);
void clearGraphicsLCD(void);
void reset_lcd();
void chip_select(int16_t value);
void LCD_clearDisplay();
void setAddress(char address);
void dataToSerial16(int16_t command, int16_t numberH, int16_t numberL);
void writeCommand16(char command, int data);

#endif /* PSERIAL_H_ */


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

