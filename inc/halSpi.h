/*****************************************************************************//**
\file  halSpi.h

\brief  Declarations of USART SPI mode.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/06/07 E. Ivanov - Created
**********************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _HALSPI_H
#define _HALSPI_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <usart.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define UDORD0   2
#define UCPHA0   1
#define UCPOL0   0

#define SPI_CHANNEL_0 USART_CHANNEL_0  // USART0 AtMega1281/2561 start addresss
#define SPI_CHANNEL_1 USART_CHANNEL_1  // USART1 AtMega1281/2561 start addresss

/******************************************************************************
                   Types section
******************************************************************************/
// spi channel
typedef UsartChannel_t SpiChannel_t;

// types of the clock mode
typedef enum
{
  // leading edge sample RX bit (rising), trailing edge setup TX bit (falling).
  SPI_CLOCK_MODE0 = ((0 << UCPOL0) | (0 << UCPHA0)),
  // leading edge setup TX bit (rising), trailing edge sample RX bit (falling).
  SPI_CLOCK_MODE1 = ((0 << UCPOL0) | (1 << UCPHA0)),
  // leading edge sample RX bit (falling), trailing edge setup TX bit (rising).
  SPI_CLOCK_MODE2 = ((1 << UCPOL0) | (0 << UCPHA0)),
  // leading edge setup TX bit (falling), trailing edge sample RX bit (rising).
  SPI_CLOCK_MODE3 = ((1 << UCPOL0) | (1 << UCPHA0))
} SpiClockMode_t;

// clock rate
typedef enum
{
  SPI_CLOCK_RATE_62 =  ((F_CPU / (2 * 62500ul)) - 1),
  SPI_CLOCK_RATE_125 =  ((F_CPU / (2 * 125000ul)) - 1),
  SPI_CLOCK_RATE_250 =  ((F_CPU / (2 * 250000ul)) - 1),
  SPI_CLOCK_RATE_500 =  ((F_CPU / (2 * 500000ul)) - 1),
  SPI_CLOCK_RATE_1000 = ((F_CPU / (2 * 1000000ul)) - 1),
  SPI_CLOCK_RATE_2000 = ((F_CPU / (2 * 2000000ul)) - 1)
} SpiBaudRate_t;

// Data order
typedef enum
{
  SPI_DATA_MSB_FIRST = 0 << UDORD0, // data with MSB first
  SPI_DATA_LSB_FIRST = 1 << UDORD0  // data with LSB first
} SpiDataOrder_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
Write a length bytes to the SPI.
Parameters:
  tty    -  spi channel
  buffer -  pointer to application data buffer;
  length -  number bytes for transfer;
Returns:
  number of written bytes
******************************************************************************/
uint16_t halSyncWriteData(SpiChannel_t tty, uint8_t *buffer, uint16_t length);

/******************************************************************************
Write & read a length bytes to & from the SPI.
Parameters:
  tty    -  spi channel
  buffer -  pointer to application data buffer;
  length -  number bytes for transfer;
Returns:
  number of written & read bytes
******************************************************************************/
uint16_t halSyncReadData(SpiChannel_t tty, uint8_t *buffer, uint16_t length);

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/******************************************************************************
Disables USART channel.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halCloseSpi(SpiChannel_t tty)
{
  UCSRnB(tty) = 0x00; // disable
}

/******************************************************************************
Enables data register empty interrupt.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halEnableSpiDremInterrupt(SpiChannel_t tty)
{
  UCSRnB(tty) |= (1 << UDRIE0);
}

/******************************************************************************
Disables data register empty interrupt.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halDisableSpiDremInterrupt(SpiChannel_t tty)
{
  UCSRnB(tty) &= ~(1 << UDRIE0);
}

/******************************************************************************
Enables transmit complete interrupt.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halEnableSpiTxcInterrupt(SpiChannel_t tty)
{
  UCSRnB(tty) |=  (1 << TXCIE0);
}

/******************************************************************************
Disables transmit complete interrupt.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halDisableSpiTxcInterrupt(SpiChannel_t tty)
{
  UCSRnB(tty) &=  ~(1 << TXCIE0);
}

/*****************************************************************************
Enables receive complete interrupt.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halEnableSpiRxcInterrupt(SpiChannel_t tty)
{
  UCSRnB(tty) |= (1 << RXCIE0);
}

/*****************************************************************************
Disables receive complete interrupt.
Parameters:
  tty  -  spi channel.
Returns:
  none.
******************************************************************************/
INLINE void halDisableSpiRxcInterrupt(SpiChannel_t tty)
{
  UCSRnB(tty) &= ~(1 << RXCIE0);
}
#endif
//eof halSpi.h

