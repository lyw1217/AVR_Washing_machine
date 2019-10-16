/*
 * buzzer.h
 *
 * Created: 2019-07-02 오후 5:16:18
 *  Author: LYW
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void buzzer_Init();
void setBuzzer(int note);
void stopBuzzer();
void playBuzzer();
void powerOnBuzzer();
void powerOffBuzzer();
void buttonBuzzer();
void finishBuzzer();

#endif /* BUZZER_H_ */