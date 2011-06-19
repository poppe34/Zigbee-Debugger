/*
 * gpio.c
 *
 * Created: 3/2/2011 12:44:20 PM
 *  Author: matt
 */ 
#include "gpio.h"
/******************************************************************************
                   Inline static functions section
******************************************************************************/

#ifdef INCLUDE_GPIO_
// the macros for the manipulation by GPIO0
HAL_ASSIGN_PIN(0, B, 5);
// the macros for the manipulation by GPIO1
HAL_ASSIGN_PIN(1, B, 6);
// the macros for the manipulation by GPIO2
HAL_ASSIGN_PIN(2, B, 7);
// the macros for the manipulation by GPIO6
HAL_ASSIGN_PIN(6, D, 6);
// the macros for the manipulation by GPIO7
HAL_ASSIGN_PIN(7, D, 7);

// macroses only for STK500
// the macros for the manipulation by GPIO9
HAL_ASSIGN_PIN(9,  C, 0);
// the macros for the manipulation by GPIO10
HAL_ASSIGN_PIN(10, C, 1);
// the macros for the manipulation by GPIO11
HAL_ASSIGN_PIN(11, C, 2);
// the macros for the manipulation by GPIO12
HAL_ASSIGN_PIN(12, C, 3);
// the macros for the manipulation by GPIO13
HAL_ASSIGN_PIN(13, C, 4);
// the macros for the manipulation by GPIO14
HAL_ASSIGN_PIN(14, C, 5);
// the macros for the manipulation by GPIO15
HAL_ASSIGN_PIN(15, C, 6);
// the macros for the manipulation by GPIO16
HAL_ASSIGN_PIN(16, C, 7);
// macroses only for STK500
#endif


#ifdef IF_I_WANT_IT_TO
// the macros for the manipulation by GPIO_I2C_CLK
HAL_ASSIGN_PIN(I2C_CLK, D, 0);
// the macros for the manipulation by GPIO_I2C_DATA
HAL_ASSIGN_PIN(I2C_DATA, D, 1);
// the macros for the manipulation by GPIO_USART1_TXD
HAL_ASSIGN_PIN(USART1_TXD, D, 2);
// the macros for the manipulation by GPIO_USART1_RXD
HAL_ASSIGN_PIN(USART1_RXD, D, 3);
// the macros for the manipulation by GPIO_USART1_EXTCLK
HAL_ASSIGN_PIN(USART1_EXTCLK, D, 4);
// the macros for the manipulation by GPIO_USART1_TXD
HAL_ASSIGN_PIN(USART0_TXD, D, 0);
// the macros for the manipulation by GPIO_USART1_RXD
HAL_ASSIGN_PIN(USART0_RXD, D, 1);
// the macros for the manipulation by GPIO_USART1_EXTCLK
HAL_ASSIGN_PIN(USART0_EXTCLK, B, 0);
// the macros for the manipulation by GPIO_UART_RTS
HAL_ASSIGN_PIN(UART_RTS, D, 4);
// the macros for the manipulation by GPIO_UART_CTS
HAL_ASSIGN_PIN(UART_CTS, D, 5);
#endif

