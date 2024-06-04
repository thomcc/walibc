#pragma once
#ifdef __has_include
# if __has_include(<__walibc_config.h>)
#  include <__walibc_config.h>
# endif
#endif

#ifdef __cplusplus
# define __WALIBC_BEGIN_EXTERN extern "C" { _Static_assert(1, "force semicolon")
# define __WALIBC_END_EXTERN } _Static_assert(1, "force semicolon")
# define __WALIBC_RESTRICT
#else
# define __WALIBC_BEGIN_EXTERN _Static_assert(1, "force semicolon")
# define __WALIBC_END_EXTERN _Static_assert(1, "force semicolon")
# define __WALIBC_RESTRICT restrict
#endif

#if defined(__wasm32) || defined(__wasm32__)
# define __WALIBC_BITS 32
# define __WALIBC_32BIT 1
#elif defined(__wasm64) || defined(__wasm64__)
// Completely untested
# define __WALIBC_BITS 64
# define __WALIBC_64BIT 1
#else
# ifndef WALIBC_YOLO_TARGET
#  error "`walibc` really only supports wasm{32,64}-unknown-unknown. Define `WALIBC_YOLO_TARGET` if you don't care."
# endif
#endif

#if defined( __cplusplus ) && __cplusplus >= 201103L
# define __WALIBC_NORETURN [[noreturn]]
#elif defined( __STDC_VERSION__ ) >= 201112L
# define __WALIBC_NORETURN _Noreturn
#else
# define __WALIBC_NORETURN
#endif

#if defined(__wasi__) && !defined(WALIBC_YOLO_TARGET)
# error "`walibc` isn't for WASI targets, since they can have a somewhat real libc"
#endif
#if defined(EMSCRIPTEN) && !defined(WALIBC_YOLO_TARGET)
# error "`walibc` isn't for emscripten targets, since they can have a somewhat real libc"
#endif

#if !defined(__clang__)
# error "only clang is supported"
#endif

#define __WALIBC_FORCEINLINE __attribute__((always_inline)) inline
