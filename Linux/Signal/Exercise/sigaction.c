/*
Question1
sigaction 함수를 이용하여 사용자가 인터럽트 키를 입력하면 임의의 함수가 호출
되고 파일에 종료 메시지를 저장하는 프로그램을 작성하시오.
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void Sigint_handler(int signo);
struct sigaction act;

FILE *fp;

int main(void)
{
	fp = fopen("./test.txt", "w");

	act.sa_handler = Sigint_handler;
	sigfillset(&act.sa_mask);

	sigaction(SIGINT, &act, NULL);

	while (1)
	{
		pause();
	}
}

void Sigint_handler(int signo)
{
	fprintf(fp, "%s", "END!\r\n");
	fclose(fp);
	exit(0);
}
