/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "io_uart.h"
#include "ext_eeprom_mem.h"

#include <SPI.h>
#include <SD.h>
#include <utility/SdFat.h>
#include <ports.h>

File myFile;

void loop() 
{
}

void config() 
{
	myFile = SD.open("test.txt", FILE_WRITE);

	if (myFile != NULL) {
		myFile.close();
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

