#include <stdio.h>

int main()
{
    int i = 10;
    char str[4] = {0};
    
    sprintf(str, "%4d", i);

    printf("%s\n", str);
    return 0;
}

