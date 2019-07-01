#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buffer[1024];
	int nread;

	nread = readlink(argv[1], buffer, 1024); //링크 내용 읽기
	if (nread > 0) {
		write(1, buffer, nread); // stdout(모니터) 파일에 출력
		putchar('\n');
		exit(0);
	}
	else
	{
		fprintf(stderr, "오류: 해당 링크 없음\n");
		exit(1);
	}
}
