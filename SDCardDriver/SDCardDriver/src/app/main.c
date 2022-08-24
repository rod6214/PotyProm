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

// pin definitions
#define DDR_SPI         DDRB
#define PORT_SPI        PORTB
#define CS              PINB2
#define MOSI            PINB3
#define MISO            PINB4
#define SCK             PINB5

// macros
#define CS_ENABLE()     PORT_SPI &= ~(1 << CS)
#define CS_DISABLE()    PORT_SPI |= (1 << CS)

uint8_t SPI_transfer(uint8_t data);
void SPI_init();
void SD_powerUpSeq();
void SD_command(uint8_t cmd, uint32_t arg, uint8_t crc);

void SPI_init()
{
    // set CS, MOSI and SCK to output
    DDR_SPI |= (1 << CS) | (1 << MOSI) | (1 << SCK);

    // enable pull up resistor in MISO
    DDR_SPI |= (1 << MISO);

    // enable SPI, set as master, and clock to fosc/128
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

uint8_t SPI_transfer(uint8_t data)
{
    // load data into register
    SPDR = data;

    // Wait for transmission complete
    while(!(SPSR & (1 << SPIF)));

    // return SPDR
    return SPDR;
}

void SD_command(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    // transmit command to sd card
    SPI_transfer(cmd|0x40);

    // transmit argument
    SPI_transfer((uint8_t)(arg >> 24));
    SPI_transfer((uint8_t)(arg >> 16));
    SPI_transfer((uint8_t)(arg >> 8));
    SPI_transfer((uint8_t)(arg));

    // transmit crc
    SPI_transfer(crc|0x01);
}

void SD_powerUpSeq()
{
    // make sure card is deselected
    CS_DISABLE();

    // give SD card time to power up
    _delay_ms(1);

    // send 80 clock cycles to synchronize
    for(uint8_t i = 0; i < 10; i++)
        SPI_transfer(0xFF);

    // deselect SD card
    CS_DISABLE();
    SPI_transfer(0xFF);
}

void config()
{
}

void loop() 
{
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

