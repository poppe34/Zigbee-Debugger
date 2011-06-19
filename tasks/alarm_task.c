/*
 * alarm_task.c
 *
 * Created: 3/22/2011 3:12:45 PM
 *  Author: matt
 */ 
#include "config.h"
#include "task_manager.h"
#include "alarm_task.h"
#include "lists.h"
#include "stdarg.h"
#include "stdio.h"

LIST(alarmLog);

static uint8_t verbose_level;

void alarm_task_init(void)
{
	list_init(alarmLog);
	verbose_level = DEBUG_LEVEL;
	alarm_new(5, "This is my new first alarm\0");
}


void alarm_ChangeLevel(uint8_t level)
{
	verbose_level = level;
}

uint8_t alarm_level(void)
{
	return verbose_level;
}

void alarm_new(uint8_t lvl, char *str, ...)
{
	va_list arg;
	va_start(arg, str);
	
	if(lvl <= verbose_level)
	{
	    if(list_length(alarmLog) < 40)
	    {
		    if(*str)
		    {
			    alarm_t *alrm = (alarm_t *)malloc(sizeof(alarm_t));

	            alrm->length = 0;
	            char *ptr = alrm->name;
				
		        vsprintf(alrm->name, str, arg);							
		   	    
		        while(*ptr)
			    {
		            alrm->length++;
		            ptr++;
			    }
				alrm->name[(alrm->length)] = 0;
				alrm->length++;
				if(alrm->length > 61)
				    alarm("Alarm Length is to Great");
			    list_add(alarmLog, alrm);	
		    }					
	    }
	}
	va_end(arg);
}

void alarm_sendQty(void)
{
	uint8_t alarm_len = list_length(alarmLog);
	packet_t *pkt = TM_newPacket();
	if(pkt)
	{
	    pkt->dir = to_usb;
	    pkt->task = task_alarm;
	    pkt->subTask = alarm_cnt;

	    pkt->buf[0] = alarm_len;
	    pkt->len = 1;
    }	
}

void alarm_sendUSBFirst(void)
{
	if((list_length(alarmLog)))
	{
	    alarm_t *alrm = list_pop(alarmLog);
	
	    if(alrm == NULL)
	    {
		    alarm("PC requested alarms when none were available");	
			return;	
	    }
	    else
	    {
		    packet_t *pkt = TM_newPacket();
			if(pkt)
			{
	            pkt->dir = to_usb;
	            pkt->task = task_alarm;
	            pkt->subTask = first_alarm;
	            pkt->len = alrm->length;

	            for(uint8_t x=0; x<alrm->length; x++)
		        pkt->buf[x] = alrm->name[x];
   
	            alarm_freeAlarm(alrm);
			}				
        }
	}
	else
	{
		packet_t *pkt = TM_newPacket();
		if(pkt)
		{
	        pkt->dir = to_usb;
	        pkt->task = task_alarm;
	        pkt->subTask = first_alarm;
	        pkt->len = 1;
			pkt->buf[0] = NULL;
		}			
	}			
}


void alarm_emptyLog(void)
{
	uint8_t alarm_len = list_length(alarmLog);
	alarm_t *alrm;
	while(alarm_len)
	{
		alrm = list_tail(alarmLog);
		list_remove(alarmLog, alrm);
		free(alrm);
		alarm_len--;
	}
	
}

void alarm_freeAlarm(alarm_t *alrm)
{
	list_remove(alarmLog, alrm);
	free(alrm);
}

void alarm_subTaskHandler(packet_t *pkt)
{
    switch(pkt->subTask)
	{
	    case alarm_cnt:
		   switch (pkt->dir)
		   {
		        case to_device:
				   
				break;
				case from_device:
					
				break;
			    case from_usb:
				    alarm_sendQty();
				break;
				case to_usb:
				    TM_toUSB(pkt);
				break;
				
		   }			
		break;
		
		case first_alarm:
		   switch (pkt->dir)
		   {
                case to_device:
				    
				break;
		        case from_device:
				    if(pkt->buf[0])
					    alarm_new(5, pkt->buf);				
				break;
			    case from_usb:
				    alarm_sendUSBFirst();
				break;
				case to_usb:
				    TM_toUSB(pkt);
				break;
		   }
		break;
			
		case clear_alarms:
		    alarm_emptyLog();
		break;
			
		default:
		alarm("Alarm received an unknown sub-Task");
		break;
	}	
   
}		
		
