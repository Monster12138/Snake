#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <list>
#include <iostream>

typedef unsigned int uint;
typedef enum {
    PAUSE = 32,
    LEFT = 97,
    RIGHT = 100,
    DOWN = 115,
    UP = 119
}Direction;

class Position{
public:
    Position(int x = 0, int y = 0):_x(x), _y(y)
    {}
    
    void setPos(int x, int y){ _x = x; _y = y; }

    int getx()const { return _x; }

    int gety()const { return _y; }
private:
    int _x;
    int _y;
};

typedef Position Node;

class Snake
{
public:
    Snake()
        :head(nullptr), tail(nullptr), length(0), speed(0), score(0), Dir(PAUSE), l() 
    {}

    ~Snake()
    {}

    void initSnake()
    {
        Node *newNode1 = new Node(5,2);
        Node *newNode2 = new Node(6,2);
        Node *newNode3 = new Node(7,2);

        l.push_back(newNode1);
        l.push_back(newNode2);
        l.push_back(newNode3);

        head = l.front();
        tail = l.back();

        length = 3;
        speed = 10;
        score = 0;
        Dir = RIGHT;
    }

    Direction getDir()const { return Dir; }

    uint getLength()const {return length; }

    Node* getHead()const { return head; }

    Node* getTail()const { return tail; }

    uint getScore()const { return score; }

    void addSore(int n) { score += n; }

    void speedCtrl()
    {
        if(length < 100)
            speed = 10 - length/10;
        else{
            speed = 1;
        }
    }

    bool eatFood(const Position& food)const
    {
        return food.getx() == head->getx()
            && food.gety() == head->gety();
    }

    bool isOnSnake(int x, int y)
    {
        auto it = l.begin();
        ++it;
        for(; it != l.end(); ++it)
        {
            if(x == (*it)->getx() && y == (*it)->gety() ){
                return true;
            }
        }
        return false;
    }

    void headAdd(const Node& next)
    {
        Node *newNode = new Node(next.getx(), next.gety());
        l.push_front(newNode);

        head = l.front();

        std::cout << "headAdd" << std::endl;
    }

    void tailRemove()
    {
        l.pop_back();
        std::cout << "tailRemove" << std::endl;
    }

    bool killedByWall(int width, int height)
    {
        bool ret = head->getx() >= height
            || head->gety() >= width
            || head->getx() <= 1
            || head->gety() <= 0;

        if(ret == true){
            std::cout << "KilledByWall!" << std::endl;
        }
        return ret;
    }

    bool killedBySelf()
    {
        auto it = l.begin();
        ++it;
        for(; it != l.end(); ++it)
        {
            if(head->getx() == (*it)->getx() && head->gety() == (*it)->gety() ){
                std::cout << "KilledBySelf!" << std::endl;
                return true;
            }
        }
        return false;
    }

private:
    Node *head;
    Node *tail;
    uint length;
    uint speed;
    uint score;
    Direction Dir;
    std::list<Node*> l;
};

#endif

