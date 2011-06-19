/*This file has been prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file manages the high level application device task.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  AT90USB1287, AT90USB1286, AT90USB647, AT90USB646
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2007, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "debugger_task.h"
#include "usb_drv.h"
#include "usb_descriptors.h"
#include "usb_standard_request.h"
#include "wdt_drv.h"
#include "ledActions.h"
#include "xplain_usb.h"

//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________

uint8_t buf_in[256];
uint8_t buf_out[256];
//_____ D E C L A R A T I O N S ____________________________________________


volatile U8 cpt_sof;

//!
//! @brief This function initializes the hardware/software resources
//! required for device application task.
//!
//!
//! @param none
//!
//! @return none
//!
//!/
void debugger_task_init(void) {
	//Joy_init();
	//Hwb_button_init();
	cpt_sof = 0;
	Usb_enable_sof_interrupt();
	rxok = FALSE;
}

//! @brief Entry point of the device application
//!
//! This function links the application with the USB bus.
//!
//! @param none
//!
//! @return none
void debugger_task(void) {
	U8 i;
	U8 *ptr;
	static U8 dummy_data;

	//.. FIRST CHECK THE DEVICE ENUMERATION STATE
	if (Is_device_enumerated()) {
		//.. HERE START THE USB DEVICE APPLICATIVE CODE
		//.. The example bellow just perform a loop back transmition/reception
		//.. All data received wth the OUT endpoint are store in a ram buffer and
		//.. send back to the IN endpoint

		//.. For example, blink a led with start of frame counter
//#if TARGET_BOARD == XPLAIN
		if (cpt_sof > 0x7F) {
			GPIO_RESET_LIGHT_clr();
		} else {
			GPIO_RESET_LIGHT_set();
		}
//#endif

		//.. First interface management
		//.. Select the OUT endpoint declared in descriptors
		//.. load the endpoint with the content of a ram buffer for example
		Usb_select_endpoint(EP_TEMP_OUT);
		if (Is_usb_receive_out()) {
			ptr = buf_out;
			for (i = 64; i; i--) {
				*ptr++ = Usb_read_byte();
			}
			TM_fromUSB(buf_out);

			Usb_ack_receive_out();
		}
		//.. First interface management (cont)
		//.. Select the IN endpoint declared in descriptors
		//.. If we receive something, just store in the ram buffer
		Usb_select_endpoint(EP_TEMP_IN);
		if (Is_usb_read_control_enabled() && (rxok == TRUE) ){
			ptr = buf_in;
			for (i = 0; i < EP_IN_LENGTH_TEMP1; i++)
				Usb_write_byte(*ptr++);
			Usb_ack_in_ready();
  			rxok = FALSE;
		}

		//.. Second interface management (interrupt IN endpoint)
		//.. Just Send dummy data bytes
		Usb_select_endpoint(EP_TEMP_INT_IN); // Select this enpoint
		if (Is_usb_write_enabled()) // Check data can be loaded
		{ // And load dummy data...
			Usb_write_byte(dummy_data);
			Usb_write_byte(dummy_data+1);
			Usb_write_byte(dummy_data+2);
			Usb_write_byte(dummy_data+3);
			Usb_ack_in_ready();
			dummy_data += 4;
		}

	}
}

//! @brief sof_action
//!
//! This function increments the cpt_sof counter each times
//! the USB Start Of Frame interrupt subroutine is executed (1ms)
//! Usefull to manage time delays
//!
//! @param none
//!
//! @return none


void sof_action() {
	cpt_sof++;
}
