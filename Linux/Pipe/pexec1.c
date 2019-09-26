#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 100

/* 파이프를 통해 자식에서 실행되는 명령어 출력을 받아 프린트 한다.*/

int main(int argc, char* argv[])
{
	int n, pid, fd[2];
	char line[MAXLINE];

	pipe(fd); /* 파이프 생성 */
	
	if ((pid == fork()) == 0) { /* 자식 프로세스 */
		close(fd[0]);
		dup2(fd[1], 1); /* 쓰기용 파이프를 표준 출력에 복제 */
		close(fd[1]);
		execvp(argv[1], &argv[1]);
	}
	else { /* 부모 프로세스 */
		close(fd[1]);
		printf("자식 프로세스로부터 받은 결과\n");
		while ((n = read(fd[0], line, MAXLINE)) > 0)
			write(STDOUT_FILENO, line, n);
	}

	exit(0);
}

