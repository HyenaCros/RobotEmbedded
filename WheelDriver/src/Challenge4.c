/*
 * Challenge4.c
 *
 * Created: 5/6/2019 10:24:45 AM
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

void Challenge4()
{
	//Tape tracking
	
	while(1)
	{
		IRrun();
	}
}