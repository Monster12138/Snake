#include "controller.h"
#include "socket.h"

void menu(Game *game)
{
    if(!game){
        printf("Fatal error!");
        GameQuit(game);
    }


    GameInit(game);
    ReadData(game);
    char ch = 1;
    while(ch != '0')
    {
        DisPlayMenu(game);

        ch = getchar();
        RefreshMap(game);
        switch(ch)
        {
        case '0':{
                     GameQuit(game);
                     getchar();
                     break;
                 }
        case '1':{
                     GameRun(game);
                     break;
                 }
        case '2':{
                     //todo
                     //GameLoad(game);
                     GameRun(game);
                     break;
                 }
        case '3':{
                     DisPlayScore_list(game);
                     DisPlayMessage(game, "press [ENTER] to return menu");
                     getchar();
                     break;
                 }
        default:{
                    break;
                }
        }
    }
}


int main()
{
    uint16_t port = 19994;
    char ip[] = "192.168.1.106";
    GameMode();

    Game g;
    g.sockfd = create_socket();
    Connect(g.sockfd, ip, port);
    srand((unsigned int)time(NULL));
    menu(&g);

    close(g.sockfd);
    return 0;
}

