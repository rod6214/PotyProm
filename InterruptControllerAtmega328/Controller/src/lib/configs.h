#include <avr/io.h>
#define FOSC 12000

#define READY_2_PIN	PIND0
#define INT_2_PIN	PIND1
#define INTA_2_PIN	PIND2
#define EX_INT_PIN	PIND3
#define Q0_PIN		PINC0
#define Q1_PIN		PINC1
#define Q2_PIN		PINC2
#define Q3_PIN		PINC3
#define Q4_PIN		PIND4
#define Q5_PIN		PIND5
#define Q6_PIN		PIND6
#define Q7_PIN		PIND7
#define IR0_PIN		PB0
#define IR1_PIN		PB1
#define IR2_PIN		PB2
#define IR3_PIN		PB3

#define Q0_on()   ((PORTC |= (1 << Q0_PIN)))
#define Q0_off()  ((PORTC &= ~(1 << Q0_PIN)))
#define Q1_on()   ((PORTC |= (1 << Q1_PIN)))
#define Q1_off()  ((PORTC &= ~(1 << Q1_PIN)))
#define Q2_on()   ((PORTC |= (1 << Q2_PIN)))
#define Q2_off()  ((PORTC &= ~(1 << Q2_PIN)))
#define Q3_on()   ((PORTC |= (1 << Q3_PIN)))
#define Q3_off()  ((PORTC &= ~(1 << Q3_PIN)))
#define Q4_on()   ((PORTD |= (1 << Q4_PIN)))
#define Q4_off()  ((PORTD &= ~(1 << Q4_PIN)))
#define Q5_on()   ((PORTD |= (1 << Q5_PIN)))
#define Q5_off()  ((PORTD &= ~(1 << Q5_PIN)))
#define Q6_on()   ((PORTD |= (1 << Q6_PIN)))
#define Q6_off()  ((PORTD &= ~(1 << Q6_PIN)))
#define Q7_on()   ((PORTD |= (1 << Q7_PIN)))
#define Q7_off()  ((PORTD &= ~(1 << Q7_PIN)))

#define READY_on()   ((PORTD |= (1 << READY_2_PIN)))
#define READY_off()  ((PORTD &= ~(1 << READY_2_PIN)))
#define INT_on()   ((PORTD |= (1 << INT_2_PIN)))
#define INT_off()  ((PORTD &= ~(1 << INT_2_PIN)))

#define Set_PortD_Ouputs()     (DDRD |= (1 << READY_2_PIN) | (1 << INT_2_PIN))
#define Set_PortD_Inputs()      (DDRD &= ~(1 << INTA_2_PIN) | ~(1 << EX_INT_PIN))
#define Set_PortB_Inputs()  (DDRD &= ~(1 << IR0_PIN) | ~(1 << IR1_PIN) | ~(1 << IR2_PIN) | ~(1 << IR3_PIN))
#define Set_DData_AsOut()  (DDRD |= (1 << Q4_PIN) | (1 << Q5_PIN) | (1 << Q6_PIN) | (1 << Q7_PIN))
#define Set_CData_AsOut()  (DDRC |= (1 << Q0_PIN) | (1 << Q1_PIN) | (1 << Q2_PIN) | (1 << Q3_PIN))
#define Set_DData_AsIn()  (DDRD &= ~(1 << Q4_PIN) | ~(1 << Q5_PIN) | ~(1 << Q6_PIN) | ~(1 << Q7_PIN))
#define Set_CData_AsIn()  (DDRC &= ~(1 << Q0_PIN) | ~(1 << Q1_PIN) | ~(1 << Q2_PIN) | ~(1 << Q3_PIN))
