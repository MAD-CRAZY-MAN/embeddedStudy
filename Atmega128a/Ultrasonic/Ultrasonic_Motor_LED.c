/*
 * Ultrasonic_Motor_LED.c
 *
 * Created: 2019-09-05 오전 9:57:01
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define TRIG 6
#define ECHO 7
#define  SOUND_VELOCITY 340UL

int main(void)
{
	unsigned int distance;
	unsigned int i;
	DDRB = 0xFF;//led
	PORTB = 0x00;
	
	DDRE = (DDRE | (1<<TRIG) & ~(1<<ECHO));
	DDRD = 0xFF;
	PORTD = 0x00;
	
	while (1)
	{
		
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		
		PORTE |= (1<<TRIG);
		_delay_us(10);
		
		PORTE &= ~(1<<TRIG);
		
		while(!(PINE&(1<<ECHO)));
		TCNT1 = 0x0000;
		
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);
		// 거리 = 속도 * 시간
	
		if(distance<500)
		{
			PORTB = 0xFF;
			PORTD = 0xFF;
		}	
		else
		{
			PORTB = 0x00;
			PORTD = 0x00;
		}
	}
}



