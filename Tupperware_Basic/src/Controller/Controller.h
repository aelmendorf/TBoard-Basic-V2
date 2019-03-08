/* 
* Controller.h
*
* Created: 2/18/2019 11:57:01 AM
* Author: 600076
*/
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <TBoard.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>
#include <Timer.h>
#include <CurrentDriver.h>
#include <Switch.h>
#include <Task.h>

typedef struct SwitchSeq{
	uint8_t pos1;
	uint8_t pos2;
	uint8_t pos3;
	
	inline SwitchSeq(){
		this->pos1=0;
		this->pos2=0;
		this->pos3=0;
	}
	
	inline void Clear(){
		this->pos1=0;
		this->pos2=0;
		this->pos3=0;
	}
	
	inline SwitchSeq(const SwitchSeq &c){
		this->pos1=c.pos1;
		this->pos2=c.pos2;
		this->pos3=c.pos3;
	}
	
	inline SwitchSeq(uint8_t p1,uint8_t p2,uint8_t p3){
		this->pos1=p1;
		this->pos2=p2;
		this->pos3=p3;
	}
	
	inline SwitchSeq& operator=(const SwitchSeq &rhs){
		this->pos1=rhs.pos1;
		this->pos2=rhs.pos2;
		this->pos3=rhs.pos3;
		return *this;
	}
	
	inline bool operator==(const SwitchSeq &rhs)const
	{
		return this->pos1==rhs.pos1 && this->pos2==rhs.pos2 && this->pos3==rhs.pos3;
	}
}SwitchSeq;

class Controller
{
//variables
public:
protected:
private:
	//typedef void (Controller::*Fptr)(void);
	//Fptr func[MODE_COUNT];
	Timer timers[TIMERCOUNT];
	CurrentDriver currentDriver;
	Task task,next_task,saved_task;
//functions
public:
	Controller(MilliTimer *tmr);
	Controller();
	void Setup(void);
	void Start(void);
	void Auto(void);
	//void CheckSwitches(void);
	~Controller();
protected:
private:
	//void ProcessSwitch(int sw);	
	void RunUVOff(void);
	void RunRed(void);
	void RunUVOn(void);
	void RunAllOff(void);
	//void On(void);
	//void Off(void);

	
}; //Controller

#endif //__CONTROLLER_H__
