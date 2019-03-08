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
	this->latched=0;
	this->state=INIT;
} //Task

Task::Task(const Task &c){
	this->latched=c.latched;
	this->state=c.state;
}

Task& Task::operator=(const Task &rhs){
	this->latched=rhs.latched;
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
