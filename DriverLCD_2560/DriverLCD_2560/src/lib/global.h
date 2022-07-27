/*
 * global.h
 *
 * Created: 7/27/2022 2:44:44 PM
 *  Author: Nelson
 */ 

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif
#define MAX_MEMORY 64
#define eint0() (INTCONbits.INT0E=1)
#define dint0() (INTCONbits.INT0E=0)
#define clearInt0F() (INTCONbits.INT0F=0)
#define _delay_loop_1(x) for(char i = 0; i < x; i++) {\
asm("nop"); \
}

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */