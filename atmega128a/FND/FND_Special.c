/*
 * FND_Special.c
 *
 * Created: 2019-04-12 오후 2:55:22
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRF = 0x00;
	DDRC = 0xFF;
	int i = -1;
	int num[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F};
    /* Replace with your application code */
    while (1) 
    {
		while(!(PINF & 0x01))
		{
			if(i==9)
				i = 0;
			else
				i++;
			
			PORTC = num[i];	
			_delay_ms(400);
		}
		while(!(PINF & 0x02))
		{
			if(i==0)
				i=9;
			else
				i--;
			PORTC = num[i];
			_delay_ms(400);
		}
		while(!(PINF & 0x04))
		{
			i = 0;
			PORTC = num[i];
		}
	}
	return 0;
}

