#ifndef __I2CEXT__H
#define __I2CEXT__H
#include <stdlib.h>

#define READ_EXT_MEMORY 0x56
#define GET_BUFFER 0x24
#define WRITE_EXT_MEMORY 0x42
#define ENABLE_DATA_BUFFER 0x45
#define DISABLED_DATA_BUFFER 0x46

typedef struct Command_H 
{
    int bytes;
    uint8_t* data;
    uint8_t address;
    uint16_t command;
    uint8_t data_distance;
} Command_t;

int I2C_Send_Command(Command_t command);
int I2C_Read_Command(Command_t command);
void TWI_vectorHandler(volatile uint8_t* pData, volatile uint8_t status);
void I2C_Register_Receiving_Callback(volatile void (*rec)(uint8_t data, uint16_t command, size_t bytes, int id));
void I2C_Register_Transmition_Callback(volatile void (*transmit)(volatile uint8_t * data, uint16_t command, size_t bytes));
#endif /*__I2CEXT__H */