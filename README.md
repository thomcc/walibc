# `walibc`: A libc for "bare metal wasm" targets.

> [!NOTE]
>
> `walibc` is currently incomplete, not yet usable, and not accepting outside contributions (for the time being).

The goal of this library is to allow Rust code that targets `wasm32-unknown-unknown` (for example) to be able to use Rust crates that bundle C libraries. These targets are effectively bare-metal, and don't come with their own C library, even things like `memcpy` are unavailable (because `string.h` doesn't exist). Unfortunately, they're also widely used, as they don't require installing a separate SDK (such as the WASI SDK, or the Emscripten SDK). `walibc` exists to fill that gap.

This wouldn't be seamless (the C library bundler would have to add a build dep on `walibc`), but it would allow things like (for example) libsqlite3-sys to avoid the need to carry it's own implementation of libc functions.

Currently, it's essentially a header-only subset-of-libc. There aren't an abundance of good reasons for this, but the basic one is it lets us avoid linker issues if two distinct copies of `walibc` are used in a single build with no coordination. A better solution here is leverage cargo to solve this problem for ourselves.

That said, making most functions inline goes part of the way towards addressing how naïve many of our function implementations are.

## Non-goals
- Supporting non-Clang compilers.
- Supporting non-wasm targets.
- Supporting non-Rust use, for now.

## License
Public domain, as explained by [the Unlicense](./UNLICENSE). Failing that, the typical Rusty combo of Apache-2.0 or MIT is available.

Portions of `walibc` were ported from [pdclib](https://github.com/DevSolar/pdclib), which is also public domain.
