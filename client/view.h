#include <unistd.h>
#include <stdio.h>                                                                 
#include "model.h"
// 清除屏幕
#define CLEAR() printf("\033[2J")

// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))

// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))

// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))

// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))

// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

// 光标复位
#define RESET_CURSOR() printf("\033[H")

// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")

// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")

//反显
#define HIGHT_LIGHT() printf("\033[7m")

#define UN_HIGHT_LIGHT() printf("\033[27m")

//显示食物
void DisPlayFood(Position *pos);

//显示墙
void DisPlayWall(int width,int height);

//显示蛇
void DisPlaySnake(const Snake *snake);

//显示蛇结点
void DisPlaySnakeNode(const Position *pos);

//显示蛇头
void DisPlaySnakeHead(const Position *pos);

//清除结点
void CleanSnakeNode(const Position *pos);

//显示蛇头位置
void DisPlayHeadPos(const Game *game);

//显示食物位置
void DisPlayFoodPos(const Game *game);

//显示按键
void DisPlayPressKey(Game *game);

//显示提示信息
void DisPlayMessage(Game *game,const char *message);

//清除提示信息
void CleanMessage(Game *game);

//显示蛇身长度和速度
void DisPlayL_S(Game *game, int speed);

//显示菜单
void DisPlayMenu(Game *game);

//刷新地图
void RefreshMap(Game *game);

//显示是否再来一局
void DisPlayPlayAgain(Game *game);

//显示游戏退出信息
void DisPlayQuit();

//显示排行榜信息
void DisPlayScore_list(Game *game);

