#include <stdio.h>

/* 텍스트 파일 내용을 표준 출력에 프린트 */
int main(int argc, char *argv[])
{
	FILE *fp;
	int c;

	if(argc < 2)
		fp = stdin;	//명령줄 인수가 없으면 표준 입력 사용
	else 
		fp = fopen(argv[1], "r"); //읽기 전용으로 파일 열기

	c = getc(fp);			//파일로부터 문자 읽기
	while(c != EOF) {		//파일 끝이 아니면
		putc(c, stdout);	//읽은 문자를 표준출력에 출력
		c = getc(fp);		//파일로부터 문자 읽기
	}
	fclose(fp);
	return 0;
}
