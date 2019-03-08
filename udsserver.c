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

#define MAX_CONNECT_NUM 2
const long BUFFER_SIZE= 64*1024;
const char *filename="uds-test";

int main()
{
    int fd,new_fd,len,i;
    struct sockaddr_un un;
    fd = socket(AF_UNIX,SOCK_STREAM,0);
    if(fd < 0){
        printf("Request socket failed!\n");
        return -1;
    }
    un.sun_family = AF_UNIX;
    unlink(filename);
    strcpy(un.sun_path,filename);
    if(bind(fd,(struct sockaddr *)&un,sizeof(un)) <0 ){
        printf("bind failed!\n");
        return -1;
    }
    if(listen(fd,MAX_CONNECT_NUM) < 0){
        printf("listen failed!\n");
        return -1;
    }
struct sockaddr_un client_addr;
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);
        len = sizeof(client_addr);
        //new_fd = accept(fd,(struct sockaddr *)&client_addr,&len);
        new_fd = accept(fd,NULL,NULL);
        if(new_fd < 0){
            printf("accept failed\n");
            return -1;
        }
	long ret = 0;
	int itime = time(NULL);
    while(1){
        
        ret += recv(new_fd,buffer,BUFFER_SIZE,0);
        if(ret < 0){
            printf("recv failed\n");
        }
	if(ret == BUFFER_SIZE*1000000)
        break;
    }
	printf("recv length %ld \n",ret);
	itime = time(NULL) - itime;
	printf("recv used time %d\n",itime);
    close(new_fd);
    close(fd);
}
