#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

/* 디렉터리 내의 파일 이름들을 리스트한다. */
int main(int argc, char *argv[])
{
	DIR *dp;	//열린 디렉터리 정보 저장
	char *dir;	
	struct dirent *d;//디렉터리 내용 저장 구조체
	struct stat st; //파일 상태 저장
	char path[BUFSIZ + 1];

	if(argc == 1)
		dir = "."; //현재 디렉터리를 대상으로
	else 
		dir = argv[1];

	if ((dp = opendir(dir)) == NULL) {
		perror(dir);
		exit(1);
	}

	while ((d = readdir(dp)) != NULL) //각 디렉터리 엔트리를 읽어서 디렉터리  구조체 d에 반환
			printf("%s \n", d->d_name); //파일 이름 출력

	close(dp);	
	exit(0);
}
