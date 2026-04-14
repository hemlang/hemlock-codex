use std::alloc::{alloc, dealloc, Layout};

fn main() {
    let layout = Layout::from_size_align(8, 4).unwrap();
    unsafe {
        let a = alloc(layout);
        let b = alloc(layout);
        let c = alloc(layout);

        *(a as *mut i32) = 10;
        *(b as *mut i32) = 20;
        *(c as *mut i32) = 30;

        let va = *(a as *const i32);
        let vb = *(b as *const i32);
        let vc = *(c as *const i32);

        println!("{} {} {}", va, vb, vc);
        println!("all memory freed");

        dealloc(a, layout);
        dealloc(b, layout);
        dealloc(c, layout);
    }
}
