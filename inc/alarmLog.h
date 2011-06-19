/*
 * alarmLog.h
 *
 *  Created on: Feb 21, 2011
 *      Author: mattpoppe
 */

#ifndef ALARMLOG_H_
#define ALARMLOG_H_

#include "config.h"
#include <stdlib.h>
#include "debugger_task.h"

#define kAlarmBufferSize 20


typedef struct alarm{
	struct alarm    *next;
	uint8_t         buf[64];
	uint8_t         length;
	uint8_t         send;
	uint8_t         *ptr;
}alarm_t;



uint8_t initAlarms(void);
void alarm(char *str);
int8_t 	alarmDataAvail(void);
uint8_t *alarmLogData(uint8_t num);
void freeAlarm(alarm_t *alrm);

#endif /* ALARMLOG_H_ */
