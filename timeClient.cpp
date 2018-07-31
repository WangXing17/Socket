#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
void str_cli(FILE *fp, int sockfd)
{
    char sendline[1000],recvline[1000];
    while(fgets(sendline,1000,fp) != NULL)
	{
	    write(sockfd,sendline,1000);
	    read(sockfd,recvline,1000);
	    fputs(recvline,stdout);
	}
}
int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if((sockfd = socket(AF_INET, SOCK_STREAM,0))<0)
	printf("creat socket failed!\n");
    else
	printf("creat socket successful!\n");
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_pton(AF_INET, argv[1],&servaddr.sin_addr);	
    
    if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	printf("connect failed!%s\n",strerror(errno));
    else
	printf("connect sucessful!\n");
    
    str_cli(stdin,sockfd);
    exit(0);    
	
}
