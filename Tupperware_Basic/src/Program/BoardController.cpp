/* 
* BoardController.cpp
*
* Created: 3/12/2019 12:41:52 PM
* Author: 600076
*/


#include "BoardController.h"

// default constructor
BoardController::BoardController()
{
	//all fields explicitly initialized in setup/start 
} //BoardController


void BoardController::Setup(){
	//disable JTAG
	MCUCR|=(1<<JTD);
	//_NOP();
	MCUCR|=(1<<JTD);
	//Set clock 16mhz
	CLKPR=0x80;
	CLKPR=0;
		
	//Signal LEDS
	DDRB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
		
	//Lid Switch setup
	PORTF|=(1<<LID_SWITCH);
	DDRF&=~(1<<LID_SWITCH);
		
	//current driver setup
	this->currentDriver.init();
	this->currentDriver.currentValue=SET_CURRENT;
}

void BoardController::Start(){
	this->Setup();
	millis_init();
	sei();
	this->time_reg.Init();
	this->task.state=INIT;
	this->task.error=false;;
	
}

void BoardController::Run(){
	while(1){
		switch(task.state){
			case INIT:{
				this->RunUVOff();
				this->time_reg.ResetDay();
				this->Transition_Wait(TO);
				break;
			}
			case WAIT_HR:{
				this->Wait_On();
				break;
			}
			case WAIT_DAY:{
				this->Wait_Cycle();
				break;
			}
			case WAIT_AUTO: {
				this->Wait_Auto();
				break;
			}
		}
		_delay_ms(5);
	}
}

bool BoardController::Check_Lid(){
	return (PINF & (1<<LID_SWITCH));
}

void BoardController::Wait_Cycle(){
	if(this->Check_Lid()){
		if(!this->task.error){
			this->RunRed();
		}
		this->task.error=true;
	}else{
		if(this->task.error){
			this->RunUVOff();
		}
		this->task.error=false;
	}
	if(this->time_reg.DayDone()){
		this->Transition_Wait(TO);
	}
}

void BoardController::Wait_Auto(){
	if(this->Check_Lid()){
		if(!this->task.error){
			this->currentDriver.turn_on();
			this->RunRed();
		}
		this->task.error=true;
	}else{
		if(this->task.error){
			this->currentDriver.turn_on();
			this->RunUVOn();
		}
		this->task.error=false;
	}
	if(this->time_reg.AutoDone()){
		this->Transition_Auto(FROM);
	}
}

void BoardController::Wait_On(){
	if(this->Check_Lid()){
		if(!this->task.error){
			this->RunRed();
		}
		this->task.error=true;
	}else{
		if(this->task.error){
			this->RunUVOff();
		}
		this->task.error=false;
	}
	if(this->time_reg.HrDone()){
		this->Transition_Wait(FROM);
	}
}

void BoardController::Transition_Auto(Direction direction){
	switch(direction){
		case TO:{
			if(!this->task.error){
				this->currentDriver.turn_on();
				this->RunUVOn();
			}
			this->task.state=WAIT_AUTO;
			this->time_reg.ResetAuto();
			break;
		}
		case FROM:{
			this->currentDriver.turn_off();
			if(!this->task.error){
				this->RunUVOff();
			}
			this->Transition_Cycle(TO);
			break;
		}
	}
}

void BoardController::Transition_Wait(Direction direction){
	switch(direction){
		case TO:{
			this->task.state=WAIT_HR;
			if(!this->task.error){
				this->RunUVOff();
			}
			this->time_reg.ResetDay();
			break;
		}
		case FROM:{
			this->Transition_Auto(TO);
			break;
		}
	}
}

void BoardController::Transition_Cycle(Direction direction){
	switch(direction){
		case TO:{
			this->task.state=WAIT_DAY;
			break;
		}
		case FROM:{
			this->time_reg.ResetDay();
			this->Transition_Wait(TO);
			break;
		}
	}
}

void BoardController::RunUVOff(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<GREEN);
}

void BoardController::RunUVOn(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<BLUE);
}

void BoardController::RunRed(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
	PORTB&=~(1<<RED);
}

void BoardController::RunAllOff(){
	PORTB|=(1<<RED) | (1<<GREEN) | (1<<BLUE);
}


// default destructor
BoardController::~BoardController()
{
	//no dynamic memory
} //~BoardController
