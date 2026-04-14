fn binary_search_rec(arr: &[i32], target: i32, low: i64, high: i64) -> Option<usize> {
    if low > high { return None; }
    let mid = low + (high - low) / 2;
    if arr[mid as usize] == target {
        Some(mid as usize)
    } else if arr[mid as usize] < target {
        binary_search_rec(arr, target, mid + 1, high)
    } else {
        binary_search_rec(arr, target, low, mid - 1)
    }
}

fn binary_search(arr: &[i32], target: i32) -> Option<usize> {
    binary_search_rec(arr, target, 0, arr.len() as i64 - 1)
}

fn main() {
    let arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];
    match binary_search(&arr, 23) {
        Some(i) => println!("search 23: found at index {}", i),
        None => println!("search 23: not found"),
    }
    match binary_search(&arr, 50) {
        Some(i) => println!("search 50: found at index {}", i),
        None => println!("search 50: not found"),
    }
}
