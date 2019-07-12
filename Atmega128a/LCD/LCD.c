/*
 * LCD.c
 *
 * Created: 5/10/2019 1:36:08 PM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define FUNCSET 0x28 //function set, 데이터 선 4비트, 2줄로 표시, 5X7비트 사용
#define ENTMODE 0x06 //entry mode set, LCD표시창에 문자를 표시하고 커서를 오른쪽으로 이동
#define ALLCLR 0x01 //all clear, LCD표시창을 클리어시키고 커서를 첫 줄의 첫 칸에 위치
#define DISPON 0x0c //display on, 표시 on

void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTB = byte & 0xf0;//상위 4비트 명령어 쓰기
	PORTB |= 0b00000001;//RS = 1, 데이터 설정
	PORTB &= 0b11111101;//RW = 0, 쓰기 설정
	_delay_us(1);
	PORTB |= 0b00000100;//E = 1, lcd 동작
	_delay_us(1);
	PORTB &= 0b11111011;//E = 0
	
	PORTB = (byte<<4) & 0xF0;	 //하위 4비트 데이터 쓰기
	PORTB |= 0b00000001;		//RS = 1, 데이터 설정
	PORTB &= 0b11111101;		//RW  = 0, 쓰기 설정
	_delay_us(1);
	PORTB |= 0b00000100;//E = 1, lcd 동작
	_delay_us(1);
	PORTB &= 0b11111011;//E = 0;
}
void COMMAND(unsigned char byte)
{
	_delay_ms(2);

	PORTB = byte & 0xF0;	//명령어 쓰기
	PORTB &= 0b11111100;	//RS = 0, RW = 0
	_delay_us(1);			//RS & RW setup
	
	PORTB |= 0b00000100;	//E = 1, lcd동작
	_delay_us(1);			//E pulse width time
	PORTB &= 0b11111011;	//E = 0
	
	PORTB = (byte<<4) & 0xF0; //명령어 쓰기
	PORTB &= 0b11111100;
	_delay_us(1);
	
	PORTB |= 0b00000100;  //E = 1, lcd동작
	_delay_us(1);
	PORTB &= 0b11111011;  //E = 0
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

int main(void)
{
	/* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	LCD_INIT();
	DATA('h');
	while (1)
	{
	}
}