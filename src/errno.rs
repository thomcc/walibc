use core::cell::UnsafeCell;
use core::ffi::c_int;

#[no_mangle]
pub unsafe extern "C" fn __walibc_errno() -> *mut c_int {
    std::thread_local! {
        static ERRNO: UnsafeCell<c_int> = const { UnsafeCell::new(0) };
    }
    ERRNO.with(|v| v.get())
}
