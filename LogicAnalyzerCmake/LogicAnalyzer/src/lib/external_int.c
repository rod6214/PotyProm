/*
 * external_int.c
 *
 * Created: 5/17/2022 7:29:03 PM
 *  Author: Nelson
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "external_int.h"

void enable_int4() 
{
    EIMSK |= (1 << INT4);
}

void disable_int4() 
{
    EIMSK &= ~(1 << INT4);
}

int is_int4_flag() 
{
    return (EIFR & (1 << INTF4)) == (1 << INTF4);
}

void clear_int4_flag() 
{
    EIFR &= ~(1 << INTF4);
}

void sense_on_low_level_int4()
{
    EICRB &= ~((1 << ISC41) | (1 << ISC40));
}

void sense_on_any_change_int4()
{
    sense_on_low_level_int4();
    EICRB |= (1 << ISC40);
}

void sense_on_falling_edge_int4()
{
    sense_on_low_level_int4();
    EICRB |= (1 << ISC41);
}

void sense_on_rising_edge_int4()
{
    sense_on_low_level_int4();
    EICRB |= (1 << ISC40) | (1 << ISC41);
}

void enable_int5() 
{
    EIMSK |= (1 << INT5);
}

void disable_int5() 
{
    EIMSK &= ~(1 << INT5);
}

int is_int5_flag() 
{
    return (EIFR & (1 << INTF5)) == (1 << INTF5);
}

void clear_int5_flag() 
{
    EIFR &= ~(1 << INTF5);
}

void sense_on_low_level_int5()
{
    EICRB &= ~((1 << ISC50) | (1 << ISC51));
}

void sense_on_any_change_int5()
{
    sense_on_low_level_int5();
    EICRB |= (1 << ISC50);
}

void sense_on_falling_edge_int5()
{
    sense_on_low_level_int5();
    EICRB |= (1 << ISC51);
}

void sense_on_rising_edge_int5()
{
    sense_on_low_level_int5();
    EICRB |= (1 << ISC50) | (1 << ISC51);
}
