/*
 * button.h
 *
 * Created: 2019-07-02 오후 6:45:09
 *  Author: LYW
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DDR_BUTTON		DDRD
#define PIN_BUTTON		PIND
#define WASH_BUTTON		PIND4
// PD3은 왜 안되지??
#define RINSE_BUTTON	PIND5
#define SPIN_BUTTON		PIND6
#define RESERV_BUTTON	PIND2
// 외부 인터럽트를 위해
#define POWER_BUTTON	PIND0
#define RUN_BUTTON		PIND1
 
void button_Init();
uint8_t run_Bt_State();
uint8_t wash_Bt_State();
uint8_t rinse_Bt_State();
uint8_t spin_Bt_State();
uint8_t reserv_Bt_State();
uint8_t power_Bt_State();



#endif /* BUTTON_H_ */