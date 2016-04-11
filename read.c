#define _POSIX_SOURCE   //to use functionality from the POSIX.1 standard as ANCI C does not support kill()
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
int main()
{
	char *buf;
	int n;
	int fd=open("head.txt",O_RDONLY);
	while((n=read(fd,buf,100))>0)
		write(1,buf,n);
	printf("\n%d",n);
}