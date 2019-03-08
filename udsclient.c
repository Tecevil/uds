#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<errno.h>
#include<stddef.h>
#include<unistd.h>
#define BUFFER_SIZE 64*1024
const char *filename="uds-test";

int main(int argc,char **argv)
{
    struct sockaddr_un un;
    int sock_fd;
    char buffer[BUFFER_SIZE];
	memset(buffer,'s',BUFFER_SIZE);
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path,filename);
    sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sock_fd < 0){
        printf("Request socket failed\n");
        return -1;
    }
    if(connect(sock_fd,(struct sockaddr *)&un,sizeof(un)) < 0){
        printf("connect socket failed\n");
        return -1;
    }
	int i = 0;
	int itime = time(NULL);
   while(i<1000000)
{
    send(sock_fd,buffer,BUFFER_SIZE,0);
	i++;

};
itime = time(NULL) - itime;
printf("send used time %d\n",itime);
    close(sock_fd);
    return 0;
}
