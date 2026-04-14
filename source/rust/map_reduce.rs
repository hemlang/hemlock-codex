use std::thread;

fn main() {
    let data = vec![1i32, 2, 3, 4, 5, 6, 7, 8];
    let chunks: Vec<Vec<i32>> = data.chunks(2).map(|c| c.to_vec()).collect();

    // Map phase
    let map_handles: Vec<_> = chunks.into_iter().map(|chunk| {
        thread::spawn(move || chunk.iter().map(|&x| x * x).collect::<Vec<i32>>())
    }).collect();

    let all_squares: Vec<i32> = map_handles.into_iter()
        .flat_map(|h| h.join().unwrap())
        .collect();

    // Reduce phase
    let reduce_handle = thread::spawn(move || all_squares.iter().sum::<i32>());
    let total = reduce_handle.join().unwrap();

    println!("sum of squares: {}", total);
}
