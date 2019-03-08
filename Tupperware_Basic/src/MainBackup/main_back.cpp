/*
 * Tupperware_Basic.cpp
 *
 * Created: 2/18/2019 10:06:44 AM
 * Author : 600076
 */ 
#include <TBoard.h>
#include <avr/io.h>
#include <util/delay.h>
#include <MilliTimer.h>
#include <Timer.h>
#include <Switch.h>
#include <CurrentDriver.h>
#include <Controller.h>




MilliTimer milli_timer;
Controller controller(&milli_timer);
//Timer timers[TIMERCOUNT]={Timer(1000,TRUE,&milli_timer),Timer(ON_TIME,FALSE,&milli_timer)};
//Switch switches[3];
//CurrentDriver currentDriver(SET_CURRENT);
//uint8_t latch_auto,latch_off,latch_on;

ISR(TIMER0_OVF_vect){
	milli_timer.isr();
}

//void Initialize(void);
//void CheckSwitches(void);
//void On(void);
//void Off(void);
//void Auto(void);
//void RunRed(void);
//void RunGreen(void);
//void RunBlue(void);
//void ProcessSwitch(int sw);


int main(void)
{
	controller.Setup();
	while(1){
		controller.CheckSwitches();
	}
	//Initialize();
	//sei();
	//while(1){
		//CheckSwitches();
	//}
}

/*void Initialize(void){
	//disable JTAG
	MCUCR|=(1<<JTD);
	//_NOP();
	MCUCR|=(1<<JTD);
		
	//CLKPR|=(1<<CLKPCE);
	//CLKPR&=~(1<<CLKPS0) & ~(1<<CLKPS1) &~(1<<CLKPCE);
	CLKPR=0x80;
	CLKPR=0;
	
	//Current driver.  set output then pull low
	DDRC|=(1<<CURRENT_DRIVER);
	PORTC&=~(1<<CURRENT_DRIVER);
		
	//Signal LEDS
	DDRB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	
	//3POS switch set inputs
	PORTD|=(1<<POS1) |(1<<POS2) |(1<<POS3);//Enable pullup
	DDRD&=~(1<<POS1) & ~(1<<POS2) & ~(1<<POS3);
	
	currentDriver.init();
	currentDriver.currentValue=SET_CURRENT;
	
	//setup switch
	switches[POS1_B]=Switch(&PIND,POS1,LOW);
	switches[POS2_B]=Switch(&PIND,POS2,LOW);
	switches[POS3_B]=Switch(&PIND,POS3,LOW);
	
	latch_on=0;
	latch_off=0;
	latch_auto=0;
	if(!(PIND & (1<<POS1))){
		Auto();
	}else if(!(PIND & (1<<POS2))){
		Off();
	}else if(!(PIND & (1<<POS3))){
		On();
	}else{
		Off();
	}//End initial check
}

void CheckSwitches(void){
	for(int i=0;i<3;i++){
		switches[i].debounce();
		if(switches[i].switched()){
			switches[i].clear_state();
			ProcessSwitch(i);
		}
		_delay_ms(5);
	}//end
}

void ProcessSwitch(int sw){
	switch(sw){
		case POS1_B:{
			Auto();
			break;
		}
		case POS2_B:{
			Off();
			break;
		}
		case POS3_B:{
			On();
			break;
		}
	}
}

void On(){
	if(latch_on!=1){
		latch_on=1;
		latch_auto=0;
		latch_off=0;
		RunGreen();
		timers[AUTOTMR].Stop();
		timers[BLINKTMR].Start();
	}
	if(timers[BLINKTMR].IsActive()){
		if(timers[BLINKTMR].IsTriggered()){
			PORTB^=(1<<GREEN);
		}
	}
}

void Off(){
	if(latch_off!=1){
		latch_off=1;
		latch_auto=0;
		latch_on=0;
		RunRed();
		timers[AUTOTMR].Stop();
	}
}

void Auto(){
	if(latch_auto!=1){
		latch_off=0;
		latch_auto=1;
		latch_on=0;
		RunBlue();
		currentDriver.turn_on();
		timers[AUTOTMR].Start();
	}
	if(timers[AUTOTMR].IsActive()){
		if(timers[AUTOTMR].IsTriggered()){
			//PORTB^=(1<<BLUE);
			currentDriver.turn_off();
			RunGreen();
		}
	}
}

void RunRed(void){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<RED);
}

void RunGreen(void){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<GREEN);
}

void RunBlue(void){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<BLUE);
}*/