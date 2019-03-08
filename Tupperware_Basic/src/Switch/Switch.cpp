/* 
* Switch.cpp
*
* Created: 9/19/2018 9:11:03 AM
* Author: 600076
*/


#include "Switch.h"


/************************************************************************/
/* Switch implementation                                                */
/************************************************************************/

Switch::Switch(){}

Switch::Switch(volatile uint8_t *port,const uint8_t &pin,uint8_t level){
	this->button_down=0;
	this->button_port=port;
	this->current_state=0;
	this->button_pin=pin;
	this->count=0;
	this->button_state=0;
	this->swtich_count=0;
	this->level=level;
}

void Switch::debounce(){
	if((*this->button_port & (1<<this->button_pin))==this->level){
		this->count+=1;
		if(this->count>=4){
			this->button_down=1;
			this->swtich_count+=1;
			this->count=0;
		}
	}else{
		this->button_down=0;
	}
}//End debounce;

void Switch::clear_state(){
	this->count=0;
}

void Switch::clear_state_count(){
	this->swtich_count=0;
}

uint8_t Switch::switched(){
	return this->button_down;
}

uint8_t Switch::get_switch_count(){
	return this->swtich_count;
}

// default destructor
Switch::~Switch()
{
} //~Switch
