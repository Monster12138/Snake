#include <stdio.h>
#include"mysql.h"
#include<unistd.h>

int main()
{
    MYSQL my_connection;

    printf("Connecting...\n");
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "39.108.227.206",
                           "zzz", "123456", "Snake", 0, NULL, 0)) {
        printf("1\n");
        getchar();
       mysql_close(&my_connection);
        return 1;
    }
    else {
            printf("0\n");
            getchar();
            return 0;
    }
}

