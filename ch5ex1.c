#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
int main(int argc, char *argv[])
{
	int i;
	void *old();
	void **old1();
	old=signal(SIGINT, SIG_IGN);
	old1=signal(SIGTSTP, SIG_IGN);
	for(i=0;i<10;i++)
	{
		printf("I am not sensitive.\n");
		sleep(1);
	}
	signal(SIGINT, old);
	signal(SIGTSTP, old1);
	for(i=0;i<10;i++)
	{
		printf("I am sensitive.\n");
		sleep(1);
	}
}