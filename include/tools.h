#ifndef TOOLS_TOOLS_H
#define TOOLS_TOOLS_H

#include <time.h>

struct timestamp {
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    long long val;
#else
    long val;
#endif
};

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
char* get_time_string(const struct tm * tm);

/**
 * Get struct tm ptr by time string
 * get_time_by_string returns a pointer to a dynamically allocated struct tm.
 * Caller is responsible for freeing the returned pointer to avoid memory leaks.
 * @param time_string time string "yyyy-MM-dd hh-mm-ss"
 * @return struct tm ptr
 */
struct tm *get_time_by_string(char * time_string);

/**
 * Get timestamp by struct tm ptr
 * @param tm struct tm ptr
 * @return seconds timestamp
 */
struct timestamp *get_timestamp_by_time(struct tm * tm);

/**
 * Get struct tm ptr by timestamp
 * get_time_by_timestamp returns a pointer to a dynamically allocated struct tm.
 * Caller is responsible for freeing the returned pointer to avoid memory leaks.
 * @param timestamp seconds timestamp
 * @return struct tm ptr
 */
struct tm *get_time_by_timestamp(const struct timestamp *timestamp);

/**
 * Get start time by struct tm ptr and type
 * @param time struct tm ptr
 * @param type m: minute, H: hour D: day, M: month
 * @return struct tm ptr
 */
struct tm *get_start_time(struct tm *time, char type);

/**
 * Check whether the year is a leap year
 * @param year year
 * @return 1: leap year, 0: not leap year
 */
int is_leap_year(int year);

/**
 * Get days in month by year and month
 * @param year year
 * @param month month[0-11]
 * @return days in month
 */
int get_days_in_month(int year, int month);

/**
 * Get end time by struct tm ptr and type
 * @param time struct tm ptr
 * @param type m: minute, H: hour D: day, M: month
 * @return struct tm ptr
 */
struct tm *get_end_time(struct tm *time, char type);

/**
 * Print timestamp, base on printf\n
 * add new format: %ts\n
 * %ts is long long number in Windows and long number in Linux\n
 * Usage: timestamp_printf("Timestamp: %ts\\n", timestamp);
 * @param format printf format
 * @param ... printf params
 * @return result
 */
int timestamp_printf(const char *format, ...);

/**
 * Replace %ts token in format string
 * @param format format string
 * @return new format string
 */
char *replace_ts_token(const char *format);

/**
 * Get string length
 * @param str string
 * @return length
 */
unsigned long safe_strlen(const char *str);

/**
 * Copy src string to dest string
 * @param dest dest string
 * @param src src string
 */
void safe_str_cpy(char *dest, const char *src);

/**
 *
 * @param dest dest string
 * @param src src string
 * @param n length
 */
void safe_str_n_cpy(char *dest, const char *src, unsigned long n);

/**
 * Parse string to int number
 * @param s string
 * @param width length or width
 * @return number
 */
int parse_int(const char **s, int width);

struct stack {
    void **data;
    int top;
    int capacity;
    size_t size;
};

/**
 * Create stack
 * @param init_capacity initial capacity
 * @param size element size
 * @return stack
 */
struct stack *create_stack(int init_capacity, size_t size);

/**
 * Check whether stack is empty
 * @param stack stack
 * @return 1: empty, 0: not empty
 */
int is_empty_stack(const struct stack *stack);

/**
 * Check whether stack is full
 * @param stack stack
 * @return 1: full, 0: not full
 */
int is_full_stack(const struct stack *stack);

/**
 * Resize stack
 * @param stack stack
 */
void resize_stack(struct stack *stack);

/**
 * Push item to stack
 * @param stack stack
 * @param item data
 */
void push_stack(struct stack *stack, const void *item);

/**
 * Pop item from stack, this will remove item from stack
 * @param stack stack
 * @return data on top of stack
 */
void *pop_stack(struct stack *stack);

/**
 * Peek item from stack, but not remove
 * @param stack stack
 * @return data on top of stack
 */
void *peek_stack(const struct stack *stack);

/**
 * Destroy stack
 * @param stack stack
 */
void destroy_stack(struct stack *stack);

struct list_node {
    void *data;
    struct list_node *prev;
    struct list_node *next;
};

/**
 * Create new list node.
 * @param prev pre node ptr
 * @param next next node ptr
 * @param data new node data
 * @return new node ptr
 */
struct list_node *new_list_node(struct list_node *prev, struct list_node *next, void *data);

/**
 * Create a new linked list.
 * @param head null ptr
 * @param fst_data first node data
 */
void create_linked_list(struct list_node **head, void *fst_data);

/**
 * Check if the list is empty.
 * @param head list head ptr
 * @return 0: not empty, 1: empty
 */
int is_empty_linked_list(const struct list_node *head);

/**
 * Get list length.\n
 * Don't worry about the head ptr reaching the end of the list.
 * @param head list head ptr
 * @return list length
 */
int get_linked_list_length(struct list_node **head);

/**
 * Insert data in head.
 * @param head list head ptr
 * @param data data
 * @return new head ptr
 */
struct list_node *insert_linked_list_in_head(struct list_node **head, void *data);

/**
 * Insert data by index.
 * @param head list head ptr
 * @param data data
 * @param index index, starts from 0
 * @return original head ptr
 */
struct list_node *insert_linked_list_by_index(struct list_node **head, void *data, int index);

/**
 * Insert data in tail.
 * @param head list head ptr
 * @param data data
 * @return original head ptr
 */
struct list_node *insert_linked_list_in_tail(struct list_node **head, void *data);

/**
 * Remove data in head.
 * @param head list head ptr
 * @return original head ptr
 */
struct list_node *remove_linked_list_node_in_head(struct list_node **head);

/**
 * Remove data by index.
 * @param head list head ptr
 * @param index index, starts from 0
 * @return original head ptr
 */
struct list_node *remove_linked_list_node_by_index(struct list_node **head, int index);

/**
 * Destroy linked list.
 * @param head list head ptr
 */
void destroy_linked_list(struct list_node **head);

#endif //TOOLS_TOOLS_H
