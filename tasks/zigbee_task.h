/*
 * zigbee_task.h
 *
 * Created: 4/29/2011 3:09:01 PM
 *  Author: mpoppe
 */ 


#ifndef ZIGBEE_TASK_H_
#define ZIGBEE_TASK_H_

#include "compiler.h"
#include "conf_debug.h"
#include "task_manager.h" 
#include "alarm_task.h"
#include "lists.h"

enum zigbeeSubtask
{
	zigbeePacketQty = 0x01,
	zigbeePacketFirst = 0x02,
};

#ifdef DEBUG_SERVER
void zigbee_subTaskHandler(packet_t *pkt);
void zigbee_task_init(void);
void zigbee_packetQTY(void);
void zigbee_packetFirst(void);
#endif

void zigbee_newPacket(uint8_t *buf, uint8_t zlen);
#endif /* ZIGBEE_TASK_H_ */