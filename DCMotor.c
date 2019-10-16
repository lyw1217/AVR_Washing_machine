/*
* DC_Motor.c
*
* Created: 2019-07-05 오후 5:23:41
*  Author: LYW
*/

#include "DCMotor.h"

#define MOTOR_SPEED			100	// 세탁조의 무게에 따라 달라질 수 있음
#define MOTOR_SPIN_SPEED	200

void DC_Motor_Init(){
	// PE 3,4번에 DC모터 연결, 출력으로 사용
	DDRE |= (1<<DDRE3) | (1<<DDRE4);

	// 8비트 고속 PWN 설정(p.348), TOP : 255(0xff)
	TCCR3A |= (0 << WGM31) | (1 << WGM30);
	TCCR3B |= (0 << WGM33) | (1 << WGM32);

	// cs3n 0,1,1 => 8 분주비 / 약 7.8kHz 주기(계산법 = F_CPU/prescale/top)
	TCCR3B |= (0 << CS32) | (1 << CS31) | (0 << CS30);
	// OC3A, OC3B 비반전모드 FastPWM 사용(p.350)
	// A, B 출력핀 전부 설정 -> datasheet를 보고 핀이 무엇인지 확인
	// COMnx 비트를 설정해주면 출력을 설정해주는 것
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0) | (1<<COM3B1) | (0<<COM3B0);
}

void DCMotorStop(){
	MOTOR_ANTICLOCK = 0;
	MOTOR_CLOCK = 0;
}

void DCMotor_Spin(uint8_t _clockspeed, uint8_t _anticlockspeed){
	
	if(_clockspeed > 255) _clockspeed = 255;
	else if(_clockspeed < 0) _clockspeed = 0;
	
	if(_anticlockspeed > 255) _anticlockspeed = 255;
	else if(_anticlockspeed < 0) _anticlockspeed = 0;
	
	MOTOR_ANTICLOCK = _anticlockspeed;
	MOTOR_CLOCK = _clockspeed;
}

void DCMotor_Washmode(uint8_t _timer){
	// 좌,우 번갈아가며 돌아야함
	static uint8_t clockwise = 0, anticlockwise = MOTOR_SPEED;
	static uint8_t count = 0;
	
	// 5초 단위가 되었을 때 그 1초 동안 방향이 계속 바뀌는 것을 방지하기 위해
	if(((_timer % 5) - 1) == 0){ // 5초 단위에서 1초 전에
		count = 0; // count를 0으로 바꿔줘서 조건문에 들어갈 수 있게 한다
	}
	
	if(((_timer % 5) == 0) && (clockwise == 0) && (count == 0)){
		clockwise = MOTOR_SPEED;
		anticlockwise = 0;
		count = 1;
	}
	else if(((_timer % 5) == 0) && (anticlockwise == 0) && (count == 0)){
		clockwise = 0;
		anticlockwise = MOTOR_SPEED;
		count = 1;
	}
	DCMotor_Spin(clockwise, anticlockwise);
}

void DCMotor_Rinsemode(uint8_t _timer){
	// 좌,우 번갈아가며 돌아야함
	static uint8_t clockwise = 0, anticlockwise = MOTOR_SPEED;
	static uint8_t count = 0;
	
	// 5초 단위가 되었을 때 그 1초 동안 방향이 계속 바뀌는 것을 방지하기 위해
	if(((_timer % 5) - 1) == 0){ // 5초 단위에서 1초 전에
		count = 0; // count를 0으로 바꿔줘서 조건문에 들어갈 수 있게 한다
	}
	
	if(((_timer % 5) == 0) && (clockwise == 0) && (count == 0)){
		clockwise = MOTOR_SPEED;
		anticlockwise = 0;
		count = 1;
		_delay_ms(1000);
	}
	else if(((_timer % 5) == 0) && (anticlockwise == 0) && (count == 0)){
		clockwise = 0;
		anticlockwise = MOTOR_SPEED;
		count = 1;
		_delay_ms(1000);
	}
	DCMotor_Spin(clockwise, anticlockwise);
}

void DCMotor_Spinmode(){
	// 한 방향으로 빠르게
	static uint8_t anticlockwise = MOTOR_SPIN_SPEED;

	DCMotor_Spin(0, anticlockwise);
}
