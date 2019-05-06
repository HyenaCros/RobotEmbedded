/*
 * UltrasonicObservers.c
 *
 * Created: 4/16/2019 3:13:00 PM
 *  Author: colea, kimbroughd
 */ 
#include "UltrasonicObservers.h"
#include <stdio.h>
#include <asf.h>
#include <acxserial.h>
#include <util/delay.h>
#include <interrupt.h>


static volatile double distance = 0;
static volatile int pulse = 0;
static volatile int senseInc = 0;
volatile char PCINT2_STATE = 0;
static volatile int avg_count = 0;

static volatile double avgSense = 0;


double getDistance()
{
	return distance;
}


ISR(PCINT2_vect)//interrupt service routine when there is a change in logic level
{
	char CURRENT_STATE = PINK;
	char changed = CURRENT_STATE ^ PCINT2_STATE;
	if(changed == 2)
	{
		if ((CURRENT_STATE & 2)==2)//when logic from HIGH to LOW
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
		}

		if ((CURRENT_STATE & 2)==2)//when logic change from LOW to HIGH
		{
			TCCR4B |= 1;//enabling counter

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
	
	//Set A9 as Interrupt pins
	PCMSK2 |= 0x02;	
	
	TCCR4A = 0;
	
	DDRF = 0x02;
}

void ultraSonicObservers()
{
	for (int j = 0; j < 5; j ++){
		PORTF |= 0x02;
		_delay_us(10);
		PORTF &= ~0x02;
		_delay_ms(2);
	}
}
