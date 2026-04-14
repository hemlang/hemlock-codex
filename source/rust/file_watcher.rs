use std::fs;
use std::time::{SystemTime, UNIX_EPOCH};

fn time_ms() -> u64 {
    SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_millis() as u64
}

fn main() {
    let watch_path = "/tmp/rust_watch_test.txt";

    fs::write(watch_path, "initial content").unwrap();
    let t1 = time_ms();
    println!("[watcher] monitoring: {}", watch_path);
    println!("[watcher] initial write at t={}", t1);

    let initial = fs::read_to_string(watch_path).unwrap();
    println!("[watcher] initial content: {}", initial);

    fs::write(watch_path, "modified content").unwrap();
    let t2 = time_ms();
    println!("[watcher] file modified at t={}", t2);

    let content = fs::read_to_string(watch_path).unwrap();
    if content == "modified content" {
        println!("[watcher] file change detected");
        println!("[watcher] new content: {}", content);
    } else {
        println!("[watcher] no change detected");
    }

    if t2 > t1 {
        println!("[watcher] modification time advanced");
    }

    println!("[watcher] done");
}
