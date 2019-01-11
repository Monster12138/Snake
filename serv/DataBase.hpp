#pragma once
#include <string>
#include <iostream>
#include "mytime.h"
#include <mysql.h>

class DataBase
{
public:
    DataBase() 
    {}

    void init()
    {
        mysql_init(&mysql);
    }

    bool Connect(const std::string &ip, 
                 const std::string &id, 
                 const std::string &pswd, 
                 const std::string &dbName)
    {

        if(!mysql_real_connect(&mysql, 
                               ip.c_str(), 
                               id.c_str(), 
                               pswd.c_str(), 
                               dbName.c_str(), 
                               0, nullptr, 0)){
            if (mysql_error(&mysql)) {
                //printf("Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
                std::cout << get_local_time() 
                    << "Connection error " 
                    << mysql_errno(&mysql) 
                    << ':'
                    << mysql_error(&mysql)
                    << std::endl;
            }

            return false;
        } else {
            std::cout << get_local_time() + "DataBase connect success\n";
            return true;
        }
    }

    bool DataSave(const std::string &sqlStr)
    {
        if(!mysql_query(&mysql, sqlStr.c_str())){
                std::cout << get_local_time() 
                    << "Insert error" 
                    << mysql_errno(&mysql) 
                    << ':'
                    << mysql_error(&mysql)
                    << std::endl;
            return false;
        } else {
            //printf("Inserted %lu rows\n",
            //       (unsigned long)mysql_affected_rows(&mysql));
            std::cout << get_local_time() << "Inserted " << (unsigned int)mysql_affected_rows(&mysql) << " rows\n";
            return true;
        }
    }

    bool ReadData(const std::string &sqlStr, std::string name[10], uint score[10])
    {
        MYSQL_RES *res;
        MYSQL_ROW row;
        int i = 0;
        mysql_real_query(&mysql, sqlStr.c_str(), sqlStr.size());
        if((res = mysql_store_result(&mysql)) == nullptr){
            std::cout << get_local_time() 
                << "ReadData error" 
                << mysql_errno(&mysql) 
                << ':'
                << mysql_error(&mysql)
                << std::endl;
            return false;
        }

        while(i < 10)
        {
            if((row = mysql_fetch_row(res))){
                name[i].assign(row[0]);
                sscanf(row[1], "%u", &score[i]);
            }
            else {
                name[i] = (char*)"---";
                score[i] = 0;
            }

            i++;
        }
        mysql_free_result(res);

        return true;
    }

    ~DataBase() 
    {
        mysql_close(&mysql);
    }

private:
    MYSQL mysql;
};

#if 0
int ReadData(std::string name[10], int score[10])
{
    MYSQL my_connection;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i = 0;
    std::string sql_str = "select * from score order by result desc";
    char error_str[100] = "";

    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "39.108.227.206",
                           "zzz", "123456", "Snake", 0, NULL, 0)) {
        mysql_real_query(&my_connection,sql_str.c_str(),sql_str.size();
        res = mysql_store_result(&my_connection);

        while(i < 10)
        {
            if(row = mysql_fetch_row(res)){
                name = res[0];
                sscanf(row[1], "%d", &score[i]);
            }
            else {
                score[i] = 0;
            }

            i++;
        }

        mysql_free_result(res); 
        mysql_close(&my_connection);
        return 1;
    }
    else {
        //todo
        if (mysql_error(&my_connection)){
            sprintf(error_str, "Connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
            std::cout << get_local_time() + error_str << std::endl;
            return 0;
        }
        return 0;
    }
}

int SaveScore(std::string name = "",int score = 0)
{
    MYSQL my_connection;
    int res;
    char sql_str[100];
    char error_str[100];

    sprintf(sql_str, "%s%s%s%d%s","INSERT INTO score(name, result) VALUES(\"",
            name.c_str(), "\",", score, ")");
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "39.108.227.206",
                           "zzz", "123456", "Snake", 0, NULL, 0)) {
        res = mysql_query(&my_connection, sql_str);
        if (!res) {
                        printf("Inserted %lu rows\n",
                               (unsigned long)mysql_affected_rows(&my_connection));
        } else {
            sprintf(error_str, "%s %d%s %s\n", 
                    "Insert error",
                    mysql_errno(&my_connection), 
                    ":", 
                    mysql_error(&my_connection));

            std::cout << get_local_time() + error_str << std::endl;
            //            fprintf(stderr, "Insert error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
            return 0;
        }

        mysql_close(&my_connection);
    } else {
        if (mysql_error(&my_connection)) {
            printf("Connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
            return 0;
        }
    }

    return 1;
}
#endif
