#include "controller.h"

bool ReadConfig(Game *game, char *ip, uint16_t *port)
{
    FILE* fp = fopen("client_conf.ini", "r");
    if(NULL == fp){
        return -1;
    }
    while(fscanf(fp, "%s", ip))
    {
        fscanf(fp, "%s", ip);
        fscanf(fp, "%s", ip);
    }
    fclose(fp);
}

void menu(Game *game)
{
    if(!game){
        printf("Fatal error!");
        GameQuit(game);
    }


    ReadData(game);

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
                     ReadData(game);
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
    //char ip[20] = {0};
    //char ip[] = "39.108.227.206";        
    char ip[] = "172.29.40.7";        
    //char ip[] = "192.168.43.137";
    //char ip[] = "192.168.1.108";
    GameMode();

    Game g;
    g.sockfd = create_socket();
    Connect(g.sockfd, ip, port);
    srand((unsigned int)time(NULL));
    MapInit(&g);  
    menu(&g);

    close(g.sockfd);
    return 0;
}

