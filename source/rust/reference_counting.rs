use std::alloc::{alloc, dealloc, Layout};

const OBJ_SIZE: usize = 8;

unsafe fn rc_new(data: i32) -> *mut u8 {
    let layout = Layout::from_size_align(OBJ_SIZE, 4).unwrap();
    let obj = alloc(layout);
    *(obj as *mut i32) = 1; // refcount
    *(obj.add(4) as *mut i32) = data;
    println!("created obj(data={}, refcount=1)", data);
    obj
}

unsafe fn rc_retain(obj: *mut u8) -> *mut u8 {
    let rc = *(obj as *const i32) + 1;
    *(obj as *mut i32) = rc;
    let data = *(obj.add(4) as *const i32);
    println!("retain obj(data={}, refcount={})", data, rc);
    obj
}

unsafe fn rc_release(obj: *mut u8) -> *mut u8 {
    let rc = *(obj as *const i32) - 1;
    let data = *(obj.add(4) as *const i32);
    if rc == 0 {
        println!("release obj(data={}, refcount=0) -> freed", data);
        dealloc(obj, Layout::from_size_align(OBJ_SIZE, 4).unwrap());
        return std::ptr::null_mut();
    }
    *(obj as *mut i32) = rc;
    println!("release obj(data={}, refcount={})", data, rc);
    obj
}

unsafe fn rc_get_data(obj: *mut u8) -> i32 { *(obj.add(4) as *const i32) }
unsafe fn rc_get_count(obj: *mut u8) -> i32 { *(obj as *const i32) }

fn main() {
    unsafe {
        println!("--- create object ---");
        let a = rc_new(42);
        println!("--- share with b ---");
        let b = rc_retain(a);
        println!("--- share with c ---");
        let c = rc_retain(a);
        println!("data: {}, refcount: {}", rc_get_data(a), rc_get_count(a));
        println!("--- release a ---");
        let _a = rc_release(a);
        println!("--- release b ---");
        let _b = rc_release(b);
        println!("--- release c (last ref, should free) ---");
        let _c = rc_release(c);
    }
}
