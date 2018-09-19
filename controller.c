#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"model.h"
#include"controller.h"

void SnakeInit(Snake *pSnake)
{
    pSnake->tail = NULL;
    for(int i = 0; i < 3; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->pos.x = 5+i;
        node->pos.y = 2;

        if(i == 0)
            pSnake->head = node;

        node->next = pSnake->tail;
        pSnake->tail = node;
    }

    pSnake->Dir = RIGHT;
}

bool IsOverLap(Position pos,Snake *pSnake)
{
    Node *cur = pSnake->tail;
    while(cur != NULL)
    {
        printf("IsOverLap!\n");
        
        if(pos.x == cur->pos.x && pos.y == cur->pos.y)
            return true;

        cur = cur->next;
    }

    return false;
}

Position Generatefood(Game *game, Snake *pSnake)
{
    Position newfood;
    do{
        newfood.x = rand()%game->width;
        newfood.y = rand()%game->height;

    }while(IsOverLap(newfood,pSnake));

    printf("Generatefood!\n");
    return newfood;
}

void GameInit(Game *game)
{
    game->width = 28;
    game->height = 27;

    SnakeInit(&game->snake);
    game->food = Generatefood(game,&game->snake);
}

Position GetNextPosition(Snake *pSnake)
{
    Position NextPos;
    NextPos.x = pSnake->head->pos.x;
    NextPos.y = pSnake->head->pos.y;
    switch(pSnake->Dir)
    {
    case UP:NextPos.y--;break;
    case DOWN:NextPos.y++;break;
    case LEFT:NextPos.x--;break;
    case RIGHT:NextPos.x++;break;
    default:break;
    }

    return NextPos;
}

int main()
{
    Game g;
//  Snake s;
//  SnakeInit(&s);
//  printf("%x %x-%x-%x-%x\n",s.head,s.tail,s.tail->next,s.tail->next->next,s.head->next);
    GameInit(&g);
//  DisPlayWall(g.width,g.height);
    printf("Init success!\n");
    return 0;
}
