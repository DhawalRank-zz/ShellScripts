#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
int main()
{
	int a;
	a=getpriority(PRIO_PROCESS, getpid());
	printf("\nPriority is : %d",a);
	a=nice(4);
	printf("\nNew priority is : %d",a);
}