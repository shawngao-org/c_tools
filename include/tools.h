#ifndef TOOLS_TOOLS_H
#define TOOLS_TOOLS_H

void hello(void);

/**
 * Get current time
 * @return struct tm ptr
 */
struct tm *get_current_time(void);

/**
 * Get time string by struct tm ptr
 * @param tm struct tm ptr
 * @return time string "yyyy-MM-dd hh-mm-ss"
 */
char* get_time_string(struct tm *);

/**
 * Get struct tm ptr by time string
 * @param time_string time string "yyyy-MM-dd hh-mm-ss"
 * @return struct tm ptr
 */
struct tm *get_time_by_string(char *);

/**
 * Get timestamp by struct tm ptr
 * @param tm struct tm ptr
 * @return seconds timestamp
 */
long get_timestamp_by_time(struct tm *);

/**
 * Get struct tm ptr by timestamp
 * @param timestamp seconds timestamp
 * @return struct tm ptr
 */
struct tm *get_time_by_timestamp(long);

#endif //TOOLS_TOOLS_H
