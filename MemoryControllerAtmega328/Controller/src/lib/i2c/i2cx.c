#include "i2c.h"

__attribute__ ((weak)) void ERROR() {}

void I2C_Master_Init()
{
	DDRC &= ~(1 << SDA_PORT) & ~(1 << SCL_PORT);
   	PORTC |= (1 << SDA_PORT) | (1 << SCL_PORT);
	TWBR = I2C_CL_100KHz;
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

unsigned char I2C_Master_Write(unsigned char data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN)|(1<<TWEA);
	I2C_Master_Wait();
	return 0;
}

unsigned char I2C_Read_Byte(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	I2C_Master_Wait();
  	return TWDR; // Return The Received Byte
}

unsigned char I2C_Read_Byte_With_ACK() 
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	I2C_Master_Wait();
  	return TWDR; // Return The Received Byte
}

void I2C_Master_Stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while(TWCR&(1<<TWSTO));
}
