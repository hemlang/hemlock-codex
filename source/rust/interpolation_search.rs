fn interpolation_search(arr: &[i32], target: i32) -> Option<usize> {
    let mut low = 0i64;
    let mut high = arr.len() as i64 - 1;
    while low <= high && target >= arr[low as usize] && target <= arr[high as usize] {
        if low == high {
            if arr[low as usize] == target { return Some(low as usize); }
            return None;
        }
        let range = arr[high as usize] - arr[low as usize];
        let pos = low + ((target - arr[low as usize]) as i64 * (high - low)) / range as i64;
        if arr[pos as usize] == target {
            return Some(pos as usize);
        } else if arr[pos as usize] < target {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    None
}

fn main() {
    let arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];
    match interpolation_search(&arr, 23) {
        Some(i) => println!("search 23: found at index {}", i),
        None => println!("search 23: not found"),
    }
    match interpolation_search(&arr, 50) {
        Some(i) => println!("search 50: found at index {}", i),
        None => println!("search 50: not found"),
    }
}
