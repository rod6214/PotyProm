#include <avr/io.h>


#define SH_PIN      PINB0
#define ST_PIN      PINB1
#define DS_PIN      PINB2
#define MR_PIN      PINB3
#define OE_PIN      PIND0
#define WR_PIN      PIND1
#define RD_PIN      PIND6
#define ALE_PIN     PINC0
#define DEN_PIN     PINC1
#define R_PIN       PINC2
#define HOLD_PIN    PIND7
#define HOLDA_PIN   PIND2
#define READY_PIN   PINC3

#define DS_on() (PORTB |= (1 << DS_PIN))
#define DS_off() (PORTB &= ~(1 << DS_PIN))
#define SH_on() (PORTB |= (1 << SH_PIN))
#define SH_off() (PORTB &= ~(1 << SH_PIN))
#define ST_on() (PORTB |= (1 << ST_PIN))
#define ST_off() (PORTB &= ~(1 << ST_PIN))
#define MR_on() (PORTB |= (1 << MR_PIN))
#define MR_off() (PORTB &= ~(1 << MR_PIN))

#define OE_on() (PORTD |= (1 << OE_PIN))
#define OE_off() (PORTD &= ~(1 << OE_PIN))
#define WR_on() (PORTD |= (1 << WR_PIN))
#define WR_off() (PORTD &= ~(1 << WR_PIN))
#define RD_on() (PORTD |= (1 << RD_PIN))
#define RD_off() (PORTD &= ~(1 << RD_PIN))
#define HOLD_on() (PORTD |= (1 << HOLD_PIN))
#define HOLD_off() (PORTD &= ~(1 << HOLD_PIN))

#define ALE_on() (PORTC |= (1 << ALE_PIN))
#define ALE_off() (PORTC &= ~(1 << ALE_PIN))
#define DEN_on() (PORTC |= (1 << DEN_PIN))
#define DEN_off() (PORTC &= ~(1 << DEN_PIN))
#define R_on() (PORTC |= (1 << R_PIN))
#define R_off() (PORTC &= ~(1 << R_PIN))
#define READY_on() (PORTC |= (1 << READY_PIN))
#define READY_off() (PORTC &= ~(1 << READY_PIN))

void PORT_Init();
uint8_t read_port(uint32_t address);
void write_port(uint32_t address);
void reset_port();
void PORT_Deactivate();
void CONTROL_Deactivate();
void CONTROL_Activate();