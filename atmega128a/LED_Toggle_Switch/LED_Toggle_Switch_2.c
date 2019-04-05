/*
 * LED_Toggle_Switch_2.c
 *
 * Created: 2019-04-05 오전 10:12:59
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	/* Replace with your application code */
	PORTB = 0b00001100;
	while (1)
	{
		DDRB = 0b00001100;
		if(!(PINB & 0x01))
		{
			PORTB ^= (PINB = 0x04)^(PINB = 0x08);
			_delay_ms(300);
		}
	}
}


