/*
 * DSM_190829_Ultrasonic_LED.c
 *
 * Created: 2019-08-29 오전 9:52:40
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
	DDRB = 0x10;
	DDRE = (DDRE | (1<<TRIG) & ~(1<<ECHO));
	DDRD = 0xFF;
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
		if(distance < 300) {
			for(i = 0; i<5; i++) {
				PORTD = 0xFF;
				_delay_ms(50);
				PORTD = 0x00;
				_delay_ms(50);
			}
		}
		else if(distance < 500) {
			for(i = 0; i<5; i++) {
				PORTD = 0xFF;
				_delay_ms(100);
				PORTD = 0x00;
				_delay_ms(100);
			}
		}
		else if(distance < 700) {
			for(i = 0; i<5; i++) {
				PORTD = 0xFF;
				_delay_ms(1000);
				PORTD = 0x00;
				_delay_ms(1000);
			}
		}
		else
			PORTD = 0x00;
	}
}

