/*
 * Electronic_Piano.c
 *
 * Created: 2019-06-21 오전 10:58:59
 * Author : tlgus
 */ 


#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define FUNCSET 0x28 //function set
#define ENTMODE 0x06 //entry mode set
#define ALLCLR 0x01 //all clear
#define DISPON 0x0c //display on

void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);
void DISPLAY_SHIFT(char p);
void IO_SETTING(void);
void INTRODUCE(int num);
void PIANO_PLAY(void);
void MENU(void);
void PIANO_RECORD(void);
void LISTEN(void);

int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 =0;
int maxTime = -1, maxWhat= -1;

unsigned int recordTime[100] = {};
unsigned int recordWhat[100] = {};
int timeCnt;
int whatCnt;

int main(void)
{
	/* Replace with your application code */
	IO_SETTING();
	LCD_INIT();
	INTRODUCE(0);		

	while (1)
	{
		
		
		PIANO_PLAY();
		if(!(PINC&0x20))				
		{
			while (!(PINC&0x20));
			_delay_ms(50);
			MENU();
			INTRODUCE(1);
		}
		
	}
}

void MENU(void)
{
	int bStat = 0, mode = 1;
	
	unsigned char record[] = "1. Record";
	unsigned char listen[] = "2. Listen";
	unsigned char myExit[] = "3. EXIT";
	COMMAND(ALLCLR);
	
	INTRODUCE(2);
	
	while(mode)
	{
		switch (bStat) {
			case 0 :	MOVE(2,1);
						STRING(record, 9);
						if(!(PINC&0x40))
						{
							while(!(PINC&0x40));
							PIANO_RECORD();
							COMMAND(ALLCLR);
							INTRODUCE(2);
						}
						break;
			
			case 1 :	MOVE(2,1);
						STRING(listen, 9);
						if(!(PINC&0x40))
						{
							while(!(PINC&0x40));
							LISTEN();
							INTRODUCE(2);
						}
						break;
			
			case 2 :	MOVE(2,1);
						STRING(myExit, 7);
						if(!(PINC&0x40))
						{
							mode = 0;
						}
						break;
		}
		if(!(PINC&0x20))
		{
			bStat++;
			bStat %= 3;
			
			COMMAND(ALLCLR);
			INTRODUCE(2);
			while(!(PINC&0x20));
			_delay_ms(30);
		}
	}
}

void LISTEN(void)
{
	unsigned char message[] = "Listening...";
	unsigned char _end[] = "END!";
	unsigned char empty[] = "Record Empty!!";
	
	int mode = 1;
	timeCnt = -1, whatCnt = -1;
	int delay = 0, i;
	while(mode)
	{
		if(whatCnt >= maxWhat) //if listend to the end, return
		{
			if(maxWhat == -1)
			{
				COMMAND(ALLCLR);
				MOVE(2, 1);
				STRING(empty, 14);
				_delay_ms(1000);
				break;
			}
			else
			{
				COMMAND(ALLCLR);
				MOVE(1,1);
				STRING(_end, 4);
				STRING(_end, 4);
				STRING(_end, 4);
				STRING(_end, 4);
				
				MOVE(2,1);
				STRING(_end, 4);
				STRING(_end, 4);
				STRING(_end, 4);
				STRING(_end, 4);
				_delay_ms(1000);
				break;
			}
		}
			
		switch (recordWhat[++whatCnt]) {
			case 0 : COMMAND(ALLCLR);
					 MOVE(1, 4);
					 STRING(message, 12);
					 delay = recordTime[++timeCnt];
					 for(i = 0; i<delay;i++)
						_delay_ms(50);
					 break;
					 
			case 1 : COMMAND(ALLCLR);
					 MOVE(1, 4);
					 STRING(message, 12);
					 MOVE(2, 5);
					 DATA(0x00);
					 
					 delay = recordTime[++timeCnt];
					 for(i=0;i<delay;i++)
						_delay_ms(50);
					 break;
					 
			case 2 : COMMAND(ALLCLR);
					MOVE(1, 4);
					STRING(message, 12);
					MOVE(2, 7);
					DATA(0x00);
					
					delay = recordTime[++timeCnt];
					for(i=0;i<delay;i++)
						_delay_ms(50);
					break;
					
			case 3 : COMMAND(ALLCLR);
					MOVE(1, 4);
					STRING(message, 12);
					MOVE(2, 9);
					DATA(0x00);
					
					delay = recordTime[++timeCnt];
					for(i=0;i<delay;i++)
						_delay_ms(50);
					break;
					
			case 4 : COMMAND(ALLCLR);
					MOVE(1, 4);
					STRING(message, 12);
					MOVE(2, 11);
					DATA(0x00);
					
					delay = recordTime[++timeCnt];
					for(i=0;i<delay;i++)
						_delay_ms(50);	
					break;
			case 5 : COMMAND(ALLCLR);
					MOVE(1, 4);
					STRING(message, 12);
					MOVE(2, 13);
					DATA(0x00);
					
					delay = recordTime[++timeCnt];
					for(i=0;i<delay;i++)
					_delay_ms(50);
						break;
		}
	
		if(!(PINC&0x40)) //if press okay, return;
		{
			mode = 0;
			while(!(PINC&0x40));
			_delay_ms(30);
		}
	}
}
void PIANO_RECORD(void)
{
	unsigned char message[] = "Recording...";
	unsigned char message2[] = "COMPLETE!";
	int mode = 1;
	COMMAND(ALLCLR);
	
	MOVE(1, 4);
	STRING(message, 12);

	int _time = 0;
	timeCnt = -1;
	whatCnt = -1;		
	while(mode)
	{	
		if(!(PINC&0x40)) // record complete
		{
			mode = 0;
			COMMAND(ALLCLR);
			MOVE(1, 5);
			STRING(message2, 9);
			_delay_ms(1000);
			
			while(!(PINC&0x40));
			_delay_ms(30);
		}
		else if(!(PINC&0x01)) //check do time
		{
			recordWhat[++whatCnt] = 1;
		
			while(!(PINC&0x01))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,5);
				DATA(0x00);
			}
			MOVE(2, 5);
			DATA(' ');
			
			recordTime[++timeCnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x02)) //check re time
		{
			recordWhat[++whatCnt] = 2;
			
			while(!(PINC&0x02))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,7);
				DATA(0x00);
			}
			MOVE(2, 7);
			DATA(' ');
			
			recordTime[++timeCnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x04)) //check do time
		{
			recordWhat[++whatCnt] = 3;
			
			while(!(PINC&0x04))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,9);
				DATA(0x00);
			}
			MOVE(2, 9);
			DATA(' ');
			
			recordTime[++timeCnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x08)) //check do time
		{
			recordWhat[++whatCnt] = 4;
			
			while(!(PINC&0x08))
			{
				_delay_ms(50);
				_time++;
				MOVE(2, 11);
				DATA(0x00);
			}
			MOVE(2, 11);
			DATA(' ');
			
			recordTime[++timeCnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x10)) //check do time
		{
			recordWhat[++whatCnt] = 5;
			
			while(!(PINC&0x10))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,13);
				DATA(0x00);
			}
			MOVE(2, 13);
			DATA(' ');
			
			recordTime[++timeCnt] = _time;
			_time = 0;
		}
		else
		{
			recordWhat[++whatCnt] = 0;
			
			while(PINC == 0b01111111)
			{
				_delay_ms(50);
				_time++;
			}

			recordTime[++timeCnt] = _time;
			_time = 0;
		}
	}
	maxTime = timeCnt;
	maxWhat = whatCnt;
	INTRODUCE(2);
}
void INTRODUCE(int num)
{
		/* num == 1, print piano start
		   num == 0, print piano start and power on!*/
 		unsigned char menu[] = "MENU";
	 	unsigned char start[] = "PIANO START";
		unsigned char hello[] = "POWER ON!";
		
		COMMAND(ALLCLR);
		
		if (num==1) // print start, piano mode
		{
			MOVE(1,4);
			STRING(start, 11);
		}
		else if (num == 2) // menu
		{
			MOVE(1, 7);
			STRING(menu, 4);
		}
		else //start, hello
		{
			MOVE(1,4);
			STRING(start, 11);
		
			MOVE(2, 5);
			STRING(hello, 9);
			_delay_ms(1000);
		
			COMMAND(ALLCLR);

			MOVE(1,4);
			STRING(start, 11);
		}
}

void PIANO_PLAY(void)
{		
	if(flag1)
	{
		MOVE(2, 5);
		DATA(0x00);
	}
	else
	{
		MOVE(2, 5);
		DATA(' ');
	}
	
	if(flag2)
	{
		MOVE(2, 7);
		DATA(0x00);
	}
	else 
	{
		MOVE(2, 7);
		DATA(' ');
	}
	
	if(flag3)
	{
		MOVE(2, 9);
		DATA(0x00);
	}
	else
	{
		MOVE(2, 9);
		DATA(' ');
	}
	
	if(flag4)
	{
		MOVE(2, 11);
		DATA(0x00);
	}
	else
	{
		MOVE(2, 11);
		DATA(' ');
	}
	
	if(flag5)
	{
		MOVE(2, 13);
		DATA(0x00);
	}
	else
	{
		MOVE(2, 13);
		DATA(' ');
	}
	
	if(!(PINC&0x01))
		flag1 = 1;
	else
		flag1 = 0;
	
	if(!(PINC&0x02))
		flag2 = 1;
	else
		flag2 = 0;
	
	if(!(PINC&0x04))
		flag3 = 1;
	else
		flag3 = 0;
	
	if(!(PINC&0x08))
		flag4 = 1;
	else
		flag4 = 0;
	
	if(!(PINC&0x10))
		flag5 = 1;
	else
		flag5 = 0;
}
void IO_SETTING(void)
{
	DDRD = 0xFF; //LCD lines output
	DDRC = 0x00; //SW lines input
	
	int iCnt;
	unsigned int pName[] =
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	};
	
	COMMAND(0x40); //SAVE IN CGRAM
	for(iCnt=0;iCnt<8;iCnt++)
		DATA(pName[iCnt]);
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
	//COMMAND(ENTMODE);
	_delay_us(40);
	
}



