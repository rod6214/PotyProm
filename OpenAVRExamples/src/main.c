#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void config()
{
    PORTB = 0;
    DDRB = (1 << DD0);
}

void loop() 
{
    if (PORTB & (1 << PB0)) 
    {
        PORTB = 0;
    }
    else 
    {
        PORTB = 1;
    }
    _delay_ms(200);
}

int main() 
{
    config();
    while(1) 
    {
        loop();
    }
}