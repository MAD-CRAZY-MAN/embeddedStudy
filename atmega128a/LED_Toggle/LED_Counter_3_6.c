/*
 * LED_Counter_3_6.c
 *
 * Created: 2019-04-05 오후 3:04:22
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	int cnt = 0;
	
    /* Replace with your application code */
    while (1) 
    {
		if(!(PINE & (1<<PINE0)))
		{
			_delay_ms(30);
			cnt++;
			if(cnt == 3)
			{
				PORTA = 0xFF;
			}
			else if(cnt == 6)
			{
				PORTA = 0x00;
				cnt = 0 ;
			}
			while(!(PINE & 0x01))
			{
				_delay_ms(30);
			}
		}
	}
}

