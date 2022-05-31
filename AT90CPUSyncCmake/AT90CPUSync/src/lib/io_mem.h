/*
 * io_mem.h
 *
 * Created: 5/1/2022 3:14:31 PM
 *  Author: Nelson
 */ 


#ifndef IO_MEM_H_
#define IO_MEM_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#define DEBUG_MODE 0x10
#define RUN_MODE 0x11
#define PROGRAM_MODE 0x12

#define LOW_BYTE(x) (0xff & x)
#define HIGH_BYTE(x) (x >> 8)
//#define SET_WORD_LOW(x, y) (x = 0x00FF & y)
//#define SET_WORD_HIGH(x, y) (x = 0x0FF00 | (y << 8))
#define READ_MEMORY 0x0A
#define WRITE_MEMORY 0x0B
#define ACK 0x0C
#define EXECUTE_PROC 0x0D
#define STORE_DATA 0x0E
#define FINISH_STORE_DATA 0x0F

#define NULL 0
#define COMMAND_STEP 1
#define LOW_BYTE_STEP 2
#define HIGH_BYTE_STEP 3
#define HIGH_OFFSET_STEP 4
#define LOW_OFFSET_STEP 5
#define DATA_STEP 6
#define WRITE_MEMORY_EXEC 7
#define USART_TX_vect _VECTOR(13)
#define USART_RX_vect _VECTOR(11)
#define MEM_ADDR_LOW_PORTC 7
#define MEM_ADDR_LOW_REGISTER 10

typedef struct _IO_MEM 
{
    int mode;
} IO_MEM_t;

extern void set_address_low(char addressl);
extern void set_address_high(char addressh);
extern void set_address_high_as_input();
extern void set_address_low_as_input();
extern void set_data_as_input();
extern void set_address_low_as_output();
extern void set_address_high_as_output();
extern void set_data_as_output();
extern void reset_ctrl();
extern void deactivate_ports();
extern char get_data();
extern void set_data(char data);
extern void init_ctrl_mem(int mode);
// extern void init_ctrl_mem();
extern void set_chip_enable(int value);
extern void set_output_enable(int value);
extern void set_write_enable(int value);

#endif /* IO_MEM_H_ */