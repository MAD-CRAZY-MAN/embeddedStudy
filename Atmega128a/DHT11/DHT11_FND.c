/*
 * DHT11_FND.c
 *
 * Created: 2019-11-20 오전 11:02:08
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define DHT11_PIN 4
#include "FND_CHAR.h"
#include <avr/interrupt.h>

uint8_t c = 0, Humi_I, Humi_D, Temp_I, Temp_D, CheckSum;

#define H_T 0
#define H_D 1
#define T_I 2
#define T_D 3
#define CS 4
uint8_t Receive_Data();
void Response();
void Request();

uint8_t count = 0;
ISR(TIMER0_OVF_vect)
{
	int hIi, hId, hDi, hDd;
	count %= 4;
	hId = Humi_I % 10; 
	hIi = (Humi_I - hId)/10; 
	
	//hDd = Humi_D % 10;
	//hDi = (Humi_D - hDd)/10;
	
	if(hIi == 0)
		hIi = _0_;
	else if(hIi == 1)
		hIi = _1_;
	else if(hIi == 2)
		hIi = _2_;
	else if(hIi == 3)
		hIi = _3_;
	else if(hIi == 4)
		hIi = _4_;
	else if(hIi == 5)
		hIi = _5_;
	else if(hIi == 6)
		hIi = _6_;
	else if(hIi == 7)
		hIi = _7_;
	else if(hIi == 8)
		hIi = _8_;	
	else if(hIi == 9)
		hIi = _9_;
	
	if(hId == 0)
		hId = _0_;
	else if(hId == 1)
		hId = _1_;
	else if(hId == 2)
		hId = _2_;
	else if(hId == 3)
		hId = _3_;
	else if(hId == 4)
		hId = _4_;
	else if(hId == 5)
		hId = _5_;
	else if(hId == 6)
		hId = _6_;
	else if(hId == 7)
		hId = _7_;
	else if(hId == 8)
		hId = _8_;
	else if(hId == 9)
		hId = _9_;
	/*
	if(hDi == 0)
		hDi = _0_;
	else if(hDi == 1)
		hDi = _1_;
	else if(hDi == 2)
		hDi = _2_;
	else if(hDi == 3)
		hDi = _3_;
	else if(hDi == 4)
		hDi = _4_;
	else if(hDi == 5)
		hDi = _5_;
	else if(hDi == 6)
		hDi = _6_;
	else if(hDi == 7)
		hDi = _7_;
	else if(hDi == 8)
		hDi = _8_;
	else if(hDi == 9)
		hDi = _9_;
	
	if(hDd == 0)
		hDd = _0_;
	else if(hDd == 1)
		hDd = _1_;
	else if(hDd == 2)
		hDd = _2_;
	else if(hDd == 3)
		hDd = _3_;
	else if(hDd == 4)
		hDd = _4_;
	else if(hDd == 5)
		hDd = _5_;
	else if(hDd == 6)
		hDd = _6_;
	else if(hDd == 7)
		hDd = _7_;
	else if(hDd == 8)
		hDd = _8_;
	else if(hDd == 9)
		hDd = _9_;
	*/
	if (count == 0)
	{
		PORTG = 0x01; 
		PORTA = hIi; 
	}
	else if(count == 1)
	{
		PORTG = 0x02;
		PORTA = hId - 0b10000000;
	}
	else if(count == 2)
	{
		PORTG = 0x04;
		PORTA = _0_;
	}
	else
	{
		PORTG = 0x08;
		PORTA = _0_;
	}
	
	TCNT0 = 0x04;
	count++;
}
int main(void)
{
	DDRA = 0xFF;
	DDRG = 0xFF;
	
	PORTG = 0x00;
	PORTA = 0x00;
	
	TCCR0 = 0x04;
	TCNT0 = 0x04;
	TIMSK = 0x01;
	
	sei();
	char data[5];
	
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
			
		}
		else
		{
			//LCD로 습도를 백분율로 출력
			itoa(Humi_I, data, 10);
		//	MOVE(1, 1);
		//	STRING(data, 2);
		//	STRING(".", 1);
			
			itoa(Humi_D, data, 10);
		//	STRING(data, 1);
		//	STRING("%", 1);
		
			
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

