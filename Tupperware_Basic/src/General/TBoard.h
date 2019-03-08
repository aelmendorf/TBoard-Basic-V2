/*
 * TBoard.h
 *
 * Created: 2/18/2019 10:15:46 AM
 *  Author: 600076
 */ 


#ifndef TBOARD_H_
#define TBOARD_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <CurrentDriver.h>
#include <millis.h>

#define TRUE			(uint8_t)1
#define FALSE			(uint8_t)0

#define HIGH			(uint8_t)1
#define LOW				(uint8_t)0

#define SET_CURRENT		(uint16_t)15

//Timers
#define TIMERCOUNT		3
#define AUTOTMR			0
#define DAYTIMER		1
#define HOURTIMER		2
//Times
#define ON_TIME			(millis_t)5000UL//(uint32_t)10800000  //3hrs
#define DAY_TIME		(millis_t)30000UL//(uint32_t)86400000	//24hrs
#define LATCH_TIME		(millis_t)250UL
#define HOUR_TIME		(millis_t)10000UL//(uint32_t)3600000	//1 hour

//Switches
#define SWITCHCOUNT		4
#define LID_B			3
#define POS1_B			0
#define POS2_B			1
#define POS3_B			2


//LED PWMM
#define ON_PWM			900
#define AUTO_PWM		900
#define ON_PWM_IDLE		1000
#define AUTO_PWM_IDLE	1000
#define PWM_OFF			1023

//Ports
#define RED				PORTB4
#define BLUE			PORTB6
#define GREEN			PORTB5
#define POS1			PIND5
#define POS2			PIND3
#define POS3			PIND2
#define LID_SWITCH		PINF5
#define CURRENT_DRIVER	PORTC7



/************************************************************************/
/*                            MilliTimer                                */
/************************************************************************/

//#define clockCyclesPerMicrosecond() ( F_CPU / 1000000UL )
//#define clockCyclesToMicroseconds(a) ( ((a) * 1000UL) / (F_CPU / 1000UL) )
//#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
//#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
//#define SECONDS_INC (milli)((milli)/ 1000)
//#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
//#define FRACT_MAX (1000 >> 3)



#endif /* TBOARD_H_ */