/*
 * FND_4_From_0_To_F.c
 *
 * Created: 4/26/2019 10:58:32 AM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "CHAR_FND.h"

int main(void)
{
	DDRC = 0xFF;
	DDRG = 0x01;
	PORTG = 0X01;
	PORTC = 0xFF;
	int i = 0;
	int num[16] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _A_, _B_, _C_, _D_, _E_, _F_};
    /* Replace with your application code */
    while (1) 
    {
		PORTC = num[i++];
		_delay_ms(500);
		
		if(i==16)
			i = 0;
    }
}

