/*
 * FND_2_Switch_3.c
 *
 * Created: 2019-04-19 오후 1:40:35
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "FND_Char.h"

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRG = 0xFF;
	PORTG = 0xFF;
	DDRF = 0x00;
	int numChar[16] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _A_, _B_, _C_, _D_, _E_, _F_};
	int i = 0, j = 0;
    /* Replace with your application code */
    while (1) 
    {
		PORTA = numChar[j];
		PORTB = numChar[i];
		
			if (!(PINF&0x01))
			{
				if(i<15)
					i++;
				else
				{
					if(j==15)
						j=0;
					else
						j++;
					i = 0;
				}
				
				while (!(PINF&0x01));
				_delay_ms(30);
			}
			if(!(PINF&0x02))
			{
				if(i>0)
					i--;
				else
				{
					if(j==0)
						j=15;
					else
						j--;
					i = 15;
				}
				
				while(!(PINF&0x02));
				_delay_ms(30);
			}
	
		if(!(PINF&0x04))	
		{
			i = 0;
			j = 0;
			
			while(!(PINF&0x04));
			_delay_ms(30);
		}
    }
	return 0;
}

