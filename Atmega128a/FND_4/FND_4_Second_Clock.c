/*
 * FND_4_Second_Clock.c
 *
 * Created: 4/26/2019 11:15:28 AM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "CHAR_FND.h"

int main(void)
{
	DDRC = 0xFF;
	DDRG = 0xFF;
	PORTC = 0xFF;
	
	int min = 0, sec = 0, ms = 0;
	int num[10] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_};
	void check_time()
	{
		ms++;
		if(ms == 1000)
		{
			ms = 0;
			sec++;
		}
		
		if(sec == 60)
		{
			sec = 0;
			min ++;
		}
		if(min == 10)
		{
			min = 0;
		}
	}
    /* Replace with your application code */
    while (1) 
    {
		PORTG = 0x08;
		PORTC = num[min] & 0x7F;
		_delay_ms(1);
		check_time();
		
		PORTG = 0x4;
		PORTC = num[(sec-sec%10)/10];
		_delay_ms(1);
		check_time();
		
		PORTG = 0x02;
		PORTC = num[sec%10] & 0x7F;
		_delay_ms(1);
		check_time();
		
		PORTG = 0x01;
		PORTC = num[ms/100];
		_delay_ms(1);
		check_time();
		
    }
}

