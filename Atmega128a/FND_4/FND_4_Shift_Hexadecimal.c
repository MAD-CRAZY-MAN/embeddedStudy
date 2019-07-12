/*
 * FND_4_Shift_Hexadecimal.c
 *
 * Created: 4/26/2019 1:58:12 PM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "CHAR_FND.h"

int main(void)
{
	DDRG = 0xFF;
	DDRC = 0xFF;
	
	PORTG = 0x00;
	PORTC = 0xFF;
	
	int i = 0;
	int num[16] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _A_, _B_, _C_, _D_, _E_, _F_};
	unsigned char fnd_position = 0x01;
    /* Replace with your application code */
    
	while (1) 
    {
		PORTG = fnd_position;
		
		PORTC = num[i++];
		_delay_ms(500);
		if(i>=16)
			i = 0;
		
		if(fnd_position<8)
			fnd_position <<= 1;
		else
			fnd_position = 0x01;
    }
}

