/*
 * conf_led.h
 *
 *  Created on: Feb 27, 2011
 *      Author: mattpoppe
 */

#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "compiler.h"

void led_taskUSB(U8 *buf);
uint8_t led_pinNum(U8 num);

#endif /* CONF_LED_H_ */
