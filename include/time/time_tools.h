//
// Created by ZetoHkr on 2025/4/11.
//

#ifndef TOOLS_TIME_TOOLS_H
#define TOOLS_TIME_TOOLS_H
#include <time.h>

struct tm* safe_localtime(const time_t *time_ptr, struct tm *buf);
struct tm *get_current_time(void);
char* get_time_string(const struct tm *);
struct tm *get_time_by_string(char *);
long long get_timestamp_by_time(struct tm *);
struct tm *get_time_by_timestamp(long long);
struct tm *get_start_time(struct tm *time, char type);

#endif //TOOLS_TIME_TOOLS_H
