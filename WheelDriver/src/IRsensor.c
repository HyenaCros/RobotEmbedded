/*
 * IRSensor.c
 *
 * Created: 4/4/2019 2:15:45 PM
 * Author : kirbysf
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <stdbool.h>
#include <avr/delay.h>
#include <interrupt.h>
#include <stdio.h>
#include "acx.h"
#include "acxserial.h"
#include "MotorControls.h"


#define F_CPU = 16000000

void IRrun();
void IRsetup();


int leftTape, rightTape = 0; 

void IRsetup()
{
	DDRB |= 0x00;
	PORTB |= 0x00;
	
	
	PCICR |= 0x01;
	PCIFR |= 0x01;
	PCMSK0 |= 0x03;
}

ISR(PCINT0_vect)
{
	char curstate = PINB;
	if((curstate & 0x03) == 0x00)
	{
		leftTape = 0;
		rightTape = 0;
	}
	if((curstate & 0x03) == 0x01)
	{
		leftTape = 0;
		rightTape = 1;
	}
	if((curstate & 0x03) == 0x02)
	{
		leftTape = 1;
		rightTape = 0;
	}
	if((curstate & 0x03) == 0x03)
	{
		leftTape = 1;
		rightTape = 1;
	}
}


void IRrun()
{
	if(leftTape==1 && rightTape==1)
	{
		stop();
		_delay_ms(3000);
	}
	else if(leftTape)
	{
		stop();
		_delay_ms(100);
		rightForwardsLeftBack()
		_delay_ms(100);
		stop();
		//TurnDegrees(15, 1);
	}
	else if (rightTape)
	{
		stop();
		_delay_ms(100);
		leftForwardsRightBack()
		_delay_ms(100);
		stop();
		TurnDegrees(15, 0);
	}
	else
	{
		goForwards();
		setSpeed(50);
	}
}


