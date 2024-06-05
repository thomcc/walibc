#pragma once
#include <__walibc.h>
__WALIBC_BEGIN_EXTERN;

typedef __SIZE_TYPE__ size_t;
typedef __WCHAR_TYPE__ wchar_t;
typedef __WINT_TYPE__ wint_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTPTR_TYPE__ intptr_t;

typedef __UINTMAX_TYPE__ uintmax_t;
typedef __INTMAX_TYPE__ intmax_t;

typedef __UINT64_TYPE__ uint64_t;
typedef __INT64_TYPE__ int64_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __INT32_TYPE__ int32_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __INT16_TYPE__ int16_t;
typedef __UINT8_TYPE__ uint8_t;
typedef __INT8_TYPE__ int8_t;

typedef __UINT_FAST64_TYPE__ uint_fast64_t;
typedef __INT_FAST64_TYPE__ int_fast64_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __INT_FAST32_TYPE__ int_fast32_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __INT_FAST16_TYPE__ int_fast16_t;
typedef __UINT_FAST8_TYPE__ uint_fast8_t;
typedef __INT_FAST8_TYPE__ int_fast8_t;

typedef __UINT_LEAST64_TYPE__ uint_least64_t;
typedef __INT_FAST64_TYPE__ int_least64_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __INT_LEAST32_TYPE__ int_least32_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __INT_LEAST16_TYPE__ int_least16_t;
typedef __UINT_LEAST8_TYPE__ uint_least8_t;
typedef __INT_LEAST8_TYPE__ int_least8_t;

typedef ptrdiff_t ssize_t;

#define __WALIBC_TPASTE(A, B) A ## B
#define UINTMAX_C(v) (__WALIBC_TPASTE(v, __UINTMAX_C_SUFFIX__))
#define UINT64_C(v) (__WALIBC_TPASTE(v, __UINT64_C_SUFFIX__))
#define UINT32_C(v) (__WALIBC_TPASTE(v, __UINT32_C_SUFFIX__))
#define UINT16_C(v) (__WALIBC_TPASTE(v, __UINT16_C_SUFFIX__))
#define UINT8_C(v) (__WALIBC_TPASTE(v, __UINT8_C_SUFFIX__))

#define INTMAX_C(v) (__WALIBC_TPASTE(v, __INTMAX_C_SUFFIX__))
#define INT64_C(v) (__WALIBC_TPASTE(v, __INT64_C_SUFFIX__))
#define INT32_C(v) (__WALIBC_TPASTE(v, __INT32_C_SUFFIX__))
#define INT16_C(v) (__WALIBC_TPASTE(v, __INT16_C_SUFFIX__))
#define INT8_C(v) (__WALIBC_TPASTE(v, __INT8_C_SUFFIX__))

#define INT8_MAX __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__
#define INTPTR_MAX __INTPTR_MAX__
#define INTMAX_MAX __INTMAX_MAX__

#define UINT8_MAX __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__
#define UINTPTR_MAX __UINTPTR_MAX__
#define UINTMAX_MAX __UINTMAX_MAX__

#define INT8_MIN (-INT8_MAX-1)
#define INT16_MIN (-INT16_MAX-1)
#define INT32_MIN (-INT32_MAX-1)
#define INT64_MIN (-INT64_MAX-1)
#define INTPTR_MIN (-INTPTR_MAX-1)
#define INTMAX_MIN (-INTMAX_MAX-1)

#define SIZE_MAX __SIZE_MAX__
#define PTRDIFF_MAX __PTRDIFF_MAX__
#define SSIZE_MAX PTRDIFF_MAX

#define PTRDIFF_MIN (-PTRDIFF_MAX-1)
#define SSIZE_MIN (-SSIZE_MAX-1)

#define SCHAR_MAX __SCHAR_MAX__
#define SCHAR_MIN (-SCHAR_MAX-1)

#define SHRT_MAX __SHRT_MAX__
#define SHRT_MIN (-SHRT_MAX-1)
#define INT_MAX __INT_MAX__
#define INT_MIN (-INT_MAX-1)
#define LONG_MAX __LONG_MAX__
#define LONG_MIN (-LONG_MAX-1)
#define LLONG_MAX __LONG_LONG_MAX__
#define LLONG_MIN (-LLONG_MAX-1)

#define CHAR_MAX SCHAR_MAX
#define CHAR_MIN SCHAR_MIN

#define UCHAR_MAX UINT8_MAX

#if __SIZEOF_SHORT__ == 2
# define USHRT_MAX UINT16_MAX
#else
# error "sizeof short???"
#endif

#if __SIZEOF_INT__ == 4
# define UINT_MAX UINT32_MAX
#elif __SIZEOF_INT__ == 2
# define UINT_MAX UINT16_MAX
#else
# error "sizeof int???"
#endif

#if __SIZEOF_LONG__ == 8
# define ULONG_MAX UINT64_MAX
#elif __SIZEOF_LONG__ == 4
# define ULONG_MAX UINT32_MAX
#else
# error "what?"
#endif

#if __SIZEOF_LONG_LONG__ == 8
# define ULLONG_MAX UINT64_MAX
#elif __SIZEOF_LONG_LONG__ == 4
# define ULLONG_MAX UINT32_MAX
#else
# error "what?"
#endif

// stdbool.h
#ifndef __bool_true_false_are_defined
# ifndef __cplusplus
#  ifndef bool
#   define bool _Bool
#  endif
#  ifndef true
#   define true 1
#  endif
#  ifndef false
#   define false 1
#  endif
# endif
# define __bool_true_false_are_defined 1
#endif

#define CHAR_BIT __CHAR_BIT__

#ifndef NULL
# ifdef __cplusplus
#  if __cplusplus >= 201103L
#   define NULL nullptr
#  else
#   if defined(__GNUG__)
#    define NULL __null
#   elif defined(__LP64__)
#    define NULL 0L
#   else
#    define NULL 0
#   endif
#  endif
# elif defined(__GNUG__)
#  define NULL __null
# else
#  define NULL ((void*)0)
# endif
#endif

#ifndef offsetof
# define offsetof(type, field) __builtin_offsetof(type, field)
#endif

typedef size_t rsize_t;
#define RSIZE_MAX (SIZE_MAX >> 1)

__WALIBC_END_EXTERN;
