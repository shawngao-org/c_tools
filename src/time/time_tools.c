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

#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
#include <errno.h>
#endif

#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
#define TIMESTAMP_TOKEN_FMT "%lld"
#else
#define TIMESTAMP_TOKEN_FMT "%ld"
#endif

struct tm* safe_localtime(const time_t *time_ptr, struct tm *buf) {
    if (buf == NULL) {
        return NULL;
    }
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    if (localtime_s(buf, time_ptr) != 0) return NULL;
#elif defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
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

char *get_time_string(const struct tm *tm) {
    char *buffer = (char *) malloc(sizeof(char) * 20);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", tm);
    return buffer;
}

#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
void win_strptime(const char *s, const char *format, struct tm *tm) {
    if (tm == NULL) {
        return;
    }
    memset(tm, 0, sizeof(struct tm));
    errno = 0;
    while (*format) {
        if (isspace(*format)) {
            while (isspace(*s)) s++;
            format++;
            continue;
        }
        if (*format == '%') {
            format++;
            if (*format == '\0') {
                return;
            }
            if (*format == 'Y') {
                tm->tm_year = parse_int(&s, 4) - 1900;
                while (isdigit(*s)) s++;
            } else if (*format == 'm') {
                tm->tm_mon = parse_int(&s, 2) - 1;
                while (isdigit(*s)) s++;
            } else if (*format == 'd') {
                tm->tm_mday = parse_int(&s, 2);
                while (isdigit(*s)) s++;
            } else if (*format == 'H') {
                tm->tm_hour = parse_int(&s, 2);
                while (isdigit(*s)) s++;
            } else if (*format == 'M') {
                tm->tm_min = parse_int(&s, 2);
                while (isdigit(*s)) s++;
            } else if (*format == 'S') {
                tm->tm_sec = parse_int(&s, 2);
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
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
    win_strptime(time_string, "%Y-%m-%d %H:%M:%S", time);
#elif defined(__linux__) || defined(__APPLE__)
    strptime(time_string, "%Y-%m-%d %H:%M:%S", time);
#else
    return NULL;
#endif
    return time;
}

struct timestamp *get_timestamp_by_time(struct tm *tm) {
    struct timestamp *timestamp = (struct timestamp *) malloc(sizeof(struct timestamp));
    timestamp->val = mktime(tm);
    return timestamp;
}

struct tm *get_time_by_timestamp(const struct timestamp *timestamp) {
    struct tm *buf = (struct tm *) malloc(sizeof(struct tm));
    safe_localtime(&timestamp->val, buf);
    return buf;
}

struct tm *get_start_time(struct tm *time, const char type) {
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

int get_days_in_month(const int year, const int month) {
    switch (month + 1) {
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

struct tm *get_end_time(struct tm *time, const char type) {
    if (time == NULL) {
        return NULL;
    }
    switch (type) {
        case 'M': {
            time->tm_mon = 11;
            time->tm_mday = get_days_in_month(time->tm_year + 1900, time->tm_mon);
            time->tm_hour = 23;
            time->tm_min = 59;
            time->tm_sec = 59;
            break;
        }
        case 'D': {
            time->tm_mday = get_days_in_month(time->tm_year + 1900, time->tm_mon);
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
    if (format == NULL) {
        return NULL;
    }
    const size_t len = safe_strlen(format);
    char *buffer = malloc(len * 2);
    if (!buffer) return NULL;
    const char *curr = format;
    char *dest = buffer;
    while ((curr = strstr(curr, "%ts"))) {
        const size_t before = curr - format;
        safe_str_n_cpy(dest, format, before);
        dest += before;
        safe_str_cpy(dest, TIMESTAMP_TOKEN_FMT);
        dest += safe_strlen(TIMESTAMP_TOKEN_FMT);
        curr += 3;
        format = curr;
    }
    safe_str_cpy(dest, format);
    return buffer;
}

int timestamp_printf(const char *format, ...) {
    char *new_format = replace_ts_token(format);
    if (!new_format) return 1;
    va_list args;
    va_start(args, format);
    const int result = vprintf(new_format, args);
    va_end(args);
    free(new_format);
    return result;
}
