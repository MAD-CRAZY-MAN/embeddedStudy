/*
 * Servo_PWM.c
 *
 * Created: 2019-10-02 오전 9:36:00
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

void Timer_Initial()
{
	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS00) | (1<<CS11);
	ICR1 = 4999; //PWM = fclk_i/o / N(1+TOP)

	TCNT1 = 0x00;
}

int main(void)
{
	DDRB = 0x20;
	PORTB = 0x00;
	Timer_Initial();
	
    /* Replace with your application code */
    while (1) 
    {
		OCR1A = 250;
		_delay_ms(500);
		OCR1A = 312;
		_delay_ms(500);
		OCR1A = 375;
		_delay_ms(500);
		OCR1A = 437;
		_delay_ms(500);
		OCR1A = 500;
		_delay_ms(500);
	}
}

