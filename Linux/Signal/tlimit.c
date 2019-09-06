#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int pid;
void alarmHandler();

/* 명령줄 인수로 받은 명령어 실행에 제한 시간을 둔다. */

int main(int argc, char *argv[])
{
	int child, status, limit;

	signal(SIGALRM, alarmHandler);
	sscanf(argv[1], "%d", &limit);
	alarm(limit);

	pid = fork();
	if(pid == 0) {
		execvp(argv[2], &argv[2]); //명령어 실행
		fprintf(stderr, "%s: 실행불가\n", argv[1]);
	}
	else {
		child = wait(&status);
		printf("[%d] 자식 프로세스 %d 종료\n", getpid(), pid);
	}
}

/* SIGALRM처리 함수 */
void alarmHandler()
{
	printf("[알람]자식 프로세스 %d 시간 초과\n", pid);
	kill(pid, SIGINT); //명령어 실행 중인 자신 프로세스 종료
}
