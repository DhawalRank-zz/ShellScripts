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
void TTIN_handler();
void TTIN_handler()
{
	printf("Attempted to read from Keyboard\n");
	exit(22);
}
int main()
{
	int i, status, pid;
	if(!(fork()))
	{
		signal(SIGTTIN, TTIN_handler);
		setpgid(0, getpid());
		printf("Enter a value:\n");
		scanf("%d", &i);
	}
	else
	{
		wait(&status);
		printf("Exit status was: %d\n", WEXITSTATUS(status));
	}
}