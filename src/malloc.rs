//! Implementation of `malloc`-family functions (forwards to Rust global
//! allocator). These don't have the correct name (they're prefixed with
//! `__walibc_`), but are wrapped by inline functions in our `stdlib.h`, which
//! simplifies some aspects of development (this is easier to test, since things
//! dislike it when we override the global malloc/free in this manner).
use core::{
    alloc::Layout,
    ffi::{c_int, c_void},
    mem::size_of,
    ptr::null_mut,
};

use std::alloc;
// Matches `__BIGGEST_ALIGNMENT__` in output of
// `clang -dM -E -target wasm32-unknown-unknown`
const DEFAULT_ALIGN: usize = 16;

// Note: The extra fields only cost anything on wasm64, on wasm32 they'd be
// padding -- all our allocations are aligned to 16, and `layout` is 8 bytes on
// 32bit targets.
#[derive(Copy, Clone)]
struct AllocHeader {
    // Layout to pass to free
    layout: Layout,
    // Pointer to free. TODO: shouldn't be necessary.
    ptr: *mut u8,
    // Actual size available, for realloc (and now for malloc_usable_size too).
    // TODO: shouldn't be necessary (for either case).
    usable_size: usize,
}

// shared code between malloc and calloc
unsafe fn do_alloc(
    sz: usize,
    align: usize,
    allocator: unsafe fn(Layout) -> *mut u8,
) -> *mut c_void {
    // Ensure no zero-sized alloc.
    let sz = sz.max(1);
    let align = align.max(DEFAULT_ALIGN);
    // Compute a layout sufficient to store `AllocHeader`
    // immediately before it.
    let header_layout = Layout::new::<AllocHeader>();
    let Ok(requested_layout) = Layout::from_size_align(sz, align) else {
        return null_mut();
    };
    let requested_layout = requested_layout.pad_to_align(); // Hmm...
    let Ok((to_request, offset)) = header_layout.extend(requested_layout) else {
        return null_mut();
    };
    let to_request = to_request.pad_to_align(); // Hmm...

    let orig_ptr = allocator(to_request);
    if orig_ptr.is_null() {
        return null_mut();
    }

    let result_ptr = orig_ptr.add(offset);
    // Write `AllocHeader` immediately prior to the pointer we return.
    // This way, we always know where to get it for passing to
    // `alloc::dealloc`.
    let info_ptr = result_ptr
        .sub(size_of::<AllocHeader>())
        .cast::<AllocHeader>();
    // This actually should be aligned in almost every case, but it's hard to
    // guarantee and unaligned read/write is very cheap anyway.
    info_ptr.write_unaligned(AllocHeader {
        layout: to_request,
        ptr: orig_ptr,
        usable_size: to_request.size() - offset,
    });
    result_ptr.cast::<c_void>()
}

#[no_mangle]
pub unsafe extern "C" fn __walibc_malloc(sz: usize) -> *mut c_void {
    do_alloc(sz, DEFAULT_ALIGN, alloc::alloc)
}

#[no_mangle]
pub unsafe extern "C" fn __walibc_calloc(cnt: usize, sz: usize) -> *mut c_void {
    let Some(total) = sz.checked_mul(cnt) else {
        return null_mut();
    };
    do_alloc(total, DEFAULT_ALIGN, alloc::alloc_zeroed)
}

#[no_mangle]
pub unsafe extern "C" fn __walibc_free(ptr: *mut c_void) {
    // Ignore `free(NULL)`
    if ptr.is_null() {
        return;
    }
    // Read the AllocHeader, and pass the info it contains to dealloc.
    let info_ptr = ptr.sub(size_of::<AllocHeader>()).cast::<AllocHeader>();
    let info = info_ptr.read_unaligned();
    alloc::dealloc(info.ptr, info.layout);
}

#[no_mangle]
pub unsafe extern "C" fn __walibc_realloc(ptr: *mut c_void, new_size: usize) -> *mut c_void {
    //  `realloc(ptr, 0)` is the same as `free` (common extension).
    if new_size == 0 {
        __walibc_free(ptr);
        return core::ptr::null_mut();
    }
    // `realloc(NULL, sz)` is the same as `malloc(sz)`.
    if ptr.is_null() {
        return __walibc_malloc(new_size);
    }
    let info_ptr = ptr.sub(size_of::<AllocHeader>()).cast::<AllocHeader>();
    let old_info = info_ptr.read_unaligned();
    let old_size_without_header = old_info.usable_size;
    if new_size <= old_size_without_header {
        // Either we're being shrunk, or grown within our bounds. Either way we
        // don't need to do anything.
        return ptr;
    }
    // Allocate a new block and copy the data over.
    // TODO: use `alloc::realloc` instead.
    let new = do_alloc(
        old_size_without_header,
        // Preserve the old alignment, this may have been allocated with
        // `posix_memalign`.
        old_info.layout.align(),
        alloc::alloc,
    );
    if new.is_null() {
        return null_mut();
    }
    new.cast::<u8>()
        .copy_from_nonoverlapping(ptr.cast::<u8>(), old_size_without_header);
    // Free the old pointer
    alloc::dealloc(old_info.ptr, old_info.layout);
    new
}

#[no_mangle]
pub unsafe extern "C" fn __walibc_posix_memalign(
    out: *mut *mut c_void,
    align: usize,
    sz: usize,
) -> c_int {
    let p = do_alloc(sz, align, alloc::alloc);
    out.write(p);
    // TODO: look up what posix_memalign is actually supposed to return
    if out.is_null() {
        // Probably should be setting `errno` too (we don't have an `errno`).
        // Actually all of these should set errno, shouldn't they...
        -1
    } else {
        0
    }
}

// C11
#[no_mangle]
pub unsafe extern "C" fn __walibc_aligned_alloc(align: usize, sz: usize) -> *mut c_void {
    do_alloc(sz, align, alloc::alloc)
}

#[no_mangle]
pub unsafe extern "C" fn __walibc_malloc_usable_size(p: *mut c_void) -> usize {
    if p.is_null() {
        return 0;
    }
    let info_ptr = p.sub(size_of::<AllocHeader>()).cast::<AllocHeader>();
    let old_info = info_ptr.read_unaligned();
    old_info.usable_size
}
