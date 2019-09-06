#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarmHandler(int signo);

/*알람 시그널을 처리한다.*/
int main()
{
	int sec = 0;

	signal(SIGALRM, alarmHandler);
	alarm(5); /*알람 시간 설정*/
	printf("무한 루프\n");
	while(1) {
		sleep(1);
		printf("%d초 경과\n", ++sec);
	}
}
/* SIGALRM 처리 함수 */
void alarmHandler(int signo)
{
	printf("일어나세요\n");
	exit(0);
}

