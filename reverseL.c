#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
int main (int argc, char argv[])
{
	char buf[255];
	int i=0;
	int fd=open(argv[1],O_RDONLY);
	int fd2=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
	int size=lseek(fd,0,SEEK_END);
	lseek(fd2,size,SEEK_SET);
	lseek(fd,0,SEEK_SET);
	while(read(fd,&buf[i],1)>0)
	{
		if(buf[i]=='\n')
		{
			i++;
			//int lineSize=strlen(buf);
			lseek(fd2,-i,SEEK_CUR);
			write(fd2,&buf,i);
			lseek(fd2,-i,SEEK_CUR);
			i=0;
		}
		else
			i++;
	}