#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 잠금 함수를 이용한 학생 데이터 베이스 수정 프로그램 */
int main(int argc, char *argv[])
{
	int fd, id;
	struct student rec;

	if (argc < 2) {
		fprintf(stderr, "사용법: %s file\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("\n수정할 학생의 학번 입력: ");
	while (scanf("%d", &id) == 1) {
		lseek(fd, (long) (id-START_ID) * sizeof(rec), SEEK_SET);
		if (lockf(fd, F_LOCK, sizeof(rec)) == -1) { //쓰기 잠금
			perror(argv[1]);
			exit(3);
		}

		if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0))
			printf("이름: %s\t 학번: %d\t 점수: %d\n", rec.name, rec.id, rec.score);
		else
			printf("레코드 %d 없음\n", id);

		printf("새로운 점수: ");
		scanf("%d", &rec.score);
		lseek(fd, (long) -sizeof(rec), SEEK_CUR);
		write(fd, &rec, sizeof(rec));

		lseek(fd, (long) (id-START_ID) * sizeof(rec), SEEK_SET);
		lockf(fd, F_ULOCK, sizeof(rec)); //잠금 해제
		printf("\n수정할 학생의 학번 입력: ");
	}

	close(fd);
	exit(0);
}
