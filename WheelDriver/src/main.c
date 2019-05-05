
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
	//IRsetup();
	
	
	
	
	stop();
	//Serial0_config(115200, SERIAL_8N1);
	setSpeed(50);
	
	/*Testing for pivoting finding object*/
	
	bool seeObject = false;
	setSpeed(50);
	leftForwardsRightBack();
	while(seeObject == false)
	{
		ultraSonicObservers();
		int distance_l = getDistanceLeft();
		int distance_r = getDistanceRight();
		if(distance_l < 5 || distance_r < 5)
		{
			stop();
			seeObject = true;
		}	
	}

//Go Straight 8ft (open loop)
	
// 	while(1)
// 	{
// 		goStraightDistance(244, 1);
// 		stop();
// 		_delay_ms(2000);
// 	}



//Tape tracking 
	
// 	while(1)
// 	{
// 		IRrun();
// 	}

//Pivot Turns 

// 	while(1)
// 	{
// 		TurnDegrees(90, 0);
// 		stop();
// 		_delay_ms(4000);
// 		TurnDegrees(180,0);
// 		stop();
// 		_delay_ms(4000);
// 		TurnDegrees(90,1);
// 		stop();
// 		_delay_ms(4000);
// 		TurnDegrees(180,1);
// 		stop();
// 		_delay_ms(10000);
// 	}	
	

//Automous Driving 
	
	while(1)
	{
		ultraSonicObservers();
		int distanceLeft = getDistanceLeft();
		int distanceRight = getDistanceRight();
		
		if(distanceLeft >= 0 && distanceLeft <= 2 && distanceRight >= 0 && distanceRight <= 1)
		{
			stop();
			_delay_ms(800);
			TurnDegrees(45, 1);
		}
		
		//Turn Right
		else if(distanceLeft >= 0 && distanceLeft <= 2)
		{
			stop();
			_delay_ms(800);
			goStraightDistance(20, 0);
			TurnDegrees(90, 0);		
		}
		
		else if(distanceRight >= 0 && distanceRight <= 2)
		{
			stop();
			_delay_ms(800);
			goStraightDistance(20, 0);
			TurnDegrees(90, 1);
		}
		
		else
		{
			//Both no sensing
			if(distanceRight < 0 && distanceRight < 0)
			{
				stop();
				_delay_ms(800);
				goForwards();
				goStraightDistance(40, 1);
			}
			
			//Right is farther than left
			//Turn Right
			else if(distanceLeft > 0 && distanceRight < 0)
			{
				stop();
				_delay_ms(800);
				RadiusTurn(120, 10, 0);
			}
			//Left is farther than right
			//Turn Left
			else if(distanceLeft < 0 && distanceRight > 0)
			{
				stop();
				_delay_ms(800);
				RadiusTurn(120, 10, 1);
			}
			//Left is farther than right
			//Turn left
			else if(distanceLeft > distanceRight)
			{
				stop();
				_delay_ms(800);
				RadiusTurn(120, 10, 0);
			}
			//Right is farther than left
			//Turn right
			else if(distanceRight > distanceLeft)
			{
				stop();
				_delay_ms(800);
				RadiusTurn(120, 10, 1);
			}
		}
		
	}
	
	
}