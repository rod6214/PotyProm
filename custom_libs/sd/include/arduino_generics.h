#ifndef __PORTS_H__
#define __PORTS_H__
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
// #define DORD 5
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define interrupts() sei()
#define noInterrupts() cli()
#define LSBFIRST 0
#define MSBFIRST 1
#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C
typedef bool boolean;
typedef uint8_t byte;

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
unsigned long millis(void);

#endif /* End __PORTS_H__*/