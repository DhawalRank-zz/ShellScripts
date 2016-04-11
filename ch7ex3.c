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
void parent(int *fd, char *argv[]);
void child(int *fd, char *argv[]);
int main(int argc, char *argv[])
{
	int fd[2];
	
	if(pipe(fd)==-1) exit(1);
	if(fork()>0)
		parent(fd, argv);
	else
		child(fd, argv);
}
void parent(int *fd, char *argv[])
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execlp(argv[1], argv[1], NULL);
}
void child(int *fd, char *argv[])
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	execlp(argv[2], argv[2], NULL);
}