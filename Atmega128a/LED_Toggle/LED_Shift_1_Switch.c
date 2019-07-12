/*
 * LED_Shift_1_Switch.c
 *
 * Created: 2019-04-05 오전 11:21:03
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	PORTA = 0X01;
    /* Replace with your application code */
    while (1) 
    {
		if(!(PINE & 0x01))
		{
			PORTA = (PORTA<<1); 
			
			
			if(PORTA == 0x00)
				PORTA = 0x01;
				
			_delay_ms(300);
		}
    }
	return 0;
}

