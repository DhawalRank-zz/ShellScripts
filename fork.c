#include <stdio.h>
int main( void ) {
	int pid = fork();

	if ( pid == 0 ) {
		printf( "This is being printed from the child process\n" );
	} else {
		printf( "This is being printed in the parent process:\n"
		        " - the process identifier (pid) of the child is %d\n", pid );
	}

	return 0;
}