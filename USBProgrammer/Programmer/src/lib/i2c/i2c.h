#include <avr/io.h>
#include "configs.h"


#define SDA_PORT PD1
#define SCL_PORT PD0
#define START_TRANSMITTED 0x08
#define REPEATED_TRANSMITTED 0x10
#define MT_SLA_W_ACK_RECEIVED 0x18
#define MT_SLA_W_NACK_RECEIVED 0x20
#define MT_DATA_ACK_RECEIVED 0x28
#define MT_DATA_NACK_RECEIVED 0x30
#define DATA_LOST 0x38
#define RT_SLA_R_ACK_RECEIVED 0x40
#define RT_SLA_R_NACK_RECEIVED 0x48
#define RT_DATA_ACK_RECEIVED 0x50
#define RT_DATA_NACK_RECEIVED 0x58

#if (FOSC==16000)
    #define I2C_CL_100KHz 18
#elif (FOSC==12000)
    #define I2C_CL_100KHz 13 
#endif

void I2C_Master_Init();
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char);
unsigned char I2C_Read_Byte(void);


