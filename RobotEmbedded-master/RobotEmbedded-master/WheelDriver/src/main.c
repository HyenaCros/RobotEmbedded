
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>
#include <stdio.h>
#include "acxserial.h"
#include "MotorControls.h"
#include "UltrasonicObservers.h"
#include "RotaryEncoder.h"
#include "IRsensor.h"


int main (void)
{
	sei();
	_delay_ms(4000);
	setUpUltraSonic();
	wheelSetup();
	RotarySetup();
	IRsetup();
	
	stop();
	//Serial0_config(115200, SERIAL_8N1);
	setSpeed(99);
	
	
	while(1)
	{
		IRrun();
	}
	
// 	while(1)
// 	{
// 		Serial0_config(115200, SERIAL_8N1);
// 		char held[100];
// 		sprintf(held, "Left: %d Right: %d", getLeftRotaryCount(), getRightRotaryCount());
// 		Serial0_poll_print(held);
// 		_delay_ms(5000);
// 	}
	
// 	while(1)
// 	{
// 		goStraightDistance(243, 1);
// 		stop();
// 		_delay_ms(1000);
// 		TurnDegrees(180, 1);
// 		stop();
// 		_delay_ms(1000);
// 		goStraightDistance(243, 1);
// 		stop();
// 		_delay_ms(1000);
// 		TurnDegrees(180, 1);
// 		stop();
// 		_delay_ms(1000);
// 	}
	
	/*
	while(1)
	{
		ultraSonicObservers();
		_delay_ms(10);
		int distanceLeft = getDistanceLeft();
		int distanceRight = getDistanceRight();
		
		Serial0_config(115200, SERIAL_8N1);
		char held[100];
		sprintf(held, "Left: %d   Right: %d	", distanceLeft, distanceRight);
		Serial0_poll_print(held);
		_delay_ms(5000);
		
	}
	*/
	/*
	while(1)
	{
 		TurnDegrees(45, 1);
		stop();
 		_delay_ms(4000);
 		goBackwards();
		goStraightDistance(20, 0);
 		TurnDegrees(70, 0);
 		stop();
		 _delay_ms(4000);
 		goBackwards();
 		goStraightDistance(20, 0);
 		TurnDegrees(70, 1);
 		stop();
		 _delay_ms(4000);
 		goForwards();
 		goStraightDistance(40, 1);
 		stop();
		 _delay_ms(4000);
 		RadiusTurn(90, 20, 0);
 		stop();
		 _delay_ms(4000);
 		RadiusTurn(90, 20, 1);
		stop();
		_delay_ms(4000);
	}
	*/
	
	/*
	while(1)
	{
		setSpeed(99);
		goStraightDistance(40);
		_delay_ms(1000);
		TurnDegrees(180, 0);
		setSpeed(99); 
		goStraightDistance(40);
		_delay_ms(1000);
		TurnDegrees(180, 1);
		_delay_ms(1000);
		setSpeed(99);
	}
	*/
	
	
// 	while(1)
// 	{
// 		ultraSonicObservers();
// 		int distanceLeft = getDistanceLeft();
// 		int distanceRight = getDistanceRight();
// 		
// 		if(distanceLeft >= 0 && distanceLeft <= 2 && distanceRight >= 0 && distanceRight <= 1)
// 		{
// 			stop();
// 			_delay_ms(800);
// 			TurnDegrees(45, 1);
// 		}
// 		
// 		//Turn Right
// 		else if(distanceLeft >= 0 && distanceLeft <= 2)
// 		{
// 			stop();
// 			_delay_ms(800);
// 			goStraightDistance(20, 0);
// 			TurnDegrees(90, 0);		
// 		}
// 		
// 		else if(distanceRight >= 0 && distanceRight <= 2)
// 		{
// 			stop();
// 			_delay_ms(800);
// 			goStraightDistance(20, 0);
// 			TurnDegrees(90, 1);
// 		}
// 		
// 		else
// 		{
// 			//Both no sensing
// 			if(distanceRight < 0 && distanceRight < 0)
// 			{
// 				stop();
// 				_delay_ms(800);
// 				goForwards();
// 				goStraightDistance(40, 1);
// 			}
// 			
// 			//Right is farther than left
// 			//Turn Right
// 			else if(distanceLeft > 0 && distanceRight < 0)
// 			{
// 				stop();
// 				_delay_ms(800);
// 				RadiusTurn(120, 10, 0);
// 			}
// 			//Left is farther than right
// 			//Turn Left
// 			else if(distanceLeft < 0 && distanceRight > 0)
// 			{
// 				stop();
// 				_delay_ms(800);
// 				RadiusTurn(120, 10, 1);
// 			}
// 			//Left is farther than right
// 			//Turn left
// 			else if(distanceLeft > distanceRight)
// 			{
// 				stop();
// 				_delay_ms(800);
// 				RadiusTurn(120, 10, 0);
// 			}
// 			//Right is farther than left
// 			//Turn right
// 			else if(distanceRight > distanceLeft)
// 			{
// 				stop();
// 				_delay_ms(800);
// 				RadiusTurn(120, 10, 1);
// 			}
// 		}
		
//	}
	
	
}