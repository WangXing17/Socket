#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
void str_echo(int sockfd)
{
    ssize_t n;
    char buf[1000];
    while((n= read(sockfd,buf,1000))>0)
	write(sockfd,buf,n);
}

int main(int argc, char** argv)
{
    int listenfd;
    int connfd;
    struct sockaddr_in servaddr;
    
    if((listenfd = socket(AF_INET, SOCK_STREAM,0))<0)
	printf("creat socket failed!\n");
    else
   	printf("creat socket successful!\n");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(13);
    
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	//printf("bind failed%s\n",strerror(errno));
	perror("bind failed!");
    else
      	printf("bind successful!\n");
    
    if(listen(listenfd,1024)<0)
	printf("listen failed!\n");
    else
	printf("listen successful!\n");
    
    while(1)
    {
	//if(connfd = accept(listenfd,(struct sockaddr*)NULL,NULL)<0)
	   // printf("accept failed!\n");
 	//else
  	   // printf("accept successful!\n");
  	connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
	int childPid;
	if((childPid = fork()) == 0)
	{
	    close(listenfd);
	    str_echo(connfd);
	    exit(0);
	}
    }
    return 0;
}
