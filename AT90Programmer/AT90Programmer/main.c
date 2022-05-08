/*
 * AT90Programmer.c
 *
 * Created: 5/1/2022 12:31:53 PM
 * Author : Nelson
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_mem.h"
#include "io_uart.h"
#include "ext_eeprom_mem.h"

#define MAX_MEMORY 64
char _buffer[MAX_MEMORY + 5];
int _idx = 0;
int command = 0;
int data_sent = FALSE;
int execute_proc = FALSE;

#define wait_host() while(!data_sent); data_sent=FALSE

ISR(USART_TX_vect)
{
	cli();
	data_sent = TRUE;
	sei();
}

ISR(USART_RX_vect)
{
	cli();
	_buffer[_idx] = usart_receive();
	_idx++;
	sei();
}

void config()
{
	usart_start();
	init_ctrl_mem();
	_delay_loop_1(100);
	_idx = 0;
	execute_proc = FALSE;
	sei();
}

void loop() 
{
	if (_idx >= 64)
	{
		usart_send(ACK);
		wait_host();
		execute_proc = TRUE;
	}
	
	if (execute_proc) 
	{
		char command = _buffer[0];
		
		if (command == WRITE_MEMORY)
		{
			reset_ctrl();
			prepare_for_write();
			_delay_loop_1(100);
			
			EEPROM_t* pEeprom = get_eeprom(_buffer);

			for (int i = 0; i < pEeprom->bytes; i++)
			{
				char data = _buffer[i + 5];
				write_mem(i + pEeprom->offset, data);
				_delay_ms(10);
			}
			
			reset_ctrl();
			usart_send(ACK);
			wait_host();
		}
		else if (command == READ_MEMORY)
		{
			reset_ctrl();
			prepare_for_read();
			_delay_loop_1(100);
			
			EEPROM_t* pEeprom = get_eeprom(_buffer);
			
			for (int i = 0; i < pEeprom->bytes; i++)
			{
				char data = read_mem(i + pEeprom->offset);
				_delay_loop_1(1);
				usart_send(data);
				wait_host();
			}
			
			reset_ctrl();
		}
		
		command = NULL;
		_idx = 0;
		execute_proc = FALSE;
		deactivate_ports();
	}
}

int main(void)
{
	config();
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

