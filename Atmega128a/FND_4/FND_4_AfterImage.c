/*
 * FND_4_AfterImage.c
 *
 * Created: 4/26/2019 10:29:57 AM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "FND_CHAR.h"
int main(void)
{
	DDRC = 0xFF;
	DDRG = 0xFF;
	
	PORTG = 0x00;
	PORTC = 0xFF;

    /* Replace with your application code */
    while (1) 
    {
		PORTG = 0x08;
		PORTC = _1_;
		_delay_ms(1);
		
		PORTG = 0x04;
		PORTC = _2_;
		_delay_ms(1);
		
		PORTG = 0x02;
		PORTC = _3_;
		_delay_ms(1);
		
		PORTG = 0x01;
		PORTC = _4_;
		_delay_ms(1);
	}
}

