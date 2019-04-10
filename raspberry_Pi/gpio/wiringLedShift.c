#include <wiringPi.h>
#include <stdio.h>

#define SW 5
#define LED 1

int switchControl()
{
	int i,  cnt = -1;

	pinMode(SW, INPUT);
	
	for(i=0;i<4;i++)
	{
		pinMode(LED+i, OUTPUT);
	}

	while(1)
	{
		if(digitalRead(SW) == LOW)
		{
			digitalWrite(LED+cnt, LOW);
			cnt++;
			if(cnt==4)
				cnt = 0;
			while(digitalRead(SW) == LOW);
			delay(30);
		}
		digitalWrite(LED+cnt, HIGH);

	}
	
}

int main(int argc, char** argv)
{
	wiringPiSetup();
	
	switchControl();
	
	return 0;
}
