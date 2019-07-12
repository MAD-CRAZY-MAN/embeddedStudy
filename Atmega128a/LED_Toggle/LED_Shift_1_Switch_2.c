/*
 * LED_Shift_1_Switch_2.c
 *
 * Created: 2019-04-05 오후 1:45:16
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xff;
	DDRE = 0x00;
	PORTA = 0x01;
	
    /* Replace with your application code */
    while (1) 
    {
		if(!(PINE & 0x01))
		{
			PORTA = (PORTA << 1);
			if(PORTA == 0x00)
			{
				PORTA = 0x01;
			}
			_delay_ms(300);
		}
		else if(!(PINE & 0x02))
		{
			PORTA = (PORTA >> 1);
			if(PORTA == 0x00)
			{
				PORTA = 0x80;
			}
			_delay_ms(300);
		}
    }
	return 0;
}

