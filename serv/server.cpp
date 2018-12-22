#include "socket.h"
#include "mytime.h"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    FILE *stream;
    stream = freopen("./log/serverLog.log", "a+", stdout);

    Socket socket;
    uint16_t port = 19995;
    //char ip[] = "172.24.0.17";
    //char ip[] = "192.168.1.106";
    char ip[] = "192.168.43.137";
    socket.create_socket();

    socket.Bind(ip, port);    

    socket.Listen(10);

    int newfd;
    Socket newsocket;
    while((newfd = socket.Accept(NULL, NULL)) > 0)
    {
        newsocket.setSockfd(newfd);
        cout << get_local_time() + "A client has connected" << endl;
        char data[1024] = {0};

        while(newsocket.Recv(data) > 0)
        {
            newsocket.Send("copy...");
        }

        newsocket.Close();
        cout << get_local_time() + "A client has leaved" << endl;
    }

    socket.Close();
    return 0;
}
