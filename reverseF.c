#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
int main (int argc, char argv[])
{
	char buf;
	int fd=open(argv[1],O_RDONLY);
	int fd2=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
	int size=lseek(fd,0,SEEK_END);
	int init=lseek(fd2,size,SEEK_SET);
	lseek(fd,0,SEEK_SET);
	while(read(fd,&buf,1)>0)
	{
		write(fd1,&buf,1);
		--size;
		init=lseek(fd2,size,SEEK_SET);
	}
	close(fd);
	close(fd1);
}