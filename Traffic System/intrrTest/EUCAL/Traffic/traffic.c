/*
 * traffic.c
 *
 * Created: 9/14/2022 6:29:56 PM
 *  Author: Ahmed
 */ 
#include "traffic.h"
void traffic_init(){
traffic_state=READY;
traffic_color=RED;
color_direction=-1;
SET_BIT(DDRA,0);
SET_BIT(DDRA,1);
SET_BIT(DDRA,2);

SET_BIT(DDRB,0);
SET_BIT(DDRB,1);
SET_BIT(DDRB,2);
}

void LED(uint8_t *PORT,uint8_t COL, uint8_t SIM){
	
	if (COL==RED)
	{
		
		SET_BIT(*PORT,0);
		if (SIM==0){
			CLR_BIT(*PORT,1);
			CLR_BIT(*PORT,2);
		}
		
	}
	if (COL==YEL)
	{
		SET_BIT(*PORT,1);
		if (SIM==0){
			CLR_BIT(*PORT,0);
			CLR_BIT(*PORT,2);
		}
	}
	if (COL==GRE)
	{
		SET_BIT(*PORT,2);
		if (SIM==0){
			CLR_BIT(*PORT,0);
			CLR_BIT(*PORT,1);
		}
	}
	if (COL==BLANK)
	{
		CLR_BIT(*PORT,1);
		if (SIM==0){
			CLR_BIT(*PORT,0);
			CLR_BIT(*PORT,2);
		}
	}
}
void CAR_LED(uint8_t COL,uint8_t SIM){
	LED(&CAR,COL,SIM);
}
void PED_LED(uint8_t COL,uint8_t SIM){
	LED(&PED,COL,SIM);
}
void traffic_normal(){
	
	if (traffic_state==READY){
		
		if ((traffic_color == RED) ||  (traffic_color == GRE))
		{
			timer_start(5,s);
			
		}
		if ((traffic_color==YEL)||(traffic_color==BLANK))
		{
			
			timer_start(500,ms);
		}
	
		traffic_state=WAIT;
		
	}
		
		if (timer_check()==(10)){
			
			if ((traffic_color==YEL)||(traffic_color==BLANK)){
				blinker++;
				traffic_color = ((traffic_color==YEL)? BLANK:YEL);
				if (blinker==10){
					blinker=0;
					traffic_color=YEL;
				}
				
			}
			if (blinker==0){
			color_direction = (((traffic_color==RED)||(traffic_color==GRE))? (- color_direction ):color_direction);
			traffic_color += color_direction;
			}
			traffic_state=READY;
		}
	CAR_LED(traffic_color,0);	
}
void traffic_ped(uint8_t State,uint8_t Mode){
	mode=Mode;
	if (traffic_state==READY || State==READY){
		State=WAIT;
	if (traffic_color==RED){
		timer_start(5,s);
		PED_LED(GRE,0);
		CAR_LED(RED,0);
		mode=Pedmode;
	}
	if ((traffic_color==YEL)||(traffic_color==BLANK)){
		timer_start(500,ms);
		CAR_LED(traffic_color,0);
		if (mode==Normal){PED_LED(RED,0);color_direction=-1;}
		
		
	}
	if ((traffic_color==GRE)){
		if (mode==Normal){PED_LED(RED,0);}
		PED_LED(RED,0);
		if (mode==Pedmode){
		CLR_INT0();
		return 0;}
	}
	traffic_state=WAIT;
	}
	if (timer_check()==(10)){
		if ((traffic_color==YEL)||(traffic_color==BLANK)){
			
			blinker++;
			traffic_color = ((traffic_color==YEL)? BLANK:YEL);
			if (blinker>=10){
				blinker=0;
				traffic_color=YEL;
			}
			
		}
		if (blinker==0){
			
			color_direction = (((traffic_color==RED)||(traffic_color==GRE))? (- color_direction ):color_direction);
			traffic_color += color_direction;
		}
		traffic_state=READY;
	}
	
	//if(blinker>0){PED_LED(traffic_color,1);}
	if (blinker>0){PED_LED(traffic_color,1);CAR_LED(traffic_color,1);}
}