//
// Created by ZetoHkr on 2025/4/11.
//

#include "../../include/time/time_tools.h"
#include <time.h>
#include <stdlib.h>

struct tm *get_current_time() {
    time_t t;
    time(&t);
    struct tm *buf = (struct tm *) malloc(sizeof(struct tm));
    if (buf == NULL) {
        return NULL;
    }
#ifdef _WIN32
    localtime_s(buf, &t);
#elif __linux__
    localtime_r(&t, buf);
#elif __APPLE__
    localtime_r(&t, buf);
#endif
    return buf;
}

char *get_time_string(const struct tm *time) {
    char *buffer = (char *) malloc(sizeof(char) * 20);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", time);
    return buffer;
}

struct tm *get_time_by_string(char *time_string) {
    struct tm *time = (struct tm *) malloc(sizeof(struct tm));
    strptime(time_string, "%Y-%m-%d %H:%M:%S", time);
    return time;
}

long get_timestamp_by_time(struct tm *time) {
    return mktime(time);
}

struct tm *get_time_by_timestamp(long timestamp) {
    struct tm *buf = (struct tm *) malloc(sizeof(struct tm));
    if (buf == NULL) {
        return NULL;
    }
#ifdef _WIN32
    localtime_s(buf, &timestamp);
#elif __linux__
    localtime_r(&timestamp, buf);
#elif __APPLE__
    localtime_r(&timestamp, buf);
#endif
    return buf;
}
