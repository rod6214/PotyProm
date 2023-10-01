#include <avr/io.h>
#include <avr/delay.h>
#include "595_driver.h"

void PORT_Init() {
    PORTB &= ~(1 << SH_PIN) | ~(1 << ST_PIN) | ~(1 << DS_PIN) | ~(1 << MR_PIN) | ~(1 << OE_PIN); 
    DDRB |= (1 << SH_PIN) | (1 << ST_PIN) | (1 << DS_PIN) | (1 << MR_PIN) | (1 << OE_PIN);
}

uint8_t read_port(uint32_t address) {
}

void write_port(uint32_t address, uint8_t data) {
    uint32_t queue = address;
    for (int i = 0; i < 24; i++) {
        queue = queue << 1;
        if (queue & (16777216)) {
            DS_on();
        }
        else {
            DS_off();
        }
        SH_on();
        SH_off();
    }
    ST_on();
    ST_off();
}

void reset_port() {
    MR_on();
    MR_off();
}
