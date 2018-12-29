#include <stdio.h>

int main()
{
    int x = 1;
    int y = 1;
    char data[1024] = {0};

    sprintf(data, "%d%d", x, y);
    printf("%s\n", data);
    return 0;
}

