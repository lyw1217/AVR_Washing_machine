/*
 * time.h
 *
 * Created: 2019-07-02 오전 10:29:38
 *  Author: LYW
 */ 


#ifndef TIME_H_
#define TIME_H_

#include "main.h"

void timer0_Init(void);
void incMilliSec(void);
uint32_t millis(void);
void incTime(void);
void st_incMilliSec(void);
uint32_t st_millis(void);
void showTime();
void stRun();
void stStop();
void stIdle();
void showStwatch();
uint8_t getDayofWeek(uint16_t year, uint8_t month, uint8_t day);
uint16_t leapYear(uint16_t year);
#endif /* TIME_H_ */