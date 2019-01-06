#include "controller.h"

void menu(Game *game)
{
    if(!game){
        printf("Fatal error!");
        GameQuit(game);
    }


    GameInit(game);
    //ReadData(game);
    char ch = 1;
    while(ch != '0')
    {
        DisPlayMenu(game);

        ch = getchar();

        Send(game->sockfd, &ch, sizeof(ch)); 
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
    uint16_t port = 8888;
    //char ip[] = "172.29.40.7";        
    //char ip[] = "192.168.43.137";
    char ip[] = "192.168.1.108";
    GameMode();

    Game g;
    g.sockfd = create_socket();
    Connect(g.sockfd, ip, port);
    srand((unsigned int)time(NULL));
    menu(&g);

    close(g.sockfd);
    return 0;
}

