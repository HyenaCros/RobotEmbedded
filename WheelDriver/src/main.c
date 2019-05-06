
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>
#include <stdio.h>
#include "acxserial.h"
#include "MotorControls.h"
#include "UltrasonicObservers.h"
#include "RotaryEncoder.h"
#include "IRsensor.h"
#include "Challenge1.h"
#include "Challenge2.h"
#include "Challenge3.h"
#include "Challenge4.h"


int main (void)
{
	sei();
	_delay_ms(4000);
	setUpUltraSonic();
	wheelSetup();
	RotarySetup();
	IRsetup();
	
	//Challenge1();
	//Challenge2();
	//Challenge3();
	Challenge4();
}