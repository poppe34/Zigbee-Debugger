/*
 * ledActions.c
 *
 *  Created on: Feb 11, 2011
 *      Author: mattpoppe
 */


#include "compiler.h"
#include "ledActions.h"
#include "xplain_usb.h"
#include "spi_task.h"
#include "task_manager.h"
#include "alarm_task.h"


EXTERNAL_LIST(spi_output);

void led_subTaskHandler(packet_t *pkt)
{
    if(pkt->dir == from_usb)
    {
	    switch(pkt->subTask)
	    {
		    case led_off:
                alarm_new(5, "LED %i off command issued from USB", pkt->buf[0]);
			    spi_addPacket(pkt);
			    break;
			
		    case led_on:
		        alarm_new(5, "LED %i on command issued from USB", pkt->buf[0]);
			    spi_addPacket(pkt);
			    break;
		    case led_toggle:
		        alarm_new(5, "LED %i toggle command issued from USB", pkt->buf[0]);
			    spi_addPacket(pkt);
		    break;
		    case led_status:
		        alarm_new(5, "LED %i status command issued from USB", pkt->buf[0]);
			    spi_addPacket(pkt);
		    break;
		    case led_report:
		        alarm_new(5, "LED %i report command issued from USB", pkt->buf[0]);
			    spi_addPacket(pkt);
		    break;
		    default:
		        alarm("LED reached an undefined subtask");
		    break;
	    }
	}		
}
