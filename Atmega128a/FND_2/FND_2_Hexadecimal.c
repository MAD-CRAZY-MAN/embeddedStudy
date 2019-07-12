/*
 * FND_2_Hexadecimal.c
 *
 * Created: 2019-04-19 오전 11:04:50
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "FND_CHAR.h"
int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRG = 0xFF;
	PORTG = 0xFF;
	
	int i, j;
	int numChar[10] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_};
    int alpChar[6] = {_A_, _B_, _C_, _D_, _E_, _F_};
	/* Replace with your application code */
    while (1) 
    {
		for(j=0;j<16;j++)
		{
			if(j<10)
				PORTA = numChar[j];
			else
				PORTA = alpChar[j-10]; 			

			for(i=0;i<10;i++)
			{
				PORTB = numChar[i];
				_delay_ms(100);
			}
			for(i=0;i<6;i++)
			{
				PORTB = alpChar[i];
				_delay_ms(100);
			}
		}
    }
}

