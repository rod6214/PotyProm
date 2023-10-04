/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "configs.h"



ISR(INT0_vect) {
	cli();
	sei();
}

ISR(INT1_vect) {
	cli();
	sei();
}

void config() {
	// Configuring INT0 as rising edge detection
	EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC10) | (1 << ISC11);
	// Enabling INT0 interrupt
	EIMSK |= (1 << INT0) | (1 << INT1);
	// Configuring default states
	Set_PortD_Ouputs();
	Set_PortD_Inputs();
	Set_PortB_Inputs();
	Set_DData_AsIn();
	Set_CData_AsIn();
	// Activate all interrupts
	sei();
}

int main(void)
{
	config();

    // /* Replace with your application code */
    while (1) 
    {
    }
}
