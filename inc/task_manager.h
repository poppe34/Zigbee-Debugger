/*
 * task_manager.h
 *
 * Created: 3/10/2011 2:16:37 PM
 *  Author: matt
 */ 


#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_
#define BYTES_NEEDED_FOR_LENGTH 1

extern uint8_t buf_in[256];
extern uint8_t rxok;

uint8_t usb_send_ok;

EXTERNAL_LIST(packets);

typedef enum data_direction
{
    to_device = 1,
	from_device = 2,
	from_usb = 3,
	to_usb = 4
}dir_t;

//TODO: I want to add a pointer to the continued packet if the length is greater than 64
typedef struct packet
{
	struct packet       *next;
	uint8_t             buf[64];
	uint8_t             *ptr;
	uint8_t             dir;
	uint8_t             len;
	uint8_t             task;
	uint8_t             subTask;
	
}packet_t;

enum tasks
{
	task_LED = 0x01,
	task_alarm = 0x02,
	task_zigbee = 0x03,
};

void        TM_task_init(void);
void        TM_task(void);
void        TM_passPacket(packet_t *pkt, packet_t *newPkt);
packet_t *  TM_newPacket(void);
void        TM_toUSB(packet_t *pkt);
void        TM_fromUSB(uint8_t *buf);//TODO: I kinda want to make this a void type of buffer
void        TM_toDevice(packet_t *pkt);
void        TM_addPacket(packet_t *pkt);
void        TM_removeTask(packet_t *pkt);
void        TM_sendDummy(void);
void        TM_handler(packet_t *pkt);
void        TM_freePacket(packet_t *pkt);



#endif /* TASK_MANAGER_H_ */