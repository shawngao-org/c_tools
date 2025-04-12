//
// Created by ZetoHkr on 2025/4/11.
//

#include "../../include/time/time_tools.h"

#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#define TIMESTAMP_TOKEN_FMT "%lld"
#else
#define TIMESTAMP_TOKEN_FMT "%ld"
#endif

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
    if (tm == NULL) {
        return;
    }
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

struct timestamp *get_timestamp_by_time(struct tm *time) {
    struct timestamp *timestamp = (struct timestamp *) malloc(sizeof(struct timestamp));
    timestamp->val = mktime(time);
    return timestamp;
}

struct tm *get_time_by_timestamp(const struct timestamp *timestamp) {
    struct tm *buf = (struct tm *) malloc(sizeof(struct tm));
    safe_localtime(&timestamp->val, buf);
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

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int get_days_in_month(int year, int month) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return is_leap_year(year) ? 29 : 28;
        default:
            return 1;
    }
}

struct tm *get_end_time(struct tm *time, char type) {
    if (time == NULL) {
        return NULL;
    }
    switch (type) {
        case 'M': {
            time->tm_mon = 11;
            time->tm_mday = get_days_in_month(time->tm_year + 1900, time->tm_mon + 1);
            time->tm_hour = 23;
            time->tm_min = 59;
            time->tm_sec = 59;
            break;
        }
        case 'D': {
            time->tm_mday = get_days_in_month(time->tm_year + 1900, time->tm_mon + 1);
            time->tm_hour = 23;
            time->tm_min = 59;
            time->tm_sec = 59;
            break;
        }
        case 'H': {
            time->tm_hour = 23;
            time->tm_min = 59;
            time->tm_sec = 59;
            break;
        }
        case 'm': {
            time->tm_min = 59;
            time->tm_sec = 59;
            break;
        }
        default:
            return NULL;
    }
    return time;
}

char *replace_ts_token(const char *format) {
    size_t len = strlen(format);
    char *buffer = malloc(len * 2);
    if (!buffer) return NULL;
    const char *curr = format;
    char *dest = buffer;
    while ((curr = strstr(curr, "%ts"))) {
        size_t before = curr - format;
        strncpy(dest, format, before);
        dest += before;
        strcpy(dest, TIMESTAMP_TOKEN_FMT);
        dest += strlen(TIMESTAMP_TOKEN_FMT);
        curr += 3;
        format = curr;
    }
    strcpy(dest, format);
    return buffer;
}

int timestamp_printf(const char *format, ...) {
    char *new_format = replace_ts_token(format);
    if (!new_format) return 1;
    va_list args;
    va_start(args, format);
    int result = vprintf(new_format, args);
    va_end(args);
    free(new_format);
    return result;
}
