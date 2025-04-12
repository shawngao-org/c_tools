//
// Created by ZetoHkr on 2025/4/12.
//

#include "string_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tools.h>

void test_str_len() {
    printf("\nTest: safe_strlen()\n");
    const char *str = "ABCD DCBA";
    const unsigned long target_len = 9;
    const unsigned long len = safe_strlen(str);
    printf("The target length is: %ld\n", target_len);
    printf("The length of the string is: %ld\n", len);
    if (len != target_len) {
        fprintf(stderr, "Error: The length of the string is not correct.\n");
        exit(1);
    }
}

void test_safe_str_cpy() {
    printf("\nTest: safe_str_cpy()\n");
    char *str1 = "A B C D ";
    char *dest = (char *) malloc(sizeof(char) * (safe_strlen(str1)));
    safe_str_cpy(dest, str1);
    printf("The target result is: %s\n", str1);
    printf("The result is: %s\n", dest);
    if (strcmp(str1, dest) != 0) {
        fprintf(stderr, "Error: safe_str_cpy() results don\'t match.");
        exit(1);
    }
}

void test_safe_str_n_cpy() {
    printf("\nTest: safe_str_n_cpy()\n");
    const char *str1 = "A B C D ";
    char *target_str = "A B";
    char *dest = (char *) malloc(sizeof(char) * (safe_strlen(str1)));
    safe_str_n_cpy(dest, str1, 3);
    printf("The target result is: %s\n", target_str);
    printf("The result is: %s\n", dest);
    if (strcmp(target_str, dest) != 0) {
        fprintf(stderr, "Error: safe_str_n_cpy() results don\'t match.");
        exit(1);
    }
}

void test_parse_int() {
    printf("\nTest: parse_int()\n");
    const char *str = "12345";
    const int num = 12345;
    const int result = parse_int(&str, 6);
    printf("The target result is: %d\n", num);
    printf("The result is: %d\n", result);
    if (result != num) {
        fprintf(stderr, "Error: parse_int() results don\'t match.");
        exit(1);
    }
    const char *n_str = "-12345";
    const int n_num = -12345;
    const int n_result = parse_int(&n_str, 6);
    printf("The target result is: %d\n", n_num);
    printf("The result is: %d\n", n_result);
    if (n_result != num) {
        fprintf(stderr, "Error: parse_int() results don\'t match.");
        exit(1);
    }
}

int string_test() {
    test_str_len();
    test_safe_str_cpy();
    test_safe_str_n_cpy();
    test_parse_int();
    return 0;
}
