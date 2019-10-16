/*
 * DCMotor.h
 *
 * Created: 2019-07-05 오후 5:24:03
 *  Author: kccistc
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOTOR_CLOCK		OCR3A
#define MOTOR_ANTICLOCK	OCR3B
void DC_Motor_Init();
void DCMotorStop();
void DCMotor_Spin(uint8_t _clockspeed, uint8_t _anticlockspeed);
void DCMotor_Washmode(uint8_t _timer);
void DCMotor_Rinsemode(uint8_t _timer);
void DCMotor_Spinmode();

#endif /* DCMOTOR_H_ */