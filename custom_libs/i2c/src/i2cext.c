#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include "i2c.h"
#include "i2cext.h"

static int index = 0;
volatile static void (*I2C_Receive_Callback)(uint8_t value, uint16_t command, size_t bytes, int idx);
volatile static void (*I2C_Transmition_Callback)(volatile uint8_t * data, uint16_t command, size_t bytes);
static int I2C_Send_Control(Command_t command, uint8_t op);
__attribute__ ((weak)) void I2C_IRQ() {}
static uint8_t bytes = 0;
static uint16_t command = 0;

ISR(TWI_vect) 
{
	cli();

	switch(TW_STATUS)
	{
		case TW_SR_SLA_ACK:
            index = 0;
		    TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		    break;
		case TW_SR_DATA_ACK:
		    // received data from master, call the receive callback
			TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            index++;
            if (index == 1) bytes = TWDR;
            else if (index == 2) 
            {
                command = TWDR;
                command <<= 8;
            }
            else if (index == 3) 
            {
                command |= (uint8_t)TWDR;
            }
            else 
            I2C_Receive_Callback(TWDR, command, bytes, index - 4);
		    break;
        case TW_REP_START:
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            index = 0;
            break;
		case TW_ST_SLA_ACK:
		case TW_ST_DATA_ACK:
            index++;
            I2C_Transmition_Callback(&TWDR, command, bytes);
            if (index < bytes)
                TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA) | (1<<TWIE);
            else
                TWCR = (1<<TWEN) | (1<<TWINT)  | (1<<TWIE);
            break;
		case TW_SR_STOP:
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            index = 0;
            break;
        case TW_ST_DATA_NACK:
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            break;
		case TW_BUS_ERROR:
		    // some sort of erroneous state, prepare TWI to be readdressed
		    TWCR = 0;
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
            break;
		default:
		    TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		    break;
	}
	sei();
}

void I2C_Register_Transmition_Callback(volatile void (*transmit)(volatile uint8_t * data, uint16_t command, size_t bytes))
{
    I2C_Transmition_Callback = transmit;
    
}

void I2C_Register_Receiving_Callback(volatile void (*rec)(uint8_t data, uint16_t command, size_t bytes, int id))
{
    I2C_Receive_Callback = rec;
}

int I2C_Send_Command(Command_t command) 
{
    if (!command.data_distance) 
    {
        command.data_distance = 1;
    }

    uint8_t* ptr = command.data;
    I2C_Master_Start();
    if (TW_STATUS != TW_START)
        return 1;
    
    I2C_Send_Control(command, TW_WRITE);

    for (int i = 0; i < command.bytes; i++) 
    {
        I2C_Write(*(ptr++), I2C_ACK);
        if (TW_STATUS != TW_MT_DATA_ACK)
            return 1;
        _delay_loop_1(command.data_distance);
    }

    I2C_Master_Stop();
    _delay_loop_1(command.data_distance);
    return 0;
}

static int I2C_Send_Control(Command_t command, uint8_t op) 
{
    // 5 is for reading to setup another state
    int i = op ? 4 : 0;
    int len = op ? 5 : 4;

    for (; i < len; i++) 
    {
        uint8_t temp = 0, status = 0;
        
        if (i == 0) 
        {
            temp = I2C_GetSLA(command.address) | op;
            status = TW_MT_SLA_ACK;
        }
        else if (i == 1) 
        {
            temp = (uint8_t)command.bytes;
            status = TW_MT_DATA_ACK;
        }
        else if (i == 2) 
        {
            uint16_t cm = command.command >> 8;
            temp = (uint8_t)cm;
            status = TW_MT_DATA_ACK;
        }
        else if (i == 3)
        {
            temp = (uint8_t)command.command;
            status = TW_MT_DATA_ACK;
        }
        else
        {
            temp = I2C_GetSLA(command.address) | op;
            status = TW_MR_SLA_ACK;
        }

        I2C_Write(temp, I2C_ACK);
        if (TW_STATUS != status)
            return 1;
        _delay_loop_1(command.data_distance);
    }

    return 0;
}

int I2C_Read_Command(Command_t command) 
{
    if (!command.data_distance) 
    {
        command.data_distance = 1;
    }

    I2C_Master_Start();
    if (TW_STATUS != TW_START)
        return 1;

    I2C_Send_Control(command, TW_WRITE);

    // Repeated start
    I2C_Master_Start();
    if (TW_STATUS != TW_REP_START)
        return 1;

    I2C_Send_Control(command, TW_READ);

    uint8_t* ptr = command.data;

    int i = 0;

    do 
    {
        if (i < (command.bytes - 1)) 
        {
            *(ptr++) = I2C_Read(I2C_ACK);
            if (TW_STATUS != TW_MR_DATA_ACK)
                return 1;
        }
        else 
        {
            *(ptr++) = I2C_Read(I2C_NACK);
            if (TW_STATUS != TW_MR_DATA_NACK)
                return 1;
        }
        _delay_loop_1(command.data_distance);
        i++;
    }
    while(i < command.bytes);

    I2C_Master_Stop();
    return 0;
}