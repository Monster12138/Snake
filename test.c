#include <stdio.h>
#include<termios.h>
#include<unistd.h>
int main()
{
    printf("Press any key to continue") ;
    struct termios te;
    tcgetattr( STDIN_FILENO,&te);
    te.c_lflag &=~( ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&te);
    tcflush(STDIN_FILENO,TCIFLUSH);
    fgetc(stdin) ; 
    te.c_lflag |=( ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&te);
    printf("Hello world\n");
    return 0;
}

