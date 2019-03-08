/* 
* CurrentDriver.cpp
*
* Created: 9/19/2018 10:58:12 AM
* Author: 600076
*/


#include "CurrentDriver.h"

CurrentDriver::CurrentDriver(int value){
	this->currentValue=value;
}

// default constructor
CurrentDriver::CurrentDriver()
{
	this->currentValue=SET_CURRENT;	
} //CurrentDriver

// default destructor
CurrentDriver::~CurrentDriver()
{
	//nothing to free
} //~CurrentDriver

void CurrentDriver::init(){
	//Current driver.  set output then pull low
	DDRC|=(1<<CURRENT_DRIVER);
	PORTC&=~(1<<CURRENT_DRIVER);
}

void CurrentDriver::set_current(uint8_t reset){
	if(this->currentValue<=0){
		PORTC&=~(1<<PORTC7);
	}else{
		int strobes=33-((8*this->currentValue)/5);
		if(reset){
			PORTC&=~(1<<PORTC7);
			_delay_us(5);
		}
		for(int i=0;i<strobes;i++){
			PORTC|=(1<<PORTC7);
			_delay_us(5);
			PORTC&=~(1<<PORTC7);
		}
		_delay_us(5);
		PORTC|=(1<<PORTC7);
		_delay_us(130);
	}//end if/else
}//End set_current

void CurrentDriver::turn_off(){
	PORTC&=~(1<<PORTC7);
	_delay_us(5);
}

void CurrentDriver::turn_on(){
	this->set_current(1);
}