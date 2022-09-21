/*
 * interrupts.c
 *
 * Created: 9/14/2022 2:40:30 PM
 *  Author: Ahmed
 */ 
#include "interrupts.h"
void INT_init(){
	SEI();
	MCUCR |= (1<<0) | (1<<1);
	GICR |= (1<<6);
}
uint8_t GET_INT0(){
	return INT0_STATE;
}
void CLR_INT0(){
	INT0_STATE=0;
}
ISR(INT0){
	INT0_STATE=1;

}