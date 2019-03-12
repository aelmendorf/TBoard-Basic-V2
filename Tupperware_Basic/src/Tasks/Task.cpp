/* 
* Task.cpp
*
* Created: 2/19/2019 10:27:00 AM
* Author: 600076
*/


#include "Task.h"

// default constructor
Task::Task()
{
	this->error=false;
	this->state=INIT;
} //Task

Task::Task(const Task &c){
	this->error=c.error;
	this->state=c.state;
}

Task& Task::operator=(const Task &rhs){
	this->error=rhs.error;
	this->state=rhs.state;
	return *this;
}

bool Task::operator !=(const Task &rhs)const{
	return this->state!=rhs.state;
}

bool Task::operator==(const Task &rhs)const{
	return this->state==rhs.state;
}

// default destructor
Task::~Task()
{
} //~Task
