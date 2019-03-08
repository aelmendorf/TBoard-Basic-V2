/* 
* MilliTimer.cpp
*
* Created: 9/20/2018 9:29:31 AM
* Author: 600076
*/

#include "MilliTimer.h"

// default constructor
MilliTimer::MilliTimer()
{
	this->millis=0;
	this->micros=0;
	this->fract=0;
} //MilliTimer

// default destructor
MilliTimer::~MilliTimer()
{

} //~MilliTimer

void MilliTimer::Setup(){
		TCCR0B|=(1<<CS01) |(1<<CS00);//prescale=64
		TIMSK0|=(1<<TOIE0);//enable interrupt
}

uint32_t MilliTimer::Millis(){
	uint32_t m;
	uint8_t sreg=SREG;
	cli();
	m=this->millis;
	sei();
	SREG=sreg;
	return m;
}

void MilliTimer::isr(){
	uint32_t m=this->millis;
	unsigned char f=this->fract;
	m+=MILLIS_INC;
	f+=FRACT_INC;
	if(f>=FRACT_MAX){
		f-=FRACT_MAX;
		m+=1;
	}
	this->fract=f;
	this->millis=m;
}