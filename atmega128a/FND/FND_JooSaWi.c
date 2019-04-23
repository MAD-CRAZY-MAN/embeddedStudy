/*
 * FND_JooSaWi.c
 *
 * Created: 2019-04-12 오후 2:38:28
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>

int main(void)
{
	int i;
	DDRC = 0xFF;
	DDRF = 0x00;
	int num[7] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D};
    /* Replace with your application code */
    while (1) 
    {
		while(!(PINF & 0x01))
		{
			i = (rand() % 6) + 1;
			PORTC = num[i];
			_delay_ms(100);
		}	
    }
	return 0;
}

