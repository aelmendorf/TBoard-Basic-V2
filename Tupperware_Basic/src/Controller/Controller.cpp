/* 
* Controller.cpp
*
* Created: 2/18/2019 11:57:01 AM
* Author: 600076
*/


#include "Controller.h"

// default constructor
Controller::Controller(MilliTimer *tmr)
{
	//auto reset timers
	tmr->Setup();
	this->timers[AUTOTMR]=Timer(ON_TIME,FALSE,tmr);
	this->timers[DAYTIMER]=Timer(DAY_TIME,TRUE,tmr);
	this->timers[HOURTIMER]=Timer(HOUR_TIME,FALSE,tmr);		
	
} //Controller

Controller::Controller()
{
} //Controller

void Controller::Setup(void){
	//disable JTAG
	MCUCR|=(1<<JTD);
	//_NOP();
	MCUCR|=(1<<JTD);
	
	CLKPR=0x80;
	CLKPR=0;
	
	//Current driver.  set output then pull low
	//DDRC|=(1<<CURRENT_DRIVER);
	//PORTC&=~(1<<CURRENT_DRIVER);
	
	//Signal LEDS
	DDRB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	
	//3POS switch set inputs
	//PORTD|=(1<<POS1) |(1<<POS2) |(1<<POS3);//Enable pullup*/
	//DDRD&=~(1<<POS1) & ~(1<<POS2) & ~(1<<POS3);
	
	PORTF|=(1<<LID_SWITCH);
	DDRF&=~(1<<LID_SWITCH);
	
	this->currentDriver.init();
	this->currentDriver.currentValue=SET_CURRENT;
		
	//TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
	//TCCR1B = (1<<WGM12)|(1<<CS10);
	//OCR1A=PWM_OFF;// LED initially off
	//OCR1B=PWM_OFF;
	//TIMSK1 |=(1<<TOIE1); // Enable overflow interrupt
	
	sei();
}



void Controller::Start(){
	this->timers[DAYTIMER].Start();
}

void Controller::Auto(){	
	if(!this->task.latched){
		this->task.state=INIT;
		this->task.latched=1;
	}
	switch(this->task.state){
		case INIT:{
				this->RunUVOff();
				this->task.state=WAIT_HOUR;
				this->timers[DAYTIMER].Start();
				this->timers[HOURTIMER].Start();
			break;
		}
		case WAIT_HOUR:{
			if(this->timers[HOURTIMER].IsTriggered()){
				this->currentDriver.turn_on();
				this->RunUVOn();
				this->task.state=RUNNING;
				this->timers[AUTOTMR].Start();
			}
			break;
		}
		case RUNNING:{		
			if((PINF & (1<<LID_SWITCH))){
				this->currentDriver.turn_off();
				this->RunRed();
				this->task.state=ERROR;
			}
			if(this->timers[AUTOTMR].IsTriggered()){
				this->RunUVOff();
				this->currentDriver.turn_off();
				this->task.state=IDLE;
			}
			break;
		}
		case IDLE:{
			if(this->timers[DAYTIMER].IsTriggered()){
				this->task.state=WAIT_HOUR;
				this->timers[DAYTIMER].Start();
				this->timers[HOURTIMER].Start();
			}
			break;
		}
		case ERROR:{
			if(!(PINF & (1<<LID_SWITCH))){
				this->currentDriver.turn_on();
				this->RunUVOn();
				this->task.state=RUNNING;
			}
			break;
		}
	}
}

void Controller::RunUVOff(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<GREEN);
	//OCR1A=ON_PWM;
	//OCR1B=PWM_OFF;
	//PORTB|=(1<<RED);
}

void Controller::RunUVOn(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<BLUE);
	//OCR1B=AUTO_PWM;
	//OCR1A=PWM_OFF;
	//PORTB|=(1<<RED);	
}

void Controller::RunRed(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<RED);
	//PORTB&=~(1<<RED);
	//OCR1A=PWM_OFF;
	//OCR1B=PWM_OFF;	
}

void Controller::RunAllOff(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	//OCR1A=PWM_OFF;
	//OCR1B=PWM_OFF;
	//PORTB|=(1<<RED);	
}

// default destructor
Controller::~Controller()
{
	
} //~Controller
