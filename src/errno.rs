use core::cell::UnsafeCell;
use core::ffi::c_int;

#[no_mangle]
pub unsafe extern "C" fn __walibc_errno() -> *mut c_int {
    std::thread_local! {
        static ERRNO: UnsafeCell<c_int> = const { UnsafeCell::new(0) };
    }
    ERRNO.with(|v| v.get())
}

pub(crate) fn set_errno(errc: c_int) {
    unsafe { __walibc_errno().write(errc) };
}

// pub(crate) fn get_errno() -> c_int {
//     unsafe { __walibc_errno().read() }
// }

// Populate this list with definitions that match our `errno.h` as needed.
pub(crate) const ENOMEM: c_int = 12;
pub(crate) const EINVAL: c_int = 22;
