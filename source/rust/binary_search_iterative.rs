fn binary_search(arr: &[i32], target: i32) -> Option<usize> {
    let mut low = 0i64;
    let mut high = arr.len() as i64 - 1;
    while low <= high {
        let mid = low + (high - low) / 2;
        if arr[mid as usize] == target {
            return Some(mid as usize);
        } else if arr[mid as usize] < target {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    None
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
