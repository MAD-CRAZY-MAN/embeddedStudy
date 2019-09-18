/*
 * Motor_Driver_FND_LCD_190918.c
 *
 * Created: 2019-09-18 오전 11:29:14
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0x00;
	DDRC = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;
	/* Replace with your application code */
	while (1)
	{

		if((PINA & 0x01))
		{
			PORTB = 0x01;
			PORTC = 0xB0;
			PORTD = 0x01;
		}
		
		if((PINA & 0x02))
		{
			PORTB = 0x00;
			PORTC = 0xC0;
			PORTD = 0x00;
		}
		
		if((PINA & 0x04))
		{
			PORTB = 0x08;
			PORTC = 0x70;
			PORTD = 0x02;
		}
	}
}
