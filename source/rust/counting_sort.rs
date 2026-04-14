fn counting_sort(arr: &mut Vec<i32>) {
    if arr.is_empty() { return; }
    let max_val = *arr.iter().max().unwrap() as usize;
    let mut count = vec![0usize; max_val + 1];
    for &x in arr.iter() {
        count[x as usize] += 1;
    }
    let mut idx = 0;
    for i in 0..=max_val {
        while count[i] > 0 {
            arr[idx] = i as i32;
            idx += 1;
            count[i] -= 1;
        }
    }
}

fn main() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
    counting_sort(&mut arr);
    let s: Vec<String> = arr.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
