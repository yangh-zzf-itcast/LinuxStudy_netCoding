/*************************************************************************
    > File Name: client.c
    > Author: yanghang
    > Mail: 2459846416@qq.com 
    > Created Time: Sat 22 Dec 2018 08:00:19 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/stat.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#define MAXLINE 10
#define SERV_PORT 9000

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char			   buf[MAXLINE];
	int				   sockfd, i;
	char			   ch = 'a';

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	while(1){
		for(i = 0;i < MAXLINE/2;i++)
			buf[i] = ch;
		buf[i - 1] = '\n';
		ch++;
		for(;i < MAXLINE;i++)
			buf[i] = ch;
		buf[i - 1] = '\n';
		ch++;
		write(sockfd, buf, sizeof(buf));
		sleep(5);
	}

	close(sockfd);

	return 0;
}

