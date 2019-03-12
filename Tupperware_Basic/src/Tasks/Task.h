/* 
* Task.h
*
* Created: 2/19/2019 10:27:00 AM
* Author: 600076
*/


#ifndef __TASK_H__
#define __TASK_H__
#include <avr/io.h>
typedef enum state{INIT,WAIT_HR,WAIT_DAY,WAIT_AUTO}STATE;

class Task
{
//variables
public:
	bool  error;
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
