//! Note: The definitions provided by the `walibc` Rust crate are intended to be
//! used only by the `walibc`` C code. They are public to ensure they aren't
//! removed despite not being used.
// Note: intentionally not `#![no_std]`
pub mod errno;
pub mod malloc;
