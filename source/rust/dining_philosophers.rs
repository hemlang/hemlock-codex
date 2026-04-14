use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let num_phil = 5;
    let forks: Vec<Arc<Mutex<()>>> = (0..num_phil).map(|_| Arc::new(Mutex::new(()))).collect();
    let (tx, rx) = std::sync::mpsc::channel();

    let mut handles = Vec::new();
    for id in 0..num_phil {
        let forks = forks.clone();
        let tx = tx.clone();
        handles.push(thread::spawn(move || {
            let left = id;
            let right = (id + 1) % num_phil;
            let (first, second) = if left < right { (left, right) } else { (right, left) };

            let _g1 = forks[first].lock().unwrap();
            let _g2 = forks[second].lock().unwrap();

            println!("philosopher {} is eating", id);

            tx.send(id).unwrap();
        }));
    }
    drop(tx);

    for h in handles { h.join().unwrap(); }
    let _: Vec<_> = rx.into_iter().collect();
    println!("all philosophers ate");
}
