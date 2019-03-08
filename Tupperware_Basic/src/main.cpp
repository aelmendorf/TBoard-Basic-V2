/*
 * Tupperware_Basic.cpp
 *
 * Created: 2/18/2019 10:06:44 AM
 * Author : 600076
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <TBoard.h>

typedef enum modes{OFF_MODE=0,AUTO_MODE=1}MODE;
typedef enum state{RUNNING,IDLE,INIT,WAIT_HOUR,ERROR}STATE;
typedef enum p_modes{INPUT,WAIT_OFF,DISPLAY,EXIT}P_MODE;

CurrentDriver currentDriver;

static const millis_t hour_timer=10000; //3600000	//1 hour
static const millis_t auto_timer=5000;  //10800000  //3hrs
static const millis_t day_timer=30000; //86400000	//24hrs


void Setup(void);
void Auto();
void RunUVOff();
void RunUVOn();
void RunRed();
void RunAllOff();

int main(void)
{

	millis_t hour_last=0;
	millis_t auto_last=0;
	millis_t day_last=0;
	millis_t now;
	bool hour_done,error,auto_on;
	
	auto_on=false;
	hour_done=false;
	error=false;
	Setup();
	RunUVOff();
	while(1){
		now=millis_get();
		if((PINF & (1<<LID_SWITCH))){
			if(!error){
				currentDriver.turn_off();
				RunRed();
				error=true;
			}
		}else{
			if(error){
				if(auto_on){
					currentDriver.turn_on();
					RunUVOn();
				}else{
					RunUVOff();
				}
				error=false;
			}
		}
		
		if((now-day_last)>=day_timer){
			hour_last=0;
			day_last=0;
			millis_reset();
			now=millis_get();
			auto_on=false;
			hour_done=false;
		}//end 24hr check
		
		if(((now-hour_last)>=hour_timer) && !hour_done){
			if(!auto_on){
				auto_on=true;
				currentDriver.turn_on();
				RunUVOn();
				auto_last=now;
			}//end latch
			if((now-auto_last)>=auto_timer){
				currentDriver.turn_off();
				RunUVOff();
				hour_done=true;
				auto_on=false;
			}//end auto timer check
		}//End time after 24hr check	
	}
}

void Setup(void){
	//disable JTAG
	MCUCR|=(1<<JTD);
	//_NOP();
	MCUCR|=(1<<JTD);
	
	CLKPR=0x80;
	CLKPR=0;
	
	//Signal LEDS
	DDRB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	
	PORTF|=(1<<LID_SWITCH);
	DDRF&=~(1<<LID_SWITCH);

	currentDriver.init();
	currentDriver.currentValue=SET_CURRENT;
	millis_init();
	sei();
}

void RunUVOff(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<GREEN);
}

void RunUVOn(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<BLUE);
}

void RunRed(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<RED);
}

void RunAllOff(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
}

