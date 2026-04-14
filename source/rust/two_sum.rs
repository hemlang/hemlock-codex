use std::collections::HashMap;

fn two_sum(nums: &[i32], target: i32) -> Option<(usize, usize)> {
    let mut map: HashMap<i32, usize> = HashMap::new();
    for (i, &x) in nums.iter().enumerate() {
        let complement = target - x;
        if let Some(&j) = map.get(&complement) {
            return Some((j, i));
        }
        map.insert(x, i);
    }
    None
}

fn main() {
    let nums = [2, 7, 11, 15];
    if let Some((a, b)) = two_sum(&nums, 9) {
        println!("indices: {}, {}", a, b);
    }
}
