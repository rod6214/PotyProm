/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
// #define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SD.h"
// #include "CRC.h"
// #include "spi.h"
#include "sdcard.h"
// #include "FatStructs.h"

static uint8_t buf[512];
// static char buf2[5] = {'1', '2', '3', '4', '\0'};

void config()
{
    PORTD = 0;
    DDRD = 255;
    
    if (SD.begin((1<<SS))) 
    {
      File myfile = SD.open("hello.txt", FILE_READ);
      myfile.read(buf, 512);
      myfile.close();

      myfile = SD.open("another.txt", FILE_WRITE);
      myfile.println("Probando nuevo archivo con caracteres!!!");
      myfile.close();
    }

    // if (SDCARD_init(SPI_HALF_SPEED, (1<<SS))) 
    // {
    //     PORTD = 0x80;
    //     return;
    // }

    // if (SDCARD_waitStartBlock()) 
    // {
    //   PORTD = 0x82;
    //   return;
    // }

  // if (SDCARD_writeBlock(2, buf, 1)) 
  //   {
  //       // PORTD = 0x81;
  //       return;
  //   }
    // if (SDCARD_readBlock(0, buf)) 
    // {
    //     // PORTD = 0x81;
    //     return;
    // }
    // SPI_begin();
    // DDRD = 255;
    // _delay_loop_1(20);
    // PORTD = 0;
    // _delay_loop_1(20);
    // // array to hold responses
    // uint8_t res[5], buf[512], token;
    // uint32_t addr = 0x00000000;

    // // initialize UART
    // // UART_init();

    // // initialize SPI
    // SPI_init(SPI_MASTER | SPI_FOSC_128 | SPI_MODE_0);

    // // initialize sd card
    // if(SD_init() != SD_SUCCESS)
    // {
    //     PORTD = 0x80;
    //     // UART_pputs("Error initializaing SD CARD\r\n");
    // }
    // else
    // {
    //     // UART_pputs("SD Card initialized\r\n");

    //     // read sector 0
    //     // UART_pputs("\r\nReading sector: 0x");
    //     // UART_puthex8((uint8_t)(addr >> 24));
    //     // UART_puthex8((uint8_t)(addr >> 16));
    //     // UART_puthex8((uint8_t)(addr >> 8));
    //     // UART_puthex8((uint8_t)addr);
    //     res[0] = SD_readSingleBlock(addr, buf, &token);
    //     // UART_pputs("\r\nResponse:\r\n");
    //     // SD_printR1(res[0]);

    //     // if no error, print buffer
    //     if ((res[0] == 0x00) && (token == SD_START_TOKEN))
    //         PORTD = 1;
    //     // if((res[0] == 0x00) && (token == SD_START_TOKEN))
    //     //     SD_printBuf(buf);
    //     // else if error token received, print
    //     else if(!(token & 0xF0))
    //     {
    //         PORTD = 81;
    //         // UART_pputs("Error token:\r\n");
    //         // SD_printDataErrToken(token);
    //     }

    //     // update address to 0x00000100
    //     addr = 0x00000100;

    //     // fill buffer with 0x55
    //     for(uint16_t i = 0; i < 512; i++) buf[i] = 0x55;

    //     // UART_pputs("Writing 0x55 to sector: 0x");
    //     // UART_puthex8((uint8_t)(addr >> 24));
    //     // UART_puthex8((uint8_t)(addr >> 16));
    //     // UART_puthex8((uint8_t)(addr >> 8));
    //     // UART_puthex8((uint8_t)addr);

    //     // write data to sector
    //     res[0] = SD_writeSingleBlock(addr, buf, &token);

    //     // UART_pputs("\r\nResponse:\r\n");
    //     // SD_printR1(res[0]);

    //     // if no errors writing
    //     if(res[0] == 0x00)
    //     {
    //         if(token == SD_DATA_ACCEPTED)
    //             PORTD = 2;
    //             // UART_pputs("Write successful\r\n");
    //     }
    // }
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

