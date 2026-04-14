fn main() {
    let mut nums: Vec<i32> = Vec::new();
    nums.push(5); nums.push(3); nums.push(8); nums.push(1); nums.push(4);
    println!("after push: {:?}", nums);

    let popped = nums.pop().unwrap();
    println!("popped: {}", popped);
    println!("after pop: {:?}", nums);

    let doubled: Vec<i32> = nums.iter().map(|x| x * 2).collect();
    println!("doubled: {:?}", doubled);

    let evens: Vec<i32> = nums.iter().filter(|&&x| x % 2 == 0).cloned().collect();
    println!("evens: {:?}", evens);

    let mut sorted = nums.clone();
    sorted.sort();
    println!("sorted: {:?}", sorted);

    println!("contains 3: {}", nums.contains(&3));
    println!("contains 9: {}", nums.contains(&9));
    println!("len: {}", nums.len());
}
