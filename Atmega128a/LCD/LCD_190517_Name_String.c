/*
 * LCD_190517_Name_String.c
 *
 * Created: 5/17/2019 11:07:43 AM
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define FUNCSET 0x28 //function set, ������ �� 4��Ʈ, 2�ٷ� ǥ��, 5X7��Ʈ ���
#define ENTMODE 0x06 //entry mode set, LCDǥ��â�� ���ڸ� ǥ���ϰ� Ŀ���� ���������� �̵�
#define ALLCLR 0x01 //all clear, LCDǥ��â�� Ŭ�����Ű�� Ŀ���� ù ���� ù ĭ�� ��ġ
#define DISPON 0x0c //display on, ǥ�� on

void STRING(unsigned char font[], unsigned char n)
{
	_delay_ms(2);
	int i = 0;
	for(;n>0;n--)
	{
		PORTB = font[i] & 0xf0;//���� 4��Ʈ ���ɾ� ����
		PORTB |= 0b00000001;//RS = 1, ������ ����
		PORTB &= 0b11111101;//RW = 0, ���� ����
		_delay_us(1);
		PORTB |= 0b00000100;//E = 1, lcd ����
		_delay_us(1);
		PORTB &= 0b11111011;//E = 0
	
		PORTB = (font[i]<<4) & 0xF0;	 //���� 4��Ʈ ������ ����
		PORTB |= 0b00000001;		//RS = 1, ������ ����
		PORTB &= 0b11111101;		//RW  = 0, ���� ����
		_delay_us(1);
		PORTB |= 0b00000100;//E = 1, lcd ����
		_delay_us(1);
		PORTB &= 0b11111011;//E = 0;
		
		if(font[i] != ' ')
			_delay_ms(200);
		else
			_delay_us(40);
		i++;
	}
}
void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTB = byte & 0xf0;//���� 4��Ʈ ���ɾ� ����
	PORTB |= 0b00000001;//RS = 1, ������ ����
	PORTB &= 0b11111101;//RW = 0, ���� ����
	_delay_us(1);
	PORTB |= 0b00000100;//E = 1, lcd ����
	_delay_us(1);
	PORTB &= 0b11111011;//E = 0
	
	PORTB = (byte<<4) & 0xF0;	 //���� 4��Ʈ ������ ����
	PORTB |= 0b00000001;		//RS = 1, ������ ����
	PORTB &= 0b11111101;		//RW  = 0, ���� ����
	_delay_us(1);
	PORTB |= 0b00000100;//E = 1, lcd ����
	_delay_us(1);
	PORTB &= 0b11111011;//E = 0;
}
void COMMAND(unsigned char byte)
{
	_delay_ms(2);

	PORTB = byte & 0xF0;	//���ɾ� ����
	PORTB &= 0b11111100;	//RS = 0, RW = 0
	_delay_us(1);			//RS & RW setup
	
	PORTB |= 0b00000100;	//E = 1, lcd����
	_delay_us(1);			//E pulse width time
	PORTB &= 0b11111011;	//E = 0
	
	PORTB = (byte<<4) & 0xF0; //���ɾ� ����
	PORTB &= 0b11111100;
	_delay_us(1);
	
	PORTB |= 0b00000100;  //E = 1, lcd����
	_delay_us(1);
	PORTB &= 0b11111011;  //E = 0
}


void LCD_INIT(void)
{
	_delay_ms(30);		//���� ���� �� 30ms �̻� ����
	
	//Function set
	//�������̽�(DL) = 0(4bit), ����(N) = 1(2����), ��Ʈ(F) = 0(5*8 dot)
	COMMAND(FUNCSET);
	_delay_us(40);

	//Display ON/OFF Control
	//ȭ�� ǥ��(D) = 1(on), Ŀ��(C) = 0(off), ����ũ(B) = 0(off)
	COMMAND(DISPON);
	_delay_us(40);

	//Clear Display
	//ȭ�� Ŭ����, Ŀ�� Ȩ��ġ
	COMMAND(ALLCLR);
	_delay_ms(1.53);
	
	//Entry Mode Set
	//Ŀ�� ����(I/D) = 1(address����), ǥ���̵�(S)=0(�̵����� ����
	COMMAND(ENTMODE);
	_delay_us(40);
	
}

int main(void)
{
	/* Replace with your application code */
	unsigned char string[] = "Noh Si Hyun";
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	LCD_INIT();

	STRING(string, 11);
	
	while (1)
	{
	}
}
