#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 파일 타입을 검사한다 */
int main(int argc, char *argv[])
{
	int i;
	struct stat buf;

	for (i=1;i<argc;i++)
	{
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			perror("lstat()");
			continue;
		}

		if (S_ISREG(buf.st_mode))
			printf("%s \n", "일반 파일");
		if (S_ISDIR(buf.st_mode))
			printf("%s \n", "디렉터리");
		if (S_ISCHR(buf.st_mode))
			printf("%s \n", "문자 장치 파일");
		if (S_ISBLK(buf.st_mode))
			printf("%s \n", "블록 장치 파일");
		if (S_ISFIFO(buf.st_mode))
			printf("%s \n", "FIFO 파일");
		if (S_ISLNK(buf.st_mode))
			printf("%s \n", "심볼릭 링크");
		if (S_ISSOCK(buf.st_mode))
			printf("%s \n", "소켓");
	}
	exit(0);
}
