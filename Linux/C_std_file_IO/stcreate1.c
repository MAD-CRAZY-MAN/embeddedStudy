#include <stdio.h>
#include "student.h"

/*구조체를 이용하여 학생정보를 파일에 저장한다.*/
int main(int argc, char* argv[])
{
	struct student rec;
	FILE *fp;

	if(argc != 2){
		fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "wb");
	printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");	
	while(scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3)
		fwrite(&rec, sizeof(rec), 1, fp);

	fclose(fp);
	return 0;
}
