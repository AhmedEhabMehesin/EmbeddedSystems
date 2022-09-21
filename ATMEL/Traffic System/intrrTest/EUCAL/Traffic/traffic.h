/*
 * traffic.h
 *
 * Created: 9/14/2022 6:22:33 PM
 *  Author: Ahmed
 */ 


#ifndef TRAFFIC_H_
#define TRAFFIC_H_
#include "../../MCAL/Timer/timer.h"

#define READY 1
#define WAIT 2

#define RED 1
#define YEL 2
#define GRE 3
#define BLANK 4
#define CAR PORTA
#define PED PORTB
#define Normal 1
#define Pedmode 2
uint8_t mode;
uint8_t blinker;
char color_direction;
uint8_t static traffic_color;
uint8_t static traffic_state;
void LED(uint8_t *PORT,uint8_t COL, uint8_t SIM);
void traffic_init();
void traffic_normal();
void traffic_ped(uint8_t State,uint8_t Mode);
void traffic_read();


#endif /* TRAFFIC_H_ */