#include <stdio.h>
#include <unistd.h>

void main()
{
		int pid, gid;

		printf("[PARENT] PID = %d GID = %d \n", getpid(), getpgrp());
		pid = fork();
		if(pid == 0) {
				setpgid(0, 0);
				printf("[CHILD] PID = %d GID = %d\n", getpid(), getpgrp());
		}
}
