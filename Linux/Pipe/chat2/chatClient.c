#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 256

int main() {
	int fd1, fd2, n;
	char inmsg[MAXLINE];
	fd1 = open("./chatfifo1", O_RDONLY);
	fd2 = open("./chatfifo2", O_WRONLY);

	if ( fd1 == -1 || fd2 == -1) {
		perror("open");
		exit(1);
	}

	printf("*클라이언트 시작 \n");
	while (1) {
		n = read(fd1, inmsg, MAXLINE); //첫 번째 파이프에서 받기
		printf("[서버] -> %s\n", inmsg);
		printf("[클라이언트]: ");
		fgets(inmsg, MAXLINE, stdin);
		write(fd2, inmsg, strlen(inmsg) + 1); // 두 번째 파이프에 보내기
	}
}
