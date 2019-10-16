/*
 * laundry.h
 *
 * Created: 2019-07-12 오후 7:07:46
 *  Author: LYW
 */ 


#ifndef LAUNDRY_H_
#define LAUNDRY_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint8_t wash_switch(uint8_t _washTime);
uint8_t rinse_switch(uint8_t _rinseTime);
uint8_t spin_switch(uint8_t _spinTime);
uint8_t reserve_Mode(uint8_t _reserveTime);
#endif /* LAUNDRY_H_ */