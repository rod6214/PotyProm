/*
 * io_uart.h
 *
 * Created: 5/7/2022 7:29:44 PM
 *  Author: Nelson
 */


#ifndef IO_UART_H_
#define IO_UART_H_
// #define wait_host() while(!data_sent); data_sent=FALSE
// int data_sent = FALSE;
extern char usart_receive();
extern void usart_send(char data);
extern void usart_start();
extern void wait_host();
extern void set_as_sent();

#endif /* IO_UART_H_*/