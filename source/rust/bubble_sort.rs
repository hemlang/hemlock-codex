fn bubble_sort(arr: &mut Vec<i32>) {
    let n = arr.len();
    for i in 0..n - 1 {
        for j in 0..n - i - 1 {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
    }
}

fn main() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
    bubble_sort(&mut arr);
    let s: Vec<String> = arr.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
