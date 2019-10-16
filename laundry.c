/*
 * laundry.c
 *
 * Created: 2019-07-12 오후 7:07:17
 *  Author: LYW
 */ 

#include "laundry.h"
#include "LED.h"

uint8_t wash_switch(uint8_t _washTime){
	wash_LED_switch();
	_washTime++;
	if(_washTime > 3){
		_washTime = 0;
	}
	return _washTime;
}

uint8_t rinse_switch(uint8_t _rinseNum){
	rinse_LED_switch();
	_rinseNum++;
	if(_rinseNum > 3){
		_rinseNum = 0;
	}
	return _rinseNum;
}

uint8_t spin_switch(uint8_t _spinTime){
	spin_LED_switch();
	_spinTime++;
	if(_spinTime > 3){
		_spinTime = 0;
	}
	return _spinTime;
}

uint8_t reserve_Mode(uint8_t _reserveTime){
	_reserveTime++;
	if(_reserveTime > 3){
		_reserveTime = 0;
	}
	return _reserveTime;
}