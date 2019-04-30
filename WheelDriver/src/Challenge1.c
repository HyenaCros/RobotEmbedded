#include <stdio.h>
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>
#include "MotorControls.h"
#include "RotaryEncoder.h"
#include "acxserial.h"
void Challenge1()
{
    while (1)
    {
        goStraightDistance(244, 1);
        stop();
        _delay_ms(2000);
    }
}