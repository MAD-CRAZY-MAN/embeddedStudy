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
	TCCR0 = 0x04;// Ŭ���� ���ֺ� 64�� �����Ѵ�. 16000000 / 64 = 250000UL
	TCNT0 = 0x04;//Timer/Counter ���������� �ʱⰪ�� 4�� �����Ѵ�. 4 ~ 255
	TIMSK = 0x01;
	
	sei();

	while(1)
	{

	}

	return 0;
}

