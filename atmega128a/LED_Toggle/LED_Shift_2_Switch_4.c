/*
 * LED_Shift_2_Switch_4.c
 *
 * Created: 2019-04-05 오후 2:14:22
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xff;
	DDRE = 0x00;
	PORTA = 0x00;
	int mode = 0;
	/* Replace with your application code */
	while (1)
	{
		if(!(PINE & 0x01) || !(PINE & 0x02))
		{
			
			if(!(PINE & 0x01))
			{
				if (mode != 1)
				{
					mode = 1;
					PORTA = 0x01;
				}
				else
					PORTA = (PORTA << 1);
				
				if(PORTA == 0x00)
				{
					PORTA = 0x01;
				}
				_delay_ms(300);
			}
			else if(!(PINE & 0x02))
			{
				if (mode != 1)
				{
					mode = 1;
					PORTA = 0x01;
				}
				else
					PORTA = (PORTA >> 1);
					
				if(PORTA == 0x00)
				{
					PORTA = 0x80;
				}
				_delay_ms(300);
			}
		}
		
		if(!(PINE & 0x04) || !(PINE & 0x08))
		{
			
			if(!(PINE & 0x04))
			{
				if (mode != 2)
				{
					PORTA = 0x03;
					mode = 2;
				}
				else
					PORTA = (PORTA << 2);
	
				if(PORTA == 0x00)
				{
					PORTA = 0x03;
				}
				_delay_ms(300);
			}
			else if(!(PINE & 0x08))
			{
				if (mode != 2)
				{
					PORTA = 0x03;
					mode = 2;
				}
				else
					PORTA = (PORTA >> 2);
	
				if(PORTA == 0x00)
				{
					PORTA = 0xC0;
				}
				_delay_ms(300);
			}
		}
		
	}
	return 0;
}
