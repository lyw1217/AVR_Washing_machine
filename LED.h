/*
 * LED.h
 *
 * Created: 2019-07-12 오후 6:34:32
 *  Author: LYW
 */ 


#ifndef LED_H_
#define LED_H_
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void led_Init();
void led_Off();
void wash_LED_switch();
void rinse_LED_switch();
void spin_LED_switch();

#endif /* LED_H_ */