/*
 * DSM_190828_Ultrasonic_Buzzer.c
 *
 * Created: 2019-08-28 오전 10:00:03
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
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(50);
		}
		else if(distance < 500) {
			for(i = 0; i<5; i++) {
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(100);
		}
		else if(distance < 700) {
			for(i = 0; i<5; i++) {
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(200);
		}	
	}
}