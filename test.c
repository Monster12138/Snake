#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "

static int get_char()
{
    fd_set rfds;
    struct timeval tv;
    int ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar();
    }

    return ch;
}

int main()
{
//    system(STTY_US TTY_PATH);
    system("stty -icanon"); 
    char ch;
    while(1)
    {
        ch = get_char();
        
        printf("%d:%c\n",ch,ch);

        sleep(1);
    }
//    system(STTY_DEF TTY_PATH);
    return 0;
}

