/**************************************************************************//**
  \file gpio.h

  \brief Implementation of gpio defines.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
     4/12/08 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _GPIO_H
#define _GPIO_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <compiler.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
/******************************************************************************
* void gpioX_set() sets GPIOX pin to logical 1 level.
* void gpioX_clr() clears GPIOX pin to logical 0 level.
* void gpioX_make_in makes GPIOX pin as input.
* void gpioX_make_in makes GPIOX pin as output.
* uint8_t gpioX_read() returns logical level GPIOX pin.
* uint8_t gpioX_state() returns configuration of GPIOX port.
*******************************************************************************/
#define ASSIGN_PIN(dev, ioport, bitnum) \
 SINLINE void  GPIO_##dev##_set(void)         {PORT##ioport |= (1 << bitnum);} \
 SINLINE void  GPIO_##dev##_clr(void)         {PORT##ioport &= ~(1 << bitnum);} \
 SINLINE uint8_t  GPIO_##dev##_read(void)     {return (PIN##ioport & (1 << bitnum)) != 0;} \
 SINLINE uint8_t  GPIO_##dev##_state(void)    {return (DDR##ioport & (1 << bitnum)) != 0;} \
 SINLINE void  GPIO_##dev##_make_out(void)    {DDR##ioport |= (1 << bitnum);} \
 SINLINE void  GPIO_##dev##_make_in(void)     {DDR##ioport &= ~(1 << bitnum); PORT##ioport &= ~(1 << bitnum);} \
 SINLINE void  GPIO_##dev##_make_pullup(void) {PORT##ioport |= (1 << bitnum);}\
 SINLINE void  GPIO_##dev##_toggle(void)      {PORT##ioport ^= (1 << bitnum);}

/*
// Empty function creation - to remove uart.c warnings which appear in case if DTR and EXCLK are not defined.
INLINE void  GPIO_UART_DTR_make_in(void){}
INLINE uint8_t  GPIO_UART_DTR_read(void){return 0;}
INLINE void  GPIO_USART_EXTCLK_make_out(void){}
INLINE void  GPIO_USART_EXTCLK_make_in(void){}
INLINE void  GPIO_USART_EXTCLK_make_pullup(void){}
*/


#endif /* _GPIO_H */
