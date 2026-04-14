use std::sync::{Arc, Barrier};
use std::thread;

fn main() {
    let num_tasks = 4;
    let barrier = Arc::new(Barrier::new(num_tasks));
    let (tx, rx) = std::sync::mpsc::channel();

    let mut handles = Vec::new();
    for i in 0..num_tasks {
        let b = Arc::clone(&barrier);
        let tx = tx.clone();
        handles.push(thread::spawn(move || {
            b.wait();
            tx.send(i).unwrap();
        }));
    }
    drop(tx);

    for h in handles { h.join().unwrap(); }
    let count = rx.into_iter().count();
    println!("all {} tasks passed barrier", count);
}
