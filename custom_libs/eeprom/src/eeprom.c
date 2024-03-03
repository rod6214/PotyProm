#include <i2c.h>
#include <i2cext.h>
#include <util/twi.h>
#include <stdlib.h>
#include <util/delay.h>
#include <i2cext.h>
#ifdef __EEPROM_ADDON__
#endif
#include <595_driver.h>
#include "eeprom.h"

// Use below only for testing cases
// #ifndef __EEPROM_ADDON__
// #define __EEPROM_ADDON__
// #endif

#ifdef __EEPROM_ADDON__
#define send_to_slave(value, cmd) { \
				uint8_t dt[1]; \
				dt[0] = (uint8_t)value; \
				((Command_t*)cmd)->bytes = 1; \
				((Command_t*)cmd)->address = 1; \
				((Command_t*)cmd)->data = dt; \
				((Command_t*)cmd)->data_distance = 50; \
				((Command_t*)cmd)->command = WRITE_EXT_MEMORY; \
				if (I2C_Send_Command(*cmd)) \
				{ \
					PORTB |= (1 << PORT0); \
				}}
#define enable_d_buffer(cmd) { \
				uint8_t dt[1]; \
				dt[0] = 0; \
				((Command_t*)cmd)->bytes = 1; \
				((Command_t*)cmd)->address = 1; \
				((Command_t*)cmd)->data = dt; \
				((Command_t*)cmd)->data_distance = 50; \
				((Command_t*)cmd)->command = ENABLE_DATA_BUFFER; \
				if (I2C_Send_Command(*cmd)) \
				{ \
					PORTB |= (1 << PORT0); \
				}}
#define disabled_d_buffer(cmd) { \
				uint8_t dt[1]; \
				dt[0] = 0; \
				((Command_t*)cmd)->bytes = 1; \
				((Command_t*)cmd)->address = 1; \
				((Command_t*)cmd)->data = dt; \
				((Command_t*)cmd)->data_distance = 50; \
				((Command_t*)cmd)->command = DISABLED_DATA_BUFFER; \
				if (I2C_Send_Command(*cmd)) \
				{ \
					PORTB |= (1 << PORT0); \
				}}
#endif
__attribute__ ((weak)) void ERROR() {}

void EEPROM_init(uint8_t clock) 
{
    I2C_Master_Init(clock);
}

unsigned char EEPROM_Read(unsigned int add, unsigned char device)
{
  unsigned char Data;
  I2C_Master_Start();
  if (I2C_GetStatus() != START_TRANSMITTED) {
    #ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  // I2C Master Start
  I2C_Write((uint8_t)(EEPROM_Address_W | (device << 1)), I2C_ACK);
  if (I2C_GetStatus() != MT_SLA_W_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  I2C_Write(add>>8, I2C_ACK);
  if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  I2C_Write((unsigned char)add, I2C_ACK);
  if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}

  // I2C Master Repeated Start
  I2C_Master_Start();
  if (I2C_GetStatus() != REPEATED_TRANSMITTED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}

  I2C_Write((uint8_t)(EEPROM_Address_R | (device << 1)), I2C_ACK);
  if (I2C_GetStatus() != MR_SLA_R_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}

  Data = I2C_Read(I2C_NACK);
  
  if (I2C_GetStatus() != MR_DATA_NACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}

  I2C_Master_Stop();
  
  return Data;
}

void EEPROM_Write(unsigned int add, unsigned char data, unsigned char device)
{
  I2C_Master_Start();

	if (TW_STATUS != TW_START) 
	{
		#ifdef __I2C_LOG_ERROR__
			ERROR();
			return;
		#endif
	}
  	// I2C Master Start
	I2C_Write((uint8_t)(TW_WRITE | 0xA0 | (device << 1)), I2C_ACK);
	if (TW_STATUS != TW_MT_SLA_ACK) 
	{
		#ifdef __I2C_LOG_ERROR__
		ERROR();
		return;
		#endif
	}

	I2C_Write(add>>8, I2C_ACK);
	if (TW_STATUS != TW_MT_DATA_ACK) 
	{
		#ifdef __I2C_LOG_ERROR__
		ERROR();
		return;
		#endif
	}
	I2C_Write((unsigned char)add, I2C_ACK);
	if (TW_STATUS != TW_MT_DATA_ACK) 
	{
		#ifdef __I2C_LOG_ERROR__
		ERROR();
		return;
		#endif
	}
	I2C_Write(data, I2C_ACK);
	if (TW_STATUS != TW_MT_DATA_ACK) 
	{
		#ifdef __I2C_LOG_ERROR__
		ERROR();
		return;
		#endif
	}
	I2C_Master_Stop();
}

void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len, unsigned char device)
{
  I2C_Master_Start();
  if (I2C_GetStatus() != START_TRANSMITTED) {
    #ifdef __I2C_LOG_ERROR__
    ERROR();
    #endif
  }
  // I2C Master Start
  I2C_Write((uint8_t)(EEPROM_Address_W | (device << 1)), I2C_ACK);
 
  I2C_Write(add>>8, I2C_ACK);
  if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  I2C_Write((unsigned char)add, I2C_ACK);
  if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  for(unsigned int i=0; i<len; i++) {
    I2C_Write(data[i], I2C_ACK);
    if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
      #ifdef __I2C_LOG_ERROR__
      ERROR();
      #endif
    }
  }
  
  I2C_Master_Stop();
}

void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len, unsigned char device)
{
  I2C_Master_Start();
  if (I2C_GetStatus() != START_TRANSMITTED) {
    #ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
 
  // I2C Master Start
  I2C_Write(EEPROM_Address_W, I2C_ACK);
  if (I2C_GetStatus() != MT_SLA_W_ACK_RECEIVED) {
    #ifdef __I2C_LOG_ERROR__
    ERROR();
    #endif
  }
  I2C_Write(add>>8, I2C_ACK);
  if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  I2C_Write((unsigned char)add, I2C_ACK);
  if (I2C_GetStatus() != MT_DATA_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}

  // I2C Master Repeated Start
  I2C_Master_Start();
  if (I2C_GetStatus() != REPEATED_TRANSMITTED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}

  I2C_Write((uint8_t)(EEPROM_Address_R | (device << 1)), I2C_ACK);
  if (I2C_GetStatus() != MR_SLA_R_ACK_RECEIVED) {
		#ifdef __I2C_LOG_ERROR__
		ERROR();
    #endif
	}
  for(unsigned int i=0; i<len; i++)
  {
    if (i < len - 1) {
      data[i] = I2C_Read(I2C_ACK);
      if (I2C_GetStatus() != MR_DATA_ACK_RECEIVED) {
        #ifdef __I2C_LOG_ERROR__
        ERROR();
        #endif
      }
    }
    else {
      data[i] = I2C_Read(I2C_NACK);
      if (I2C_GetStatus() != MR_DATA_NACK_RECEIVED) {
        #ifdef __I2C_LOG_ERROR__
        ERROR();
        #endif
      }
    }
  }
  I2C_Master_Stop();
}

#ifdef __EEPROM_ADDON__
void populateROM16bit(uint32_t bits) {
	const size_t MAX_PROC_SIZE = 1024;
	unsigned char buffer[MAX_PROC_SIZE];
	Command_t cmd;
	R_on();
	DEN_on();
	RD_on();
	WR_off();
	for (int i = 0, k = 0; i < 8; i++) {
		EEPROM_Read_Page(k, buffer, MAX_PROC_SIZE, 0);
		for (int j = 0; j < MAX_PROC_SIZE; j++, k++) {
			uint32_t addr = ((k & 1) == 1)? (k & 0xfffff) : (k | 0x100000);
			int value = (k & 1)? (buffer[j] << 8) : buffer[j];
			// Map from top of memory "0xFE000" due to length of 8192 bytes
			if (k >= 0x400)
				addr+=0xFE000;
			// Set address memory
			if (bits == L595_BUS_LENGTH_SHORT) 
			{
				disabled_d_buffer(&cmd);
				OE_off();
			}
			write_port(addr, bits);
			ALE_on();
			ALE_off();
			DEN_off();
			if (bits == L595_BUS_LENGTH_NORMAL) 
			{
				// Set data memory
				write_port(value, L595_BUS_LENGTH_NORMAL);
			}
			else 
			{
				OE_on();
				enable_d_buffer(&cmd);
				send_to_slave(value, &cmd);
			}
			WR_off();
			_delay_loop_1(20);
			WR_on();
			DEN_on();
		}
	}
}

void populateROM(int bits) {
	const size_t MAX_PROC_SIZE = 1024;
	unsigned char buffer[MAX_PROC_SIZE];
	Command_t cmd;
	R_on();
	DEN_on();
	RD_on();
	WR_off();
	for (int i = 0, k = 0; i < 8; i++) {
		EEPROM_Read_Page(k, buffer, MAX_PROC_SIZE, 0);
		for (int j = 0; j < MAX_PROC_SIZE; j++, k++) {
			// Set address memory
			uint32_t addr = k;
			if (k >= 0x400)
				addr+=0xFE000;
			if (bits == L595_BUS_LENGTH_SHORT) 
			{
				disabled_d_buffer(&cmd);
				OE_off();
			}
			write_port(addr, bits);
			ALE_on();
			ALE_off();
			DEN_off();
			if (bits == L595_BUS_LENGTH_NORMAL) 
			{
				// Set data memory
				write_port(buffer[j], L595_BUS_LENGTH_NORMAL);
				
			}
			else 
			{
				OE_on();
				enable_d_buffer(&cmd);
				send_to_slave(buffer[j], &cmd);
			}
			WR_off();
			WR_on();
			DEN_on();
		}
	}
}
#endif
