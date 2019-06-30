#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* 파일 복사 프로그램 */
int main(int argc, char *argv[])
{
	int fd1, fd2, n;
	char buf[BUFSIZ];

	if(argc != 3) {
		fprintf(stderr, "사용법: %s file1 file2 \n", argv[0]);
		exit(1);
	}

	if((fd1 = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	if ((fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1) {
			perror(argv[2]);
			exit(3);
	}

	while((n = read(fd1, buf, BUFSIZ)) > 0)
		write(fd2, buf, n);
	exit(0);
}

