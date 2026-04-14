use std::thread;

fn merge(left: Vec<i32>, right: Vec<i32>) -> Vec<i32> {
    let mut result = Vec::new();
    let mut i = 0; let mut j = 0;
    while i < left.len() && j < right.len() {
        if left[i] <= right[j] { result.push(left[i]); i += 1; }
        else { result.push(right[j]); j += 1; }
    }
    result.extend_from_slice(&left[i..]);
    result.extend_from_slice(&right[j..]);
    result
}

fn merge_sort(arr: Vec<i32>) -> Vec<i32> {
    if arr.len() <= 1 { return arr; }
    let mid = arr.len() / 2;
    let left_arr = arr[..mid].to_vec();
    let right_arr = arr[mid..].to_vec();
    let left_thread = thread::spawn(move || merge_sort(left_arr));
    let right_thread = thread::spawn(move || merge_sort(right_arr));
    let sorted_left = left_thread.join().unwrap();
    let sorted_right = right_thread.join().unwrap();
    merge(sorted_left, sorted_right)
}

fn main() {
    let arr = vec![38, 27, 43, 3, 9, 82, 10, 55];
    let sorted = merge_sort(arr);
    let s: Vec<String> = sorted.iter().map(|x| x.to_string()).collect();
    println!("sorted: {}", s.join(" "));
}
