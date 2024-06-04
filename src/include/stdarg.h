#pragma once
#include <__walibc.h>
__WALIBC_BEGIN_EXTERN;

typedef __builtin_va_list va_list;
#define va_start(__v, __a) __builtin_va_start(__v, __a)
#define va_end(__v) __builtin_va_end(__v)
#define va_arg(__v, __ty) __builtin_va_arg(__v, __ty)
#define va_copy(__d, __s) __builtin_va_copy(__d, __s)

__WALIBC_END_EXTERN;
