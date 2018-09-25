#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<termio.h>
#include<unistd.h>
#include"model.h"
#include"controller.h"
#include"view.h"
#include<stdio.h>
#include <stdlib.h>

#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "

int scanKeyboard()
{
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);

    in = getchar();

    tcsetattr(0,TCSANOW,&stored_settings);
    return in;
}

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

    pSnake->length = 3;
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

Position Generatefood(Game *game)
{
    Position newfood;
    do{
        newfood.x = rand()%game->width + 1;
        newfood.y = rand()%game->height + 1;

    }while(IsOverLap(newfood,&game->snake));

    DisPlayFood(&newfood);
    return newfood;
}

void GameInit(Game *game)
{
    game->width = 28;
    game->height = 27;

    SnakeInit(&game->snake);
    game->food = Generatefood(game);
}

Position GetNextPosition(Snake *pSnake)
{
    Position NextPos;
    NextPos.x = pSnake->head->pos.x;
    NextPos.y = pSnake->head->pos.y;
    switch(pSnake->Dir)
    {
    case UP:NextPos.x--;break;
    case DOWN:NextPos.x++;break;
    case LEFT:NextPos.y--;break;
    case RIGHT:NextPos.y++;break;
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
    snake->head = NewNode;

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
    return snake->head->pos.x >= height + 1
        || snake->head->pos.y >= width
        || snake->head->pos.x <= 1
        || snake->head->pos.y <= 0;
}

bool KilledBySelf(const Snake *snake)
{
    Node *head = snake->head;
    Node *cur = snake->tail;
    while(cur && cur->next)
    {
        if(cur->pos.x == head->pos.x
           && cur->pos.y == head->pos.y){
            printf("KilledBySelf!\n");
            printf("%d,%d\n",cur->pos.x,cur->pos.y);
            return true;
        }

        cur = cur->next;
    }
    return false;
}

bool GameOver(Game *game)
{
    return KilledBySelf(&game->snake)
        || KilledByWall(&game->snake, game->width, game->height);
}

static int get_char()
{
    fd_set rfds;
    struct timeval tv;
    int ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 1; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar();
    }

    return ch;
}

//UP 103
//LEFT 105
//RIGHT 106
//DOWN 108

void GameRun(Game *game)
{
    Position NextPos, food;
    int speed = ONE;
    int input = 0;
    food = Generatefood(game);
    while(!GameOver(game))
    {
        DisPlaySnake(&game->snake);
        input = get_char();
        switch(input)
        {
        case 119:{
                    if(game->snake.Dir != DOWN)
                        game->snake.Dir = UP;
                    break;
                }
        case 97:{
                    if(game->snake.Dir != RIGHT)
                        game->snake.Dir = LEFT;
                    break;
                }
        case 100:{
                    if(game->snake.Dir != LEFT)
                       game->snake.Dir = RIGHT;
                    break;
                }
        case 115:{
                    if(game->snake.Dir != UP)
                        game->snake.Dir = DOWN;
                    break;
                }
        default:break;
        }
        NextPos = GetNextPosition(&game->snake);
//        MOVETO(0,0);
//        printf("%d,%d",game->snake.head->pos.x,game->snake.head->pos.y);
        HeadAdd(&game->snake, &NextPos); 

        if(IsEat(&food, &game->snake))
            food = Generatefood(game);
        else
            RemoveTail(&game->snake);

        DisPlaySnake(&game->snake);
        MOVETO(0,0);
//        printf("■");

        printf("%d:%d\n",input,input);
        usleep(500000);
    }
}


int main()
{
    system(STTY_US TTY_PATH);
    system("stty -icanon"); 

    Game g;
    srand((unsigned int)time(NULL));
    GameInit(&g);
    DisPlayWall(g.width,g.height);
    GameRun(&g);

    system(STTY_DEF TTY_PATH);
    return 0;
}
