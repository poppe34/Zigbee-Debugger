/*
 * IOPort.h
 *
 * Created: 3/2/2011 11:47:30 AM
 *  Author: matt
 */ 


#ifndef IOPORT_H_
#define IOPORT_H_

#include "compiler.h"

#define IOPORT_CREATE_PIN(port, pin) (port*8 + pin);

#define PORT_PORTA      (0)
#define PORT_PORTB      (1)
#define PORT_PORTC      (2)
#define PORT_PORTD      (3)
#define PORT_PORTE      (4)




#endif /* IOPORT_H_ */