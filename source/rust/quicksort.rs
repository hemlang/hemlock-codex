fn quicksort(arr: &mut Vec<i32>, low: usize, high: usize) {
    if low < high {
        let pivot = arr[high];
        let mut i = low as i64 - 1;
        for j in low..high {
            if arr[j] <= pivot {
                i += 1;
                arr.swap(i as usize, j);
            }
        }
        let pi = (i + 1) as usize;
        arr.swap(pi, high);
        if pi > 0 {
            quicksort(arr, low, pi - 1);
        }
        quicksort(arr, pi + 1, high);
    }
}

fn main() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
    let n = arr.len();
    quicksort(&mut arr, 0, n - 1);
    let s: Vec<String> = arr.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
