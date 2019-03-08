/* 
* CurrentDriver.h
*
* Created: 9/19/2018 10:58:12 AM
* Author: 600076
*/


#ifndef __CURRENTDRIVER_H__
#define __CURRENTDRIVER_H__
#include <TBoard.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>


class CurrentDriver
{
//variables
public:
	uint16_t currentValue;
protected:
private:

//functions
public:
	CurrentDriver();
	CurrentDriver(int value);
	~CurrentDriver();
	void turn_off(void);
	void turn_on(void);
	void init(void);
	void set_current(uint8_t reset);
	uint8_t get_display(void);
	int8_t set_current_value(uint8_t value);
protected:
private:

}; //CurrentDriver

#endif //__CURRENTDRIVER_H__
