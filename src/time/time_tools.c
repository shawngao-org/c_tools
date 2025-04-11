//
// Created by ZetoHkr on 2025/4/11.
//

#include "../../include/time/time_tools.h"
#include <time.h>
#include <stdlib.h>

struct tm* safe_localtime(const time_t *time_ptr, struct tm *buf) {
    if (buf == NULL) {
        return NULL;
    }
#ifdef _WIN32
    if (localtime_s(buf, time_ptr) != 0) return NULL;
#elif defined(__linux__) || defined(__APPLE__)
    if (localtime_r(time_ptr, buf) == NULL) return NULL;
#else
    return NULL;
#endif
    return buf;
}

struct tm *get_current_time() {
    time_t t;
    time(&t);
    struct tm *buf = (struct tm *) malloc(sizeof(struct tm));
    safe_localtime(&t, buf);
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
    safe_localtime(&timestamp, buf);
    return buf;
}

struct tm *get_start_time(struct tm *time, char type) {
    if (time == NULL) {
        return NULL;
    }
    switch (type) {
        case 'M': {
            time->tm_mon = 0;
        }
        case 'D': {
            time->tm_mday = 1;
        }
        case 'H': {
            time->tm_hour = 0;
        }
        case 'm': {
            time->tm_min = 0;
            time->tm_sec = 0;
            break;
        }
        default:
            return NULL;
    }
    return time;
}
