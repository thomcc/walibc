#pragma once
#include <__walibc.h>
__WALIBC_BEGIN_EXTERN;

#define LC_ALL 0
#define LC_COLLATE 1
#define LC_CTYPE 2
#define LC_MONETARY 3
#define LC_NUMERIC 4
#define LC_TIME 5
#define LC_MESSAGES 6

static inline char *setlocale(int __category, char const *__locale) {
    if (!__locale || (__locale[0] == 'C' && __locale[1] == '\0'))
        return (char *)"C";
    return 0;
}

// TODO: lconv/localeconv?

__WALIBC_END_EXTERN;
