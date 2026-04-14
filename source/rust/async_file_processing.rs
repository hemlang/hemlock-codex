use std::thread;

fn process_file(name: &str, data: &[i32]) -> (String, i32, i32, usize) {
    let sum: i32 = data.iter().sum();
    let max = *data.iter().max().unwrap();
    (name.to_string(), sum, max, data.len())
}

fn main() {
    let files: Vec<(&str, Vec<i32>)> = vec![
        ("data_a.csv", vec![10, 20, 30, 40, 50]),
        ("data_b.csv", vec![5, 15, 25, 35, 45, 55]),
        ("data_c.csv", vec![100, 200, 300]),
    ];

    let handles: Vec<_> = files.into_iter().map(|(name, data)| {
        thread::spawn(move || process_file(&name, &data))
    }).collect();

    let results: Vec<_> = handles.into_iter().map(|h| h.join().unwrap()).collect();

    for (name, sum, max, count) in &results {
        println!("{}: sum={} max={} count={}", name, sum, max, count);
    }
    println!("all files processed");
}
