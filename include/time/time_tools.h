//
// Created by ZetoHkr on 2025/4/11.
//

#ifndef TOOLS_TIME_TOOLS_H
#define TOOLS_TIME_TOOLS_H

#include "tools.h"

struct tm* safe_localtime(const time_t *time_ptr, struct tm *buf);
struct tm *get_current_time(void);
char* get_time_string(const struct tm *);
struct tm *get_time_by_string(char *);
struct timestamp *get_timestamp_by_time(struct tm *);
struct tm *get_time_by_timestamp(const struct timestamp *);
struct tm *get_start_time(struct tm *time, char type);
int is_leap_year(int year);
int get_days_in_month(int year, int month);
struct tm *get_end_time(struct tm *time, char type);
int timestamp_printf(const char *format, ...);
char *replace_ts_token(const char *format);

#endif //TOOLS_TIME_TOOLS_H
