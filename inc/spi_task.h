/*
 * USBspi_task.h
 *
 *  Created on: Feb 28, 2011
 *      Author: mattpoppe
 */

#ifndef USBSPI_TASK_H_
#define USBSPI_TASK_H_

#include "compiler.h"
#include "lists.h"
#include "debugger_task.h"
#include "task_manager.h"

typedef enum
{
	spi_notInit = 0x00,
	spi_idle = 0x01,
	spi_from_master = 0x02,
	spi_to_master = 0x03,
}spi_direction_t;

void spi_task_init(void);
void spi_informMaster(void);
void spi_send_alarm(char *inx);
void spi_writeMaster_cb(void);
void spi_readMaster_cb(void);
void spi_IRQ_CB(void);
void spi_addPacket(packet_t *pkt);
void spi_startOfCB(void);
packet_t *spi_newPacket(void);
void spi_freePacket(packet_t *pkt);
void spi_readByte_CB(void);
void spi_writeByte_CB(void);
#endif /* USBSPI_TASK_H_ */
