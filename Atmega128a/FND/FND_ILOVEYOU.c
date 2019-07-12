/*
 * FND_ILOVEYOU.c
 *
 * Created: 2019-04-12 오후 1:45:35
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRC = 0xFF;
	DDRF = 0x00;
	int name[8] = {0x06, 0x38, 0x3f, 0x3e, 0x79, 0x66, 0x3f, 0x3e};
	int i=0;
    /* Replace with your application code */
    while (1) 
    {
			while(!(PINF & 0X01))
			{
				
				PORTC = name[i%8];
				i++;
				_delay_ms(500);
			}		
    }
	return 0;
}

