/*
 * Motor_190918.c
 *
 * Created: 2019-09-18 오전 10:05:05
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{

	DDRB = 0xFF;
	DDRD = 0xFF;
	/* Replace with your application code */
	while (1)
	{
		PORTB = 0x0F;
		PORTD = 0xFF;
		_delay_ms(5000);
			
		PORTB = 0x00;
		PORTD = 0x00;
		_delay_ms(5000);
		
		PORTB = 0x03;
		PORTD = 0xFF;
		_delay_ms(3000);
		
		PORTB = 0x03;
		PORTD = 0x00;
		_delay_ms(3000);
	
	}
}

