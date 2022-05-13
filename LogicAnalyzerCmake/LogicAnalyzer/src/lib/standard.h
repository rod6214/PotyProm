/*
 * standard.h
 *
 * Created: 5/10/2022 2:04:44 PM
 * Author: Nelson
 * Argentina
 */

#ifndef STANDARD_H_
#define STANDARD_H_
#define LOW_BYTE(x) (0xFF & x)
#define HIGH_BYTE(x) (x >> 8)
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
#endif /* STANDARD_H_ */