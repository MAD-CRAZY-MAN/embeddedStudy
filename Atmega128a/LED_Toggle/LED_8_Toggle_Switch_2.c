/*
 * LED_8_Toggle_Switch_2.c
 *
 * Created: 2019-04-05 오전 10:59:23
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	PORTA = 0xFF;
	/* Replace with your application code */
	while (1)
	{
		if(!(PINE & 0x01))
		{
			PORTA ^= 0xFF;
			_delay_ms(300);
		}
		
	}
	return 0;
}


