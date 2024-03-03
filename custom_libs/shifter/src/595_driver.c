#include <avr/io.h>
#include <util/delay.h>
#include "595_driver.h"

void PORT_Init() {
    PORTB &= ~(1 << SH_PIN) & ~(1 << ST_PIN) & ~(1 << DS_PIN) & ~(1 << MR_PIN) & ~(1 << OE_PIN); 
    DDRB |= (1 << SH_PIN) | (1 << ST_PIN) | (1 << DS_PIN) | (1 << MR_PIN);
    PORTC &= ~(1 << ALE_PIN) & ~(1 << R_PIN) & ~(1 << DEN_PIN);
    PORTD &= ~(1 << READY_PIN);
    DDRC |=  (1 << READY_PIN);
    PORTD |= (1 << OE_PIN) | (1 << WR_PIN) | (1 << RD_PIN);
    PORTD &= ~(1 << OE_PIN);
    DDRD |= (1 << OE_PIN) | (1 << HOLD_PIN);
    DDRD &= ~(1 << HOLDA_PIN);
}

void PORT_Deactivate() {
    OE_on();
    // DDRD &= ~(1 << WR_PIN) & ~(1 << RD_PIN);
    // DDRC &= ~(1 << R_PIN) & ~(1 << DEN_PIN);
    // PORTD &= ~(1 << WR_PIN) & ~(1 << RD_PIN);
    PORTC &= ~(1 << ALE_PIN) & ~(1 << R_PIN) & ~(1 << DEN_PIN);
}

void CONTROL_Deactivate() {
    DDRC &= ~(1 << ALE_PIN) & ~(1 << R_PIN) & ~(1 << DEN_PIN);
    DDRD &= ~(1 << WR_PIN) & ~(1 << RD_PIN);
}

void CONTROL_Activate() {
    DDRC |= (1 << ALE_PIN) | (1 << R_PIN) | (1 << DEN_PIN);
    DDRD |= (1 << WR_PIN) | (1 << RD_PIN);
}

void write_port(uint32_t value, uint32_t bits) {
    uint32_t queue = value;
    uint32_t sh = bits >= 24 ? 16777216 : 65536;
    for (int i = 0; i < bits; i++) {
        queue = queue << 1;
        if (queue & (sh)) {
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
