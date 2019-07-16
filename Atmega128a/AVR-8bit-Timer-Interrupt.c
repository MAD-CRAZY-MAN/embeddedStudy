#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t count = 0;

ISR(TIMER0_OVF_vect)
{
	if(count == 100)
	{		




	}
	TCNT0 = 0x04;
	count++;
}

int main(void)
{
	TCCR0 = 0x04;// 클럭의 분주비를 64로 설정한다. 16000000 / 64 = 250000UL
	TCNT0 = 0x04;//Timer/Counter 레지스터의 초기값을 4로 설정한다. 4 ~ 255
	TIMSK = 0x01;
	
	sei();

	while(1)
	{

	}

	return 0;
}

