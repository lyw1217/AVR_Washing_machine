/*
* Washing_machine.c
*
* Created: 2019-07-10 오전 9:20:10
* Author : LYW
*/

#include "main.h"

volatile enum {POWERON, POWEROFF} powerState;
volatile enum {RUN, STANDBY, RESERVE, PAUSE} workState;
volatile enum {FINISH_WASH, FINISH_RINSE, FINISH_SPIN, FINISH_STANDBY} finishState;

void INT0_Init(){
	EIMSK |= (1 << INT0) | (1 << INT1);    // INT0 인터럽트 활성화
	EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);    // 하강 엣지에서 인터럽트 발생
	
	// sleep 모드 활성화
	MCUCR |= (1<<SE);
}

// 파워 버튼 외부 인터럽트(전원 ON/OFF)
ISR(INT0_vect){
	_delay_ms(10);
	
	// 전원 켜진 상태에서 전원버튼 눌렀을 때
	if(powerState == POWERON)
	{
		powerState = POWEROFF;
		DCMotorStop();			// 세탁기 우선 정지
		powerOffBuzzer();		// 전원 꺼짐 부저 울리기
		LCD_write_XY_string(0, 0, "   POWER OFF    ");	// LCD 출력
		LCD_write_XY_string(1, 0, "     Bye..      ");
		_delay_ms(1500);
		LCD_clear();
		PORTF = 0x00;
		PORTG = 0x00; // ALL LED OFF
		
		// STANDBY 슬립모드
		MCUCR |= (1<<SE);
		MCUCR |= (0 << SM0) | (1 << SM1) | (1 << SM2);
		
		// 딜레이가 없으면 잠깐 LCD가 표시됨
		_delay_ms(1000);
	}
	// 전원 꺼진 상태에서 전원버튼 눌렀을 때
	else if(powerState == POWEROFF)
	{
		// 재시작(리셋)
		wdt_enable(WDTO_60MS);	// 60ms 후 워치도그 타이머 리셋
		while(1);				// 리셋까지 대기
	}
	// 채터링 예방
	EIFR |= 0x01;
	_delay_ms(10);
}


// 동작 버튼 외부 인터럽트(일시정지 기능)
ISR(INT1_vect){
	_delay_ms(10);
	buttonBuzzer();
	if(workState == STANDBY){
		workState = RUN;
	}
	else if(workState == RUN)
	{
		workState = PAUSE;
	}
	else if(workState == PAUSE && ((PINC & (0x01 << PINC5)) == (0x01 << PINC5)))
	{
		// 문 열림 감지
		workState = RUN;
	}
	
	// 채터링 예방
	EIFR |= 0x02;
	_delay_ms(10);
}

int main(void)
{
	LCD_init();
	// LCD backlight ON
	PORTB |= (1<<PORTB1);
	LCD_write_XY_string(0, 0, "INITIALIZING...");
	DS1302_Init();
	led_Init();
	button_Init();
	buzzer_Init();
	DC_Motor_Init();
	INT0_Init();
	
	// 전원 꺼짐 시 LCD backlight OFF
	DDRB |= (1<<DDRB1);
	
	// 문 열림 감지
	DDRC &= ~(1<<PINC5);
	
	sei();
	
	uint8_t prevSec = 0, prevSec2 = 0, timer = 0;
	uint8_t washTimeSet[] = {0, 11, 21, 31};
	uint8_t spinTimeSet[] = {0, 6, 11, 16};
	uint8_t reserveTimeSet[] = {80, 100, 120, 0};
	// 기본 동작 설정 값
	uint8_t washTime = 2, rinseTime = 10, spinTime = 2;
	uint8_t workCount = 0;
	uint8_t reserveTime = 0;
	uint8_t tot_time = 0;
	uint8_t rinseNum = 1;
	
	char buff[20];
	
	powerState = POWERON;
	workState = STANDBY;
	finishState = FINISH_STANDBY;
	
	powerOnBuzzer();
	LCD_write_XY_string(0, 0, "  <>WELCOME!<>  ");
	LCD_write_XY_string(1, 0, "  ............  ");
	_delay_ms(1000);
	LCD_clear();
	
	while (1)
	{
		DS1302_GetTime(&stTime);
		DS1302_GetDate(&stTime);
		switch(powerState){
			// 전원 켜진 이후 동작부
			case POWERON:
						
			if(prevSec != stTime.seconds){
				// 현재 시간 보여주기
				if(workState == STANDBY) showTime();
				prevSec = stTime.seconds;
			}
			
			// 문 열림 감지(동작 상태에서 문 열림이 감지되면)
			if((workState == RUN) && (PINC & (0x01 << PINC5)) == 0){
				LCD_write_XY_string(0,0,"Plz,  Close Door");
				workState = PAUSE;
			}
			
			switch (workState){
				case STANDBY:
				//	전원 켜진 상태에서 버튼 눌렀을 시, 스탠바이 상태에서
				if((wash_Bt_State() == 1)){
					buttonBuzzer();
					washTime = wash_switch(washTime);
				}
				else if((rinse_Bt_State() == 1)){
					buttonBuzzer();
					rinseNum = rinse_switch(rinseNum);
				}
				else if((spin_Bt_State() == 1)){
					buttonBuzzer();
					spinTime = spin_switch(spinTime);
				}
				else if((reserv_Bt_State() == 1)){
					// 예약 기능
					buttonBuzzer();
					workState = RESERVE;
					timer = reserveTimeSet[reserveTime];
				}
				break;
				
				//예약 기능
				case RESERVE:
				if((reserv_Bt_State() == 1)){
					// 예약 기능
					buttonBuzzer();
					reserveTime = reserve_Mode(reserveTime);
					if(reserveTimeSet[reserveTime] == 0){
						workState = STANDBY;
						reserveTime = 0;
						break;
					}
					timer = reserveTimeSet[reserveTime];
				}
				LCD_write_XY_string(0,0," |Reserve Mode| ");
				LCD_write_XY_string(1,0,buff);
				if(prevSec2 != stTime.seconds){
					prevSec2 = stTime.seconds;
					timer--;
					sprintf(buff,"COMPLETE %02d sec ", timer);
					LCD_write_XY_string(1,0,buff);
					// 전체 세탁 시간이 timer와 같아지면 동작 시작(예약 시간은 완료시간)
					tot_time = washTimeSet[washTime] + (rinseTime*rinseNum) + spinTimeSet[spinTime];
					if(timer == tot_time){
						workState = RUN;
						timer = 0;
						workCount = 0;
					}
					
				}
				break;
				
				
				case RUN:
				// 전원 켜진 상태에서, RUN 상태에서,
				
				// 타이머 증가를 위한 부분
				if(prevSec2 != stTime.seconds){
					prevSec2 = stTime.seconds;
					// 작동 시작하면 타이머 초기화
					if(workCount == 0) timer = 0;
					timer++;
				}
				
				if(finishState == FINISH_STANDBY){
					if(washTime == 0) {
						finishState = FINISH_WASH; // 세탁 미설정 시 바로 헹굼으로
						break;
					}
					
					if((timer % 2) == 0)
					LCD_write_XY_string(0, 0, "  WASHING...()    ");
					else
					LCD_write_XY_string(0, 0, "  WASHING...)(  ");
					
					sprintf(buff,"REMAINING: %02dsec", washTimeSet[washTime] - timer);
					
					LCD_write_XY_string(1, 0, buff);
					
					workCount = 1;	// 작동 시작
					DCMotor_Washmode(washTimeSet[washTime] - timer);	// 드럼세탁기 동작부
					
					if(timer >= washTimeSet[washTime]){	// washtime 지나면
						DCMotorStop();		// 모터 멈추고
						finishState = FINISH_WASH;	// 세탁 끝
						workCount = 0;		// 타이머 초기화를 위해
						LCD_write_XY_string(0, 0, "  WASH FINISH   ");
						LCD_write_XY_string(1, 0, "  ***********   ");
						_delay_ms(1000);
					}
				}
				
				// rinse 부분
				else if(finishState == FINISH_WASH)
				{
					if(rinseNum == 0){
						finishState = FINISH_RINSE; // 헹굼 미설정 시 바로 탈수로
						break;
					}
					
					if((timer % 2) == 0)
					LCD_write_XY_string(0, 0, "  RINSING...><  ");
					else
					LCD_write_XY_string(0, 0, "  RINSING...<>  ");
					
					sprintf(buff,"REMAINING: [%02d] ", rinseNum);
					
					LCD_write_XY_string(1, 0, buff);
					
					workCount = 1;	// 작동 시작
					if((rinseTime-timer) == 0){
						rinseNum--;
						timer = 0;
					}
					if(rinseNum == 0){	// 헹굼 횟수만큼 하면
						DCMotorStop();		// 모터 멈추고
						finishState = FINISH_RINSE;	// 세탁 끝
						workCount = 0;		// 타이머 초기화를 위해
						LCD_write_XY_string(0, 0, "  RINSE FINISH  ");
						LCD_write_XY_string(1, 0, "  ------------  ");
						_delay_ms(1000);
					}
					DCMotor_Rinsemode(rinseTime - timer);	// 드럼세탁기 동작부
				}
				// spin 부분
				else if(finishState == FINISH_RINSE)
				{
					// 탈수 미설정 시 바로 대기로
					if(spinTime == 0){
						finishState = FINISH_SPIN;
						break;
					}
					
					if((timer % 2) == 0)
					LCD_write_XY_string(0, 0, "  SPINNING...][ ");
					else
					LCD_write_XY_string(0, 0, "  SPINNING...[] ");
					
					sprintf(buff,"REMAINING: %02dsec", spinTimeSet[spinTime] - timer);
					
					LCD_write_XY_string(1, 0, buff);
					
					workCount = 1;	// 작동 시작
					DCMotor_Spinmode();	// 드럼세탁기 동작부
					
					if(timer >= spinTimeSet[spinTime]){	// washtime 지나면
						DCMotorStop();		// 모터 멈추고
						finishState = FINISH_SPIN;	// 세탁 끝
						workCount = 0;		// 타이머 초기화를 위해
						LCD_write_XY_string(0, 0, "  SPIN  FINISH  ");
						LCD_write_XY_string(1, 0, "  ::::::::::::  ");
						_delay_ms(1000);
					}
				}
				// 빨래 끝
				else if(finishState == FINISH_SPIN)
				{
					DCMotorStop();
					finishBuzzer();
					LCD_write_XY_string(0, 0, "  WORK  FINISH  ");
					LCD_write_XY_string(1, 0, "  ////////////  ");
					_delay_ms(1000);
					finishState = FINISH_STANDBY;
					workState = STANDBY;
					
					// 세탁이 종료되면 전원 OFF
					powerState = POWEROFF;
					DCMotorStop();			// 세탁기 우선 정지
					powerOffBuzzer();		// 전원 꺼짐 부저 울리기
					LCD_write_XY_string(0, 0, "   POWER OFF    ");	// LCD 출력
					LCD_write_XY_string(1, 0, "     Bye..      ");
					_delay_ms(1500);
					LCD_clear();
					PORTF = 0x00;
					PORTG = 0x00; // ALL LED OFF
					
					// STANDBY 슬립모드
					MCUCR |= (1<<SE);
					MCUCR |= (0 << SM0) | (1 << SM1) | (1 << SM2);
					
					// 딜레이가 없으면 잠깐 LCD가 표시됨
					_delay_ms(1000);
				}
				break;

				case PAUSE:
				DCMotorStop();
				LCD_write_XY_string(1, 0, "      PAUSE     ");
				break;
			}
			
			break;
			
			
			case POWEROFF:
			// 전원 OFF
			DCMotorStop();
			LCD_clear();
			// LCD backlight OFF;
			PORTB &= ~(1<<PORTB1);
			break;
		}
	}
	return 0;
}