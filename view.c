 #include "view.h"
 #include"model.h"
 #include <stdio.h>                                                                 
//♠♣♧♡♥❤❥❣♂♀✲☀☼☾☽◐◑☺☻☎☏✿❀№↑↓←→√×÷★℃℉°◆◇⊙■□△▽¿½☯✡㍿卍卐♂♀✚〓㎡♪♫♩♬㊚㊛囍㊒㊖Φ♀♂‖$@*&#※卍卐Ψ♫♬♭♩♪♯♮⌒¶∮‖€￡¥$
void DisPlayWall(int width,int height)
{
    CLEAR();
    HIDE_CURSOR();

    MOVETO(0,0);
    //上
    for(int i = 0;i < 2*width; i++)
    {
        printf("■");
    }
    //左
    for(int i = 0;i < height + 2; i++)
    {
        MOVETO(i, 0);
        printf("■");
    }
    //右
    for(int i = 0;i < height + 2; i++)
    {
        MOVETO(i, 2 *width);
        printf("■");
    }
    //下
    MOVETO(height+1, 0);
    for(int i = 0;i <2*width; i++)
    {
        printf("■");
    }
 
    MOVETO(height + 2, 0);
}

void DisPlayFood(Position *pos)
{
    MOVETO(pos->x,2*(pos->y + 1));

    printf("■");
}

void DisPlaySnake(const Snake *snake)
{
    Node *cur = snake->tail;
    while(cur)
    {
        int x = cur->pos.x;
        int y = cur->pos.y;
        MOVETO(x,2 * (y + 1));
        printf("□ ");
        cur = cur->next;
    }
}

void DisPlaySnakeNode(const Position *pos)
{
    MOVETO(pos->x, 2 * (pos->y + 1));
    printf("□ ");
}

void CleanSnakeNode(const Position *pos)
{
    MOVETO(pos->x, 2 * (pos->y + 1));
    printf("  ");
}
