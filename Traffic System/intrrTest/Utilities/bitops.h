/*
 * bitops.h
 *
 * Created: 9/13/2022 6:54:05 PM
 *  Author: Ahmed
 */ 


#ifndef BITOPS_H_
#define BITOPS_H_

#define SET_BIT(PORT,PIN)  (PORT |= (1<<PIN))
#define CLR_BIT(PORT,PIN)  (PORT &= ~(1<<PIN))
#define GET_BIT(PORT,PIN)  ((PORT & (1<<PIN))>>PIN)



#endif /* BITOPS_H_ */