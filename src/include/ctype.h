#pragma once
#include <__walibc.h>
__WALIBC_BEGIN_EXTERN;
/* Based on a trick from luajit. */
static const unsigned char __walibc_char_masks[258] = {
    0, /* to handle EOF */
    1,   1,   1,   1,   1,   1,   1,   1,   1,   3,   3,   3,   3,   3,   1,   1,
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
    2,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 4,   4,   4,   4,   4,   4,
    4,   176, 176, 176, 176, 176, 176, 160, 160, 160, 160, 160, 160, 160, 160, 160,
    160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 4,   4,   4,   4,   132,
    4,   208, 208, 208, 208, 208, 208, 192, 192, 192, 192, 192, 192, 192, 192, 192,
    192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 4,   4,   4,   4,   1,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    0, /* so we can be put in SHF_STRINGS and potentially deduped (does this work?) */
};

static inline int iscntrl(int __c) { return !!(__walibc_char_masks[__c+1] & 0x01); }
static inline int isspace(int __c) { return !!(__walibc_char_masks[__c+1] & 0x02); }
static inline int ispunct(int __c) { return !!(__walibc_char_masks[__c+1] & 0x04); }
static inline int isdigit(int __c) { return !!(__walibc_char_masks[__c+1] & 0x08); }
static inline int isxdigit(int __c) { return !!(__walibc_char_masks[__c+1] & 0x10); }
static inline int isupper(int __c) { return !!(__walibc_char_masks[__c+1] & 0x20); }
static inline int islower(int __c) { return !!(__walibc_char_masks[__c+1] & 0x40); }
static inline int isident(int __c) { return !!(__walibc_char_masks[__c+1] & 0x80); }
static inline int isalpha(int __c) { return !!(__walibc_char_masks[__c+1] & (0x20|0x40)); }
static inline int isalnum(int __c) { return !!(__walibc_char_masks[__c+1] & (0x08|0x20|0x40)); }
static inline int isgraph(int __c) { return !!(__walibc_char_masks[__c+1] & (0x08|0x20|0x40|0x04)); }
static inline int toupper(int __c) { return __c - ((__walibc_char_masks[__c+1] & 0x40) >> 1); }
static inline int tolower(int __c) { return __c + (__walibc_char_masks[__c+1] & 0x20); }
static inline int isblank(int __c) { return __c == 0x20 || __c == 0x09; }

__WALIBC_END_EXTERN;
