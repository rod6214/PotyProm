#include "i2c.h"
// #include "../usb/conf/config.h"
#define BITRATE(TWSR)	((16000000/100000)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
void ERROR() {}

void I2C_Master_Init()
{
	DDRD &= ~(1 << SDA_PORT) & ~(1 << SCL_PORT);
   	PORTD |= (1 << SDA_PORT) | (1 << SCL_PORT);
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
	TWCR = (1 << TWINT) | (1 << TWEN);
	I2C_Master_Wait();
	return 0;
}

unsigned char I2C_Read_Byte(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	I2C_Master_Wait();
  	return TWDR; // Return The Received Byte
}

void I2C_Master_Stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while(TWCR&(1<<TWSTO));
}
