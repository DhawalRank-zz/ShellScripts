#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
void Alarmhandler()
{
	static int n=0;
	if(n++<6)
	{
		printf("Beeping %c%c%c\n",7,7,7);
		alarm(10);
	}
	else
		exit(0);
}
int main(int argc, char *argv[])
{
	signal(SIGALRM, Alarmhandler);
	Alarmhandler();
	while(1)
		pause();
}