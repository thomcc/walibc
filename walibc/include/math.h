#pragma once
#include <__walibc.h>
#include <__walibc_ints.h>
__WALIBC_BEGIN_EXTERN;

// These are defined in compiler-builtins, which (hopefully?) we can rely on and
// use (that is: we should ultimately be linked against it). This list is from
// https://github.com/rust-lang/compiler-builtins/blob/c04eb9e1a/src/math.rs

extern double acos(double);
extern double asin(double);
extern double cbrt(double);
extern double expm1(double);
extern double hypot(double, double);
extern double tan(double);
extern double cos(double);
extern float expf(float);
extern double log2(double);
extern float log2f(float);
extern double log10(double);
extern float log10f(float);
extern double log(double);
extern float logf(float);
extern double round(double);
extern float roundf(float);
extern double rint(double);
extern float rintf(float);
extern double sin(double);
extern double pow(double, double);
extern float powf(float, float);
extern float acosf(float);
extern float atan2f(float, float);
extern float atanf(float);
extern float coshf(float);
extern float expm1f(float);
extern double fdim(double, double);
extern float fdimf(float, float);
extern float log1pf(float);
extern float sinhf(float);
extern float tanhf(float);
extern double ldexp(double, int);
extern float ldexpf(float, int);
extern double tgamma(double);
extern float tgammaf(float);
extern double atan(double);
extern double atan2(double, double);
extern double cosh(double);
extern double log1p(double);
extern double sinh(double);
extern double tanh(double);
extern float cosf(float);
extern double exp(double);
extern float sinf(float);
extern double exp2(double);
extern float exp2f(float);
extern double fma(double, double, double);
extern float fmaf(float, float, float);
extern float asinf(float);
extern float cbrtf(float);
extern float hypotf(float, float);
extern float tanf(float);
extern float sqrtf(float);
extern double sqrt(double);
extern double ceil(double);
extern float ceilf(float);
extern double floor(double);
extern float floorf(float);
extern double trunc(double);
extern float truncf(float);
extern double fmin(double, double);
extern float fminf(float, float);
extern double fmax(double, double);
extern float fmaxf(float, float);
extern double fmod(double, double);
extern float fmodf(float, float);

__WALIBC_END_EXTERN;
