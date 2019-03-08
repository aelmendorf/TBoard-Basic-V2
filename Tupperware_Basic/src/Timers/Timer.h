/* 
* Timer.h
*
* Created: 2/18/2019 10:21:01 AM
* Author: 600076
*/


#ifndef __TIMER_H__
#define __TIMER_H__

#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <MilliTimer.h>

class Timer
{
//variables
public:


protected:

private:
	MilliTimer* milliTimer;
	volatile uint8_t triggered:1;
	volatile uint8_t active:1;
	volatile uint8_t done:1;
	volatile uint8_t autoReset:1;
	volatile uint32_t elapsed_sec;
	volatile uint32_t ms_delay;
	volatile uint32_t start_milli;
	volatile uint32_t elapsed_milli;

//functions
public:
	Timer();
	Timer(uint32_t del,uint8_t reset,MilliTimer *milli);
	uint8_t IsTriggered();
	void Start();
	void Stop();
	void Reset();
	uint8_t IsActive();
	Timer& operator=(const Timer &rhs);
	Timer(const Timer &c);
	~Timer();
protected:
private:
}; //Timer

#endif //__TIMER_H__
