//Name: Dhawal Rank
//Uwin ID: 104340181
//Section 01
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
void loop();
char *read_line();
char **split_line();
int launch();
int execute();
int main(int argc, char **argv)
{
	loop();
	return EXIT_SUCCESS;
}
void loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    write(1, ">", 1);
    line = read_line();
	args=split_line(line);
    status = execute(args);
  } while (status);
}
char *read_line(void)
{
	char *buf = malloc(sizeof(char) * 1024);
	read(0,buf,20);
	return buf;
}
#define DELIM " \t\r\n\a"
char **split_line(char *line)
{
	char *token;
	char **tokens = malloc(64 * sizeof(char*));
	int i=0;
	token = strtok(line, DELIM);
	while (token != NULL) {
    tokens[i] = token;
    i++;
    token = strtok(NULL, DELIM);
	}
	tokens[i] = NULL;
	return tokens;
}
int launch(char **args)
{
	pid_t pid;
	int status;
	pid = fork();
	if (pid == 0) {
    // Child process
	if(execvp(args[0], args) == -1) {
      perror("Dhawal's Shell");
	}
    exit(EXIT_FAILURE);
	} else if (pid < 0) {
    // Error forking
	perror("Dhawal's Shell");
	} else {
    // Parent process
	waitpid(-1, &status, 0);
	}
  return 1;
}
int execute(char **args)
{
  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
  return launch(args);
}