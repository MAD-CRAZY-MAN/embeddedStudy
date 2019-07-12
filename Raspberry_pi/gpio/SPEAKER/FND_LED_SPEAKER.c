#include <wiringPi.h>
#include <stdio.h>
#include <softTone.h>

#define FND 0
#define SW 29
#define LED 22
#define SPKR 26
#define TOTAL 32

//FND TYPE CA


int notes[] = { 
	391, 391, 440, 440, 391, 391, 329.63, 329.63, \
	391, 391, 329.63, 329.63, 293.66, 293.66, 293.66, 0, \
	391, 391, 440, 440, 391, 391, 329.63, 329.63, \
	391, 329.63, 293.66, 329.63, 261.63, 261.63, 261.63, 0
};

int musicPlay()
{
	while(digitalRead(SW)==LOW);


	int i, j;

	softToneCreate(SPKR);

	while(digitalRead(SW) == HIGH)
	{
		for(i = 0;i < TOTAL; i++)
		{
			for(j = 0; j < 2600000 ; j++)
			{
				if(digitalRead(SW) == LOW)
				{
					softToneWrite(SPKR, 0);
					break;
				}
				softToneWrite(SPKR, notes[i]);
			}
		};
	}
	return 0;
}
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
	int i = 0, j = -1;
	
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
				musicPlay();
			
				while(digitalRead(SW)==LOW);
				delay(30);
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
