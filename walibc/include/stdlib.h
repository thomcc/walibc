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

extern char **environ;

static inline char *getenv(char const *__name) {
    extern char *__walibc_getenv(char const *);
    return __walibc_getenv(__name);
}

static inline int setenv(char const *__var, char const *__val, int __over) {
    extern int __walibc_setenv(char const *, char const *, int);
    return __walibc_setenv(__var, __val, __over);
}

static inline int unsetenv(char const *__name) {
    extern int __walibc_unsetenv(char const *);
    return __walibc_unsetenv(__name);
}

static inline int putenv(char *__s) {
    extern int __walibc_putenv(char *);
    return __walibc_putenv(__s);
}

static inline int clearenv(void) {
    extern int __walibc_clearenv(void);
    return __walibc_clearenv();
}

typedef struct { int quot, rem } div_t;
static inline div_t div(int __n, int __d) {
    div_t __r = {__n / __d, __n % __d};
    return __r;
}

typedef struct { long quot, rem } ldiv_t;
static inline ldiv_t ldiv(long __n, long __d) {
    ldiv_t __r = {__n / __d, __n % __d};
    return __r;
}

typedef struct { long long quot, rem } lldiv_t;
static inline lldiv_t lldiv(long long __n, long long __d) {
    lldiv_t __r = {__n / __d, __n % __d};
    return __r;
}

__WALIBC_END_EXTERN;
