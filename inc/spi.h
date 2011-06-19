/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief SPI driver for AVR.
 *
 * This file defines a useful set of functions for the SPI interface on AVR
 * devices.
 *
 * - Compiler:           IAR and GNU GCC for AVR
 * - Supported devices:  All AVR devices with an SPI module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "config.h"
#include "xplain_usb.h"


/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable(void)
{
	SPCR |= _BV(SPE);
}

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
static inline void spi_disable(void)
{
	SPCR &= ~_BV(SPIE);
}

/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI is enabled, otherwise \c 0.
 */
static inline bool spi_is_enabled(void)
{
	return SPCR & _BV(SPIE) ? true : false;
}

/*! \brief Put one data byte to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded 
 *
 */
static inline void spi_put(uint8_t data)
{
	SPDR = data;
}

/*! \brief Get one data byte to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \return The data byte 
 *
 */
static inline uint8_t spi_get(void)
{
	return SPDR;
}

/*! \brief Tests if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
static inline Bool spi_is_tx_ok(void)
{
	return SPSR & _BV(SPIF) ? true : false;
}

/*! \brief Activate SPI master mode of a SPI peripheral
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
static inline void spi_enable_master_mode(void)
{
	SPCR |= _BV(MSTR);
}

/*! \name Part Specific SPI Driver
 */
//! @{
//! @}


#define DEFAULT_DELAY                   50000  

#define WAIT_FOR_DATA                   while(!(SPSR & _BV(SPIF))){;}
#define WAIT_FOR_DATA_TIMEOUT(delay)   delay = DEFAULT_DELAY;                            \
                                        while((!(SPSR & _BV(SPIF))) && delay)//{delay--;}	
#define WAIT_FOR_DATA_SLAVE				while(!(SPSR & _BV(SPIF)))					\
										 if(GPIO_XMEGA_SS_read() == 1){	GPIO_XMEGA_IRQ_set();  sei(); spi_active = NO; inactive_count = 0; return;}

#define SPI_IRQ_MASTER                  GPIO_XMEGA_IRQ_clr()
                          
#endif  // _SPI_H_
