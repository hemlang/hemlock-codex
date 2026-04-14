use std::sync::{Arc, atomic::{AtomicI32, Ordering}};
use std::thread;

fn main() {
    let counter = Arc::new(AtomicI32::new(0));
    let num_tasks = 10;
    let iterations = 100;

    let mut handles = Vec::new();
    for _ in 0..num_tasks {
        let c = Arc::clone(&counter);
        handles.push(thread::spawn(move || {
            for _ in 0..iterations {
                c.fetch_add(1, Ordering::SeqCst);
            }
        }));
    }
    for h in handles { h.join().unwrap(); }
    println!("final: {}", counter.load(Ordering::SeqCst));
}
