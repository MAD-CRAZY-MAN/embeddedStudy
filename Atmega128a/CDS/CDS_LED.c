/*
 * CDS_LED.c
 *
 * Created: 2019-10-16 오전 10:13:34
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define CDS_10 340
#define CDS_100 730

void init_adc()
{
	ADMUX = 0x40; //내부 전압사용, ADC 0채널(PF0) 사용
	ADCSRA = 0x87;//adc활성화, prescaler 128
}

int read_adc()
{
	unsigned char adc_low, adc_high;
	unsigned int value;
	ADCSRA |= 0x40; //ADC변환 시작
	while((ADCSRA & 0x10) != 0x10); //변환이 완료되기를 기다림
	adc_low = ADCL; //결과 저장
	adc_high =ADCH; //결과 저장
	value = (adc_high << 5) | adc_low; // 값으로 변환

	return value;
}

void display_LED(value)
{
	if(value<200)
	{
		PORTB = 0x0F;
	}
	else if(value < 800)
	{
		PORTB = 0xFF;
	}
//	else if(value < 750)
	//{
		//PORTB = 0x3F;
//	}
	//else if(value < 1024)
//	{
	//	PORTB = 0xFF;
	//}
}
int main(void)
{
	unsigned int value;
	DDRF = 0x00;
	DDRB = 0xFF;
	
	init_adc();
	while(1)
	{
		value = read_adc();
		display_LED(value);
	}
}

