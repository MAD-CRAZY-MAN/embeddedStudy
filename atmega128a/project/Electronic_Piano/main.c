/*
 * Electronic_Piano.c
 *
 * Created: 2019-06-21 Ïò§Ï†Ñ 10:58:59
 * Author : tlgus
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "CHAR_FND.h"

void DISPLAY_SHIFT(char p);
void IO_SETTING(void);
void INTRODUCE(int num);
void PIANO_PLAY(void);
void MENU(void);
void PIANO_RECORD(void);
void LISTEN(void);
void TIMER_SETTING(void);
void OFF_FND(void);

int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 =0;
int maxCnt = 0;

int min = 0, sec = 0, ms = 0;
int num[10] = {_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_};
int fndChk = -1;
	
unsigned int recordTime[200] = {};
unsigned int recordWhat[200] = {};


int main(void)
{
	/* Replace with your application code */
	IO_SETTING();
	LCD_INIT();
	TIMER_SETTING();
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

ISR(TIMER0_OVF_vect)
{
	ms++;
	fndChk++;
	fndChk %= 4;
	
	if(ms == 1000)
	{
		ms = 0;
		sec++;
	}
	
	if(sec == 60)
	{
		sec = 0;
		min ++;
	}
	if(min == 10)
	{
		min = 0;
	}
	
	if(fndChk==0)
	{
		PORTF = 0x08;
		PORTE = num[min] & 0x7F;
	}
	else if(fndChk==1)
	{
		PORTF = 0x04;
		PORTE = num[(sec-sec%10)/10];
	}
	else if (fndChk==2)
	{
		PORTF = 0x02;
		PORTE = num[sec%10] & 0x7F;
	}
	else if(fndChk==3)
	{
		PORTF = 0x01;
		PORTE = num[ms/100];
	}

	TCNT0 = 0x04;
}

void TIMER_SETTING(void)
{
	TCCR0 = 0x04; // ≈¨∑∞¿« ∫–¡÷∫Ò∏¶ 64∑Œ º≥¡§«—¥Ÿ. 16000000 / 64 = 250000UL
	TCNT0 = 0x04; //Timer/Counter ∑π¡ˆΩ∫≈Õ¿« √ ±‚∞™¿ª 4∑Œ º≥¡§«—¥Ÿ. 4 ~ 255
	TIMSK = 0x01; //ø¿πˆ«√∑Œ ¿Œ≈Õ∑¥∆Æ
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
							while(!(PINC&0x40));
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

void OFF_FND()
{
	PORTF = 0x08;
	PORTE = 0xFF;
	_delay_ms(1);
	
	PORTF = 0x04;
	PORTE = 0xFF;
	_delay_ms(1);
	
	PORTF = 0x02;
	PORTE = 0xFF;
	_delay_ms(1);
	
	PORTF = 0x02;
	PORTE = 0xFF;
	_delay_ms(1);
	
	TCNT0 = 0x04;
	
	fndChk = -1;
	min = 0, sec = 0, ms = 0;
}
void PIANO_RECORD(void)
{
	sei();
	unsigned char message[] = "Recording...";
	unsigned char message2[] = "COMPLETE!";
	int mode = 1;
	PORTB = 0x01;
	COMMAND(ALLCLR);
	
	MOVE(1, 4);
	STRING(message, 12);

	int _time = 0;
	int Cnt = 0;
	while(mode)
	{
		if(!(PINC&0x40)) // record complete
		{
			mode = 0;
			cli();	//¿Œ≈Õ∑¥∆Æ ¡æ∑·
			OFF_FND();//fnd ≤Ù±‚, ¿Œ≈Õ∑¥∆Æ √ ±‚»≠
			PORTB = 0x00; //led off
			
			COMMAND(ALLCLR);
			MOVE(1, 5);
			STRING(message2, 9);
			_delay_ms(1000);
			
			while(!(PINC&0x40));
			_delay_ms(30);
		}
		else if(!(PINC&0x01)) //check do time
		{
			recordWhat[Cnt++] = 1;
			
			while(!(PINC&0x01))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,5);
				DATA(0x00);
			}
			MOVE(2, 5);
			DATA(' ');
			
			recordTime[Cnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x02)) //check re time
		{
			recordWhat[Cnt++] = 2;
			
			while(!(PINC&0x02))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,7);
				DATA(0x00);
			}
			MOVE(2, 7);
			DATA(' ');
			
			recordTime[Cnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x04)) //check mi time
		{
			recordWhat[Cnt++] = 3;
			
			while(!(PINC&0x04))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,9);
				DATA(0x00);
			}
			MOVE(2, 9);
			DATA(' ');
			
			recordTime[Cnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x08)) //check pa time
		{
			recordWhat[Cnt++] = 4;
			
			while(!(PINC&0x08))
			{
				_delay_ms(50);
				_time++;
				MOVE(2, 11);
				DATA(0x00);
			}
			MOVE(2, 11);
			DATA(' ');
			
			recordTime[Cnt] = _time;
			_time = 0;
		}
		else if(!(PINC&0x10)) //check sol time
		{
			recordWhat[Cnt++] = 5;
			
			while(!(PINC&0x10))
			{
				_delay_ms(50);
				_time++;
				MOVE(2,13);
				DATA(0x00);
			}
			MOVE(2, 13);
			DATA(' ');
			
			recordTime[Cnt] = _time;
			_time = 0;
		}
		else if(PINC == 0b01111111) //check none time
		{
			recordWhat[Cnt++] = 0;
			
			while(PINC == 0b01111111)
			{
				_delay_ms(50);
				_time++;
			}

			recordTime[Cnt] = _time;
			_time = 0;
		}
	}

	maxCnt = Cnt;
	maxCnt = Cnt;
	
	INTRODUCE(2);
}

void LISTEN(void)
{
	unsigned char message[] = "Listening...";
	unsigned char _end[] = "End of Play!";
	unsigned char empty[] = "Record Empty!!";
	
	int mode = 1;
	int iCnt = 0;
	int delay = 0, i;
	
	COMMAND(ALLCLR);
	MOVE(1, 3);
	STRING(message, 12);
	while(mode)
	{
		if(iCnt == maxCnt) //if listend to the end, return
		{
			if(maxCnt == 0)
			{
				COMMAND(ALLCLR);
				MOVE(1, 1);
				STRING(empty, 14);
				_delay_ms(1000);
				break;
			}
			else
			{
				COMMAND(ALLCLR);
				MOVE(1,1);
				STRING(_end, 12);
				_delay_ms(1500);
				break;
			}
		}

		switch (recordWhat[iCnt++]) {
			case 0 : delay = recordTime[iCnt];
					 for(i = 0; i<delay;i++)
					 {
						if(!(PINC&0x40)) //if press okay, return;
						{
							mode = 0;
							break;
						}
						_delay_ms(50);
					 }
					 break;
					 
			case 1 : MOVE(2, 5);
					 DATA(0x00);
					 
					 delay = recordTime[iCnt];
					 for(i=0;i<delay;i++)
					 {
						if(!(PINC&0x40)) //if press okay, return;
				 		{
					 		mode = 0;
					 		break;
				 		}
						_delay_ms(50);
					 }
					 MOVE(2, 5);
					 DATA(' ');
					 break;
					 
			case 2 :MOVE(2, 7);
					DATA(0x00);
					
					delay = recordTime[iCnt];
					for(i=0;i<delay;i++)
					{
						_delay_ms(50);
						if(!(PINC&0x40)) //if press okay, return;
						{
							mode = 0;
							break;
						}
					}
					MOVE(2, 7);
					DATA(' ');
					break;
					
			case 3 :MOVE(2, 9);
					DATA(0x00);
					
					delay = recordTime[iCnt];
					for(i=0;i<delay;i++)
					{
						if(!(PINC&0x40)) //if press okay, return;
						{
							mode = 0;
							break;
						}
						_delay_ms(50);
					}
					MOVE(2, 9);
					DATA(' ');
					break;
					
			case 4 :MOVE(2, 11);
					DATA(0x00);
					
					delay = recordTime[iCnt];
					for(i=0;i<delay;i++)
					{
						if(!(PINC&0x40)) //if press okay, return;
						{
							mode = 0;
							break;
						}
						_delay_ms(50);	
					}
					MOVE(2, 11);
					DATA(' ');
					break;
					
			case 5 :MOVE(2, 13);
					DATA(0x00);
					
					delay = recordTime[iCnt];
					for(i=0;i<delay;i++)
					{
						if(!(PINC&0x40)) //if press okay, return;
						{
							mode = 0;
							break;
						}
					   _delay_ms(50);
					}
					MOVE(2, 13);
					DATA(' ');
					break;
		}
		
	}
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
		else if (num == 0)//start, hello
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
	DDRD = 0xFF; //LCD PORT output
	DDRC = 0x00; //SWITCH PORT input
	DDRB = 0xFF; //LED PORT output
	DDRE = 0xFF; //FND PORT output
	DDRF = 0xFF; //FND COM PORT output
	
	PORTC = 0x00; //switch init
	PORTE = 0xFF; //FND init
	int iCnt;
	unsigned int pName[] =
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	};
	
	COMMAND(0x40); //SAVE IN CGRAM
	for(iCnt=0;iCnt<8;iCnt++)
		DATA(pName[iCnt]);
}



