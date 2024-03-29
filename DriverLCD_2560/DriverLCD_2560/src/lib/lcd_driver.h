/*
 * lcd_driver.h
 *
 * Created: 7/27/2022 2:44:44 PM
 *  Author: Nelson
 */ 


#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef PSERIAL_H_
#define PSERIAL_H_


// #define F_CPU 1000000UL
#include <avr/io.h>
// #include <Arduino.h>
// #include <xc.h>
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

#define PORT_CONTROL PORTF
#define TRIS_CONTROL DDRF

#define CS_PIN PF0 // Chip select signal
#define DATA_PIN PF1 //  Data signal
#define CLK_PIN PF2 // Clock signal
#define PSB_PIN PF3 // 1: Parallel bus mode, 0: Serial mode
#define LCD_RESET_PIN PF4 // Reset all the screen
#define INT_RESET_PIN PF5 // Reset all the screen
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

extern int pointer;
extern int starting_sequence;
extern int execute_proc;
extern int bytes;
extern char command;
extern char _buffer[];
extern char dataToSerial(int16_t numberH, int16_t numberL);
extern void writeCommand(char command, char instruction);
extern void consoleWriteCommand(char command, char instruction);
extern void LCDGraphicsInit(int16_t serialMode);
extern void LCDConsoleInit(int16_t serialMode);
extern void clearGraphicsLCD(void);
extern void reset_lcd();
extern void chip_select(int16_t value);
extern void LCD_clearDisplay();
extern void setAddress(char address);
extern void dataToSerial16(int16_t command, int16_t numberH, int16_t numberL);
extern void writeCommand16(char command, int data);
extern void resetFlag();

#endif /* PSERIAL_H_ */


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */