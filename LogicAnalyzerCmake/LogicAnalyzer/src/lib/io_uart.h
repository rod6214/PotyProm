/*
 * io_uart.h
 *
 * Created: 5/7/2022 7:29:44 PM
 *  Author: Nelson
 */


#ifndef IO_UART_H_
#define IO_UART_H_

extern char usart_receive();
extern void usart_send(char data);
extern void usart_start();

#endif /* IO_UART_H_*/