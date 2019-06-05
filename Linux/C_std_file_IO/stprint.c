#include <stdio.h>
#include "student.h"

/*파일에 저장된 모든 학생 정보를 읽어서 출력한다.*/

int main(int argc, char* argv[])
{
	struct student rec;
	FILE *fp;

	if(argc != 2) {
		fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
		return 1;
	}

	if((fp=fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "파일 열기 오류\n");
		return 2;
	}

	printf("--------------------------------------\n");
	printf("%10s %6s %6s\n", "학번", "이름", "점수");
	printf("--------------------------------------\n");

	while(fread(&rec, sizeof(rec), 1, fp) > 0)
		if(rec.id != 0)
			printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);

	printf("--------------------------------------\n");
	fclose(fp);
	return 0;
}
