/*
 * alarm_task.h
 *
 * Created: 3/22/2011 3:17:01 PM
 *  Author: matt
 */ 


#ifndef ALARM_TASK_H_
#define ALARM_TASK_H_
#include "compiler.h"
#include "task_manager.h"
#define alarm(str) alarm_new(5, str)


typedef struct alarm 
{
	struct alarm    *next;
	char            name[64];
	uint8_t         length;
	uint16_t        timestamp;
}alarm_t;

enum alarm_subTasks
{
    alarm_cnt = 0x01,
	first_alarm = 0x02,
	clear_alarms = 0x03,	
};

void alarm_changeLevel(uint8_t num);
uint8_t alarm_level(void);
void alarm_new(uint8_t lvl, char *str, ...);
void alarm_subTaskHandler(packet_t *pkt);
void alarm_sendUSBFirst(void);
void alarm_readDeviceFirst(packet_t *pkt);
void alarm_freeAlarm(alarm_t *alrm);

#endif /* ALARM_TASK_H_ */