#ifndef _MODEL_H_
#define _MODEL_H_ 

typedef enum {
    UP,DOWN,LEFT,RIGHT
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
    Direction Dir;
} Snake;

typedef struct Game{
    Position food;
    Snake snake;
    unsigned int width;
    unsigned int height;
}Game;

#endif