#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#define _BSD_SOURCE
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
void child(char *);
int win;
void action(){}
void action1(){
	int player = open("player.txt", O_RDWR);
	int score = open("score.txt", O_RDWR);
	int points = 0;
	char play[4];

	read(score, &points, sizeof(points));
	read(player, play, sizeof(play));
	printf("\nReferee: \n");

	if(points >= win){
		printf("GAME OVER: %s won with %d points\n ", play, points);
		kill(0, SIGTERM);
	}
}
int main(){
	pid_t pid1, pid2, pid3;
	signal(SIGINT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	printf("This is a 3 player game with a Refree\n");
	printf("Enter the winning score:\n");
	scanf("%d", &win);
	if((pid1=fork())==0) 
		child("TOTO");
	sleep(1);
	if((pid2=fork())==0) 
		child("TITI");
	sleep(1);
	if((pid3=fork())==0) 
		child("TUTU");
	sleep(1);
	signal(SIGUSR1, action1);
	while(1){
		printf("Refree: TOTO plays\n\n");
		kill(pid1, SIGUSR1);
		pause();
		printf("Refree: TITI plays\n\n");
		kill(pid2, SIGUSR1);
		pause();
		printf("Refree: TUTU plays\n\n");
		kill(pid3, SIGUSR1);
		pause();
	}
}
void child(char *s){
  int points=0, dice;
  srand(time(NULL));

  while(1){
	signal(SIGINT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	int player = open("player.txt", O_RDWR | O_CREAT);
    int score = open("score.txt", O_RDWR | O_CREAT);
    signal(SIGUSR1, action);
    pause();
    printf("%s: playing my dice\n", s);
    dice = rand()%20 + 1;
    printf("%s: got %d points\n", s, dice);
    points+=dice;
    printf("%s: Total so far %d\n\n", s, points);
	lseek(player,0,SEEK_SET);
	lseek(score,0,SEEK_SET);
	write(player,s,sizeof(s));
	write(score,&points,sizeof(points));
    sleep(3);
    kill(getppid(), SIGUSR1);
  }
}