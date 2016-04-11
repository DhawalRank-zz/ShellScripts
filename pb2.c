#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
  pid_t pid;
  int fd;
  int status;
  char c;

  if(argc !=2 ){
	  printf("Call model: %s <inputFile>\n", argv[0]);
	  exit(0);
  }
  if ( (fd = open(argv[1], O_RDONLY)) == -1){
    printf("%s could not be opened, please create file first\n", argv[1]);
    exit(0);
  }

  printf("Parent is going to create a child process\n\n");
  sleep(1);
  if ((pid = fork()) > 0){
    printf("Parent: child created, waiting for my child to terminate\n\n");
    wait(&status);    
    
    printf("Parent: child terminated with status=%d\n", WEXITSTATUS(status));
    printf("Parent: Bye Bye\n");
  }
  else
    if(pid==0){ 
      sleep(2);
      printf("Child: I am going to disply the file contents\n");
      sleep(2);
      while(read(fd, &c, 1)>0)
	write(STDOUT_FILENO, &c, 1);
      
      sleep(2);
      printf("\n\nChild: I am done, terminating with status = 20\n\n");
      sleep(2);
      exit(20);
    }
 exit(0);	
}