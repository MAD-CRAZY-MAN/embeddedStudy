/* 다음 예제를 수정하여 모든 시그널을 봉쇄하여 don`t disturb me를 5번
 출력한 후 SIGINT의 봉쇄만 제외하여 disturb me를 출력하는 프로그램을
 작성하시오.*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void main(void)
{
	sigset_t set;
	int count = 5;

	sigfillset(&set);

	sigprocmask(SIG_BLOCK, &set, NULL);

	while(count)
	{
		printf("don`t disturb me (%d)\n", count--);
		sleep(1);
	}

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	
	count = 5;
	while(count)
	{
		printf("disturb me\n");
		count--;
		sleep(1);
	}
}
