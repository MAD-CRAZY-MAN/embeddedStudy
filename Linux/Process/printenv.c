#include <stdio.h>
#include <stdlib.h>

/*환경변수를 3개 프린트한다.*/

int main(int argc, char *argv[])
{
	char *ptr;

	ptr = getenv("HOME");
	printf("HOME = %s \n", ptr);

	ptr = getenv("SHELL");
	printf("SHELL = %s \n", ptr);

	ptr = getenv("PATH");
	printf("PATH = %s \n", ptr);

	exit(0);
}
