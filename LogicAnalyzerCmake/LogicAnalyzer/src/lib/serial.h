/*
 * serial.h
 *
 * Created: 5/14/2022 12:31:53 PM
 * Author : Nelson
 */ 
#ifndef SERIAL_H_
#define SERIAL_H_
#define READY 0xf1
#define IN_PROCESS 0xf2
#define PENDING 0xf3
#define NOT_STARTED 0xf4
#define READ_PROCESSOR 0x2f1
extern int serial_set_command(char byte);
extern int serial_get_command();
extern int serial_get_status();
extern void init_serial();
extern int serial_count();
extern char* serial_get_buffer();
extern void serial_send_response();
#endif /* SERIAL_H_ */
