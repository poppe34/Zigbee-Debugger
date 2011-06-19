/*
 * ledActions.h
 *
 *  Created on: Feb 23, 2011
 *      Author: mattpoppe
 */

#ifndef LEDACTIONS_H_
#define LEDACTIONS_H_
#include "config.h"

typedef enum ledOperation{
	led_off = 0,
	led_on = 1,
	led_toggle = 2,
	led_status = 3,
	led_report = 4
}ledOperation_t;

extern uint8_t buf_in[256];
extern uint8_t rxok;

void ledOn(U8);
void ledOff(U8);

#endif /* LEDACTIONS_H_ */
