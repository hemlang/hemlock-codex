fn permute(arr: &mut Vec<char>, start: usize, results: &mut Vec<String>) {
    if start == arr.len() - 1 {
        results.push(arr.iter().collect());
        return;
    }
    for i in start..arr.len() {
        arr.swap(start, i);
        permute(arr, start + 1, results);
        arr.swap(start, i);
    }
}

fn main() {
    let mut chars: Vec<char> = "abc".chars().collect();
    let mut results = Vec::new();
    permute(&mut chars, 0, &mut results);
    for p in &results {
        println!("{}", p);
    }
}
