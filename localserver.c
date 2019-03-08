#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <string.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include <sys/wait.h>
#define BUFFER_SIZE 64*1024
#define MYPORT 3490 /*定义用户连接端口*/

#define BACKLOG 10 /*多少等待连接控制*/

int main(int argc,char **argv)
{
	char buffer[BUFFER_SIZE];
	memset(buffer,'s',BUFFER_SIZE);
	int sockfd;
	int new_fd; /* listen on sock_fd, new connection on new_fd */
	struct sockaddr_in my_addr; /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	int sin_size;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
		}
	my_addr.sin_family = AF_INET; /* host byte order */
	my_addr.sin_port = htons(MYPORT); /* short, network byte order */
	//my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
	struct in_addr ia;
	inet_aton("192.168.34.2", &ia);
	my_addr.sin_addr = *((struct in_addr *)&ia);
	bzero(&(my_addr.sin_zero),sizeof(my_addr.sin_zero)); /* zero the rest of the struct */
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
	perror("bind");
	exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {

	perror("listen");

	exit(1);

	}
	sin_size = sizeof(struct sockaddr_in);

	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {

	perror("accept");

	}

	printf("server: got connection");

	int i =0;
	long ret = 0;
	int itime = time(NULL);
	while(i < 1000000)
	{
		ret += send(new_fd, buffer, BUFFER_SIZE, 0);
		i++;
	};
	printf("send length %ld\n",ret);
	itime = time(NULL) - itime;
	printf("send used time %d\n",itime);
	close(new_fd);
	close(sockfd);
	return 0;
}