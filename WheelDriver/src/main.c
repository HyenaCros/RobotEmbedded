
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
	
// 	while(1)
// 	{
// 		goForwards();
// 		setSpeed(90);
// 	}
	
	
	//stop();
	//Serial0_config(115200, SERIAL_8N1);
	//setSpeed(50);
	
	/*Testing for pivoting finding object*/
// 	while(1)
// 	{
// 		ultraSonicObservers();
// 		Serial0_config(115200, SERIAL_8N1);
// 		char held[100];
// 		int left = getDistanceLeft();
// 		int right = getDistanceRight();
// 		sprintf(held, "Left: %d Right: %d", left, right);
// 		Serial0_poll_print(held);
// 		_delay_ms(5000);
// 	}

// 	
	while(1)
	{
		bool seeObject = false;
		setSpeed(99);
		leftForwardsRightBack();
		
		while(seeObject == false)
		{
			ultraSonicObservers();
			//_delay_ms(100);
			int left = getDistanceLeft();
			int right = getDistanceRight();
			if((left < 5 && left > 0))
			{
				stop();
				seeObject = true;
				_delay_ms(1000);
			}
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
}