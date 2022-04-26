/*
 * io_handle.h
 *
 * Created: 4/25/2022 9:53:41 PM
 *  Author: Nelson
 */ 


#ifndef IO_HANDLE_H_
#define IO_HANDLE_H_

#define LOW_BYTE(x) (0xFF & x)
#define HIGH_BYTE(x) ((0xFF00 & x) >> 8)
#define READ_MEMORY 0
#define WRITE_MEMORY 1
#define ACK 0x0A
#define COMMAND_STEP 0
#define LOW_BYTE_STEP 1
#define HIGH_BYTE_STEP 2
#define DATA_STEP 3
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
extern void set_portB_as_highZ();
extern void set_portC_as_highZ();
extern void set_portD_as_highZ();
extern void set_address_low(char addressL);
extern void set_address_high(char addressH);
extern void set_data(char data);
extern char get_data();
extern void ctrl_chip_enable(int value);
extern void ctrl_output_enable(int value);
extern void ctrl_write_enable(int value);
#endif /* IO_HANDLE_H_ */