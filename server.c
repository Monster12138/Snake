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

int main()
{
    int sockfd;
    uint16_t port = 19995;
    //char ip[] = "172.24.0.17";
    char ip[] = "192.168.1.106";
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){
        perror("create error");
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    socklen_t len = sizeof(addr);
    int ret = bind(sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0){
        perror("bind error");
        return 0;
    }

    listen(sockfd, 10);

    int newfd;
    struct sockaddr_in client_addr;
    socklen_t client_len;

    newfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    if(newfd < 0){
        perror("accept error");
        return 0;
    }

    char data[1024] = {0};
    
    while(1)
    {
        memset(data, 0, 1024);
        recv(newfd, (void *)data, 1024, 0);
        printf("data :%s\n", data);
    }

    close(newfd);
    close(sockfd);
    return 0;
}






