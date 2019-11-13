/*
 * Sound sensor - Motor.c
 *
 * Created: 2019-10-30 오전 10:53:15
 * Author : tlgus
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
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

int main(void)
{
	DDRE = 0x00;
	PORTE = 0xFF;
	DDRB =0x01;
	char buffer[20];
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRA = 0xFF;
	PORTA = 0x00;
	PORTF = 0x00;
	LCD_INIT();
	int score = 1; 
	int status = -1;
	/* Replace with your application code */
	while (1)
	{
		if(score % 5 == 0)
		{
			status *= -1;
			while (1)
			{
				if(!(PINE & 0x01))
				{
					score++;
					_delay_ms(300);
				}
				if(score % 5 != 0)
					break;
			}
		}
		
		if(status == 1)
			PORTA = 0x01;
		else
			PORTA = 0x00;
		
		if(!(PINF & 0x01))
		{
			score = 0;
			while(!(PINF & 0x01));
		}
		if(!(PINE & 0x01))
		{
			score++;
			_delay_ms(300);
		}
		sprintf(buffer, "Score = %02d", score);
		MOVE(1, 1);
		STRING(buffer, 10);
	}
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

