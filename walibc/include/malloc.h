#pragma once
#include <__walibc.h>
#include <__walibc_ints.h>
__WALIBC_BEGIN_EXTERN;

#ifndef alloca
# define alloca(sz) __builtin_alloca(sz)
#endif

static inline void *malloc(size_t __size) {
    extern void *__walibc_malloc(size_t);
    return __walibc_malloc(__size);
}

static inline void *calloc(size_t __count, size_t __size) {
    extern void *__walibc_calloc(size_t, size_t);
    return __walibc_calloc(__count, __size);
}

static inline void free(void *__ptr) {
    extern void __walibc_free(void *);
    __walibc_free(__ptr);
}

static inline void *realloc(void *__ptr, size_t __newsz) {
    extern void *__walibc_realloc(void *, size_t);
    return __walibc_realloc(__ptr, __newsz);
}

static inline int posix_memalign(void **__memptr, size_t __alignment, size_t __size) {
    extern int __walibc_posix_memalign(void **, size_t, size_t);
    return __walibc_posix_memalign(__memptr, __alignment, __size);
}

// C11
static inline void *aligned_alloc(size_t __alignment, size_t __size) {
    extern void *__walibc_aligned_alloc(size_t, size_t);
    return __walibc_aligned_alloc(__alignment, __size);
}

// Some non-standard functions that are easy to support.
static inline void *memalign(size_t __alignment, size_t __size) {
    return aligned_alloc(__alignment, __size);
}

static inline void *valloc(size_t __size) {
    size_t __wasm_known_page_size = 0x10000; // per spec.
    return aligned_alloc(__wasm_known_page_size, __size);
}

// Provided cuz it's easy for us to support and SQLite uses it.
static inline size_t malloc_usable_size(void *__ptr) {
    extern size_t __walibc_malloc_usable_size(void *);
    return __walibc_malloc_usable_size(__ptr);
}

// Could pretty easily do valloc and such.

__WALIBC_END_EXTERN;
