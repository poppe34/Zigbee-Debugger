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
static uint8_t delay_flag;


packet_t dummy_packet;
LIST(spi_output);

void spi_task_init(void)
{
	dummy_packet.len = 0;
	inactive_count = 0;
    delay_flag = 0;
	
	
	list_init(spi_output);
	spi_enable();
    
	GPIO_XMEGA_IRQ_set();
	GPIO_RESET_LIGHT_make_out();
  
    PCMSK0 |= _BV(PCINT0);
	PCICR |= _BV(PCIE0);

    spi_active = NO;
	set_PCINT0_vect_cb(&spi_startOfCB);
	
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
void spi_writeMaster_cb(void)
{
 
    uint8_t len;
	packet_t *packet;
    uint8_t to_num = 0;
	inactive_count = 0;
	uint8_t count = 0;
	delay_flag = 0;

	packet = (packet_t *)list_pop(spi_output);
	packet->ptr = packet->buf;

	len = packet->len;

    if(packet)
	{
	    SPDR = packet->len;
	    WAIT_FOR_DATA_SLAVE;

	    SPDR = packet->task;	
	    WAIT_FOR_DATA_SLAVE;

	    SPDR = packet->subTask;
	    WAIT_FOR_DATA_SLAVE;
	    
	    while(len != count)
	    {
	        SPDR = *packet->ptr++;
		    WAIT_FOR_DATA_SLAVE;
		    //TODO: add the code to keep the packet if we do have a timeout and make sure we don't delete out of spi_output list
		    count++;
	    }


	     
	}		
	GPIO_XMEGA_IRQ_set();
	spi_freePacket(packet);
	inactive_count = 0;
	spi_active = NO;

}

void spi_addPacket(packet_t *pkt)
{
	packet_t *newpkt = spi_newPacket();
	if(newpkt)
	    TM_passPacket(pkt, newpkt);
	else
	    alarm("SPI_addPacket did not receive a valid packet");
}
void spi_readMaster_cb(void)
{
	uint8_t len, once = 0, to_num, count = 1;
	uint16_t delay;
	packet_t *pkt = TM_newPacket();
	delay_flag = 0;

	if(pkt)
	{	
	    pkt->dir = from_device;
	
	    WAIT_FOR_DATA_SLAVE;
	    pkt->len = SPDR;

	
	    len = pkt->len;
			
	    WAIT_FOR_DATA_SLAVE;
	    pkt->task = SPDR;

	
	    WAIT_FOR_DATA_SLAVE;
	    pkt->subTask = SPDR;

	 
	    while(len)
	    {
	        WAIT_FOR_DATA_SLAVE;
	        *pkt->ptr++ = SPDR;
		    len--;
	    }		
	}
	else
	{
		alarm("I didn't get a new packet to read SPI Master");
	}
	spi_active = NO;

	inactive_count = 0;
}

void spi_startOfCB(void)
{   
	cli();
	uint8_t display = 0x11;

	WAIT_FOR_DATA_SLAVE;
	display = SPDR;
	
/*	if(display == 0xff | display == 0 | display == 0x11)
	{
 //       alarm_new(5, "SPI Read received an invalid packet %i", display);
		spi_active = NO;
		sei();
	    return;
	}
	*/

	if(display == 0x88)
		spi_writeMaster_cb();		
	else if(display == 0xaa)
	    spi_readMaster_cb();
		
	sei();
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

void spi_freePacket(packet_t *pkt)
{
	list_remove(spi_output, pkt);
	free(pkt);
}