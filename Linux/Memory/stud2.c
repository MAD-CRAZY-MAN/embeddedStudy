#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int id;
	char name[20];
	struct student *next;
};

/* 학생 정보를 입력받아 연결 리스트에 저장하고 학생 정보를 역순으로 출력한다. */ 

int main()
{
	int count = 0, id;
	char name[20];
	struct student *ptr, *head = NULL;
	
	printf("학번과 이름을 입력하세요\n");
	
	while(scanf("%d %s", &id, name) == 2) {
		ptr = (struct student *) malloc(sizeof(struct student));
		if(ptr == NULL) {
			perror("malloc");
			exit(1);
		}
		
		ptr -> id = id;
		strcpy(ptr->name, name);
		
		ptr->next = head;
		head = ptr;
	}
	
	printf("\n*학생 정보(역순)*\n");
	
	//	ptr = head;
	while(ptr != NULL) {
		count++;
		printf("학번: %d 이름: %s \n", ptr->id, ptr->name);
		ptr = ptr->next;
	}
	
	printf("총 %d명입니다.\n", count);
	exit(0);
}
