/*
 * IRSensor.c
 *
 * Created: 4/4/2019 2:15:45 PM
 * Author : kirbysf
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <stdbool.h>
#include <avr/delay.h>
#include "acx.h"
#include "acxserial.h"

#define F_CPU = 16000000

int main(void)
{
    DDRE = 0x00;
	DDRB = 0x80;
	
	PORTB = 0x00;
	PORTE = 0x00;
	
	Serial_open(0, 9600, SERIAL_8N1);
	int left;
	int right; 
	
    while (1) 
    {
		left = ((PINE >> 4) & 0x01);
		right = ((PINE >> 5) & 0x01);
		if(left && right)
		{
			Serial_puts(0, "Stop");
		}
		else if(left) //left sensor (D2)
		{
			Serial_puts(0, "Turning left");
			PORTB = 0x80;
		}
		else if (right) { //right sensor (D3)
			Serial_puts(0, "Turning right");
			PORTB = 0x80;
		}
		else {
			Serial_puts(0, "Stay Straight");
			PORTB = 0x00;
		}
			
		_delay_ms(500);
    }
}

