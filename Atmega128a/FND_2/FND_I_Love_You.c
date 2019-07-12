/*
 * FND_I_Love_You.c
 *
 * Created: 2019-04-19 오후 2:37:17
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
	DDRF = 0x00;
	DDRG = 0xFF;
	
	PORTG = 0xFF;
	int i = 0, j = 1;
	int fndChar[12] = {_NULL_, _I_, _NULL_, _L_, _O_, _V_, _E_, _NULL_, _Y_, _O_, _U_, _NULL_};
    /* Replace with your application code */
    while (1) 
    {
		PORTA = fndChar[i];
		PORTB = fndChar[j];
		while(!(PINF & 0x01))
		{
			
			i++;
			j++;
			
			while(!(PINF & 0x01));
			_delay_ms(30);
		}
		if(i>10)
		{
			i = 0;
			j = 1;
		}
		
    }
}

