#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include<stdbool.h>
#include"model.h"
//初始化蛇
void SnakeInit(Snake *pSnake);

//判断是否撞自己的身体
bool IsOverLap(Position pos,Snake *pSnake);

//随机刷新食物
Position Generatefood(Game *game);

//初始化游戏
void GameInit(Game *game);

//获取蛇下一个位置
Position GetNextPosition(Snake *pSnake);
#endif
