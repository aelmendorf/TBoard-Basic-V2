/* 
* Switch.h
*
* Created: 9/19/2018 9:11:03 AM
* Author: 600076
*/


#ifndef __SWITCH_H__
#define __SWITCH_H__
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdbool.h>


class Switch
{
//variables
public:
	uint8_t button_down;
	uint8_t count;
	uint8_t current_state;
	uint8_t button_state;
	uint8_t button_pin;
	uint8_t pullup;
	uint8_t swtich_count;
	uint8_t latched;
	uint8_t level;
	volatile uint8_t* button_port;
protected:
private:

//functions
public:
	Switch();
	Switch(volatile uint8_t *port,const uint8_t &pin,uint8_t level);
	~Switch();
	void initialize(void);
	void debounce(void);
	void clear_state(void);
	uint8_t switched(void);
	uint8_t get_switch_count(void);
	void clear_state_count(void);
protected:
private:
	//Switch( const Switch &c );
	//Switch& operator=( const Switch &c );

}; //Switch

#endif //__SWITCH_H__
