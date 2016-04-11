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
void player(char *s, int *fd1, int * fd2);
int main(int argc, char *argv[])
{
	int fd1[2], fd2[2], fd3[2], fd4[2];
	char turn='T';
	printf("This is a 2 player game with a Refree\n");
	pipe(fd1);
	pipe(fd2);
	if(!fork())
		player("TOTO", fd1, fd2);
	sleep(1);
	close(fd1[0]);
	close(fd2[1]);
	
	pipe(fd3);
	pipe(fd4);
	if(!fork())
		player("TITI", fd3, fd4);
	sleep(1);
	close(fd3[0]);
	close(fd4[1]);
	
	while(1)
	{
		printf("\nRefree: TOTO plays\n\n");
		write(fd1[1], &turn, 1);
		read(fd2[0], &turn, 1);
		
		printf("\nRefree: TITI plays\n\n");
		write(fd3[1], &turn, 1);
		read(fd4[0], &turn, 1);
	}
}
void player(char *s, int *fd1, int *fd2)
{
	int points=0, dice;
	char turn;
	srand(time(NULL));
	while(1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGSTOP, SIG_IGN);
		read(fd1[0], &turn, 1);
		printf("%s: Playing my dice\n",s);
		dice =rand() % 20 + 1;
		printf("%s: got %d points\n", s, dice);
		points+=dice;
		printf("%s: Total so far %d\n\n", s, points);
		if(points>50)
		{
			printf("\n%s: Game Over. I won"\n, s);
			kill(0, SIGTERM);
		}
		sleep(3);
		write(fd2[1], &turn, 1);
	}
}