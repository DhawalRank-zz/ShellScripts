
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
void myAlarmHandler();
void myAlarmHandler()
{
	printf("Handled.\n");
	alarm(3);
}
int main(int argc,char *argv[])
{
	signal(SIGALRM,myAlarmHandler);
	alarm(3);
	while(1)
	{
		signal(SIGALRM,myAlarmHandler);
		printf("I am working.\n");
		sleep(1);
	}
}