/*
 * LCD_190614_DisplayShift_Ex.c
 *
 * Created: 2019-06-14 오후 1:40:00
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define FUNCSET 0x28 //function set, 데이터 선 4비트, 2줄로 표시, 5X7비트 사용
#define ENTMODE 0x06 //entry mode set, LCD표시창에 문자를 표시하고 커서를 오른쪽으로 이동
#define ALLCLR 0x01 //all clear, LCD표시창을 클리어시키고 커서를 첫 줄의 첫 칸에 위치
#define DISPON 0x0c //display on, 표시 on

void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);
void DISPLAY_SHIFT(char p);


int main(void)
{
	/* Replace with your application code */
	//unsigned char string[] = "Je m`appelle";
	int iCnt=1, jCnt, shift;
	int alp[17] = {0x00, 'J', 'e', ' ', 'm', '`', 'a', 'p', 'p', 'e', 'l', 'l', 'e', 0x02, 0x03, 0x04, 0x00};
	unsigned int pName[] =
	{
		0x00, 0x0A, 0x04, 0x04, 0x11, 0x0E, 0x00, 0x00,//웃음 기호
		0x00, 0x10, 0x10, 0x1F, 0x04, 0x04, 0x1F, 0x00,//노
		0x00, 0x00, 0x09, 0x09, 0x15, 0x15, 0x15, 0x00,//시
		0x08, 0x1D, 0x01, 0x0B, 0x09, 0x03, 0x08, 0x0F,//현
	};
	DDRB = 0xFF;
	PORTB = 0x00;
	
	LCD_INIT();
	
	COMMAND(0x40); //CGRAM 저장
	
	for(iCnt=0;iCnt<32;iCnt++)//웃음기호 + 노시현, CGRAM에 저장
	DATA(pName[iCnt]);
	
	MOVE(1,1);
	DATA(alp[17]);
	DISPLAY_SHIFT('R');
	COMMAND(0x02);
	DATA(alp[16]);
	while (1)
	{
	/*	iCnt=1;
		for(jCnt = 1; jCnt <= 16; jCnt++)
		{
			MOVE(iCnt, jCnt);
			DATA('j');
			_delay_ms(500);
			COMMAND(ALLCLR);
			if(jCnt == 16)
			{
					iCnt=2;
					jCnt=0;
			}
		}*/
	
	}
}

void DISPLAY_SHIFT(char p)
{
	if ( p == 'R')
	{
		COMMAND(0x1c);
	}
	if (p == 'L')
	{
		COMMAND(0x18);
	}
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
		PORTB = font[i] & 0xf0;//상위 4비트 명령어 쓰기
		PORTB |= 0b00000001;//RS = 1, 데이터 설정
		PORTB &= 0b11111101;//RW = 0, 쓰기 설정
		_delay_us(1);
		PORTB |= 0b00000100;//E = 1, lcd 동작
		_delay_us(1);
		PORTB &= 0b11111011;//E = 0
		
		PORTB = (font[i]<<4) & 0xF0;	 //하위 4비트 데이터 쓰기
		PORTB |= 0b00000001;		//RS = 1, 데이터 설정
		PORTB &= 0b11111101;		//RW  = 0, 쓰기 설정
		_delay_us(1);
		PORTB |= 0b00000100;//E = 1, lcd 동작
		_delay_us(1);
		PORTB &= 0b11111011;//E = 0;
		
		_delay_us(40);
		i++;
	}
}
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
	//COMMAND(ENTMODE);
	_delay_us(40);
	
}



