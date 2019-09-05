/*
 * Ultrasonic_cm.c
 *
 * Created: 2019-09-04 오전 11:53:29
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define FUNCSET 0x28
#define ENTMODE 0x06
#define ALLCLR 0x01
#define DISPON 0x0c

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);

int main(void)
{
	unsigned int distance;
	
	DDRB = 0x10;
	DDRE = (DDRE | (1<<TRIG) & ~(1<<ECHO));
	int i;
	DDRA = 0xFF; // LCD
	PORTA = 0x00;
	
	LCD_INIT();
	int mode = 0;
	
	STRING("CM: ", 4);
	char cm[4];
	/* Replace with your application code */
	while (1)
	{
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		
		PORTE |= (1<<TRIG);
		_delay_us(10);
		
		PORTE &= ~(1<<TRIG);
		
		while(!(PINE&(1<<ECHO)));
		TCNT1 = 0x0000;
		
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);
		
		MOVE(1,1);
		
		sprintf(cm, "CM: %2d", distance/10);
		STRING(cm, 6);
		_delay_ms(300);
		
	}
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






