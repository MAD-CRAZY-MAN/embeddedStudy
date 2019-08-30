#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	int id;
	char name[20];
};

int main(void)
{
	struct student *ptr;
	int n=0, i;
	int id;
	char name[20];
		
	printf("학번 이름을 입력하세요\n");
	ptr = (struct student*)malloc(n * sizeof(struct student));	
	
	while(scanf("%d %s", &id, name) == 2)
	{
		n++;
		
		ptr = (struct student*)realloc(ptr, n * sizeof(struct student));	
	
		if(ptr == NULL) {
			perror("malloc");
			exit(2);
		}
		ptr[n-1].id = id;
		strcpy(ptr[n-1].name, name);
	}
	
	printf("\n* 학생 정보(역순) *\n");
	for(i = n-1;i>=0;i--)
		printf("%d %s\n", ptr[i].id, ptr[i].name);
	
	printf("\n");
	exit(0);
}
