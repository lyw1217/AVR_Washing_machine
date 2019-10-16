/*
 * main.h
 *
 * Created: 2019-07-10 오전 9:21:35
 *  Author: LYW
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include "button.h"
#include "buzzer.h"
#include "lcd.h"
#include "time.h"
#include "DCMotor.h"
#include "DS1302.h"
#include "LED.h"
#include "laundry.h"

#endif /* MAIN_H_ */