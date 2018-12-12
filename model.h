#ifndef _MODEL_H_
#define _MODEL_H_ 

typedef enum {
    PAUSE = 32,
    LEFT = 97,
    RIGHT = 100,
    DOWN = 115,
    UP = 119
}Direction;

typedef struct{
    int x;
    int y;
}Position;

typedef struct Node{
    Position pos;
    struct Node *next;
}Node;

typedef struct Snake{
    Node *head;
    Node *tail;
    unsigned int length;
    Direction Dir;
} Snake;

typedef struct Game{
    Position food;
    Snake snake;

    unsigned int width;
    unsigned int height;
    unsigned int score;
    unsigned int speed;
    unsigned int highest_score;
    unsigned int score_list[10];
    char *name_list[10];
}Game;

#endif
