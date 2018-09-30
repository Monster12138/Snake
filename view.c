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
 
    MOVETO(height + 2, 0);
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
    MOVETO(game->height - 10,2 * game->width + 6);
    printf("---------------------------");

    MOVETO(game->height - 8, 2 *  game->width + 6);
    printf(" %s\n",message);
}

void CleanMessage(Game *game)
{
    MOVETO(game->height - 8,2 *  game->width + 6);
    printf("                                   ");
}

void DisPlayL_S(Game *game, int speed)
{
    MOVETO(game->height/3,2 * game->width + 6);
    printf("Length: %d m", game->snake.length);

    MOVETO(game->height/3 + 2,2 * game->width + 6);
    printf("Speed:  %d m/s", speed);
}

