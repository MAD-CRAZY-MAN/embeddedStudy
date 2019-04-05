#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void My_sleep(void)
{
	int i;
	for(i=0;i<9999999;i++)
	{
	}
	for(i=0;i<9999999;i++)
	{
	}
}

int ledControl(int gpio)
{
	int fd;
	char buf[BUFSIZ];

	fd = open("/sys/class/gpio/export", O_WRONLY);
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	close(fd);
	
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	write(fd, "out", 4);
	close(fd);
	
	
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	write(fd, "1", 2);
	close(fd);

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	close(fd);

	return 0;
}

int main(int argc, char** argv)
{
	int gno, i, num = 10;

	if(argc < 2) {
		printf("Usage : %s GPIO_NO\n", argv[0]);
		return -1;
	}

	while(num)
	{
		for(i=1;i<=4;i++)
		{
			gno = atoi(argv[i]);	
			ledControl(gno);
			sleep(1);
		}
		num--;
	}
	return 0;
}



















