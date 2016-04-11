#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
	int fd;
	pid_t pid;
	int status;
	char *buf = malloc(sizeof(char) * 1024);
	fd = open(argv[1], O_RDONLY);
	if(fd != -1)
	{
		printf("Parent is going to create a child process\n");
		if((pid=fork())>0)
		{
			sleep(2);
			printf("Parent is waiting\n");
			sleep(1);
			wait(&status);
			printf("Child has terminated with %d\n",WEXITSTATUS(status));
		}
		else
		{
			sleep(1);
			printf("Child process created\n");
			sleep(2);
			if(pid==0)
			{
			while(read(fd, &buf, 1)>0)
				write(1, &buf, 1);
			sleep(5);
			write(1,"Child is terminating.\n",22);
			sleep(5);
			exit(20);
			}
		}
	exit(0);
	}
}