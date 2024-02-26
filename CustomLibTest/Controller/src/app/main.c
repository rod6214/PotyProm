/*
 * CustomLibTest.c
 *
 * Created: 2/25/2024 12:31:53 PM
 * Author : Nelson
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/twi.h>
#include <spi.h>
#include <SD.h>

void ERROR() 
{
	PORTB = 1;
}

ISR(INT0_vect) {}

void config()
{
	PORTD = 0;
	DDRD = 255;
	spi_init();
	SD_init();
	// SPI_init(SPI_MASTER | SPI_FOSC_128 | SPI_MODE_0);
	// SPI_init(SPI_MASTER | SPI_FOSC_128 | SPI_MODE_0);
	// SPI_transfer(0x33);
	// PORTD = SPI_receive();
}


void loop() 
{
}

int main(void)
{
	config();
    // /* Replace with your application code */
    while (1) 
    {
		// loop();
    }
}
