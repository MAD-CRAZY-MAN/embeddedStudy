/*다음 예제를 수정하여 부모 프로세스가 fork로 자식 프로세스를 생성한 다음 자식 프로세스는 초기화 완료를 kill함수를 이용하여 부모 프로세스
 에게 알린 후 종료되고 시그널이 반환되는 것을 기다린 후 부모 프로세스도 종료하는 프로그램을 작성하시오.(각 프로세스 종료할 때 화면에 종료
 를 출력해야한다.) */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void quit();

void main(void)
{
	pid_t pid, status, parentId;
	int count = 5;
	
	pid = fork();

	if(pid == 0) //자식 프로세스
	{
		parentId = getppid();
		while (count)
		{
			printf("[childe] count is %d \n", count--);
			sleep(1);
		}
		kill(parentId, SIGALRM);
		printf("[childe] bye!\n");

		raise(SIGKILL);
	}
	else if(pid>0) //부모 프로세스
	{
		signal(SIGALRM, quit);
		wait(&status);//pause()를 이용해도 됨
	}
	else	
		printf("fail to fork\n");
}

void quit()
{
	printf("[parent] bye!\n");
	raise(SIGKILL);
	//kill(getpid(), SIGKILL);
}
