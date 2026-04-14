use std::alloc::{alloc, dealloc, Layout};

struct DynArray {
    data: *mut i32,
    size: usize,
    capacity: usize,
}

impl DynArray {
    fn new(capacity: usize) -> Self {
        let layout = Layout::array::<i32>(capacity).unwrap();
        let data = unsafe { alloc(layout) as *mut i32 };
        DynArray { data, size: 0, capacity }
    }

    fn grow(&mut self) {
        let new_cap = self.capacity * 2;
        let new_layout = Layout::array::<i32>(new_cap).unwrap();
        let new_data = unsafe { alloc(new_layout) as *mut i32 };
        unsafe {
            std::ptr::copy_nonoverlapping(self.data, new_data, self.size);
            dealloc(self.data as *mut u8, Layout::array::<i32>(self.capacity).unwrap());
        }
        self.data = new_data;
        self.capacity = new_cap;
    }

    fn push(&mut self, val: i32) {
        if self.size == self.capacity { self.grow(); }
        unsafe { *self.data.add(self.size) = val; }
        self.size += 1;
    }

    fn print_all(&self) {
        let mut parts = Vec::new();
        for i in 0..self.size {
            parts.push(unsafe { *self.data.add(i) }.to_string());
        }
        println!("values: {}", parts.join(" "));
    }
}

impl Drop for DynArray {
    fn drop(&mut self) {
        unsafe { dealloc(self.data as *mut u8, Layout::array::<i32>(self.capacity).unwrap()); }
    }
}

fn main() {
    let mut arr = DynArray::new(4);
    for i in 1..=10 {
        arr.push(i);
    }
    println!("capacity: {}", arr.capacity);
    arr.print_all();
}
