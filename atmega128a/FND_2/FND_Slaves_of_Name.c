/*
 * FND_Slaves_of_Name.c
 *
 * Created: 2019-04-19 오후 2:59:40
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "FND_CHAR.h"
#include <stdlib.h>

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRG = 0xFF;
	DDRF = 0x00;

	PORTG = 0xFF;
	
	int numChar[16] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _A_, _B_, _C_, _D_, _E_, _F_};
	PORTA = 0xFF;
	PORTB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		while(!(PINF & 0x01))
		{
			PORTA = numChar[rand() % 16];
			PORTB = numChar[rand() % 16];
			_delay_ms(150);
		}
    }
	return 0;
}

