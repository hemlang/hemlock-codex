use std::sync::mpsc;
use std::thread;

fn main() {
    let (gen_tx, gen_rx) = mpsc::channel::<i32>();
    let (dbl_tx, dbl_rx) = mpsc::channel::<i32>();
    let (add_tx, add_rx) = mpsc::channel::<i32>();

    // Stage 1: generate
    let t1 = thread::spawn(move || {
        for i in 1..=5 { gen_tx.send(i).unwrap(); }
    });

    // Stage 2: double
    let t2 = thread::spawn(move || {
        for val in gen_rx { dbl_tx.send(val * 2).unwrap(); }
    });

    // Stage 3: add10
    let t3 = thread::spawn(move || {
        for val in dbl_rx { add_tx.send(val + 10).unwrap(); }
    });

    let mut results: Vec<i32> = add_rx.into_iter().collect();
    t1.join().unwrap(); t2.join().unwrap(); t3.join().unwrap();

    let s: Vec<String> = results.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
