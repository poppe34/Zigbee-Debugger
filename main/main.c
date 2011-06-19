/*This file has been prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Main for USB application.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  AT90USB1287, AT90USB1286, AT90USB647, AT90USB646
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************
//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "scheduler.h"
#include "wdt_drv.h"
#include "power_drv.h"
#include "uart_lib.h"
#include "spi_task.h"
#include "alarm_task.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________


int main(void)
{
	board_init();
	wdtdrv_disable();
	Clear_prescaler();
	sei();
	scheduler();
    
	return 0;
}

//! \name Procedure to speed up the startup code
//! This one increment the CPU clock before RAM initialization
//! @{
#ifdef  __GNUC__
// Locate low level init function before RAM init (init3 section)
// and remove std prologue/epilogue
char __low_level_init(void) __attribute__ ((section (".init3"),naked));
#endif

#ifdef __cplusplus
extern "C" {
#endif
char __low_level_init()
{
	clock_prescale_set(0);
  return 1;
}
#ifdef __cplusplus
}
#endif
//! @}

