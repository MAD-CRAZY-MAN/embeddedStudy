#include <wiringPi.h>
#include <stdio.h>

#define FND 0
#define SW 29
#define LED 22
//FND TYPE CA

void writeFnd(int fnd, int value)
{
	int i;
	if(fnd == 0)
	{
		digitalWrite(1, value);
		digitalWrite(2, value);
		digitalWrite(3, value);
		digitalWrite(4, value);
		digitalWrite(5, value);
		digitalWrite(6, value);
	}
	else if(fnd == 1)
	{	
		digitalWrite(2, value);
		digitalWrite(3, value);
	}
	else if(fnd == 2)
	{
		digitalWrite(1, value);
		digitalWrite(2, value);
		digitalWrite(7, value);
		digitalWrite(5, value);
		digitalWrite(4, value);
	}
	else if(fnd == 3)
	{
		digitalWrite(1, value);
		digitalWrite(2, value);
		digitalWrite(3, value);
		digitalWrite(4, value);
		digitalWrite(7, value);
	}
	else if(fnd == 4)
	{
		digitalWrite(6, value);
		digitalWrite(2, value);
		digitalWrite(3, value);
		digitalWrite(7, value);
	}
	else if(fnd == 5)
	{
		digitalWrite(1, value);
		digitalWrite(6, value);
		digitalWrite(7, value);
		digitalWrite(3, value);
		digitalWrite(4, value);
	}
	else if(fnd == 6)
	{
		digitalWrite(1, value);
		digitalWrite(6, value);
		digitalWrite(7, value);
		digitalWrite(5, value);
		digitalWrite(4, value);
		digitalWrite(3, value);
	}
	else if(fnd == 7)
	{
		digitalWrite(1, value);
		digitalWrite(2, value);
		digitalWrite(3, value);
		digitalWrite(6, value);
	}
	else if(fnd == 8)
	{
		for(i=1;i<8;i++)
		{
			digitalWrite(FND+i, value);
		}
	}
	else if(fnd == 9)
	{
		digitalWrite(1, value);
		digitalWrite(2, value);
		digitalWrite(3, value);
		digitalWrite(4, value);
		digitalWrite(7, value);
		digitalWrite(6, value);
	}

}
int ledControl(int j, int value)
{
	if(value == HIGH)
	{
		if(j<3)
			j++;
		else
			j=0;
	}
	digitalWrite(LED+j, value);

	return j;
}



int fndControl()
{
	int i = 0, j = -1, mode = 1;
	
	for(i=1;i<8;i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(FND+i, HIGH);
	}
	for(i=22;i<26;i++)
	{
		pinMode(i,OUTPUT);
		delay(30);
		digitalWrite(i, LOW);
	}
	pinMode(SW, INPUT);
	
	
	while(1)
	{
		for(i=0;i<10;i++)
		{
			j = ledControl(j, HIGH);
			writeFnd(i, LOW);
			if(digitalRead(SW)==LOW)
			{
				mode *= -1;
				while(digitalRead(SW)==LOW);
				delay(30);
			}
			while(mode == -1)
			{
				if(digitalRead(SW)==LOW)
				{
					mode *= -1;
					while(digitalRead(SW)==LOW);
					delay(30);
				}
			}
			delay(100);
			j = ledControl(j, LOW);
			writeFnd(FND+i, HIGH);
		}
	}
	return 0;
}


	
int main(int argc, char** argv)
{
	wiringPiSetup();

	fndControl();

	return 0;
}
