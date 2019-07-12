/*
 * LED_Counter_Special.c
 *
 * Created: 2019-04-05 오후 3:07:05
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	int mode = 0;
    /* Replace with your application code */
    while (1) 
    {
		if(!(PINE & 0x01))
		{
			mode++;
			_delay_ms(300);
		}
		if(mode == 3)
		{
			PORTA = 0b10101010;
		}
		else if(mode == 6)
		{
			PORTA = 0b01010101;
		}
		else if(mode == 9)
		{
			PORTA = 0xF0;
		}
		else if(mode == 12)
		{
			PORTA = 0x0F;
		}
		else if(mode == 15)
		{
			PORTA = 0x00;
			mode = 0;
		}
	}
	
}

