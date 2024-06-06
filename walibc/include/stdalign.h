#pragma once
#include <__walibc.h>
__WALIBC_BEGIN_EXTERN;

#ifndef __cplusplus
# define alignas _Alignas
# define alignof _Alignof
#endif

#define __alignas_is_defined 1
#define __alignof_is_defined 1

__WALIBC_END_EXTERN;
