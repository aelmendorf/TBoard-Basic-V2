/* 
* Timer.cpp
*
* Created: 2/18/2019 10:21:01 AM
* Author: 600076
*/


#include "Timer.h"

Timer::Timer(){
	this->triggered=0;
	this->active=0;
	this->start_milli=0;
	this->elapsed_milli=0;
}

// default constructor
Timer::Timer(uint32_t del,uint8_t reset,MilliTimer *milli)
{
	this->milliTimer=milli;
	this->autoReset=reset;
	this->triggered=0;
	this->active=0;
	this->ms_delay=del;
	this->start_milli=0;
	this->elapsed_milli=0;
} //Timer

Timer::Timer(const Timer &c){
	this->triggered=c.triggered;
	this->active=c.active;
	this->ms_delay=c.ms_delay;
	this->start_milli=c.start_milli;
	this->elapsed_milli=c.elapsed_milli;
	this->milliTimer=c.milliTimer;
}

void Timer::Start(){
	this->triggered=0;
	this->active=1;
	this->done=0;
	this->elapsed_milli=0;
	this->start_milli=this->milliTimer->Millis();
}

uint8_t Timer::IsTriggered(){
	uint8_t trg=0;
	if(this->active){
		
		this->elapsed_milli=this->milliTimer->Millis()-this->start_milli;
		if(this->elapsed_milli>=this->ms_delay){
			this->triggered=1;
			trg=1;
			if(this->autoReset){
				this->Reset();
			}else{
				this->active=0;
				this->done=1;
			}
		}	
	}
	return trg;
}

uint8_t Timer::IsActive(){
	return this->active;
}

void Timer::Stop(){
	this->active=0;
	this->done=1;
}

void Timer::Reset(){
	this->triggered=0;
	this->active=1;
	this->done=0;
	this->elapsed_milli=0;
	this->start_milli=this->milliTimer->Millis();
}

Timer& Timer::operator=(const Timer &rhs){
	this->triggered=rhs.triggered;
	this->active=rhs.active;
	this->ms_delay=rhs.ms_delay;
	this->start_milli=rhs.start_milli;
	this->elapsed_milli=rhs.elapsed_milli;
	this->milliTimer=rhs.milliTimer;
	return *this;
}

// default destructor
Timer::~Timer()
{
	//nothing to free
} //~Timer
