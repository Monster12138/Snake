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
#include "socket.h"

void Socket::setSockfd(int sockfd)
{
    _sockfd = sockfd;
}

int Socket::create_socket(){
    int ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(ret < 0){
        perror("create error");
        exit(0);
    }
    return ret; 
}

void Socket::Bind(char *ip, uint16_t port)
{
    assert(ip != NULL);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    socklen_t len = sizeof(addr);
    int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0){
        perror("bind error");
        exit(0);
    }
}

void Socket::Connect(char *ip, uint16_t port)
{
    assert(NULL != ip);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    socklen_t len = sizeof(addr);
    int ret = connect(_sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0){
        perror("connect error");
        exit(0);
    }
}

void Socket::Listen(int blog)
{
    listen(_sockfd, blog);
}

int Socket::Accept(char *ip, int *len)
{
    int newfd;
    struct sockaddr_in client_addr;
    socklen_t client_len;

    newfd = accept(_sockfd, (struct sockaddr*)&client_addr, &client_len);
    if(newfd < 0){
        perror("accept error");
        return -1;
    }

    return newfd;
}

void Socket::Send(const char *buf)
{
    assert(NULL != buf);

    int len = strlen(buf);

    int ret = send(_sockfd, buf, len, 0);
    if(ret < 0){
        perror("send error");
        exit(0);
    }
}

int Socket::Recv(char *buf)
{
    assert(buf != NULL);
    
    memset(buf, 0, 1024);
    int ret = recv(_sockfd, (void *)buf, 1024, 0);
    if(ret < 0){
        perror("recv error");
        exit(0);
    }
    printf("buf :%s\n", buf);

    return ret;
}

void Socket::Close()
{
    close(_sockfd);
}
