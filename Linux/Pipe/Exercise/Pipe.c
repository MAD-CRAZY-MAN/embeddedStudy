#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 100

int main(int argc, char* argv[])
{
	int fd[2], n, status;
	int pid1, pid2;
	char line[MAXLINE];
	char string[MAXLINE];

	if((pid1 = fork()) == 0) // 첫 번째 자식 프로세스
	{
		pipe(fd);
		if((pid2 = fork()) == 0)
		{
			close(fd[0]); //읽기용 파이프 닫기

			printf("소문자 문자열 입력: ");
			scanf("%s", string);

			dup2(fd[1], 1); //쓰기용 파이프를 표준 출력에 복제

			close(fd[1]);
			printf("%s", string);
		}
		else
		{
			int i;
			close(fd[1]); //쓰기용 파이프 닫기
			printf("%s: ", "대문자 문자열");

			n = read(fd[0], line, MAXLINE);

			for(i=0;i<n;i++)
			{
				if(line[i] >= 'a' && line[i]<= 'z')							line[i] = line[i] - 32;
			}
			printf("%s", line);
			putchar('\n');
			exit(0);
		}
	}
	wait(&status);
	exit(0);
}
