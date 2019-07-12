/*
 * FND_4_PhoneNumber.c
 *
 * Created: 4/26/2019 2:32:40 PM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "CHAR_FND.h"
int phone_Num[17] = {_0_, _1_, _0_, 0xbf, _7_, _1_, _6_, _3_, 0xbf, _6_, _8_, _0_, _4_, 0xFF, 0xFF, 0xFF, 0xFF};
int i;
int a = 14, b = 15, c = 16, d = 0;
int main(void)
{
	
	DDRG = 0xFF;
	DDRC = 0xFF;

	
	
	/* Replace with your application code */
    while (1) 
    {			
		for(i=0;i<100;i++)
		{
			PORTG = 0x08;
			PORTC = phone_Num[a];
			_delay_ms(1);
		
			PORTG = 0x04;
			PORTC = phone_Num[b];
			_delay_ms(1);
		
			PORTG = 0x02;
			PORTC = phone_Num[c];
			_delay_ms(1);
		
			PORTG = 0x01;
			PORTC = phone_Num[d];
			_delay_ms(1);
		}
		a++; b++; c++; d++;
		a %= 17;
		b %= 17;
		c %= 17;
		d %= 17;
	}
	return 0;
}

