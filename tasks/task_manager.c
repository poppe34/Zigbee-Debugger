/*
 * task_manager.c
 *
 * Created: 3/10/2011 2:15:59 PM
 *  Author: matt
 */ 
#include "compiler.h"
#include "task_manager.h"
#include "lists.h"
#include "xplain_usb.h"
#include "alarm_task.h"

LIST(packets);

void TM_task_init(void)
{
	list_init(packets);
	alarm_task_init();
	usb_send_ok = NO;
}

void TM_task(void)
{
	packet_t *pkt;
	uint8_t length;
	pkt = NULL;
	

	length = list_length(packets);
	
	if(length)
	{
		TM_handler(list_pop(packets));
	}
}


void TM_passPacket(packet_t *pkt, packet_t *newpkt)
{
	newpkt->len = pkt->len;
	newpkt->task = pkt->task;
	newpkt->subTask = pkt->subTask;
	
	for(uint8_t x = 0; x<pkt->len; x++)
	    newpkt->buf[x] = pkt->buf[x];
}

void TM_fromUSB(uint8_t *buf)
{
	void *ptr = buf;
	uint8_t cnt = 64;
	packet_t *pkt;
	if(*buf)
	{
	
        pkt = TM_newPacket();
		if(pkt == NULL) 
		{
            alarm("(task_manager)TM_fromUSB:Null Packet Returned");
			return;
		}		
			
	    pkt->len = *buf;
		
		//prevent duplicate packets by setting the future lengths to 0
		*buf = 0;
	    uint8_t length;
		buf++;
		
		pkt->task = *buf++;
		pkt->subTask = *buf++;
		
		pkt->ptr = pkt->buf;
		
		length = pkt->len;
	
	    while(length)
		{
			*pkt->ptr++ = *buf++;
			length--;
		}
	
	    pkt->dir = from_usb;
		
		
	}
}

packet_t *TM_newPacket(void)
{
	if(list_length(packets) >= 40)
	{
      alarm("(task_manager.c)TM_newPacket:Overflow of packets");
	  return NULL;
	}	
	packet_t *newPacket = (packet_t *)malloc(sizeof(packet_t));
	
	newPacket->ptr = newPacket->buf;
	newPacket->dir = 0;
	newPacket->len = 0;
	newPacket->subTask = 0;
	newPacket->task = 0;
	
	list_add(packets, newPacket);
	
	return newPacket;
}	

void TM_toUSB(packet_t *pkt)
{
	uint8_t *ptr = buf_in;
    uint8_t len;
	pkt->ptr = pkt->buf;
	
	*ptr++ = (pkt->len+3);
	
	*ptr++ = pkt->task;
	*ptr++ = pkt->subTask;
	
    len = pkt->len;
	while(len)
	{
        *ptr++ = *pkt->ptr++;
		len--;
	}
	rxok = YES;
}

void TM_handler(packet_t *pkt)
{
	switch(pkt->task)
	{
		case task_LED:
		    //led_subTaskHandler(pkt); I stopped this So I would not have any transmissions to the device
		break;
		
		case task_alarm:
		    alarm_subTaskHandler(pkt);
		break;
		
		case task_zigbee:
		    zigbee_subTaskHandler(pkt);
		break;
		
		default:
		    alarm("Task Manager reached and unknown task");
		break;
	}
	TM_freePacket(pkt);
}
void TM_removeTask(packet_t *pkt)
{
	list_remove(packets, pkt);
}

void TM_freePacket(packet_t *pkt)
{
	list_remove(packets, pkt);
	free(pkt);
}