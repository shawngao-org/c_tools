//
// Created by ZetoHkr on 2025/4/12.
//

#ifndef TOOLS_STRING_TOOLS_H
#define TOOLS_STRING_TOOLS_H

unsigned long safe_strlen(const char *str);

void safe_str_cpy(char *dest, const char *src);

void safe_str_n_cpy(char *dest, const char *src, unsigned long n);

int parse_int(const char **s, int width);

#endif //TOOLS_STRING_TOOLS_H
