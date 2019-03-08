/* 
* Task.h
*
* Created: 2/19/2019 10:27:00 AM
* Author: 600076
*/


#ifndef __TASK_H__
#define __TASK_H__
#include <avr/io.h>
typedef enum state{RUNNING,IDLE,INIT,WAIT_HOUR,ERROR}STATE;

class Task
{
//variables
public:
	uint8_t latched:1;
	STATE state;
protected:
private:

//functions
public:
	Task();
	void Clear();
	Task(const Task &c);
	Task& operator=(const Task &c);
	bool operator!=(const Task &c)const;
	bool operator==(const Task &c)const;
	~Task();
protected:
private:


}; //Task

#endif //__TASK_H__
