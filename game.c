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
void action1(){};
void action2(){};
void child(char *);
int main(int argc, char *argv[])
{
	pid_t pid1,pid2, pid3;
	printf("This is a 3 player game\n");
	if((pid1=fork()==0)) child("TOTO");
	if((pid2=fork()==0)) child("TITI");
	if((pid3=fork()==0)) child("TUTU");
	
	sleep(1);
	signal(SIGUSR1, action1);
	while(1)
	{
		printf("\nRefree: TOTO Plays\n\n");
		kill(pid1, SIGUSR1);
		pause();
		printf("\nRefree: TITI Plays\n\n");
		kill(pid2, SIGUSR1);
		pause();
		printf("\nRefree: TUTU Plays\n\n");
		kill(pid3, SIGUSR1);
		pause();
	}
}
void child(char *s)
{
	int points=0,dice;
	while(1)
	{
		signal(SIGUSR1, action2);
		pause();
		printf("\n%s: Playing my dice\n",s);
		dice = (rand() % 10)+1;
		printf("%s: got %d points\n",s, dice);
		points+=dice;
		printf("%s: Total so far %d\n\n", s, points);
		sleep(3);
		if(points >= 50)
		{
			printf("%s: game over I won\n", s);
			kill(0, SIGTERM);
		}
		kill(getppid(), SIGUSR1);
	}
}