fn main() {
    let nums: Vec<i32> = (1..=20).collect();
    println!("range: {:?}", nums);

    let evens: Vec<i32> = nums.iter().filter(|&&x| x % 2 == 0).cloned().collect();
    println!("evens: {:?}", evens);

    let squared: Vec<i32> = evens.iter().map(|&x| x * x).collect();
    println!("squared: {:?}", squared);

    let sum: i32 = squared.iter().fold(0, |acc, &x| acc + x);
    println!("sum of squared evens: {}", sum);

    let result: i32 = (1..=20)
        .filter(|x| x % 3 == 0)
        .map(|x| x + 10)
        .fold(0, |acc, x| acc + x);
    println!("chained result: {}", result);

    let labels: Vec<String> = (1..=5).map(|x| format!("item_{}", x)).collect();
    println!("labels: {:?}", labels);
}
