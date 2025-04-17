//
// Created by ZetoHkr on 2025/4/12.
//

#include "../../include/string/string_tools.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>

unsigned long safe_strlen(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

void safe_str_cpy(char *dest, const char *src) {
    if (src == NULL || dest == NULL || src[0] == '\0') {
        return;
    }
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void safe_str_n_cpy(char *dest, const char *src, unsigned long n) {
    if (src == NULL || dest == NULL || src[0] == '\0') {
        return;
    }
    int i = 0;
    for (; i < n; ++i) {
        if (src[i] == '\0') {
            break;
        }
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int parse_int(const char **s, const int width) {
    int i = 0;
    int flag = 1;
    if ((*s)[i] == '-') {
        i = 1;
        flag = -1;
    }
    if ((*s)[i] == '+') {
        i = 1;
    }
    int result = 0;
    while (i < width && isdigit((*s)[i])) {
        if ((*s)[i] > '9' || (*s)[i] < '0') {
            break;
        }
        result = result * 10 + ((*s)[i] - '0');
        i++;
    }
    return result * flag;
}
