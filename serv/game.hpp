#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <string.h>
#include "DataBase.hpp"
#include "snake.hpp"
#include "socket.h"

class Game
{
public:
    Game()
        :rank_score(),name(),food(0,0),snake(),width(0),height(0),highest_score(0)
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
            x = rand()%width + 1;
            y = rand()%height + 1;
        }while(snake.isOnSnake(x, y));
        food.setPos(x, y);
    }
        
    void init()
    {
        width = 28;
        height = 27;
        highest_score = 0;
        
        freshFood();
        srand(time(NULL));

        memset(rank_score, 10, sizeof(uint));
        
   }

    bool gameOver()
    {
        bool b = snake.killedBySelf() || snake.killedByWall(width, height);

        return b;
    }

    void run(Socket &socket )
    {
        Position NextPos;
        freshFood();
        socket.Send(&food, sizeof(food));
        
        std::cout << "Send food!" << std::endl;
        while(socket.Recv(&NextPos, sizeof(NextPos)))
        {
            std::cout << "foodx:" << food.getx() << "   foody:" << food.gety() << std::endl;
            std::cout << "x:" << NextPos.getx() << "   y:" << NextPos.gety() << std::endl;
            snake.headAdd(NextPos);

            if(snake.eatFood(food)){
                freshFood();
                socket.Send(&food, sizeof(food)); 
            } else {
                snake.tailRemove();
            }

            bool isOver = gameOver();
            socket.Send(&isOver, sizeof(isOver));
            if(isOver){
                std::cout << "Game Over!" << std::endl;
                break;
            }
        }
    }
    uint rank_score[10];
    std::string name[10];
private:
    Position food;
    Snake snake;

    uint width;
    uint height;
    uint highest_score;
    
};


#endif

