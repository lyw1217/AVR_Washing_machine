/*
 * lcd.h
 *
 * Created: 2019-07-02 오후 2:11:27
 *  Author: LYW
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT_DATA		PORTA
#define PORT_CONTROL	PORTB
#define DDR_DATA		DDRA
#define DDR_CONTROL		DDRB

#define RS_PIN			0
#define RW_PIN			2
#define E_PIN			3

#define COMMAND_CLEAR_DISPLAY	0x01
#define COMMAND_8_BIT_MODE		0x38	// 8비트, 2라인, 5x8폰트
#define COMMAND_4_BIT_MODE		0x28	// 4비트, 2라인, 5x8폰트

#define COMMAND_DISPLAY_ON_OFF_BIT		2
#define COMMAND_CURSOR_ON_OFF_BIT		1
#define COMMAND_BLINK_ON_OFF_BIT		0

void LCD_pulse_enable();
void LCD_write_data(uint8_t data);
void LCD_write_command(uint8_t command);
void LCD_clear();
void LCD_init();
void LCD_write_string(char *string);
void LCD_goto_XY(uint8_t row, uint8_t col);
void LCD_write_XY_string(uint8_t row, uint8_t col, char *string);


#endif /* LCD_H_ */