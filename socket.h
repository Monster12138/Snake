#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <assert.h>

int create_socket()
{
    int ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(ret < 0){
        perror("create error");
        exit(0);
    }
    return ret; 
}

void Bind(int sockfd, char *ip, int port)
{
    assert(ip != NULL);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    socklen_t len = sizeof(addr);
    int ret = bind(sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0){
        perror("bind error");
        exit(0);
    }
}

void Listen(int sockfd, int blog)
{
    listen(sockfd, blog);
}

int Accept(int sockfd, char *ip, int *len)
{
    int newfd;
    struct sockaddr_in client_addr;
    socklen_t client_len;

    newfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    if(newfd < 0){
        perror("accept error");
        exit(0);
    }

    return newfd;
}

void Send(int newfd, char *buf)
{
    assert(NULL != buf);

    scanf("%s", buf);
    int len = strlen(buf);

    int ret = send(newfd, buf, len, 0);
    if(ret < 0){
        perror("send error");
        exit(0);
    }
}

int Recv(int newfd, char *buf)
{
    assert(buf != NULL);
    
    memset(buf, 0, 1024);
    int ret = recv(newfd, (void *)buf, 1024, 0);
    if(ret < 0){
        perror("recv error");
        exit(0);
    }
    printf("buf :%s\n", buf);

    return ret;
}

#endif
