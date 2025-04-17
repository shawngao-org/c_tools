//
// Created by ZetoHkr on 2025/4/12.
//

#include "string/string_tools.h" // Assuming the header is in the specified path
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test case for safe_strlen
static void test_safe_strlen(void **state) {
    assert_int_equal(safe_strlen(NULL), 0);
    assert_int_equal(safe_strlen(""), 0);
    assert_int_equal(safe_strlen("hello"), 5);
    assert_int_equal(safe_strlen("world!"), 6);
}

// Test case for safe_str_cpy
static void test_safe_str_cpy(void **state) {
    char dest[20];
    safe_str_cpy(dest, NULL);
    assert_string_equal(dest, ""); // Expect no change

    safe_str_cpy(dest, "");
    assert_string_equal(dest, "");

    safe_str_cpy(NULL, "test");
    // No assertion here, we expect it to handle NULL gracefully without crashing

    safe_str_cpy(dest, "hello");
    assert_string_equal(dest, "hello");

    safe_str_cpy(dest, "a longer string");
    assert_string_equal(dest, "a longer string");
}

// Test case for safe_str_n_cpy
static void test_safe_str_n_cpy(void **state) {
    char dest[20];

    safe_str_n_cpy(dest, NULL, 5);
    assert_string_equal(dest, "");

    safe_str_n_cpy(dest, "", 5);
    assert_string_equal(dest, "");

    safe_str_n_cpy(NULL, "test", 5);
    // No assertion here, expect graceful handling of NULL

    safe_str_n_cpy(dest, "hello", 3);
    assert_string_equal(dest, "hel");

    safe_str_n_cpy(dest, "hello", 10);
    assert_string_equal(dest, "hello");

    safe_str_n_cpy(dest, "short", 0);
    assert_string_equal(dest, "");

    safe_str_n_cpy(dest, "longer string", 5);
    assert_string_equal(dest, "longe");
}

// Test case for parse_int
static void test_parse_int(void **state) {
    const char *str1 = "123";
    assert_int_equal(parse_int(&str1, 3), 123);

    const char *str2 = "-45";
    assert_int_equal(parse_int(&str2, 3), -45);

    const char *str3 = "abc";
    assert_int_equal(parse_int(&str3, 3), 0);

    const char *str4 = "12x";
    assert_int_equal(parse_int(&str4, 3), 12);

    const char *str5 = "-9y";
    assert_int_equal(parse_int(&str5, 3), -9);

    const char *str6 = "9876";
    assert_int_equal(parse_int(&str6, 3), 987); // Width limits parsing

    const char *str7 = "-1234";
    assert_int_equal(parse_int(&str7, 4), -123); // Width limits parsing with negative

    const char *str8 = "";
    assert_int_equal(parse_int(&str8, 3), 0);

    const char *str9 = "+12"; // Plus sign is not handled
    assert_int_equal(parse_int(&str9, 3), 12);
}

void string_test() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_safe_strlen),
        cmocka_unit_test(test_safe_str_cpy),
        cmocka_unit_test(test_safe_str_n_cpy),
        cmocka_unit_test(test_parse_int),
    };

    cmocka_run_group_tests(tests, NULL, NULL);
}
