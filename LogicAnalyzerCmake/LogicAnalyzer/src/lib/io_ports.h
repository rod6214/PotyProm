/*
 * io_ports.h
 *
 * Created: 5/15/2022 7:29:03 PM
 *  Author: Nelson
 */
#ifndef IO_PORTS_H_
#define IO_PORTS_H_
extern void set_porta_direction(char pins);
extern void set_porta(char value);
extern void set_portc_direction(char pins);
extern void set_portc(char value);
extern void set_pin(volatile uint8_t* port, uint8_t pin);
extern void clear_pin(volatile uint8_t* port, uint8_t pin);
extern char read_registerA();
extern char read_registerC();
#endif /* IO_PORTS_H_*/