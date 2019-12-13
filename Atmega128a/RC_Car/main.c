/*
 * RC_CAR.c
 *
 * Created: 2019-12-11 오전 9:04:37
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>

#define ipin PINF
#define iport PORTF
#define ADC_VREF_TYPE 0x20

#define TRIG 4
#define ECHO 5
#define SOUND_VELOCITY 340UL

void ADC_Init();
int ADC_Read(char channel);
void Motor_Init();
void Ultra_Init();

int main(void)
{
	unsigned int distance;
	unsigned int i;
	
	int ADC_value;
	ADC_Init();
    Motor_Init();
	Timer_Initial();
	Ultra_Init();
	/* Replace with your application code */
    while (1) 
    {	
		TCCR3B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		
		PORTE |= (1<<TRIG);
		_delay_us(10);
		
		PORTE &= ~(1<<TRIG);
		
		while(!(PINE&(1<<ECHO)));
		TCNT3 = 0x0000;
		
		while(PINE & (1<<ECHO));
		TCCR3B = 0x00;
		distance = (unsigned)(SOUND_VELOCITY * (TCNT3 * 4 / 2) / 1000);
		// 거리 = 속도 * 시간

		if(distance>300)
		{
		ADC_value = ADC_Read(1); //y value, motor 	
		if(ADC_value > 530)
			PORTD = 0x01;
		else if(ADC_value < 480)
			PORTD = 0x02;
		else
			PORTD = 0x00;
			
		ADC_value = ADC_Read(0); //y value, motor 
		if(ADC_value > 530)
			OCR1A = 250;
		else if(ADC_value < 480)
			OCR1A = 500;
		else
			OCR1A = 375;
		}
		else
		{
			PORTD = 0x00;
			OCR1A = 375;
		}
	}
}
void Ultra_Init()
{
	DDRE = (DDRE | (1<<TRIG) & ~(1<<ECHO));
}
void Timer_Initial()
{
	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS00) | (1<<CS11);
	ICR1 = 4999; //PWM = fclk_i/o / N(1+TOP)

	TCNT1 = 0x00;
}

void Motor_Init()
{
	DDRD = 0xFF; // DC
	PORTD = 0x00;
	
	DDRB = 0x20; // Servo
	PORTB = 0x00;
}

int ADC_Read(char channel) {
	int ADC_value, adc_low, adc_high;
	ADMUX = (0x40) | (channel & 0x07);
	_delay_us(20);
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & 0x10)!=0x10);
	ADCSRA |= (1<<ADIF);
	
	adc_low = ADCL; //결과 저장
	adc_high =ADCH; //결과 저장
	ADC_value = (adc_high << 8) | adc_low; // 값으로 변환

	return ADC_value;
}

void ADC_Init()
{
	DDRF = 0x00;
	ADCSRA = 0x87;
	ADMUX = 0x40;
}

