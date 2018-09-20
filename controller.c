#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include"model.h"
#include"controller.h"
#include"view.h"

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

bool IsEat(const Position *food,const Snake *snake)
{
    return food->x == snake->head->pos.x 
        && food->y == snake->head->pos.y;
}

void HeadAdd(Snake *snake, const Position *next)
{
    Node *NewNode = (Node *)malloc(sizeof(Node));
    NewNode->pos.x = next->x;
    NewNode->pos.y = next->y;

    NewNode->next = NULL;
    snake->head->next = NewNode;
    snake->head = NewNode;;

    DisPlaySnakeNode(&NewNode->pos);
}

void RemoveTail(Snake *snake)
{
    Node *cur = snake->tail;
    if(snake->tail)
        snake->tail = snake->tail->next;
    
    CleanSnakeNode(&cur->pos);
    free(cur);
}

bool KilledByWall(const Snake *snake, int width, int height)
{
    //To write
    return false;
}

bool KilledBySelf(const Snake *snake)
{
    //To write
    return false;
}

int main()
{
    Game g;
    srand((unsigned int)time(NULL));
    GameInit(&g);
    DisPlayWall(g.width,g.height);
    while(1)
    {
        g.food = Generatefood(&g,&g.snake);
        DisPlayFood(&g.food);
        DisPlaySnake(&g.snake);
        usleep(2);
    }
    printf("Init success!\n");
    return 0;
}
