/*
* LED.c
*
* Created: 2019-07-12 오후 6:29:27
*  Author: LYW
*/

#include "LED.h"

void led_Init(){
	DDRF = 0xff;
	DDRG = 0b00000111; // LED 초기화
	
	PORTF = 0xff;
	PORTG = 0b00000111; // ALL LED ON
	_delay_ms(500);
	
	PORTF &= (1 << PORTF1) | (1 << PORTF3) | (1 << PORTF5);
	PORTG &= (1 << PORTG1); // ALL LED OFF except power led, default led
}

void led_Off(){
	PORTF = 0x00;
	PORTG = 0x00;
}

void wash_LED_switch(){
	uint8_t state = 0;
	
	if((PORTF & (1<<PORTF2)) == (1<<PORTF2)){
		PORTF |= (1 << PORTF3);
		PORTF &= ~(1 << PORTF2);
	}
	else if((PORTF & (1<<PORTF3)) == (1<<PORTF3)){
		PORTF |= (1 << PORTF4);
		PORTF &= ~(1 << PORTF3);
	}
	else if((PORTF & (1<<PORTF4)) == (1<<PORTF4)){
		PORTF &= ~(1 << PORTF4);
		state = 1;
	}
	else if(state = 1){
		PORTF |= (1 << PORTF2);
		state = 0;
	}
}

void rinse_LED_switch(){
	uint8_t state = 0;
	
	if((PORTF & (1<<PORTF5)) == (1<<PORTF5)){
		PORTF |= (1 << PORTF6);
		PORTF &= ~(1 << PORTF5);
	}
	else if((PORTF & (1<<PORTF6)) == (1<<PORTF6)){
		PORTF |= (1 << PORTF7);
		PORTF &= ~(1 << PORTF6);
	}
	else if((PORTF & (1<<PORTF7)) == (1<<PORTF7)){
		PORTF &= ~(1 << PORTF7);
		state = 1;
	}
	else if(state = 1){
		PORTF |= (1 << PORTF5);
		state = 0;
	}
}

void spin_LED_switch(){
	if(PORTG == (1<<PORTG0))			{PORTG = (1 << PORTG1);}
	else if(PORTG == (1<<PORTG1))		{PORTG = (1 << PORTG2);}
	else if(PORTG == (1<<PORTG2))		{PORTG = 0;}
	else if(PORTG == 0)					{PORTG = (1<<PORTG0);}
}