#Dhawal Rank
#Student ID:104340181
#Section 2
#define _POSIX_SOURCE
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
void action(){}	//blocking function
void action1(){}//blocking function
int main(int argc, char *argv[]){
	pid_t pid1, pid2, pid3;
	int win;
	signal(SIGINT, SIG_IGN);		//ignore ctrl+C and ctrl+z
	signal(SIGSTOP, SIG_IGN);		//ignore ctrl+C and ctrl+z
	printf("This is a 3 player game with a Refree\n");
	printf("Enter the winning score:\n");
	scanf("%d", &win);
	if((pid1=fork())==0) 		//
		child("TOTO");			//
	sleep(1);					//
	if((pid2=fork())==0) 		//
		child("TITI");			// Create 3 players(child) and send them to pause()
	sleep(1);					//
	if((pid3=fork())==0) 		//
		child("TUTU");			//
	sleep(1);
	signal(SIGUSR1, action1);
	//only refree(parent) will reach upto here
	while(1){
		int points;
		FILE *score;
		printf("Refree: TOTO plays\n\n");
		kill(pid1, SIGUSR1);
		sleep(1);
		score=fopen("score.txt", "r");			//read scores
        fscanf(score,"%d", &points);
        if(points>=win){						//compare scores
            printf("TOTO: game over I won with %d points.\n",points);
            kill(0, SIGTERM);
        }
		fclose(score);
		pause();
		printf("Refree: TITI plays\n\n");
		kill(pid2, SIGUSR1);
		sleep(1);
		score=fopen("score.txt", "r");			//read scores
        fscanf(score,"%d", &points);
        if(points>=win){						//compare scores
            printf("TITI: game over I won with %d points.\n",points);
            kill(0, SIGTERM);
        }
		fclose(score);
		pause();
		printf("Refree: TUTU plays\n\n");
		kill(pid3, SIGUSR1);
		sleep(1);
		score=fopen("score.txt", "r");			//read scores
        fscanf(score,"%d", &points);
        if(points>=win){						//compare scores
            printf("TUTU: game over I won with %d points.\n",points);
            kill(0, SIGTERM);
        }
		fclose(score);
		pause();
	}
}
void child(char *s){
  int points=0, dice, fd;
  srand(time(NULL));				//seeding random number
  FILE *score;
  while(1){
	signal(SIGINT, SIG_IGN);		//ignore ctrl+C and ctrl+Z signals
	signal(SIGSTOP, SIG_IGN);		//ignore Ctrl+C and ctrl+Z signals
	score = fopen(fd, "w+");
    signal(SIGUSR1, action);
    pause();
    printf("%s: playing my dice\n", s);
    dice = rand()%20 + 1;							//get random value
    printf("%s: got %d points\n", s, dice);
    points+=dice;
    printf("%s: Total so far %d\n\n", s, points);
	fprintf(score, "%d", points);					//write score to file
	fclose(score);
    sleep(3);
    kill(getppid(), SIGUSR1);
  }
}