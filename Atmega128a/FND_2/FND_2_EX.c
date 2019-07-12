/*
 * FND_2_EX.c
 *
 * Created: 2019-04-19 오전 10:46:40
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRG = 0xFF;
	PORTG = 0xFF;
	
	/* Replace with your application code */
	while (1)
	{
		PORTA = 0x00;
		PORTB = 0x00;
		_delay_ms(500);
		PORTA = 0xFF;
		PORTB = 0xFF;
		_delay_ms(500);
	}
	return 0;
}

