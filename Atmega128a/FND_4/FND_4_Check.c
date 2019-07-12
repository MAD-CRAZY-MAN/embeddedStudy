/*
 * FND_4_Check.c
 *
 * Created: 4/26/2019 10:20:07 AM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
// CA TYPE FND
int main(void)
{
	DDRC = 0xFF;
	DDRG = 0xFF;
	
	PORTC = 0x00;
	PORTG = 0x0F;
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

