#include "socket.h"

void Socket::setSockfd(int sockfd)
{
    _sockfd = sockfd;
}

void Socket::create_socket(){
    _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(_sockfd < 0){
        perror("create error");
        exit(2);
    }
}

void Socket::Bind(uint16_t port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

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

void Socket::Listen(int backlog)
{
    listen(_sockfd, backlog);
}

int Socket::Accept(struct sockaddr_in& clientAddr)
{
    int newfd;
    socklen_t client_len = sizeof(clientAddr);

    newfd = accept(_sockfd, (struct sockaddr*)&clientAddr, &client_len);
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

    return ret;
}

void Socket::Close()
{
    close(_sockfd);
}
