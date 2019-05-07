/*
 * Challenge3.c
 *
 * Created: 5/6/2019 10:25:18 AM
 *  Author: colea
 */ 
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>
#include <stdio.h>
#include "acxserial.h"
#include "MotorControls.h"
#include "UltrasonicObservers.h"
#include "RotaryEncoder.h"
#include "IRsensor.h"

void Challenge3()
{
	stop();
	Serial0_config(115200, SERIAL_8N1);
	//setSpeed(50);
	
	/*Testing for pivoting finding object*/
// 	 	while(1)
// 	 	{
// 	 		ultraSonicObservers();
// 			 _delay_ms(60);
// 	 		Serial0_config(115200, SERIAL_8N1);
// 	 		char held[100];
// 	 		int left = getDistanceLeft();
// 	 		sprintf(held, "Distance: %d ", left);
// 	 		Serial0_poll_print(held);
// 	 		_delay_ms(4000);
// 	 	}

	
	int objectDistance = 100;
	int completed = 0;
	int rotaryStart = getLeftRotaryCount();
	while(1)
	{
		if (!completed) {
			setSpeed(60);
			leftForwardsRightBack();
			ultraSonicObservers();
			_delay_ms(70);
			int object = getDistanceLeft();
			if(object <= objectDistance && object > 3)
			{
				objectDistance = object;
			}
		}
		else {
			
		}
	}
	
	
// 	setSpeed(60);
// 	leftForwardsRightBack();
// 	while(1)
// 	{
// 		ultraSonicObservers();
// 		_delay_ms(70);
// 		int distance = getDistanceLeft();
// 		if(distance > 4 && distance < 50)
// 		{
// 			stop();
// 		}
// 	}
}