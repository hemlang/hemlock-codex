use std::alloc::{alloc, dealloc, Layout};

const NODE_SIZE: usize = 24;

unsafe fn make_node(val: i32) -> *mut u8 {
    let layout = Layout::from_size_align(NODE_SIZE, 8).unwrap();
    let node = alloc(layout);
    *(node as *mut i32) = val;
    // Zero prev and next
    *(node.add(8) as *mut u64) = 0;
    *(node.add(16) as *mut u64) = 0;
    node
}

unsafe fn node_val(node: *mut u8) -> i32 { *(node as *const i32) }

unsafe fn get_prev(node: *mut u8) -> *mut u8 {
    let raw = *(node.add(8) as *const u64);
    if raw == 0 { std::ptr::null_mut() } else { raw as *mut u8 }
}

unsafe fn set_prev(node: *mut u8, prev: *mut u8) {
    *(node.add(8) as *mut u64) = prev as u64;
}

unsafe fn get_next(node: *mut u8) -> *mut u8 {
    let raw = *(node.add(16) as *const u64);
    if raw == 0 { std::ptr::null_mut() } else { raw as *mut u8 }
}

unsafe fn set_next(node: *mut u8, nxt: *mut u8) {
    *(node.add(16) as *mut u64) = nxt as u64;
}

struct Deque {
    head: *mut u8,
    tail: *mut u8,
    size: usize,
}

impl Deque {
    fn new() -> Self { Deque { head: std::ptr::null_mut(), tail: std::ptr::null_mut(), size: 0 } }

    fn push_front(&mut self, val: i32) {
        unsafe {
            let node = make_node(val);
            if self.head.is_null() {
                self.head = node; self.tail = node;
            } else {
                set_next(node, self.head);
                set_prev(self.head, node);
                self.head = node;
            }
            self.size += 1;
        }
        println!("push_front: {}", val);
    }

    fn push_back(&mut self, val: i32) {
        unsafe {
            let node = make_node(val);
            if self.tail.is_null() {
                self.head = node; self.tail = node;
            } else {
                set_prev(node, self.tail);
                set_next(self.tail, node);
                self.tail = node;
            }
            self.size += 1;
        }
        println!("push_back: {}", val);
    }

    fn pop_front(&mut self) {
        if self.head.is_null() { println!("deque empty"); return; }
        unsafe {
            let node = self.head;
            let val = node_val(node);
            let nxt = get_next(node);
            if !nxt.is_null() { set_prev(nxt, std::ptr::null_mut()); } else { self.tail = std::ptr::null_mut(); }
            self.head = nxt;
            dealloc(node, Layout::from_size_align(NODE_SIZE, 8).unwrap());
            self.size -= 1;
            println!("pop_front: {}", val);
        }
    }

    fn pop_back(&mut self) {
        if self.tail.is_null() { println!("deque empty"); return; }
        unsafe {
            let node = self.tail;
            let val = node_val(node);
            let prv = get_prev(node);
            if !prv.is_null() { set_next(prv, std::ptr::null_mut()); } else { self.head = std::ptr::null_mut(); }
            self.tail = prv;
            dealloc(node, Layout::from_size_align(NODE_SIZE, 8).unwrap());
            self.size -= 1;
            println!("pop_back: {}", val);
        }
    }

    fn print_deque(&self) {
        unsafe {
            let mut parts = Vec::new();
            let mut cur = self.head;
            while !cur.is_null() {
                parts.push(node_val(cur).to_string());
                cur = get_next(cur);
            }
            println!("deque: {}", parts.join(" "));
        }
    }
}

fn main() {
    let mut dq = Deque::new();
    dq.push_front(1);
    dq.push_front(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.print_deque();
    println!("size: {}", dq.size);
    dq.pop_front();
    dq.pop_back();
    dq.print_deque();
    println!("size: {}", dq.size);
    while !dq.head.is_null() { dq.pop_front(); }
    println!("deque cleared");
}
