#include <wiringPi.h>
#include <stdio.h>

#define LED 1
#define SW 5

int switchControl()
{
	int i = 0, mode = 1;
	for(i=0;i<4;i++)
	{
		pinMode(LED+i, OUTPUT);
	}
	pinMode(SW, INPUT);
	while(1)
	{	
		for(i=0;i<4;i++)
		{
			digitalWrite(LED+i, HIGH);
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
					while(digitalRead(SW) == LOW);
					delay(30);
				}		
			}
			delay(100);
			digitalWrite(LED+i, LOW);

		}
	}
	
	return 0;
}

int main(int argc, char** argv)
{
	wiringPiSetup();
	
	switchControl();


	return 0;

}
