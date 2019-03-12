/*
 * Tupperware_Basic.cpp
 *
 * Created: 2/18/2019 10:06:44 AM
 * Author : 600076
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <TBoard.h>
#include <Task.h>
#include <BoardController.h>

int main(void)
{
	BoardController controller;
	controller.Start();
	controller.Run();
	return 1;
}


