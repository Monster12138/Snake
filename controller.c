#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "

#include"controller.h"

pthread_t Listener, Runner, Show;
pthread_rwlock_t rwlock;
pthread_rwlockattr_t attr;

//暂停
void Pause(Game *game)
{
    tcflag_t tmp;
    char pauseMes[] =  "Press any key to continue";
    DisPlayMessage(game,pauseMes);

    struct termios te;
    tcgetattr( STDIN_FILENO,&te);
    tmp = te.c_lflag;
    te.c_lflag &=~( ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&te);
    tcflush(STDIN_FILENO,TCIFLUSH);
    fgetc(stdin) ;
    te.c_lflag |=( ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&te);
    te.c_lflag = tmp;

    system(STTY_US TTY_PATH);
    system("stty -icanon"); 
}

//键盘监视
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

//进入游戏模式（隐藏光标，清空输入缓存，关闭按键回显）
void GameMode()
{
    printf("\033[47;30m");
    HIDE_CURSOR();
    system(STTY_US TTY_PATH);
    system("stty -icanon");
    setbuf(stdin, NULL);
}

//退出游戏模式（显示光标，按键回显）
void QuitGameMode()
{
    printf("\033[49;47m");
    system(STTY_DEF TTY_PATH);
    SHOW_CURSOR();
}


void GameQuit(Game *game)
{
    if(game){
        int i = 0;
        while(i < 10)
        {
            if(game->name_list[i])free(game->name_list[i]);
            else break;
            i++;
        }
    }
    QuitGameMode();
    DisPlayQuit();

    MOVETO(29, 0);

    exit(0);
}

int ReadData(Game *game)
{
    MYSQL my_connection;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i = 0;
    char sql_str[50] = "select * from score order by result desc";
    char error_str[100] = "";

    DisPlayMessage(game, "Loading...");
    sleep(1);
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "39.108.227.206",
                           "zzz", "123456", "Snake", 0, NULL, 0)) {
        mysql_real_query(&my_connection,sql_str,strlen(sql_str));
        res = mysql_store_result(&my_connection);

        while(i < 10)
        {
            char *name = (char *)malloc(20);
            if(row = mysql_fetch_row(res)){
                strcpy(name, row[0]);
                sscanf(row[1], "%d", &game->score_list[i]);
            }
            else {
                strcpy(name, "---");
                game->score_list[i] = 0;
            }

            game->name_list[i] = name;
            i++;
        }

        game->highest_score = game->score_list[0];

        mysql_free_result(res); 
        mysql_close(&my_connection);
        return 1;
    }
    else {
        //todo
        DisPlayMessage(game, "Connection failed!");
        sleep(1);
        if (mysql_error(&my_connection)){
            sprintf(error_str, "Connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
            DisPlayMessage(game, error_str);
            return 0;
        }
        getchar();
        GameQuit(game);
        return 0;
    }
}


//初始化蛇身
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

//检查食物是否刷新在蛇身上
bool IsOverLap(Position pos,Snake *pSnake)
{
    if(pos.x <= 1 || pos.y <= 0)
        return true;
    Node *cur = pSnake->tail;
    while(cur != NULL)
    {

        if(pos.x == cur->pos.x && pos.y == cur->pos.y)
            return true;

        cur = cur->next;
    }

    return false;
}

//随机生成食物的位置
Position Generatefood(Game *game)
{
    Position newfood;
    do{
        newfood.x = rand()%game->height;
        newfood.y = rand()%game->width;

    }while(IsOverLap(newfood,&game->snake));

    DisPlayFood(&newfood);
    return newfood;
}

//游戏初始化
void GameInit(Game *game)
{
    game->width = 28;
    game->height = 27;
    game->score = 0;
    game->speed = 10;

    SnakeInit(&game->snake);

    game->food.x = 0;
    game->food.y = 0;

    memset(game->score_list,10,sizeof(unsigned int));

    for(int i = 0; i < 10; i++)
    {
        game->name_list[i] = NULL;
    }

    RefreshMap(game);
}

//获得蛇头下一步的坐标
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

//判断蛇是否吃到食物
bool IsEat(const Position *food,const Snake *snake)
{
    return food->x == snake->head->pos.x 
        && food->y == snake->head->pos.y;
}

//蛇头增加1个结点
void HeadAdd(Snake *snake, const Position *next)
{
    Node *NewNode = (Node *)malloc(sizeof(Node));
    NewNode->pos.x = next->x;
    NewNode->pos.y = next->y;

    NewNode->next = NULL;
    snake->head->next = NewNode;

    DisPlaySnakeNode(&snake->head->pos);
    snake->head = NewNode;

    DisPlaySnakeHead(&NewNode->pos);
}

//蛇尾去掉一个结点
void RemoveTail(Snake *snake)
{
    Node *cur = snake->tail;
    if(snake->tail)
        snake->tail = snake->tail->next;

    CleanSnakeNode(&cur->pos);
    free(cur);
}

//判断是否撞墙
bool KilledByWall(const Snake *snake, int width, int height)
{
    pthread_rwlock_rdlock(&rwlock);
    bool b = snake->head->pos.x >= height
        || snake->head->pos.y >= width
        || snake->head->pos.x <= 1
        || snake->head->pos.y <= 0;
    pthread_rwlock_unlock(&rwlock);

    return b;
}

//判断是否撞到自己的身体
bool KilledBySelf(const Snake *snake)
{
    pthread_rwlock_rdlock(&rwlock);
    Node *head = snake->head;
    Node *cur = snake->tail;
    while(cur && cur->next)
    {
        if(cur->pos.x == head->pos.x
           && cur->pos.y == head->pos.y){
            return true;
        }

        cur = cur->next;
    }
    pthread_rwlock_unlock(&rwlock);
    return false;
}

//判断游戏是否结束
bool GameOver(Game *game)
{
    pthread_rwlock_rdlock(&rwlock);
    bool b = KilledBySelf(&game->snake)
        || KilledByWall(&game->snake, game->width, game->height);
    pthread_rwlock_unlock(&rwlock);

    /*
       if(KilledBySelf(&game->snake))
       DisPlayMessage(game, "KilledBySelf");
       if(KilledByWall(&game->snake,game->width, game->height))
       DisPlayMessage(game, "KilledByWall");
       */
    return b;
}

//接受键盘输入
static int get_char()
{
    fd_set rfds;
    struct timeval tv;
    int ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 100; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar();
    }

    return ch;
}

int SpeedCtrl(unsigned int length)
{
    if(length < 100)
        return (10 - length/10);

    return 1;
}

bool PlayAgain(Game *game)
{
    DisPlayPlayAgain(game);
    bool b = true;

    char ch = getchar();
    switch(ch)
    {
    case 'Y':
    case 'y':{
                 b = true;
                 break;
             }
    case 'N':
    case 'n':{
                 b = false;
                 break;
             }
    default:{
                b = PlayAgain(game);
                break;
            }
    }

    return b;
}

char CheckName(char *name)
{
    int i;
    for(i = 0; *(name + i) != '\0'; i++)
    {
        if( (*(name + i) > 32 && *(name + i) < '0' )||
            (*(name + i) > '9' && *(name + i) < 'A') )
            break;
    }

    return *(name + i);
}

char* SafeInputName(Game *game, char *name)
{
    char error_str[100] = "";

    scanf("%s", name);

    char c = CheckName(name);
    if(c != '\0'){
        sprintf(error_str, "%s%c %s", 
                "Name contains illegal characters:[", 
                c, 
                "],Please input again!:>");
        DisPlayMessage(game ,error_str);
        name = SafeInputName(game, name);
    }

    return name;
}

int SaveScore(Game *game)
{
    MYSQL my_connection;
    int res;
    char *name = (char*)malloc(20);
    char sql_str[100];
    char error_str[100];

    DisPlayMessage(game, "Please input your name:>");
    setbuf(stdin, NULL);
    QuitGameMode();

    name = SafeInputName(game, name);

    GameMode();
    sprintf(sql_str, "%s%s%s%d%s","INSERT INTO score(name, result) VALUES(\"",
            name, "\",", game->score, ")");
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "39.108.227.206",
                           "zzz", "123456", "Snake", 0, NULL, 0)) {
        //        DisPlayMessage(game, "Connection success");
        res = mysql_query(&my_connection, sql_str);
        if (!res) {
            DisPlayMessage(game, "Successfully saved results");
            sleep(1);
            CleanMessage(game);
            //            printf("Inserted %lu rows\n",
            //                   (unsigned long)mysql_affected_rows(&my_connection));
        } else {
            sprintf(error_str, "%s %d%s %s\n", 
                    "Insert error",
                    mysql_errno(&my_connection), 
                    ":", 
                    mysql_error(&my_connection));

            DisPlayMessage(game, error_str);
            //            fprintf(stderr, "Insert error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
            return 0;
        }

        mysql_close(&my_connection);
    } else {
        if (mysql_error(&my_connection)) {
            fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
            return 0;
        }
    }

    free(name);
    return 1;
}

bool DirCheck(int input, int lastDir)
{
    return (
            (input == LEFT && lastDir == RIGHT)
            || (input == RIGHT && lastDir == LEFT)
            || (input == DOWN && lastDir == UP)
            || (input == UP && lastDir == DOWN));
}

void *KeyBoardListener(void *arg)
{
    Game *game = (Game*)arg;
    int input = 32;
    int lastDir;
    while(!GameOver(game))
    {
        lastDir = game->snake.Dir;
        input = get_char();
        if(DirCheck(input, lastDir))continue;

        pthread_rwlock_wrlock(&rwlock);
        if(input == lastDir){
            game->speed = 3;
        }
        else if(input == LEFT || input == RIGHT || input == UP || input == DOWN || input == PAUSE){
            game->speed = SpeedCtrl(game->snake.length);
        }

        switch(input)
        {
        case 32:game->snake.Dir = PAUSE;break;
        case 97:game->snake.Dir = LEFT;break;
        case 100:game->snake.Dir = RIGHT;break;
        case 115:game->snake.Dir = DOWN;break;
        case 119:game->snake.Dir = UP;break;
        }
        pthread_rwlock_unlock(&rwlock);
    }
    //DisPlayMessage(game, "Listener exit!");
    return NULL;
}

void *show(void *arg)
{
    Game *game = (Game*)arg;
    while(!GameOver(game))
    {
        pthread_rwlock_wrlock(&rwlock);

        DisPlayPressKey(game);
        DisPlayL_S(game,10 - game->speed + 1);

        pthread_rwlock_unlock(&rwlock);
    }

    return NULL;
}

void *run(void *arg)
{
    Game *game = (Game*)arg;
    Position NextPos;
    game->food = Generatefood(game);
    while(!GameOver(game))
    {
        pthread_rwlock_wrlock(&rwlock);
        NextPos = GetNextPosition(&game->snake);
        //        MOVETO(0,0);
        //        printf("%d,%d",game->snake.head->pos.x,game->snake.head->pos.y);
        HeadAdd(&game->snake, &NextPos); 

        if(IsEat(&game->food, &game->snake)){
            game->food = Generatefood(game);
            game->score+=10;
            game->snake.length++;
        }
        else
            RemoveTail(&game->snake);

        pthread_rwlock_unlock(&rwlock);
        //        DisPlaySnake(&game->snake);

        //      printf("%d:%d\n",input,input);
        //      DisPlayFoodPos(game);
        //      DisPlayHeadPos(game);

        usleep(game->speed * 5 * 10000);
    }
    DisPlayMessage(game, "Game Over!");
    sleep(1);

    if(game->score >= game->score_list[9]){
        if(SaveScore(game))
            ReadData(game);
    }
    /*
       if(PlayAgain(game)){
       GameInit(game);
       run(game);
       }
       */
    return NULL;
}

//UP 103
//LEFT 105
//RIGHT 106
//DOWN 108
#if 0
//游戏开始
void GameRun(Game *game)
{
    Position NextPos;
    bool flag = 0;
    int speed = 10;
    int input = 0;
    game->food = Generatefood(game);
    while(!GameOver(game))
    {
        flag = 1;
        DisPlaySnake(&game->snake);
        input = get_char();
        switch(input)
        {
        case 32:{
                    Pause(game);
                    CleanMessage(game);
                    break;
                }
        case 97:{
                    if(game->snake.Dir == LEFT)
                        flag = 0;

                    else if(game->snake.Dir != RIGHT)
                        game->snake.Dir = LEFT;
                    break;
                }
        case 100:{
                     if(game->snake.Dir == RIGHT)
                         flag = 0;

                     else if(game->snake.Dir != LEFT)
                         game->snake.Dir = RIGHT;
                     break;
                 }
        case 115:{
                     if(game->snake.Dir == DOWN)
                         flag = 0;

                     else if(game->snake.Dir != UP)
                         game->snake.Dir = DOWN;
                     break;
                 }
        case 119:{
                     if(game->snake.Dir == UP)
                         flag = 0;
                     else if(game->snake.Dir != DOWN)
                         game->snake.Dir = UP;
                     break;
                 }
        default:break;
        }

        NextPos = GetNextPosition(&game->snake);
        //        MOVETO(0,0);
        //        printf("%d,%d",game->snake.head->pos.x,game->snake.head->pos.y);
        HeadAdd(&game->snake, &NextPos); 

        if(IsEat(&game->food, &game->snake)){
            game->food = Generatefood(game);
            game->score+=10;
            game->snake.length++;
        }
        else
            RemoveTail(&game->snake);

        //        DisPlaySnake(&game->snake);

        //      printf("%d:%d\n",input,input);
        //      DisPlayFoodPos(game);
        //      DisPlayHeadPos(game);
        DisPlayPressKey(game);

        speed = SpeedCtrl(game->snake.length);

        DisPlayL_S(game,10 - speed + 1);
        if(flag)usleep(speed * 5 * 10000);
        else usleep(50000);
    }

    DisPlayMessage(game, "Game Over!");
    sleep(1);

    if(SaveScore(game))
        ReadData(game);

    if(PlayAgain(game)){
        GameInit(game);
        GameRun(game);
    }
}
#endif

void GameRun(Game *game)
{
    GameInit(game);
    pthread_rwlock_init(&rwlock, NULL);
    pthread_rwlockattr_init(&attr);
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP); 

    pthread_create(&Runner, NULL, run, (void*)game);
    pthread_create(&Show, NULL, show, (void*)game);
    pthread_create(&Listener, NULL, KeyBoardListener, (void*)game);

    pthread_join(Listener, NULL);
    pthread_join(Runner, NULL);
    pthread_join(Show, NULL);
    CLEAR();
}


