/*
 * spi_driver.c
 *
 *  Created on: Dec 14, 2010
 *      Author: mattpoppe
 */
#include "avr/io.h"
#include "conf_board.h"
#include "gpio.h"
#include "spi.h"




void spi_init(void){

/*
 * Make sure the Power Reduction Register is low
 */
	 PRR0 |= _BV(PRSPI);

 /*
 *  Setup the Speed and make the device master of SPI
 */
	SPCR = (_BV(SPE) | _BV(SPIE));  // SPI enable, slave mode.

    

}//init slave spi


