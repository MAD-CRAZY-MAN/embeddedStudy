#ifndef LCD_H_
#define LCD_H_

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

	PORTD = byte & 0xF0;	//��ɾ� ����
	PORTD &= 0b11111100;	//RS = 0, RW = 0
	_delay_us(1);			//RS & RW setup
	
	PORTD |= 0b00000100;	//E = 1, lcd����
	_delay_us(1);			//E pulse width time
	PORTD &= 0b11111011;	//E = 0
	
	PORTD = (byte<<4) & 0xF0; //��ɾ� ����
	PORTD &= 0b11111100;
	_delay_us(1);
	
	PORTD |= 0b00000100;  //E = 1, lcd����
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
		PORTD = font[i] & 0xf0;//���� 4��Ʈ ��ɾ� ����
		PORTD |= 0b00000001;//RS = 1, ������ ����
		PORTD &= 0b11111101;//RW = 0, ���� ����
		_delay_us(1);
		PORTD |= 0b00000100;//E = 1, lcd ����
		_delay_us(1);
		PORTD &= 0b11111011;//E = 0
		
		PORTD = (font[i]<<4) & 0xF0;	 //���� 4��Ʈ ������ ����
		PORTD |= 0b00000001;		//RS = 1, ������ ����
		PORTD &= 0b11111101;		//RW  = 0, ���� ����
		_delay_us(1);
		PORTD |= 0b00000100;//E = 1, lcd ����
		_delay_us(1);
		PORTD &= 0b11111011;//E = 0;
		
		_delay_us(40);
		i++;
	}
}
void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTD = byte & 0xf0;//���� 4��Ʈ ��ɾ� ����
	PORTD |= 0b00000001;//RS = 1, ������ ����
	PORTD &= 0b11111101;//RW = 0, ���� ����
	_delay_us(1);
	PORTD |= 0b00000100;//E = 1, lcd ����
	_delay_us(1);
	PORTD &= 0b11111011;//E = 0
	
	PORTD = (byte<<4) & 0xF0;	 //���� 4��Ʈ ������ ����
	PORTD |= 0b00000001;		//RS = 1, ������ ����
	PORTD &= 0b11111101;		//RW  = 0, ���� ����
	_delay_us(1);
	PORTD |= 0b00000100;//E = 1, lcd ����
	_delay_us(1);
	PORTD &= 0b11111011;//E = 0;
}



void LCD_INIT(void)
{
	_delay_ms(30);		//���� ���� �� 30ms �̻� ����
	
	//Function set
	//�������̽�(DL) = 0(4bit), ����(N) = 1(2����), ��Ʈ(F) = 0(5*8 dot)
	COMMAND(FUNCSET);
	_delay_us(40);

	//Display ON/OFF Control
	//ȭ�� ǥ��(D) = 1(on), Ŀ��(C) = 0(off), ��ũ(B) = 0(off)
	COMMAND(DISPON);
	_delay_us(40);

	//Clear Display
	//ȭ�� Ŭ����, Ŀ�� Ȩ��ġ
	COMMAND(ALLCLR);
	_delay_ms(1.53);
	
	//Entry Mode Set
	//Ŀ�� ����(I/D) = 1(address����), ǥ���̵�(S)=0(�̵����� ����
	//COMMAND(ENTMODE);
	_delay_us(40);
	
}



#endif /* LCD_H_ */
