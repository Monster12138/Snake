#include "socket.h"

int main()
{
    int sockfd;
    uint16_t port = 19995;
    //char ip[] = "172.24.0.17";
    char ip[] = "192.168.1.106";
    sockfd = create_socket();

    Bind(sockfd, ip, port);    

    Listen(sockfd, 10);

    int newfd = Accept(sockfd, NULL, NULL);

    char data[1024] = {0};
    
    while(Recv(sockfd, data) > 0)
    {
        Send(sockfd, "copy...");
    }

    close(newfd);
    close(sockfd);
    return 0;
}






