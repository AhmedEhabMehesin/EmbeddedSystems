/*
 * timer.c
 *
 * Created: 9/14/2022 3:18:07 PM
 *  Author: Ahmed
 */ 
#include "timer.h"
uint8_t initial=0;
uint32_t overflows=0;
uint32_t ofcounter=0;
void calc(uint16_t amount, uint8_t unit){
	uint32_t us_amount=1;
	us_amount=((unit==ms)? 1000:us_amount);
	us_amount=((unit==s)?  1000000:us_amount);
	us_amount *= amount;
	overflows=((us_amount)/(256))+1;
	initial=256-(us_amount % 256);
	
}
void timer_start(uint16_t amount, uint8_t unit){
	calc(amount,unit);
	TCCR0=0;
	ofcounter=0;
	TIFR |=(1<<0);
	TCNT0=initial;
	TCCR0=1;
}
uint8_t timer_check(){
	
	if ((TIFR & (1<<0))==1){
		if (ofcounter==overflows){
			ofcounter=0;
			TCCR0=0;
			return (10);
		}
		TIFR |=(1<<0);
		ofcounter++;
		return (0);
	}
}