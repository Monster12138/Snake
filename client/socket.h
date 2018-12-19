#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int create_socket();

void Bind(int sockfd, char *ip, uint16_t port);

void Connect(int sockfd, char *ip, uint16_t port);

void Listen(int sockfd, int blog);

int Accept(int sockfd, char *ip, int *len);

void Send(int newfd,const char *buf);

int Recv(int newfd, char *buf);

#endif
