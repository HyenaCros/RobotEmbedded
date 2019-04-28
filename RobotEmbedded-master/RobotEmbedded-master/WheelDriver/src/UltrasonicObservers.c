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

static volatile double distanceLeft = 0;
static volatile double distanceRight = 9;
static volatile int leftPulse = 0;
static volatile int rightPulse = 0;
static volatile int leftInc = 0;
static volatile int rightInc = 0;
volatile char PCINT2_STATE = 0;
static volatile int avg_countL = 0;
static volatile int avg_countR = 0;
static volatile double avgL = 0;
static volatile double avgR = 0;


double getDistanceRight()
{
	return distanceRight;
}
double getDistanceLeft()
{
	return distanceLeft;
}


ISR(PCINT2_vect)//interrupt service routine when there is a change in logic level
{
	char CURRENT_STATE = PINK;
	char changed = CURRENT_STATE ^ PCINT2_STATE;
	
	/*
	Serial0_config(115200, SERIAL_8N1);
	char held[100];
	sprintf(held, "Current State: %x   Previous State: %x	Pin: %x			", CURRENT_STATE, PCINT2_STATE, changed);
	Serial0_poll_print(held);
	_delay_ms(3000);
	*/
	
	
	if(changed == 1)
	{
		if (leftInc==1)//when logic from HIGH to LOW
		{
			TCCR4B=0;//disabling counter
			leftPulse=TCNT4;//count memory is updated to integer
			
		    distanceLeft = ((double)leftPulse/148.0)/14.0;
			distanceLeft = distanceLeft*1.1;
			
			avgL += distanceLeft;
			avg_countL++;
			if (avg_countL == 5) {
				distanceLeft = avgL / 5;	
				avg_countL = 0;
				avgL = 0;
			}
			
			TCNT4=0;//resetting the counter memory
			leftInc=0;
		}

		if (leftInc==0)//when logic change from LOW to HIGH
		{
			TCCR4B |=(1);//enabling counter
			leftInc=1;
		}
	}
	else if(changed == 2)
	{
		if (rightInc==1)//when logic from HIGH to LOW
		{
			TCCR4B=0;//disabling counter
			rightPulse=TCNT4;//count memory is updated to integer
			
			distanceRight = (rightPulse/148)/14;
			avgR += distanceRight;
			avg_countR++;
			if (avg_countR == 5) {
				distanceRight = avgR / 5;
				avg_countR = 0;
				avgR = 0;
			}
			
			TCNT4=0;//resetting the counter memory
			rightInc=0;
		}

		if (rightInc==0)//when logic change from LOW to HIGH
		{
			TCCR4B |= 1;//enabling counter
			rightInc=1;
		}
	}
	
	PCINT2_STATE = CURRENT_STATE;
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
	for (int i = 0; i < 5; i++) {
		PORTF |= 0x01;
		_delay_us(10);
		PORTF &= ~0x01;
		_delay_ms(2);
	}
	
	for (int j = 0; j < 5; j ++){
		PORTF |= 0x02;
		_delay_us(10);
		PORTF &= ~0x02;
		_delay_ms(2);
	}
}