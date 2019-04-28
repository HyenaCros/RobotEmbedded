/*
 * RotaryEncoder.c
 *
 * Created: 4/4/2019 11:35:23 AM
 * Author : chaserony
 */ 
#include "RotaryEncoder.h"
#include <stdbool.h>
#include <stdio.h>
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>
#include "acxserial.h"

volatile int right;
volatile int left;

volatile char PCINT1_STATE = 0;
ISR(PCINT1_vect) {	
	
	char CURRENT_STATE = PINJ;
	char changed = CURRENT_STATE ^ PCINT1_STATE;
	
    if ((CURRENT_STATE&0x01)==0x01 && (changed&0x01) == 0x01)
	{ 
		right++;
	}
    if ((CURRENT_STATE&0x02)==0x02 && (changed&0x02) == 0x02)
	{
		left++;
	}
	/*
	Serial0_config(115200, SERIAL_8N1);
	char held[5];
	//sprintf(held, "Left: %d Right: %d Current State: %x Changed: %x\n", left, right, CURRENT_STATE, changed);
	sprintf(held, "%d", left);
	Serial0_poll_print(held);
	_delay_ms(500);
	*/
	PCINT1_STATE = CURRENT_STATE;
}

void RotarySetup()
{
	MCUCR = 0x03;
    right = 0;
    left = 0;
	DDRJ = 0x00;
	PORTJ = 0x00;
	
    PCICR |= 0x07;
	PCIFR |= 0x02;
	//Enable PCINT 9 & 10
    PCMSK1 |= 0x06;
}

int getLeftRotaryCount()
{
	return left;
}
int getRightRotaryCount()
{
	return right;
}