/**************************************************************************//**
\file  halSpi.c

\brief Implementation of USART SPI mode.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <spi.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Set the parameters of USART to work at SPI mode.
Parameters:
  descriptor - pointer to the spi descriptor.
Returns:
  none.
******************************************************************************/
void halSetSpiConfig(HAL_SpiDescriptor_t *descriptor)
{
  UBRRn(descriptor->tty) = 0;
  // Set MSPI mode
  UCSRnC(descriptor->tty) = (1 << UMSEL01) | (1 << UMSEL00);
  // Set clock mode and data order
  UCSRnC(descriptor->tty) |= ((uint8_t)descriptor->dataOrder | (uint8_t)descriptor->clockMode);
  // Enable receiver and transmitter
  UCSRnB(descriptor->tty) = (1 << RXEN0) | (1 << TXEN0);
  // Set baud rate
  UBRRn(descriptor->tty) = descriptor->baudRate;
}

/******************************************************************************
Write a length bytes to the SPI.
Parameters:
  tty    -  spi channel
  buffer -  pointer to application data buffer;
  length -  number bytes for transfer;
Returns:
  number of written bytes
******************************************************************************/
uint16_t halSyncWriteData(SpiChannel_t tty, uint8_t *buffer, uint16_t length)
{
  uint16_t i;
  uint8_t temp;

  for (i = 0; i < length; i++)
  {
    // Wait for empty transmit buffer
    while (!(UCSRnA(tty) & (1 << UDRE0)));
    // Send data
    UDRn(tty) = *(buffer + i);
    // Wait for data to be received
    while (!(UCSRnA(tty) & (1 << RXC0)));
    // receives data to clear received usart buffer
    temp = UDRn(tty);
    (void)temp;
  }
  return i;
}

/******************************************************************************
Write & read a length bytes to & from the SPI.
Parameters:
  tty    -  spi channel
  buffer -  pointer to application data buffer;
  length -  number bytes for transfer;
Returns:
  number of written & read bytes
******************************************************************************/
uint16_t halSyncReadData(SpiChannel_t tty, uint8_t *buffer, uint16_t length)
{
  uint16_t i;

  for (i = 0; i < length; i++)
  {
    // Wait for empty transmit buffer
    while (!(UCSRnA(tty) & (1 << UDRE0)));
    // Send data
    UDRn(tty) = *(buffer + i);
    // Wait for data to be received
    while (!(UCSRnA(tty) & (1 << RXC0)));
    // Receive data
    *(buffer + i) = UDRn(tty);
  }
  return i;
}

//end of halSpi.c
