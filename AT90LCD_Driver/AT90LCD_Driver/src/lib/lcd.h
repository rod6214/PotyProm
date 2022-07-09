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
#include <avr/io.h>
// #include <Arduino.h>

#define GRAPHIC_ADDR_COMMAND 128
#define FUNCTION_SET_COMMAND(x, y, z) (32 | (x << 4) | (y << 2) | (z << 1))

#define BITS_8 1
#define BITS_4 0
#define EXTENDED 1
#define GDISPLAY 1

#define _PARALLEL_ false
#define _SERIAL_ true

#define CS_PIN PINB2 // Chip select signal
#define DATA_PIN PINB1 //  Data signal
#define CLK_PIN PINB0 // Clock signal
#define PSB_PIN PINB3 // 1: Parallel bus mode, 0: Serial mode
#define LCD_RESET_PIN PINB4 // Reset all the screen

// #define csPort(x) digitalWrite(CS_PIN, x)
// #define dataPort(x) digitalWrite(DATA_PIN, x)
// #define clkPort(x) digitalWrite(CLK_PIN, x)

#define DISPLAY_ON 12
#define DISPLAY_OFF 8
#define SHOW_CURSOR 2
#define SHOW_BLINK 1
#define C_EON 4
#define C_RS 1
#define C_CLEAR 0
#define ISOLATE_ALL 4095
#define X_LIM 15
#define Y_LIM ISOLATE_ALL
#define set_Vertical(x) (GRAPHIC_ADDR_COMMAND | (127 & x))
#define set_Horizontal(x) (GRAPHIC_ADDR_COMMAND | (X_LIM & x))

void dataToSerial(int numberH, int numberL);
void writeCommand(char control, char instruction);
void LCDInit (int serialMode);
void clearGraphicsLCD(void);
void reset_lcd();
void chip_select(int value);

#endif /* PSERIAL_H_ */