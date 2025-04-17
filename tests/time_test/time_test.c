//
// Created by ZetoHkr on 2025/4/11.
//

#include "time/time_tools.h" // Assuming the header is in the specified path
#include "string/string_tools.h" // Assuming string_tools.h is needed for parse_int
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Helper function to compare struct tm
static int compare_tm(const struct tm *tm1, const struct tm *tm2) {
    if (tm1 == NULL) {
        return tm1 == tm2;
    }
    return tm1->tm_year == tm2->tm_year &&
           tm1->tm_mon == tm2->tm_mon &&
           tm1->tm_mday == tm2->tm_mday &&
           tm1->tm_hour == tm2->tm_hour &&
           tm1->tm_min == tm2->tm_min &&
           tm1->tm_sec == tm2->tm_sec;
}

// Test case for safe_localtime (difficult to fully automate due to time dependency)
static void test_safe_localtime(void **state) {
    time_t t = time(NULL);
    struct tm buf;
    struct tm *result = safe_localtime(&t, &buf);
    assert_non_null(result);
    // We can't assert the exact time, but we can check if the function returns a valid pointer.
}

// Test case for get_current_time (difficult to fully automate due to time dependency)
static void test_get_current_time(void **state) {
    struct tm *current_time = get_current_time();
    assert_non_null(current_time);
    free(current_time);
}

// Test case for get_time_string (difficult to fully automate due to time dependency)
static void test_get_time_string(void **state) {
    const time_t t = 1678886400; // Example timestamp (March 15, 2023)
    struct tm buf;
    safe_localtime(&t, &buf);
    char *time_string = get_time_string(&buf);
    assert_non_null(time_string);
    assert_string_equal(time_string, "2023-03-15 21:20:00");
    free(time_string);
}

// Test case for get_time_by_string
static void test_get_time_by_string(void **state) {
    char *time_string = "2025-04-17 10:30:45";
    struct tm *parsed_time = get_time_by_string(time_string);
    assert_non_null(parsed_time);
    assert_int_equal(parsed_time->tm_year + 1900, 2025);
    assert_int_equal(parsed_time->tm_mon + 1, 4);
    assert_int_equal(parsed_time->tm_mday, 17);
    assert_int_equal(parsed_time->tm_hour, 10);
    assert_int_equal(parsed_time->tm_min, 30);
    assert_int_equal(parsed_time->tm_sec, 45);
    free(parsed_time);

    time_string = "2023-01-01 00:00:00";
    parsed_time = get_time_by_string(time_string);
    assert_non_null(parsed_time);
    assert_int_equal(parsed_time->tm_year + 1900, 2023);
    assert_int_equal(parsed_time->tm_mon + 1, 1);
    assert_int_equal(parsed_time->tm_mday, 1);
    assert_int_equal(parsed_time->tm_hour, 0);
    assert_int_equal(parsed_time->tm_min, 0);
    assert_int_equal(parsed_time->tm_sec, 0);
    free(parsed_time);
}

// Test case for get_timestamp_by_time
static void test_get_timestamp_by_time(void **state) {
    struct tm time_val;
    memset(&time_val, 0, sizeof(struct tm));
    time_val.tm_year = 2025 - 1900;
    time_val.tm_mon = 3; // April
    time_val.tm_mday = 17;
    time_val.tm_hour = 11;
    time_val.tm_min = 0;
    time_val.tm_sec = 0;
    time_t expected_ts = mktime(&time_val);

    struct timestamp *ts = get_timestamp_by_time(&time_val);
    assert_non_null(ts);
    assert_int_equal(ts->val, expected_ts);
    free(ts);
}

// Test case for get_time_by_timestamp
static void test_get_time_by_timestamp(void **state) {
    struct timestamp ts;
    struct tm expected_time;
    memset(&expected_time, 0, sizeof(struct tm));
    expected_time.tm_year = 2025 - 1900;
    expected_time.tm_mon = 3; // April
    expected_time.tm_mday = 17;
    expected_time.tm_hour = 11;
    expected_time.tm_min = 30;
    expected_time.tm_sec = 59;
    ts.val = mktime(&expected_time);

    struct tm *actual_time = get_time_by_timestamp(&ts);
    assert_non_null(actual_time);
    assert_int_equal(actual_time->tm_year, expected_time.tm_year);
    assert_int_equal(actual_time->tm_mon, expected_time.tm_mon);
    assert_int_equal(actual_time->tm_mday, expected_time.tm_mday);
    assert_int_equal(actual_time->tm_hour, expected_time.tm_hour);
    assert_int_equal(actual_time->tm_min, expected_time.tm_min);
    assert_int_equal(actual_time->tm_sec, expected_time.tm_sec);
    free(actual_time);
}

// Test case for get_start_time
static void test_get_start_time(void **state) {
    struct tm time_val;
    memset(&time_val, 0, sizeof(struct tm));
    time_val.tm_year = 2025 - 1900;
    time_val.tm_mon = 3; // April
    time_val.tm_mday = 17;
    time_val.tm_hour = 10;
    time_val.tm_min = 30;
    time_val.tm_sec = 45;

    struct tm expected_month_start;
    memcpy(&expected_month_start, &time_val, sizeof(struct tm));
    expected_month_start.tm_mon = 0;
    expected_month_start.tm_mday = 1;
    expected_month_start.tm_hour = 0;
    expected_month_start.tm_min = 0;
    expected_month_start.tm_sec = 0;
    struct tm *actual_month_start = get_start_time(&time_val, 'M');
    assert_non_null(actual_month_start);
    assert_true(compare_tm(actual_month_start, &expected_month_start));

    struct tm expected_day_start;
    memcpy(&expected_day_start, &time_val, sizeof(struct tm));
    expected_day_start.tm_mday = 1;
    expected_day_start.tm_hour = 0;
    expected_day_start.tm_min = 0;
    expected_day_start.tm_sec = 0;
    struct tm *actual_day_start = get_start_time(&time_val, 'D');
    assert_non_null(actual_day_start);
    assert_true(compare_tm(actual_day_start, &expected_day_start));

    struct tm expected_hour_start;
    memcpy(&expected_hour_start, &time_val, sizeof(struct tm));
    expected_hour_start.tm_hour = 0;
    expected_hour_start.tm_min = 0;
    expected_hour_start.tm_sec = 0;
    struct tm *actual_hour_start = get_start_time(&time_val, 'H');
    assert_non_null(actual_hour_start);
    assert_true(compare_tm(actual_hour_start, &expected_hour_start));

    struct tm expected_minute_start;
    memcpy(&expected_minute_start, &time_val, sizeof(struct tm));
    expected_minute_start.tm_min = 0;
    expected_minute_start.tm_sec = 0;
    struct tm *actual_minute_start = get_start_time(&time_val, 'm');
    assert_non_null(actual_minute_start);
    assert_true(compare_tm(actual_minute_start, &expected_minute_start));

    assert_null(get_start_time(&time_val, 'X'));
    assert_null(get_start_time(NULL, 'M'));
}

// Test case for is_leap_year
static void test_is_leap_year(void **state) {
    assert_true(is_leap_year(2000));
    assert_true(is_leap_year(2024));
    assert_false(is_leap_year(2100));
    assert_false(is_leap_year(2023));
}

// Test case for get_days_in_month
static void test_get_days_in_month(void **state) {
    assert_int_equal(get_days_in_month(2023, 0), 31); // January
    assert_int_equal(get_days_in_month(2024, 1), 29); // February (leap year)
    assert_int_equal(get_days_in_month(2023, 1), 28); // February (non-leap year)
    assert_int_equal(get_days_in_month(2023, 2), 31); // March
    assert_int_equal(get_days_in_month(2023, 3), 30); // April
    assert_int_equal(get_days_in_month(2023, 11), 31); // December
    assert_int_equal(get_days_in_month(2023, -1), 1);  // Invalid month
    assert_int_equal(get_days_in_month(2023, 13), 1); // Invalid month
}

// Test case for get_end_time
static void test_get_end_time(void **state) {
    struct tm time_val;
    memset(&time_val, 0, sizeof(struct tm));
    time_val.tm_year = 2025 - 1900;
    time_val.tm_mon = 3;
    time_val.tm_mday = 17;
    time_val.tm_hour = 10;
    time_val.tm_min = 30;
    time_val.tm_sec = 45;

    struct tm expected_month_end;
    memcpy(&expected_month_end, &time_val, sizeof(struct tm));
    expected_month_end.tm_mon = 11;
    expected_month_end.tm_mday = 31;
    expected_month_end.tm_hour = 23;
    expected_month_end.tm_min = 59;
    expected_month_end.tm_sec = 59;
    struct tm *actual_month_end = get_end_time(&time_val, 'M');
    assert_non_null(actual_month_end);
    assert_true(compare_tm(actual_month_end, &expected_month_end));

    struct tm expected_day_end;
    memcpy(&expected_day_end, &time_val, sizeof(struct tm));
    expected_day_end.tm_mday = 31;
    expected_day_end.tm_hour = 23;
    expected_day_end.tm_min = 59;
    expected_day_end.tm_sec = 59;
    struct tm *actual_day_end = get_end_time(&time_val, 'D');
    assert_non_null(actual_day_end);
    assert_true(compare_tm(actual_day_end, &expected_day_end));

    struct tm expected_hour_end;
    memcpy(&expected_hour_end, &time_val, sizeof(struct tm));
    expected_hour_end.tm_hour = 23;
    expected_hour_end.tm_min = 59;
    expected_hour_end.tm_sec = 59;
    struct tm *actual_hour_end = get_end_time(&time_val, 'H');
    assert_non_null(actual_hour_end);
    assert_true(compare_tm(actual_hour_end, &expected_hour_end));

    struct tm expected_minute_end;
    memcpy(&expected_minute_end, &time_val, sizeof(struct tm));
    expected_minute_end.tm_min = 59;
    expected_minute_end.tm_sec = 59;
    struct tm *actual_minute_end = get_end_time(&time_val, 'm');
    assert_non_null(actual_minute_end);
    assert_true(compare_tm(actual_minute_end, &expected_minute_end));

    assert_null(get_end_time(&time_val, 'X'));
    assert_null(get_end_time(NULL, 'M'));
}

// Test case for replace_ts_token
static void test_replace_ts_token(void **state) {
    const char *format1 = "%Y-%m-%d %H:%M:%S";
    char *replaced1 = replace_ts_token(format1);
    assert_non_null(replaced1);
    assert_string_equal(replaced1, "%Y-%m-%d %H:%M:%S");
    free(replaced1);

    const char *format2 = "Timestamp: %ts";
    char *replaced2 = replace_ts_token(format2);
    assert_non_null(replaced2);
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
    assert_string_equal(replaced2, "Timestamp: %lld");
#else
    assert_string_equal(replaced2, "Timestamp: %ld");
#endif
    free(replaced2);

    const char *format3 = "%ts - %ts";
    char *replaced3 = replace_ts_token(format3);
    assert_non_null(replaced3);
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
    assert_string_equal(replaced3, "%lld - %lld");
#else
    assert_string_equal(replaced3, "%ld - %ld");
#endif
    free(replaced3);

    char *format4 = "No token";
    char *replaced4 = replace_ts_token(format4);
    assert_non_null(replaced4);
    assert_string_equal(replaced4, "No token");
    free(replaced4);

    assert_null(replace_ts_token(NULL));
}

// Test case for timestamp_printf (difficult to fully automate due to output)
static void test_timestamp_printf(void **state) {
    // This test primarily checks if the function runs without crashing.
    // Verifying the output requires capturing stdout, which is more complex.
    int result = timestamp_printf("Current timestamp: %ts\n", (long long)time(NULL));
    assert_true(result >= 0);

    result = timestamp_printf("Regular format: %d\n", 123);
    assert_true(result >= 0);
    result = timestamp_printf("Mixed: %s - %ts - %d\n", "hello", (long long)time(NULL), 456);
    assert_true(result >= 0);

    result = timestamp_printf("No token format\n");
    assert_true(result >= 0);

    // Note: We are not directly asserting the output of printf here.
    // More advanced testing would involve redirecting stdout and capturing the output.
}

void time_test() {
#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
    setenv("TZ", "Etc/GMT-8", 1);
    tzset();
#endif
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_safe_localtime),
        cmocka_unit_test(test_get_current_time),
        cmocka_unit_test(test_get_time_string),
        cmocka_unit_test(test_get_time_by_string),
        cmocka_unit_test(test_get_timestamp_by_time),
        cmocka_unit_test(test_get_time_by_timestamp),
        cmocka_unit_test(test_get_start_time),
        cmocka_unit_test(test_is_leap_year),
        cmocka_unit_test(test_get_days_in_month),
        cmocka_unit_test(test_get_end_time),
        cmocka_unit_test(test_replace_ts_token),
        cmocka_unit_test(test_timestamp_printf),
    };

    cmocka_run_group_tests(tests, NULL, NULL);
}
