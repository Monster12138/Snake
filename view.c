 #include "view.h"
 #include"model.h"
 #include <stdio.h>                                                                 
//♠♣♧♡♥❤❥❣♂♀✲☀☼☾☽◐◑☺☻☎☏✿❀№↑↓←→√×÷★℃℉°◆◇⊙■□△▽¿½☯✡㍿卍卐♂♀✚〓㎡♪♫♩♬㊚㊛囍㊒㊖Φ♀♂‖$@*&#※卍卐Ψ♫♬♭♩♪♯♮⌒¶∮‖€￡¥$
void DisPlayWall(int width,int height)
{
    CLEAR();
    HIDE_CURSOR();

     //左
    for(int i = 0;i < height; i++)
    {
        MOVETO(i, 0);
        printf("■ ");
    }
    //右
    for(int i = 0;i < height; i++)
    {
        MOVETO(i, 2 *width);
        printf("■ ");
    }
    MOVETO(0,0);
    //上
    for(int i = 0;i < 2*width; i++)
    {
        printf("■");
    }

    //下
    MOVETO(height, 0);
    for(int i = 0;i <2*width; i++)
    {
        printf("■");
    }
}

void DisPlayFood(Position *pos)
{
    MOVETO(pos->x,2*pos->y);

    printf("★ ");
}

void DisPlaySnake(const Snake *snake)
{
    Node *cur = snake->tail;
    while(cur)
    {
        int x = cur->pos.x;
        int y = cur->pos.y;
        MOVETO(x,2 * y);
        printf("□ ");
        cur = cur->next;
    }
}

void DisPlaySnakeNode(const Position *pos)
{
    MOVETO(pos->x, 2 * (pos->y));
    printf("□ ");
}

void CleanSnakeNode(const Position *pos)
{
    MOVETO(pos->x, 2 * (pos->y));
    printf("  ");
}

void DisPlayFoodPos(const Game *game)
{
    MOVETO(game->height/3,2 * game->width + 6);
    printf("Food Position:[%d,%d]",game->food.x,game->food.y);
}

void DisPlayHeadPos(const Game *game)
{
    MOVETO(game->height/3 + 2,2 * game->width + 6);
    printf("Snake Head Position:[%d,%d]\n",game->snake.head->pos.x,game->snake.head->pos.y);
}

void DisPlayPressKey(Game *game,const int key)
{
    MOVETO(game->height - 4,2 * game->width + 8);
    //↑↓←→
    if(key == 119)
        printf("↑ ");
    else 
        printf("◆ ");

    MOVETO(game->height - 3,2 * game->width + 6);
    if(key == 97)
        printf("← ");
    else 
        printf("◆ ");
    
    MOVETO(game->height - 3,2 * game->width + 10);
    if(key == 100)
        printf("→ ");
    else 
        printf("◆ ");

    MOVETO(game->height - 2,2 * game->width + 8);
    if(key == 115)
        printf("↓ ");
    else 
        printf("◆ ");
}

void DisPlayMessage(Game *game,const char *message)
{
    MOVETO(game->height - 8, 2 *  game->width + 6);
    printf(" %s\n",message);
}

void CleanMessage(Game *game)
{
    MOVETO(game->height - 8,2 *  game->width + 6);
    printf("                                        ");
}

void DisPlayL_S(Game *game, int speed)
{
    MOVETO(game->height/3,2 * game->width + 6);
    printf("Length: %d m", game->snake.length);

    MOVETO(game->height/3 + 2,2 * game->width + 6);
    printf("Speed:  %d m/s", speed);

    MOVETO(game->height/3 + 4,2 * game->width + 6);
    printf("Score:  %d",game->score);

    MOVETO(game->height/3 + 6,2 * game->width + 6);
    printf("Highest Score:  %d",game->highest_score);
}

void DisPlayMenu(Game *game)
{
    char message[] = "Please enter an option with keyboard";
    DisPlayWall(game->width, game->height);

    MOVETO(game->height/3, game->width - 4);
    printf("1.开始新游戏");

    MOVETO(game->height/3 + 2, game->width - 4);
    printf("2.继续游戏");

    MOVETO(game->height/3 + 4, game->width - 4);
    printf("3.排行榜");

    MOVETO(game->height/3 + 6, game->width - 4);
    printf("0.退出游戏");

    DisPlayMessage(game, message);
}

void RefreshMap(Game *game)
{
    DisPlayWall(game->width, game->height);
    CleanMessage(game);
}

void DisPlayPlayAgain(Game *game)
{
    MOVETO(game->height/3 + 2, game->width - 6);
    printf("    再来一局？");

    MOVETO(game->height/3 + 4, game->width - 6);
    printf("y.确认    n.返回菜单");
}

void DisPlayQuit(Game *game)
{
    CLEAR();
    MOVETO(game->height/2, game->width - 6);
    printf("Thanks for playing my game~");
}

void DisPlayScore_list(Game *game)
{
    int i = 0;
    int height_offset = 4;
    MOVETO(game->height + height_offset, game->width - 10);
    printf("%10s    %10s","name", "score");
    while(i < 10)
    {
        MOVETO(game->height + height_offset, game->width - 10);
//        printf("%10s    %10d",game->name_list[i],game->score_list[i]);

        i++;
        height_offset += 2;
    }
    //todo
}
