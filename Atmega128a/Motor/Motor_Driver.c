/*
 * Motor_Driver_190918.c
 *
 * Created: 2019-09-18 오전 10:44:49
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{

	DDRC = 0xFF;
	DDRB = 0xFF;
	/* Replace with your application code */
	while (1)
	{
		PORTB = 0x01;
		PORTC = 0xB0;
		_delay_ms(5000);
		
		PORTB = 0x00;
		PORTC = 0xC0;
		_delay_ms(5000);
		
		PORTB = 0x08;
		PORTC = 0x70;
		_delay_ms(5000);

		PORTB = 0x00;
		PORTC = 0xC0;
		_delay_ms(5000);
	}
}


