#include "i2c/i2c.h"
#include "eeprom.h"

void CERROR();

void EEPROM_init() 
{
    I2C_Master_Init();
}

unsigned char EEPROM_Read(unsigned int add, unsigned char device)
{
  unsigned char Data;
  I2C_Master_Start();
  if ((TWSR & 0xf8) != START_TRANSMITTED) {
    #ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  // Wait Until EEPROM Is IDLE
  I2C_Master_Write((uint8_t)(EEPROM_Address_W | (device << 1)));
  if ((TWSR & 0xf8) != MT_SLA_W_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  I2C_Master_Write(add>>8);
  if ((TWSR & 0xf8) != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  I2C_Master_Write((unsigned char)add);
  if ((TWSR & 0xf8) != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}

  // I2C Master Repeated Start
  I2C_Master_Start();
  if ((TWSR & 0xf8) != REPEATED_TRANSMITTED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}

  I2C_Master_Write((uint8_t)(EEPROM_Address_R | (device << 1)));
  if ((TWSR & 0xf8) != RT_SLA_R_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}

  Data = I2C_Read_Byte();
  
  if ((TWSR & 0xf8) != RT_DATA_NACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}

  I2C_Master_Stop();
  
  return Data;
}

void EEPROM_Write(unsigned int add, unsigned char data, unsigned char device)
{
  I2C_Master_Start();
  if ((TWSR & 0xf8) != START_TRANSMITTED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  // Wait Until EEPROM Is IDLE
  I2C_Master_Write((uint8_t)(EEPROM_Address_W | (device << 1)));
  if ((TWSR & 0xf8) != MT_SLA_W_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}

  I2C_Master_Write(add>>8);
  if ((TWSR & 0xf8) != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  I2C_Master_Write((unsigned char)add);
  if ((TWSR & 0xf8) != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  I2C_Master_Write(data);
  if ((TWSR & 0xf8) != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		CERROR();
    #endif
	}
  I2C_Master_Stop();
}

void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len)
{
  // I2C_Master_Start();
 
  // // Wait Until EEPROM Is IDLE
  // I2C_Master_Write(EEPROM_Address_W);
 
  // I2C_Master_Write(add>>8);
  // I2C_Master_Write((unsigned char)add);
  // for(unsigned int i=0; i<len; i++)
  //   I2C_Master_Write(data[i]);
  
  // I2C_Master_Stop();
}

void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len)
{
//   I2C_Master_Start();
 
//   // Wait Until EEPROM Is IDLE
//   I2C_Master_Write(EEPROM_Address_W);
 
//   I2C_Master_Write(add>>8);
//   I2C_Master_Write((unsigned char)add);
// //   I2C_Master_RepeatedStart();
//   I2C_Master_Write(EEPROM_Address_R);
//   for(unsigned int i=0; i<len; i++)
//   {
//     data[i] = I2C_Read_Byte();
//     // I2C_ACK();
//   }
//   I2C_Master_Stop();
}