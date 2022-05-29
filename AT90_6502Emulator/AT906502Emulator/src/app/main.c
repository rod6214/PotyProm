/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>

char ACUM;
char IR;

void config()
{
  PORTB = 0;
  PORTA = 0;
  PORTC = 0;
  DDRA = 255;
  DDRC = 255;
  DDRB = 0;
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

