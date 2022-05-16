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
#define INVALID 0xf5
#define READ_STRING 0x2f1
#define READ_PROCESSOR 0x2f2
#define TURN_ON_PINC1 0x2f3
#define TURN_OFF_PINC1 0x2f4
#define RESET_PROCESSOR 0x2f5
#define ERROR 0x2ff
#define PIN_SCK 0
#define PIN_READY 1
#define PIN_RESET 2
extern int serial_process_input(char byte);
extern int serial_get_command();
extern int serial_get_status();
extern void init_serial();
extern int serial_count();
extern char* serial_get_buffer();
extern void serial_send_response();
extern void serial_send_data(const char* data, int bytes);
extern void reset_pointer();
extern int get_pointer_value();
extern void serial_set_command(int command);
extern void serial_set_bytes(int count);
#endif /* SERIAL_H_ */
