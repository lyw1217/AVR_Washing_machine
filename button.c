/*
 * button.c
 *
 * Created: 2019-07-02 오후 6:45:01
 *  Author: LYW
 */ 

#include "button.h"

void button_Init(){
	DDR_BUTTON &= ~((1<<RUN_BUTTON) | (1<<WASH_BUTTON) | (1<<RINSE_BUTTON) | (1<<SPIN_BUTTON) | (1<<RESERV_BUTTON) | (1<<POWER_BUTTON));
}

// 버튼이 눌리면 1을 리턴, 눌리지 않으면 0을 리턴

uint8_t wash_Bt_State(){
	static uint8_t prevState2 = 1; // static을 선언하면 전역변수처럼, 처음만 설정되고 다음부터는 기존 값을 그대로 사용한다.
	
	_delay_ms(10); // 채터링 예방
	
	if(((PIN_BUTTON & (0x01 << WASH_BUTTON)) == 0) && (prevState2 == 1)){ // 버튼 close 이면서 prevState == 1 --> 버튼이 처음 눌린 상태
		prevState2 = 0;
		return 0;
	}
	else if (((PIN_BUTTON & (0x01 << WASH_BUTTON)) == (0x01 << WASH_BUTTON)) && (prevState2 == 0)){ // 버튼이 open 이면서 prevState == 0 --> 버튼이 처음 눌렸다가 떼졌을 때
		prevState2 = 1;
		return 1;
	}
	return 0;
}

uint8_t rinse_Bt_State(){
	static uint8_t prevState3 = 1; // static을 선언하면 전역변수처럼, 처음만 설정되고 다음부터는 기존 값을 그대로 사용한다.
	
	_delay_ms(10); // 채터링 예방
	
	if(((PIN_BUTTON & (0x01 << RINSE_BUTTON)) == 0) && (prevState3 == 1)){ // 버튼 close 이면서 prevState == 1 --> 버튼이 처음 눌린 상태
		prevState3 = 0;
		return 0;
	}
	else if (((PIN_BUTTON & (0x01 << RINSE_BUTTON)) == (0x01 << RINSE_BUTTON)) && (prevState3 == 0)){ // 버튼이 open 이면서 prevState == 0 --> 버튼이 처음 눌렸다가 떼졌을 때
		prevState3 = 1;
		return 1;
	}
	return 0;
}

uint8_t spin_Bt_State(){
	static uint8_t prevState4 = 1; // static을 선언하면 전역변수처럼, 처음만 설정되고 다음부터는 기존 값을 그대로 사용한다.
	
	_delay_ms(10); // 채터링 예방
	
	if(((PIN_BUTTON & (0x01 << SPIN_BUTTON)) == 0) && (prevState4 == 1)){ // 버튼 close 이면서 prevState == 1 --> 버튼이 처음 눌린 상태
		prevState4 = 0;
		return 0;
	}
	else if (((PIN_BUTTON & (0x01 << SPIN_BUTTON)) == (0x01 << SPIN_BUTTON)) && (prevState4 == 0)){ // 버튼이 open 이면서 prevState == 0 --> 버튼이 처음 눌렸다가 떼졌을 때
		prevState4 = 1;
		return 1;
	}
	return 0;
}

uint8_t reserv_Bt_State(){
	static uint8_t prevState5 = 1; // static을 선언하면 전역변수처럼, 처음만 설정되고 다음부터는 기존 값을 그대로 사용한다.
	
	_delay_ms(10); // 채터링 예방
	
	if(((PIN_BUTTON & (0x01 << RESERV_BUTTON)) == 0) && (prevState5 == 1)){ // 버튼 close 이면서 prevState == 1 --> 버튼이 처음 눌린 상태
		prevState5 = 0;
		return 0;
	}
	else if (((PIN_BUTTON & (0x01 << RESERV_BUTTON)) == (0x01 << RESERV_BUTTON)) && (prevState5 == 0)){ // 버튼이 open 이면서 prevState == 0 --> 버튼이 처음 눌렸다가 떼졌을 때
		prevState5 = 1;
		return 1;
	}
	return 0;
}

uint8_t power_Bt_State(){
	static uint8_t prevState6 = 1; // static을 선언하면 전역변수처럼, 처음만 설정되고 다음부터는 기존 값을 그대로 사용한다.
	
	_delay_ms(10); // 채터링 예방
	
	if(((PIN_BUTTON & (0x01 << POWER_BUTTON)) == 0) && (prevState6 == 1)){ // 버튼 close 이면서 prevState == 1 --> 버튼이 처음 눌린 상태
		prevState6 = 0;
		return 0;
	}
	else if (((PIN_BUTTON & (0x01 << POWER_BUTTON)) == (0x01 << POWER_BUTTON)) && (prevState6 == 0)){ // 버튼이 open 이면서 prevState == 0 --> 버튼이 처음 눌렸다가 떼졌을 때
		prevState6 = 1;
		return 1;
	}
	return 0;
}