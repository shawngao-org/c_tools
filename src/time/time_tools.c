//
// Created by ZetoHkr on 2025/4/11.
//

#include "../../include/time/time_tools.h"

#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#ifdef _WIN32
void win_strptime(const char *s, const char *format, struct tm *tm) {
    memset(tm, 0, sizeof(struct tm));
    if (tm == NULL) return;
    errno = 0;
    while (*format) {
        if (isspace(*format)) {
            while (isspace(*s)) {
                s++;
            }
            format++;
            continue;
        }
        if (*format == '%') {
            format++;
            if (*format == '\0') {
                return;
            }
            if (*format == 'Y') {
                if (strtol(s, "%4d", tm->tm_year) != 1) return;
                tm->tm_year -= 1900;
                while (isdigit(*s)) s++;
            } else if (*format == 'm') {
                if (strtol(s, "%2d", tm->tm_mon) != 1) return;
                tm->tm_mon -= 1;
                while (isdigit(*s)) s++;
            } else if (*format == 'd') {
                if (strtol(s, "%2d", tm->tm_mday) != 1) return;
                while (isdigit(*s)) s++;
            } else if (*format == 'H') {
                if (strtol(s, "%2d", tm->tm_hour) != 1) return;
                while (isdigit(*s)) s++;
            } else if (*format == 'M') {
                if (strtol(s, "%2d", tm->tm_min) != 1) return;
                while (isdigit(*s)) s++;
            } else if (*format == 'S') {
                if (strtol(s, "%2d", tm->tm_sec) != 1) return;
                while (isdigit(*s)) s++;
            } else if (*format == '-') {
                if (*s != '-') return;
                s++;
            } else if (*format == ':') {
                if (*s != ':') return;
                s++;
            } else if (*format == ' ') {
                if (*s != ' ') return;
                s++;
            } else {
                return;
            }
            format++;
        } else {
            if (*s != *format) {
                return;
            }
            s++;
            format++;
        }
    }
}
#endif

struct tm *get_time_by_string(char *time_string) {
    struct tm *time = (struct tm *) malloc(sizeof(struct tm));
#ifdef _WIN32
    win_strptime(time_string, "%Y-%m-%d %H:%M:%S", time);
#elif defined(__linux__) || defined(__APPLE__)
    strptime(time_string, "%Y-%m-%d %H:%M:%S", time);
#else
    return NULL;
#endif
    return time;
}

long long get_timestamp_by_time(struct tm *time) {
    return mktime(time);
}

struct tm *get_time_by_timestamp(const long long timestamp) {
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
            time->tm_mday = 1;
            time->tm_hour = 0;
            time->tm_min = 0;
            time->tm_sec = 0;
            break;
        }
        case 'D': {
            time->tm_mday = 1;
            time->tm_hour = 0;
            time->tm_min = 0;
            time->tm_sec = 0;
            break;
        }
        case 'H': {
            time->tm_hour = 0;
            time->tm_min = 0;
            time->tm_sec = 0;
            break;
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
