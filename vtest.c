#include <stdio.h>
#include"view.h"

int main()
{
    CLEAR();
    HIDE_CURSOR();

    MOVETO(0,0);
    printf("0,0");
    MOVETO(10,10);
    printf("10,10");
    MOVETO(0,10);
    printf("0,10");
    MOVETO(10,0);
    printf("10,0");

    return 0;
}

