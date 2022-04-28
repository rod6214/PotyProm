/*
 * io_handle.h
 *
 * Created: 4/25/2022 9:53:41 PM
 *  Author: Nelson
 */ 


#ifndef IO_HANDLE_H_
#define IO_HANDLE_H_

#define F_CPU 16E6
#include <util/delay.h>

#define LOW_BYTE(x) (0xFF & x)
#define HIGH_BYTE(x) ((0xFF00 & x) >> 8)
#define SET_WORD_LOW(x, y) (x = 0x00FF & y)
#define SET_WORD_HIGH(x, y) (x = 0x0FF00 | (y << 8))
#define READ_MEMORY 0x0A
#define WRITE_MEMORY 0x0B
#define ACK 0x0C
#define NULL 0
#define COMMAND_STEP 1
#define LOW_BYTE_STEP 2
#define HIGH_BYTE_STEP 3
#define DATA_STEP 4
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
extern void set_address_low_as_highZ();
extern void set_address_high_as_highZ();
extern void set_port_data_as_highZ();
extern void set_address_low(char addressL);
extern void set_address_high(char addressH);
extern void set_data(char data);
extern char get_data();
extern void ctrl_chip_enable(int value);
extern void ctrl_output_enable(int value);
extern void ctrl_write_enable(int value);
extern void ctrl_low();
extern void ctrl_high();
extern void ctrl_init();
#endif /* IO_HANDLE_H_ */