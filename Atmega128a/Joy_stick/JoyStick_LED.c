/*
 * Joystick_LED_191023.c
 *
 * Created: 2019-10-23 오전 11:43:10
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>

#define FUNCSET 0x28 //function set, 데이터 선 4비트, 2줄로 표시, 5X7비트 사용
#define ENTMODE 0x06 //entry mode set, LCD표시창에 문자를 표시하고 커서를 오른쪽으로 이동
#define ALLCLR 0x01 //all clear, LCD표시창을 클리어시키고 커서를 첫 줄의 첫 칸에 위치
#define DISPON 0x0c //display on, 표시 on

void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);
void ADC_Init();
int ADC_Read(char channel);

#define ipin PINF
#define iport PORTF
#define ADC_VREF_TYPE 0x20

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRF = 0x00;
	DDRE = 0xFF;
	PORTE = 0xFF;
	
	int ADC_value;
	
	LCD_INIT();
	ADC_Init();
	while (1)
	{
		ADC_value = ADC_Read(0);
		if(ADC_value > 510)//498
			PORTE &= 0b11111011;
		else if(ADC_value < 490)
			PORTE &= 0b11111110;
		else
			PORTE |= 0xFF;
		
		ADC_value = ADC_Read(1);
		if(ADC_value > 525)//514
			PORTE &= 0b11101111;
		else if (ADC_value < 500)
			PORTE &= 0b11110111;
		else
			PORTE |= 0xFF;
		
		ADC_value = ADC_Read(2);
		if(ADC_value > 30)
			PORTE &= 0b11111101;
		else if(ADC_value < 25)
			PORTE &= 0b11111111;
		else
			PORTE |= 0xFF;		
	}
	
	return 0;
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

void COMMAND(unsigned char byte)
{
	_delay_ms(2);

	PORTD = byte & 0xF0;	//명령어 쓰기
	PORTD &= 0b11111100;	//RS = 0, RW = 0
	_delay_us(1);			//RS & RW setup
	
	PORTD |= 0b00000100;	//E = 1, lcd동작
	_delay_us(1);			//E pulse width time
	PORTD &= 0b11111011;	//E = 0
	
	PORTD = (byte<<4) & 0xF0; //명령어 쓰기
	PORTD &= 0b11111100;
	_delay_us(1);
	
	PORTD |= 0b00000100;  //E = 1, lcd동작
	_delay_us(1);
	PORTD &= 0b11111011;  //E = 0
}

void MOVE(int y, int x)
{
	unsigned char data = 0;
	if(y==1)
	{
		data = 0x80 + x - 1;
	}
	else if(y == 2)
	{
		data = 0xC0 + x - 1;
	}
	
	COMMAND(data);
}
void STRING(unsigned char font[], unsigned char n)
{
	_delay_ms(2);
	int i = 0;
	for(;n>0;n--)
	{
		PORTD = font[i] & 0xf0;//상위 4비트 명령어 쓰기
		PORTD |= 0b00000001;//RS = 1, 데이터 설정
		PORTD &= 0b11111101;//RW = 0, 쓰기 설정
		_delay_us(1);
		PORTD |= 0b00000100;//E = 1, lcd 동작
		_delay_us(1);
		PORTD &= 0b11111011;//E = 0
		
		PORTD = (font[i]<<4) & 0xF0;	 //하위 4비트 데이터 쓰기
		PORTD |= 0b00000001;		//RS = 1, 데이터 설정
		PORTD &= 0b11111101;		//RW  = 0, 쓰기 설정
		_delay_us(1);
		PORTD |= 0b00000100;//E = 1, lcd 동작
		_delay_us(1);
		PORTD &= 0b11111011;//E = 0;
		
		_delay_us(40);
		i++;
	}
}
void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTD = byte & 0xf0;//상위 4비트 명령어 쓰기
	PORTD |= 0b00000001;//RS = 1, 데이터 설정
	PORTD &= 0b11111101;//RW = 0, 쓰기 설정
	_delay_us(1);
	PORTD |= 0b00000100;//E = 1, lcd 동작
	_delay_us(1);
	PORTD &= 0b11111011;//E = 0
	
	PORTD = (byte<<4) & 0xF0;	 //하위 4비트 데이터 쓰기
	PORTD |= 0b00000001;		//RS = 1, 데이터 설정
	PORTD &= 0b11111101;		//RW  = 0, 쓰기 설정
	_delay_us(1);
	PORTD |= 0b00000100;//E = 1, lcd 동작
	_delay_us(1);
	PORTD &= 0b11111011;//E = 0;
}



void LCD_INIT(void)
{
	_delay_ms(30);		//전원 투입 후 30ms 이상 지연
	
	//Function set
	//인터페이스(DL) = 0(4bit), 라인(N) = 1(2라인), 폰트(F) = 0(5*8 dot)
	COMMAND(FUNCSET);
	_delay_us(40);

	//Display ON/OFF Control
	//화면 표시(D) = 1(on), 커서(C) = 0(off), 블링크(B) = 0(off)
	COMMAND(DISPON);
	_delay_us(40);

	//Clear Display
	//화면 클리어, 커서 홈위치
	COMMAND(ALLCLR);
	_delay_ms(1.53);
	
	//Entry Mode Set
	//커서 방향(I/D) = 1(address증가), 표시이동(S)=0(이동하지 않음
	COMMAND(ENTMODE);
	_delay_us(40);
	
}
