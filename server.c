#include "socket.h"

int main()
{
    int sockfd;
    uint16_t port = 19995;
    //char ip[] = "172.24.0.17";
    //char ip[] = "192.168.1.106";
    char ip[] = "192.168.43.137";
    sockfd = create_socket();

    Bind(sockfd, ip, port);    

    Listen(sockfd, 10);

    int newfd;
    while((newfd = Accept(sockfd, NULL, NULL)) > 0)
    {
        printf("A client has connected\n");
        char data[1024] = {0};

        while(Recv(newfd, data) > 0)
        {
            Send(newfd, "copy...");
        }

        close(newfd);
    }

    close(sockfd);
    return 0;
}






