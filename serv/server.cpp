#include "socket.h"
#include "mytime.h"
#include "controller.h"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

void init(Socket& socket, uint16_t port, int backlog)
{
    socket.create_socket();

    socket.Bind(port);    

    socket.Listen(backlog);
}

void Run(Socket& listenSock)
{
    while(1)
    {
        Game g;
        GameInit(&g);
        int newfd;
        Socket newsocket;
        struct sockaddr_in clientAddr;
        
        if((newfd = listenSock.Accept(clientAddr)) > 0)
        {
            newsocket.setSockfd(newfd);
            string clientIp = inet_ntoa(clientAddr.sin_addr);
            uint16_t clientPort = ntohs(clientAddr.sin_port);
            cout << get_local_time() + "client " << clientIp << ":" << clientPort <<" has connected" << endl;
            char data[1024] = {0};

            while(newsocket.Recv(data) > 0)
            {
                newsocket.Send("copy...");
            }

            newsocket.Close();
            cout << get_local_time() + "A client has leaved" << endl;
        }
        else{
            cout << get_local_time() + "Accept error" << endl;
        }
    }
}


int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "Usage: Please Enter:./" << argv[0] << " port" << endl;
    }
    FILE *stream;
    stream = freopen("./log/serverLog.log", "a+", stdout);

    Socket socket;
    uint16_t port = atoi(argv[1]);

    init(socket, port, 5);

    Run(socket);

    socket.Close();
    return 0;
}
