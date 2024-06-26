// #pragma once
#include <__walibc.h>
__WALIBC_BEGIN_EXTERN;
// Is this compliant?
#ifdef NDEBUG
# define assert(X) ((void)(0))
#else
# define assert(X) ((void)((X) ? 0 : (__builtin_trap(), 0)))
#endif

#ifndef __cplusplus
# define static_assert _Static_assert
#endif

__WALIBC_END_EXTERN;
