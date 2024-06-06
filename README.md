# `walibc`: A libc for "bare metal wasm" targets.

> [!NOTE]
>
> `walibc` is currently incomplete, not yet usable, and not accepting outside contributions (for the time being).

The goal of this library is to allow Rust code that targets `wasm32-unknown-unknown` (for example) to be able to use Rust crates that bundle C libraries. These targets are effectively bare-metal, and don't come with their own C library, even things like `memcpy` are unavailable (because `string.h` doesn't exist). Unfortunately, they're also widely used, as they don't require installing a separate SDK (such as the WASI SDK, or the Emscripten SDK). `walibc` exists to fill that gap.

This wouldn't be seamless (the C library bundler would have to add a build dep on `walibc`), but it would allow things like (for example) libsqlite3-sys to avoid the need to carry it's own implementation of libc functions.

Currently, it's essentially a nearly-header-only subset-of-libc; almost everything is defined as `static inline`. There aren't an abundance of good reasons for it being header only, but the basic one is it lets us avoid linker issues if two distinct copies of `walibc` are used in a single build with no coordination. There are a few other workflow-related reasons too -- this better avoids symbol collisions in some cases.

And not for nothing, making most functions inline goes part of the way towards addressing how naïve many of our function implementations are.

## Non-goals
- Supporting non-Clang compilers.
- Supporting non-wasm targets.
- Supporting non-Rust use, for now.

## License
MIT. While most of `walibc` was written fresh, portions are taken from other places, all of which are either public domain, or MIT licensed themselves:

- Portions of `walibc` were ported from [pdclib](https://github.com/DevSolar/pdclib), which is public domain.
- The implementation of the `vsnprintf`-family of functions is taken from [`stb_sprintf`](https://github.com/nothings/stb/blob/013ac3beddff3dbffafd5177e7972067cd2b5083/stb_sprintf.h) (with some modifications), which is public also domain.
- Portions of `walibc` are based on code from [musl](https://musl.libc.org/), which is also [MIT licensed](https://git.musl-libc.org/cgit/musl/tree/COPYRIGHT?h=v1.2.5).
