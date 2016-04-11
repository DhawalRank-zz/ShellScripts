//Name: Dhawal Rank
//Uwin ID: 104340181
//Section 01
//Assign02
#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
//declaration of functions
void loop();
void help();
char *read_line();
char **split_line();
int launch();
int execute();
int main(int argc, char **argv)
{
	help();
	loop();
	return EXIT_SUCCESS;
}
//infinite loop for reading commands
void loop(void)
{
  char *line;
  char **args;
  int status;
  do 
  {
	  write(1, "archer:~$", 9);
	  line = read_line();
	  args=split_line(line);
	  status = execute(args);
  }
  while (status);
}
//this function reads line using read() system call
char *read_line(void)
{
	char *buf = malloc(sizeof(char) * 1024);
	if(read(0,buf,4096)==0)						//check if CTRL+D is pressed
	{
		printf("\n");
		exit(0);	
	}
		return buf;
}
//split_line function splits lines to token and save it in an array
#define DELIM " \t\r\n\a" 			//regex for white space
char **split_line(char *line)
{
	char *token;
	char **tokens = malloc(64 * sizeof(char*));
	int i=0;
	token = strtok(line, DELIM);		//tokenize when whitespace appears
	while (token != NULL) 
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, DELIM);
	}
	tokens[i] = NULL;
	return tokens;
}
// launch() function forks the process and child process execs to new process 
int launch(char **args)
{
	pid_t pid;
	int status;
	pid = fork();
	if (pid == 0) 
	{
		// Child process
		if(strcmp(args[0],"exit")==0)		//exit command entered
		{
			kill(pid,SIGTERM);
		}
		else if(strcmp(args[0],"help")==0)		//help command entered
		{
			help();
			return 1;
		}
		else if(strcmp(args[0],"cd")==0)		//cd command entered
		{
			if (args[1] == NULL) 	//directory not provided in command
			{
				write(2,"\nDhawal's Shell: enter directory to change to\n",46);
			} 
			else 
			{
				if (chdir(args[1]) != 0) 		
				{
					perror("Dhawal's Shell");		//enters when directory does not exist
				}
			}
		}
		else
		{
			if(execvp(args[0], args) == -1) 		//exec to new process
			{
				perror("Dhawal's Shell");				//command does not exist
			}
		}   
		exit(EXIT_FAILURE);
	} 
	else if (pid < 0) 
	{
		// Error forking
		perror("Dhawal's Shell");
	} 
	else 
	{
		// Parent process
		waitpid(-1, &status, 0);			//wait till child is executing
	}
	return 1;
}
//function execute() checks if user entered any command
int execute(char **args)
{
	if (args[0] == NULL) 			//user does not enter any command
	{
		// An empty command was entered.
		return 1;
	}
	return launch(args);
}
//help() is used to display help
void help(void)
{
	write(1,"This is Dhawal Rank's Shell\n",28);
	write(1,"Developed as a part of Assignment of 03-60-656-01 Course in \nUniversity of Windsor, School Computer Science.\n",109);
	write(1,"\nType program names and arguments, and hit enter.\n",50);
	write(1,"\nCommand example: 'ls -F'\n\n",27 );
	write(1,"Use the 'man' command for information on other programs.\nPress Ctrl+C or Ctrl+Z or Ctrl+D or type 'exit' command to exit anytime.\n\n",130);
	write(1,"\nType 'help' command to get help anytime.\n",42);
}