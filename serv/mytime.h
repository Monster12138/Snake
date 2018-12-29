#ifndef _MYTIME_H_
#define _MYTIME_H_
#include <string>

std::string get_local_time()
{
    std::string t;
    char buffer[32] = {0};
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d————",
            (timeinfo->tm_year+1900), timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    t.assign(buffer);

    return t;
}

#endif
