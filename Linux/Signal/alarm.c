#include <unistd.h>
#include <stdio.h>

/*알람 시그널을 보여주는 프로그램*/
int main()
{
	int sec = 0;

	alarm(5);
	printf("무한 루프\n");
	while(1) {
		sleep(1);
		printf("%d초 경과 \n", ++sec);
	}
	printf("실행되지 않음\n");
}
