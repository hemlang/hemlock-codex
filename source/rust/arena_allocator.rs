use std::alloc::{alloc, dealloc, Layout};

struct Arena {
    data: *mut u8,
    offset: usize,
    size: usize,
}

impl Arena {
    fn new(size: usize) -> Self {
        let layout = Layout::from_size_align(size, 8).unwrap();
        let data = unsafe { alloc(layout) };
        Arena { data, offset: 0, size }
    }

    fn alloc(&mut self, bytes: usize) -> Option<*mut u8> {
        if self.offset + bytes > self.size {
            println!("arena out of memory!");
            return None;
        }
        let p = unsafe { self.data.add(self.offset) };
        self.offset += bytes;
        Some(p)
    }

    fn reset(&mut self) { self.offset = 0; }
}

impl Drop for Arena {
    fn drop(&mut self) {
        unsafe { dealloc(self.data, Layout::from_size_align(self.size, 8).unwrap()); }
    }
}

fn main() {
    let mut arena = Arena::new(1024);
    let slots: Vec<*mut u8> = (0..5).map(|_| arena.alloc(4).unwrap()).collect();
    let vals = [100i32, 200, 300, 400, 500];
    for (i, &slot) in slots.iter().enumerate() {
        unsafe { *(slot as *mut i32) = vals[i]; }
    }
    for (i, &slot) in slots.iter().enumerate() {
        let v = unsafe { *(slot as *const i32) };
        println!("slot {}: {}", i, v);
    }
    println!("arena used: {} bytes", arena.offset);
    drop(arena);
    println!("arena freed");
}
