#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
void action()
{
	sleep(2);
	printf("Switching.\n");
}
int main()
{
	pid_t pid;
	if((pid=fork())>0)
	{
		usleep(2);
		signal(SIGUSR1, action);
		while(1)
		{
			
			printf("Parent is running.\n");
			kill(pid, SIGUSR1);
			pause();
		}
	}
	else
	{
		signal(SIGUSR1, action);
			while(1)
			{
				pause();
				printf("Child is running.\n");
				kill(getppid(), SIGUSR1);
			}
	}
}