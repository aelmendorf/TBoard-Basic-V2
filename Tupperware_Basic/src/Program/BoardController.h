/* 
* BoardController.h
*
* Created: 3/12/2019 12:41:52 PM
* Author: 600076
*/


#ifndef __BOARDCONTROLLER_H__
#define __BOARDCONTROLLER_H__

#include <TBoard.h>
#include <Task.h>

typedef struct timer_registers{
	bool error;
	millis_t wait_last;
	millis_t auto_last;
	millis_t cycle_last;
	millis_t now;
	static const millis_t wait_timer=WAIT_TIME;
	static const millis_t cycle_timer=CYCLE_TIME;
	static const millis_t auto_timer=AUTO_TIME;
	
	inline timer_registers(){
		this->wait_last=0;
		this->auto_last=0;
		this->cycle_last=0;
		this->now=0;
		this->error=false;
	}
	
	inline void Init(){
		this->wait_last=0;
		this->auto_last=0;
		this->cycle_last=this->Now();
		this->error=false;
	}
	
	inline void ResetDay(){
		this->cycle_last=Now();
		this->wait_last=this->now;
	}
	
	inline void ResetAuto(){
		this->auto_last=Now();
	}
	
	inline void ResetHr(){
		this->wait_last=Now();
	}
	
	inline millis_t Now(){
		this->now=millis_get();
		return this->now;
	}
	
	inline bool AutoDone(){
		return (this->Now()-this->auto_last)>=auto_timer;
	}
	
	inline bool HrDone(){
		return (this->Now()-this->wait_last)>=wait_timer;
	}
	
	inline bool DayDone(){
		return (this->Now()-this->cycle_last)>=cycle_timer;
	}
	
}TIMER_REG;

typedef enum transition{
	TO,
	FROM
}Direction;

class BoardController
{
//variables
public:

protected:
//Timer Variables DO NOT TOUCH

private:
CurrentDriver currentDriver;
Task task;
TIMER_REG time_reg;

//functions
public:
	BoardController();
	void Setup(void);
	void Start(void);
	bool Check_Lid(void);
	void Run(void);
	~BoardController();
private:
	//States
	void Wait_Cycle(void);
	void Wait_Auto(void);
	void Wait_On(void);
	
	//State Transitions
	void Transition_Wait(Direction direction);
	void Transition_Auto(Direction direction);
	void Transition_Cycle(Direction direction);
	
	void RunUVOff(void);
	void RunUVOn(void);
	void RunRed(void);
	void RunAllOff(void);
}; //BoardController

#endif //__BOARDCONTROLLER_H__
