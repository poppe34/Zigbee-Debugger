/*
 * uart.h
 *
 *  Created on: Feb 24, 2011
 *      Author: mattpoppe
 */

#ifndef UART_H_
#define UART_H_

#include "config.h"

#define ENABLE_TRANSMITTER(num)		UCSR##num##B |= _BV(TXEN##num)
#define ENABLE_RECIEVER(num)		UCSR##num##B |= _BV(RXEN##num)
#define DISABLE_TRANSMITTER(num)	UCSR##num##B &= ~(_BV(TXEN##num))
#define DISABLE_RECIEVER(num)		UCSR##num##B &= ~(_BV(TXEN##num))

#define ENABLE_TX_INTERRUPT(num) 	UCSR##num##B |= _BV(TXCIE##num)
#define ENABLE_RX_INTERRUPT(num) 	UCSR##num##B |= _BV(RXCIE##num)
#define DISABLE_TX_INTERRUPT(num) 	UCSR##num##B &= ~(_BV(TXCIE##num))
#define DISABLE_RX_INTERRUPT(num) 	UCSR##num##B &= ~(_BV(RXCIE##num))

typedef enum uart_deviceType{
	uart_receive = 0x00,
	uart_transmit = 0x01
}uart_deviceType_t;

typedef enum uart_stopBit{
	uart_stopBit1 = 0x00,
	uart_stopBit2 = 0x01
}uart_stopBit_t;

typedef enum uart_baudRate{
	uart_baud9600 = 0x00,
}uart_baudRate_t;

typedef enum uart_mode{
	uart_sync = 0x00,
	uart_async = 0x01,
	uart_SPImaster = 0x03
}uart_mode_t;

typedef enum uart_charSize{
	uart_5bit = 0x00,
	uart_6bit = 0x01,
	uart_7bit = 0x02,
	uart_8bit = 0x03,
	uart_9bit = 0x04
}uart_charSize_t;
typedef enum uart_parity{
	uart_noParity = 0x00,
	uart_even = 0x02,
	uart_odd  = 0x03
}uart_parity_t;

typedef enum uart_polarity{
	uart_risingEdge = 0x00,
	uart_fallingEdge = 0x01
}uart_polarity_t;

typedef struct uart_config{
	uart_baudRate_t		baudrate;
	uart_stopBit_t		stop;
	uart_deviceType_t  	device;
	uart_mode_t			mode;
	uart_parity_t		parity;
	uart_charSize_t		charSize;
	uart_polarity_t		polarity;
}uart_config_t;

//Init UART
U8 init_uart(U8, uart_config_t *);
U8 init_uart0(uart_config_t *);
U8 init_uart1(uart_config_t *);

//misc
U16 uart_calcBaud(uart_baudRate_t);

//transmit and receive
void uart_writeData(U8 *buf, U8 len);
void uart_readData(U8 *buf);
#endif /* UART_H_ */
