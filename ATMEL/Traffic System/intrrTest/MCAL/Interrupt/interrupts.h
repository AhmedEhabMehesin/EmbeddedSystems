/*
 * interrupts.h
 *
 * Created: 9/13/2022 6:44:50 PM
 *  Author: Ahmed
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include "../../Utilities/registers.h"
#include "../../Utilities/bitops.h"
#define INT0 __vector_1
#define INT1 __vector_2
#define INT2 __vector_3

#define SEI() SET_BIT(SREG,7)
#define CLI() CLR_BIT(SREG,7)

#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)
//
uint8_t INT0_STATE;
void INT_init();
uint8_t GET_INT0();
void CLR_INT0();
#endif /* INTERRUPTS_H_ */