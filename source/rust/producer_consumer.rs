use std::sync::mpsc;
use std::thread;

fn main() {
    let (tx, rx) = mpsc::channel();

    let producer = thread::spawn(move || {
        for i in 1..=10 {
            tx.send(i).unwrap();
        }
    });

    let consumer = thread::spawn(move || {
        let mut results = Vec::new();
        for val in rx {
            results.push(val);
        }
        results
    });

    producer.join().unwrap();
    let results: Vec<i32> = consumer.join().unwrap();
    let s: Vec<String> = results.iter().map(|x| x.to_string()).collect();
    println!("received: {}", s.join(" "));
}
