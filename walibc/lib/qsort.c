#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static void swap(uint8_t *a, uint8_t *b, size_t n) {
    do { uint8_t t = *a; *a++ = *b; *b++ = t; } while (--n);
}

void __walibc_qsort_r(
    void *basep, size_t len, size_t elemsz,
    int (*cmp)(void const *, void const *, void *),
    void *this
) {
    enum { kStack = 128 };
    uint8_t *base = (uint8_t *)basep;
    uint8_t *lim = base + len * elemsz;
    uint8_t *stack[kStack], **sptr = stack;

    for (;;) {
        if ((size_t)(lim - base) > 7 * elemsz) {
            size_t p = ((size_t)(lim - base) / elemsz) / 2;
            swap(p * elemsz + base, base, elemsz);

            uint8_t *i = base + elemsz;
            uint8_t *j = lim - elemsz;

            if (cmp(i, j, this) > 0) swap(i, j, elemsz);
            if (cmp(base, j, this) > 0) swap(base, j, elemsz);
            if (cmp(i, base, this) > 0) swap(i, base, elemsz);

            for (;;) {
                do i += elemsz; while (cmp(i, base, this) < 0);
                do j -= elemsz; while (cmp(j, base, this) > 0);

                if (i > j) break;
                swap(i, j, elemsz);
            }

            swap(base, j, elemsz);

            if (sptr + 2 >= stack + kStack) abort();
            if (j - base > lim - i) {
                *sptr++ = base;
                *sptr++ = j;
                base = i;
            } else {
                *sptr++ = i;
                *sptr++ = lim;
                lim = j;
            }
        } else {
            for (uint8_t *j = base, *i = j + elemsz; i < lim; j = i, i += elemsz) {
                for (; cmp(j, j + elemsz, this) > 0; j -= elemsz) {
                    swap(j, j + elemsz, elemsz);
                    if (j == base) break;
                }
            }

            if (sptr == stack) break;
            lim = *--sptr;
            base = *--sptr;
        }
    }
}

static cmpshim(void const *a, void const *b, void *cmp) {
    typedef int (*SelflessCmpF)(void const *, void const *);
    return ((SelflessCmpF)cmp)(a, b);
}

void __walibc_qsort(
    void *basep, size_t len, size_t elemsz,
    int (*cmp)(void const *, void const *)
) {
    __walibc_qsort_r(basep, len, elemsz, cmpshim, (void*)cmp);
}
