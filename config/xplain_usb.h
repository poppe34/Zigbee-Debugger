/*
 * xplain_usb.h
 *
 * Created: 3/2/2011 6:20:32 PM
 *  Author: matt
 */ 


#ifndef XPLAIN_USB_H_
#define XPLAIN_USB_H_

#include "conf_board.h"
#include "gpio.h"
/*
#define SPI_XMEGA_DDR         DDRC
#define SPI_XMEGA_PORT        PORTC
#define SPI_XMEGA_DATA        SPDR
#define SPI_XMEGA_MISO        PINC0
#define SPI_XMEGA_MOSI        PINC5
#define SPI_XMEGA_SS          PINC6
#define SPI_XMEGA_CLK         PINC7

#define SPI_MASTER_IRQ        PIND0
#define SPI_MASTER_IRQ_DDR    DDRD
#define SPI_MASTER_IRQ_PORT   PORTD
*/

#ifdef CONFIG_BOARD_XMEGA_SPI

ASSIGN_PIN(XMEGA_MOSI, B, 2);
ASSIGN_PIN(XMEGA_MISO, B, 3);
ASSIGN_PIN(XMEGA_SS, B, 0);
ASSIGN_PIN(XMEGA_CLK, B, 1);
ASSIGN_PIN(XMEGA_IRQ, D, 0);
ASSIGN_PIN(RESET_LIGHT, B, 6)
#endif



#endif /* XPLAIN_USB_H_ */