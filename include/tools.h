#ifndef TOOLS_TOOLS_H
#define TOOLS_TOOLS_H

#include <time.h>

void hello(void);

/**
 * Get struct tm ptr by time_t ptr
 * safe_localtime returns a pointer to a dynamically allocated struct tm.
 * Caller is responsible for freeing the returned pointer to avoid memory leaks.
 * @param time_ptr time_t ptr
 * @param buf time buffer
 * @return struct tm ptr, if NULL is returned, it means that the current system platform is not supported.
 */
struct tm* safe_localtime(const time_t *time_ptr, struct tm *buf);

/**
 * Get current time
 * get_current_time returns a pointer to a dynamically allocated struct tm.
 * Caller is responsible for freeing the returned pointer to avoid memory leaks.
 * @return struct tm ptr
 */
struct tm *get_current_time(void);

/**
 * Get time string by struct tm ptr
 * @param tm struct tm ptr
 * @return time string "yyyy-MM-dd hh-mm-ss"
 */
char* get_time_string(const struct tm *);

/**
 * Get struct tm ptr by time string
 * get_time_by_string returns a pointer to a dynamically allocated struct tm.
 * Caller is responsible for freeing the returned pointer to avoid memory leaks.
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
 * get_time_by_timestamp returns a pointer to a dynamically allocated struct tm.
 * Caller is responsible for freeing the returned pointer to avoid memory leaks.
 * @param timestamp seconds timestamp
 * @return struct tm ptr
 */
struct tm *get_time_by_timestamp(long);

#endif //TOOLS_TOOLS_H
