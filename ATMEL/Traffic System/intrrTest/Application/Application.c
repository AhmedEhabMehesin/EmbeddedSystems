/*
 * Application.c
 *
 * Created: 9/14/2022 10:28:05 PM
 *  Author: Ahmed
 */ 
#include "Application.h"
void APP_init(){
	INT_init();
	traffic_init();
	
}
void APP_run(){
	uint8_t Turn;
	while (1)
	{
		if (GET_INT0()==1){
			
			if (Turn==0)
			{
				Turn=1;
				traffic_ped(READY,Normal);
			}
			
			traffic_ped(WAIT,mode);
		}
		else{traffic_normal(); Turn=0;}
		
	}
}