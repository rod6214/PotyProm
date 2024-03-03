#include "i2c.h"

__attribute__ ((weak)) void ERROR() {}
static void I2C_Init(uint8_t clock);


void I2C_Master_Init(uint8_t clock)
{
	I2C_Init(clock);
}

void I2C_Slave_Init(uint8_t clock, uint8_t address)
{
	// DDRC = 0;
	// PORTC = 0;
	// DDRC &= ~(1 << SDA_PORT) & ~(1 << SCL_PORT);
   	// PORTC |= (1 << SDA_PORT) | (1 << SCL_PORT);
	// I2C_Init(clock);
    I2C_SetSlaveAddress(address);
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);;
}

static void I2C_Init(uint8_t clock) 
{
    DDRC &= ~(1 << SDA_PORT) & ~(1 << SCL_PORT);
   	PORTC |= (1 << SDA_PORT) | (1 << SCL_PORT);
	TWBR = clock;
	TWSR &= ~(1 << TWPS1);
	TWSR &= ~(1 << TWPS0);
}

void I2C_Master_Wait()
{
  	while (!(TWCR & (1 << TWINT)));
}

void I2C_Master_Start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	I2C_Master_Wait();
}

void I2C_Write(unsigned char data, int ack)
{
	TWDR = data;
	if (ack) {
        TWCR = (1 << TWINT) | (1 << TWEN)|(1<<TWEA);
    }
    else {
        TWCR = (1 << TWEN)|(1<<TWINT);
    }
	I2C_Master_Wait();
}

unsigned char I2C_Read(int ack)
{
    if (ack) {
	    TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    }
    else 
    {
        TWCR=(1<<TWEN)|(1<<TWINT);
    }
	I2C_Master_Wait();
  	return TWDR; // Return The Received Byte
}

void I2C_Master_Stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while(TWCR&(1<<TWSTO));
}
