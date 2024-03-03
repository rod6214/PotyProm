#include <avr/io.h>


#define SDA_PORT PC4
#define SCL_PORT PC5
#define START_TRANSMITTED 0x08
#define REPEATED_TRANSMITTED 0x10
#define MT_SLA_W_ACK_RECEIVED 0x18
#define MT_SLA_W_NACK_RECEIVED 0x20
#define MT_DATA_ACK_RECEIVED 0x28
#define MT_DATA_NACK_RECEIVED 0x30
#define DATA_LOST 0x38
#define MR_SLA_R_ACK_RECEIVED 0x40
#define MR_SLA_R_NACK_RECEIVED 0x48
#define MR_DATA_ACK_RECEIVED 0x50
#define MR_DATA_NACK_RECEIVED 0x58
#define SR_SLA_W_ACK_RECEIVED 0x60 
#define SR_DATA_ACK_RECEIVED 0x80 
#define ST_DATA_ACK_RECEIVED 0xA8
#define I2C_ACK 1
#define I2C_NACK 0
#define I2C_GetStatus() (TWSR & 0xf8)
#define I2C_SetSlaveAddress(x) (TWAR = (x << 1))
#define I2C_GetSLA(x) (x << 1)
#define I2C_InterruptEnable() (TWCR |= (1 << TWIE))
#define I2C_InterruptDisable() (TWCR &=~(1 << TWIE))
#define I2C_ClearFlag() (TWCR &=~(1 << TWINT))

#if (FOSC==16000)
    #define I2C_CL_100KHz 
#elif (FOSC==12000)
    #define I2C_CL_100KHz 13 
#endif

void I2C_Master_Init(uint8_t clock);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_Slave_Init(uint8_t clock, uint8_t address);
void I2C_Write(unsigned char data, int ack);
unsigned char I2C_Read(int ack);
