/*
 * MotorControls.c
 *
 * Created: 4/16/2019 3:02:13 PM
 *  Author: colea
 */ 
#include <stdio.h>
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>
#include "MotorControls.h"
#include "RotaryEncoder.h"
#include "acxserial.h"

void goStraightDistance(int cm, int forwards)
{
	int startingRight = getRightRotaryCount();
	int startingLeft = getLeftRotaryCount();
	int leftCurrent = 0;
	int rightCurrent = 0;
	
	if(forwards == 1)
	{
		goForwards();
	}
	else
	{
		goBackwards();
	}
	
	setSpeed(80);
	while(rightCurrent < cm)
	{
		rightCurrent = getRightRotaryCount() - startingRight;
		leftCurrent = getLeftRotaryCount() - startingLeft;
		if(leftCurrent > rightCurrent)
		{
			PORTC &= ~(0x06);
		}
		else if(leftCurrent < rightCurrent)
		{
			PORTC &= ~(0x09);
		}
		else
		{
			if(forwards == 1)
			{
				goForwards();
			}
			else
			{
				goBackwards();
			}
		}
	}
	stop();
}

void driveStraight(int millis, int forwards)
{
	int startingRight = getRightRotaryCount();
	int rightCurrent = getRightRotaryCount();
	int startingLeft = getLeftRotaryCount();
	int leftCurrent = getLeftRotaryCount();
	
	if(forwards)
	{
		goForwards();
	}
	else
	{
		goBackwards();
	}
	
	setSpeed(100);
	while(1)
	{
		int rightCurrent = getRightRotaryCount() - startingRight;
		int leftCurrent = getLeftRotaryCount() - startingLeft;
		
		if(leftCurrent > rightCurrent)
		{
			PORTC &= ~(0x06);
		}
		else if(leftCurrent < rightCurrent)
		{
			PORTC &= ~(0x09);
		}
		else
		{
			goForwards();
		}
	}
}

void test4()
{
	TurnDegrees(90, 0);
	//RadiusTurn(24*2.54, 90, 0);
	_delay_ms(4000);
	TurnDegrees(180, 0);
	//RadiusTurn(24*2.54, 90, 0);
	_delay_ms(4000);
	TurnDegrees(90, 1);
	//RadiusTurn(24*2.54, 90, 0);
	_delay_ms(4000);
	TurnDegrees(180, 1);
	//RadiusTurn(24*2.54, 90, 0);
	_delay_ms(4000);
}












int SYNCH = 0;
ISR(TIMER1_COMPA_vect) //set right vector for this operation (interrupt for output compare match)
{
	if(SYNCH == 1)
	{
		PORTL ^= 0x18;
	}
	else
	{
		PORTL ^= 0x08;
	}
}

ISR(TIMER3_COMPA_vect) //set right vector for this operation (interrupt for output compare match)
{
	if(SYNCH == 1)
	{
		
	}
	else
	{
		PORTL ^= 0x10;
	}
}

void wheelSetup()
{
	//--------------------TIMER 1 SETUP-----------------
	// period = 333.3 ms, on-time = 75ms
	TCCR1A = ((1 << COM1A0) | (1 << COM1A1));
	//configure match register
	OCR1A = 10;
	//configure Top
	ICR1 = 100;
	//Enable interrupts
	TIMSK1 = (1 << OCIE1A);
	//Counter
	TCNT1 = 0;
	TCCR1B = (1 << WGM13) | (1 << CS12); //timer starts running and sets prescaller to 256
	
	//--------------------TIMER 2 SETUP-----------------
	// period = 333.3 ms, on-time = 75ms
	TCCR3A = ((1 << COM1A1) | (1 << COM1A0));
	//configure match register
	OCR3A = 10;
	//configure Top
	ICR3 = 100;
	//Enable interrupts
	TIMSK3 = (1 << OCIE1A);
	//Counter
	TCNT3 = 0;
	TCCR3B = (1 << WGM13) | (1 << CS12); //timer starts running and sets prescaller to 256
	
	DDRL = 0xFF;//0x18;
	DDRC = 0xFF;//0x0F;
	SYNCH = 1;
	goForwards();
}

void RadiusTurn(double cm, double degrees, int left)
{
	if(cm < 12.7)
	{
		return;
	}
	
	//Find the circumference of the circle taken by the outer wheel and multiply it by the percentage around the circle we want to travel(degrees/360)
	int outerCirc = (int)((2*cm*3.14)*(degrees/360.0));
	
	//Find the circumference of the circle taken by the inner wheel (12.7cm or 5inches shorter radius) and multiply it by the percentage around the circle we want to travel(degrees/360)
	int innerCirc = (int)((2*(cm-12.7)*3.14)*(degrees/360.0));
	
	int innerRotar = (int)(innerCirc);
	int outerRotar = (int)(outerCirc);
	
	int leftCount = 0;
	int rightCount = 0;
	int startingRight = getRightRotaryCount();
	int rightCurrent = getRightRotaryCount();
	int startingLeft = getLeftRotaryCount();
	int leftCurrent = getLeftRotaryCount();
	
	//The percentage speed of the inner wheel based of difference in circumference.
	int slowerSpeed = ((double)innerRotar/(double)outerRotar)*100;
	
	
	if(slowerSpeed < 35)
	{
		return;
	}
	goForwards();
	//Turn Right
	if(left == 0)
	{
		rightCount = outerRotar;
		leftCount = innerRotar;
		differentSpeeds(slowerSpeed, 99);
		
	}
	//Turn Left
	else if(left == 1)
	{
		rightCount = innerRotar;
		leftCount = outerRotar;
		differentSpeeds(99, slowerSpeed);
	}
	/*
			Serial0_config(115200, SERIAL_8N1);
			char held[100];
			sprintf(held, "Left: %d Right: %d LeftMeet: %d RightMeet: %d", getLeftRotaryCount(), getRightRotaryCount(), (startingLeft + leftCount), (startingRight + rightCount));
			Serial0_poll_print(held);
			_delay_ms(5000);
	*/
	
	while((leftCurrent < (startingLeft + leftCount)) && (rightCurrent < (startingRight + rightCount)))
	{
		leftCurrent = getLeftRotaryCount();
		rightCurrent = getRightRotaryCount();
		
		if(leftCurrent >= (startingLeft + leftCount))
		{
			PORTC &= ~(0x06);
		}  
		if(rightCurrent >= (startingRight + rightCount))
		{
			PORTC &= ~(0x09);
		}
	}
}


void TurnDegrees(int degree, int left)
{
	int direction = left;
	int rotaryCount = (int)((double)degree/4.5);
	int leftCount = rotaryCount/2;
	int rightCount = rotaryCount/2;
	
	int startingRight = getRightRotaryCount();
	int rightCurrent = getRightRotaryCount();
	int startingLeft = getLeftRotaryCount();
	int leftCurrent = getLeftRotaryCount();
	
	//Turn Left
	if(direction == 1)
	{
		rightForwardsLeftBack();
	}
	//Turn Right
	else
	{
		leftForwardsRightBack();
	}
	setSpeed(50);
	
	while((leftCurrent < (startingLeft + leftCount)) && (rightCurrent < (startingRight + rightCount)))
	{
		/*
			Serial0_config(115200, SERIAL_8N1);
			char held[100];
			sprintf(held, "Left: %d Right: %d LeftMeet: %d RightMeet: %d", getLeftRotaryCount(), getRightRotaryCount(), (startingLeft + leftCount), (startingRight + rightCount));
			Serial0_poll_print(held);
			_delay_ms(3000);
			*/
		leftCurrent = getLeftRotaryCount();
		rightCurrent = getRightRotaryCount();
		
		if(leftCurrent >= (startingLeft + leftCount))
		{
			PORTC &= ~(0x06);
		}
		if(rightCurrent >= (startingRight + rightCount))
		{
			PORTC &= ~(0x09);
		}
	}
}


void goForwards()
{
	PORTC = 0x05;
}

void goBackwards()
{
	PORTC = 0x0A;
}

void stop()
{
	OCR1A = 300;
	TCNT1 = 0;
	PORTL = 0;
	OCR3A = 300;
	TCNT3 = 0;
}

void onlyLeftForwards()
{
	PORTC = 0x04;
}

void onlyRightForwards()
{
	PORTC = 0x01;
}

void onlyLeftBackwards()
{
	PORTC = 0x02;
}
void onlyRightBackwards()
{
	PORTC = 0x08;
}

void differentSpeeds(int right, int left)
{
	SYNCH = 0;
	int newLeftSpeed = findSpeed(left);
	int newRightSpeed = findSpeed(right);
	OCR1A = newLeftSpeed;
	OCR3A = newRightSpeed;
	if(newLeftSpeed == 100)
	{
		OCR1A = 300;
		PORTL &= 0xEF;
		TCNT1 = 0;
	}
	if(newRightSpeed == 100)
	{
		OCR3A = 300;
		PORTL &= 0xF7;
		TCNT3 = 0;
	}
}

void leftForwardsRightBack()
{
	PORTC = 0x0C;
}
void rightForwardsLeftBack()
{
	PORTC = 0x03;
}

int findSpeed(int speed)
{
	int match = speed;
	if(speed < 35)
	{
		match = 35;
	}
	else
	{
		match = 100-speed;
	}
	return match;
}

void setSpeed(int speed)
{
	SYNCH = 1;
	int match = findSpeed(speed);
	if(match == 100)
	{
		stop();
	}
	OCR1A = match;
	OCR3A = match;
}