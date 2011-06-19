/*****************************************************************************//**
\file  halUsart.h

\brief  Declarations of usart hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/05/07 E. Ivanov - Created
**********************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _HAL_USART_H
#define _HAL_USART_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halDbg.h>
#include <halClkCtrl.h>
#include <halTaskManager.h>
#include <gpio.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/* if USART_DOUBLE_SPEED is 1 the USART uses U2Xn bit (Double speed the usart transmition).
   if USART_DOUBLE_SPEED is 0 then U2Xn bit is not been used.
 */
#ifndef USART_DOUBLE_SPEED
  #define USART_DOUBLE_SPEED 1ul
#endif

#define MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define MMIO_WORD(mem_addr) (*(volatile uint16_t *)(mem_addr))

#define USART_CHANNEL_1  0xC8 // USART At90USB1287 start address

#define UCSRnA(tty) MMIO_BYTE(tty + 0)
#define UCSRnB(tty) MMIO_BYTE(tty + 1)
#define UCSRnC(tty) MMIO_BYTE(tty + 2)
#define UBRRnL(tty) MMIO_BYTE(tty + 4)
#define UBRRnH(tty) MMIO_BYTE(tty + 5)
#define UBRRn(tty)  MMIO_WORD(tty + 4)
#define UDRn(tty)   MMIO_BYTE(tty + 6)

/******************************************************************************
                   Types section
******************************************************************************/
// clock rate of usart
typedef enum
{
  USART_BAUDRATE_1200 =  (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 1200ul) - 1ul), // 1200 baud rate
  USART_BAUDRATE_2400 =  (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 2400ul) - 1ul), // 2400 baud rate
  USART_BAUDRATE_4800 =  (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 4800ul) - 1ul), // 4800 baud rate
  USART_BAUDRATE_9600 =  (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 9600ul) - 1ul), // 9600 baud rate
  USART_BAUDRATE_19200 =  (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 19200ul) - 1ul), // 19200 baud rate
  USART_BAUDRATE_38400 = (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 38400ul) - 1ul), // 38400 baud rate
  USART_BAUDRATE_115200 = (unsigned)((F_CPU * (USART_DOUBLE_SPEED + 1ul)) / (16ul * 115200ul)), // 115200 baud rate
  USART_SYNC_BAUDRATE_1200  =  (uint16_t)((F_CPU / (2ul * 1200ul)) - 1ul),
  USART_SYNC_BAUDRATE_2400  =  (uint16_t)((F_CPU / (2ul * 2400ul)) - 1ul),
  USART_SYNC_BAUDRATE_4800  =  (uint16_t)((F_CPU / (2ul * 4800ul)) - 1ul),
  USART_SYNC_BAUDRATE_9600  =  (uint16_t)((F_CPU / (2ul * 9600ul)) - 1ul),
  USART_SYNC_BAUDRATE_38400 =  (uint16_t)((F_CPU / (2ul * 38400ul)) - 1ul),
  USART_SYNC_BAUDRATE_57600 =  (uint16_t)((F_CPU / (2ul * 57600ul)) - 1ul),
  USART_SYNC_BAUDRATE_115200 = (uint16_t)((F_CPU / (2ul * 115200ul)) - 1ul)
} UsartBaudRate_t;

// usart data length
typedef enum
{
  USART_DATA5 = (0 << UCSZ12) | (0 << UCSZ11) | (0 << UCSZ10), // 5 bits data length
  USART_DATA6 = (0 << UCSZ12) | (0 << UCSZ11) | (1 << UCSZ10), // 6 bits data length
  USART_DATA7 = (0 << UCSZ12) | (1 << UCSZ11) | (0 << UCSZ10), // 7 bits data length
  USART_DATA8 = (0 << UCSZ12) | (1 << UCSZ11) | (1 << UCSZ10), // 8 bits data length
} UsartData_t;

// parity mode
typedef enum
{
  USART_PARITY_NONE = (0 << UPM11) | (0 << UPM10), // Non parity mode
  USART_PARITY_EVEN = (1 << UPM11) | (0 << UPM10), // Even parity mode
  USART_PARITY_ODD =  (1 << UPM11) | (1 << UPM10)  // Odd parity mode
} UsartParity_t;

// number of stop bits
typedef enum
{
  USART_STOPBIT_1 = (0 << USBS1), // 1 stop bits mode
  USART_STOPBIT_2 = (1 << USBS1)  // 2 stop bits mode
} UsartStopBits_t;

// USART task IDs.
typedef enum
{
#if defined(HAL_USE_USART_CHANNEL_1)
  HAL_USART_TASK_USART1_DRE,
  HAL_USART_TASK_USART1_TXC,
  HAL_USART_TASK_USART1_RXC,
  #if defined(_USE_USART_ERROR_EVENT_)
    HAL_USART_TASK_USART1_ERR,
  #endif
#endif

  HAL_USART_TASKS_NUMBER
} HalUsartTaskId_t;

// USART External CLK pin description structure.
typedef struct
{
  uint8_t portAddr;
  uint8_t pinNumber;
} HalUsartExtClkPinDescr_t;

// Defines edge of clock to sample data.
/*
------------------------------------------------------------------------------------
|            |  Transmitted Data Changed (Output | Received Data Sampled (Input on |
|            |  of TxDn Pin)                     | RxDn Pin)                       |
|------------|-----------------------------------|----------------------------------
|FALLING_EDGE|  Rising XCKn Edge                 | Falling XCKn Edge               |
|RISING_EDGE |  Falling XCKn Edge                | Rising XCKn Edge                |
------------------------------------------------------------------------------------
*/
typedef enum
{
  USART_EDGE_MODE_FALLING = 0,
  USART_EDGE_MODE_RISING  = 1
} UsartEdgeMode_t;

// USART synchronization mode.
typedef enum
{
  USART_MODE_ASYNC = ((0 << UMSEL11) | (0 << UMSEL10)),
  USART_MODE_SYNC  = ((0 << UMSEL11) | (1 << UMSEL10))
} UsartMode_t;

// clck is output in master mode else input
typedef enum
{
  USART_CLK_MODE_MASTER = 0,
  USART_CLK_MODE_SLAVE  = 1
} UsartClkMode_t;

#if defined(_USE_USART_ERROR_EVENT_)
  // usart receiver error reason
  typedef enum
  {
    FRAME_ERROR,
    DATA_OVERRUN,
    PARITY_ERROR
  } UsartErrorReason_t;
#endif

// usart control
typedef struct
{
  uint16_t txPointOfRead;
  uint16_t txPointOfWrite;
  volatile uint16_t rxPointOfRead;
  volatile uint16_t rxPointOfWrite;
  uint8_t  usartShiftRegiaterEmpty;
#if defined(_USE_USART_ERROR_EVENT_)
  volatile uint8_t  errorReason;
#endif
} UsartControl_t;

// HAL USART service field - contatins variables for HAL USART module internal needs
typedef struct
{
  UsartControl_t halUsartControl;
} HalUsartService_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Puts the byte received to the cyclic buffer.

\param[in]
  tty - channel number.
\param[in]
  data - data to put.
******************************************************************************/
void halUsartRxBufferFiller(uint8_t i, uint8_t data);

#if defined(_USE_USART_ERROR_EVENT_)
/**************************************************************************//**
\brief Save status register for analyzing of the error reason.

\param[in]
  tty - channel number.
\param[in]
  status - usart status register.
******************************************************************************/
void halUsartSaveErrorReason(uint8_t tty, uint8_t status);
#endif

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/**************************************************************************//**
  \brief Disables USART channel

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halCloseUsart(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALCLOSEUSART_0);
  UCSRnB(tty) = 0x00;
}

/**************************************************************************//**
  \brief Enables data register empty interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halEnableUsartDremInterrupt(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALENABLEUSARTDREMINTERRUPT_0);
  UCSRnB(tty) |= (1 << UDRIE1);
}

/**************************************************************************//**
  \brief Disables data register empty interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halDisableUsartDremInterrupt(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALDISABLEUSARTDREMINTERRUPT_0);
  UCSRnB(tty) &= ~(1 << UDRIE1);
}

/**************************************************************************//**
  \brief Enables transmit complete interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halEnableUsartTxcInterrupt(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALENABLEUSARTTXCINTERRUPT_0);
  UCSRnB(tty) |= (1 << TXCIE1);
}

/**************************************************************************//**
  \brief Disables transmit complete interrupt

  \param tty - number of USART channel.
  return none.
******************************************************************************/
INLINE void halDisableUsartTxcInterrupt(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALDISABLEUSARTTXCINTERRUPT_0);
  UCSRnB(tty) &= ~(1 << TXCIE1);
}

/**************************************************************************//**
  \brief Enables receive complete interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halEnableUsartRxcInterrupt(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALENABLEUSARTRXCINTERRUPT_0);
  UCSRnB(tty) |= (1 << RXCIE1);
}

/**************************************************************************//**
  \brief Disables receive complete interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halDisableUsartRxcInterrupt(uint8_t tty)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALDISABLEUSARTRXCINTERRUPT_0);
  UCSRnB(tty) &= ~(1 << RXCIE1);
}

/**************************************************************************//**
  \brief Puts byte to data register of USART

  \param tty - number of USART channel.
         data - byte to send.
  \return none.
******************************************************************************/
INLINE void halSendUsartByte(uint8_t tty, uint8_t data)
{
  assert(USART_CHANNEL_1 == tty, HALUSARTH_HALSENDUSARTBYTE_0);
  UDRn(tty) = data;
}

#endif /* _HAL_USART_H */
//eof halUsart.h
