/*
 * zigbee_task.c
 *
 * Created: 4/29/2011 3:08:32 PM
 *  Author: mpoppe
 */ 
#include "zigbee_task.h"
#ifdef DEBUG_SERVER
LIST(zPackets);

void zigbee_task_init(void)
{
	list_init(zPackets);
}

void zigbee_subTaskHandler(packet_t *pkt)
{
	switch (pkt->subTask)
	{
		case zigbeePacketQty:
		    switch(pkt->dir)
			{
				case to_usb:
				TM_toUSB(pkt);
				break;
				case from_usb:
				zigbee_packetQTY();
				break;
			}
		break;
		
		case zigbeePacketFirst:
		    switch(pkt->dir)
			{
				case from_device:
				zigbee_newPacket(pkt->buf, pkt->len);
				break;
				case from_usb:
				zigbee_packetFirst();
				break;
				case to_usb:
				//TM_toUSB(pkt);
				break;
			}
		break;
	}
}

void zigbee_packetQTY(void)
{
	packet_t *pkt = TM_newPacket();
	if(pkt)
	{
	    pkt->len = BYTES_NEEDED_FOR_LENGTH;
	    pkt->task = task_zigbee;
	    pkt->subTask = zigbeePacketQty;

#ifdef DEBUG_SERVER
		pkt->dir = to_usb;
		pkt->buf[0] = list_length(zPackets);
#endif
#ifdef DEBUG_CLIENT

	    pkt->dir = to_device;
#endif 

	}	
}

void zigbee_packetFirst(void)
{
	if(list_length(zPackets))
	{
		packet_t *pkt = list_pop(zPackets);
		
		if(pkt)
		{
			TM_toUSB(pkt);
		}
		else alarm("Request for first Zigbee Packet with non avail");
		
		free(pkt);
	}
}
#endif



void zigbee_newPacket(uint8_t *buf, uint8_t zlen)
{
	packet_t *pkt = TM_newPacket();
	
	pkt->len = zlen;
	pkt->ptr = (pkt->buf);
	
	while(zlen)
	{
		*pkt->ptr++ = *buf++;
		zlen--;
	}
#ifdef DEBUG_CLIENT
	pkt->dir = to_usb;
#endif
	pkt->dir = to_usb;
	pkt->task = task_zigbee;
	pkt->subTask = zigbeePacketFirst;
	
#ifdef DEBUG_SERVER
    list_add(zPackets, pkt);
	TM_removeTask(pkt);
#endif
}
