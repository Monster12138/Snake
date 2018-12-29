#include "socket.h"
#include "mytime.h"
#include "game.hpp"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

void init(Socket& socket, uint16_t port, int backlog)
{
    socket.create_socket();

    socket.Bind(port);    

    socket.Listen(backlog);

    cout << get_local_time() <<  "init success!" << endl;
}

void Run(Socket& listenSock)
{
#if 0
    while(1)
    {
        struct sockaddr_in clientAddr;
        Socket newsocket;
        int newfd = listenSock.Accept(clientAddr);
        newsocket.setSockfd(newfd);
        string clientIp = inet_ntoa(clientAddr.sin_addr);
        uint16_t clientPort = ntohs(clientAddr.sin_port);
        cout << get_local_time() + "client " << clientIp << ":" << clientPort <<" has connected" << endl;
        char data[1024] = {0};
        while(newsocket.Recv(data))
        {
            printf("%s\n", data);
        }
        newsocket.Close();
#endif
    while(1)
    {
        Game g;
        g.init();
        cout << "Accept start" << endl;
        int newfd;
        Socket newsocket;
        struct sockaddr_in clientAddr;
        char data[1024] = {0};

        if((newfd = listenSock.Accept(clientAddr)) > 0)
        {
            newsocket.setSockfd(newfd);
            string clientIp = inet_ntoa(clientAddr.sin_addr);
            uint16_t clientPort = ntohs(clientAddr.sin_port);
            cout << get_local_time() + "client " << clientIp << ":" << clientPort <<" has connected" << endl;

            while(newsocket.Recv(data))
            {
                if(data[0] == '0')break;
                else if(data[0] == '1'){
                    gameRun();
                }
                else if(data[0] == '2'){
                    ;
                }
                else {

            }
            while(newsocket.Recv(data))
            {
                char strx[3];
                strx[0] = data[0];
                strx[1] = data[1];
                strx[2] = '\0';

                char stry[3];
                stry[0] = data[2];
                stry[1] = data[3];
                stry[2] = '\0';

                cout << "x:" << atoi(strx) << "   " << "y:" << atoi(strx) << endl;
                Position next(atoi(strx), atoi(stry));
#if 0
                g.getSnake().headAdd(next);
                
                if(!g.getSnake().eatFood(next)){
                    g.getSnake().tailRemove();
                }

                if(g.gameOver()){
                    newsocket.Send("T");
                    break;
                } else {
                    newsocket.Send("F");
                }
#endif
                memset(data, 1024, '\0');
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
        cout << "Usage: Please Enter:" << argv[0] << " port" << endl;
        exit(1);
    }
//    FILE *stream;
//    stream = freopen("./log/serverLog.log", "a+", stdout);

    Socket socket;
    socket.create_socket();
    uint16_t port = atoi(argv[1]);
    cout << port << endl;
    init(socket, port, 5);

    Run(socket);

    socket.Close();
    return 0;
}
