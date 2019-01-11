#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <mysql.h>
#include "model.h"
#include "view.h"
#include "socket.h"

//暂停
void Pause(Game *game);


//进入游戏模式（隐藏光标，清空输入缓存，关闭按键回显）
void GameMode();


//退出游戏模式（显示光标，按键回显）
void QuitGameMode();

//退出游戏
void GameQuit(Game *game);

//从数据库读取数据
int ReadData(Game *game);

//往数据库存放数据
int SaveScore(Game *game);

//初始化蛇
void SnakeInit(Snake *pSnake);

//判断是否撞自己的身体
bool IsOverLap(Position pos,Snake *pSnake);

//检查食物是否刷新在蛇身上
bool IsOverLap(Position pos,Snake *pSnake);

//随机刷新食物
Position Generatefood(Game *game);

//地图初始化
void MapInit(Game *game);

//初始化游戏
void GameInit(Game *game);

//获取蛇下一个位置
Position GetNextPosition(Snake *pSnake);

//判断蛇是否吃到食物
bool IsEat(const Position *food,const Snake *snake);

//蛇头增加1个结点
void HeadAdd(Snake *snake, const Position *next);

//蛇尾去掉一个结点
void RemoveTail(Snake *snake);

//判断是否撞墙
bool KilledByWall(const Snake *snake, int width, int height);

//判断是否撞到自己的身体
bool KilledBySelf(const Snake *snake);

//判断游戏是否结束
bool GameOver(Game *game);

//接受键盘输入
static int get_char();

//速度控制
int SpeedCtrl(unsigned int length);

//判断是否再来一局
bool PlayAgain(Game *game);

//定位不合法字符
char CheckName(char *name);

//名字合法性检查
char* SafeInputName(Game *game, char *name);

//蛇头方向检查
bool DirCheck(int input, int lastDir);

//键盘监听线程入口函数
void *KeyBoardListener(void *arg);

//显示线程入口函数
void *show(void *arg);

//蛇运动线程入口函数
void *run(void *arg);

//游戏开始函数
void GameRun(Game *game);

int toserv();
#endif
