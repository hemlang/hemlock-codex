fn insertion_sort(arr: &mut Vec<i32>) {
    let n = arr.len();
    for i in 1..n {
        let key = arr[i];
        let mut j = i as i64 - 1;
        while j >= 0 && arr[j as usize] > key {
            arr[(j + 1) as usize] = arr[j as usize];
            j -= 1;
        }
        arr[(j + 1) as usize] = key;
    }
}

fn main() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
    insertion_sort(&mut arr);
    let s: Vec<String> = arr.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
