#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <string.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include <sys/wait.h>

#define PORT 3490 /* 客户机连接远程主机的端口 */

const long  MAXDATASIZE = 1024*64; /* 每次可以接收的最大字节 */

int main(int argc, char *argv[])

{

int sockfd;

char buf[MAXDATASIZE];
memset(buf,'s',MAXDATASIZE);
struct sockaddr_in their_addr; /* connector's address information */


if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {

perror("socket");

exit(1);

}

their_addr.sin_family = AF_INET; /* host byte order */

their_addr.sin_port = htons(PORT); /* short, network byte order */
struct in_addr ia;
ia.s_addr = inet_addr("192.168.34.2");
their_addr.sin_addr = *((struct in_addr *)&ia);

bzero(&(their_addr.sin_zero),sizeof(their_addr.sin_zero)); /* zero the rest of the struct */

if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1) {

perror("connect");

exit(1);

}
	long ret = 0;
	int itime = time(NULL);
    while(1)
	{
		ret +=recv(sockfd, buf, MAXDATASIZE, 0);
		if(ret < 0)
			printf("recv failed\n");
		if(ret == MAXDATASIZE*1000000)
			break;
	};
	printf("recv length %ld \n",ret);
	itime = time(NULL) - itime;
	printf("send used time %d\n",itime);
	close(sockfd);

return 0;

}