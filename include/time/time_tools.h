//
// Created by ZetoHkr on 2025/4/11.
//

#ifndef TOOLS_TIME_TOOLS_H
#define TOOLS_TIME_TOOLS_H

struct tm *get_current_time(void);
char* get_time_string(struct tm *);
struct tm *get_time_by_string(char *);
long get_timestamp_by_time(struct tm *);
struct tm *get_time_by_timestamp(long);

#endif //TOOLS_TIME_TOOLS_H
