use std::alloc::{alloc, dealloc, Layout};

fn cleanup() {
    println!("resource cleaned up");
}

fn risky_operation() -> Result<(), String> {
    let layout = Layout::from_size_align(64, 8).unwrap();
    let _p = unsafe { alloc(layout) };
    // Simulate defer: cleanup runs on return
    let result = Err("something went wrong".to_string());
    cleanup();
    unsafe { dealloc(_p, layout); }
    result
}

fn main() {
    match risky_operation() {
        Err(_) => println!("error handled"),
        Ok(_) => {}
    }
}
