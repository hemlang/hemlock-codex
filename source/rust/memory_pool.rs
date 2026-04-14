use std::alloc::{alloc, dealloc, Layout};

const SLOT_SIZE: usize = 8;
const POOL_SLOTS: usize = 8;

struct Pool {
    data: *mut u8,
    used: [bool; POOL_SLOTS],
}

impl Pool {
    fn new() -> Self {
        let layout = Layout::from_size_align(SLOT_SIZE * POOL_SLOTS, 8).unwrap();
        let data = unsafe { alloc(layout) };
        Pool { data, used: [false; POOL_SLOTS] }
    }

    fn alloc_slot(&mut self) -> Option<(usize, *mut u8)> {
        for i in 0..POOL_SLOTS {
            if !self.used[i] {
                self.used[i] = true;
                println!("alloc slot {}", i);
                let ptr = unsafe { self.data.add(i * SLOT_SIZE) };
                return Some((i, ptr));
            }
        }
        println!("pool exhausted!");
        None
    }

    fn free_slot(&mut self, slot_index: usize) {
        if self.used[slot_index] {
            self.used[slot_index] = false;
            println!("freed slot {}", slot_index);
        }
    }

    fn active_count(&self) -> usize {
        self.used.iter().filter(|&&u| u).count()
    }
}

impl Drop for Pool {
    fn drop(&mut self) {
        unsafe { dealloc(self.data, Layout::from_size_align(SLOT_SIZE * POOL_SLOTS, 8).unwrap()); }
    }
}

fn main() {
    let mut pool = Pool::new();
    let (_, s0) = pool.alloc_slot().unwrap();
    let (_, s1) = pool.alloc_slot().unwrap();
    let (_, _s2) = pool.alloc_slot().unwrap();
    let (_, _s3) = pool.alloc_slot().unwrap();
    let (_, _s4) = pool.alloc_slot().unwrap();

    unsafe {
        *(s0 as *mut i64) = 100;
        *(s1 as *mut i64) = 200;
    }

    println!("active: {}", pool.active_count());
    pool.free_slot(1);
    pool.free_slot(3);
    println!("active after free: {}", pool.active_count());

    pool.alloc_slot();
    pool.alloc_slot();
    pool.alloc_slot();
    println!("final active: {}", pool.active_count());

    drop(pool);
    println!("pool freed");
}
