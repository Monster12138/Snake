 #include "view.h"                                                               
 #include <stdio.h>                                                                 
//♠♣♧♡♥❤❥❣♂♀✲☀☼☾☽◐◑☺☻☎☏✿❀№↑↓←→√×÷★℃℉°◆◇⊙■□△▽¿½☯✡㍿卍卐♂♀✚〓㎡♪♫♩♬㊚㊛囍㊒㊖Φ♀♂‖$@*&#※卍卐Ψ♫♬♭♩♪♯♮⌒¶∮‖€￡¥$
void DisPlayWall(int width,int height)
{
    HIDE_CURSOR();

    MOVETO(0,0);
    //上
    for(int i = 0;i < width + 2; i++)
    {
        printf("■");
    }
    //下
    MOVETO(0,height+1);
    for(int i = 0;i < width + 2; i++)
    {
        printf("■");
    }
    //左
    for(int i = 0;i < height + 2; i++)
    {
        MOVETO(0, i);
        printf("■");
    }
    //右
    for(int i = 0;i < height + 2; i++)
    {
        MOVETO(2 *(width + 1), i);
        printf("■");
    }
}
