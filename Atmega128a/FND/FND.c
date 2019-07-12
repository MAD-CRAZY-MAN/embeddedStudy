/*
 * FND.c
 *
 * Created: 2019-04-12 오전 10:42:34
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h> 

int main(void)
{
	DDRC = 0xFF;
	
    /* Replace with your application code */
    while (1) 
    {
		PORTC = 0x3F;
		_delay_ms(300);
		PORTC = 0x06;
		_delay_ms(300);
		PORTC = 0x5b;
		_delay_ms(300);
		PORTC = 0x4F;
		_delay_ms(300);
		PORTC = 0x66;
		_delay_ms(300);
		PORTC = 0x6D;
		_delay_ms(300);
		PORTC = 0x7D;
		_delay_ms(300);
		PORTC = 0x27;
		_delay_ms(300);
		PORTC = 0x7F;
		_delay_ms(300);
		PORTC = 0x6F;
		_delay_ms(300);
		
	}
	return 0;
}

