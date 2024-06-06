#pragma once
#include <__walibc.h>
#include <__walibc_ints.h>
#include <stdarg.h>
__WALIBC_BEGIN_EXTERN;

static inline int vsprintf(char *__buf, char const *__fmt, va_list __ap) {
    extern int __walibc_vsprintf(char *, char const*, va_list);
    return __walibc_vsprintf(__buf, __fmt, __ap);
}

static inline int vsnprintf(char *__buf, size_t __n, char const *__fmt, va_list __va) {
    extern int __walibc_vnsprintf(char *, size_t, char const*, va_list);
    return __walibc_vnsprintf(__buf, __n, __fmt, __va);
}

static inline int sprintf(char *__buf, char const *__fmt, ...) {
    va_list __ap;
    va_start(__ap, __fmt);
    int __ret = vsprintf(__buf, __fmt, __ap);
    va_end(__ap);
    return __ret;
}

static inline int snprintf(char *__buf, size_t __n, char const *__fmt, ...) {
    va_list __ap;
    va_start(__ap, __fmt);
    int __ret = vnsprintf(__buf, __n, __fmt, __ap);
    va_end(__ap);
    return __ret;
}

__WALIBC_END_EXTERN;
