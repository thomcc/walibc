#include <__walibc_ints.h>
#include <stdarg.h>
#define STB_SPRINTF_DECORATE(name) __walibc_stbsp_##name
#define STB_SPRINTF_STATIC 1
#define STB_SPRINTF_IMPLEMENTATION 1
#define STB_SPRINTF_NOUNALIGNED 1
#include "./stb_sprintf.h"

__WALIBC_BEGIN_EXTERN;

// Only expose these two (everything else is static).
int __walibc_vsprintf(char *buf, char const *fmt, va_list va) {
    return __walibc_stbsp_vsprintf(buf, fmt, va);
}

int __walibc_vsnprintf(char *buf, size_t n, char const *fmt, va_list va) {
    if (n > INT_MAX) n = (size_t)INT_MAX;
    return __walibc_stbsp_vnsprintf(buf, n, fmt, va);
}

__WALIBC_END_EXTERN;
