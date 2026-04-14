fn selection_sort(arr: &mut Vec<i32>) {
    let n = arr.len();
    for i in 0..n - 1 {
        let mut min_idx = i;
        for j in i + 1..n {
            if arr[j] < arr[min_idx] {
                min_idx = j;
            }
        }
        if min_idx != i {
            arr.swap(i, min_idx);
        }
    }
}

fn main() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
    selection_sort(&mut arr);
    let s: Vec<String> = arr.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
