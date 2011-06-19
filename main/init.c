/*
 * init.c
 *
 * Created: 3/2/2011 11:41:26 AM
 *  Author: matt
 */ 
#include "xplain_usb.h"


/*
 * Declare the IO for SPI
 */


void board_init(void)
{
	/*
 * Declare the output Ports
 */
    GPIO_XMEGA_MISO_make_out();
	GPIO_XMEGA_IRQ_make_out();
	
/*
 *  Declare the inputs
 */
	GPIO_XMEGA_MOSI_make_in();
	GPIO_XMEGA_SS_make_in();
	GPIO_XMEGA_CLK_make_in();

}    
