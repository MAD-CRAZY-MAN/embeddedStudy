/*
 * LCD_CGRAM_Introdution_190531.c
 *
 * Created: 2019-05-31 오전 10:39:43
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

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRE = 0x00;
	DDRF = 0xFF;
	
	LCD_INIT();
	unsigned int iCnt;
	unsigned int pName[] =
	{
		0x00, 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00,
		0x00, 0x10, 0x10, 0x1F, 0x04, 0x04, 0x1F, 0x00,
		0x00, 0x00, 0x09, 0x09, 0x15, 0x15, 0x15, 0x00,
		0x08, 0x1D, 0x01, 0x0B, 0x09, 0x03, 0x08, 0x0F,
		0x00, 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00,
		0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02, 0x00,
		0x08, 0x0C, 0x0A, 0x09, 0x0A, 0x0C, 0x08, 0x00
		 
	};
	unsigned char english[12] = "My Name is ";
	unsigned char noEnglish[12] = "Jem`appelle";
	
	STRING(english, 11);
	MOVE(2, 1);
	STRING(noEnglish, 11);
	
	COMMAND(0x40);
	for(iCnt = 0; iCnt<56; iCnt++)
	{
		DATA(pName[iCnt]);
	}
	MOVE(1, 12);
	
	for(iCnt=0;iCnt<5;iCnt++)
		DATA(iCnt);
	
	MOVE(2, 12);
	DATA(0x05);
	
	for(iCnt=1;iCnt<4;iCnt++)
		DATA(iCnt);
	DATA(0x06);
	
	/* Replace with your application code */
	while (1)
	{
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
	COMMAND(ENTMODE);
	_delay_us(40);
	
}


