#pragma once
#include <__walibc.h>
#include <__walibc_ints.h>
__WALIBC_BEGIN_EXTERN;
// Most of this is provided by `__walibc_ints.h`.

// TODO: Is this right?
typedef struct { _Alignas(__BIGGEST_ALIGNMENT__) char _Private[__BIGGEST_ALIGNMENT__]; } max_align_t;


__WALIBC_END_EXTERN;
