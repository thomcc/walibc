#pragma once
#include <__walibc.h>
#include <__walibc_ints.h>
__WALIBC_BEGIN_EXTERN;

static inline int strcmp(char const *__s1, char const *__s2) {
    while (*__s1 && *__s1 == *__s2) ++__s1, ++__s2;
    return *(uint8_t const*)__s1 - *(uint8_t const*)__s2;
}

static inline int strcoll(char const *__s1, char const *__s2) {
    // Look ma, no locales.
    return strcmp(__s1, __s2);
}

static inline size_t strcspn(char const *__s1, char const *__s2) {
    size_t __i;
    for (__i = 0; __s1[__i]; ++__i) {
        for (char const *__p = __s2; *__p;)
            if (__s1[__i] == *__p++) return __i;
    }
    return __i;
}

static inline size_t strlen(char const *__s) {
    size_t __l = 0;
    while (__s[__l]) ++__l;
    return __l;
}

static inline int strncmp(char const *__s1, char const *__s2, size_t __n) {
    while (__n && *__s1 && (*__s1 == *__s2)) ++__s1, ++__s2, --__n;
    if (__n == 0) return 0;
    return *(unsigned char *)__s1 - *(unsigned char *)__s2;
}

static inline char *strrchr(char const *s, int c) {
    size_t __i = 0;
    while (s[__i++]);
    do if (s[--__i] == (char)c) return (char*)(s + __i);
    while (__i);
    return NULL;
}

static inline void *memchr(void const *__s, int __c, size_t __n) {
    unsigned char const *__p = (unsigned char const*)__s;
    while (__n--) {
        if (*__p == (unsigned char)__c) return (void *)__p;
        ++__p;
    }
}

static inline int memcmp(void const *__s1, void const *__s2, size_t __n) {
    unsigned char const *__p1 = (unsigned char const *)__s1, *__p2 = (unsigned char const *)__s2;
    while (__n--) {
        if (*__p1 != *__p2) return *__p1 - *__p2;
        ++__p1, ++__p2;
    }
}

static inline void *memcpy(void *__WALIBC_RESTRICT __s1, void const *__WALIBC_RESTRICT __s2, size_t __n) {
    char *__d = (char *)__s1;
    char const *__s = (char const *)__s2;
    while (__n--) *__d++ = *__s++;
    return __s1;
}

static inline void *memmove(void *__s1, void const *__s2, size_t __n) {
    char *__d = (char *)__s1;
    const char *__s = (const char *)__s2;
    if (__d <= __s) while (__n--) *__d++ = *__s++;
    else {
        __s += __n, __d += __n;
        while (__n--) *--__d = *--__s;
    }
    return __s1;
}

static inline void *memset(void *__s, int __c, size_t __n) {
    unsigned char *__p = (unsigned char *)__s;
    while (__n--) *__p++ = (unsigned char)__c;
    return __s;
}

static inline char *strcpy(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2) {
    char *__ret = __s1;
    while ((*__s1++ = *__s2++));
    return __ret;
}

static inline char *strncpy(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, size_t __n) {
    char *__ret = __s1;
    while (__n && (*__s1++ = *__s2++)) --__n;
    while (__n-- > 1) *__s1++ = '\0';
    return __ret;
}

static inline char *strcat(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2) {
    char *__ret = __s1;
    if (*__s1) while (*++__s1);
    while ((*__s1++ = *__s2++));
    return __ret;
}

static inline char *strncat(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, size_t __n) {
    char *__ret = __s1;
    while (*__s1) ++__s1;
    while (__n && (*__s1++ = *__s2++)) --__n;
    if (!__n) *__s1 = '\0';
    return __ret;
}

static inline char *strchr(char const *__s, int __c) {
    do if (*__s == (char)__c) return (char *)__s;
    while (*__s++);
    return 0;
}

static inline char *strrchr(char const *__s, int __c) {
    size_t __i = 0;
    while (__s[__i++]);
    do if (__s[--__i] == (char)__c) return ((char *)__s) + __i;
    while (__i);
    return 0;
}

static inline char *strstr(char const *__s1, char const *__s2) {
    char const *__p1 = __s1;
    while (*__s1) {
        char const *__p2 = __s2;
        while (*__p2 && (*__p1 == *__p2)) ++__p1, ++__p2;
        if (!*__p2) return (char *)__s1;
        ++__s1;
        __p1 = __s1;
    }
    return 0;
}

static inline char *strtok_s(
    char *__WALIBC_RESTRICT __s1,
    rsize_t *__WALIBC_RESTRICT __s1max,
    char const *__WALIBC_RESTRICT __s2,
    char **__WALIBC_RESTRICT __ptr
) {
    char const *__p = __s2;
    if (!__s1max || !__s2 || !__ptr || (!__s1 && !*__ptr) || *__s1max > RSIZE_MAX)
        return 0; // EINVAL

    if (__s1) *__ptr = __s1;
    else {
        if (!*__ptr) return 0;
        __s1 = *__ptr;
    }

    while (*__p && *__s1) {
        if (*__s1 == *__p) {
            if (*__s1max == 0) return 0; // EINVAL
            ++__s1;
            --*__s1max;
            __p = __s2;
            continue;
        }

        ++__p;
    }

    if (!*__s1) {
        *__ptr = __s1;
        return 0;
    }

    *__ptr = __s1;

    while (**__ptr) {
        __p = __s2;
        while (*__p) {
            if (**__ptr == *__p++) {
                if (*__s1max == 0) return 0; // EINVAL
                --*__s1max;
                *((*__ptr)++) = '\0';
                return __s1;
            }
        }

        if (*__s1max == 0) return 0; // EINVAL
        --*__s1max;
        ++*__ptr;
    }
    return __s1;
}

static inline char *strtok(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2) {
    static struct { char *__tmp; rsize_t __max; } __state = {0};
    if (__s1) __state.__tmp = __s1, __state.__max = strlen(__s1);
    return strtok_s(__s1, &__state.__max, __s2, &__state.__tmp);
}

static inline size_t strxfrm(char * __WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, size_t __n) {
    // basically just strncpy without zeroing the tail.
    size_t __len = strlen(__s2);
    if (__len < __n) while (__n-- && (*__s1++ = (unsigned char)*__s2++));
    return __len;
}

static inline size_t strspn(char const *__s1, char const *__s2) {
    // TODO bitset
    size_t __n = 0;
    while (__s1[__n]) {
        char const *__p = __s2;
        while (*__p) {
            if (__s1[__n] == *__p) break;
            ++__p;
        }
        if (!*__p) return __n;
        ++__n;
    }
    return __n;
}

static inline size_t strcspn(char const *__s1, char const *__s2) {
    // TODO bitset
    size_t __n = 0;
    while (__s1[__n]) {
        for (char const *__p = __s2; *__p;)
            if (__s1[__n] == *__p++) return __n;
        ++__n;
    }
    return __n;
}

static inline char *strpbrk(char const *__s1, char const *__s2) {
    while (*__s1) {
        for (char const *__p2 = __s2; *__p2;)
            if (*__s1 == *__p2++) return (char*)__s1;
        ++__s1;
    }
    return 0;
}

/*
TODO:
- strerror
*/
__WALIBC_END_EXTERN;