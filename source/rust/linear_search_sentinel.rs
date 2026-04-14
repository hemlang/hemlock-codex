fn linear_search_sentinel(arr: &[i32], target: i32) -> Option<usize> {
    let n = arr.len();
    let mut v = arr.to_vec();
    let last = v[n - 1];
    v[n - 1] = target;
    let mut i = 0;
    while v[i] != target {
        i += 1;
    }
    v[n - 1] = last;
    if i < n - 1 {
        Some(i)
    } else if arr[n - 1] == target {
        Some(n - 1)
    } else {
        None
    }
}

fn main() {
    let arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];
    match linear_search_sentinel(&arr, 23) {
        Some(i) => println!("search 23: found at index {}", i),
        None => println!("search 23: not found"),
    }
    match linear_search_sentinel(&arr, 50) {
        Some(i) => println!("search 50: found at index {}", i),
        None => println!("search 50: not found"),
    }
}
