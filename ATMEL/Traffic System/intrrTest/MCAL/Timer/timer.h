/*
 * timer.h
 *
 * Created: 9/14/2022 3:06:40 PM
 *  Author: Ahmed
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "../../Utilities/types.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bitops.h"
#define us 0
#define ms 1
#define s 2
uint8_t selected_unit;
uint16_t selected_amount;
void timer_start(uint16_t amount, uint8_t unit);
uint8_t timer_check();


#endif /* TIMER_H_ */