#include<stdio.h>
#include<stdlib.h>
#include"model.h"
#include"controller.h"

void SnakeInit(Snake *pSnake)
{
    pSnake->tail = NULL;
    for(int i = 0; i < 3; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->pos.x = 20+i;
        node->pos.y = 2;

        if(i == 0)
            pSnake->head = node;

        node->next = pSnake->tail;
        pSnake->tail = node;
    }

    pSnake->Dir = RIGHT;
}

void GameInit(Game *game)
{
    game->width = 28;
    game->height = 27;

    SnakeInit(&game->snake);
}

int main()
{
    Game g;
    GameInit(&g);
    printf("Init success!\n");
    return 0;
}
