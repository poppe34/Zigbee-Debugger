                   /*
 * spi_task.c
 *
 * Created: 3/4/2011 10:42:13 AM
 *  Author: matt
 */ 

#include "config.h"
#include "spi.h"
#include "spi_task.h"
#include "conf_interrupt.h"
#include "avr/io.h"
#include "task_manager.h"
#include "lists.h"
#include "util/delay.h"
#include "alarm_task.h"

static uint8_t spi_active;
static uint16_t inactive_count;
static packet_t *currentPkt;

static uint8_t estLength;

packet_t dummy_packet;
LIST(spi_output);

void spi_task_init(void)
{
	dummy_packet.len = 0;
	inactive_count = 0;
   
	
	
	list_init(spi_output);
	spi_enable();
    
	GPIO_XMEGA_IRQ_set();
	GPIO_RESET_LIGHT_make_out();

	PCMSK0 |= (_BV(PCINT0));
	PCICR |= (_BV(PCIE0));



    spi_active = NO;
	set_PCINT0_vect_cb(&spi_writeByte_CB);
	
	set_SPI_STC_vect_cb(&spi_startOfCB);
	
	SPCR |= _BV(SPIE);
}

void spi_task(void)
{
	uint8_t length = list_length(spi_output);
	
	if(length == 9)
		alarm("spi output stack size is to large");
	
	if(length)
	{
	    if(spi_active == NO)
		{
			packet_t *pkt = list_head(spi_output);
	        spi_informMaster();

			inactive_count = 0;	
		}			
		else
		    inactive_count++;
	}
	else
	{
		inactive_count = 0;
	}	
	if(inactive_count >= 5000)
	{
	    spi_active = NO;
//		alarm("SPI send Timed Out");
		inactive_count = 0;


	}		

}
void spi_informMaster(void)
{
	spi_active = YES;
	GPIO_XMEGA_IRQ_clr();

}


void spi_addPacket(packet_t *pkt)
{
	packet_t *newpkt = spi_newPacket();
	if(newpkt)
	    TM_passPacket(pkt, newpkt);
	else
	    alarm("SPI_addPacket did not receive a valid packet");
}

packet_t *spi_newPacket(void)
{
	packet_t *newPkt;
	
	if(list_length(spi_output) <= 10)
	{
		newPkt = (packet_t *)malloc(sizeof(packet_t));
		list_add(spi_output, newPkt);		
	}
	else
	{
		newPkt == NULL;
		alarm("Exceded the alotment of spi Packets");
	}
	return newPkt;
}

void spi_startOfCB(void)
{   
	//Direction 0 is writing 
	//			1 is reading
	//Get a new Packet
	
	currentPkt = TM_newPacket(NO);
	
	if(currentPkt)
	{
		
		uint8_t display = SPDR;
		estLength = 0;
		if(display == 0x88)
		{
			currentPkt->dir = from_device;
			set_SPI_STC_vect_cb(&spi_writeByte_CB);
		}				
		else if(display == 0xaa)
		{
			currentPkt->dir = from_device;
			set_SPI_STC_vect_cb(&spi_readByte_CB);
		}
	}				
}

void spi_freePacket(packet_t *pkt)
{
	if(pkt)
	{
		list_remove(spi_output, pkt);
		free(pkt);
	}		
}

void spi_readByte_CB(void)
{
	if(currentPkt)
	{	
		if(estLength == 0)
		{
			currentPkt->len = SPDR;
			estLength = currentPkt->len;
		
			currentPkt->ptr = &currentPkt->task;
		}
		else
		{
			*currentPkt->ptr++ = SPDR;
			estLength--;
			if(estLength == 0)
			{
			
			
			}
		}
	}		
}

void spi_writeByte_CB(void)
{
	if(GPIO_XMEGA_SS_read() == 1){
		if(currentPkt)
		{
			TM_addPacket(currentPkt);
		}			
		currentPkt = NULL;
		set_SPI_STC_vect_cb(&spi_startOfCB);
	}
}
