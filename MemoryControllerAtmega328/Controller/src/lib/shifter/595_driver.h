#include <avr/io.h>


#define SH_PIN      PINB0
#define ST_PIN      PINB1
#define DS_PIN      PINB2
#define MR_PIN      PINB3
#define OE_PIN      PINB4
#define WR_PIN      PINB5
#define RD_PIN      PINB6
#define ALE_PIN     PC0
#define DEN_PIN     PC1
#define R_PIN       PC2
#define DS_on() (PORTB |= (1 << DS_PIN))
#define DS_off() (PORTB &= ~(1 << DS_PIN))
#define SH_on() (PORTB |= (1 << SH_PIN))
#define SH_off() (PORTB &= ~(1 << SH_PIN))
#define ST_on() (PORTB |= (1 << ST_PIN))
#define ST_off() (PORTB &= ~(1 << ST_PIN))
#define MR_on() (PORTB |= (1 << MR_PIN))
#define MR_off() (PORTB &= ~(1 << MR_PIN))
#define OE_on() (PORTB |= (1 << OE_PIN))
#define OE_off() (PORTB &= ~(1 << OE_PIN))
#define WR_on() (PORTB |= (1 << WR_PIN))
#define WR_off() (PORTB &= ~(1 << WR_PIN))
#define RD_on() (PORTB |= (1 << RD_PIN))
#define RD_off() (PORTB &= ~(1 << RD_PIN))
#define ALE_on() (PORTB |= (1 << ALE_PIN))
#define ALE_off() (PORTB &= ~(1 << ALE_PIN))
#define DEN_on() (PORTB |= (1 << DEN_PIN))
#define DEN_off() (PORTB &= ~(1 << DEN_PIN))
#define R_on() (PORTB |= (1 << R_PIN))
#define R_off() (PORTB &= ~(1 << R_PIN))
#define Set_Data(x) (PORTD = x) 
#define Set_Data_As_Out() (DDRD = 255) 
#define Set_Data_As_In() (DDRD = 0) 

void PORT_Init();
uint8_t read_port(uint32_t address);
void write_port(uint32_t address, uint8_t data);
void reset_port();
void chip_select();