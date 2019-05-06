/*
 * Challenge2.c
 *
 * Created: 5/6/2019 10:25:01 AM
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

void Challenge2()
{
	//Pivot Turns
	while(1)
	{
	 	TurnDegrees(90, 0);
	 	stop();
	 	_delay_ms(4000);
	 	TurnDegrees(180,0);
	 	stop();
	 	_delay_ms(4000);
	 	TurnDegrees(90,1);
	 	stop();
	 	_delay_ms(4000);
	 	TurnDegrees(180,1);
	 	stop();
	 	_delay_ms(10000);
	}
}