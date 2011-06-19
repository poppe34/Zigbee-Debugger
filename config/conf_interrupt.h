/*
 * conf_interrupt.h
 *
 * Created: 3/3/2011 8:44:20 PM
 *  Author: matt
 */ 


#ifndef CONF_INTERRUPT_H_
#define CONF_INTERRUPT_H_

#include "interrupt_driver.h"
        
#define EXTERN_ASSIGN_INTERRUPT(vect) \
    extern irq_cb_t irq_##vect##_cb; \
    extern INLINE void set_##vect##_cb(irq_cb_t irq) {irq_##vect##_cb = irq;} \
    extern INLINE void release_##vect##_cb(void) {irq_##vect##_cb = NULL;} \
    extern INLINE Bool isSet_##vect##_cb(void) {return((irq_##vect##_cb != NULL) ? YES : NO);} \
    extern INLINE irq_cb_t get_##vect##_cb(void) {return irq_##vect##_cb;}
        

EXTERN_ASSIGN_INTERRUPT(PCINT0_vect);

#endif /* CONF_INTERRUPT_H_ */