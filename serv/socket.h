#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdint.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class Socket{
public:
    void setSockfd(int sockfd);

    int create_socket();

    void Bind(char *ip, uint16_t port);

    void Connect(char *ip, uint16_t port);

    void Listen(int blog);

    int Accept(char *ip, int *len);

    void Send(const char *buf);

    int Recv(char *buf);

    void Close();
private:
    int _sockfd;
};


#endif
