/*
 * UltrasonicObservers.c
 *
 * Created: 4/16/2019 3:13:00 PM
 *  Author: colea
 */ 
#include "UltrasonicObservers.h"
#include <stdio.h>
#include <asf.h>
#include <acxserial.h>
#include <util/delay.h>
#include <interrupt.h>

static volatile int distanceLeft = 0;
static volatile unsigned int leftPulse = 0;
static volatile int rightPulse = 0;
// static volatile int leftInc = 0;
// static volatile int rightInc = 0;
volatile char PCINT2_STATE = 0;
static volatile int avg_countL = 0;
static volatile int avg_countR = 0;
static volatile double avgL = 0;
static volatile double avgR = 0;

double getDistanceLeft()
{
	int l = distanceLeft;
	distanceLeft = 0;
	return l;
}

int timerStart = 1;
ISR(PCINT2_vect)//interrupt service routine when there is a change in logic level
{
	if (timerStart==0)//when logic from HIGH to LOW
		{
			TCCR4B=0;//disabling counter
			leftPulse=TCNT4;//count memory is updated to integer
			distanceLeft = leftPulse/9;
			
// 			Serial0_config(115200, SERIAL_8N1);
// 			char held[100];
// 			sprintf(held, "Distance: %d Pulse: %d", distanceLeft, leftPulse);
// 			Serial0_poll_print(held);
// 			_delay_ms(2000);
			
			/*
			if(leftPulse > 0)
			{
				distanceLeft = leftPulse/34;
				avgL += distanceLeft;
				avg_countL++;
			}
		    
			if (avg_countL == 5) {
				distanceLeft = avgL / 5;	
				avg_countL = 0;
				avgL = 0;
			}
			*/
			
			TCNT4=0;//resetting the counter memory
			timerStart = 1;
		}
		else//when logic change from LOW to HIGH
		{	
			TCCR4B |=(4);//enabling counter
			timerStart = 0;
		}
}

void setUpUltraSonic()
{
	
	DDRB = 0x80;
	PORTB = 0x00;
	
	PRR0 = 0x00;
	
	DDRK = 0x00;
	PORTK = 0x00;
	
	
	MCUCR = 0x03;
	
	//Enable Interrupt 2
	PCICR |= 0x04;
	
	//Set A8 A9 as Interrupt pins
	PCMSK2 |= 0x03;	
	
	TCCR4A = 0;
	
	DDRF = 0x03;
}

void ultraSonicObservers()
{
	timerStart = 1;
	TCNT4 = 0;
	TCCR4B = 0;
	PORTF |= 0x01;
	_delay_us(5);
	PORTF &= ~0x01;
	
	/*
	for (int i = 0; i < 5; i++) {
		timerStart = 1;
		TCNT4 = 0;
		TCCR4B = 0;
		PORTF |= 0x01;
		_delay_us(5);
		PORTF &= ~0x01;
	}
	*/
	
}