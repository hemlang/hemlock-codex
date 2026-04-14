use std::sync::mpsc;
use std::thread;

fn main() {
    let (work_tx, work_rx) = mpsc::channel::<i32>();
    let work_rx = std::sync::Arc::new(std::sync::Mutex::new(work_rx));
    let (result_tx, result_rx) = mpsc::channel::<i32>();

    for i in 1..=20 {
        work_tx.send(i).unwrap();
    }
    drop(work_tx);

    let mut workers = Vec::new();
    for _ in 0..4 {
        let rx = work_rx.clone();
        let tx = result_tx.clone();
        workers.push(thread::spawn(move || {
            loop {
                let val = { rx.lock().unwrap().recv() };
                match val {
                    Ok(v) => tx.send(v * v).unwrap(),
                    Err(_) => break,
                }
            }
        }));
    }
    drop(result_tx);

    for w in workers { w.join().unwrap(); }

    let mut results: Vec<i32> = result_rx.into_iter().collect();
    results.sort();
    let s: Vec<String> = results.iter().map(|x| x.to_string()).collect();
    println!("results: {}", s.join(" "));
}
