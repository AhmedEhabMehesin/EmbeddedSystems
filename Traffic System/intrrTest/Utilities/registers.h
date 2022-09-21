/*
 * registers.h
 *
 * Created: 9/13/2022 6:47:47 PM
 *  Author: Ahmed
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_
// including types to use uint8_t type
#include "types.h"

//Interrupt Registers
#define SREG *((volatile uint8_t*) 0x5F)
#define MCUCSR *((volatile uint8_t*) 0x54)
#define MCUCR *((volatile uint8_t*) 0x55)
#define GIFR *((volatile uint8_t*) 0x5A)
#define GICR *((volatile uint8_t*) 0x5B)
//Timer Registers
#define TIFR *((volatile uint8_t*) 0x58)
#define TCCR0 *((volatile uint8_t*) 0x53)
#define TCNT0 *((volatile uint8_t*) 0x52)
//Data Direction Registers
#define DDRA *((volatile uint8_t*) 0x3A)
#define DDRB *((volatile uint8_t*) 0x37)
#define DDRC *((volatile uint8_t*) 0x34)
#define DDRD *((volatile uint8_t*) 0x31)
//PORT Registers
#define PORTA *((volatile uint8_t*) 0x3B)
#define PORTB *((volatile uint8_t*) 0x38)
#define PORTC *((volatile uint8_t*) 0x35)
#define PORTD *((volatile uint8_t*) 0x32)
//PIN Registers
#define PINA *((volatile uint8_t*) 0x39)
#define PINB *((volatile uint8_t*) 0x36)
#define PINC *((volatile uint8_t*) 0x33)
#define PIND *((volatile uint8_t*) 0x30)
//



#endif /* REGISTERS_H_ */