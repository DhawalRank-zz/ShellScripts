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

int getRandomInteger(int n){
  srand(time(NULL));
int r = rand() % 10;
  return (r);
}
int winningValue = 50;
// int file;

void action1(){
  int file = open("score", O_RDWR);
  int file2 = open("playername", O_RDWR);
  int points = 0;
  char playername[100];

  read(file, &points, sizeof(points));
  read(file2, playername, sizeof(playername));
  // printf("%d\n", points);
  // printf("%s\n", playername);
  printf("\nReferee: ");

  if(points >= winningValue){
    printf("GAME OVER: %s won with %d points\n ", playername, points);
    kill(0, SIGTERM);
  }

  close(file);
  close(file2);
}
void action2(){};
void child(char *);


int main(int argc, char *argv[]){

  void (*handler1)();
  void (*handler2)();

  handler1 = signal(SIGINT, SIG_IGN);
  handler2 = signal(SIGTSTP, SIG_IGN);

  pid_t pid1, pid2, pid3;
  printf("This is a 2-players game with a referee\n");
  printf("Enter the winningValue: \n");
  scanf("%d", &winningValue);
  if((pid1=fork()) == 0) child("TOTO");
  if((pid2=fork()) == 0) child("TITI");
  if((pid3=fork()) == 0) child("TUTU");

  sleep(1);
  signal(SIGUSR1, action1);
  while(1){
    printf("TOTO plays\n");
    kill(pid1, SIGUSR1);
    pause();
    printf("TITI plays\n");
    kill(pid2, SIGUSR1);
    pause();
    printf("TUTU plays\n");
    kill(pid3, SIGUSR1);
    pause();
  }
}
void child(char *s){
  int points=0;
  int dice, n=10;
  while(1){
    int file = open("score", O_RDWR);
    int file2 = open("playername", O_RDWR);

    signal(SIGUSR1, action2);  // block myself
    pause();
    // printf("%s: playing my dice\n", s);
    dice = getRandomInteger(n);
    // printf("%s: got %d points\n", s, dice);
    points+=dice;
    // printf("%s: Total so far %d\n\n", s, points);

    printf("%s: playing my dice, Got: %d, Total: %d\n", s, dice, points);

    // char buffer = (char)points;
    //reset
    lseek(file, 0 , SEEK_SET);
    lseek(file2, 0 , SEEK_SET);
    write(file, &points, sizeof(points));
    write(file2, s, sizeof(s));
    close(file);
    close(file2);
	sleep(3);
    kill(getppid(), SIGUSR1);
  }
}