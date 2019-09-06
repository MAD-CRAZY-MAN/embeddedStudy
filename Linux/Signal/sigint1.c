#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void intHandler(int signo);

/* 인터럽트 시그널을 처리한다. */
int main()
{
	signal(SIGINT, intHandler);

	while(1)
		pause();

	printf("실행되지 않음\n");
}

/* SIGINT 처리 함수 */
void intHandler(int signo)
{
	printf("인터럽트 시그널 처리\n");
	printf("시그널 번호: %d\n", signo);
	exit(0);
}
