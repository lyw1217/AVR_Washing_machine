/*
* buzzer.c
*
* Created: 2019-07-02 오후 5:16:08
*  Author: LYW
*/

#include "buzzer.h"

#define C4	262	 // 도
#define D4	294	 // 레
#define E4	330  // 미
#define F4	349  // 파
#define F4S 370  // 파#
#define G4	392  // 솔
#define A4	440  // 라
#define B4	494  // 시
#define C5	523  // 도
#define D5	587	 // 레
#define E5	659  // 미
#define F5	698  // 파
#define G5	784  // 솔
#define A5	880  // 라
#define B5	987  // 시
#define C6	1046 // 도


void buzzer_Init(){
	DDRB |= (1 << PORTB6);
	TCCR1B |= (0<<CS12) | (1<<CS11) | (0<<CS10); // 분주비 8
	// CTC Mode
	TCCR1B |= (0<<WGM13) | (1<<WGM12);
	TCCR1B |= (0<<WGM11) | (0<<WGM11);
	// Toggle 출력
	TCCR1A |= (0<<COM1B1) | (1<<COM1B0);
	OCR1A = 1000;
}

/*
/ 주파수 값 입력 설정
/ ex) 1kHz 출력 : setSound(1000);
*/

void setBuzzer(int note){
	int ocr_value = 1000000 / note; // == ( F_CPU / 2 / PRESCALER / note )
	OCR1A = ocr_value;
}

void stopBuzzer(){
	TCCR1A &= ~((1<<COM1B1) | (1<<COM1B0));
}

void playBuzzer(){
	TCCR1A |= (0<<COM1B1) | (1<<COM1B0);
}

void powerOnBuzzer(){
	playBuzzer();
	setBuzzer(C4);
	_delay_ms(300);
	setBuzzer(E4);
	_delay_ms(300);
	setBuzzer(G4);
	_delay_ms(300);
	setBuzzer(C5);
	_delay_ms(300);
	stopBuzzer();
}

void powerOffBuzzer(){
	playBuzzer();
	setBuzzer(C5);
	_delay_ms(300);
	setBuzzer(G4);
	_delay_ms(300);
	setBuzzer(E4);
	_delay_ms(300);
	setBuzzer(C4);
	_delay_ms(300);
	stopBuzzer();
}

void buttonBuzzer(){
	playBuzzer();
	setBuzzer(C5);
	_delay_ms(50);
	setBuzzer(F4);
	_delay_ms(50);
	stopBuzzer();
}

void finishBuzzer(){
	playBuzzer();
	setBuzzer(G4);
	_delay_ms(200);
	
	setBuzzer(C5);
	_delay_ms(200);
	setBuzzer(C5);
	_delay_ms(200);
	
	setBuzzer(E5);
	_delay_ms(200);
	setBuzzer(E5);
	_delay_ms(200);
	
	setBuzzer(C5);
	_delay_ms(350);
	
	setBuzzer(G4);
	_delay_ms(200);
	setBuzzer(G4);
	_delay_ms(200);
	setBuzzer(G4);
	_delay_ms(350);
	
	setBuzzer(G4);
	_delay_ms(200);
	setBuzzer(A5);
	_delay_ms(200);
	setBuzzer(C5);
	_delay_ms(200);
	setBuzzer(B4);
	_delay_ms(200);
	setBuzzer(A4);
	_delay_ms(200);
	setBuzzer(G4);
	_delay_ms(350);
	
	setBuzzer(G4);
	_delay_ms(200);
	
	setBuzzer(C5);
	_delay_ms(200);
	setBuzzer(C5);
	_delay_ms(200);
	
	setBuzzer(E5);
	_delay_ms(200);
	setBuzzer(E5);
	_delay_ms(200);
	
	setBuzzer(C5);
	_delay_ms(350);
	
	setBuzzer(G4);
	_delay_ms(200);
	setBuzzer(C5);
	_delay_ms(200);
	
	setBuzzer(B4);
	_delay_ms(300);
	
	setBuzzer(A4);
	_delay_ms(200);
	setBuzzer(B4);
	_delay_ms(200);
	setBuzzer(C5);
	_delay_ms(300);
	
	setBuzzer(F4S);
	_delay_ms(200);
	setBuzzer(G4);
	_delay_ms(350);
	stopBuzzer();
}