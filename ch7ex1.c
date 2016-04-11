#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
void action();
void child(FILE *);
void parent(FILE *, pid_t);
void action(){sleep(1);}
int main(int argc, char *argv[])
{
	FILE *fp;
	pid_t pid;
	int childRes;
	fp=fopen("wow.txt", "w+");
	setbuf(fp, NULL);
	if((pid=fork())==0)
		child(fp);
	parent(fp, pid);
}
void parent(FILE *fp, pid_t pid)
{
	int childRes, n=0;
	
	while(1)
	{
		signal(SIGUSR1, action);
		pause();
		rewind(fp);
		fread(&childRes, sizeof(int), 1, fp);
		printf("\nParent: child result: %d\n", childRes);
		if(++n>5)
		{
			printf("Parent: work done, bye bye\n");
			kill(0, SIGTERM);
		}
		printf("Parent: waiting for child to start\n\n");
		kill(pid, SIGUSR1);
	}
}
void child(FILE *fp)
{
	int value;
	srand(time(NULL));
	
	while(1)
	{
		sleep(1);
		value=rand()%100;
		rewind(fp);
		fwrite(&value, sizeof(int), 1, fp);
		printf("Child: waiting for parent to start\n\n\n\n");
		signal(SIGUSR1, action);
		kill(getppid(), SIGUSR1);
		pause();
	}
}