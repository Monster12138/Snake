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

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class Socket{
public:
    void setSockfd(int sockfd);

    void create_socket();

    void Bind(uint16_t port);

    void Connect(char *ip, uint16_t port);

    void Listen(int blog);

    int Accept(struct sockaddr_in& clientAddr);

    void Send(const char *buf);

    int Recv(char *buf);

    void Close();
private:
    int _sockfd;
};


#endif
