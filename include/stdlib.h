#pragma once
#include <__walibc.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
__WALIBC_BEGIN_EXTERN;

static inline long long atoll(char const *__s) {
    while (isspace((unsigned char)*__s)) ++__s;

    int __neg = 0;
    if (*__s == '+') ++__s;
    else if (*__s == '-') __neg = 1, ++__s;

    long long __res = 0;
    static char const __dig[] = "0123456789";
    for (char const *__x; (__x = (char const*)memchr(__dig, tolower((unsigned char)*__s++), 10));)
        __res = __res * 10 + (__x - __dig);

    return __neg ? -__res : __res;
}

static inline long atol(char const *__s) {
    return (long)atoll(__s);
}

static inline int atoi(char const *__s) {
    return (int)atoll(__s);
}

__WALIBC_END_EXTERN;
