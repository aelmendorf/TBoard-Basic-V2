/* 
* MilliTimer.h
*
* Created: 9/20/2018 9:29:31 AM
* Author: 600076
*/


#ifndef __MILLITIMER_H__
#define __MILLITIMER_H__
#include "TBoard.h"
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include <stdbool.h>
#include <math.h>

class MilliTimer
{
//variables
public:
protected:
private:
	volatile uint32_t micros;
	volatile uint32_t millis;
	volatile unsigned char fract;
//functions
public:
	MilliTimer();
	~MilliTimer();
	uint32_t Millis(void);
	void Setup();
	void isr(void);
protected:
private:
	
}; //MilliTimer

#endif //__MILLITIMER_H__
