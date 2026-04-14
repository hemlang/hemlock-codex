use std::sync::{Arc, Mutex, mpsc};
use std::thread;

fn main() {
    let num_producers = 3;
    let items_per_producer = 5;
    let total_items = num_producers * items_per_producer;

    let (tx, rx) = mpsc::channel::<String>();
    let results = Arc::new(Mutex::new(Vec::new()));
    let results_c = Arc::clone(&results);

    // Start consumer
    let consumer = thread::spawn(move || {
        let mut received = Vec::new();
        for _ in 0..total_items {
            received.push(rx.recv().unwrap());
        }
        *results_c.lock().unwrap() = received;
    });

    // Start producers
    let mut producers = Vec::new();
    for id in 0..num_producers {
        let tx = tx.clone();
        producers.push(thread::spawn(move || {
            for i in 0..items_per_producer {
                tx.send(format!("p{}-{}", id, i)).unwrap();
            }
        }));
    }

    for p in producers { p.join().unwrap(); }
    consumer.join().unwrap();

    let mut res = results.lock().unwrap().clone();
    println!("consumed {} items", res.len());
    res.sort();
    println!("values: {}", res.join(" "));
}
