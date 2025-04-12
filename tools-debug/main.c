#include <stdio.h>
#include <tools.h>
#include <stdlib.h>
#include <string.h>

void test_get_current_time() {
    printf("\nTest: get_current_time()\n");
    const int b = get_current_time() != NULL;
    printf("Current time is not null: %d\n", b);
    if (!b) {
        fprintf(stderr, "Error: get_current_time() returned NULL.\n");
        exit(1);
    }
}

void test_get_time_string() {
    printf("\nTest: get_time_string()\n");
    const struct tm *time = get_current_time();
    const char *time_string = get_time_string(time);
    const int n = time_string != NULL;
    const int e = time_string[0] != '\0';
    printf("Current time string is not null: %d\n", n);
    printf("Current time string is not empty: %d\n", e);
    if (!n || !e) {
        fprintf(stderr, "Error: get_time_string() returned NULL or Empty.\n");
        exit(1);
    }
}

void test_get_time_by_string() {
    printf("\nTest: get_time_by_string()\n");
    char *time_string = "2025-01-01 00:00:00";
    const struct tm *time = get_time_by_string(time_string);
    const int n = time != NULL;
    printf("Current time is not null: %d\n", n);
    if (!n) {
        fprintf(stderr, "Error: get_time_by_string() returned NULL.\n");
        exit(1);
    }
    char *time_string_converted = get_time_string(time);
    printf("Time string: %s\n", time_string_converted);
    if (strcmp(time_string, time_string_converted) != 0) {
        fprintf(stderr, "Error: get_time_by_string() results don\'t match.");
        exit(1);
    }
}

void test_get_timestamp_by_time() {
    printf("\nTest: get_timestamp_by_time()\n");
    const long original_ts = 1735660800;
    char *time_string = "2025-01-01 00:00:00";
    struct tm *time = get_time_by_string(time_string);
    const struct timestamp *ts = get_timestamp_by_time(time);
    const int n = ts->val != 0;
    printf("Current timestamp is not zero: %d\n", n);
    timestamp_printf("Current timestamp: %ts\n", ts->val);
    printf("Original timestamp: %ld\n", original_ts);
    if (!n) {
        fprintf(stderr, "Error: get_timestamp_by_time() returned NULL.\n");
        exit(1);
    }
    if (ts->val != original_ts) {
        fprintf(stderr, "Error: get_timestamp_by_time() results don\'t match.");
        exit(1);
    }
}

void test_get_time_by_timestamp() {
    printf("\nTest: get_time_by_timestamp()\n");
    struct tm *original_t = get_current_time();
    printf("Original time string: %s\n", get_time_string(original_t));
    const struct timestamp *ts = get_timestamp_by_time(original_t);
    timestamp_printf("Original timestamp: %ts\n", ts->val);
    struct tm *time = get_time_by_timestamp(ts);
    const int n = time != NULL;
    printf("Current time is not null: %d\n", n);
    printf("Current time string: %s\n", get_time_string(time));
    timestamp_printf("Current timestamp: %ts\n", get_timestamp_by_time(time)->val);
    if (!n) {
        fprintf(stderr, "Error: get_time_by_timestamp() returned NULL.\n");
        exit(1);
    }
}

void test_get_start_time() {
    printf("\nTest: get_start_time()\n");
    char *time_string = "2025-05-10 07:30:50";
    char *target_string = "2025-01-01 00:00:00";
    const char type = 'M';
    struct tm *time = get_time_by_string(time_string);
    const struct tm *start_time = get_start_time(time, type);
    const int n = start_time != NULL;
    printf("Start time is not null: %d\n", start_time != NULL);
    printf("Start time type: %c\n", type);
    printf("Original time string: %s\n", time_string);
    printf("Start time string: %s\n", get_time_string(start_time));
    printf("Target time string: %s\n", target_string);
    if (!n) {
        fprintf(stderr, "Error: get_start_time() returned NULL.\n");
        exit(1);
    }
    if (strcmp(get_time_string(start_time), target_string) != 0) {
        fprintf(stderr, "Error: get_start_time() results don\'t match.");
        exit(1);
    }
}

int main() {
    printf("Hello World!\n");
    hello();
#ifdef defined(__linux__) || defined(__APPLE__)
    setenv("TZ", "Etc/GMT-8", 1);
    tzset();
#endif
     test_get_current_time();
     test_get_time_string();
     test_get_time_by_string();
     test_get_timestamp_by_time();
     test_get_time_by_timestamp();
     test_get_start_time();
    return 0;
}
