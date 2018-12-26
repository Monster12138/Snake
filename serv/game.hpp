#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <string.h>
#include "DataBase.hpp"
#include "snake.hpp"

class Game
{
public:
    Game()
        :food(0,0),snake(),width(0),height(0),highest_score(0),rank_score(),name(), db()
    {}

    ~Game() {}

    uint getWidth() { return width; }

    uint getHeight() { return height; }

    uint getHighestScore() { return highest_score; }

    Position& getFoodPos() { return food; }

    Snake& getSnake() { return snake; }

    void freshFood()
    {
        int x, y;
        do{
            x = rand()%width;
            y = rand()%height;
        }while(!snake.isOnSnake(x, y));
    }
        
    void init()
    {
        width = 28;
        height = 27;
        highest_score = 0;
        
        freshFood();

        memset(rank_score, 10, sizeof(uint));
        
        db.init();
        if(db.Connect("39.108.227.206", "zzz", "123456", "Snake")){
            db.ReadData("select * from score order by result desc", name, rank_score);
        }
        else {
            exit(1);
        }
    }

    bool gameOver()
    {
        bool b = snake.killedBySelf() || snake.killedByWall(width, height);

        return b;
    }

    void run()
    {
        init();
    }
private:
    Position food;
    Snake snake;

    uint width;
    uint height;
    uint highest_score;
    uint rank_score[10];
    std::string name[10];
    
    DataBase db;
};


#endif
