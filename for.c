#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
	if(!fork())
		printf("%d\n",getgpid(0));
	else
		printf("%d\n",getgpid(0));
}