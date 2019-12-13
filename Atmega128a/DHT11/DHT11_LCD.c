/*
 * GccApplication1.c
 *
 * Created: 2019-11-13 오전 9:46:10
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define DHT11_PIN 4

#define FUNCSET 0x28 //function set, 데이터 선 4비트, 2줄로 표시, 5X7비트 사용
#define ENTMODE 0x06 //entry mode set, LCD표시창에 문자를 표시하고 커서를 오른쪽으로 이동
#define ALLCLR 0x01 //all clear, LCD표시창을 클리어시키고 커서를 첫 줄의 첫 칸에 위치
#define DISPON 0x0c //display on, 표시 on

void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);

uint8_t c = 0, Humi_I, Humi_D, Temp_I, Temp_D, CheckSum;

#define H_T 0
#define H_D 1
#define T_I 2
#define T_D 3
#define CS 4
uint8_t Receive_Data();
void Response();
void Request();

int main(void)
{
	DDRA = 0xFF;
	
	PORTA = 0x00;
	LCD_INIT();
	char data[5];
	char error_msg[20] = "Checksum error";
    /* Replace with your application code */
    while (1) 
    {
		Request();//start pulse
		Response();//response pulse
		
		Humi_I = Receive_Data();//humi 정수
		Humi_D = Receive_Data();//humi 실수
		Temp_I = Receive_Data();//temp 정수
		Temp_D = Receive_Data();//temp 실수
		CheckSum = Receive_Data();//check sum
		
		if((Humi_I + Humi_D + Temp_I + Temp_D) != CheckSum)//Check Sum이 걸렸을 떄와 안걸렸을 떄
		{
			MOVE(1, 1);
			STRING(error_msg, 14);		//error 메세지
			_delay_ms(300);
			COMMAND(ALLCLR);
		}
		else
		{
			//LCD로 습도를 백분율로 출력
			itoa(Humi_I, data, 10);
			MOVE(1, 1);
			STRING(data, 2);
			STRING(".", 1);
			
			itoa(Humi_D, data, 10);
			STRING(data, 1);
			STRING("%", 1);

			//LCD로 온도를 C단위로 출력
			itoa(Temp_I, data, 10);
			MOVE(2, 1);
			STRING(data, 2);
			STRING(".", 1);
			
			itoa(Temp_D, data, 10);
			STRING(data, 1);
			STRING("C", 1);
			
			//LCD에 체크섬 출력
			itoa(CheckSum, data, 10);
			
			if(CheckSum>=100)
			{
				MOVE(2, 9);
				STRING(data, 3);
			}
			else
			{
				MOVE(2, 9);
				STRING("0", 1);
				MOVE(2, 10);
				STRING(data, 2);
			}
		}
		_delay_ms(300);
	}
}

void Request()
{
	DDRD |= (1<<DHT11_PIN);
	
	PORTD &= ~(1<<DHT11_PIN);
	_delay_ms(18);
	PORTD |= (1<<DHT11_PIN);	
}

void Response()
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN)) == 0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_Data()
{
	for(int b=0; b<8; b++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);
		_delay_us(35);
		if(PIND & (1<<DHT11_PIN))
		{
			c = (c<<1)|(0x01);
		}
		else
		{
			c = (c<<1)|(0x00);
		}
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}
void COMMAND(unsigned char byte)
{
	_delay_ms(2);

	PORTA = byte & 0xF0;	//명령어 쓰기
	PORTA &= 0b11111100;	//RS = 0, RW = 0
	_delay_us(1);			//RS & RW setup
	
	PORTA |= 0b00000100;	//E = 1, lcd동작
	_delay_us(1);			//E pulse width time
	PORTA &= 0b11111011;	//E = 0
	
	PORTA = (byte<<4) & 0xF0; //명령어 쓰기
	PORTA &= 0b11111100;
	_delay_us(1);
	
	PORTA |= 0b00000100;  //E = 1, lcd동작
	_delay_us(1);
	PORTA &= 0b11111011;  //E = 0
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
		PORTA = font[i] & 0xf0;//상위 4비트 명령어 쓰기
		PORTA |= 0b00000001;//RS = 1, 데이터 설정
		PORTA &= 0b11111101;//RW = 0, 쓰기 설정
		_delay_us(1);
		PORTA |= 0b00000100;//E = 1, lcd 동작
		_delay_us(1);
		PORTA &= 0b11111011;//E = 0
		
		PORTA = (font[i]<<4) & 0xF0;	 //하위 4비트 데이터 쓰기
		PORTA |= 0b00000001;		//RS = 1, 데이터 설정
		PORTA &= 0b11111101;		//RW  = 0, 쓰기 설정
		_delay_us(1);
		PORTA |= 0b00000100;//E = 1, lcd 동작
		_delay_us(1);
		PORTA &= 0b11111011;//E = 0;
		
		_delay_us(40);
		i++;
	}
}
void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTA = byte & 0xf0;//상위 4비트 명령어 쓰기
	PORTA |= 0b00000001;//RS = 1, 데이터 설정
	PORTA &= 0b11111101;//RW = 0, 쓰기 설정
	_delay_us(1);
	PORTA |= 0b00000100;//E = 1, lcd 동작
	_delay_us(1);
	PORTA &= 0b11111011;//E = 0
	
	PORTA = (byte<<4) & 0xF0;	 //하위 4비트 데이터 쓰기
	PORTA |= 0b00000001;		//RS = 1, 데이터 설정
	PORTA &= 0b11111101;		//RW  = 0, 쓰기 설정
	_delay_us(1);
	PORTA |= 0b00000100;//E = 1, lcd 동작
	_delay_us(1);
	PORTA &= 0b11111011;//E = 0;
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
