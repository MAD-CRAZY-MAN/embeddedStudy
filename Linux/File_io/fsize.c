#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 512

/*파일 크기를 계산한다*/
int main(int argc, char *argv[])
{
	char buf[BUFSIZE];
	int fd;
	ssize_t nread; //ssize_t == signed int, size_t == unsigned
	long total = 0;

	if((fd = open(argv[1], O_RDONLY)) == -1)
		perror(argv[1]);

	/*파일의 끝에 도달할 때까지 반복해서 읽으면서 파일 크기를 계산*/
	while((nread = read(fd, buf, BUFSIZE)) > 0)
		total += nread;

	close(fd);
	printf("%s 파일 크기: %ld바이트 \n", argv[1], total);
	exit(0);
}
