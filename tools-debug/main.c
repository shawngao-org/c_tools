#include <stdio.h>
#include <tools.h>
#include <stdlib.h>
#include <string.h>

void test_get_current_time() {
    printf("\nTest: get_current_time()\n");
    int b = get_current_time() != NULL;
    printf("Current time is not null: %d\n", b);
    if (!b) {
        exit(1);
    }
}

void test_get_time_string() {
    printf("\nTest: get_time_string()\n");
    struct tm *time = get_current_time();
    char *time_string = get_time_string(time);
    int n = time_string != NULL;
    int e = time_string[0] != '\0';
    printf("Current time string is not null: %d\n", n);
    printf("Current time string is not empty: %d\n", e);
    if (!n || !e) {
        exit(1);
    }
}

void test_get_time_by_string() {
    printf("\nTest: get_time_by_string()\n");
    char *time_string = "2025-01-01 00:00:00";
    struct tm *time = get_time_by_string(time_string);
    int n = time != NULL;
    printf("Current time is not null: %d\n", n);
    if (!n) {
        exit(1);
    }
    char *time_string_converted = get_time_string(time);
    printf("Time string: %s\n", time_string_converted);
    if (strcmp(time_string, time_string_converted) != 0) {
        exit(1);
    }
}

void test_get_timestamp_by_time() {
    printf("\nTest: get_timestamp_by_time()\n");
    long original_ts = 1735660800;
    char *time_string = "2025-01-01 00:00:00";
    struct tm *time = get_time_by_string(time_string);
    long timestamp = get_timestamp_by_time(time);
    int n = timestamp != 0;
    printf("Current timestamp is not zero: %d\n", n);
    printf("Current timestamp: %ld\n", timestamp);
    printf("Original timestamp: %ld\n", original_ts);
    if (!n) {
        exit(1);
    }
    if (timestamp != original_ts) {
        exit(1);
    }
}

void test_get_time_by_timestamp() {
    printf("\nTest: get_time_by_timestamp()\n");
    struct tm *original_t = get_current_time();
    printf("Original time string: %s\n", get_time_string(original_t));
    long timestamp = get_timestamp_by_time(original_t);
    printf("Original timestamp: %ld\n", timestamp);
    struct tm *time = get_time_by_timestamp(timestamp);
    int n = time != NULL;
    printf("Current time is not null: %d\n", n);
    printf("Current time string: %s\n", get_time_string(time));
    printf("Current timestamp: %ld\n", get_timestamp_by_time(time));
    if (!n) {
        exit(1);
    }
}

void test_get_start_time() {
    printf("\nTest: get_start_time()\n");
    char *time_string = "2025-05-10 07:30:50";
    char *target_string = "2025-01-01 00:00:00";
    char type = 'M';
    struct tm *time = get_time_by_string(time_string);
    struct tm *start_time = get_start_time(time, type);
    int n = start_time != NULL;
    printf("Start time is not null: %d\n", start_time != NULL);
    printf("Start time type: %c\n", type);
    printf("Original time string: %s\n", time_string);
    printf("Start time string: %s\n", get_time_string(start_time));
    printf("Target time string: %s\n", target_string);
    if (!n) {
        exit(1);
    }
    if (strcmp(get_time_string(start_time), target_string) != 0) {
        exit(1);
    }
}

int main() {
    hello();
    setenv("TZ", "Etc/GMT-8", 1);
    tzset();
    test_get_current_time();
    test_get_time_string();
    test_get_time_by_string();
    test_get_timestamp_by_time();
    test_get_time_by_timestamp();
    test_get_start_time();
    return 0;
}
