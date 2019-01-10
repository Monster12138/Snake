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

void SendRank(Game &g, const Socket& newsocket)
{        
    DataBase db;
    db.init();
    if(db.Connect("39.108.227.206", "zzz", "123456", "Snake")){
    }
    else {
        exit(1);
    }

    db.ReadData("select * from score order by result desc", g.name, g.rank_score);
    cout << "Send start" << endl;
    char tmp[20] = {0};
    newsocket.Send(&g.rank_score, sizeof(g.rank_score));
    for(int i = 0; i < 10; ++i)
    {
        strcpy(tmp, g.name[i].c_str());
        newsocket.Send(tmp, g.name[i].size() + 1);
        cout << tmp << endl;
        usleep(100);
    }
    cout << "Send finish" << endl;
}

void Run(Socket& listenSock)
{
    while(1)
    {
        Game g;
        g.init();
        cout << "Accept start" << endl;
        int newfd;
        Socket newsocket;
        struct sockaddr_in clientAddr;

        char ch;
        while((newfd = listenSock.Accept(clientAddr)) > 0)
        {
            if(newfd < 0){
                cout << get_local_time() + "Accept error" << endl;
                break;
            }

            newsocket.setSockfd(newfd);
            string clientIp = inet_ntoa(clientAddr.sin_addr);
            uint16_t clientPort = ntohs(clientAddr.sin_port);
            cout << get_local_time() + "client " << clientIp << ":" << clientPort <<" has connected" << endl;

            SendRank(g, newsocket);

            while(newsocket.Recv(&ch, sizeof(ch)))
            {
                cout << "进入菜单，选项为" << ch << endl;
                if(ch == '0')break;
                else if(ch == '1'){
                    g.run(newsocket);
                }
                else if(ch == '2'){
                    SendRank(g, newsocket);
                }
                else {
                    continue;
                }
            }
            newsocket.Close();
            cout << get_local_time() + "A client has leaved" << endl;
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
    bool option = true;
    socklen_t len = sizeof(option);
    setsockopt(socket.getSockfd(),SOL_SOCKET,SO_REUSEADDR,(const char *)&option,len);
    uint16_t port = atoi(argv[1]);
    cout << port << endl;
    init(socket, port, 5);

    Run(socket);

    socket.Close();
    return 0;
}
