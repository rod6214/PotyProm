/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(USART_TX_vect)
{
	cli();
	sei();
}

ISR(USART_RX_vect)
{
	cli();
	sei();
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

