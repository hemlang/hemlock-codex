fn counting_sort_by_digit(arr: &mut Vec<i32>, exp: i32) {
    let n = arr.len();
    let mut output = vec![0i32; n];
    let mut count = vec![0usize; 10];

    for &x in arr.iter() {
        let digit = ((x / exp) % 10) as usize;
        count[digit] += 1;
    }
    for i in 1..10 {
        count[i] += count[i - 1];
    }
    for i in (0..n).rev() {
        let digit = ((arr[i] / exp) % 10) as usize;
        count[digit] -= 1;
        output[count[digit]] = arr[i];
    }
    arr.copy_from_slice(&output);
}

fn radix_sort(arr: &mut Vec<i32>) {
    if arr.is_empty() { return; }
    let max_val = *arr.iter().max().unwrap();
    let mut exp = 1;
    while max_val / exp > 0 {
        counting_sort_by_digit(arr, exp);
        exp *= 10;
    }
}

fn main() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
    radix_sort(&mut arr);
    let s: Vec<String> = arr.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
