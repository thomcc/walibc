#pragma once
#include <__walibc.h>
#include <__walibc_ints.h>
#include <malloc.h>
#include <ctype.h>
#include <errno.h>
__WALIBC_BEGIN_EXTERN;

static inline int strcmp(char const *__s1, char const *__s2) {
    while (*__s1 && *__s1 == *__s2) ++__s1, ++__s2;
    return *(uint8_t const*)__s1 - *(uint8_t const*)__s2;
}

static inline int strcoll(char const *__s1, char const *__s2) {
    // Look ma, no locales.
    return strcmp(__s1, __s2);
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
    uint8_t const *__p = (uint8_t const*)__s;
    while (__n--) {
        if (*__p == (uint8_t)__c) return (void *)__p;
        ++__p;
    }
    return 0;
}

static inline void *memrchr(void const *__s, int __c, size_t __n) {
    uint8_t const *__p = (uint8_t const*)__s;
    while (__n--) if (__p[__n] == (uint8_t)__c) return (void *)&__p[__n];
    return 0;
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

static inline size_t strxfrm(char * __WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, size_t __n) {
    // basically just strncpy without zeroing the tail.
    size_t __len = strlen(__s2);
    if (__len < __n) while (__n-- && (*__s1++ = (unsigned char)*__s2++));
    return __len;
}

static inline int strcasecmp(char const *__s1, char const *__s2) {
    while (*__s1 && (*__s1 == *__s2 || tolower(*__s1) == tolower(*__s2))) ++__s1, ++__s2;
    return tolower(*__s1) - tolower(*__s2);
}

static inline int strncasecmp(char const *__s1, char const *__s2, size_t __n) {
    while (__n && *__s1 && (*__s1 == *__s2 || tolower(*__s1) == tolower(*__s2)))
        ++__s1, ++__s2, --__n;
    if (__n == 0) return 0;
    return tolower(*__s1) - tolower(*__s2);
}

static inline char *strcasestr(char const *__s1, char const *__s2) {
	for (size_t l = strlen(__s2); *__s1; ++__s1)
        if (!strncasecmp(__s1, __s2, l)) return (char *)__s1;
	return 0;
}

static inline size_t strlcpy(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, size_t __n) {
    char *__start = __s1;
	while (__n && (*__s1 = *__s2)) --__n, ++__s2, ++__s1;
	*__s1 = 0;
	return (__s1 - __start) + strlen(__s2);
}

static inline size_t strlcat(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, size_t __n) {
	size_t __len = strnlen(__s1, __n);
	if (__len == __n) return __len + strlen(__s2);
	return __len + strlcpy(__s1 + __len, __s2, __n - __len);
}

static inline char *strdup(char const *__s) {
    size_t __len = strlen(__s);
    char *__p = (char*)malloc(__len + 1);
    if (!__p) return 0;
    memcpy(__p, __s, __len);
    __p[__len] = '\0';
    return __p;
}

static inline char *strndup(char const *__s, size_t __n) {
    size_t __len = strnlen(__s, __n);
    char *__p = (char*)malloc(__len + 1);
    if (!__p) return 0;
    memcpy(__p, __s, __len);
    __p[__len] = '\0';
    return __p;
}

static inline char const *strerror(int __e) {
    extern char const *__walibc_strerror(int);
    return __walibc_strerror(__e);
}

static inline int strerror_r(int __e, char *__o, size_t __n) {
	char const *__s = strerror(__e);
	size_t __l = strlen(__s);
	if (__l >= __n) {
		if (__n) {
            __o[__n - 1] = 0;
            memcpy(__o, __s, __n - 1);
        }
		return ERANGE;
	}
	memcpy(__o, __s, __l + 1);
	return 0;
}

static inline char *strchrnul(char const *__s, int __c) {
	uint8_t __b = (uint8_t)__c;
	if (!__b) return (char *)__s + strlen(__s);
	for (; *__s && *(uint8_t *)__s != __b; ++__s);
	return (char *)__s;
}

#define __WALIBC_BITOP(a,b,op) \
    ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))

// Based on musl
static inline size_t strspn(char const *__s1, char const *__s2) {
    char const *__p = __s1;
	size_t __set[32 / sizeof(size_t)] = {0};

	if (!__s2[0]) return 0;
	if (!__s2[1]) {
		for (; *__s1 == *__s2; ++__s1);
		return __s1 - __p;
	}

	for (; *__s2 && __WALIBC_BITOP(__set, *(uint8_t*)__s2, |=); ++__s2);
	for (; *__s1 && __WALIBC_BITOP(__set, *(uint8_t*)__s1, &); ++__s1);
	return __s1 - __p;
}

// Based on musl
static inline size_t strcspn(char const *__s1, char const *__s2) {
	char const *__p = __s1;
	size_t __set[32 / sizeof(size_t)] = {0};

	if (!__s2[0] || !__s2[1]) return strchrnul(__s1, *__s2) - __p;

	for (; *__s2 && __WALIBC_BITOP(__set, *(uint8_t*)__s2, |=); ++__s2);
	for (; *__s1 && !__WALIBC_BITOP(__set, *(uint8_t*)__s1, &); ++__s1);
	return __s1-__p;
}

#undef __WALIBC_BITOP

// based on musl
static inline char *strtok(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2) {
	static char *__p = 0;
	if (!__s1 && !(__s1 = __p)) return NULL;
	__s1 += strspn(__s1, __s2);
	if (!*__s1) return __p = 0;
	__p = __s1 + strcspn(__s1, __s2);
	if (*__p) *__p++ = 0;
	else __p = 0;
	return __s1;
}

// based on musl
static inline char *strtok_r(char *__WALIBC_RESTRICT __s1, char const *__WALIBC_RESTRICT __s2, char **__WALIBC_RESTRICT __p) {
	if (!__s1 && !(__s1 = *__p)) return NULL;
	__s1 += strspn(__s1, __s2);
	if (!*__s1) return *__p = 0;
	*__p = __s1 + strcspn(__s1, __s2);
	if (**__p) *(*__p)++ = 0;
	else *__p = 0;
	return __s1;
}

// based on musl
static inline char *strsep(char **__ptr, const char *__sep) {
	char *__s = *__ptr, *__e;
	if (!__s) return 0;
	__e = __s + strcspn(__s, __sep);
	if (*__e) *__e++ = 0;
	else __e = 0;
	*__ptr = __e;
	return __s;
}

static inline char *strpbrk(char const *__s1, char const *__s2) {
	char const *__p = strcspn(__s1, __s2) + __s1;
    if (*__p) return (char*)__p;
    return 0;
}

static inline void bzero(void *__s, size_t __n) {
	memset(__s, 0, __n);
}

static inline void bcopy(void const *__s1, void *__s2, size_t __n) {
	memmove(__s2, __s1, __n);
}

static inline int bcmp(void const *__s1, void const *__s2, size_t __n) {
	return memcmp(__s1, __s2, __n);
}

static inline void *explicit_bzero(void *__s, size_t __n) {
    uint8_t volatile *__p = (uint8_t volatile *)__s;
    while (__n--) *__p++ = 0;
    return __s;
}

/*
TODO:
- more common non-standard apis?
- more of the `_s` APIs?
*/
__WALIBC_END_EXTERN;
