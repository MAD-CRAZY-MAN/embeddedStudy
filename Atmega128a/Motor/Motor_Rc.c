/*
 * Motor_Rc190919.c
 *
 * Created: 2019-09-19 오전 9:15:01
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		if (PINA & 0x01)
		{
			PORTB = 0x01;
			PORTC = 0x22;	
		}
		if (PINA & 0x02)
		{
			PORTB = 0x06;
			PORTC = 0x12;
		}
		if (PINA & 0x04)
		{
			PORTB = 0x0E;
			PORTC = 0x00;
		}
		if (PINA & 0x08)
		{
			PORTB = 0x0C;
			PORTC = 0x21;
		}
		if (PINA & 0x10)
		{
			PORTB = 0x10;
			PORTC = 0x11;
		}
    }
}

